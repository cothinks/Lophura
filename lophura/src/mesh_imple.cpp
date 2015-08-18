#include "lophura/include/mesh_imple.h"

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/math.h"

#include "lophura/include/data_buffer.h"

using namespace lophura_base;
using namespace std;

BEGIN_NS_LOPHURA()

mesh_imple::mesh_imple(render_ptr render):mesh(render),render_(render)
{}

mesh_imple::~mesh_imple(void)
{}

void mesh_imple::render()
{
	assert(render_.get());

	render_->set_index_buffer(index_buffer_,ifm_16);
	render_->set_vertex_buffer(vertex_buffer_);
	render_->draw_index(0,primcount_);
}

data_buffer_ptr mesh_imple::create_buffer(size_t size)
{
	return render_->create_buffer(size);
}

void mesh_imple::set_index_buffer(data_buffer_ptr buffer,index_format index_fmt)
{
	index_buffer_	= buffer;
	index_fmt_		= index_fmt;
}

void mesh_imple::set_vertex_buffer(data_buffer_ptr buffer,color_format pixel_fmt)
{
	vertex_buffer_	= buffer;
	pixel_fmt_		= pixel_fmt;
}

void mesh_imple::set_primitive_count(size_t count)
{
	primcount_ = count;
}

mesh_ptr	creat_box(render_ptr render)
{
	mesh_imple* mesh	= new mesh_imple(render);
	{
		data_buffer_ptr indices		= mesh->create_buffer(sizeof(uint16_t)*36);
		data_buffer_ptr verts		= mesh->create_buffer(sizeof(vec4)*24);

		uint16_t*    pidxs = reinterpret_cast<uint16_t*>(indices->raw_data(0));
		vec4*		pverts = reinterpret_cast<vec4*>(verts->raw_data(0));

		{
			//+x
			pverts[0]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pverts[0]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pverts[1]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pverts[2]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[3]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			//-x
			pverts[4]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[5]	= vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pverts[6]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pverts[7]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			//+y
			pverts[8]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pverts[9]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pverts[10]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[11]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			//-y
			pverts[12]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[13]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pverts[14]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			pverts[15]	= vec4(.0f, 0.0f, 1.0f, 1.0f);
			//+z
			pverts[16]	= vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pverts[17]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			pverts[18]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[19]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			//-z
			pverts[20]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[21]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pverts[22]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pverts[23]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			//indices
			pidxs[ 0] = 0;	pidxs[ 1] = 1;	pidxs[ 2] = 2;
			pidxs[ 3] = 2;	pidxs[ 4] = 3;	pidxs[ 5] = 0;
			pidxs[ 6] = 4;	pidxs[ 7] = 5;	pidxs[ 8] = 6;
			pidxs[ 9] = 6;	pidxs[10] = 7;	pidxs[11] = 4;
			pidxs[12] = 8;	pidxs[13] = 9;	pidxs[14] = 10;
			pidxs[15] = 10;	pidxs[16] = 11;	pidxs[17] = 8;
			pidxs[18] = 12;	pidxs[19] = 13;	pidxs[20] = 14;
			pidxs[21] = 14;pidxs[22] = 15;pidxs[23] = 12;
			pidxs[24] = 16;pidxs[25] = 17;pidxs[26] = 18;
			pidxs[27] = 18;pidxs[28] = 19;pidxs[29] = 16;
			pidxs[30] = 20;pidxs[31] = 21;pidxs[32] = 22;
			pidxs[33] = 22;pidxs[34] = 23;pidxs[35] = 20;
		}

		mesh->set_vertex_buffer(verts,fmt_r32g32b32a32_unit);
		mesh->set_index_buffer(indices,ifm_16);

		mesh->set_primitive_count(12);
	}
	return mesh_ptr(mesh);
}

END_NS_LOPHURA()