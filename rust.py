import numpy as np

import symforce

symforce.set_symbolic_api("symengine")
symforce.set_log_level("warning")

# Set epsilon to a symbol for safe code generation.  For more information, see the Epsilon tutorial:
# https://symforce.org/tutorials/epsilon_tutorial.html
symforce.set_epsilon_to_symbol()


import symforce.symbolic as sf
from symforce import codegen
from symforce.codegen import CppConfig
from symforce.values import Values
from dataclasses import dataclass

def foo(x: sf.Scalar, y: sf.Scalar) -> sf.Scalar:
    return sf.V1(x*x + y*y)

cg = codegen.Codegen.function(
    func=foo,
    config=codegen.RustConfig(),
)

codegen_data = cg.with_linearization(
    which_args=["x", "y"],
    linearization_mode=codegen.LinearizationMode.FULL_LINEARIZATION
).generate_function()

for f in codegen_data.generated_files:
    with open(f, "r") as file:
        print(file.read())