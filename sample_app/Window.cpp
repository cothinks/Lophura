#include "Window.h"
#include "NativeWindow.h"

namespace sample_app{

Window::Window()
{
}

Window::~Window()
{
}

bool Window::OnCreate(SDL_Surface* surface)
{
	return false;
}

void Window::OnDraw()
{
}

void Window::OnIdle()
{
}

void Window::RunApp()
{
	NativeWindow* native_window = CreateNativeWindow(this);
}

};