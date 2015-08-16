#pragma once

#include "Lophura.h"
#include "DataBuffer.h"
#include "ViewPort.h"
#include "color.h"
#include "vector.h"
#include "RenderState.h"

LOPHURA_BEGIN

class Render
{
public:
	Render(void);
	virtual ~Render(void);
public:
	virtual BufferPtr	CreateBuffer(size_t size) = 0;

	virtual	void		SetVertexBuffer(BufferPtr const& buffer)	= 0;
	virtual void		SetIndexBuffer(BufferPtr const& buffer,INDEX_FORMAT index_fmt)	= 0;
	virtual void		SetRenderTarget(BufferPtr const& color_buffer,BufferPtr const& ds_buffer) = 0;
	virtual void		ClearColor(COLORRGBA32F const& color) = 0;

	virtual void		SetWVPMatrix(Matrix44 const& wvp) = 0;
	virtual void		SetViewPort(ViewPort const& view_port) = 0;
	virtual void		SetPrimitiveTopology(PrimitiveTopology primitive_topology) = 0;

	virtual void		DrawIndex(size_t start_pos,size_t prim_count) = 0;

	//test
	virtual void		SetSwapChian(SwapChainPtr swap_chain) = 0;
};

LOPHURA_DECLARE_PTR(Render)

LOPHURA_END

extern "C"
{
	void LophuraCreateRender(Lophura::RenderPtr& render);
};
