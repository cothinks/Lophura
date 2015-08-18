#include "lophura/include/syn_render.h"

BEGIN_NS_LOPHURA()

syn_render::syn_render(void)
{}

syn_render::~syn_render(void)
{}

void syn_render::commit_command()
{
	render_core_.process_render_request(state_);
}

END_NS_LOPHURA()