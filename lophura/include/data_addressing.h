#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/index_fetcher.h"
#include "lophura/include/shader.h"
#include "lophura/include/shader_regs.h"
#include "lophura/include/stream_assembler.h"

BEGIN_NS_LOPHURA()

struct render_stages;

class data_addressing
{
public:
	void initialize( render_stages const* stage);
	void update(render_state const* state);
	void fetch3(vs_output* v,size_t prim_id);
private:
	index_fetcher		index_fetcher_;
	cpp_vertex_shader*	cpp_vs_;
	stream_assembler*	assembler_;
};

END_NS_LOPHURA()