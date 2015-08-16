#pragma once
#include "Lophura.h"
#include "vector.h"

LOPHURA_BEGIN 

template<class T>
void clamp(T& out,T min,T max)
{
	if( out > max )
		out = max;
	if( out < min )
		out = min;
}

void	MakeVec4(vec4& vec,float v1,float v2,float v3,float v4);

vec3	CrossProd3(vec3 const& v1,vec3 const& v2);
float	DotProd3(const vec3& v1, const vec3& v2);
float	DotProd4(const vec4& v1, const vec4& v2);

vec4&	Transform(vec4& out,vec4 const& v,Matrix44 const& m);

Matrix44&	MatrixMul(Matrix44& matrix,Matrix44 const& m1,Matrix44 const& m2);
void		MatrixScale(Matrix44& matrix,float sx,float sy,float sz);
void		MatrixLookAt(Matrix44& matrix,const vec3& eye,const vec3& target,const vec3& up);
void		MatrixPerspectiveFov(Matrix44& matrix,float fov,float aspect,float n,float f);

Matrix44& MatrixRotY(Matrix44& out, float delta);
	

LOPHURA_END