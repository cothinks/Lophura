#pragma once

#include "lophura.h"
#include "databuffer.h"
#include "viewport.h"
#include "color.h"
#include "renderstate.h"

#include "lophura_base/include/math/vector.h"

LOPHURA_BEGIN

enum RenderType
{
	RenderSyn,
	RenderAsyn
};


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

	virtual void		SetWVPMatrix(lophura_base::Matrix44 const& wvp) = 0;
	virtual void		SetViewPort(ViewPort const& view_port) = 0;
	virtual void		SetPrimitiveTopology(PrimitiveTopology primitive_topology) = 0;

	virtual void		DrawIndex(size_t start_pos,size_t prim_count) = 0;
};

LOPHURA_DECLARE_PTR(Render)

LOPHURA_END

extern "C"
{
	void LophuraCreateRender(Lophura::RenderPtr& render,Lophura::RenderType render_type);
};
