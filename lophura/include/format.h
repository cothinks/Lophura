#pragma once

#include "lophura/include/lophura_forward.h"

BEGIN_NS_LOPHURA()

enum index_format
{
	ifm_16,
	ifm_32
};

enum color_format
{
	fmt_unknown				= 0,
	fmt_r32g32b32a32_unit	= 1
};

enum clear_flag
{
	clear_depth = 0x1,
	clear_stencil = 0x2
};

END_NS_LOPHURA()