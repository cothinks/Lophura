#pragma once

#include "lophura_base/include/platform/typedefs.h"
#include "lophura_base/include/math/vector.h"
#include "lophura/include/lophura_forward.h"
#include "lophura/include/format.h"
#include "lophura/include/colors.h"

#include <vector>

BEGIN_NS_LOPHURA()

class surface
{
public:
	surface();
	surface(size_t width, size_t height, size_t num_sample, color_format fmt);
	~surface();

	size_t width() const
	{
		return size_[0];
	}

	size_t height() const
	{
		return size_[1];
	}

	size_t pitch() const
	{
		return width() * sample_count_ * elem_size_;
	}

	lophura_base::uint4 size() const
	{
		return size_;
	}

	size_t sample_count() const
	{
		return sample_count_;
	}

	color_format get_color_format() const
	{
		return format_;
	}

	void* texel_address(size_t x, size_t y, size_t sample);
	void const* texel_address(size_t x, size_t y, size_t sample) const;

	void fill_texels(size_t sx, size_t sy, size_t width, size_t height, const color_rgba_32f& color);
	void fill_texels(color_rgba_32f const& color);
private:
	size_t texel_offset(size_t x, size_t y, size_t sample) const;
private:
	size_t				elem_size_;
	lophura_base::uint4	size_;
	size_t				sample_count_;
	color_format		format_;
	std::vector<lophura_base::byte>
						data_;
};

END_NS_LOPHURA()