#pragma once

#include "lophura/include/lophura_forward.h"

BEGIN_NS_LOPHURA()

struct viewport
{
	float x;
	float y;
	float w;
	float h;
	float minz;
	float maxz;
};

END_NS_LOPHURA()