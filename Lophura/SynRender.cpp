#include "SynRender.h"

LOPHURA_BEGIN

SynRender::SynRender(void)
{
}


SynRender::~SynRender(void)
{
}

void SynRender::CommitCommand()
{
	render_core_.ProcessRenderRequest(state_);
}

LOPHURA_END