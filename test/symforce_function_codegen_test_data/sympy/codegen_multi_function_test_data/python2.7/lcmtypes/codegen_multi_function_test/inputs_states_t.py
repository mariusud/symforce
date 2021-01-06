"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct


class inputs_states_t(object):
    __slots__ = ["p"]

    __typenames__ = ["double"]

    __dimensions__ = [[2]]

    def __init__(self):
        self.p = [0.0 for dim0 in range(2)]

    def encode(self):
        buf = BytesIO()
        buf.write(inputs_states_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">2d", *self.p[:2]))

    def decode(data):
        if hasattr(data, "read"):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != inputs_states_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return inputs_states_t._decode_one(buf)

    decode = staticmethod(decode)

    def _decode_one(buf):
        self = inputs_states_t()
        self.p = struct.unpack(">2d", buf.read(16))
        return self

    _decode_one = staticmethod(_decode_one)

    _hash = None

    def _get_hash_recursive(parents):
        if inputs_states_t in parents:
            return 0
        tmphash = (0x21F0A3981EF33559) & 0xFFFFFFFFFFFFFFFF
        tmphash = (((tmphash << 1) & 0xFFFFFFFFFFFFFFFF) + (tmphash >> 63)) & 0xFFFFFFFFFFFFFFFF
        return tmphash

    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if inputs_states_t._packed_fingerprint is None:
            inputs_states_t._packed_fingerprint = struct.pack(
                ">Q", inputs_states_t._get_hash_recursive([])
            )
        return inputs_states_t._packed_fingerprint

    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)
