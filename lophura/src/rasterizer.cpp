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



bool get_interp_info( const vec2& vp, vec4** vt, float& u, float& v)
{
	float a1 = vt[1]->x() - vt[0]->x();
	float b1 = vt[2]->x() - vt[0]->x();
	float c1 = vp.x() - vt[0]->x();

	float a2 = vt[1]->y() - vt[0]->y();
	float b2 = vt[2]->y() - vt[0]->y();
	float c2 = vp.y() - vt[0]->y();

	u = ( b2*c1 - b1*c2 ) / ( -a2*b1 + a1*b2);
	v = ( a2*c1 - a1*c2 ) / ( a2*b1 - a1*b2);

	return true;
}

color_rgba_32f gen_interp_val( const vec2& vp, vec4** vt, color_rgba_32f* colors)
{
	float u,v;
	get_interp_info( vp,vt,u,v);

	return colors[0]*(1-u-v) + colors[1]*u 
			+ colors[2]*v;
}

float gen_interp_z_val( const vec2& vp, vec4** vt )
{
	float u,v;
	get_interp_info( vp,vt,u,v);

	return vt[0]->z()*(1-u-v) + vt[1]->z()*u 
		+ vt[2]->z()*v;
}

float get_edeg(vec2 v1, vec2 v2)
{
	float edeg = (v2.x() - v1.x())*(v2.x() - v1.x()) + (v2.y() - v1.y())*(v2.y() - v1.y());
	 edeg = sqrt(edeg);

	if (edeg <= 0)
	{
		//void(0);
		return 1;
	}

	return edeg;
}

float get_area(vec2 v1,vec2 v2,vec2 v3)
{
	float edge[3];

	edge[0] = get_edeg(v1,v2);
	edge[1] = get_edeg(v2,v3);
	edge[2] = get_edeg(v3,v1);

	assert(edge[0] > 0 && edge[1] > 0 && edge[2] > 0);

	float s = 1.0f / 2 * (edge[0] + edge[1] + edge[2]);

	float area = s*(s - edge[0])*(s - edge[1])*(s - edge[2]);
	return sqrt(area);

}

vec3 get_trangle_weight(const vec2& vp, vec4** vt)
{
	vec4* A = vt[0];
	vec4* B = vt[1];
	vec4* C = vt[2];

	float T1 = get_area(vp,B->xy(),C->xy());
	float T2 = get_area(vp,A->xy(),C->xy());
	float T3 = get_area(vp,A->xy(),B->xy());

	float T = get_area(A->xy(),B->xy(),C->xy());

	return vec3(T1/T,T2/T,T3/T);
}

void rasterizer::initialize(render_stages const* stages)
{
	frame_buffer_	= stages->backend.get();
	addressing_		= stages->data_address_;
}

void rasterizer::update(render_state const* state)
{
	rs_state_		= state->ras_state_.get();
	vp_				= state->view_port_;
	prim_count_		= state->primitive_count_;

	ps_				= state->cpp_ps_;

	update_prim_info(state);
	frame_buffer_->update(state);
}

void rasterizer::draw()
{
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

		for (auto& v : vo){
			viewport_transform(v.position(),vp);
		}

		rasterize_prim_context rs_ctxt;
		rs_ctxt.vso_ = vo;
		rs_ctxt.shaders.cpp_ps = ps_.get();

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
			//frame_buffer_->set_pos(x,y,clr);
		}
	}
}

void rasterizer::rasterize_wireframe_triangle(rasterize_prim_context const* ctxt)
{
	assert(false && "unimplemented!");
	return;
}


int get_critical_edge(vec4** vertex, float y, std::vector<size_t>& inter_edge)
{
	//3edge
	size_t edge[3][2] = { { 0, 1 }
						, { 1, 2 }
						, { 2, 0 } };
	//height filter
	inter_edge.clear();
	
	for (size_t i = 0; i < 3; i++)
	{
		vec4* vpos1 = vertex[edge[i][0]];
		vec4* vpos2 = vertex[edge[i][1]];

		float min_y, max_y;
		min_y = std::min(vpos1->y(),vpos2->y());
		max_y = std::max(vpos1->y(),vpos2->y());//vpos1->y() + vpos2-

		//matched
		if (min_y <= y && y <= max_y)
		{
			inter_edge.push_back(i);
		}
	}

	//assert(inter_edge.size() <= 2);

	return inter_edge.size();
}

