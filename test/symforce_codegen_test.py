import logging
import tempfile
import sys
import os

from symforce import geo
from symforce import ops
from symforce import logger
from symforce import python_util
from symforce import sympy as sm
from symforce import types as T
from symforce.codegen import CodegenMode
from symforce.codegen import Codegen
from symforce.codegen import geo_package_codegen
from symforce.codegen import codegen_util
from symforce.test_util import TestCase
from symforce.values import Values

SYMFORCE_DIR = os.path.dirname(os.path.dirname(__file__))
TEST_DATA_DIR = os.path.join(SYMFORCE_DIR, "test", "symforce_function_codegen_test_data")

# Test function
def az_el_from_point(nav_T_cam, nav_t_point, epsilon=0):
    # type: (geo.Pose3, geo.Matrix, T.Scalar) -> geo.Matrix
    """
    Transform a nav point into azimuth / elevation angles in the
    camera frame.

    Args:
        nav_T_cam (geo.Pose3): camera pose in the world
        nav_t_point (geo.Matrix): nav point
        epsilon (Scalar): small number to avoid singularities

    Returns:
        geo.Matrix: (azimuth, elevation)
    """
    cam_t_point = nav_T_cam.inverse() * nav_t_point
    x, y, z = cam_t_point
    theta = sm.atan2_safe(y, x, epsilon=epsilon)
    phi = sm.pi / 2 - sm.acos(z / (cam_t_point.norm() + epsilon))
    return geo.V2(theta, phi)


