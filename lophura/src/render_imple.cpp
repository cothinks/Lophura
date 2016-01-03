#include "lophura/include/render_imple.h"
#include "lophura/include/syn_render.h"
#include "lophura/include/asyn_render.h"

#include <memory>

using namespace lophura_base;
using namespace std;

BEGIN_NS_LOPHURA()

render_imple::render_imple(void)
{
	state_.reset( new render_state() );
}

render_imple::~render_imple(void)
{}

data_buffer_ptr render_imple::create_buffer(size_t size)
{
	return make_shared<data_buffer>(size);
}

surface_ptr render_imple::create_tex2d(size_t width, size_t height, size_t num_samples, color_format fmt)
{
	return make_shared<surface>(width,height,num_samples,fmt);
}

void render_imple::set_rasterizer_state(raster_state_ptr const& rs)
{
	state_->ras_state_ = rs;
}

void render_imple::set_cpp_vertex_shader( cpp_vertex_shader_ptr const& rhs )
{
	state_->cpp_vs_ = rhs;
}

void render_imple::set_cpp_pixel_shader(cpp_pixel_shader_ptr const& rhs)
{
	state_->cpp_ps_ = rhs;
}

void render_imple::set_input_layout( input_layout_ptr const& layout )
{
	state_->input_layout_ = layout;
}

void render_imple::set_vertex_buffer( size_t start_slot, data_buffer_ptr const* buffer, size_t buffer_count, size_t const* strides, size_t const* offsets )
{
	state_->input_assembly_slots_.update(start_slot, buffer, buffer_count, strides,offsets);
}

void render_imple::set_index_buffer(data_buffer_ptr const& buffer,index_format index_fmt)
{
	state_->index_buffer_ = buffer;
	state_->index_format_ = index_fmt;
}

void render_imple::set_render_target(surface_ptr const& color_buffer, surface_ptr const& ds_buffer)
{
	state_->color_target_			= color_buffer;
	state_->depth_stencil_target_	= ds_buffer;
}

void render_imple::set_viewport(viewport const& view_port)
{
	state_->view_port_ = view_port;
}

void render_imple::set_primitive_topology(primitive_topology pt)
{
	state_->primitive_topology_ = pt;
}

void render_imple::draw_index(size_t start_pos,size_t prim_count)
{
	state_->command_			= command_id::draw_index;
	state_->start_index_		= start_pos;
	state_->primitive_count_	= prim_count;

	commit_command();
}

void render_imple::clear_color( color_rgba_32f const& color )
{
	state_->clear_color_	= color;
	state_->command_		= command_id::clear_color;

	commit_command();
}

void render_imple::clear_depth_stencil(surface_ptr const& depth_stencil_target, uint32_t f,float d,uint32_t s)
{
	state_->clear_f = f;
	state_->clear_z = d;
	state_->clear_stencil = s;
	state_->command_ = command_id::clear_depth_stencil;

	commit_command();
}

void render_imple::commit_command()
{
	render_core_.process_render_request(state_);
}


END_NS_LOPHURA()

extern "C"
{
	void lophura_create_render(lophura::render_ptr& render,lophura::render_type render_type)
	{
		switch (render_type)
		{
		case lophura::render_syn:
				render = make_shared<lophura::syn_render>();
			break;
		case lophura::render_asyn:
				render = make_shared<lophura::asyn_render>();
			break;
		default:
				assert( false && "unknown render type !" );
			break;
		}
		
	}
};