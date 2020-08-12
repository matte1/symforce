//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./atan_camera_cal.h"

// Explicit instantiation
template class cam::ATANCameraCal<double>;
template class cam::ATANCameraCal<float>;

// Camera operation implementations
namespace cam {

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> ATANCameraCal<Scalar>::PixelFromCameraPoint(const Eigen::Matrix<Scalar, 3, 1>& point, const Scalar epsilon, Scalar* const is_valid) const {
    // Input arrays
    const Eigen::Matrix<Scalar, 5, 1>& _self = Data();
    assert( is_valid != nullptr );

    // Intermediate terms (4)
    const Scalar _tmp0 = std::max<Scalar>(epsilon, std::fabs(point(2, 0)));
    const Scalar _tmp1 = std::pow(_tmp0, -2);
    const Scalar _tmp2 = std::sqrt(_tmp1*(point(0, 0) * point(0, 0)) + _tmp1*(point(1, 0) * point(1, 0)) + epsilon);
    const Scalar _tmp3 = std::atan(2*_tmp2*std::tan(0.5*_self[4]))/(_self[4]*_tmp0*_tmp2);

    // Output terms (2)
    Eigen::Matrix<Scalar, 2, 1> _pixel;
    Scalar& _is_valid = (*is_valid);

    _pixel(0, 0) = _self[0]*_tmp3*point(0, 0) + _self[2];
    _pixel(1, 0) = _self[1]*_tmp3*point(1, 0) + _self[3];
    _is_valid = std::max<Scalar>(0, (((point(2, 0)) > 0) - ((point(2, 0)) < 0)));


    return _pixel;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 3, 1> ATANCameraCal<Scalar>::CameraRayFromPixel(const Eigen::Matrix<Scalar, 2, 1>& pixel, const Scalar epsilon, Scalar* const is_valid) const {
    // Input arrays
    const Eigen::Matrix<Scalar, 5, 1>& _self = Data();
    assert( is_valid != nullptr );

    // Intermediate terms (5)
    const Scalar _tmp0 = -_self[2] + pixel(0, 0);
    const Scalar _tmp1 = -_self[3] + pixel(1, 0);
    const Scalar _tmp2 = std::sqrt(epsilon + (_tmp1 * _tmp1)/(_self[1] * _self[1]) + (_tmp0 * _tmp0)/(_self[0] * _self[0]));
    const Scalar _tmp3 = _self[4]*_tmp2;
    const Scalar _tmp4 = (1.0/2.0)*std::tan(_tmp3)/(_tmp2*std::tan(0.5*_self[4]));

    // Output terms (2)
    Eigen::Matrix<Scalar, 3, 1> _camera_ray;
    Scalar& _is_valid = (*is_valid);

    _camera_ray(0, 0) = _tmp0*_tmp4/_self[0];
    _camera_ray(1, 0) = _tmp1*_tmp4/_self[1];
    _camera_ray(2, 0) = 1;
    _is_valid = std::max<Scalar>(0, (((-std::fabs(_tmp3) + M_PI_2) > 0) - ((-std::fabs(_tmp3) + M_PI_2) < 0)));


    return _camera_ray;
}


}  // namespace cam

// Print implementations
std::ostream& operator<<(std::ostream& os, const cam::ATANCameraCald& a) {
    const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
    os << "<ATANCameraCald " << a.Data().transpose().format(fmt) << ">";
    return os;
}
std::ostream& operator<<(std::ostream& os, const cam::ATANCameraCalf& a) {
    const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
    os << "<ATANCameraCalf " << a.Data().transpose().format(fmt) << ">";
    return os;
}


// Concept implementations for this class
#include "./ops/atan_camera_cal/storage_ops.cc"
