#pragma once

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/matrix.h"

#include "lophura/include/lophura_forward.h"
#include "lophura/include/lophura_define.h"
#include "lophura/include/format.h"
#include "lophura/include/viewport.h"
#include "lophura/include/colors.h"
#include "lophura/include/lophura_declaration.h"

#include "lophura_base/include/utility/shared_declaration.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_STRUCT_SHARED_PTR(render_state);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(input_layout);

class render
{
public:
	render(void){};
	virtual ~render(void){};
public:
	virtual data_buffer_ptr	create_buffer(size_t size) = 0;

	virtual void		set_cpp_vertex_shader(cpp_vertex_shader_ptr const& rhs) = 0;
	virtual void		set_input_layout( input_layout_ptr const& layout) = 0;
	virtual void		set_vertex_buffer( 
		size_t start_slot,
		data_buffer_ptr const* buffer, size_t buffer_count,
		size_t const* strides, size_t const* offsets ) = 0;
	virtual void		set_index_buffer(data_buffer_ptr const& buffer,index_format index_fmt)	= 0;
	virtual void		set_render_target(data_buffer_ptr const& color_buffer,data_buffer_ptr const& ds_buffer) = 0;
	//virtual void		set_wvp_matrix(lophura_base::matrix44 const& wvp) = 0;
	virtual void		set_viewport(viewport const& view_port) = 0;
	virtual void		set_primitive_topology(primitive_topology pt) = 0;

	virtual void		clear_color(color_rgba_32f const& color) = 0;
	virtual void		draw_index(size_t start_pos,size_t prim_count) = 0;
};

END_NS_LOPHURA()

extern "C"
{
	void lophura_create_render(lophura::render_ptr& render,lophura::render_type render_type);
};
