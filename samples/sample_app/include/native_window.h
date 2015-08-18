#pragma once

#include "3rd/SDL/include/SDL.h"

namespace sample_app
{
	class IWindowDelegate;
	class NativeWindow
	{
	public:
		NativeWindow(IWindowDelegate* delegate);
		virtual ~NativeWindow();
	public:
		virtual bool	CreateWindow()	= 0;
		virtual void	RunWindow()		= 0;

		virtual void	get_surface(SDL_Surface*& surface) = 0;
	protected:
		IWindowDelegate*	window_delegate_;
	};

	NativeWindow* CreateNativeWindow(IWindowDelegate* delegate);
};


