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

struct vertex
{
	vec4 pos;
	color_rgba_32f color;
};

struct edge
{
	vertex v;
	vertex v1;
	vertex v2;
};

struct trapezoid
{
	float top,bottom;
	edge left,right;
};

struct scanline{ vertex v, step; int x, y, w; };

int trapezoid_init_triangle(trapezoid *trap, const vertex *p1, 
							const vertex *p2, const vertex *p3)
{
	const vertex *p;
	float k, x;

	if (p1->pos.y() > p2->pos.y()) p = p1, p1 = p2, p2 = p;
	if (p1->pos.y() > p3->pos.y()) p = p1, p1 = p3, p3 = p;
	if (p2->pos.y() > p3->pos.y()) p = p2, p2 = p3, p3 = p;
	if (p1->pos.y() == p2->pos.y() && p1->pos.y() == p3->pos.y()) return 0;
	if (p1->pos.x() == p2->pos.x() && p1->pos.x() == p3->pos.x()) return 0;

	if (p1->pos.y() == p2->pos.y()) {	// triangle down
		if (p1->pos.x() > p2->pos.x()) p = p1, p1 = p2, p2 = p;
		trap[0].top = p1->pos.y();
		trap[0].bottom = p3->pos.y();
		trap[0].left.v1 = *p1;
		trap[0].left.v2 = *p3;
		trap[0].right.v1 = *p2;
		trap[0].right.v2 = *p3;
		return (trap[0].top < trap[0].bottom)? 1 : 0;
	}

	if (p2->pos.y() == p3->pos.y()) {	// triangle up
		if (p2->pos.x() > p3->pos.x()) p = p2, p2 = p3, p3 = p;
		trap[0].top = p1->pos.y();
		trap[0].bottom = p3->pos.y();
		trap[0].left.v1 = *p1;
		trap[0].left.v2 = *p2;
		trap[0].right.v1 = *p1;
		trap[0].right.v2 = *p3;
		return (trap[0].top < trap[0].bottom)? 1 : 0;
	}

	trap[0].top = p1->pos.y();
	trap[0].bottom = p2->pos.y();
	trap[1].top = p2->pos.y();
	trap[1].bottom = p3->pos.y();

	k = (p3->pos.y() - p1->pos.y()) / (p2->pos.y() - p1->pos.y());
	x = p1->pos.x() + (p2->pos.x() - p1->pos.x()) * k;

	if (x <= p3->pos.x()) {		// triangle left
		trap[0].left.v1 = *p1;
		trap[0].left.v2 = *p2;
		trap[0].right.v1 = *p1;
		trap[0].right.v2 = *p3;
		trap[1].left.v1 = *p2;
		trap[1].left.v2 = *p3;
		trap[1].right.v1 = *p1;
		trap[1].right.v2 = *p3;
	}	else {					// triangle right
		trap[0].left.v1 = *p1;
		trap[0].left.v2 = *p3;
		trap[0].right.v1 = *p1;
		trap[0].right.v2 = *p2;
		trap[1].left.v1 = *p1;
		trap[1].left.v2 = *p3;
		trap[1].right.v1 = *p2;
		trap[1].right.v2 = *p3;
	}

	return 2;
}

float interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }
void vector_interp(vec4 *z, const vec4 *x1, const vec4 *x2, float t) {
	(*z)[0] = interp(x1->x(), x2->x(), t);
	(*z)[1] = interp(x1->y(), x2->y(), t);
	(*z)[2] = interp(x1->z(), x2->z(), t);
	(*z)[3] = interp(x1->w(), x2->w(), t);
}

void vertex_interp(vertex *y, const vertex *x1, const vertex *x2, float t) {
	vector_interp(&(y->pos), &(x1->pos), &(x2->pos), t);

	y->color.r = interp(x1->color.r,x2->color.r,t);
	y->color.g = interp(x1->color.g,x2->color.g,t);
	y->color.b = interp(x1->color.b,x2->color.b,t);
	y->color.a = interp(x1->color.a,x2->color.a,t);
}
void vertex_division(vertex *y, const vertex *x1, const vertex *x2, float w) {
	float inv = 1.0f / w;
	y->pos[0] = (x2->pos.x() - x1->pos.x()) * inv;
	y->pos[1] = (x2->pos.y() - x1->pos.y()) * inv;
	y->pos[2] = (x2->pos.z() - x1->pos.z()) * inv;
	y->pos[3] = (x2->pos.w() - x1->pos.w()) * inv;

	y->color.r = (x2->color.r - x1->color.r) * inv;
	y->color.g = (x2->color.g - x1->color.g) * inv;
	y->color.b = (x2->color.b - x1->color.b) * inv;
	y->color.a = (x2->color.a - x1->color.a) * inv;
}
void trapezoid_init_scan_line(const trapezoid *trap, scanline *scanline, int y) {
	float width = trap->right.v.pos.x() - trap->left.v.pos.x();
	scanline->x = (int)(trap->left.v.pos.x() + 0.5f);
	scanline->w = (int)(trap->right.v.pos.x() + 0.5f) - scanline->x;
	scanline->y = y;
	scanline->v = trap->left.v;
	if (trap->left.v.pos.x() >= trap->right.v.pos.x()) scanline->w = 0;
	vertex_division(&scanline->step, &trap->left.v, &trap->right.v, width);
}

