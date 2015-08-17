#include "RenderCore.h"
#include "PipeLine.h"

LOPHURA_BEGIN

RenderCore::RenderCore(void)
{}


RenderCore::~RenderCore(void)
{}

void RenderCore::ProcessRenderRequest(RenderStatePtr const& state)
{
	state_ = state;

	Execute();
}

void RenderCore::Execute()
{
	switch (state_->command_)
	{
	case CommandId::clear_color:
			ClearColor();
		break;
	case CommandId::draw_index:
			Draw();
		break;
	default:
			assert( false && "unknown command !");
		break;
	}
}

void RenderCore::ClearColor()
{
	state_->color_target_->FillColor(state_->clear_color_);
}

void RenderCore::Draw()
{
	pipe_line_.Lanche(state_);
}

LOPHURA_END