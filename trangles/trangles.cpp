#include <tchar.h>

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/matrix.h"
#include "lophura_base/include/math/math.h"

#include "lophura/render.h"
#include "lophura/mesh.h"

#include "sample_app/window.h"

#include <chrono>

using namespace lophura_base;
using namespace Lophura;
using namespace sample_app;
using namespace std::chrono;

extern SDL_Surface* g_sdl_surface;

int fps_count  = 0;

class TestWindow : public Window
{
public:
	virtual bool	OnCreate(SDL_Surface* surface)	override
	{
		LophuraCreateSwapchain(swap_chain_);

		swap_chain_->set_sdl_surface(surface);

		LophuraCreateRender(render_,Lophura::RenderAsyn);

		BufferPtr color_buffer	= swap_chain_->GetBuffer();
		BufferPtr ds_buffer		= render_->CreateBuffer(800*600*4);

		render_->SetRenderTarget(color_buffer,ds_buffer);

		ViewPort	vp;
		vp.w = 800;
		vp.h = 600;
		vp.x = 0;
		vp.y = 0;
		vp.minz = 0;
		vp.maxz = 1;

		rotate_y_ = 0;

		render_->SetViewPort(vp);

		box_ = CreatBox(render_);

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

		render_->ClearColor(COLORRGBA32F(0.1f,0.1f,0.0f,1.0f));
		vec3 camera(80.0f,80.0f,80.0f);
		Matrix44 moudle,world,view,proj,wvp;

		MatrixRotY(moudle,rotate_y_);
		rotate_y_ += 0.3f;
		world  = Matrix44::Identity();

		MatrixScale(world,30.0f,30.0f,30.0f);
		MatrixMul(world,moudle,world);
		MatrixLookAt(view,camera,vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,1.0f));
		MatrixPerspectiveFov(proj,static_cast<float>(HALF_PI),1.0f,0.1f,1000.0f);

		MatrixMul(wvp,world,MatrixMul(wvp,view,proj));
		render_->SetWVPMatrix(wvp);

		box_->Render();
		swap_chain_->Present();
	}
private:
	RenderPtr		render_;
	SwapChainPtr	swap_chain_;

	float		rotate_y_;
	MeshPtr		box_;

	system_clock::time_point	time_last_;
	system_clock::time_point	time_now_;
};

int _tmain( int /*argc*/, TCHAR* /*argv*/[] ){
	TestWindow window;
	window.RunApp();

	return 0;
}