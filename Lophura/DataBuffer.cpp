#include "Lophura.h"
#include "DataBuffer.h"

LOPHURA_BEGIN

Buffer::Buffer(size_t size) :data_(size)
{
}

Buffer::~Buffer()
{
}

void Buffer::FillColor( COLORRGBA32F const& color )
{
	FillColor(0,0,800,600,color);
}

void Buffer::FillColor( size_t sx,size_t sy,size_t width,size_t height,COLORRGBA32F const& color )
{
	size_t elem_size = sizeof(COLORRGBA32F);
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

void Buffer::SetPos(int x,int y,COLORRGBA32F const& color)
{
	uint8_t color_rgba8[4] = {0};

	color_rgba8[0] = color.b*255;
	color_rgba8[1] = color.g*255;
	color_rgba8[2] = color.r*255;
	color_rgba8[3] = color.a*255;

	memcpy(&data_[(800*y+x)*4],&color_rgba8,4);
}

LOPHURA_END