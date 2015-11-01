#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/data_buffer.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/data_addressing.h"
#include "lophura/include/render_stages.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_STRUCT_SHARED_PTR(render_state);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_buffer);
LOPHURA_DECLARE_CLASS_SHARED_PTR(data_addressing);

class pipeline
{
public:
	pipeline(void);
	~pipeline(void);
public:
	void	initialize(render_stages const* stages);
	void	lanche(render_state_ptr state);
protected:
	void	prepare();
	void	draw();
private:
	render_state_ptr		state_;
	data_addressing_ptr		addressing_;
};

END_NS_LOPHURA()

