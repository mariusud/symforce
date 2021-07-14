from __future__ import annotations

import collections
import contextlib
import numpy as np

from symforce import logger
from symforce import sympy as sm
from symforce import types as T
from symforce import geo
from symforce import cam
from symforce import initialization
from symforce import ops
from symforce import python_util
from symforce.ops.interfaces import Storage

from .attr_accessor import AttrAccessor
from .index_entry import IndexEntry


class Values:
    """
    Ordered dictionary serializable storage. This class is the basis for specifying both inputs
    and outputs in symforce. The hierarchy of nested values get code generated into types, and
    several methods of access and introspection are provided that reduce downstream complexity.

    Includes standard operator[] access to keys and values.

    Attributes:
        attr: Access with dot notation, such as `v.attr.states.x0` instead of `v['states.x0']`.
    """

    def __init__(self, **kwargs: T.Any) -> None:
        """
        Create like a Python dict.

        Args:
            kwargs (dict): Initial values
        """
        # Underlying storage - ordered dictionary
        self.dict: T.Dict[str, T.Any] = collections.OrderedDict()

        # Allow dot notation through this member
        # ex: v.attr.foo.bar = 12
        self.attr = AttrAccessor(self.dict)

        # Create context manager helpers for .scope()
        self.__scopes__: T.List[str] = []
        self.symbol_name_scoper = initialization.create_named_scope(sm.__scopes__)
        self.key_scoper = initialization.create_named_scope(self.__scopes__)

        # Fill with construction kwargs
        self.update(kwargs)

    # -------------------------------------------------------------------------
    # Dict API
    # -------------------------------------------------------------------------

    def keys(self) -> T.List[str]:
        """
        An object providing a view on contained keys.
        """
        return list(self.dict.keys())

    def values(self) -> T.List[T.Any]:
        """
        An object providing a view on contained values.
        """
        return list(self.dict.values())

    def items(self) -> T.List[T.Tuple[str, T.Any]]:
        """
        An object providng a view on contained key/value pairs.
        """
        return list(self.dict.items())

    def get(self, key: str, default: T.Any = None) -> T.Any:
        """
        Return the value for key if key is in the dictionary, else default.

        Args:
            key (str):
            default (any): Default value if key is not present.

        Returns:
            any: self[key] or default
        """
        return self.dict.get(key, default)

    def update(self, other: T.Union[Values, T.Mapping[str, T.Any]]) -> None:
        """
        Updates keys in this Values from those of the other.
        """
        for key, value in other.items():
            self[key] = value

    def copy(self) -> Values:
        """
        Returns a deepcopy of this Values.
        """
        return self.from_storage(self.to_storage())

    # -------------------------------------------------------------------------
    # Serialization
    # -------------------------------------------------------------------------

    def index(self) -> T.Dict[str, IndexEntry]:
        """
        Returns the index with structural information to reconstruct this values
        in :func:`from_storage()`.
        """
        return Values.get_index_from_items(self.items())

    @staticmethod
    def get_index_from_items(items: T.Iterable[T.Tuple[str, T.Any]]) -> T.Dict[str, IndexEntry]:
        """
        Builds an index from a list of key/value pairs of objects. This function
        can be called recursively either for the items of a Values object or for the
        items of a list (using e.g. zip(my_keys, my_list), where my_keys are some
        arbitrary names for each element in my_list)
        """
        offset = 0
        index_dict = collections.OrderedDict()
        for name, value in items:

            entry_helper = lambda datatype=type(value), shape=None, item_index=None: IndexEntry(
                offset=offset,
                storage_dim=ops.StorageOps.storage_dim(value),
                stored_datatype=datatype,
                shape=shape,
                item_index=item_index,
            )

            if isinstance(value, Values):
                entry = entry_helper(item_index=value.index())
            elif isinstance(value, np.ndarray):
                entry = entry_helper(shape=value.shape)
            elif isinstance(value, geo.Matrix):
                entry = entry_helper(shape=value.shape, datatype=geo.Matrix)
            elif isinstance(value, (sm.Expr, sm.Symbol, int, float)):
                entry = entry_helper(datatype=T.Scalar)
            elif isinstance(value, (list, tuple)):
                assert all([type(v) == type(value[0]) for v in value])
                name_list = [f"{name}_{i}" for i in range(len(value))]
                item_index = Values.get_index_from_items(zip(name_list, value))
                entry = entry_helper(item_index=item_index)
            else:
                entry = entry_helper()

            index_dict[name] = entry
            offset += entry.storage_dim

        return index_dict

    @staticmethod
    def _items_recursive(v: T.Union[T.Sequence, Values, np.ndarray]) -> T.List[T.Tuple[str, T.Any]]:
        """
        Helper for items_recursive that handles sequences
        """
        flat_items: T.List[T.Tuple[str, T.Any]] = []

        if isinstance(v, Values):
            key_value_pairs = v.items()
        else:
            key_value_pairs = [(str(i), sub_value) for i, sub_value in enumerate(v)]

        for sub_key, sub_value in key_value_pairs:
            if isinstance(v, Values):
                formatted_sub_key = f".{sub_key}"
            else:
                formatted_sub_key = f"[{sub_key}]"

            if isinstance(sub_value, (Values, list, tuple, np.ndarray)):
                flat_items.extend(
                    (f"{formatted_sub_key}{sub_sub_key}", sub_sub_value)
                    for sub_sub_key, sub_sub_value in Values._items_recursive(sub_value)
                )
            else:
                flat_items.append((formatted_sub_key, sub_value))

        return flat_items

    def items_recursive(self) -> T.List[T.Tuple[str, T.Any]]:
        """
        Returns a flat list of key/value pairs for every element in this object in insertion order
        of highest level dot seperated key.
        """
        return [(key[len(".") :], value) for key, value in Values._items_recursive(self)]

    def keys_recursive(self) -> T.List[str]:
        """
        Returns a flat list of unique keys for every element in this object in insertion order
        of highest level dot seperated key.
        """
        items = self.items_recursive()
        if len(items) == 0:
            return []
        return [key for key, _ in items]

    def values_recursive(self) -> T.List[T.Any]:
        """
        Returns a flat list of elements stored in this Values object in insertion order
        of highest level dot seperated key.
        """
        items = self.items_recursive()
        if len(items) == 0:
            return []
        return [value for _, value in items]

    def subkeys_recursive(self) -> T.List[str]:
        """
        Returns a flat list of subkeys for every element in this object in insertion order
        of highest level dot seperated key. Unlike keys_recursive, subkeys_recursive does not
        return dot-separated keys.
        """
        return [k.split(".")[-1] for k in self.keys_recursive()]

    def scalar_keys_recursive(self) -> T.List[str]:
        """
        Returns a flat list of keys to each scalar in this object in insertion order
        of highest level dot seperated key.
        """
        flat_scalar_keys: T.List[str] = []
        for key, value in self.items_recursive():
            storage_dim = ops.StorageOps.storage_dim(value)
            if storage_dim > 1:
                flat_scalar_keys.extend(f"{key}[{i}]" for i in range(storage_dim))
            else:
                flat_scalar_keys.append(key)
        return flat_scalar_keys

    # -------------------------------------------------------------------------
    # Storage concept - see symforce.ops.storage_ops
    # -------------------------------------------------------------------------

    def storage_dim(self) -> int:
        """
        Dimension of the underlying storage
        """
        return sum([ops.StorageOps.storage_dim(v) for v in self.values()])

    def to_storage(self) -> T.List[T.Any]:
        """
        Returns a flat list of unique values for every scalar element in this object.
        """
        return [scalar for v in self.values() for scalar in ops.StorageOps.to_storage(v)]

    @classmethod
    def from_storage_index(
        cls, vector_values: T.List[T.Scalar], indices: T.Mapping[str, IndexEntry]
    ) -> Values:
        """
        Takes a vectorized values and corresponding indices and reconstructs the original form.
        Reverse of :func:`to_storage()`.

        Args:
            vector_values (list): Vectorized values
            indices (dict(str, list)): Dict of key to the source (index, datatype, shape, item_index)
        """
        values = cls()
        for name, entry in indices.items():
            vec = vector_values[entry.offset : entry.offset + entry.storage_dim]

            datatype = entry.datatype()
            if issubclass(datatype, T.Scalar):
                values[name] = vec[0]
            elif issubclass(datatype, Values):
                assert entry.item_index is not None
                values[name] = cls.from_storage_index(vec, entry.item_index)
            elif issubclass(datatype, np.ndarray):
                assert entry.shape is not None
                values[name] = np.array(vec).reshape(*entry.shape)
            elif issubclass(datatype, geo.Matrix):
                assert entry.shape is not None
                values[name] = datatype(vec).reshape(*entry.shape)
            elif issubclass(datatype, (list, tuple)):
                assert entry.item_index is not None
                values[name] = datatype(cls.from_storage_index(vec, entry.item_index).values())
            else:
                values[name] = ops.StorageOps.from_storage(datatype, vec)

        return values

    def from_storage(self, elements: T.List[T.Scalar]) -> Values:
        """
        Create a Values object with the same structure as self but constructed
        from a flat list representation. Opposite of `.to_storage()`.
        """
        assert len(elements) == self.storage_dim()
        return Values.from_storage_index(elements, self.index())

    def symbolic(self, name: str, **kwargs: T.Dict) -> Values:
        """
        Create a Values object with the same structure as self, where each element
        is a symbolic element with the given name prefix. Kwargs are forwarded
        to sm.Symbol (for example, sympy assumptions).
        """
        symbolic_values = Values()
        for k, v in self.items():
            symbolic_values[k] = ops.StorageOps.symbolic(v, f"{name}_{k}", **kwargs)
        return symbolic_values

    def evalf(self) -> Values:
        """
        Numerical evaluation.
        """
        return self.from_storage_index(
            [ops.StorageOps.evalf(e) for e in self.to_storage()], self.index()
        )

    # -------------------------------------------------------------------------
    # Group concept - see symforce.ops.group_ops
    # -------------------------------------------------------------------------

    def identity(self) -> Values:
        """
        Returns Values object with same structure as self, but with each element as an identity element.
        """
        identity_values = Values()
        for k, v in self.items():
            identity_values[k] = ops.GroupOps.identity(v)
        return identity_values

    def compose(self, other: Values) -> Values:
        """
        Element-wise compose of each element with another Values of identical structure
        """
        assert self.index() == other.index()
        composed_values = Values()
        for k, v in self.items():
            composed_values[k] = ops.GroupOps.compose(v, other[k])
        return composed_values

    def inverse(self) -> Values:
        """
        Element-wise inverse of this Values
        """
        inverse_values = Values()
        for k, v in self.items():
            inverse_values[k] = ops.GroupOps.inverse(v)
        return inverse_values

    # -------------------------------------------------------------------------
    # Lie group concept - see symforce.ops.lie_group_ops
    # -------------------------------------------------------------------------

    def tangent_dim(self) -> int:
        """
        Sum of the dimensions of the embedded manifold of each element
        """
        return sum([ops.LieGroupOps.tangent_dim(v) for v in self.values()])

    def from_tangent(self, vec: T.List[T.Scalar], epsilon: T.Scalar = 0) -> Values:
        """
        Returns a Values object with the same structure as self, but by computing
        each element using the mapping from its corresponding tangent space vector
        about identity into a group element.
        """
        updated_values = Values()
        inx = 0
        for k, v in self.items():
            dim = ops.LieGroupOps.tangent_dim(v)
            updated_values[k] = ops.LieGroupOps.from_tangent(v, vec[inx : inx + dim], epsilon)
            inx += dim
        return updated_values

    def to_tangent(self, epsilon: T.Scalar = 0) -> T.List[T.Scalar]:
        """
        Returns flat vector representing concatentated tangent spaces of each element.
        """
        vec = []
        for v in self.values():
            vec.extend(ops.LieGroupOps.to_tangent(v, epsilon))
        return vec

    def retract(self, vec: T.List[T.Scalar], epsilon: T.Scalar = 0) -> Values:
        """
        Apply a pertubation vec in the concatenated tangent spaces of each element. Often used in
        optimization to update nonlinear values from an update step in the tangent space.

        NOTE(aaron): We have to override the default LieGroup implementation of retract because not
        all values we can store here obey retract(a, vec) = compose(a, from_tangent(vec))
        """
        retracted_values = Values()
        inx = 0
        for k, v in self.items():
            dim = ops.LieGroupOps.tangent_dim(v)
            retracted_values[k] = ops.LieGroupOps.retract(v, vec[inx : inx + dim], epsilon)
            inx += dim
        return retracted_values

    def local_coordinates(self, b: Values, epsilon: T.Scalar = 0) -> T.List[T.Scalar]:
        """
        Computes a pertubation in the combined tangent space around self to produce b. Often used
        in optimization to minimize the distance between two group elements.

        NOTE(aaron): We have to override the default LieGroup implementation of local_coordinates
        because not all values we can store here obey
        local_coordinates(a, b) = to_tangent(between(a, b))
        """
        vec = []
        for va, vb in zip(self.values(), b.values()):
            vec.extend(ops.LieGroupOps.local_coordinates(va, vb, epsilon))
        return vec

    def storage_D_tangent(self) -> geo.Matrix:
        """
        Returns a matrix with dimensions (storage_dim x tangent_dim) which represents
        the jacobian of the flat storage space of self wrt to the flat tangent space of
        self. The resulting jacobian is a block diagonal matrix, where each block corresponds
        to the storage_D_tangent for a single element or is zero.
        """
        storage_D_tangent = geo.Matrix(self.storage_dim(), self.tangent_dim()).zero()
        s_inx = 0
        t_inx = 0
        for v in self.values():
            s_dim = ops.StorageOps.storage_dim(v)
            t_dim = ops.LieGroupOps.tangent_dim(v)
            storage_D_tangent[
                s_inx : s_inx + s_dim, t_inx : t_inx + t_dim
            ] = ops.LieGroupOps.storage_D_tangent(v)
            s_inx += s_dim
            t_inx += t_dim
        return storage_D_tangent

    def tangent_D_storage(self) -> geo.Matrix:
        """
        Returns a matrix with dimensions (tangent_dim x storage_dim) which represents
        the jacobian of the flat tangent space of self wrt to the flat storage space of
        self. The resulting jacobian is a block diagonal matrix, where each block corresponds
        to the tangent_D_storage for a single element or is zero.
        """
        tangent_D_storage = geo.Matrix(self.tangent_dim(), self.storage_dim()).zero()
        t_inx = 0
        s_inx = 0
        for v in self.values():
            t_dim = ops.LieGroupOps.tangent_dim(v)
            s_dim = ops.StorageOps.storage_dim(v)
            tangent_D_storage[
                t_inx : t_inx + t_dim, s_inx : s_inx + s_dim
            ] = ops.LieGroupOps.tangent_D_storage(v)
            t_inx += t_dim
            s_inx += s_dim
        return tangent_D_storage

    # -------------------------------------------------------------------------
    # Printing
    # -------------------------------------------------------------------------

    def format(self, indent: int = 0) -> str:
        """
        Pretty format as an indented tree.

        Args:
            indent (int): Number of spaces to indent

        Returns:
            str:
        """
        lines = []
        lines.append(self.__class__.__name__ + "(")
        for key, value in self.items():
            if isinstance(value, Values):
                value_str = value.format(indent=indent + 2)
            else:
                value_str = str(value).strip()

            lines.append(f"  {key}: {value_str},")
        lines.append(")")
        indent_str = " " * indent
        return "\n".join(indent_str + line for line in lines)

    def __repr__(self) -> str:
        """
        String representation, simply calls :func:`format()`.
        """
        return self.format()

    # -------------------------------------------------------------------------
    # Dict magic methods
    # -------------------------------------------------------------------------

    def _get_subvalues_key_and_indices(
        self, key: str, create: bool = False
    ) -> T.Tuple[Values, str, T.List[int]]:
        """
        Given a key, compute the full key name by applying name scopes and
        the innermost values that contains that key. Return the innermost values,
        the child key within that, and the attached indices.

        Example:
            >>> v = Values(a=1, b=Values(c=3, d=Values(e=4, f=[[5, 6], [7, 5]])))
            >>> subvalues, key, indices = v._get_subvalues_and_key('b.d.f[1][0]')
            >>> assert subvalues == v['b.d']
            >>> assert key == 'f'
            >>> assert indices == [1, 0]

        Args:
            key (str):
            create (bool): If True, create inner Values along the way

        Returns:
            Values: Innermost sub-values containing key
            str: Key name within the values
            T.List[int]: The indices used to index into the key's value
        """
        # Prepend the key scopes if not the latest symbol scopes already
        key_scope_is_subset = sm.__scopes__[-len(self.__scopes__) :] == self.__scopes__
        if len(sm.__scopes__) > len(self.__scopes__) and key_scope_is_subset:
            full_key = key
        else:
            full_key = ".".join(self.__scopes__ + [key])

        split_key = full_key.split(".")
        *key_path, key_name = split_key

        values = self
        for i, part in enumerate(key_path):
            base, indices = python_util.base_and_indices(part)
            if base not in values.dict:
                if not create:
                    return Values(), key_name, []
                assert indices == []
                values.dict[base] = Values()

            sub_values_or_sequence = values.dict[base]
            for i in indices:
                sub_values_or_sequence = sub_values_or_sequence[i]
            values = sub_values_or_sequence
            assert isinstance(values, Values), 'Cannot set "{}", "{}" not a Values!'.format(
                full_key, ".".join(split_key[: i + 1])
            )

        key_name_base, key_name_indices = python_util.base_and_indices(key_name)
        return values, key_name_base, key_name_indices

    def __getitem__(self, key: str) -> T.Any:
        values, key_name, indices = self._get_subvalues_key_and_indices(key)
        if not key_name.isidentifier():
            raise python_util.InvalidPythonIdentifierError(key_name)
        item = values.dict[key_name]
        for i in indices:
            item = item[i]
        return item

    def __setitem__(self, key: str, value: T.Any) -> None:
        values, key_name, indices = self._get_subvalues_key_and_indices(key, create=True)
        if not key_name.isidentifier():
            raise python_util.InvalidPythonIdentifierError(key_name)
        if not indices:
            values.dict[key_name] = value
        else:
            item = values.dict[key_name]
            for i in indices[:-1]:
                item = item[i]
            item[indices[-1]] = value

    def __delitem__(self, key: str) -> None:
        values, key_name, indices = self._get_subvalues_key_and_indices(key)
        if not key_name.isidentifier():
            raise python_util.InvalidPythonIdentifierError(key_name)
        if not indices:
            del values.dict[key_name]
        else:
            item = values.dict[key_name]
            for i in indices[:-1]:
                item = item[i]
            del item[indices[-1]]

    def __contains__(self, key: str) -> bool:
        values, key_name, indices = self._get_subvalues_key_and_indices(key)
        if not key_name.isidentifier():
            raise python_util.InvalidPythonIdentifierError(key_name)
        if not indices:
            return values.dict.__contains__(key_name)
        else:
            try:
                item = values.dict[key_name]
            except KeyError:
                return False
            try:
                for i in indices:
                    item = item[i]
            except IndexError:
                return False
            return True

    # -------------------------------------------------------------------------
    # Name scope management
    # -------------------------------------------------------------------------

    @contextlib.contextmanager
    def scope(self, scope: str) -> T.Iterator[None]:
        """
        Context manager to apply a name scope to both keys added to the values
        and new symbols created within the with block.
        """
        with self.symbol_name_scoper(scope), self.key_scoper(scope):
            yield None

    def _remove_scope(self, key: str) -> str:
        """
        Strips the current Values scope off of the given key if present.
        """
        prefix = ".".join(self.__scopes__) + "."
        return key[key.startswith(prefix) and len(prefix) :]

    def add(self, value: T.Union[str, sm.Symbol], **kwargs: T.Any) -> None:
        """
        Add a symbol into the values using its given name, either a Symbol or a string.
        Allows avoiding duplication of the sort `v['foo'] = sm.Symbol('foo')`.

        Args:
            value (Symbol or str):
        """
        if isinstance(value, sm.Symbol):
            self[self._remove_scope(value.name)] = value
        elif isinstance(value, str):
            symbol = sm.Symbol(value, **kwargs)
            self[self._remove_scope(symbol.name)] = symbol
        else:
            raise NameError("Expr of type {} has no .name".format(type(value)))

    # -------------------------------------------------------------------------
    # Miscellaneous helpers
    # -------------------------------------------------------------------------

    def __eq__(self, other: T.Any) -> bool:
        """
        Exact equality check.
        """
        if isinstance(other, Values):
            return self.to_storage() == other.to_storage() and self.index() == other.index()
        else:
            return False

    def subs(self, *args: T.Any, **kwargs: T.Any) -> Values:
        """
        Substitute given values of each scalar element into a new instance.
        """
        return self.from_storage(
            [s.subs(*args, **kwargs) if hasattr(s, "subs") else s for s in self.to_storage()]
        )

    def simplify(self) -> Values:
        """
        Simplify each scalar element into a new instance.
        """
        return self.from_storage(sm.simplify(sm.Matrix(self.to_storage())))


from symforce.ops.impl.class_lie_group_ops import ClassLieGroupOps

ops.LieGroupOps.register(Values, ClassLieGroupOps)
