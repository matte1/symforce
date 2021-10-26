// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>
#include <sym/pose3.h>

namespace sym {

/**
 * Reprojects the landmark ray into the target spherical camera and returns the delta between the
 * correspondence and the reprojection.
 *
 * The landmark is specified as a 3D point or ray (will be normalized) in the source spherical
 * camera; this means the landmark is fixed in the source camera and always has residual 0 there
 * (this 0 residual is not returned, only the residual in the target camera is returned).
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target spherical camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     p_camera_source: The location of the landmark in the source camera coordinate, will be
 * normalized target_pixel: The location of the correspondence in the target camera epsilon: Small
 * positive value
 *
 * Outputs:
 *     res: 2dof reprojection delta
 *     valid: is valid projection or not
 *
 */
template <typename Scalar>
void SphericalReprojectionDelta(const sym::Pose3<Scalar>& source_pose,
                                const sym::Pose3<Scalar>& target_pose,
                                const Eigen::Matrix<Scalar, 9, 1>& target_calibration_storage,
                                const Scalar source_inverse_range,
                                const Eigen::Matrix<Scalar, 3, 1>& p_camera_source,
                                const Eigen::Matrix<Scalar, 2, 1>& target_pixel,
                                const Scalar epsilon,
                                Eigen::Matrix<Scalar, 2, 1>* const reprojection_delta = nullptr,
                                Scalar* const is_valid = nullptr) {
  // Total ops: 200

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (45)
  const Scalar _tmp0 = _source_pose[0] * _target_pose[3] + _source_pose[1] * _target_pose[2] -
                       _source_pose[2] * _target_pose[1] - _source_pose[3] * _target_pose[0];
  const Scalar _tmp1 = _source_pose[0] * _target_pose[1] - _source_pose[1] * _target_pose[0] +
                       _source_pose[2] * _target_pose[3] - _source_pose[3] * _target_pose[2];
  const Scalar _tmp2 = 2 * _tmp1;
  const Scalar _tmp3 = _tmp0 * _tmp2;
  const Scalar _tmp4 = -_source_pose[0] * _target_pose[2] + _source_pose[1] * _target_pose[3] +
                       _source_pose[2] * _target_pose[0] - _source_pose[3] * _target_pose[1];
  const Scalar _tmp5 = _source_pose[0] * _target_pose[0] + _source_pose[1] * _target_pose[1] +
                       _source_pose[2] * _target_pose[2] + _source_pose[3] * _target_pose[3];
  const Scalar _tmp6 = 2 * _tmp4 * _tmp5;
  const Scalar _tmp7 = std::pow(Scalar(epsilon + std::pow(p_camera_source(0, 0), Scalar(2)) +
                                       std::pow(p_camera_source(1, 0), Scalar(2)) +
                                       std::pow(p_camera_source(2, 0), Scalar(2))),
                                Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp8 = _tmp7 * p_camera_source(2, 0);
  const Scalar _tmp9 = 2 * _tmp0;
  const Scalar _tmp10 = _tmp4 * _tmp9;
  const Scalar _tmp11 = _tmp2 * _tmp5;
  const Scalar _tmp12 = _tmp7 * p_camera_source(1, 0);
  const Scalar _tmp13 = -2 * std::pow(_tmp1, Scalar(2));
  const Scalar _tmp14 = 1 - 2 * std::pow(_tmp4, Scalar(2));
  const Scalar _tmp15 = _tmp7 * p_camera_source(0, 0);
  const Scalar _tmp16 = 2 * _target_pose[2];
  const Scalar _tmp17 = _target_pose[3] * _tmp16;
  const Scalar _tmp18 = 2 * _target_pose[0];
  const Scalar _tmp19 = _target_pose[1] * _tmp18;
  const Scalar _tmp20 = _tmp17 + _tmp19;
  const Scalar _tmp21 = _target_pose[2] * _tmp18;
  const Scalar _tmp22 = 2 * _target_pose[1] * _target_pose[3];
  const Scalar _tmp23 = _tmp21 - _tmp22;
  const Scalar _tmp24 = -2 * std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp25 = 1 - 2 * std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp26 = _tmp24 + _tmp25;
  const Scalar _tmp27 =
      _tmp12 * (_tmp10 - _tmp11) + _tmp15 * (_tmp13 + _tmp14) + _tmp8 * (_tmp3 + _tmp6) +
      source_inverse_range *
          (_source_pose[4] * _tmp26 + _source_pose[5] * _tmp20 + _source_pose[6] * _tmp23 -
           _target_pose[4] * _tmp26 - _target_pose[5] * _tmp20 - _target_pose[6] * _tmp23);
  const Scalar _tmp28 = -2 * std::pow(_tmp0, Scalar(2));
  const Scalar _tmp29 = _tmp2 * _tmp4;
  const Scalar _tmp30 = _tmp5 * _tmp9;
  const Scalar _tmp31 = -_tmp17 + _tmp19;
  const Scalar _tmp32 = _target_pose[1] * _tmp16;
  const Scalar _tmp33 = _target_pose[3] * _tmp18;
  const Scalar _tmp34 = _tmp32 + _tmp33;
  const Scalar _tmp35 = -2 * std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp36 = _tmp24 + _tmp35 + 1;
  const Scalar _tmp37 =
      _tmp12 * (_tmp13 + _tmp28 + 1) + _tmp15 * (_tmp10 + _tmp11) + _tmp8 * (_tmp29 - _tmp30) +
      source_inverse_range *
          (_source_pose[4] * _tmp31 + _source_pose[5] * _tmp36 + _source_pose[6] * _tmp34 -
           _target_pose[4] * _tmp31 - _target_pose[5] * _tmp36 - _target_pose[6] * _tmp34);
  const Scalar _tmp38 =
      std::sqrt(std::pow(_tmp27, Scalar(2)) + std::pow(_tmp37, Scalar(2)) + epsilon);
  const Scalar _tmp39 = _tmp32 - _tmp33;
  const Scalar _tmp40 = _tmp21 + _tmp22;
  const Scalar _tmp41 = _tmp25 + _tmp35;
  const Scalar _tmp42 = std::atan2(
      _tmp38, _tmp12 * (_tmp29 + _tmp30) + _tmp15 * (_tmp3 - _tmp6) + _tmp8 * (_tmp14 + _tmp28) +
                  source_inverse_range * (_source_pose[4] * _tmp40 + _source_pose[5] * _tmp39 +
                                          _source_pose[6] * _tmp41 - _target_pose[4] * _tmp40 -
                                          _target_pose[5] * _tmp39 - _target_pose[6] * _tmp41));
  const Scalar _tmp43 = std::min<Scalar>(_tmp42, -epsilon + target_calibration_storage(4, 0));
  const Scalar _tmp44 = (std::pow(_tmp43, Scalar(9)) * target_calibration_storage(8, 0) +
                         std::pow(_tmp43, Scalar(7)) * target_calibration_storage(7, 0) +
                         std::pow(_tmp43, Scalar(5)) * target_calibration_storage(6, 0) +
                         [&]() {
                           const Scalar base = _tmp43;
                           return base * base * base;
                         }() *
                             target_calibration_storage(5, 0) +
                         _tmp43) /
                        _tmp38;

  // Output terms (2)
  if (reprojection_delta != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _reprojection_delta = (*reprojection_delta);

    _reprojection_delta(0, 0) = _tmp27 * _tmp44 * target_calibration_storage(0, 0) +
                                target_calibration_storage(2, 0) - target_pixel(0, 0);
    _reprojection_delta(1, 0) = _tmp37 * _tmp44 * target_calibration_storage(1, 0) +
                                target_calibration_storage(3, 0) - target_pixel(1, 0);
  }

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::max<Scalar>(0, (((-_tmp42 + target_calibration_storage(4, 0)) > 0) -
                                     ((-_tmp42 + target_calibration_storage(4, 0)) < 0)));
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
