#pragma once

#include "render.h"
#include "renderstate.h"
#include "rendercore.h"

LOPHURA_BEGIN

class RenderImple :
	public Render
{
public:
	RenderImple(void);
	~RenderImple(void);
public:
	virtual BufferPtr	CreateBuffer(size_t size) override;

	virtual void		SetVertexBuffer(BufferPtr const& buffer) override;
	virtual void		SetIndexBuffer(BufferPtr const& buffer,INDEX_FORMAT index_fmt) override;
	virtual void		SetRenderTarget(BufferPtr const& color_buffer,BufferPtr const& ds_buffer) override;
	virtual void		ClearColor(COLORRGBA32F const& color) override;

	virtual void		SetWVPMatrix(lophura_base::Matrix44 const& wvp) override;
	virtual void		SetViewPort(ViewPort const& view_port) override;
	virtual void		SetPrimitiveTopology(PrimitiveTopology primitive_topology) override;

	virtual void		DrawIndex(size_t start_pos,size_t prim_count) override;

protected:
	virtual void		CommitCommand() = 0;
protected:
	RenderStatePtr		state_;
	RenderCore			render_core_;
};

LOPHURA_END