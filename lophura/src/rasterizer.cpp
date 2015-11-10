#include "lophura/include/rasterizer.h"
#include "lophura_base/include/math/vector.h"

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

void rasterizer::initialize(render_stages const* stages)
{
	addressing_ = stages->data_address_;
}

void rasterizer::update(render_state const* state)
{
	rs_state_		= state->ras_state_.get();
	frame_buffer_	= state->color_target_.get();
	vp_				= state->view_port_;
	prim_count_		= state->primitive_count_;

	update_prim_info(state);
}

void rasterizer::draw()
{
	data_buffer* color_target= frame_buffer_;

	size_t prim_count	= prim_count_;
	viewport const& vp	= vp_;

	switch (prim_)
	{
	case lophura::pt_line:
	case lophura::pt_wireframe_tri:
		rasterize_prims_ = std::mem_fn(&rasterizer::rasterize_wireframe_triangle);
		break;
	case lophura::pt_solid_tri:
		rasterize_prims_ = std::mem_fn(&rasterizer::rasterize_solid_triangle);
		break;
	default:
		assert(false && "prim type is not correct.");
	}

	for (size_t prim_id = 0; prim_id < prim_count; ++prim_id){
		vs_output vo[3];
		addressing_->fetch3( vo, prim_id);

		color_rgba_32f color(0.0f,1.0f,0.0f,1.0f);
		vec4* trangles[] = { &(vo[0].position()), &(vo[1].position()), &(vo[2].position())};

		for (auto const& pos : trangles){
			viewport_transform(*pos,vp);
		}

		rasterize_prim_context rs_ctxt;
		rs_ctxt.vertex_ = trangles;
		rs_ctxt.color_	= color;

		rasterize_prims_(this,&rs_ctxt);
	}
}

void rasterizer::update_prim_info(render_state const* state)
{
	bool is_tri = false;
	bool is_line = false;
	bool is_point = false;

	bool is_wireframe = false;
	bool is_solid = false;

	prim_count_ = state->primitive_count_;

	switch (rs_state_->get_desc().fm)
	{
	case fill_solid:
		is_solid = true;
		break;
	case fill_wireframe:
		is_wireframe = true;
		break;
	}

	switch (state->primitive_topology_)
	{
	case primitive_topology::primitive_triangle_list:
		is_tri = true;
		break;
	}

	if (is_solid && is_tri)
	{
		prim_ = pt_solid_tri;
	}
	else if(is_wireframe && is_tri)
	{
		prim_ = pt_wireframe_tri;
	}
	else
	{
		prim_ = pt_none;
		assert(false && "unkown prim type.");
	}

	switch (prim_)
	{
	case lophura::pt_line:
	case lophura::pt_wireframe_tri:
		prim_size_ = 3;
		break;
	case lophura::pt_solid_tri:
		prim_size_ = 3;
		break;
	default:
		assert(false && "unkown prim type.");
	}
}

void rasterizer::rasterize_line(const vec2& v1,const vec2& v2, color_rgba_32f clr)
{
	float angle = 0.0f;

	vec2 start_pos,end_pos;

	if (v1.x() != v2.x()){
		start_pos = ( v1.x() < v2.x() ) ? v1 : v2;
		end_pos   = ( v1.x() > v2.x() ) ? v1 : v2;
	}else{
		start_pos = v1;
		end_pos	  = v2;
	}

	float delta_x,delta_y;

	delta_x = end_pos.x() - start_pos.x();
	delta_y = end_pos.y() - start_pos.y();

	if( fabs(delta_x) < 1.0f ){
		delta_x = delta_x >= 0 ? 1.0f : -1.0f;
	}

	if( fabs(delta_y) < 1.0f ){
		delta_y = delta_y >= 0 ? 1.0f : -1.0f;
	}

	angle = delta_y / delta_x;

	float delta = fabs(delta_x) > fabs(delta_y) ? 1.0f : ( delta_x / delta_y );
	delta = fabs(delta);

	for (float i = 0; i <= fabs(delta_x); i += delta){
		float x = start_pos.x() + i;
		float y = start_pos.y() + ( x - start_pos.x()) * angle;

		if( ( x >= 0 && x < 800 ) && ( y >= 0 && y < 600)){
			frame_buffer_->set_pos(x,y,clr);
		}
	}
}

void rasterizer::rasterize_wireframe_triangle(rasterize_prim_context const* ctxt)
{
	vec4**	data = ctxt->vertex_;
	color_rgba_32f color = ctxt->color_;

	vec4*	pos1 = data[0];
	vec4*	pos2 = data[1];
	vec4*	pos3 = data[2];

	rasterize_line(pos1->xy(),pos2->xy(),color);
	rasterize_line(pos2->xy(),pos3->xy(),color);
	rasterize_line(pos3->xy(),pos1->xy(),color);
}

void rasterizer::rasterize_solid_triangle(rasterize_prim_context const* ctxt)
{
	vec4**	data = ctxt->vertex_;
	color_rgba_32f color = ctxt->color_;

	vec4*	pos1 = data[0];
	vec4*	pos2 = data[1];
	vec4*	pos3 = data[2];

	struct equation_param{
		int k,b;
	};
	equation_param edge_equation[3];

	//1-2
	edge_equation[0].k = (pos2->y() - pos1->y()) / ( pos2->x() - pos1->x());
	edge_equation[0].b = pos1->y() - edge_equation[0].k * pos1->x();
	//2-3
	edge_equation[1].k = (pos3->y() - pos2->y()) / ( pos3->x() - pos2->x());
	edge_equation[1].b = pos2->y() - edge_equation[1].k * pos2->x();
	//3-1
	edge_equation[2].k = (pos1->y() - pos3->y()) / ( pos1->x() - pos3->x());
	edge_equation[2].b = pos3->y() - edge_equation[2].k * pos3->x();


	for (int x = 0; x < 800; ++x){
		for (int y = 0; y < 600; ++y){
			if ( ( y - edge_equation[0].k*x - edge_equation[0].b) >0 &&
				 ( y - edge_equation[1].k*x - edge_equation[1].b) >0 &&
				 ( y - edge_equation[2].k*x - edge_equation[2].b) >0
				)
			{
				frame_buffer_->set_pos(x,y,color);
			}
		}
	}
}

END_NS_LOPHURA()