#include "lophura/include/pipeline.h"

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/math.h"

#include "lophura/include/viewport.h"
#include "lophura/include/render_state/render_state.h"

using namespace lophura_base;

BEGIN_NS_LOPHURA()

void viewport_transform(vec4& position, const viewport& vp)
{

	float invw = ( position[3] == 0.0f) ? 1.0f : 1.0f / position[3];
	vec4 pos = position * invw;

	float ox = (vp.x + vp.w) * 0.5f;
	float oy = (vp.y + vp.h) * 0.5f;

	position[0] = (float(vp.w) * 0.5f) *  pos.x() + ox;
	position[1] = (float(vp.h) * 0.5f) * -pos.y() + oy;
	position[2] = (vp.maxz - vp.minz) * pos.z() + vp.minz;
	position[3] = invw;
}

pipeline::pipeline(void)
{}


pipeline::~pipeline(void)
{}

void pipeline::lanche( render_state_ptr state )
{
	state_ = state;

	prepare();

	draw();
}

void pipeline::prepare()
{
	
}

void pipeline::draw()
{
	data_buffer_ptr color_target	= state_->color_target_;

	size_t prim_count  = state_->primitive_count_;
	viewport const& vp = state_->view_port_;

	for (size_t prim_id = 0; prim_id < prim_count; ++prim_id)
	{
		vs_output vo[3];
		addressing_->fetch3( vo, prim_id);

		color_rgba_32f color(0.0f,1.0f,0.0f,1.0f);

		vec4* trangles[] = { &(vo[0].position()), &(vo[1].position()), &(vo[2].position())};

		for (auto const& pos : trangles)
		{
			viewport_transform(*pos,vp);
		}

		raster::draw_trangle(color_target,trangles,color);
	}
}

void pipeline::initialize( render_stages const* stages )
{
	addressing_ = stages->data_address_;
}

END_NS_LOPHURA()