#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/platform/typedefs.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/lophura_capacity.h"

#include <array>

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);

struct input_assembly_desc
{
	size_t			slot_;
	data_buffer_ptr	buffer_;
	size_t			stride_;
	size_t			offset_;
};

struct input_assembly_state
{
	void update(
		size_t start_slot,
		data_buffer_ptr const* buffer, size_t buffer_count,
		size_t const* strides, size_t const* offsets
		);

	std::tr1::array<input_assembly_desc,MAX_IA_SLOT> slots_;
};

END_NS_LOPHURA()