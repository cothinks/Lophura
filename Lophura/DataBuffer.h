#pragma once
#include "color.h"
#include <vector>

LOPHURA_BEGIN

class Buffer
{
public:
	Buffer(size_t size);
	virtual ~Buffer();
public:
	size_t		Size() const { return data_.size(); }
	uint8_t*	RawData(size_t offset){ return data_.data() + offset; }

	void		FillColor(COLORRGBA32F const& color);
	void		FillColor(size_t sx,size_t sy,size_t width,size_t height,COLORRGBA32F const& color);

	void		SetPos(int x,int y,COLORRGBA32F const& color);
private:
	std::vector<uint8_t>	data_;
};

LOPHURA_DECLARE_PTR(Buffer)

LOPHURA_END