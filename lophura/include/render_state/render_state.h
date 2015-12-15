#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/math/matrix.h"

#include "lophura/include/lophura_define.h"
#include "lophura/include/format.h"
#include "lophura/include/viewport.h"
#include "lophura/include/colors.h"
#include "lophura/include/render_state/input_layout.h"
#include "lophura/include/render_state/input_assembly_state.h"
//#include "lophura/include/surface.h"

#include "lophura_base/include/utility/shared_declaration.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(cpp_vertex_shader);
LOPHURA_DECLARE_CLASS_SHARED_PTR(cpp_pixel_shader);
LOPHURA_DECLARE_CLASS_SHARED_PTR(raster_state);
LOPHURA_DECLARE_CLASS_SHARED_PTR(surface);

struct render_state
{
	command_id				command_;

	data_buffer_ptr			index_buffer_;
	index_format			index_format_;

	input_layout_ptr		input_layout_;
	input_assembly_state	input_assembly_slots_;

	surface_ptr				color_target_;
	surface_ptr				depth_stencil_target_;

	viewport				view_port_;
	raster_state_ptr		ras_state_;
	primitive_topology		primitive_topology_;

	cpp_vertex_shader_ptr	cpp_vs_;
	cpp_pixel_shader_ptr	cpp_ps_;

	size_t					start_index_;
	size_t					primitive_count_;
		
	color_rgba_32f			clear_color_;
};

END_NS_LOPHURA()