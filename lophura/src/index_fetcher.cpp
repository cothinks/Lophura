#include "lophura/include/index_fetcher.h"
#include <assert.h>

using namespace lophura;

void lophura::index_fetcher::update( render_state const* state )
{
	index_buffer_	= state->command_ == command_id::draw_index ? state->index_buffer_.get() : nullptr;
	index_format_	= state->index_format_;
	prim_topo_		= state->primitive_topology_;

	if (ifm_16 == index_format_){
		stride_ = 2;
	}
	else{
		assert(ifm_32 == index_format_ && "Index type is wrong.");
		stride_ = 4;
	}
	start_addr_ = state->start_index_ * stride_;
	base_vert_  = 0;
}

void lophura::index_fetcher::fetch_indexes( uint32_t* index_of_prim, uint32_t prim_id_beg, uint32_t prim_id_end )
{
	uint32_t* out_indexes = index_of_prim;
	uint32_t  prim_vert_count = 0;
	uint32_t const min_prim_id = prim_id_beg;
	uint32_t const max_prim_id = prim_id_end;

	switch (prim_topo_)
	{
	case primitive_topology::primitive_triangle_list:
		prim_vert_count = 3;
		break;
	default:
		assert(false && "unkown primitive type!");
		return;
	}

	for (uint32_t prim_id = prim_id_beg; prim_id < prim_id_end; ++prim_id){
		uint32_t ids[3];

		switch (prim_topo_)
		{
		case primitive_topology::primitive_triangle_list:
			ids[0] = prim_id*3 + 0;
			ids[1] = prim_id*3 + 1;
			ids[2] = prim_id*3 + 2;
			break;
		default:
			break;
		}

		if (index_buffer_){
			uint8_t* index_buffer_address = index_buffer_->raw_data(start_addr_);
			if (ifm_16 == index_format_){
				uint16_t* pidx = reinterpret_cast<uint16_t*>(index_buffer_address);
				for (uint32_t i = 0;i < prim_vert_count; ++i){
					out_indexes[i] = base_vert_ + pidx[ids[i]];
				}
			}else{
				assert(false && "index format is wrong!");
				uint32_t* pidx = reinterpret_cast<uint32_t*>(index_buffer_->raw_data(start_addr_));
				for (uint32_t i = 0;i < prim_vert_count; ++i){
					out_indexes[i] = base_vert_ + pidx[ids[i]];
				}
			}
		}else{
			for (uint32_t i = 0; i < prim_vert_count; ++ i){
				out_indexes[i] = ids[i] + base_vert_;
			}
		}
	}
}
