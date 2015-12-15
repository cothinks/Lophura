#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render_stages.h"
#include "lophura/include/render_state/render_state.h"
#include "lophura/include/surface.h"

BEGIN_NS_LOPHURA()

class framebuffer
{
public:
	framebuffer();
	~framebuffer();

	void initialize(render_stages const* stages);
	void update(render_state const* state);

	bool early_z_enable() const { return early_z_enable_; }
	uint64_t early_z_test(size_t x, size_t y, float depth);

	void render_sample(size_t x,size_t y,color_rgba_32f const& clr);
private:
	bool		early_z_enable_;
	surface*	color_target_;
	surface*	ds_target_;
};

END_NS_LOPHURA()