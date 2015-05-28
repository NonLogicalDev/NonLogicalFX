///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// Restrictions:
///		By making use of the Software for military purposes, you choose to make
///		a Bunny unhappy.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @file glm/glm.h
/// @date 2009-05-01 / 2011-05-16
/// @author Christophe Riccio
///
/// @ref core (Dependence)
/// 
/// @defgroup gtc GTC Extensions (Stable)
///
/// @brief Functions and types that the GLSL specification doesn't define, but useful to have for a C++ program.
/// 
/// GTC extensions aim to be stable. 
/// 
/// Even if it's highly unrecommended, it's possible to include all the extensions at once by
/// including <glm/ext.h>. Otherwise, each extension needs to be included  a specific file.
/// 
/// @defgroup gtx GTX Extensions (Experimental)
/// 
/// @brief Functions and types that the GLSL specification doesn't define, but 
/// useful to have for a C++ program.
/// 
/// Experimental extensions are useful functions and types, but the development of
/// their API and functionality is not necessarily stable. They can change 
/// substantially between versions. Backwards compatibility is not much of an issue
/// for them.
/// 
/// Even if it's highly unrecommended, it's possible to include all the extensions 
/// at once by including <glm/ext.h>. Otherwise, each extension needs to be 
/// included  a specific file.
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_EXT_INCLUDED_DISPLAYED))
#	define GLM_MESSAGE_EXT_INCLUDED_DISPLAYED
#	pragma message("GLM: All extensions included (not recommanded)")
#endif//GLM_MESSAGES

#include "./gtc/bitfield.h"
#include "./gtc/constants.h"
#include "./gtc/epsilon.h"
#include "./gtc/integer.h"
#include "./gtc/matrix_access.h"
#include "./gtc/matrix_integer.h"
#include "./gtc/matrix_inverse.h"
#include "./gtc/matrix_transform.h"
#include "./gtc/noise.h"
#include "./gtc/packing.h"
#include "./gtc/quaternion.h"
#include "./gtc/random.h"
#include "./gtc/reciprocal.h"
#include "./gtc/round.h"
#include "./gtc/type_precision.h"
#include "./gtc/type_ptr.h"
#include "./gtc/ulp.h"
#include "./gtc/vec1.h"

#include "./gtx/associated_min_max.h"
#include "./gtx/bit.h"
#include "./gtx/closest_point.h"
#include "./gtx/color_space.h"
#include "./gtx/color_space_YCoCg.h"
#include "./gtx/compatibility.h"
#include "./gtx/component_wise.h"
#include "./gtx/dual_quaternion.h"
#include "./gtx/euler_angles.h"
#include "./gtx/extend.h"
#include "./gtx/extented_min_max.h"
#include "./gtx/fast_exponential.h"
#include "./gtx/fast_square_root.h"
#include "./gtx/fast_trigonometry.h"
#include "./gtx/gradient_paint.h"
#include "./gtx/handed_coordinate_space.h"
#include "./gtx/integer.h"
#include "./gtx/intersect.h"
#include "./gtx/log_base.h"
#include "./gtx/matrix_cross_product.h"
#include "./gtx/matrix_interpolation.h"
#include "./gtx/matrix_major_storage.h"
#include "./gtx/matrix_operation.h"
#include "./gtx/matrix_query.h"
#include "./gtx/mixed_product.h"
#include "./gtx/norm.h"
#include "./gtx/normal.h"
#include "./gtx/normalize_dot.h"
#include "./gtx/number_precision.h"
#include "./gtx/optimum_pow.h"
#include "./gtx/orthonormalize.h"
#include "./gtx/perpendicular.h"
#include "./gtx/polar_coordinates.h"
#include "./gtx/projection.h"
#include "./gtx/quaternion.h"
#include "./gtx/raw_data.h"
#include "./gtx/rotate_vector.h"
#include "./gtx/spline.h"
#include "./gtx/std_based_type.h"
#if !(GLM_COMPILER & GLM_COMPILER_CUDA)
#	include "./gtx/string_cast.h"
#endif
#include "./gtx/transform.h"
#include "./gtx/transform2.h"
#include "./gtx/type_aligned.h"
#include "./gtx/vector_angle.h"
#include "./gtx/vector_query.h"
#include "./gtx/wrap.h"

#if GLM_HAS_TEMPLATE_ALIASES
#	include "./gtx/scalar_multiplication.h"
#endif

#if GLM_HAS_RANGE_FOR
#	include "./gtx/range.h"
#endif

#if GLM_ARCH & GLM_ARCH_SSE2
#	include "./gtx/simd_vec4.h"
#	include "./gtx/simd_mat4.h"
#endif
