#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/render_state/input_layout.h"

#include <vector>

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(mesh);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);

class mesh
{
public:
	mesh(render_ptr render);
	virtual ~mesh(void);
public:
	virtual data_buffer_ptr	create_buffer(size_t size) = 0;
	virtual void			set_index_buffer(data_buffer_ptr buffer,index_format index_fmt) = 0;
	virtual void			add_vertex_buffer(size_t slot, data_buffer_ptr const& buffer, size_t stride, size_t offset) = 0;
	virtual void			set_input_element_desc( std::vector<input_element_desc> const& descs) = 0;
	virtual void			set_primitive_count(size_t count) = 0;

	virtual void			render() = 0;
};

END_NS_LOPHURA()

lophura::mesh_ptr	creat_box(lophura::render_ptr render);
lophura::mesh_ptr	creat_trangle(lophura::render_ptr render);

