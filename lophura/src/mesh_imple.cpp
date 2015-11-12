#include "lophura/include/mesh_imple.h"

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/math.h"

#include "lophura/include/data_buffer.h"
#include "lophura/include/render_state/input_layout.h"

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

	input_layout_ptr input_layout_ = input_layout::create(&( descs_[0] ), descs_.size());

	if ( !input_layout_){
		return;
	}
	
	for ( size_t i_buffer = 0; i_buffer < vertex_buffers_.size(); ++i_buffer){
		render_->set_vertex_buffer(
			slots_[i_buffer], &vertex_buffers_[i_buffer], 1,
			&strides_[i_buffer], &offsets_[i_buffer]);
	}
	render_->set_index_buffer( index_buffer_, index_fmt_);
	render_->set_input_layout( input_layout_);
	render_->set_primitive_topology(primitive_topology::primitive_triangle_list);

	render_->draw_index( 0, primcount_);
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

void mesh_imple::add_vertex_buffer(size_t slot, data_buffer_ptr const& buffer, size_t stride, size_t offset)
{
	assert(buffer);
	slots_.push_back(slot);
	vertex_buffers_.push_back(buffer);
	strides_.push_back(stride);
	offsets_.push_back(offset);
}

void mesh_imple::set_primitive_count(size_t count)
{
	primcount_ = count;
}

void mesh_imple::set_input_element_desc( std::vector<input_element_desc> const& descs )
{
	descs_ = descs;
}

END_NS_LOPHURA()

using namespace lophura;

