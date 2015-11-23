#pragma once

#include "lophura_base/include/platform/constant.h"
#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/matrix.h"

#include <limits>

namespace lophura_base
{
	template<typename param_type>
	param_type clamp(param_type val,param_type min_val,param_type max_val)
	{
		assert(min_val <= max_val);

		if(val < min_val) return min_val;
		if(val > max_val) return max_val;
		return val;
	}

	template <class T>
	bool equal(const T& in1, const T& in2)
	{
		if((T)(std::abs(in1 - in2)) <= std::numeric_limits<T>::epsilon()) return true;
		return false;
	}

	inline bool equal(const vec2& v1, const vec2& v2){
		return
			equal(v1.x(), v2.x()) &&
			equal(v1.y(), v2.y());
	}

	inline bool equal(const vec3& v1, const vec3& v2)
	{
		return
			equal(v1.x(), v2.x()) &&
			equal(v1.y(), v2.y()) &&
			equal(v1.z(), v2.z());
	}

	inline bool equal(const vec4& v1, const vec4& v2)
	{
		return
			equal(v1.x(), v2.x()) &&
			equal(v1.y(), v2.y()) &&
			equal(v1.z(), v2.z()) &&
			equal(v1.w(), v2.w())
			;
	}

	vec2 clampss(const vec2& v, float min, float max);
	vec3 clampss(const vec3& v, float min, float max);
	vec4 clampss(const vec4& v, float min, float max);
// base vector function
	vec2 normalize2(const vec2& v);
	vec3 normalize3(const vec3& v);
	vec4 normalize4(const vec4& v);

//vector transform
	float		dot_prod3(const vec3& v1, const vec3& v2);
	float		dot_prod4(const vec4& v1, const vec4& v2);
	vec3		cross_prod3(vec3 const& v1,vec3 const& v2);
	vec4&		transform(vec4& out,vec4 const& v,matrix44 const& m);

//matrix transform
	void		matrix_scale(matrix44& matrix,float sx,float sy,float sz);
	void		matrix_lookat(matrix44& matrix,const vec3& eye,const vec3& target,const vec3& up);
	void		matrix_perspective_fov(matrix44& matrix,float fov,float aspect,float n,float f);
	matrix44&	matrix_mul(matrix44& matrix,matrix44 const& m1,matrix44 const& m2);
	matrix44&	matrix_roty(matrix44& out, float delta);

};