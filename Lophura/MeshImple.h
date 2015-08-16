#pragma once
#include "mesh.h"
#include "Lophura.h"

LOPHURA_BEGIN

class MeshImple :
	public Mesh
{
public:
	MeshImple(RenderPtr render);
	~MeshImple(void);
public:

	virtual BufferPtr	CreateBuffer(size_t size) override;
	virtual void		SetIndexBuffer(BufferPtr buffer,INDEX_FORMAT index_fmt) override;
	virtual void		SetVertexBuffer(BufferPtr buffer,COLOR_FORMAT pixel_fmt) override;
	virtual void		SetPrimitiveCount(size_t count) override;

	virtual void		Render() override;
private:
	RenderPtr	render_;
	BufferPtr	index_buffer_;
	BufferPtr	vertex_buffer_;

	INDEX_FORMAT	index_fmt_;
	COLOR_FORMAT	pixel_fmt_;
	size_t			primcount_;
};

LOPHURA_END