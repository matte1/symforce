// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/rot2.h>

namespace sym {

/**
 * Residual that penalizes the difference between(a, b) and a_T_b.
 *
 * In vector space terms that would be:
 *     (b - a) - a_T_b
 *
 * In lie group terms:
 *     local_coordinates(a_T_b, between(a, b))
 *     to_tangent(compose(inverse(a_T_b), compose(inverse(a), b)))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *
 */
template <typename Scalar>
void BetweenFactorRot2(const geo::Rot2<Scalar>& a, const geo::Rot2<Scalar>& b,
                       const geo::Rot2<Scalar>& a_T_b, const Eigen::Matrix<Scalar, 1, 1>& sqrt_info,
                       const Scalar epsilon, Eigen::Matrix<Scalar, 1, 1>* const res = nullptr,
                       Eigen::Matrix<Scalar, 1, 2>* const jac = nullptr) {
  // Input arrays
  const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 2, 1>& _b = b.Data();
  const Eigen::Matrix<Scalar, 2, 1>& _a_T_b = a_T_b.Data();

  // Intermediate terms (32)
  const Scalar _tmp0 = (_a[1] * _a[1]);
  const Scalar _tmp1 = (_a[0] * _a[0]);
  const Scalar _tmp2 = _tmp0 + _tmp1;
  const Scalar _tmp3 = 1.0 / (_tmp2);
  const Scalar _tmp4 = _b[1] * _tmp3;
  const Scalar _tmp5 = _b[0] * _tmp3;
  const Scalar _tmp6 = _a[0] * _tmp4 - _a[1] * _tmp5;
  const Scalar _tmp7 = 1.0 / ((_a_T_b[0] * _a_T_b[0]) + (_a_T_b[1] * _a_T_b[1]));
  const Scalar _tmp8 = _a_T_b[0] * _tmp7;
  const Scalar _tmp9 = _a[0] * _tmp5 + _a[1] * _tmp4;
  const Scalar _tmp10 = _a_T_b[1] * _tmp7;
  const Scalar _tmp11 = -_tmp10 * _tmp9 + _tmp6 * _tmp8;
  const Scalar _tmp12 = _tmp10 * _tmp6 + _tmp8 * _tmp9;
  const Scalar _tmp13 = 2 / (_tmp2 * _tmp2);
  const Scalar _tmp14 = _a[0] * _a[1] * _tmp13;
  const Scalar _tmp15 = _b[0] * _tmp14;
  const Scalar _tmp16 = _tmp0 * _tmp13;
  const Scalar _tmp17 = -_b[1] * _tmp16 - _tmp15 + _tmp4;
  const Scalar _tmp18 = -_b[1] * _tmp14;
  const Scalar _tmp19 = _b[0] * _tmp16 + _tmp18 - _tmp5;
  const Scalar _tmp20 = (_tmp12 * _tmp12);
  const Scalar _tmp21 = _tmp11 / _tmp20;
  const Scalar _tmp22 = 1.0 / (_tmp12);
  const Scalar _tmp23 = _tmp20 * sqrt_info(0, 0) / ((_tmp11 * _tmp11) + _tmp20);
  const Scalar _tmp24 = _tmp1 * _tmp13;
  const Scalar _tmp25 = -_b[0] * _tmp24 + _tmp18 + _tmp5;
  const Scalar _tmp26 = -_b[1] * _tmp24 + _tmp15 + _tmp4;
  const Scalar _tmp27 = _a[1] * _tmp3;
  const Scalar _tmp28 = _tmp27 * _tmp8;
  const Scalar _tmp29 = _a[0] * _tmp3;
  const Scalar _tmp30 = _tmp10 * _tmp29;
  const Scalar _tmp31 = -_tmp10 * _tmp27 + _tmp29 * _tmp8;

  // Output terms (2)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _res = (*res);

    _res(0, 0) = sqrt_info(0, 0) * std::atan2(_tmp11, _tmp12);
  }

  if (jac != nullptr) {
    Eigen::Matrix<Scalar, 1, 2>& _jac = (*jac);

    _jac(0, 0) = _a[0] * _tmp23 *
                     (-_tmp21 * (_tmp10 * _tmp19 + _tmp17 * _tmp8) +
                      _tmp22 * (-_tmp10 * _tmp17 + _tmp19 * _tmp8)) -
                 _a[1] * _tmp23 *
                     (-_tmp21 * (_tmp10 * _tmp26 + _tmp25 * _tmp8) +
                      _tmp22 * (-_tmp10 * _tmp25 + _tmp26 * _tmp8));
    _jac(0, 1) = _b[0] * _tmp23 * (-_tmp21 * (_tmp28 + _tmp30) + _tmp22 * _tmp31) -
                 _b[1] * _tmp23 * (-_tmp21 * _tmp31 + _tmp22 * (-_tmp28 - _tmp30));
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