mesh_ptr	creat_box(render_ptr render)
{
	mesh_imple* mesh	= new mesh_imple(render);
	
	size_t const geometry_slot	= 0;
	size_t const normal_slot	= 1;
	size_t const uv_slot		= 2;

	{
		data_buffer_ptr indices	= mesh->create_buffer(sizeof(uint16_t)*36);
		data_buffer_ptr verts	= mesh->create_buffer(sizeof(vec4)*24);
		data_buffer_ptr normals	= mesh->create_buffer(sizeof(vec4)*24);
		data_buffer_ptr uvs		= mesh->create_buffer(sizeof(vec4)*24);

		uint16_t*    pidxs	= reinterpret_cast<uint16_t*>(indices->raw_data(0));
		vec4*		 pverts = reinterpret_cast<vec4*>(verts->raw_data(0));
		vec4*		 pnorms = reinterpret_cast<vec4*>(normals->raw_data(0));
		vec4*		 puvs	= reinterpret_cast<vec4*>(uvs->raw_data(0));

		{
			//+x
			pverts[0]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pverts[1]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pverts[2]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[3]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			pnorms[0] = pnorms[1] = pnorms[2] = pnorms[3] = vec4(1.0f,0.0f,0.0f,0.0f);
			puvs[0]		= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[1]		= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[2]		= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[3]		= vec4(0.0f , 1.0f , 0.0f , 0.0f);
			//-x
			pverts[4]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[5]	= vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pverts[6]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pverts[7]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pnorms[4] = pnorms[5] = pnorms[6] = pnorms[7] = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
			puvs[4]		= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[5]		= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[6]		= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[7]		= vec4(0.0f , 1.0f , 0.0f , 0.0f);
			//+y
			pverts[8]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pverts[9]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pverts[10]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[11]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pnorms[8] = pnorms[9] = pnorms[10] = pnorms[11] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
			puvs[8]		= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[9]		= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[10]	= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[11]	= vec4(0.0f , 1.0f , 0.0f , 0.0f);
			//-y
			pverts[12]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[13]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pverts[14]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			pverts[15]	= vec4(.0f, 0.0f, 1.0f, 1.0f);
			pnorms[12] = pnorms[13] = pnorms[14] = pnorms[15] = vec4(0.0f, -1.0f, 0.0f, 0.0f);
			puvs[12]	= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[13]	= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[14]	= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[15]	= vec4(0.0f , 1.0f , 0.0f , 0.0f);
			//+z
			pverts[16]	= vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pverts[17]	= vec4(1.0f, 0.0f, 1.0f, 1.0f);
			pverts[18]	= vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pverts[19]	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pnorms[16] = pnorms[17] = pnorms[18] = pnorms[19] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
			puvs[16]	= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[17]	= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[18]	= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[19]	= vec4(0.0f , 1.0f , 0.0f , 0.0f);
			//-z
			pverts[20]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[21]	= vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pverts[22]	= vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pverts[23]	= vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pnorms[20] = pnorms[21] = pnorms[22] = pnorms[23] = vec4(0.0f, 0.0f, -1.0f, 0.0f);
			puvs[20]	= vec4(0.0f , 0.0f , 0.0f , 0.0f);
			puvs[21]	= vec4(1.0f , 0.0f , 0.0f , 0.0f);
			puvs[22]	= vec4(1.0f , 1.0f , 0.0f , 0.0f);
			puvs[23]	= vec4(0.0f , 1.0f , 0.0f , 0.0f);
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

		mesh->add_vertex_buffer(geometry_slot,verts,sizeof(vec4),0);
		mesh->add_vertex_buffer(normal_slot,normals,sizeof(vec4),0);
		mesh->add_vertex_buffer(uv_slot,uvs,sizeof(vec4),0);
		mesh->set_index_buffer(indices, lophura::ifm_16);

		std::vector<input_element_desc> descs;
		descs.push_back( input_element_desc( "POSITION", 0, fmt_r32g32b32a32_unit, geometry_slot));
		descs.push_back( input_element_desc( "NORMAL", 0, fmt_r32g32b32a32_unit, normal_slot));
		descs.push_back( input_element_desc( "TEXCOORD", 0, fmt_r32g32b32a32_unit, uv_slot));

		mesh->set_input_element_desc(descs);

		mesh->set_primitive_count(12);
	}
	return mesh_ptr(mesh);
}

mesh_ptr creat_trangle(lophura::render_ptr render)
{
	mesh_imple* mesh	= new mesh_imple(render);

	size_t const geometry_slot	= 0;
	size_t const normal_slot	= 1;
	size_t const uv_slot		= 2;

	{
		data_buffer_ptr indices	= mesh->create_buffer(sizeof(uint16_t)*36);
		data_buffer_ptr verts	= mesh->create_buffer(sizeof(vec4)*24);
		data_buffer_ptr normals	= mesh->create_buffer(sizeof(vec4)*24);
		data_buffer_ptr uvs		= mesh->create_buffer(sizeof(vec4)*24);

		uint16_t*    pidxs	= reinterpret_cast<uint16_t*>(indices->raw_data(0));
		vec4*		 pverts = reinterpret_cast<vec4*>(verts->raw_data(0));
		vec4*		 pnorms = reinterpret_cast<vec4*>(normals->raw_data(0));
		vec4*		 puvs	= reinterpret_cast<vec4*>(uvs->raw_data(0));

		{
			//+x
			pverts[0]	= vec4(0.0f, 0.0f, 0.0f, 1.0f);
			pverts[1]	= vec4(2.0f, 1.0f, 0.0f, 1.0f);
			pverts[2]	= vec4(2.0f, 0.0f, 0.0f, 1.0f);
			pnorms[0] = pnorms[1] = pnorms[2] = pnorms[3] = vec4(1.0f,0.0f,0.0f,0.0f);
			//indices
			pidxs[ 0] = 0;	pidxs[ 1] = 1;	pidxs[ 2] = 2;
		}

		mesh->add_vertex_buffer(geometry_slot,verts,sizeof(vec4),0);
		mesh->add_vertex_buffer(normal_slot,normals,sizeof(vec4),0);
		mesh->add_vertex_buffer(uv_slot,uvs,sizeof(vec4),0);
		mesh->set_index_buffer(indices, lophura::ifm_16);

		std::vector<input_element_desc> descs;
		descs.push_back( input_element_desc( "POSITION", 0, fmt_r32g32b32a32_unit, geometry_slot));
		descs.push_back( input_element_desc( "NORMAL", 0, fmt_r32g32b32a32_unit, normal_slot));
		descs.push_back( input_element_desc( "TEXCOORD", 0, fmt_r32g32b32a32_unit, uv_slot));

		mesh->set_input_element_desc(descs);

		mesh->set_primitive_count(1);
	}
	return mesh_ptr(mesh);
}