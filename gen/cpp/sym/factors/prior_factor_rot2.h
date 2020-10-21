// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/rot2.h>

namespace sym {

/**
 * Residual that penalizes the difference between a value and prior (desired / measured value).
 *
 * In vector space terms that would be:
 *     prior - value
 *
 * In lie group terms:
 *     to_tangent(compose(inverse(value), prior))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *
 */
template <typename Scalar>
void PriorFactorRot2(const geo::Rot2<Scalar>& value, const geo::Rot2<Scalar>& prior,
                     const Eigen::Matrix<Scalar, 1, 1>& sqrt_info, const Scalar epsilon,
                     Eigen::Matrix<Scalar, 1, 1>* const res = nullptr,
                     Eigen::Matrix<Scalar, 1, 1>* const jac = nullptr) {
  // Input arrays
  const Eigen::Matrix<Scalar, 2, 1>& _value = value.Data();
  const Eigen::Matrix<Scalar, 2, 1>& _prior = prior.Data();

  // Intermediate terms (9)
  const Scalar _tmp0 = 1.0 / ((_prior[0] * _prior[0]) + (_prior[1] * _prior[1]));
  const Scalar _tmp1 = _prior[0] * _tmp0;
  const Scalar _tmp2 = _prior[1] * _tmp0;
  const Scalar _tmp3 = _tmp1 * _value[1] - _tmp2 * _value[0];
  const Scalar _tmp4 = _tmp1 * _value[0] + _tmp2 * _value[1];
  const Scalar _tmp5 = (_tmp4 * _tmp4);
  const Scalar _tmp6 = _tmp3 / _tmp5;
  const Scalar _tmp7 = 1.0 / (_tmp4);
  const Scalar _tmp8 = _tmp5 * sqrt_info(0, 0) / ((_tmp3 * _tmp3) + _tmp5);

  // Output terms (2)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _res = (*res);

    _res(0, 0) = sqrt_info(0, 0) * std::atan2(_tmp3, _tmp4);
  }

  if (jac != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _jac = (*jac);

    _jac(0, 0) = _tmp8 * _value[0] * (_tmp1 * _tmp7 - _tmp2 * _tmp6) -
                 _tmp8 * _value[1] * (-_tmp1 * _tmp6 - _tmp2 * _tmp7);
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
