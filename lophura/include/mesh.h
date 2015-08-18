#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render.h"
#include "lophura_base/include/utility/shared_declaration.h"

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
	virtual void			set_vertex_buffer(data_buffer_ptr buffer,color_format pixel_fmt) = 0;
	virtual void			set_primitive_count(size_t count) = 0;

	virtual void			render() = 0;
};

mesh_ptr	creat_box(render_ptr render);

END_NS_LOPHURA()

