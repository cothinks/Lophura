#include "lophura/include/data_addressing.h"
#include "lophura/include/render_stages.h"

BEGIN_NS_LOPHURA()

void data_addressing::initialize(render_stages const* stage)
{
	assembler_ = stage->assembler_.get();
}

void data_addressing::update(render_state const* state)
{
	index_fetcher_.update(state);
	cpp_vs_ = state->cpp_vs_.get();
}

void data_addressing::fetch3(vs_output* v,size_t prim_id)
{
	uint32_t indexes[3];
	index_fetcher_.fetch_indexes(indexes, prim_id, prim_id+1);

	for (int i = 0; i < 3; i++)
	{
		uint32_t index = indexes[i];

		if (cpp_vs_)
		{
			vs_input vertex;
			assembler_->fetch_vertex(vertex,index);

			if (&v[i])
			{
				cpp_vs_->execute(vertex,v[i]);
			}
		}
	}
}

END_NS_LOPHURA()
