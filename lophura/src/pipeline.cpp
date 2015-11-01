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

class raster
{
public:
	static void draw_line(data_buffer_ptr frame_buffer,vec2& pos1,vec2& pos2,color_rgba_32f color)
	{
		float angle = 0.0f;

		vec2 start_pos,end_pos;

		if (pos1.x() != pos2.x())
		{
			start_pos = ( pos1.x() < pos2.x() ) ? pos1 : pos2;
			end_pos   = ( pos1.x() > pos2.x() ) ? pos1 : pos2;
		}else
		{
			start_pos = pos1;
			end_pos		= pos2;
		}

		float delta_x,delta_y;

		delta_x = end_pos.x() - start_pos.x();
		delta_y = end_pos.y() - start_pos.y();

		if( fabs(delta_x) < 1.0f )
		{
			delta_x = delta_x >= 0 ? 1.0f : -1.0f;
		}

		if( fabs(delta_y) < 1.0f )
		{
			delta_y = delta_y >= 0 ? 1.0f : -1.0f;
		}

		angle = delta_y / delta_x;

		float delta = fabs(delta_x) > fabs(delta_y) ? 1.0f : ( delta_x / delta_y );
		delta = fabs(delta);

		for (float i = 0; i <= fabs(delta_x); i += delta)
		{
			float x = start_pos.x() + i;
			float y = start_pos.y() + ( x - start_pos.x()) * angle;

			if( ( x >= 0 && x < 800 ) && ( y >= 0 && y < 600))
			{
				frame_buffer->set_pos(x,y,color);
			}
		}
	}

	static void draw_trangle(data_buffer_ptr frame_buffer,vec4** data,color_rgba_32f color)
	{
		vec4* pos1 = data[0];
		vec4* pos2 = data[1];
		vec4* pos3 = data[2];

		//pos1-->pos2
		vec2 v1 = pos1->xy();
		vec2 v2 = pos2->xy();
		draw_line(frame_buffer,v1,v2,color);
		//pos2-->pos3
		v1 = pos2->xy();
		v2 = pos3->xy();
		draw_line(frame_buffer,v1,v2,color);
		//pos3-->pos1
		v1 = pos3->xy();
		v2 = pos1->xy();
		draw_line(frame_buffer,v1,v2,color);
	}
};

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