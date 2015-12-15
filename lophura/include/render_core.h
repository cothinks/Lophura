#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/render_stages.h"

BEGIN_NS_LOPHURA()

LOPHURA_DECLARE_STRUCT_SHARED_PTR(render_state)

class render_core
{
public:
	render_core(void);
	virtual ~render_core(void);
public:
	void process_render_request(render_state_ptr const& state);
protected:
	void execute();
	void clear_color();
	void draw();
protected:
	render_state_ptr	state_;
	render_stages		stages_;
};

END_NS_LOPHURA()