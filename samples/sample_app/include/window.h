#pragma once

#include "3rd/SDL/include/SDL.h"

namespace sample_app
{
	class IWindowDelegate
	{
	public:
		virtual bool	OnCreate(SDL_Surface* surface)	= 0;
		virtual void	OnDraw()	= 0;
		virtual void	OnIdle()	= 0;
	};

	class Window : public IWindowDelegate
	{
	public:
		Window();
		virtual ~Window();
	public:
		virtual bool	OnCreate(SDL_Surface* surface);
		virtual void	OnDraw();
		virtual void	OnIdle();
	public:
	void	RunApp();

	};
};