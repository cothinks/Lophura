#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/lophura_define.h"

#include "lophura_base/include/utility/shared_declaration.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(swap_chain);

class swap_chain
{
public:
	swap_chain();
	virtual ~swap_chain(void);
public:
	virtual void			create(swap_chain_parameter const& swap_chain_param)	= 0;
	virtual	void			present()	= 0;
	virtual data_buffer_ptr	get_buffer()	= 0;
};

END_NS_LOPHURA()

extern "C"
{
	void lophura_create_swap_chain(lophura::swap_chain_ptr& swap_chain,lophura::swap_chain_parameter const& swap_chain_param);
};