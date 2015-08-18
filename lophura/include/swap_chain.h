#pragma once

#include "lophura/include/lophura_forward.h"
#include "3rd/SDL/include/SDL.h"

#include "lophura_base/include/utility/shared_declaration.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(swap_chain);

//sdl-based frame buffer
class swap_chain
{
public:
	swap_chain(void);
	virtual ~swap_chain(void);

	//sdl frame buffer
	virtual	void			set_sdl_surface(SDL_Surface*	surface) = 0;
public:
	virtual data_buffer_ptr	GetBuffer()	= 0;
	virtual	void			Present()	= 0;
};

END_NS_LOPHURA()

extern "C"
{
	void lophura_create_swap_chain(lophura::swap_chain_ptr& swap_chain);
};