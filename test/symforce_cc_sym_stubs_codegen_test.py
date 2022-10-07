# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

import os
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

from symforce import path_util
from symforce import typing as T
from symforce.codegen import template_util
from symforce.test_util import TestCase


class SymforceCCSymStubsCodegenTest(TestCase):
    def cc_sym_stubgen_output(self) -> str:
        """
        Returns the contents of the stub file produced by pybind11-stubgen on module cc_sym
        """
        output_dir = Path(self.make_output_dir("sf_cc_sym_stubgen_output"))

        subprocess.check_call(
            [
                "pybind11-stubgen",
                "--bare-numpy-ndarray",
                "--no-setup-py",
                "-o",
                output_dir,
                "cc_sym",
            ],
            env=dict(
                os.environ,
                PYTHONPATH=os.pathsep.join(
                    [os.environ.get("PYTHONPATH", ""), os.fspath(path_util.cc_sym_install_dir())]
                ),
            ),
        )
        generated_file = output_dir / "cc_sym-stubs" / "__init__.pyi"

        return generated_file.read_text()

    def test_generate_cc_sym_stubs(self) -> None:
        output_dir = Path(self.make_output_dir("sf_cc_sym_stubs_codegen_test"))

        stubgen_output = self.cc_sym_stubgen_output()

        # Change return type of Values.at to be Any rather than object
        stubgen_output = re.sub(r"(def at\([^)]*\) ->) object", r"\1 typing.Any", stubgen_output)

        # Change eigen return types to Any
        stubgen_output = re.sub("Eigen::Matrix<int, -1, 1, 0, -1, 1>", "typing.Any", stubgen_output)

        # Change type of OptimizationStats.best_linearization to be Optional[Linearization]
        stubgen_output = re.sub(
            "def best_linearization\(self\) -> object",
            "def best_linearization(self) -> typing.Optional[Linearization]",
            stubgen_output,
        )

        @dataclass
        class TypeStubParts:
            lcm_include_type_names: T.List[str]
            sym_include_type_names: T.List[str]
            third_party_includes: T.List[str]
            cleaned_up_stubgen_output: str

        pybind_dir = path_util.symforce_dir() / "symforce" / "pybind"

        template_util.render_template(
            template_dir=pybind_dir,
            template_path="cc_sym.pyi.jinja",
            data={
                "spec": TypeStubParts(
                    lcm_include_type_names=[
                        "index_entry_t",
                        "index_t",
                        "key_t",
                        "linearized_dense_factor_t",
                        "optimization_iteration_t",
                        "optimization_stats_t",
                        "optimizer_params_t",
                        "sparse_matrix_structure_t",
                        "values_t",
                    ],
                    sym_include_type_names=[
                        "ATANCameraCal",
                        "DoubleSphereCameraCal",
                        "EquirectangularCameraCal",
                        "LinearCameraCal",
                        "PolynomialCameraCal",
                        "Pose2",
                        "Pose3",
                        "Rot2",
                        "Rot3",
                        "SphericalCameraCal",
                    ],
                    third_party_includes=["import scipy"],
                    cleaned_up_stubgen_output=stubgen_output,
                )
            },
            output_path=str(output_dir / "cc_sym.pyi"),
        )

        self.compare_or_update_file(
            new_file=output_dir / "cc_sym.pyi", path=pybind_dir / "cc_sym.pyi"
        )


if __name__ == "__main__":
    TestCase.main()
