#pragma once

#include "lophura/include/mesh.h"

BEGIN_NS_LOPHURA()

class mesh_imple :
	public mesh
{
public:
	mesh_imple(render_ptr render);
	~mesh_imple(void);
public:

	virtual data_buffer_ptr	create_buffer(size_t size) override;
	virtual void			set_index_buffer(data_buffer_ptr buffer,index_format index_fmt) override;
	virtual void			set_vertex_buffer(data_buffer_ptr buffer,color_format pixel_fmt) override;
	virtual void			set_primitive_count(size_t count) override;

	virtual void			render() override;
private:
	render_ptr	render_;
	data_buffer_ptr	index_buffer_;
	data_buffer_ptr	vertex_buffer_;

	index_format	index_fmt_;
	color_format	pixel_fmt_;
	size_t			primcount_;
};

END_NS_LOPHURA()