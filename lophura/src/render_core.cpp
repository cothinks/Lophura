#include "lophura/include/render_core.h"
#include "lophura/include/render_state/render_state.h"
#include "lophura/include/rasterizer.h"
#include "lophura/include/framebuffer.h"

BEGIN_NS_LOPHURA()

render_core::render_core(void)
{
	stages_.assembler_		.reset( new stream_assembler());
	stages_.data_address_	.reset( new data_addressing());
	stages_.ras_			.reset( new rasterizer());
	stages_.backend			.reset(	new framebuffer());

	stages_.data_address_->initialize(&stages_);
	stages_.ras_->initialize(&stages_);
}

render_core::~render_core(void)
{} 

void render_core::process_render_request(render_state_ptr const& state)
{
	state_ = state;
	execute();
}

void render_core::execute()
{
	switch (state_->command_)
	{
	case command_id::clear_color:
			clear_color();
		break;
	case command_id::draw_index:
			draw();
		break;
	default:
			assert( false && "unknown command !");
		break;
	}
}

void render_core::clear_color()
{
	state_->color_target_->fill_texels(state_->clear_color_);
}

void render_core::draw()
{
	stages_.data_address_->update(state_.get());
	stages_.assembler_->update(state_.get());
	stages_.ras_->update(state_.get());

	stages_.ras_->draw();
}

END_NS_LOPHURA()