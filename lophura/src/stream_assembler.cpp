#include "lophura/include/stream_assembler.h"
#include "lophura/include/data_buffer.h"

#include "lophura_base/include/math/vector.h"

using namespace lophura_base;
using namespace std;

BEGIN_NS_LOPHURA()

vec4 get_vec4(color_format fmt, semantic_value const& sv, const void* data)
{
	assert( data );

	if( !data ){ return vec4::zero(); }

	const float* floats = (const float*)data;

	float w_comp = ( sv.get_system_value() == sv_position ) ? 1.0f : 0.0f;

	switch(fmt)
	{
	case fmt_r32g32b32a32_unit:
		return *reinterpret_cast<vec4 const*>(floats);
	default:
		assert(false);
	}

	return vec4::zero();
}


void stream_assembler::update(render_state const* state)
{
	layout_ = state->input_layout_.get();
	stream_buffer_descs_ = state->input_assembly_slots_.slots_.data();

	if (state->cpp_vs_)
	{
		update_register_map(state->cpp_vs_->get_register_map());
	}
}

void stream_assembler::update_register_map( map<semantic_value, size_t> const& reg_map )
{
	register_to_intput_element_desc_.clear();
	register_to_intput_element_desc_.reserve( reg_map.size());

	typedef pair<semantic_value, size_t> pair_t;
	for(auto const& sv_reg_pair: reg_map)
	{
		input_element_desc const* elem_desc = layout_->find_desc(sv_reg_pair.first);

		if(elem_desc == nullptr)
		{
			register_to_intput_element_desc_.clear();
			return;
		}

		register_to_intput_element_desc_.push_back(
			make_pair(sv_reg_pair.second, elem_desc) 
			);
	}
}

void const* stream_assembler::element_address(input_element_desc const& elem_desc, size_t vert_index) const
{
	auto buf_desc = stream_buffer_descs_ + elem_desc.input_slot;
	return buf_desc->buffer_->raw_data( buf_desc->stride_ * vert_index + buf_desc->offset_ );
}

void stream_assembler::fetch_vertex(vs_input& vertex, size_t vert_index) const
{
	for(auto const& reg_ied_pair: register_to_intput_element_desc_ )
	{
		auto reg_index	= reg_ied_pair.first;
		auto desc		= reg_ied_pair.second;

		void const* pdata = element_address(*desc, vert_index);
		vertex.attribute(reg_index) = get_vec4( desc->data_format, semantic_value(desc->semantic_name, desc->semantic_index), pdata);
	}
}

END_NS_LOPHURA()