class SymforceCodegenTest(TestCase):
    """
    Test symforce.codegen.EvaluatorCodegen.
    """

    @staticmethod
    def build_values():
        # type: () -> T.Tuple[Values, Values]
        """
        Create some example input/output values.
        """
        inputs = Values()
        x, y = sm.symbols("x y")
        inputs.add(x)
        inputs.add(y)

        inputs["rot"] = geo.Rot3().symbolic("rot")

        # Test lists of objects, scalars, and Values
        inputs["rot_vec"] = [
            geo.Rot3().symbolic("rot1"),
            geo.Rot3().symbolic("rot2"),
            geo.Rot3().symbolic("rot3"),
        ]
        inputs["scalar_vec"] = [
            sm.Symbol("scalar1"),
            sm.Symbol("scalar2"),
            sm.Symbol("scalar3"),
        ]
        inputs["list_of_lists"] = [
            ops.StorageOps.symbolic(inputs["rot_vec"], "rot_vec1"),
            ops.StorageOps.symbolic(inputs["rot_vec"], "rot_vec2"),
            ops.StorageOps.symbolic(inputs["rot_vec"], "rot_vec3"),
        ]
        inputs_copy = inputs.copy()
        inputs["values_vec"] = [
            inputs_copy.symbolic("inputs_copy1"),
            inputs_copy.symbolic("inputs_copy2"),
            inputs_copy.symbolic("inputs_copy3"),
        ]
        inputs["values_vec_2D"] = [
            [inputs_copy.symbolic("inputs_copy11")],
            [inputs_copy.symbolic("inputs_copy12")],
        ]

        # Scalar
        inputs.add(sm.Symbol("constants.epsilon"))

        with inputs.scope("states"):
            # Array element, turns into std::array
            inputs["p"] = geo.V2.symbolic("p")

            # Vector element, turns into Eigen::Vector
            # inputs.add(sm.Symbol('q(0)'))

        outputs = Values()
        outputs["foo"] = x ** 2 + inputs["rot"].q.w
        outputs["bar"] = inputs.attr.constants.epsilon + sm.sin(inputs.attr.y) + x ** 2
        # Test outputing lists of objects, scalars, and Values
        outputs["scalar_vec_out"] = ops.GroupOps.compose(inputs["scalar_vec"], inputs["scalar_vec"])
        outputs["values_vec_out"] = ops.GroupOps.compose(inputs["values_vec"], inputs["values_vec"])
        outputs["values_vec_2D_out"] = ops.GroupOps.compose(
            inputs["values_vec_2D"], inputs["values_vec_2D"]
        )

        return inputs, outputs

    # -------------------------------------------------------------------------
    # Python
    # -------------------------------------------------------------------------

    def test_codegen_python(self):
        # type: () -> None
        """
        Test python code generation.
        """
        inputs, outputs = self.build_values()

        for scalar_type in ("double", "float"):
            python_func = Codegen(
                "python_function", inputs, outputs, CodegenMode.PYTHON2, scalar_type=scalar_type
            )
            shared_types = {
                "values_vec": "values_vec_t",
                "values_vec_out": "values_vec_t",
                "values_vec_2D": "values_vec_t",
                "values_vec_2D_out": "values_vec_t",
            }
            namespace = "codegen_test_python"
            codegen_data = python_func.generate_function(
                shared_types=shared_types, namespace=namespace
            )
            if scalar_type == "double":
                self.compare_or_update_directory(
                    actual_dir=codegen_data["output_dir"],
                    expected_dir=os.path.join(TEST_DATA_DIR, namespace + "_data"),
                )

            geo_package_codegen.generate(
                mode=CodegenMode.PYTHON2, output_dir=codegen_data["output_dir"]
            )

            geo_pkg = codegen_util.load_generated_package(
                os.path.join(codegen_data["output_dir"], "geo")
            )
            types_module = codegen_util.load_generated_package(
                os.path.join(codegen_data["python_types_dir"], namespace)
            )

            x = 2.0
            y = -5.0
            rot = geo_pkg.Rot3()
            rot_vec = [geo_pkg.Rot3(), geo_pkg.Rot3(), geo_pkg.Rot3()]
            scalar_vec = [1.0, 2.0, 3.0]
            list_of_lists = [rot_vec, rot_vec, rot_vec]
            values_vec = [
                types_module.values_vec_t(),
                types_module.values_vec_t(),
                types_module.values_vec_t(),
            ]
            values_vec_2D = [[types_module.values_vec_t()], [types_module.values_vec_t()]]

            states = types_module.states_t()
            states.p = [1.0, 2.0]
            constants = types_module.constants_t()
            constants.epsilon = 1e-8

            gen_module = codegen_util.load_generated_package(codegen_data["python_function_dir"])
            # TODO(nathan): Split this test into several different functions
            (
                foo,
                bar,
                scalar_vec_out,
                values_vec_out,
                values_vec_2D_out,
            ) = gen_module.python_function(
                x,
                y,
                rot,
                rot_vec,
                scalar_vec,
                list_of_lists,
                values_vec,
                values_vec_2D,
                constants,
                states,
            )
            self.assertNear(foo, x ** 2 + rot.data[3])
            self.assertNear(bar, constants.epsilon + sm.sin(y) + x ** 2)

            # Clean up
            if logger.level != logging.DEBUG:
                python_util.remove_if_exists(codegen_data["output_dir"])

    def test_function_codegen_python(self):
        # type: () -> None

        # Create the specification
        az_el_codegen = Codegen.function(
            name="az_el_from_point",
            func=az_el_from_point,
            input_types=[geo.Pose3, geo.V3, sm.Symbol],
            mode=CodegenMode.PYTHON2,
        )
        az_el_codegen_data = az_el_codegen.generate_function()

        # Compare to expected
        expected_code_file = os.path.join(TEST_DATA_DIR, "az_el_from_point.py")
        output_function = os.path.join(
            az_el_codegen_data["python_function_dir"], "az_el_from_point.py"
        )
        self.compare_or_update_file(expected_code_file, output_function)

        # Clean up
        if logger.level != logging.DEBUG:
            python_util.remove_if_exists(az_el_codegen_data["output_dir"])

    # -------------------------------------------------------------------------
    # C++
    # -------------------------------------------------------------------------

    def test_codegen_cpp(self):
        # type: () -> None
        """
        Test C++ code generation.
        """
        inputs, outputs = self.build_values()

        for scalar_type in ("double", "float"):
            cpp_func = Codegen(
                "CodegenTestCpp", inputs, outputs, CodegenMode.CPP, scalar_type=scalar_type
            )
            shared_types = {
                "values_vec": "values_vec_t",
                "values_vec_out": "values_vec_t",
                "values_vec_2D": "values_vec_t",
                "values_vec_2D_out": "values_vec_t",
            }
            namespace = "codegen_test_cpp"
            codegen_data = cpp_func.generate_function(
                shared_types=shared_types, namespace=namespace
            )

            if scalar_type == "double":
                self.compare_or_update_directory(
                    actual_dir=os.path.join(codegen_data["output_dir"]),
                    expected_dir=os.path.join(TEST_DATA_DIR, namespace + "_data"),
                )

                if not self.UPDATE:
                    try:
                        TestCase.compile_and_run_cpp(
                            os.path.join(SYMFORCE_DIR, "test"), "codegen_function_test"
                        )
                    finally:
                        if logger.level != logging.DEBUG:
                            python_util.remove_if_exists(
                                os.path.join(SYMFORCE_DIR, "test", "codegen_function_test")
                            )
                            python_util.remove_if_exists(
                                os.path.join(SYMFORCE_DIR, "test", "libsymforce_geo.so")
                            )

            # Clean up
            if logger.level != logging.DEBUG:
                python_util.remove_if_exists(codegen_data["output_dir"])

    def test_function_codegen_cpp(self):
        # type: () -> None

        # Create the specification
        az_el_codegen = Codegen.function(
            name="AzElFromPoint",
            func=az_el_from_point,
            input_types=[geo.Pose3, geo.V3, sm.Symbol],
            mode=CodegenMode.CPP,
        )
        az_el_codegen_data = az_el_codegen.generate_function()

        # Compare to expected
        expected_code_file = os.path.join(TEST_DATA_DIR, "az_el_from_point.h")
        output_function = os.path.join(az_el_codegen_data["cpp_function_dir"], "az_el_from_point.h")
        self.compare_or_update_file(expected_code_file, output_function)

        # Clean up
        if logger.level != logging.DEBUG:
            python_util.remove_if_exists(az_el_codegen_data["output_dir"])

    def test_cpp_nan(self):
        # type: () -> None
        inputs = Values()
        inputs["R1"] = geo.Rot3.symbolic("R1")
        inputs["e"] = sm.Symbol("e")
        dist_to_identity = geo.M(
            inputs["R1"].local_coordinates(geo.Rot3.identity(), epsilon=inputs["e"])
        ).squared_norm()
        dist_D_R1 = dist_to_identity.diff(inputs["R1"].q.w)  # type: ignore

        namespace = "codegen_nan_test"
        cpp_func = Codegen(
            name="IdentityDistJacobian",
            inputs=inputs,
            outputs=Values(dist_D_R1=dist_D_R1),
            return_key="dist_D_R1",
            mode=CodegenMode.CPP,
            scalar_type="double",
        )
        codegen_data = cpp_func.generate_function(namespace=namespace)

        # Compare the function file
        self.compare_or_update_directory(
            actual_dir=os.path.join(codegen_data["output_dir"]),
            expected_dir=os.path.join(TEST_DATA_DIR, namespace + "_data"),
        )

        if not self.UPDATE:
            try:
                TestCase.compile_and_run_cpp(
                    package_dir=os.path.join(SYMFORCE_DIR, "test"),
                    executable_names="codegen_nan_test",
                    make_args=("codegen_nan_test",),
                )
            finally:
                if logger.level != logging.DEBUG:
                    python_util.remove_if_exists(
                        os.path.join(SYMFORCE_DIR, "test", "codegen_nan_test")
                    )
                    python_util.remove_if_exists(
                        os.path.join(SYMFORCE_DIR, "test", "libsymforce_geo.so")
                    )
        # Clean up
        if logger.level != logging.DEBUG:
            python_util.remove_if_exists(codegen_data["output_dir"])

    def test_multi_function_codegen_cpp(self):
        # type: () -> None
        inputs, outputs_1 = self.build_values()
        outputs_2 = Values()
        outputs_2["foo"] = inputs["y"] ** 3 + inputs["x"]

        cpp_func_1 = Codegen(
            name="CodegenMultiFunctionTest1",
            inputs=Values(inputs=inputs),
            outputs=Values(outputs_1=outputs_1),
            mode=CodegenMode.CPP,
        )
        cpp_func_2 = Codegen(
            name="CodegenMultiFunctionTest2",
            inputs=Values(inputs=inputs),
            outputs=Values(outputs_2=outputs_2),
            mode=CodegenMode.CPP,
        )

        namespace = "codegen_multi_function"
        output_dir = tempfile.mkdtemp(prefix="sf_codegen_multiple_functions_", dir="/tmp")
        logger.debug("Creating temp directory: {}".format(output_dir))

        shared_types = {
            "inputs.values_vec": "values_vec_t",
            "outputs_1.values_vec_out": "values_vec_t",
            "inputs.values_vec_2D": "values_vec_t",
            "outputs_1.values_vec_2D_out": "values_vec_t",
        }
        cpp_func_1.generate_function(
            output_dir=output_dir, shared_types=shared_types, namespace=namespace
        )
        shared_types["inputs"] = namespace + ".inputs_t"
        cpp_func_2.generate_function(
            output_dir=output_dir, shared_types=shared_types, namespace=namespace
        )

        # Compare the generated types
        self.compare_or_update_directory(
            output_dir, expected_dir=os.path.join(TEST_DATA_DIR, namespace + "_data"),
        )

        if not self.UPDATE:
            try:
                TestCase.compile_and_run_cpp(
                    package_dir=os.path.join(SYMFORCE_DIR, "test"),
                    executable_names="codegen_multi_function_test",
                    make_args=("codegen_multi_function_test",),
                )
            finally:
                if logger.level != logging.DEBUG:
                    python_util.remove_if_exists(
                        os.path.join(SYMFORCE_DIR, "test", "codegen_multi_function_test")
                    )
                    python_util.remove_if_exists(
                        os.path.join(SYMFORCE_DIR, "test", "libsymforce_geo.so")
                    )

        # Clean up
        if logger.level != logging.DEBUG:
            python_util.remove_if_exists(output_dir)

    def test_invalid_codegen_raises(self):
        # type: () -> None
        """
        Tests:
            Codegen outputs must be a function of given inputs
            Codegen input/output names must be valid variable names
        """
        # Outputs have symbols not present in inputs
        x = sm.Symbol("x")
        y = sm.Symbol("y")
        inputs = Values(input=x)
        outputs = Values(output=x + y)
        self.assertRaises(AssertionError, Codegen, "test", inputs, outputs, CodegenMode.CPP)

        # Inputs or outputs have keys that aren't valid variable names
        invalid_name_values = Values()
        invalid_name_values["1"] = x
        valid_name_values = Values(x=x)
        self.assertRaises(
            AssertionError, Codegen, "test", invalid_name_values, valid_name_values, CodegenMode.CPP
        )
        self.assertRaises(
            AssertionError, Codegen, "test", valid_name_values, invalid_name_values, CodegenMode.CPP
        )
        name_with_spaces = Values()
        name_with_spaces[" spa ces "] = x
        self.assertRaises(
            AssertionError, Codegen, "test", name_with_spaces, valid_name_values, CodegenMode.CPP
        )
        self.assertRaises(
            AssertionError, Codegen, "test", valid_name_values, name_with_spaces, CodegenMode.CPP
        )

        # Inputs have non-unique symbols
        inputs = Values(in_x=x, in_y=x)
        outputs = Values(out_x=x)
        self.assertRaises(AssertionError, Codegen, "test", inputs, outputs, CodegenMode.CPP)

        # Inputs and outputs have non-unique keys
        inputs = Values(x=x)
        outputs = Values(x=x)
        self.assertRaises(AssertionError, Codegen, "test", inputs, outputs, CodegenMode.CPP)


if __name__ == "__main__":
    TestCase.main()
