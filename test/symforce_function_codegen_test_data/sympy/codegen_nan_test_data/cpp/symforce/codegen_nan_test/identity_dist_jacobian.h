// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/rot3.h>

namespace codegen_nan_test {

/**
 * This function was autogenerated. Do not modify by hand.
 *
 * Arg type(s): Rot3, Symbol
 * Return type(s): Add
 *
 */
template <typename Scalar>
Scalar IdentityDistJacobian(const geo::Rot3<Scalar>& R1, const Scalar e) {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _R1 = R1.Data();

  // Intermediate terms (13)
  const Scalar _tmp0 = -e + 1;
  const Scalar _tmp1 = std::min<Scalar>(_R1[3], _tmp0);
  const Scalar _tmp2 = 8 * 0.5 * ((((-_R1[3] + _tmp0) >= 0) - ((-_R1[3] + _tmp0) < 0)) + 1) * 0.5 *
                       ((((_tmp0 + _tmp1) >= 0) - ((_tmp0 + _tmp1) < 0)) + 1);
  const Scalar _tmp3 = (_R1[0] * _R1[0]) * _tmp2;
  const Scalar _tmp4 = std::max<Scalar>(_tmp1, e - 1);
  const Scalar _tmp5 = -(_tmp4 * _tmp4) + 1;
  const Scalar _tmp6 = std::acos(_tmp4);
  const Scalar _tmp7 = _tmp6 / (_tmp5 * std::sqrt(_tmp5));
  const Scalar _tmp8 = (_R1[1] * _R1[1]);
  const Scalar _tmp9 = _tmp2 * _tmp7;
  const Scalar _tmp10 = (_R1[2] * _R1[2]);
  const Scalar _tmp11 = _tmp4 * (_tmp6 * _tmp6) / (_tmp5 * _tmp5);
  const Scalar _tmp12 = _tmp11 * _tmp2;

  // Output terms (1)
  Scalar _dist_D_R1;

  _dist_D_R1 = _tmp10 * _tmp12 - _tmp10 * _tmp9 + _tmp11 * _tmp3 + _tmp12 * _tmp8 - _tmp3 * _tmp7 -
               _tmp8 * _tmp9;

  return _dist_D_R1;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace codegen_nan_test
