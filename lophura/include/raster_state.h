#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/lophura_define.h"

BEGIN_NS_LOPHURA()

struct raster_desc
{
	fill_mode			fm;
	cull_mode			cm;
};

class raster_state
{
public:
	raster_state( raster_desc const& desc);

	inline raster_desc const& get_desc() const
	{
		return desc_;
	}

private:
	raster_desc	desc_;
};

END_NS_LOPHURA()