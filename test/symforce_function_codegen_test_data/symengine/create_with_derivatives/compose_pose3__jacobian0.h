// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <sym/pose3.h>

namespace sym {

/**
 * Composition of two elements in the group.
 *
 * Returns:
 *     geo.Matrix: Jacobian for arg 0 (a)
 */
template <typename Scalar>
Eigen::Matrix<Scalar, 6, 6> ComposePose3_Jacobian0(const sym::Pose3<Scalar>& a,
                                                   const sym::Pose3<Scalar>& b) {
  // Total ops: 318

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _b = b.Data();

  // Intermediate terms (76)
  const Scalar _tmp0 =
      2 * _a[0] * _b[1] - 2 * _a[1] * _b[0] + 2 * _a[2] * _b[3] + 2 * _a[3] * _b[2];
  const Scalar _tmp1 = _b[0] * _tmp0;
  const Scalar _tmp2 =
      -2 * _a[0] * _b[0] - 2 * _a[1] * _b[1] - 2 * _a[2] * _b[2] + 2 * _a[3] * _b[3];
  const Scalar _tmp3 = _b[1] * _tmp2;
  const Scalar _tmp4 =
      -2 * _a[0] * _b[2] + 2 * _a[1] * _b[3] + 2 * _a[2] * _b[0] + 2 * _a[3] * _b[1];
  const Scalar _tmp5 = _b[3] * _tmp4;
  const Scalar _tmp6 =
      2 * _a[0] * _b[3] + 2 * _a[1] * _b[2] - 2 * _a[2] * _b[1] + 2 * _a[3] * _b[0];
  const Scalar _tmp7 = _b[2] * _tmp6;
  const Scalar _tmp8 = -_tmp5 + _tmp7;
  const Scalar _tmp9 = _tmp1 - _tmp3 + _tmp8;
  const Scalar _tmp10 = (1.0 / 2.0) * _a[1];
  const Scalar _tmp11 = _b[1] * _tmp0;
  const Scalar _tmp12 = _b[2] * _tmp4;
  const Scalar _tmp13 = _b[3] * _tmp6;
  const Scalar _tmp14 = -_tmp13;
  const Scalar _tmp15 = _b[0] * _tmp2;
  const Scalar _tmp16 = _tmp11 - _tmp12 + _tmp14 + _tmp15;
  const Scalar _tmp17 = (1.0 / 2.0) * _a[0];
  const Scalar _tmp18 = _b[1] * _tmp4;
  const Scalar _tmp19 = -_tmp18;
  const Scalar _tmp20 = _b[0] * _tmp6;
  const Scalar _tmp21 = _b[2] * _tmp0;
  const Scalar _tmp22 = _b[3] * _tmp2;
  const Scalar _tmp23 = -_tmp21 + _tmp22;
  const Scalar _tmp24 = _tmp19 + _tmp20 + _tmp23;
  const Scalar _tmp25 = (1.0 / 2.0) * _a[3];
  const Scalar _tmp26 = _b[3] * _tmp0;
  const Scalar _tmp27 = _b[1] * _tmp6;
  const Scalar _tmp28 = _b[0] * _tmp4;
  const Scalar _tmp29 = _b[2] * _tmp2;
  const Scalar _tmp30 = _tmp28 + _tmp29;
  const Scalar _tmp31 = _tmp26 + _tmp27 + _tmp30;
  const Scalar _tmp32 = (1.0 / 2.0) * _a[2];
  const Scalar _tmp33 = -_tmp1 + _tmp3 + _tmp8;
  const Scalar _tmp34 = _tmp11 + _tmp12;
  const Scalar _tmp35 = _tmp13 + _tmp15 + _tmp34;
  const Scalar _tmp36 = -_tmp20;
  const Scalar _tmp37 = _tmp18 + _tmp23 + _tmp36;
  const Scalar _tmp38 = -_tmp26;
  const Scalar _tmp39 = _tmp27 + _tmp28 - _tmp29 + _tmp38;
  const Scalar _tmp40 = _tmp1 + _tmp3 + _tmp5 + _tmp7;
  const Scalar _tmp41 = _tmp14 - _tmp15 + _tmp34;
  const Scalar _tmp42 = _tmp19 + _tmp21 + _tmp22 + _tmp36;
  const Scalar _tmp43 = -_tmp27 + _tmp30 + _tmp38;
  const Scalar _tmp44 = 2 * _a[1];
  const Scalar _tmp45 = _b[6] * _tmp44;
  const Scalar _tmp46 = 2 * _b[5];
  const Scalar _tmp47 = _a[2] * _tmp46;
  const Scalar _tmp48 = _tmp45 - _tmp47;
  const Scalar _tmp49 = _a[1] * _tmp46;
  const Scalar _tmp50 = 2 * _a[2];
  const Scalar _tmp51 = _b[6] * _tmp50;
  const Scalar _tmp52 = _tmp49 + _tmp51;
  const Scalar _tmp53 = 2 * _a[0];
  const Scalar _tmp54 = _b[6] * _tmp53;
  const Scalar _tmp55 = 2 * _a[3];
  const Scalar _tmp56 = _b[5] * _tmp55;
  const Scalar _tmp57 = 4 * _a[2];
  const Scalar _tmp58 = -_b[4] * _tmp57 + _tmp54 - _tmp56;
  const Scalar _tmp59 = 4 * _a[1];
  const Scalar _tmp60 = _a[0] * _tmp46;
  const Scalar _tmp61 = _b[6] * _tmp55;
  const Scalar _tmp62 = -_b[4] * _tmp59 + _tmp60 + _tmp61;
  const Scalar _tmp63 = _b[4] * _tmp50;
  const Scalar _tmp64 = -_tmp54 + _tmp63;
  const Scalar _tmp65 = _b[4] * _tmp53;
  const Scalar _tmp66 = _tmp51 + _tmp65;
  const Scalar _tmp67 = _b[4] * _tmp55;
  const Scalar _tmp68 = -_b[5] * _tmp57 + _tmp45 + _tmp67;
  const Scalar _tmp69 = _b[4] * _tmp44;
  const Scalar _tmp70 = 4 * _a[0];
  const Scalar _tmp71 = -_b[5] * _tmp70 - _tmp61 + _tmp69;
  const Scalar _tmp72 = _tmp60 - _tmp69;
  const Scalar _tmp73 = _tmp49 + _tmp65;
  const Scalar _tmp74 = -_b[6] * _tmp59 + _tmp47 - _tmp67;
  const Scalar _tmp75 = -_b[6] * _tmp70 + _tmp56 + _tmp63;

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 6> _res_D_a;

  _res_D_a(0, 0) = -_tmp10 * _tmp9 - _tmp16 * _tmp17 + _tmp24 * _tmp25 + _tmp31 * _tmp32;
  _res_D_a(0, 1) = -_tmp10 * _tmp16 + _tmp17 * _tmp9 - _tmp24 * _tmp32 + _tmp25 * _tmp31;
  _res_D_a(0, 2) = _tmp10 * _tmp24 - _tmp16 * _tmp32 - _tmp17 * _tmp31 + _tmp25 * _tmp9;
  _res_D_a(0, 3) = 0;
  _res_D_a(0, 4) = 0;
  _res_D_a(0, 5) = 0;
  _res_D_a(1, 0) = -_tmp10 * _tmp35 - _tmp17 * _tmp33 + _tmp25 * _tmp39 + _tmp32 * _tmp37;
  _res_D_a(1, 1) = -_tmp10 * _tmp33 + _tmp17 * _tmp35 + _tmp25 * _tmp37 - _tmp32 * _tmp39;
  _res_D_a(1, 2) = _tmp10 * _tmp39 - _tmp17 * _tmp37 + _tmp25 * _tmp35 - _tmp32 * _tmp33;
  _res_D_a(1, 3) = 0;
  _res_D_a(1, 4) = 0;
  _res_D_a(1, 5) = 0;
  _res_D_a(2, 0) = -_tmp10 * _tmp42 - _tmp17 * _tmp43 + _tmp25 * _tmp40 + _tmp32 * _tmp41;
  _res_D_a(2, 1) = -_tmp10 * _tmp43 + _tmp17 * _tmp42 + _tmp25 * _tmp41 - _tmp32 * _tmp40;
  _res_D_a(2, 2) = _tmp10 * _tmp40 - _tmp17 * _tmp41 + _tmp25 * _tmp42 - _tmp32 * _tmp43;
  _res_D_a(2, 3) = 0;
  _res_D_a(2, 4) = 0;
  _res_D_a(2, 5) = 0;
  _res_D_a(3, 0) = -_tmp10 * _tmp58 - _tmp17 * _tmp48 + _tmp25 * _tmp52 + _tmp32 * _tmp62;
  _res_D_a(3, 1) = -_tmp10 * _tmp48 + _tmp17 * _tmp58 + _tmp25 * _tmp62 - _tmp32 * _tmp52;
  _res_D_a(3, 2) = _tmp10 * _tmp52 - _tmp17 * _tmp62 + _tmp25 * _tmp58 - _tmp32 * _tmp48;
  _res_D_a(3, 3) = 1;
  _res_D_a(3, 4) = 0;
  _res_D_a(3, 5) = 0;
  _res_D_a(4, 0) = -_tmp10 * _tmp68 - _tmp17 * _tmp64 + _tmp25 * _tmp71 + _tmp32 * _tmp66;
  _res_D_a(4, 1) = -_tmp10 * _tmp64 + _tmp17 * _tmp68 + _tmp25 * _tmp66 - _tmp32 * _tmp71;
  _res_D_a(4, 2) = _tmp10 * _tmp71 - _tmp17 * _tmp66 + _tmp25 * _tmp68 - _tmp32 * _tmp64;
  _res_D_a(4, 3) = 0;
  _res_D_a(4, 4) = 1;
  _res_D_a(4, 5) = 0;
  _res_D_a(5, 0) = -_tmp10 * _tmp73 - _tmp17 * _tmp72 + _tmp25 * _tmp75 + _tmp32 * _tmp74;
  _res_D_a(5, 1) = -_tmp10 * _tmp72 + _tmp17 * _tmp73 + _tmp25 * _tmp74 - _tmp32 * _tmp75;
  _res_D_a(5, 2) = _tmp10 * _tmp75 - _tmp17 * _tmp74 + _tmp25 * _tmp73 - _tmp32 * _tmp72;
  _res_D_a(5, 3) = 0;
  _res_D_a(5, 4) = 0;
  _res_D_a(5, 5) = 1;

  return _res_D_a;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
