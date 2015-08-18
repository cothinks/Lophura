#include "lophura/include/data_buffer.h"

BEGIN_NS_LOPHURA()

data_buffer::data_buffer(size_t size) :data_(size)
{
}

data_buffer::~data_buffer()
{
}

void data_buffer::fill_color( color_rgba_32f const& color )
{
	fill_color(0,0,800,600,color);
}

void data_buffer::fill_color( size_t sx,size_t sy,size_t width,size_t height,color_rgba_32f const& color )
{
	size_t elem_size = sizeof(color_rgba_32f);
	uint8_t color_rgba8[4] = {0};

	color_rgba8[0] = color.b*255;
	color_rgba8[1] = color.g*255;
	color_rgba8[2] = color.r*255;
	color_rgba8[3] = color.a*255;

	for (size_t x = sx;x < sx+width;++x)
	{
		memcpy(&data_[(width*sy+x)*4],&color_rgba8,4);
	}

	for (size_t y = sy;y < height;++y)
	{
		memcpy(&data_[(width*y+sx)*4],&data_[(width*sy+sx)*4],width*4);
	}
}

void data_buffer::set_pos(int x,int y,color_rgba_32f const& color)
{
	uint8_t color_rgba8[4] = {0};

	color_rgba8[0] = color.b*255;
	color_rgba8[1] = color.g*255;
	color_rgba8[2] = color.r*255;
	color_rgba8[3] = color.a*255;

	memcpy(&data_[(800*y+x)*4],&color_rgba8,4);
}

END_NS_LOPHURA()