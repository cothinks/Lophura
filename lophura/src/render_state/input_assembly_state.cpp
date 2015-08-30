#include "lophura/include/render_state/input_assembly_state.h"

BEGIN_NS_LOPHURA()

void input_assembly_state::update( size_t start_slot,
								   data_buffer_ptr const* buffer, size_t buffer_count,
								   size_t const* strides, size_t const* offsets )
{
	if ( buffer == nullptr || strides == nullptr || offsets == nullptr )
	{
		return;
	}

	if( start_slot + buffer_count >=  MAX_IA_SLOT )
	{
		return;
	}

	for ( size_t i = 0; i < buffer_count; ++i )
	{
		slots_[start_slot+i].slot_		= start_slot+i;
		slots_[start_slot+i].buffer_	= buffer[i];
		slots_[start_slot+i].stride_	= strides[i];
		slots_[start_slot+i].offset_	= offsets[i];
	}
}

END_NS_LOPHURA()