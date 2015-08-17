#include "PipeLine.h"

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/math.h"

using namespace lophura_base;

LOPHURA_BEGIN

void ViewportTransform(vec4& position, const ViewPort& vp)
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

class Raster
{
public:
	static void DrawLine(BufferPtr frame_buffer,vec2& pos1,vec2& pos2,COLORRGBA32F color)
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
				frame_buffer->SetPos(x,y,color);
			}
		}
	}

	static void DrawTrangle(BufferPtr frame_buffer,vec4** data,COLORRGBA32F color)
	{
		vec4* pos1 = data[0];
		vec4* pos2 = data[1];
		vec4* pos3 = data[2];

		//pos1-->pos2
		vec2 v1 = pos1->xy();
		vec2 v2 = pos2->xy();
		DrawLine(frame_buffer,v1,v2,color);
		//pos2-->pos3
		v1 = pos2->xy();
		v2 = pos3->xy();
		DrawLine(frame_buffer,v1,v2,color);
		//pos3-->pos1
		v1 = pos3->xy();
		v2 = pos1->xy();
		DrawLine(frame_buffer,v1,v2,color);
	}
};

PipeLine::PipeLine(void):transformed_verts_(800*600)
{}


PipeLine::~PipeLine(void)
{}

void PipeLine::Lanche( RenderStatePtr state )
{
	state_ = state;

	Prepare();

	Draw();
}

void PipeLine::Prepare()
{
	BufferPtr vertex_buffer = state_->vertex_buffer_;
	Matrix44  wvp			= state_->wrold_view_proj_;

	transformed_verts_	= *vertex_buffer;

	vec4*	vertx		= reinterpret_cast<vec4*>(transformed_verts_.RawData(0));
	size_t	vert_count	= vertex_buffer->Size() / sizeof(vec4);

	for (size_t i = 0;i < vert_count; ++i)
	{
		Transform(vertx[i],vertx[i],wvp);
	}

	ViewPort const& vp = state_->view_port_;
	for (size_t i = 0;i < vert_count; ++i)
	{
		ViewportTransform(vertx[i],vp);
	}
}

void PipeLine::Draw()
{
	BufferPtr color_target	= state_->color_target_;
	BufferPtr vertex_buffer = state_->vertex_buffer_;
	BufferPtr index_buffer  = state_->index_buffer_;

	vec4*	vertx		= reinterpret_cast<vec4*>(transformed_verts_.RawData(0));
	size_t	vert_count	=  vertex_buffer->Size() / sizeof(vec4);

	assert(IF_16 == state_->index_format_);

	uint16_t* idis = reinterpret_cast<uint16_t*>(state_->index_buffer_->RawData(0));
	size_t	index_count	= state_->index_buffer_->Size() / sizeof(uint16_t);

	COLORRGBA32F color(0.0f,1.0f,0.0f,1.0f);

	for (size_t i = 0;i < index_count; i += 3)
	{
		vec4* trangles[] = { &vertx[idis[i]],&vertx[idis[i+1]],&vertx[idis[i+2]] };
		Raster::DrawTrangle(color_target,trangles,color);
	}
}

LOPHURA_END