#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura/include/shader_regs.h"
#include "lophura/include/render_state/render_state.h"
#include "lophura/include/render_state/input_layout.h"
#include "lophura/include/render_state/input_assembly_state.h"

#include <vector>

struct input_assembly_desc;
class  input_layout;

BEGIN_NS_LOPHURA()

class stream_assembler
{
public:
	void update( render_state const* state);

	void update_register_map( std::map<semantic_value, size_t> const& reg_map );
	void fetch_vertex(vs_input& vertex, size_t vert_index) const;

	void const* element_address( input_element_desc const& elem_desc, size_t vert_index) const;
private:
	std::vector<
		std::pair<size_t, input_element_desc const*>
	>	register_to_intput_element_desc_;

	input_layout*				layout_;
	input_assembly_desc const*	stream_buffer_descs_;	
};

END_NS_LOPHURA()