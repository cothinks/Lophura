#pragma once

#include "lophura_base/include/math/vector.h"
#include "lophura/include/lophura_forward.h"
#include "lophura/include/lophura_capacity.h"
#include "lophura/include/surface.h"

#include <array>

BEGIN_NS_LOPHURA()

class vs_input
{
public:
	vs_input()
	{}

	lophura_base::vec4& attribute(size_t index)
	{
		return attributes_[index];
	}

	lophura_base::vec4 const& attribute(size_t index) const
	{
		return attributes_[index];
	}
private:
	typedef std::tr1::array<
		lophura_base::vec4, MAX_VS_INPUT_ATTRS> attribute_array;
	attribute_array attributes_;
};

class vs_output
{
public:
	enum attrib_modifier_type
	{
		am_linear = 1UL << 0
	};
public:
	vs_output()
	{}

	lophura_base::vec4& position()
	{
		return registers_[0];
	}

	lophura_base::vec4 const& position() const
	{
		return registers_[0];
	}

	lophura_base::vec4* raw_data()
	{
		return registers_.data();
	}

	lophura_base::vec4 const* raw_data() const
	{
		return registers_.data();
	}

	lophura_base::vec4* attribute_data()
	{
		return registers_.data() + 1;
	}

	lophura_base::vec4 const* attribute_data() const
	{
		return registers_.data() + 1;
	}

	lophura_base::vec4& attribute(size_t index)
	{
		return attribute_data()[index];
	}

	lophura_base::vec4 const& attribute(size_t index) const
	{
		return attribute_data()[index];
	}
private:
	typedef std::tr1::array<
		lophura_base::vec4,MAX_VS_OUTPUT_ATTRS> register_array;
	register_array registers_;

	vs_output(vs_output const& rhs);
	//vs_output& operator=(vs_output const& rhs);
};

struct ps_output
{
	lophura_base::vec4 color;
};

struct pixel_accessor
{
	pixel_accessor(surface** const& color_buffers, surface* ds_buffer)
	{
		color_buffers_ = color_buffers;
		ds_buffer_ = ds_buffer;
	}

	void set_pos(size_t x, size_t y)
	{
		x_ = x;
		y_ = y;
	}

	color_rgba_32f color(size_t target_index, size_t sample_index) const
	{
		if(color_buffers_[target_index] == nullptr)
		{
			return color_rgba_32f(0.0f, 0.0f, 0.0f, 0.0f);
		}
		return color_buffers_[target_index]->get_texel(x_, y_, sample_index);
	}

	void color(size_t target_index, size_t sample, const color_rgba_32f& clr)
	{
		if(color_buffers_[target_index] != nullptr)
		{
			color_buffers_[target_index]->fill_texels(x_, y_,1,1, clr);
		}
	}

	void* depth_stencil_address(size_t sample) const
	{
		return ds_buffer_->texel_address(x_, y_, sample);
	}

private:
	pixel_accessor(const pixel_accessor& rhs);
	pixel_accessor& operator = (const pixel_accessor& rhs);

	surface**   color_buffers_;
	surface*    ds_buffer_;
	size_t      x_, y_;
};

END_NS_LOPHURA()