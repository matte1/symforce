// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/pose3.h>

namespace sym {

/**
 * Composition of two elements in the group.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     geo.Matrix: Jacobian for arg 1 (b)
 */
template <typename Scalar>
Eigen::Matrix<Scalar, 6, 6> ComposePose3_Jacobian1(const geo::Pose3<Scalar>& a,
                                                   const geo::Pose3<Scalar>& b) {
  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _b = b.Data();

  // Intermediate terms (110)
  const Scalar _tmp0 = _a[0] * _b[3] + _a[1] * _b[2] - _a[2] * _b[1] + _a[3] * _b[0];
  const Scalar _tmp1 = 2 * _tmp0;
  const Scalar _tmp2 = _a[3] * _tmp1;
  const Scalar _tmp3 = -_a[0] * _b[2] + _a[1] * _b[3] + _a[2] * _b[0] + _a[3] * _b[1];
  const Scalar _tmp4 = 2 * _tmp3;
  const Scalar _tmp5 = _a[2] * _tmp4;
  const Scalar _tmp6 = _a[0] * _b[1] - _a[1] * _b[0] + _a[2] * _b[3] + _a[3] * _b[2];
  const Scalar _tmp7 = 2 * _a[1];
  const Scalar _tmp8 = _tmp6 * _tmp7;
  const Scalar _tmp9 = -_a[0] * _b[0] - _a[1] * _b[1] - _a[2] * _b[2] + _a[3] * _b[3];
  const Scalar _tmp10 = 2 * _a[0];
  const Scalar _tmp11 = _tmp10 * _tmp9;
  const Scalar _tmp12 = _tmp11 - _tmp2 - _tmp5 + _tmp8;
  const Scalar _tmp13 = (1.0 / 2.0) * _b[0];
  const Scalar _tmp14 = -_tmp12 * _tmp13;
  const Scalar _tmp15 = _a[2] * _tmp1;
  const Scalar _tmp16 = _tmp10 * _tmp6;
  const Scalar _tmp17 = 2 * _a[3];
  const Scalar _tmp18 = _tmp17 * _tmp3;
  const Scalar _tmp19 = _tmp7 * _tmp9;
  const Scalar _tmp20 = _tmp15 - _tmp16 - _tmp18 + _tmp19;
  const Scalar _tmp21 = (1.0 / 2.0) * _tmp20;
  const Scalar _tmp22 = -_b[1] * _tmp21;
  const Scalar _tmp23 = _tmp0 * _tmp7;
  const Scalar _tmp24 = _tmp10 * _tmp3;
  const Scalar _tmp25 = _tmp17 * _tmp6;
  const Scalar _tmp26 = 2 * _a[2];
  const Scalar _tmp27 = _tmp26 * _tmp9;
  const Scalar _tmp28 =
      (1.0 / 2.0) * _tmp23 - 1.0 / 2.0 * _tmp24 + (1.0 / 2.0) * _tmp25 - 1.0 / 2.0 * _tmp27;
  const Scalar _tmp29 = (1.0 / 2.0) * _tmp0 * _tmp10 + (1.0 / 2.0) * _tmp17 * _tmp9 +
                        (1.0 / 2.0) * _tmp26 * _tmp6 + (1.0 / 2.0) * _tmp3 * _tmp7;
  const Scalar _tmp30 = _b[3] * _tmp29;
  const Scalar _tmp31 = (1.0 / 2.0) * _b[1];
  const Scalar _tmp32 = _b[0] * _tmp21;
  const Scalar _tmp33 = _b[2] * _tmp29;
  const Scalar _tmp34 = (1.0 / 2.0) * _b[2];
  const Scalar _tmp35 = _tmp12 * _tmp34;
  const Scalar _tmp36 = _b[1] * _tmp29;
  const Scalar _tmp37 = -_tmp11 + _tmp2 + _tmp5 - _tmp8;
  const Scalar _tmp38 =
      -1.0 / 2.0 * _tmp23 + (1.0 / 2.0) * _tmp24 - 1.0 / 2.0 * _tmp25 + (1.0 / 2.0) * _tmp27;
  const Scalar _tmp39 = -_b[2] * _tmp38 + _tmp30;
  const Scalar _tmp40 = (1.0 / 2.0) * _b[3];
  const Scalar _tmp41 = _b[0] * _tmp29;
  const Scalar _tmp42 = _b[1] * _tmp38;
  const Scalar _tmp43 = -_tmp15 + _tmp16 + _tmp18 - _tmp19;
  const Scalar _tmp44 = (1.0 / 2.0) * _tmp43;
  const Scalar _tmp45 = 2 * _b[1];
  const Scalar _tmp46 = _b[3] * _tmp45;
  const Scalar _tmp47 = 2 * _b[2];
  const Scalar _tmp48 = _b[0] * _tmp47;
  const Scalar _tmp49 = -_tmp46 + _tmp48;
  const Scalar _tmp50 = -2 * (_a[0] * _a[0]);
  const Scalar _tmp51 = -2 * (_a[1] * _a[1]) + 1;
  const Scalar _tmp52 = _tmp50 + _tmp51;
  const Scalar _tmp53 = _tmp4 * _tmp9;
  const Scalar _tmp54 = _tmp1 * _tmp6;
  const Scalar _tmp55 = -_tmp53 + _tmp54;
  const Scalar _tmp56 = _a[2] * _tmp7;
  const Scalar _tmp57 = _a[3] * _tmp10;
  const Scalar _tmp58 = _tmp56 - _tmp57;
  const Scalar _tmp59 = 2 * _tmp6 * _tmp9;
  const Scalar _tmp60 = _tmp1 * _tmp3;
  const Scalar _tmp61 = _tmp59 + _tmp60;
  const Scalar _tmp62 = -2 * (_tmp6 * _tmp6);
  const Scalar _tmp63 = -2 * (_tmp3 * _tmp3);
  const Scalar _tmp64 = _tmp62 + _tmp63 + 1;
  const Scalar _tmp65 = _a[2] * _tmp10;
  const Scalar _tmp66 = _a[3] * _tmp7;
  const Scalar _tmp67 = _tmp65 + _tmp66;
  const Scalar _tmp68 = _tmp52 * _tmp55 + _tmp58 * _tmp61 + _tmp64 * _tmp67;
  const Scalar _tmp69 = _b[3] * _tmp47;
  const Scalar _tmp70 = _b[0] * _tmp45;
  const Scalar _tmp71 = _tmp69 + _tmp70;
  const Scalar _tmp72 = _tmp56 + _tmp57;
  const Scalar _tmp73 = -2 * (_a[2] * _a[2]);
  const Scalar _tmp74 = _tmp50 + _tmp73 + 1;
  const Scalar _tmp75 = _a[1] * _tmp10;
  const Scalar _tmp76 = _a[2] * _tmp17;
  const Scalar _tmp77 = _tmp75 - _tmp76;
  const Scalar _tmp78 = _tmp55 * _tmp72 + _tmp61 * _tmp74 + _tmp64 * _tmp77;
  const Scalar _tmp79 = -2 * (_b[1] * _b[1]);
  const Scalar _tmp80 = -2 * (_b[2] * _b[2]) + 1;
  const Scalar _tmp81 = _tmp79 + _tmp80;
  const Scalar _tmp82 = _tmp65 - _tmp66;
  const Scalar _tmp83 = _tmp75 + _tmp76;
  const Scalar _tmp84 = _tmp51 + _tmp73;
  const Scalar _tmp85 = _tmp55 * _tmp82 + _tmp61 * _tmp83 + _tmp64 * _tmp84;
  const Scalar _tmp86 = 2 * _b[0] * _b[3];
  const Scalar _tmp87 = _b[1] * _tmp47;
  const Scalar _tmp88 = _tmp86 + _tmp87;
  const Scalar _tmp89 = -2 * (_b[0] * _b[0]);
  const Scalar _tmp90 = _tmp80 + _tmp89;
  const Scalar _tmp91 = -_tmp69 + _tmp70;
  const Scalar _tmp92 = -_tmp86 + _tmp87;
  const Scalar _tmp93 = _tmp79 + _tmp89 + 1;
  const Scalar _tmp94 = _tmp46 + _tmp48;
  const Scalar _tmp95 = -2 * (_tmp0 * _tmp0) + 1;
  const Scalar _tmp96 = _tmp62 + _tmp95;
  const Scalar _tmp97 = _tmp1 * _tmp9;
  const Scalar _tmp98 = _tmp4 * _tmp6;
  const Scalar _tmp99 = _tmp97 + _tmp98;
  const Scalar _tmp100 = -_tmp59 + _tmp60;
  const Scalar _tmp101 = _tmp100 * _tmp67 + _tmp52 * _tmp99 + _tmp58 * _tmp96;
  const Scalar _tmp102 = _tmp100 * _tmp77 + _tmp72 * _tmp99 + _tmp74 * _tmp96;
  const Scalar _tmp103 = _tmp100 * _tmp84 + _tmp82 * _tmp99 + _tmp83 * _tmp96;
  const Scalar _tmp104 = _tmp63 + _tmp95;
  const Scalar _tmp105 = -_tmp97 + _tmp98;
  const Scalar _tmp106 = _tmp53 + _tmp54;
  const Scalar _tmp107 = _tmp104 * _tmp52 + _tmp105 * _tmp58 + _tmp106 * _tmp67;
  const Scalar _tmp108 = _tmp104 * _tmp72 + _tmp105 * _tmp74 + _tmp106 * _tmp77;
  const Scalar _tmp109 = _tmp104 * _tmp82 + _tmp105 * _tmp83 + _tmp106 * _tmp84;

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 6> _res_D_b;

  _res_D_b(0, 0) = _b[2] * _tmp28 + _tmp14 + _tmp22 + _tmp30;
  _res_D_b(0, 1) = _b[3] * _tmp28 - _tmp12 * _tmp31 + _tmp32 - _tmp33;
  _res_D_b(0, 2) = -_b[0] * _tmp28 + _b[3] * _tmp21 - _tmp35 + _tmp36;
  _res_D_b(0, 3) = 0;
  _res_D_b(0, 4) = 0;
  _res_D_b(0, 5) = 0;
  _res_D_b(1, 0) = _b[3] * _tmp38 - _tmp31 * _tmp37 - _tmp32 + _tmp33;
  _res_D_b(1, 1) = _tmp13 * _tmp37 + _tmp22 + _tmp39;
  _res_D_b(1, 2) = -_tmp20 * _tmp34 + _tmp37 * _tmp40 - _tmp41 + _tmp42;
  _res_D_b(1, 3) = 0;
  _res_D_b(1, 4) = 0;
  _res_D_b(1, 5) = 0;
  _res_D_b(2, 0) = -_b[0] * _tmp38 + _b[3] * _tmp44 + _tmp35 - _tmp36;
  _res_D_b(2, 1) = _tmp12 * _tmp40 - _tmp34 * _tmp43 + _tmp41 - _tmp42;
  _res_D_b(2, 2) = _b[1] * _tmp44 + _tmp14 + _tmp39;
  _res_D_b(2, 3) = 0;
  _res_D_b(2, 4) = 0;
  _res_D_b(2, 5) = 0;
  _res_D_b(3, 0) = 0;
  _res_D_b(3, 1) = 0;
  _res_D_b(3, 2) = 0;
  _res_D_b(3, 3) = _tmp49 * _tmp68 + _tmp71 * _tmp78 + _tmp81 * _tmp85;
  _res_D_b(3, 4) = _tmp68 * _tmp88 + _tmp78 * _tmp90 + _tmp85 * _tmp91;
  _res_D_b(3, 5) = _tmp68 * _tmp93 + _tmp78 * _tmp92 + _tmp85 * _tmp94;
  _res_D_b(4, 0) = 0;
  _res_D_b(4, 1) = 0;
  _res_D_b(4, 2) = 0;
  _res_D_b(4, 3) = _tmp101 * _tmp49 + _tmp102 * _tmp71 + _tmp103 * _tmp81;
  _res_D_b(4, 4) = _tmp101 * _tmp88 + _tmp102 * _tmp90 + _tmp103 * _tmp91;
  _res_D_b(4, 5) = _tmp101 * _tmp93 + _tmp102 * _tmp92 + _tmp103 * _tmp94;
  _res_D_b(5, 0) = 0;
  _res_D_b(5, 1) = 0;
  _res_D_b(5, 2) = 0;
  _res_D_b(5, 3) = _tmp107 * _tmp49 + _tmp108 * _tmp71 + _tmp109 * _tmp81;
  _res_D_b(5, 4) = _tmp107 * _tmp88 + _tmp108 * _tmp90 + _tmp109 * _tmp91;
  _res_D_b(5, 5) = _tmp107 * _tmp93 + _tmp108 * _tmp92 + _tmp109 * _tmp94;

  return _res_D_b;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
