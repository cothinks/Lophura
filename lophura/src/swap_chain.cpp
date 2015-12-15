#include "lophura/include/swap_chain.h"
//#include "lophura/include/data_buffer.h"
#include "lophura/include/surface.h"

#include <windows.h>

using namespace std;

BEGIN_NS_LOPHURA()

swap_chain::swap_chain()
{}

swap_chain::~swap_chain(void)
{}

class swap_chain_imple : public swap_chain
{
public:
	swap_chain_imple()
	{}

	void			create(swap_chain_parameter const& swap_chain_param) override
	{
		swap_chain_param_ = swap_chain_param;

		size_t width		= swap_chain_param.width;
		size_t height		= swap_chain_param.height;
		size_t num_samples	= swap_chain_param.num_samples;
		color_format fmt	= swap_chain_param.color_fmt;
		
		color_target_ = make_shared<surface>(width, height, num_samples,fmt);
	}

	surface_ptr	get_surface() override { return color_target_; }
protected:
	surface_ptr				color_target_;
	swap_chain_parameter	swap_chain_param_;
	uint64_t				any_data_;				
};


class win32_swap_chain : public swap_chain_imple
{
public:
	win32_swap_chain()
	{}

	void	create(swap_chain_parameter const& swap_chain_param) override
	{
		swap_chain_imple::create(swap_chain_param);
		init_bitmap_info(swap_chain_param);

		hdc_ = reinterpret_cast<HDC__*>(swap_chain_param.any_data);
	}

	void	present() override
	{
		uint32_t width	= swap_chain_param_.width;
		uint32_t height	= swap_chain_param_.height;

		::SetDIBitsToDevice(hdc_, 0, 0, width, height, 0, 0, 0, height, reinterpret_cast<void*>(color_target_->texel_address(0,0,1))
			,&bitmap_info_,DIB_RGB_COLORS);
	}
private:
	void	init_bitmap_info(swap_chain_parameter const& swap_chain_param)
	{
		bitmap_info_.bmiHeader.biBitCount = 32;
		bitmap_info_.bmiHeader.biClrImportant = 0;
		bitmap_info_.bmiHeader.biClrUsed = 0;
		bitmap_info_.bmiHeader.biCompression = BI_RGB;  
		bitmap_info_.bmiHeader.biPlanes = 1;  
		bitmap_info_.bmiHeader.biSize=sizeof(tagBITMAPINFOHEADER);  
		bitmap_info_.bmiHeader.biSizeImage = 0;  
		bitmap_info_.bmiHeader.biXPelsPerMeter = 0;  
		bitmap_info_.bmiHeader.biYPelsPerMeter = 0;  
		bitmap_info_.bmiHeader.biWidth = swap_chain_param.width;
		bitmap_info_.bmiHeader.biHeight = -swap_chain_param.height;
	}
protected:
	BITMAPINFO	bitmap_info_;
	HDC			hdc_;
};

END_NS_LOPHURA()


extern "C"
{
	void lophura_create_swap_chain( lophura::swap_chain_ptr& swap_chain,lophura::swap_chain_parameter const& swap_chain_param)
	{
		swap_chain	= make_shared<lophura::win32_swap_chain>();
		swap_chain->create(swap_chain_param);
	}
}