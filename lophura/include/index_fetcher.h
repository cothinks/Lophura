#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render_state/render_state.h"
#include "lophura/include/data_buffer.h"
#include "lophura/include/format.h"

BEGIN_NS_LOPHURA()

class index_fetcher
{
public:
	void update(render_state const* state);
	void fetch_indexes(uint32_t* index_of_prim, uint32_t prim_id_beg,
		uint32_t prim_id_end);
private:
	data_buffer*		index_buffer_;
	index_format		index_format_;
	primitive_topology	prim_topo_;
	uint32_t			start_addr_;
	uint32_t			base_vert_;
	uint32_t			stride_;
};

END_NS_LOPHURA()