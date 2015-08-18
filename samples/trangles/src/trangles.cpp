#include <tchar.h>

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/matrix.h"
#include "lophura_base/include/math/math.h"

#include "lophura/include/lophura_declaration.h"
#include "lophura/include/Render.h"
#include "lophura/include/Mesh.h"
#include "lophura/include/swap_chain.h"

#include "samples/sample_app/include/Window.h"

#include <chrono>

using namespace lophura_base;
using namespace lophura;
using namespace sample_app;
using namespace std::chrono;

extern SDL_Surface* g_sdl_surface;

int fps_count  = 0;

class TestWindow : public Window
{
public:
	virtual bool	OnCreate(SDL_Surface* surface)	override
	{
		lophura_create_swap_chain(swap_chain_);

		swap_chain_->set_sdl_surface(surface);

		lophura_create_render(render_,lophura::render_syn);

		data_buffer_ptr color_buffer	= swap_chain_->GetBuffer();
		data_buffer_ptr ds_buffer		= render_->create_buffer(800*600*4);

		render_->set_render_target(color_buffer,ds_buffer);

		viewport	vp;
		vp.w = 800;
		vp.h = 600;
		vp.x = 0;
		vp.y = 0;
		vp.minz = 0;
		vp.maxz = 1;

		rotate_y_ = 0;

		render_->set_viewport(vp);

		box_ = creat_box(render_);

		return true;
	}
	virtual void	OnDraw()	override
	{
		swap_chain_->Present();
	}
	virtual void	OnIdle()	override
	{
		

		time_now_ = system_clock::now();

		int s = duration_cast<std::chrono::seconds>(time_now_ - time_last_).count();

		if ( s > 1 )
		{

			printf("fps:%d\n",fps_count);
			time_last_ = time_now_;
			fps_count = 0;
		}

		fps_count++;
		//printf("fps:%d\n",fps_count);

		render_->clear_color(color_rgba_32f(0.1f,0.1f,0.0f,1.0f));
		vec3 camera(80.0f,80.0f,80.0f);
		matrix44 moudle,world,view,proj,wvp;

		matrix_roty(moudle,rotate_y_);
		rotate_y_ += 0.3f;
		world  = matrix44::identity();

		matrix_scale(world,30.0f,30.0f,30.0f);
		matrix_mul(world,moudle,world);
		matrix_lookat(view,camera,vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,1.0f));
		matrix_perspective_fov(proj,static_cast<float>(HALF_PI),1.0f,0.1f,1000.0f);

		matrix_mul(wvp,world,matrix_mul(wvp,view,proj));
		render_->set_wvp_matrix(wvp);

		box_->render();
		swap_chain_->Present();
	}
private:
	render_ptr		render_;
	swap_chain_ptr	swap_chain_;

	float		rotate_y_;
	mesh_ptr		box_;

	system_clock::time_point	time_last_;
	system_clock::time_point	time_now_;
};

int _tmain( int /*argc*/, TCHAR* /*argv*/[] ){
	TestWindow window;
	window.RunApp();

	return 0;
}