void trapezoid_edge_interp(trapezoid *trap, float y)
{
	float s1 = trap->left.v2.pos.y() - trap->left.v1.pos.y();
	float s2 = trap->right.v2.pos.y() - trap->right.v1.pos.y();
	float t1 = (y - trap->left.v1.pos.y()) / s1;
	float t2 = (y - trap->right.v1.pos.y()) / s2;
	vertex_interp(&trap->left.v, &trap->left.v1, &trap->left.v2, t1);
	vertex_interp(&trap->right.v, &trap->right.v1, &trap->right.v2, t2);
}

void vertex_add(vertex *y, const vertex *x) {
	y->pos[0] += x->pos.x();
	y->pos[1] += x->pos.y();
	y->pos[2] += x->pos.z();
	y->pos[3] += x->pos.w();

	y->color.r += x->color.r;
	y->color.g += x->color.g;
	y->color.b += x->color.b;
	y->color.a += x->color.a;
}

void rasterizer::rasterize_solid_triangle(rasterize_prim_context const* ctxt)
{
	vs_output*	vso = ctxt->vso_;
	cpp_pixel_shader* ps = ctxt->shaders.cpp_ps;

	vec4*	pos1 = &vso[0].position();
	vec4*	pos2 = &vso[1].position();
	vec4*	pos3 = &vso[2].position();

	color_rgba_32f color3[3] = { color_rgba_32f(),color_rgba_32f(),color_rgba_32f()};

	if ( ps )
	{
		for (int i = 0;i < 3;++i)
		{
			ps_output out;
			ps->execute(vso[i],out);
			color3[i] = color_rgba_32f(out.color.x(),out.color.y(),out.color.z(),out.color.w());
		}
	}

	vertex v1,v2,v3;
	v1.pos = *pos1;v1.color = color3[0];
	v2.pos = *pos2;v2.color = color3[1];
	v3.pos = *pos3;v3.color = color3[2];

	trapezoid trap[2];
	int n = trapezoid_init_triangle(trap,&v1,&v2,&v3);

	if (n >= 1)
	{
		scanline sl;
		int j, top, bottom;
		top = (int)(trap[0].top + 0.5f);
		bottom = (int)(trap[0].bottom + 0.5f);
		for (j = top; j < bottom; j++) {
			if (j >= 0 && j < 600) {
				trapezoid_edge_interp(&(trap[0]), (float)j + 0.5f);
				trapezoid_init_scan_line(&(trap[0]), &sl, j);
				int x = sl.x;
				int w = sl.w;
				int width = 800;
				for (; w > 0; x++, w--) {
					if (x >= 0 && x < width) {
						float depth = sl.v.pos.w();
						color_rgba_32f color = sl.v.color;
						frame_buffer_->render_sample(x,j,depth,color);
					}
				vertex_add(&(sl.v), &(sl.step));
				if (x >= width) break;
				}
			}
			if (j >= 600) break;
		}
	}
	if (n >= 2)
	{
		scanline sl;
		int j, top, bottom;
		top = (int)(trap[1].top + 0.5f);
		bottom = (int)(trap[1].bottom + 0.5f);
		for (j = top; j < bottom; j++) {
			if (j >= 0 && j < 600) {
				trapezoid_edge_interp(&(trap[1]), (float)j + 0.5f);
				trapezoid_init_scan_line(&(trap[1]), &sl, j);
				int x = sl.x;
				int w = sl.w;
				int width = 800;
				for (; w > 0; x++, w--) {
					if (x >= 0 && x < width) {
						float depth = sl.v.pos.w();
						color_rgba_32f color = sl.v.color;
						frame_buffer_->render_sample(x,j,depth,color);
					}
					vertex_add(&(sl.v), &(sl.step));
					if (x >= width) break;
				}
			}
			if (j >= 600) break;
		}
	}
}

END_NS_LOPHURA()