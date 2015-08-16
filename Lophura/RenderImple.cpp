#include "RenderImple.h"
#include <memory>

using namespace std;

LOPHURA_BEGIN

RenderImple::RenderImple(void)
{
	state_.reset( new RenderState() );
}


RenderImple::~RenderImple(void)
{
}

BufferPtr RenderImple::CreateBuffer(size_t size)
{
	return make_shared<Buffer>(size);
}

void RenderImple::SetIndexBuffer(BufferPtr const& buffer,INDEX_FORMAT index_fmt)
{
	state_->index_buffer_ = buffer;
	state_->index_format_ = index_fmt;
}

void RenderImple::SetVertexBuffer(BufferPtr const& buffer)
{
	state_->vertex_buffer_ = buffer;
}

void RenderImple::SetRenderTarget( BufferPtr const& color_buffer,BufferPtr const& ds_buffer )
{
	state_->color_target_			= color_buffer;
	state_->depth_stencil_target_	= ds_buffer;
}

void RenderImple::SetWVPMatrix(Matrix44 const& wvp)
{
	state_->wrold_view_proj_ = wvp;
}

void RenderImple::SetViewPort(ViewPort const& view_port)
{
	state_->view_port_ = view_port;
}

void RenderImple::SetPrimitiveTopology(PrimitiveTopology primitive_topology)
{
	state_->primitive_topology_ = primitive_topology;
}

void RenderImple::DrawIndex(size_t start_pos,size_t prim_count)
{
	state_->command_			= CommandId::draw_index;
	state_->start_index_		= start_pos;
	state_->primitive_count_	= prim_count;

	PushCommand();
}

void RenderImple::ClearColor( COLORRGBA32F const& color )
{
	state_->clear_color_	= color;
	state_->command_		= CommandId::clear_color;

	PushCommand();
}

void RenderImple::PushCommand()
{
	render_core_.Update(state_);
	render_core_.Execute();
}

void RenderImple::SetSwapChian( SwapChainPtr swap_chain )
{
	state_->swap_chain_ = swap_chain;
}

LOPHURA_END

extern "C"
{
	void LophuraCreateRender(Lophura::RenderPtr& render)
	{
		render = make_shared<Lophura::RenderImple>();
	}
};