#pragma once
#include "Lophura.h"
#include "Render.h"

LOPHURA_BEGIN

class Mesh
{
public:
	Mesh(RenderPtr render);
	virtual ~Mesh(void);
public:
	virtual BufferPtr	CreateBuffer(size_t size) = 0;
	virtual void		SetIndexBuffer(BufferPtr buffer,INDEX_FORMAT index_fmt) = 0;
	virtual void		SetVertexBuffer(BufferPtr buffer,COLOR_FORMAT pixel_fmt) = 0;
	virtual void		SetPrimitiveCount(size_t count) = 0;

	//virtual void		ClearColor() = 0;

	virtual void		Render() = 0;
};

LOPHURA_DECLARE_PTR(Mesh)

MeshPtr	CreatBox(RenderPtr render);

LOPHURA_END

