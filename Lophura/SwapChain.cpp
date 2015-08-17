#include "Lophura.h"
#include "DataBuffer.h"
#include "SwapChain.h"

LOPHURA_BEGIN

SwapChain::SwapChain(void)
{
}


SwapChain::~SwapChain(void)
{
}

class SwapChainImple : public SwapChain
{
public:
	SwapChainImple(){
		
	}

	void set_sdl_surface(SDL_Surface* surface)
	{
		surface_ = surface;

		color_target_.reset(new Buffer(surface_->pitch*surface_->h));
	}

	BufferPtr	GetBuffer() override
	{
		return color_target_;
	}

	void		Present() override
	{
		uint8_t* src_buffer		= color_target_->RawData(0);
		uint8_t* dest_buffer	= reinterpret_cast<uint8_t*>(surface_->pixels);

		memcpy(dest_buffer,src_buffer,color_target_->Size());

		SDL_Flip(surface_);
	}
protected:
	BufferPtr		color_target_;

	SDL_Surface*	surface_;
};

LOPHURA_END


extern "C"
{
	void LophuraCreateSwapchain( Lophura::SwapChainPtr& swap_chain )
	{
		swap_chain = Lophura::SwapChainPtr(new Lophura::SwapChainImple());
	}
}