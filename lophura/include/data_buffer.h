#pragma once

#include "lophura_base/include/platform/typedefs.h"
#include "lophura/include/lophura_forward.h"
#include "lophura/include/colors.h"

#include <vector>

BEGIN_NS_LOPHURA()

class data_buffer
{
public:
	data_buffer(size_t size);
	virtual ~data_buffer();
public:
	size_t		size() const { return data_.size(); }

	uint8_t*	raw_data(size_t offset){ return data_.data() + offset; }

	void		fill_color(size_t sx,size_t sy,size_t width,size_t height,color_rgba_32f const& color);
	void		fill_color(color_rgba_32f const& color);

	void		set_pos(int x,int y,color_rgba_32f const& color);
private:
	std::vector<uint8_t>	data_;
};

END_NS_LOPHURA()