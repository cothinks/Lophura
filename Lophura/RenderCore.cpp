#include "RenderCore.h"
#include "PipeLine.h"
#include "PipeLineImple.h"

LOPHURA_BEGIN

RenderCore::RenderCore(void):pipe_line_(new PipeLineImple)
{
}


RenderCore::~RenderCore(void)
{
}

void RenderCore::Update( RenderStatePtr const& state )
{
	state_ = state;
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
		break;
	}
}

void RenderCore::ClearColor()
{
	state_->color_target_->FillColor(state_->clear_color_);
}

void RenderCore::Draw()
{
	pipe_line_->Lanche(state_);
}

LOPHURA_END