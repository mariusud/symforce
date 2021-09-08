// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/cam_package/ops/CLASS/storage_ops.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <vector>

#include <Eigen/Dense>
#include <sym/spherical_camera_cal.h>

namespace sym {
namespace spherical_camera_cal {

/**
 * C++ StorageOps implementation for <class 'symforce.cam.spherical_camera_cal.SphericalCameraCal'>.
 */
template <typename Scalar>
struct StorageOps {
  static constexpr int32_t StorageDim() {
    return 9;
  }

  static void ToStorage(const sym::SphericalCameraCal<Scalar>& a, Scalar* const vec);
  static sym::SphericalCameraCal<Scalar> FromStorage(const Scalar* const vec);
};

}  // namespace spherical_camera_cal
}  // namespace sym

// Wrapper to specialize the public concept
namespace sym {

template <>
struct StorageOps<sym::SphericalCameraCal<double>>
    : public sym::spherical_camera_cal::StorageOps<double> {};
template <>
struct StorageOps<sym::SphericalCameraCal<float>>
    : public sym::spherical_camera_cal::StorageOps<float> {};

}  // namespace sym

// Explicit instantiation
extern template struct sym::spherical_camera_cal::StorageOps<double>;
extern template struct sym::spherical_camera_cal::StorageOps<float>;
