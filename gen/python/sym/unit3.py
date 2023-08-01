# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     geo_package/CLASS.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------

import math
import random
import typing as T

import numpy

from .rot3 import Rot3

# isort: split
from .ops import unit3 as ops


class Unit3(object):
    """
    Autogenerated Python implementation of :py:class:`symforce.geo.unit3.Unit3`.

    Direction in R^3, represented as a :class:`Rot3 <symforce.geo.rot3.Rot3>` that transforms
    [0, 0, 1] to the desired direction.

    The storage is therefore a quaternion and the tangent space is 2 dimensional.
    Most operations are implemented using operations from :class:`Rot3 <symforce.geo.rot3.Rot3>`.

    Note: an alternative implementation could directly store a unit vector and define its boxplus
    manifold as described in Appendix B.2 of [Hertzberg 2013]. This can be done by finding the
    Householder reflector of x and use it to transform the exponential map of delta, which is a
    small perturbation in the tangent space (R^2). Namely::

        x.retract(delta) = x [+] delta = Rx * Exp(delta), where
        Exp(delta) = [sinc(||delta||) * delta, cos(||delta||)], and
        Rx = (I - 2 vv^T / (v^Tv))X, v = x - e_z != 0, X is a matrix negating 2nd vector component
        = I                     , x = e_z

    [Hertzberg 2013] Integrating Generic Sensor Fusion Algorithms with Sound State Representations
    through Encapsulation of Manifolds
    """

    __slots__ = ["data"]

    def __repr__(self):
        # type: () -> str
        return "<{} {}>".format(self.__class__.__name__, self.data)

    # --------------------------------------------------------------------------
    # Handwritten methods included from "custom_methods/unit3.py.jinja"
    # --------------------------------------------------------------------------

    def __init__(self, rot3=None):
        # type: (Rot3) -> None
        if rot3 is None:
            self.data = ops.GroupOps.identity().data  # type: T.List[float]
        else:
            self.data = rot3.data

    # --------------------------------------------------------------------------
    # Custom generated methods
    # --------------------------------------------------------------------------

    @staticmethod
    def from_vector(a, epsilon):
        # type: (numpy.ndarray, float) -> Unit3
        """
        Return a :class:`Unit3` that points along the direction of vector ``a``

        ``a`` does not have to be a unit vector.
        """

        # Total ops: 35

        # Input arrays
        if a.shape == (3,):
            a = a.reshape((3, 1))
        elif a.shape != (3, 1):
            raise IndexError(
                "a is expected to have shape (3, 1) or (3,); instead had shape {}".format(a.shape)
            )

        # Intermediate terms (8)
        _tmp0 = 1.0 / 2.0 - 1.0 / 2.0 * (
            0.0 if 1 - epsilon ** 2 == 0 else math.copysign(1, 1 - epsilon ** 2)
        )
        _tmp1 = 1 / math.sqrt(a[0, 0] ** 2 + a[1, 0] ** 2 + a[2, 0] ** 2 + epsilon)
        _tmp2 = _tmp1 * a[2, 0]
        _tmp3 = (
            0.0 if -epsilon + abs(_tmp2 + 1) == 0 else math.copysign(1, -epsilon + abs(_tmp2 + 1))
        ) + 1
        _tmp4 = (1.0 / 2.0) * _tmp3
        _tmp5 = 1 - _tmp4
        _tmp6 = math.sqrt(2 * _tmp2 + epsilon + 2)
        _tmp7 = _tmp1 * _tmp4 / _tmp6

        # Output terms
        _res = [0.0] * 4
        _res[0] = _tmp5 * (1 - _tmp0) - _tmp7 * a[1, 0]
        _res[1] = _tmp0 * _tmp5 + _tmp7 * a[0, 0]
        _res[2] = 0
        _res[3] = (1.0 / 4.0) * _tmp3 * _tmp6
        return Unit3.from_storage(_res)

    def to_unit_vector(self):
        # type: (Unit3) -> numpy.ndarray
        """
        This function was autogenerated from a symbolic function. Do not modify by hand.

        Symbolic function: to_unit_vector

        Args:

        Outputs:
            res: Matrix31
        """

        # Total ops: 14

        # Input arrays
        _self = self.data

        # Intermediate terms (2)
        _tmp0 = 2 * _self[1]
        _tmp1 = 2 * _self[0]

        # Output terms
        _res = numpy.zeros(3)
        _res[0] = _self[2] * _tmp1 + _self[3] * _tmp0
        _res[1] = _self[2] * _tmp0 - _self[3] * _tmp1
        _res[2] = -2 * _self[0] ** 2 - 2 * _self[1] ** 2 + 1
        return _res

    def to_rotation(self):
        # type: (Unit3) -> Rot3
        """
        This function was autogenerated from a symbolic function. Do not modify by hand.

        Symbolic function: to_rotation

        Args:

        Outputs:
            res: Rot3
        """

        # Total ops: 0

        # Input arrays
        _self = self.data

        # Intermediate terms (0)

        # Output terms
        _res = [0.0] * 4
        _res[0] = _self[0]
        _res[1] = _self[1]
        _res[2] = _self[2]
        _res[3] = _self[3]
        return Rot3.from_storage(_res)

    # --------------------------------------------------------------------------
    # StorageOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def storage_dim():
        # type: () -> int
        return 4

    def to_storage(self):
        # type: () -> T.List[float]
        return list(self.data)

    @classmethod
    def from_storage(cls, vec):
        # type: (T.Sequence[float]) -> Unit3
        instance = cls.__new__(cls)

        if isinstance(vec, list):
            instance.data = vec
        else:
            instance.data = list(vec)

        if len(vec) != cls.storage_dim():
            raise ValueError(
                "{} has storage dim {}, got {}.".format(cls.__name__, cls.storage_dim(), len(vec))
            )

        return instance

    # --------------------------------------------------------------------------
    # GroupOps concept
    # --------------------------------------------------------------------------

    @classmethod
    def identity(cls):
        # type: () -> Unit3
        return ops.GroupOps.identity()

    def inverse(self):
        # type: () -> Unit3
        return ops.GroupOps.inverse(self)

    def compose(self, b):
        # type: (Unit3) -> Unit3
        return ops.GroupOps.compose(self, b)

    def between(self, b):
        # type: (Unit3) -> Unit3
        return ops.GroupOps.between(self, b)

    # --------------------------------------------------------------------------
    # LieGroupOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def tangent_dim():
        # type: () -> int
        return 2

    @classmethod
    def from_tangent(cls, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Unit3
        if len(vec) != cls.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), cls.tangent_dim()
                )
            )
        return ops.LieGroupOps.from_tangent(vec, epsilon)

    def to_tangent(self, epsilon=1e-8):
        # type: (float) -> numpy.ndarray
        return ops.LieGroupOps.to_tangent(self, epsilon)

    def retract(self, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Unit3
        if len(vec) != self.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), self.tangent_dim()
                )
            )
        return ops.LieGroupOps.retract(self, vec, epsilon)

    def local_coordinates(self, b, epsilon=1e-8):
        # type: (Unit3, float) -> numpy.ndarray
        return ops.LieGroupOps.local_coordinates(self, b, epsilon)

    def interpolate(self, b, alpha, epsilon=1e-8):
        # type: (Unit3, float, float) -> Unit3
        return ops.LieGroupOps.interpolate(self, b, alpha, epsilon)

    # --------------------------------------------------------------------------
    # General Helpers
    # --------------------------------------------------------------------------
    def __eq__(self, other):
        # type: (T.Any) -> bool
        if isinstance(other, Unit3):
            return self.data == other.data
        else:
            return False

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (Unit3) -> Unit3
        pass

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (numpy.ndarray) -> numpy.ndarray
        pass

    def __mul__(self, other):
        # type: (T.Union[Unit3, numpy.ndarray]) -> T.Union[Unit3, numpy.ndarray]
        if isinstance(other, Unit3):
            return self.compose(other)
        elif isinstance(other, numpy.ndarray) and hasattr(self, "compose_with_point"):
            return getattr(self, "compose_with_point")(other).reshape(other.shape)
        else:
            raise NotImplementedError("Cannot compose {} with {}.".format(type(self), type(other)))
