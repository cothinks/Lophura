#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render_stages.h"
#include "lophura/include/raster_state.h"

BEGIN_NS_LOPHURA()

class rasterizer
{
public:
	void initialize	(render_stages const* stages);
	void update		(render_state const* state);

	void draw();
private:
	raster_state*	state_;
};

END_NS_LOPHURA()