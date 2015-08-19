#include "samples/sample_app/include/window/window.h"
#include "samples/sample_app/include/window/native_window.h"

namespace sample_app{

window::window()
{
}

window::~window()
{
}

bool window::on_create()
{
	return false;
}

void window::on_draw()
{
}

void window::on_idle()
{
}

void window::create_window(uint32_t width,uint32_t height)
{
	native_window_ = create_native_window(this);
	native_window_->create_window(width,height);
}

void window::run_app()
{
	native_window_->run_window();
}

};