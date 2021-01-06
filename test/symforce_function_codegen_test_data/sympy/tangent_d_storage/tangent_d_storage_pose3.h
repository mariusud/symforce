// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/pose3.h>

namespace sym {

/**
 * Computes the jacobian of the tangent space around an element with respect to the storage space of
 * that element.
 *
 */
template <typename Scalar>
Eigen::Matrix<Scalar, 6, 7> Tangent_D_Storage(const geo::Pose3<Scalar>& a, const Scalar epsilon) {
  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();

  // Intermediate terms (16)
  const Scalar _tmp0 = 2 * _a[3];
  const Scalar _tmp1 = 2 * _a[2];
  const Scalar _tmp2 = 2 * _a[1];
  const Scalar _tmp3 = -_tmp2;
  const Scalar _tmp4 = 2 * _a[0];
  const Scalar _tmp5 = -_tmp4;
  const Scalar _tmp6 = -_tmp1;
  const Scalar _tmp7 = -2 * (_a[1] * _a[1]);
  const Scalar _tmp8 = -2 * (_a[2] * _a[2]) + 1;
  const Scalar _tmp9 = _a[0] * _tmp2;
  const Scalar _tmp10 = _a[2] * _tmp0;
  const Scalar _tmp11 = _a[0] * _tmp1;
  const Scalar _tmp12 = _a[1] * _tmp0;
  const Scalar _tmp13 = -2 * (_a[0] * _a[0]);
  const Scalar _tmp14 = _a[0] * _tmp0;
  const Scalar _tmp15 = _a[1] * _tmp1;

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 7> _res;

  _res(0, 0) = _tmp0;
  _res(0, 1) = _tmp1;
  _res(0, 2) = _tmp3;
  _res(0, 3) = _tmp5;
  _res(0, 4) = 0;
  _res(0, 5) = 0;
  _res(0, 6) = 0;
  _res(1, 0) = _tmp6;
  _res(1, 1) = _tmp0;
  _res(1, 2) = _tmp4;
  _res(1, 3) = _tmp3;
  _res(1, 4) = 0;
  _res(1, 5) = 0;
  _res(1, 6) = 0;
  _res(2, 0) = _tmp2;
  _res(2, 1) = _tmp5;
  _res(2, 2) = _tmp0;
  _res(2, 3) = _tmp6;
  _res(2, 4) = 0;
  _res(2, 5) = 0;
  _res(2, 6) = 0;
  _res(3, 0) = 0;
  _res(3, 1) = 0;
  _res(3, 2) = 0;
  _res(3, 3) = 0;
  _res(3, 4) = _tmp7 + _tmp8;
  _res(3, 5) = _tmp10 + _tmp9;
  _res(3, 6) = _tmp11 - _tmp12;
  _res(4, 0) = 0;
  _res(4, 1) = 0;
  _res(4, 2) = 0;
  _res(4, 3) = 0;
  _res(4, 4) = -_tmp10 + _tmp9;
  _res(4, 5) = _tmp13 + _tmp8;
  _res(4, 6) = _tmp14 + _tmp15;
  _res(5, 0) = 0;
  _res(5, 1) = 0;
  _res(5, 2) = 0;
  _res(5, 3) = 0;
  _res(5, 4) = _tmp11 + _tmp12;
  _res(5, 5) = -_tmp14 + _tmp15;
  _res(5, 6) = _tmp13 + _tmp7 + 1;

  return _res;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
