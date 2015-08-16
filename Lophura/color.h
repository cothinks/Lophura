#pragma once

#include "Lophura.h"

LOPHURA_BEGIN

struct COLORRGBA32F  
{
	float r,g,b,a;

	COLORRGBA32F()
	{}
	explicit COLORRGBA32F(float r,float g,float b,float a):r(r),g(g),b(b),a(a)
	{}
};

LOPHURA_END