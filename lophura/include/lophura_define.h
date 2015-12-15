#pragma once

#include "lophura_base/include/platform/typedefs.h"
#include "lophura/include/lophura_forward.h"
#include "lophura/include/format.h"

BEGIN_NS_LOPHURA()

struct swap_chain_parameter
{
	size_t			width;
	size_t			height;
	size_t			num_samples;
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

enum cull_mode
{
	cull_none,
	cull_front,
	cull_back,

	cull_mode_count,
};

enum fill_mode
{
	fill_wireframe,
	fill_solid,

	fill_mode_count
};

enum prim_type
{
	pt_none,
	pt_point,
	pt_line,
	pt_solid_tri,
	pt_wireframe_tri
};

END_NS_LOPHURA()