#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/render_stages.h"
#include "lophura/include/raster_state.h"
#include "lophura_base/include/math/vector.h"

#include <functional>

BEGIN_NS_LOPHURA()

struct rasterize_prim_context
{
	//std::vector<uint32_t> const*	sorted_prims;
	//viewport const*					tile_vp;
	lophura_base::vec4**	vertex_;
	color_rgba_32f	color_;
};

class rasterizer
{
public:
	void initialize(render_stages const* stages);
	void update(render_state const* state);
	void draw();

	void update_prim_info(render_state const* state);
	//void rasterize_multi_line(rasterize_multi_prim_context const*);
	void rasterize_line(const lophura_base::vec2& v1,const lophura_base::vec2& v2,
				color_rgba_32f clr);
	void rasterize_wireframe_triangle(rasterize_prim_context const*);
	void rasterize_solid_triangle(rasterize_prim_context const*);
private:
	raster_state*	rs_state_;

	data_addressing_ptr		addressing_;

	vs_output*		clipped_verts_;
	data_buffer*	frame_buffer_;
	viewport		vp_;
	size_t			prim_count_;

	prim_type		prim_;
	uint32_t		prim_size_;

	std::function< void (rasterizer*, rasterize_prim_context*)>
					rasterize_prims_;
};

END_NS_LOPHURA()