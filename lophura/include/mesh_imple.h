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
	virtual void			add_vertex_buffer(size_t slot, data_buffer_ptr const& buffer, size_t stride, size_t offset) override;
	virtual void			set_input_element_desc(std::vector<input_element_desc> const& descs) override;
	virtual void			set_primitive_count(size_t count) override;

	virtual void			render() override;
private:
	render_ptr	render_;
	data_buffer_ptr	index_buffer_;

	std::vector<input_element_desc> descs_;

	std::vector<data_buffer_ptr> vertex_buffers_;
	std::vector<size_t>			 strides_;
	std::vector<size_t>			 offsets_;
	std::vector<size_t>			 slots_;

	index_format	index_fmt_;
	size_t			primcount_;
};

END_NS_LOPHURA()