#pragma once

#include "lophura/include/lophura_forward.h"

BEGIN_NS_LOPHURA()

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