void lerp(vec4** vertex, float y, const color_rgba_32f* vertex_color, vs_output* out_vertex)
{
	std::vector<size_t> edges;
	int edge_count = get_critical_edge(vertex, y, edges);

	//3edge
	size_t edge[3][2] = { { 0, 1 }
						, { 1, 2 }
						, { 2, 0 } };

	int counter = 0;
	for (size_t i = 0; i < edges.size(); i++)
	{
		size_t edge_index = edges[i];

		vec4* vpos1 = vertex[edge[edge_index][0]];
		vec4* vpos2 = vertex[edge[edge_index][1]];

		float t = ( y - vpos1->y() ) / ( vpos2->y() - vpos1->y() );
		vec4 vpos = *vpos1 + (*vpos2 - *vpos1)*t;

		color_rgba_32f color1 = vertex_color[edge[edge_index][0]];
		color_rgba_32f color2 = vertex_color[edge[edge_index][1]];
		color_rgba_32f color = color1 + (color2 - color1)*t;

		bool repeated = false;
		for (size_t j = 0; j < 2; ++j)
		{
			if (vpos == out_vertex[j].position())
			{
				repeated = true;
			}
		}

		if (repeated)
		{
			continue;
		}

		out_vertex[counter].position() = vpos;
		out_vertex[counter++].attribute(1) = vec4(color.r, color.g, color.b, color.a);
	}
}

void rasterizer::rasterize_solid_triangle(rasterize_prim_context const* ctxt)
{
	vs_output*	vso = ctxt->vso_;
	//color_rgba_32f color = ctxt->color_;
	cpp_pixel_shader* ps = ctxt->shaders.cpp_ps;

	vec4*	pos1 = &vso[0].position();
	vec4*	pos2 = &vso[1].position();
	vec4*	pos3 = &vso[2].position();

	color_rgba_32f color3[3] = { color_rgba_32f(),color_rgba_32f(),color_rgba_32f()};

	if ( ps )
	{
		for (int i = 0;i < 3;++i)
		{
			vs_output& in = vso[i];
			//in.position() = *data[i];

			ps_output out;
			ps->execute(in,out);
			color3[i] = color_rgba_32f(out.color.x(),out.color.y(),out.color.z(),out.color.w());
		}
	}

	//edge function E(x,y) = ( x - X )* dx - ( y - Y)*dy
	struct equation_param{
		float X,Y,dx,dy;
	};
	equation_param edge_equation[3];

	//1-2
	edge_equation[0].X	= pos1->x();
	edge_equation[0].Y	= pos1->y();
	edge_equation[0].dx	= pos2->x() - pos1->x();
	edge_equation[0].dy = pos2->y() - pos1->y();
	//2-3
	edge_equation[1].X	= pos2->x();
	edge_equation[1].Y	= pos2->y();
	edge_equation[1].dx	= pos3->x() - pos2->x();
	edge_equation[1].dy = pos3->y() - pos2->y();
	//3-1
	edge_equation[2].X	= pos3->x();
	edge_equation[2].Y	= pos3->y();
	edge_equation[2].dx	= pos1->x() - pos3->x();
	edge_equation[2].dy = pos1->y() - pos3->y();

	vec4* data[3] = { &vso[0].position(), &vso[1].position(), &vso[2].position() };

	for (float y = 0; y < 600; ++y)
	{
		vs_output out[2];
		lerp(data,y,color3,out);
		for (float x = 0; x < 800; ++x)
		{
			if (((x - edge_equation[0].X) * edge_equation[0].dy - (y - edge_equation[0].Y)*edge_equation[0].dx) >= 0 &&
				((x - edge_equation[1].X) * edge_equation[1].dy - (y - edge_equation[1].Y)*edge_equation[1].dx) >= 0 &&
				((x - edge_equation[2].X) * edge_equation[2].dy - (y - edge_equation[2].Y)*edge_equation[2].dx) >= 0)
			{
				
				float t = ( x - out[0].position().x() ) / ( out[1].position().x() - out[0].position().x() );

				color_rgba_32f color1 = color_rgba_32f(out[0].attribute(1)[0],out[0].attribute(1)[1],out[0].attribute(1)[2],out[0].attribute(1)[3]);
				color_rgba_32f color2 = color_rgba_32f(out[1].attribute(1)[0],out[1].attribute(1)[1],out[1].attribute(1)[2],out[1].attribute(1)[3]);
				color_rgba_32f color = color1 + (color2 - color1)*t;

				float depth1 = out[0].position().w();
				float depth2 = out[1].position().w();
				float depth = depth1 + (depth2 - depth1)* t;

				frame_buffer_->render_sample(x,y,depth,color);
			}

		}
	}
}

END_NS_LOPHURA()