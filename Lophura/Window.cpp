#include "Window.h"
#include "NativeWindow.h"

LOPHURA_BEGIN

Window::Window()
{
}

Window::~Window()
{
}

bool Window::OnCreate()
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
	CreateNativeWindow(this);
}

LOPHURA_END