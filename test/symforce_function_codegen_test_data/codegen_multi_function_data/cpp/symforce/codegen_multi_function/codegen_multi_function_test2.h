// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <lcmtypes/codegen_multi_function/inputs_t.hpp>
#include <lcmtypes/codegen_multi_function/outputs_2_t.hpp>

namespace codegen_multi_function {


/**
* This function was autogenerated. Do not modify by hand.
*
* Arg type(s): Values
* Return type(s): Values
*
*/
template <typename Scalar>
void CodegenMultiFunctionTest2(const codegen_multi_function::inputs_t& inputs, codegen_multi_function::outputs_2_t* const outputs_2) {
    // Input arrays
    assert( outputs_2 != nullptr );

    // Intermediate terms (0)

    // Output terms (1)
    codegen_multi_function::outputs_2_t& _outputs_2 = (*outputs_2);

    _outputs_2.foo = inputs.x + (inputs.y * inputs.y * inputs.y);



}

}  // namespace codegen_multi_function