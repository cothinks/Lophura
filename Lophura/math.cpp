#include "math.h"
#include "constant.h"

LOPHURA_BEGIN

void MakeVec4(vec4& vec,float v1,float v2,float v3,float v4)
{
		vec.data_[0] = v1;
		vec.data_[1] = v2;
		vec.data_[2] = v3;
		vec.data_[3] = v4;
}

vec3 CrossProd3(vec3 const& v1,vec3 const& v2)
{
	return vec3(
		v1[1]*v2[2] - v1[2]*v2[1],
		v1[2]*v2[0] - v1[0]*v2[2],
		v1[0]*v2[1] - v1[1]*v2[0]
	);
}

float DotProd3(const vec3& v1, const vec3& v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

float DotProd4(const vec4& v1, const vec4& v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
}

vec4& Transform(vec4& out,vec4 const& v,Matrix44 const& m)
{
	if(&out == &v)
	{
		vec4 tempv(v);
		return Transform(out,tempv,m);
	}

	out[0] = DotProd4(v,m.GetCol(0));
	out[1] = DotProd4(v,m.GetCol(1));
	out[2] = DotProd4(v,m.GetCol(2));
	out[3] = DotProd4(v,m.GetCol(3));

	return out;
}

Matrix44& MatrixMul(Matrix44& matrix,Matrix44 const& m1,Matrix44 const& m2)
{
	if (&matrix == &m1)
	{
		Matrix44 temp_matrix(m1);
		return MatrixMul(matrix,temp_matrix,m2);
	}else if(&matrix == &m2)
	{
		Matrix44 temp_matrix(m2);
		return MatrixMul(matrix,m1,temp_matrix);
	}

	matrix.data_[0][0] = DotProd4(m1.GetRow(0), m2.GetCol(0));
	matrix.data_[0][1] = DotProd4(m1.GetRow(0), m2.GetCol(1));
	matrix.data_[0][2] = DotProd4(m1.GetRow(0), m2.GetCol(2));
	matrix.data_[0][3] = DotProd4(m1.GetRow(0), m2.GetCol(3));

	matrix.data_[1][0] = DotProd4(m1.GetRow(1), m2.GetCol(0));
	matrix.data_[1][1] = DotProd4(m1.GetRow(1), m2.GetCol(1));
	matrix.data_[1][2] = DotProd4(m1.GetRow(1), m2.GetCol(2));
	matrix.data_[1][3] = DotProd4(m1.GetRow(1), m2.GetCol(3));

	matrix.data_[2][0] = DotProd4(m1.GetRow(2), m2.GetCol(0));
	matrix.data_[2][1] = DotProd4(m1.GetRow(2), m2.GetCol(1));
	matrix.data_[2][2] = DotProd4(m1.GetRow(2), m2.GetCol(2));
	matrix.data_[2][3] = DotProd4(m1.GetRow(2), m2.GetCol(3));

	matrix.data_[3][0] = DotProd4(m1.GetRow(3), m2.GetCol(0));
	matrix.data_[3][1] = DotProd4(m1.GetRow(3), m2.GetCol(1));
	matrix.data_[3][2] = DotProd4(m1.GetRow(3), m2.GetCol(2));
	matrix.data_[3][3] = DotProd4(m1.GetRow(3), m2.GetCol(3));

	return matrix;
}

void MatrixScale(Matrix44& matrix,float sx,float sy,float sz)
{
	matrix.data_[0][0] = sx;
	matrix.data_[1][1] = sy;
	matrix.data_[2][2] = sz;
	matrix.data_[3][3] = 1;
}

void MatrixLookAt(Matrix44& matrix,const vec3& eye,const vec3& target,const vec3& up)
{
	vec3 zdir = target - eye;
	zdir.Normalize();
	vec3 xdir = CrossProd3(up,zdir);
	xdir.Normalize();
	vec3 ydir = CrossProd3(zdir,xdir);

	matrix = Matrix44(
			xdir[0],ydir[0],zdir[0],0.0f,
			xdir[1],ydir[1],zdir[1],0.0f,
			xdir[2],ydir[2],zdir[2],0.0f,
			-DotProd3(xdir,eye),-DotProd3(ydir,eye),-DotProd3(zdir,eye),1.0f
		);
}

void MatrixPerspectiveFov(Matrix44& matrix,float fov,float aspect,float n,float f)
{
	float ys = 1.0f / std::tan(fov/2);
	float xs = ys / aspect;

	matrix = Matrix44(
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

Matrix44& MatrixRotY(Matrix44& out, float delta)
{
	float s, c;
	s = sin(radians(delta));
	c = cos(radians(delta));

	out = Matrix44::Identity();

	out.data_[0][0] = c;
	out.data_[2][0] = s;
	out.data_[0][2] = -s;
	out.data_[2][2] = c;

	return out;
}

LOPHURA_END