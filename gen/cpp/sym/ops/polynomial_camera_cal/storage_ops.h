// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/ops/CLASS/storage_ops.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <lcmtypes/sym/type_t.hpp>

#include <sym/polynomial_camera_cal.h>

namespace sym {

/**
 * C++ StorageOps implementation for <class
 * 'symforce.cam.polynomial_camera_cal.PolynomialCameraCal'>.
 */
template <typename ScalarType>
struct StorageOps<PolynomialCameraCal<ScalarType>> {
  using T = PolynomialCameraCal<ScalarType>;
  using Scalar = typename PolynomialCameraCal<ScalarType>::Scalar;

  static constexpr int32_t StorageDim() {
    return 8;
  }

  static void ToStorage(const T& a, ScalarType* out);
  static T FromStorage(const ScalarType* data);

  static constexpr type_t TypeEnum() {
    return type_t::POLYNOMIAL_CAMERA_CAL;
  }
};

}  // namespace sym

// Explicit instantiation
extern template struct sym::StorageOps<sym::PolynomialCameraCal<double>>;
extern template struct sym::StorageOps<sym::PolynomialCameraCal<float>>;
