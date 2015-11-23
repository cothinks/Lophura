#include <include/math/math.h>
#include <cmath>

namespace lophura_base
{
	vec2 clampss(const vec2& v, float min, float max)
	{
		return vec2(
			clamp(v[0], min, max),
			clamp(v[1], min, max)
			);
	}

	vec3 clampss(const vec3& v, float min, float max)
	{
		return vec3(
			clamp(v[0], min, max),
			clamp(v[1], min, max),
			clamp(v[2], min, max)
			);
	}

	vec4 clampss(const vec4& v, float min, float max)
	{
		return vec4(
			clamp(v[0], min, max),
			clamp(v[1], min, max),
			clamp(v[2], min, max),
			clamp(v[3], min, max)
			);
	}

	vec2 normalize2(const vec2& v)
	{
		float length = v.length();
		if(equal<float>(length, 0.0f)){
			length = 1.0f;
		}
		float inv_length = 1.0f / length;
		return v * inv_length;
	}

	vec3 normalize3(const vec3& v)
	{
		float length = v.length();
		if(equal<float>(length, 0.0f)){
			length = 1.0f;
		}
		float inv_length = 1.0f / length;
		return v * inv_length;
	}

	vec4 normalize4(const vec4& v)
	{
		float length = v.length();
		if(equal<float>(length, 0.0f)){
			length = 1.0f;
		}
		float inv_length = 1.0f / length;
		return v * inv_length;
	}

vec3 cross_prod3(vec3 const& v1,vec3 const& v2)
{
	return vec3(
		v1[1]*v2[2] - v1[2]*v2[1],
		v1[2]*v2[0] - v1[0]*v2[2],
		v1[0]*v2[1] - v1[1]*v2[0]
	);
}

float dot_prod3(const vec3& v1, const vec3& v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

float dot_prod4(const vec4& v1, const vec4& v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
}

vec4& transform(vec4& out,vec4 const& v,matrix44 const& m)
{
	if(&out == &v)
	{
		vec4 tempv(v);
		return transform(out,tempv,m);
	}

	out[0] = dot_prod4(v,m.get_col(0));
	out[1] = dot_prod4(v,m.get_col(1));
	out[2] = dot_prod4(v,m.get_col(2));
	out[3] = dot_prod4(v,m.get_col(3));

	return out;
}

matrix44& matrix_mul(matrix44& matrix,matrix44 const& m1,matrix44 const& m2)
{
	if (&matrix == &m1)
	{
		matrix44 temp_matrix(m1);
		return matrix_mul(matrix,temp_matrix,m2);
	}
	else if(&matrix == &m2)
	{
		matrix44 temp_matrix(m2);
		return matrix_mul(matrix,m1,temp_matrix);
	}

	matrix.data_[0][0] = dot_prod4(m1.get_row(0), m2.get_col(0));
	matrix.data_[0][1] = dot_prod4(m1.get_row(0), m2.get_col(1));
	matrix.data_[0][2] = dot_prod4(m1.get_row(0), m2.get_col(2));
	matrix.data_[0][3] = dot_prod4(m1.get_row(0), m2.get_col(3));

	matrix.data_[1][0] = dot_prod4(m1.get_row(1), m2.get_col(0));
	matrix.data_[1][1] = dot_prod4(m1.get_row(1), m2.get_col(1));
	matrix.data_[1][2] = dot_prod4(m1.get_row(1), m2.get_col(2));
	matrix.data_[1][3] = dot_prod4(m1.get_row(1), m2.get_col(3));

	matrix.data_[2][0] = dot_prod4(m1.get_row(2), m2.get_col(0));
	matrix.data_[2][1] = dot_prod4(m1.get_row(2), m2.get_col(1));
	matrix.data_[2][2] = dot_prod4(m1.get_row(2), m2.get_col(2));
	matrix.data_[2][3] = dot_prod4(m1.get_row(2), m2.get_col(3));

	matrix.data_[3][0] = dot_prod4(m1.get_row(3), m2.get_col(0));
	matrix.data_[3][1] = dot_prod4(m1.get_row(3), m2.get_col(1));
	matrix.data_[3][2] = dot_prod4(m1.get_row(3), m2.get_col(2));
	matrix.data_[3][3] = dot_prod4(m1.get_row(3), m2.get_col(3));

	return matrix;
}

void matrix_scale(matrix44& matrix,float sx,float sy,float sz)
{
	matrix.data_[0][0] = sx;
	matrix.data_[1][1] = sy;
	matrix.data_[2][2] = sz;
	matrix.data_[3][3] = 1;
}

void matrix_lookat(matrix44& matrix,const vec3& eye,const vec3& target,const vec3& up)
{
	vec3 zdir = target - eye;
	zdir.normalize();
	vec3 xdir = cross_prod3(up,zdir);
	xdir.normalize();
	vec3 ydir = cross_prod3(zdir,xdir);

	matrix = matrix44(
		xdir[0],ydir[0],zdir[0],0.0f,
		xdir[1],ydir[1],zdir[1],0.0f,
		xdir[2],ydir[2],zdir[2],0.0f,
		-dot_prod3(xdir,eye),-dot_prod3(ydir,eye),-dot_prod3(zdir,eye),1.0f
		);
}

void matrix_perspective_fov(matrix44& matrix,float fov,float aspect,float n,float f)
{
	float ys = 1.0f / std::tan(fov/2);
	float xs = ys / aspect;

	matrix = matrix44(
		xs,		0.0f,	0.0f,		0.0f,
		0.0f,	ys,		0.0f,		0.0f,
		0.0f,	0.0f,	f/(f-n),		1.0f,
		0.0f,	0.0f,	-n*f/(f-n),	0.0f
		);
}

template <class T>
T radians(T angle)
{
	return T(angle * PI / T(180.0));
}

matrix44& matrix_roty(matrix44& out, float delta)
{
	float s, c;
	s = sin(radians(delta));
	c = cos(radians(delta));

	out = matrix44::identity();

	out.data_[0][0] = c;
	out.data_[2][0] = s;
	out.data_[0][2] = -s;
	out.data_[2][2] = c;

	return out;
}

};