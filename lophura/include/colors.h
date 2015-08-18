#pragma once

#include "lophura/include/lophura_forward.h"

BEGIN_NS_LOPHURA()

struct color_rgba_32f  
{
	float r,g,b,a;

	color_rgba_32f()
	{}
	explicit color_rgba_32f(float r,float g,float b,float a):r(r),g(g),b(b),a(a)
	{}
};

END_NS_LOPHURA()