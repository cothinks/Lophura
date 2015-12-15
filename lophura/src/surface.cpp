#include "lophura/include/surface.h"

BEGIN_NS_LOPHURA()

surface::surface()
{}

surface::surface(size_t width, size_t height, size_t num_sample, color_format fmt)
				:size_(width,height,1,0)
				,sample_count_(num_sample)
				,format_(fmt)
				,elem_size_(4)
{
	if (fmt == fmt_r32g32b32a32_unit){
		elem_size_ = sizeof(color_rgba_32f);
	}else{
		elem_size_ = 4;
	}

	data_.resize(pitch() * height);
}

surface::~surface()
{}

size_t surface::texel_offset(size_t x, size_t y, size_t sample) const
{
	return ((y * size_[0] + x) * sample_count_ + sample) * elem_size_;
}

void* surface::texel_address(size_t x, size_t y, size_t sample)
{
	return reinterpret_cast<void*>(data_.data() + texel_offset(x, y, sample));
}

void const* surface::texel_address(size_t x, size_t y, size_t sample) const
{
	return reinterpret_cast<void const*>(data_.data() + texel_offset(x, y, sample));
}

void surface::fill_texels(color_rgba_32f const& color)
{
	fill_texels(0, 0, size_[0], size_[1], color);
}

color_rgba_32f surface::get_texel(size_t x, size_t y, size_t sample) const
{
	color_rgba_32f color;
	uint8_t const* pix_clr = reinterpret_cast<uint8_t const*>(texel_address(x,y,sample));

	color.b = pix_clr[0] / 255.0f;
	color.g = pix_clr[1] / 255.0f;
	color.r = pix_clr[2] / 255.0f;
	color.a = pix_clr[3] / 255.0f;

	return color;
}

void surface::fill_texels(size_t sx, size_t sy, size_t width, size_t height, const color_rgba_32f& color)
{
	uint8_t pix_clr[4] = {0};

	pix_clr[0] = color.b * 255;
	pix_clr[1] = color.g * 255;
	pix_clr[2] = color.r * 255;
	pix_clr[3] = color.a * 255;

	for (size_t x = sx; x < sx + width; ++x)
	{
		for (size_t s = 0; s < sample_count_; ++s)
		{
			memcpy(&data_[((size_[0] * sy + x) * sample_count_ + s) * elem_size_], pix_clr, elem_size_);
		}
	}

	for (size_t y = sy + 1; y < sy + height; ++y)
	{
		memcpy(&data_[(size_[0] * y + sx) * sample_count_ * elem_size_], &data_[(size_[0] * sy + sx) * sample_count_ * elem_size_], sample_count_ * elem_size_ * width);
	}
}

END_NS_LOPHURA()