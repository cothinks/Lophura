#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/stream_assembler.h"
#include "lophura/include/data_addressing.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(stream_assembler);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_addressing);

struct render_stages
{
	stream_assembler_ptr assembler_;
	data_addressing_ptr	 data_address_;
};

END_NS_LOPHURA()