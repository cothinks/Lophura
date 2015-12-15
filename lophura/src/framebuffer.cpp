#include "lophura/include/framebuffer.h"

BEGIN_NS_LOPHURA()

framebuffer::framebuffer()
{}

framebuffer::~framebuffer()
{}

void framebuffer::initialize(render_stages const* stages)
{}

void framebuffer::update(render_state const* state)
{
	color_target_	= state->color_target_.get();
	ds_target_		= state->depth_stencil_target_.get();
}

void framebuffer::render_sample(size_t x, size_t y, color_rgba_32f const& clr)
{
	color_target_->fill_texels(x, y, 1, 1, clr);
}

END_NS_LOPHURA()