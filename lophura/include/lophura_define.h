#pragma once

#include "lophura_base/include/platform/typedefs.h"
#include "lophura/include/lophura_forward.h"
#include "lophura/include/format.h"

BEGIN_NS_LOPHURA()

struct swap_chain_parameter
{
	uint32_t	width;
	uint32_t	height;

	color_format	color_fmt;
	uint64_t		any_data;
};

enum render_type
{
	render_syn,
	render_asyn
};

enum class primitive_topology
{
	primitive_triangle_list,
};

enum class command_id
{
	draw,
	draw_index,
	clear_depth_stencil,
	clear_color
};

END_NS_LOPHURA()