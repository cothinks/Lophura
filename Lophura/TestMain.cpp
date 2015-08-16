#include "Window.h"
#include "Render.h"
#include "ViewPort.h"
#include "Mesh.h"
#include "SwapChain.h"
#include "math.h"
#include "constant.h"
#include<windows.h>

USING_LOPHURA

//SwapChainPtr	swap_chain_;

class TestWindow : public Window
{
public:
	virtual bool	OnCreate()	override
	{
		LophuraCreateSwapchain(swap_chain_);
		LophuraCreateRender(render_);
		render_->SetSwapChian(swap_chain_);

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
};

int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nShowCmd)
{
	TestWindow window;
	window.RunApp();

	return 0;
}