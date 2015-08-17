#pragma once

#include "3rd/SDL/include/SDL.h"

LOPHURA_BEGIN

//sdl-based frame buffer
class SwapChain
{
public:
	SwapChain(void);
	virtual ~SwapChain(void);

	//sdl frame buffer
	virtual	void		set_sdl_surface(SDL_Surface*	surface) = 0;
public:
	virtual BufferPtr	GetBuffer()	= 0;
	virtual	void		Present()	= 0;
};

LOPHURA_DECLARE_PTR(SwapChain)

LOPHURA_END



extern "C"
{
	void LophuraCreateSwapchain(Lophura::SwapChainPtr& swap_chain);
};