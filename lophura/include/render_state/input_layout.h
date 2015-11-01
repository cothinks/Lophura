#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/platform/typedefs.h"
#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura/include/format.h"
#include "lophura/include/shader.h"

#include <vector>

BEGIN_NS_LOPHURA()

struct input_element_desc
{
	std::string				semantic_name;
	uint32_t				semantic_index;
	color_format			data_format;
	uint32_t				input_slot;

	input_element_desc(
		const char*		semantic_name,
		uint32_t		semantic_index,
		color_format	data_format,
		uint32_t		input_slot
		)
		: semantic_name(semantic_name)
		, semantic_index(semantic_index)
		, data_format(data_format)
		, input_slot(input_slot)
	{}

	input_element_desc()
		: semantic_index(0)
		, data_format(data_format)
		, input_slot(input_slot)
	{}
		
};

LOPHURA_DECLARE_CLASS_SHARED_PTR(input_layout);

class input_layout
{
public:
	static input_layout_ptr create( input_element_desc const* decs, size_t desc_count);

	virtual input_element_desc const* find_desc( size_t slot ) const;
	virtual input_element_desc const* find_desc( semantic_value const& ) const;
private:
	std::vector<input_element_desc> layout_desc_;
};

END_NS_LOPHURA()
