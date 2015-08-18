#include "lophura/include/swap_chain.h"
#include "lophura/include/data_buffer.h"

BEGIN_NS_LOPHURA()

swap_chain::swap_chain(void)
{
}


swap_chain::~swap_chain(void)
{
}

class swap_chain_imple : public swap_chain
{
public:
	swap_chain_imple(){
		
	}

	void set_sdl_surface(SDL_Surface* surface)
	{
		surface_ = surface;

		color_target_.reset(new data_buffer(surface_->pitch*surface_->h));
	}

	data_buffer_ptr	GetBuffer() override
	{
		return color_target_;
	}

	void		Present() override
	{
		uint8_t* src_buffer		= color_target_->raw_data(0);
		uint8_t* dest_buffer	= reinterpret_cast<uint8_t*>(surface_->pixels);

		memcpy(dest_buffer,src_buffer,color_target_->size());

		SDL_Flip(surface_);
	}
protected:
	data_buffer_ptr		color_target_;
	SDL_Surface*	surface_;
};

END_NS_LOPHURA()


extern "C"
{
	void lophura_create_swap_chain( lophura::swap_chain_ptr& swap_chain )
	{
		swap_chain = lophura::swap_chain_ptr(new lophura::swap_chain_imple());
	}
}