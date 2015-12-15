#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/stream_assembler.h"
#include "lophura/include/data_addressing.h"
#include "lophura/include/framebuffer.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(stream_assembler);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_addressing);
LOPHURA_DECLARE_CLASS_SHARED_PTR(rasterizer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(framebuffer);

struct render_stages
{
	stream_assembler_ptr assembler_;
	data_addressing_ptr	 data_address_;
	rasterizer_ptr		 ras_;
	framebuffer_ptr		 backend;
};

END_NS_LOPHURA()