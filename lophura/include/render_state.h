#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/math/matrix.h"

#include "lophura/include/lophura_define.h"
#include "lophura/include/format.h"
#include "lophura/include/viewport.h"
#include "lophura/include/colors.h"

#include "lophura_base/include/utility/shared_declaration.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);

struct render_state
{
	command_id				command_;

	data_buffer_ptr			index_buffer_;
	index_format			index_format_;
	data_buffer_ptr			vertex_buffer_;

	data_buffer_ptr			color_target_;
	data_buffer_ptr			depth_stencil_target_;

	viewport				view_port_;
	lophura_base::matrix44			wrold_view_proj_;
	primitive_topology		primitive_topology_;

	size_t					start_index_;
	size_t					primitive_count_;
		
	color_rgba_32f			clear_color_;
};

END_NS_LOPHURA()