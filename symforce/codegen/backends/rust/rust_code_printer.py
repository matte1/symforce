# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

from enum import Enum

import sympy
from sympy.core.singleton import S
from sympy.core.numbers import Rational
from sympy.codegen.ast import float32
from sympy.codegen.ast import float64
from sympy.codegen.ast import real
from sympy.printing.rust import RustCodePrinter as SympyRustCodePrinter

from symforce import typing as T


class ScalarType(Enum):
    FLOAT = float32
    DOUBLE = float64


class RustCodePrinter(SympyRustCodePrinter):
    """
    SymForce code printer for Rust. Based on the SymPy C printer.
    """

    def __init__(
        self,
        scalar_type: ScalarType,
        settings: T.Optional[T.Dict[str, T.Any]] = None,
        override_methods: T.Optional[T.Dict[sympy.Function, str]] = None,
    ) -> None:
        super().__init__(dict(settings or {}))

        self.scalar_type = scalar_type.value
        self.override_methods = override_methods or {}
        for expr, name in self.override_methods.items():
            self._set_override_methods(expr, name)

    def _set_override_methods(self, expr: sympy.Function, name: str) -> None:
        method_name = f"_print_{str(expr)}"

        def _print_expr(expr: sympy.Expr) -> str:
            expr_string = ", ".join(map(self._print, expr.args))
            return f"{name}({expr_string})"

        setattr(self, method_name, _print_expr)


    def _print_ImaginaryUnit(self, expr: sympy.Expr) -> str:
        raise NotImplementedError(
            "You tried to print an expression that contains the imaginary unit `i`.  SymForce does "
            "not support complex numbers in Rust"
        )

    def _print_Float(self, flt: sympy.Float) -> str:
        """
        Customizations:
            * Cast all literals to Scalar at compile time instead of using a suffix at codegen time
        """
        if self.scalar_type is float32:
            return f"{super()._print_Float(flt)}_f32"
        if self.scalar_type is float64:
            return f"{super()._print_Float(flt)}_f64"

        raise NotImplementedError(f"Scalar type {self.scalar_type} not supported")

    def _print_Pi(self, expr, _type=False):
        if self.scalar_type is float32:
            return f"core::f32::consts::PI"
        if self.scalar_type is float64:
            return f"core::f64::consts::PI"

    def _print_Max(self, expr: sympy.Max) -> str:
        """
        Customizations:
            * The first argument calls the max method on the second argument.
        """
        return "{}.max({})".format(self._print(expr.args[0]), self._print(expr.args[1]))

    def _print_Min(self, expr: sympy.Min) -> str:
        """
        Customizations:
            * The first argument calls the min method on the second argument.
        """
        return "{}.min({})".format(self._print(expr.args[0]), self._print(expr.args[1]))

    def _print_log(self, expr: sympy.log) -> str:
        """
        Customizations:
        """
        return "{}.ln()".format(self._print(expr.args[0]))


    def _print_Rational(self, expr):
        p, q = int(expr.p), int(expr.q)

        float_suffix = None
        if self.scalar_type is float32:
            float_suffix = 'f32'
        elif self.scalar_type is float64:
            float_suffix = 'f64'

        return '%d_%s/%d.0' % (p, float_suffix, q)


    def _print_Exp1(self, expr, _type=False):
        if self.scalar_type is float32:
            return 'core::f32::consts::E'
        elif self.scalar_type is float64:
            return 'core::f64::consts::E'
