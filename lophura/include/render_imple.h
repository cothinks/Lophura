#pragma once

#include "lophura/include/lophura_forward.h"

#include "lophura/include/render.h"
#include "lophura/include/render_state/render_state.h"
#include "lophura/include/render_core.h"

BEGIN_NS_LOPHURA()

class render_imple :
	public render
{
public:
	render_imple(void);
	~render_imple(void);
public:
	virtual data_buffer_ptr	create_buffer(size_t size) override;

	virtual void		set_cpp_vertex_shader(cpp_vertex_shader_ptr const& rhs) override;
	virtual void		set_input_layout( input_layout_ptr const& layout ) override;
	virtual void		set_vertex_buffer( 
		size_t start_slot, 
		data_buffer_ptr const* buffer, size_t buffer_count,
		size_t const* strides, size_t const* offsets ) override;
	virtual void		set_index_buffer(data_buffer_ptr const& buffer,index_format index_fmt) override;
	virtual void		set_render_target(data_buffer_ptr const& color_buffer,data_buffer_ptr const& ds_buffer) override;
	//virtual void		set_wvp_matrix(lophura_base::matrix44 const& wvp) override;
	virtual void		set_viewport(viewport const& view_port) override;
	virtual void		set_primitive_topology(primitive_topology pt) override;

	virtual void		clear_color(color_rgba_32f const& color) override;
	virtual void		draw_index(size_t start_pos,size_t prim_count) override;

protected:
	virtual void		commit_command() = 0;
protected:
	render_state_ptr		state_;
	render_core				render_core_;
};

END_NS_LOPHURA()