#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/matrix.h"
#include "lophura_base/include/math/math.h"

#include "lophura/include/lophura_declaration.h"
#include "lophura/include/format.h"
#include "lophura/include/render.h"
#include "lophura/include/mesh.h"
#include "lophura/include/swap_chain.h"
#include "lophura/include/shader.h"
#include "lophura/include/raster_state.h"

#include "samples/sample_app/include/window/window.h"
#include "samples/sample_app/include/window/native_window.h"

#include <tchar.h>
#include <chrono>
#include <windows.h>

using namespace lophura_base;
using namespace lophura;
using namespace sample_app;
using namespace std::chrono;

class vs : public cpp_vertex_shader
{
	matrix44 wvp;
	vec4 light0,light1,light2;
public:
	vs():wvp(matrix44::identity()){
		declare_constant(_T("WorldViewProjMat"), wvp);
		
		bind_semantic( "POSITION", 0, 0 );
	}

	vs(const matrix44& wvp):wvp(wvp){}
	void shader_prog(const vs_input& in, vs_output& out)
	{
		vec4 pos = in.attribute(0);
		transform(out.position(), pos, wvp);
	}

	uint32_t num_output_attributes() const
	{
		return 2;
	}

	uint32_t output_attribute_modifiers(uint32_t index) const
	{
		switch (index)
		{
		case 0:
			return vs_output::am_linear;

		case 1:
			return vs_output::am_linear;

		case 2:
			return vs_output::am_linear;

		default:
			return vs_output::am_linear;
		}
	}

	virtual cpp_shader_ptr clone()
	{
		typedef std::remove_pointer<decltype(this)>::type this_type;
		return cpp_shader_ptr(new this_type(*this));
	}
};

class ps : public cpp_pixel_shader
{
public:
	vec4 color;
	ps()
	{
		declare_constant(_T("Color"),   color );
	}
	void shader_prog(const vs_output& in, ps_output& out)
	{
		out.color = color;
	}

	virtual cpp_shader_ptr clone()
	{
		typedef std::remove_pointer<decltype(this)>::type this_type;
		return cpp_shader_ptr(new this_type(*this));
	}
};

class test_window : public window
{
public:

	virtual bool	on_create()	override
	{
		native_window_->set_title(_T("trangles"));

		uint64_t data;
		native_window_->get_any_data(data);

		swap_chain_parameter	swap_chain_param;
		swap_chain_param.width = 800;
		swap_chain_param.height = 600;
		swap_chain_param.color_fmt = fmt_r32g32b32a32_unit;
		swap_chain_param.any_data = uint64_t(::GetDC((HWND)data));

		lophura_create_swap_chain(swap_chain_,swap_chain_param);

		lophura_create_render(render_,lophura::render_syn);
		surface_ptr color_buffer	= swap_chain_->get_surface();
		surface_ptr ds_buffer = render_->create_tex2d(800, 600, 1, fmt_r32g32b32a32_unit);

		render_->set_render_target(color_buffer,ds_buffer);

		raster_desc rs_desc;
		rs_desc.fm = fill_solid;
		rs_desc.cm = cull_none;
		rs_back_.reset(new raster_state(rs_desc));
		render_->set_rasterizer_state(rs_back_);

		viewport	vp;
		vp.w = 800;
		vp.h = 600;
		vp.x = 0;
		vp.y = 0;
		vp.minz = 0;
		vp.maxz = 1;

		render_->set_viewport(vp);
		box_ = creat_box(render_);

		camera_angle = 0;
		fps_count = 0;

		pvs_.reset( new vs());
		pps_.reset( new ps());

		return true;
	}

	virtual void	on_draw()	override
	{
		swap_chain_->present();
	}

	virtual void	on_idle()	override
	{
		time_now_ = system_clock::now();
		int s = duration_cast<std::chrono::seconds>(time_now_ - time_last_).count();
		if ( s > 1 ){
			printf("fps:%d\n",fps_count);
			time_last_ = time_now_;
			fps_count = 0;
		}

		fps_count++;
		camera_angle += 0.03f;

		render_->set_cpp_vertex_shader(pvs_);
		render_->set_cpp_pixel_shader(pps_);

		render_->clear_color(color_rgba_32f(0.1f,0.1f,0.0f,1.0f));

		vec3 camera(cos(camera_angle) * 2.3f, 2.5f, sin(camera_angle) * 2.3f);
		matrix44 moudle,world,view,proj,wvp;

		world  = matrix44::identity();
		moudle = matrix44::identity();

		matrix_mul(world,moudle,world);
		matrix_lookat(view,camera,vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,1.0f));
		matrix_perspective_fov(proj,static_cast<float>(HALF_PI),1.0f,0.1f,1000.0f);

		vec4 lightPos0( sin(-camera_angle * 1.5f) * 2.2f, 0.15f, cos( camera_angle * 0.9f) * 1.8f, 0.0f );
		vec4 lightPos1( sin( camera_angle * 0.7f) * 1.9f, 0.15f, cos(-camera_angle * 0.4f) * 2.5f, 0.0f );
		vec4 lightPos2( sin( camera_angle * 2.6f) * 2.3f, 0.15f, cos( camera_angle * 0.6f) * 1.7f, 0.0f );

		matrix_mul(wvp,world,matrix_mul(wvp,view,proj));
		pvs_->set_constant(_T("WorldViewProjMat"),&wvp);
		pvs_->set_constant(_T("Light0"),&lightPos0);
		pvs_->set_constant(_T("Light1"),&lightPos1);
		pvs_->set_constant(_T("Light2"),&lightPos2);

		vec4 color( 0.0f, 1.0f, 0.0f, 1.0f );
		pps_->set_constant( _T("Color"), &color);

		box_->render();
		swap_chain_->present();
	}
private:
	render_ptr					render_;
	swap_chain_ptr				swap_chain_;

	float						camera_angle;
	mesh_ptr					box_;
	raster_state_ptr			rs_back_;

	cpp_vertex_shader_ptr		pvs_;
	cpp_pixel_shader_ptr		pps_;

	int							fps_count;
	system_clock::time_point	time_last_;
	system_clock::time_point	time_now_;
};

int _tmain( int /*argc*/, TCHAR* /*argv*/[] ){
	test_window window;
	window.create_window(800,600);

	window.run_app();

	return 0;
}