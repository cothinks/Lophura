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

pipeline::pipeline(void):transformed_verts_(800*600)
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
	data_buffer_ptr vertex_buffer = state_->vertex_buffer_;
	matrix44  wvp			= state_->wrold_view_proj_;

	transformed_verts_	= *vertex_buffer;

	vec4*	vertx		= reinterpret_cast<vec4*>(transformed_verts_.raw_data(0));
	size_t	vert_count	= vertex_buffer->size() / sizeof(vec4);

	for (size_t i = 0;i < vert_count; ++i)
	{
		transform(vertx[i],vertx[i],wvp);
	}

	viewport const& vp = state_->view_port_;
	for (size_t i = 0;i < vert_count; ++i)
	{
		viewport_transform(vertx[i],vp);
	}
}

void pipeline::draw()
{
	data_buffer_ptr color_target	= state_->color_target_;
	data_buffer_ptr vertex_buffer = state_->vertex_buffer_;
	data_buffer_ptr index_buffer  = state_->index_buffer_;

	vec4*	vertx		= reinterpret_cast<vec4*>(transformed_verts_.raw_data(0));
	size_t	vert_count	=  vertex_buffer->size() / sizeof(vec4);

	assert(ifm_16 == state_->index_format_);

	uint16_t* idis = reinterpret_cast<uint16_t*>(state_->index_buffer_->raw_data(0));
	size_t	index_count	= state_->index_buffer_->size() / sizeof(uint16_t);

	color_rgba_32f color(0.0f,1.0f,0.0f,1.0f);

	for (size_t i = 0;i < index_count; i += 3)
	{
		vec4* trangles[] = { &vertx[idis[i]],&vertx[idis[i+1]],&vertx[idis[i+2]] };
		raster::draw_trangle(color_target,trangles,color);
	}
}

END_NS_LOPHURA()