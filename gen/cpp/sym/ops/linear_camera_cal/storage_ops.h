// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/cam_package/ops/CLASS/storage_ops.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <vector>

#include <Eigen/Dense>
#include <sym/linear_camera_cal.h>

namespace sym {
namespace linear_camera_cal {

/**
 * C++ StorageOps implementation for <class 'symforce.cam.linear_camera_cal.LinearCameraCal'>.
 */
template <typename Scalar>
struct StorageOps {
  static constexpr int32_t StorageDim() {
    return 4;
  }

  static void ToStorage(const sym::LinearCameraCal<Scalar>& a, Scalar* const vec);
  static sym::LinearCameraCal<Scalar> FromStorage(const Scalar* const vec);
};

}  // namespace linear_camera_cal
}  // namespace sym

// Wrapper to specialize the public concept
namespace sym {

template <>
struct StorageOps<sym::LinearCameraCal<double>>
    : public sym::linear_camera_cal::StorageOps<double> {};
template <>
struct StorageOps<sym::LinearCameraCal<float>> : public sym::linear_camera_cal::StorageOps<float> {
};

}  // namespace sym

// Explicit instantiation
extern template struct sym::linear_camera_cal::StorageOps<double>;
extern template struct sym::linear_camera_cal::StorageOps<float>;
