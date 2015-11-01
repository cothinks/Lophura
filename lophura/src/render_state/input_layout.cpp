#include "lophura/include/render_state/input_layout.h"

using namespace std;

BEGIN_NS_LOPHURA()

input_layout_ptr input_layout::create(input_element_desc const* desc, size_t desc_count)
{
	input_layout_ptr input_layout_ = make_shared<input_layout>();
	input_layout_->layout_desc_.assign(desc,desc+desc_count);

	return input_layout_;
}

input_element_desc const* input_layout::find_desc( size_t slot ) const
{
	for( size_t i_desc = 0; i_desc < layout_desc_.size(); ++i_desc ){
		if( slot == layout_desc_[i_desc].input_slot ){
			return &( layout_desc_[i_desc] );
		}
	}
	return NULL;
}

input_element_desc const* input_layout::find_desc( semantic_value const& v) const
{
	for( size_t i_desc = 0; i_desc < layout_desc_.size(); ++i_desc ){
		if( semantic_value( layout_desc_[i_desc].semantic_name,  layout_desc_[i_desc].semantic_index ) == v ){
			return &( layout_desc_[i_desc] );
		}
	}
	return NULL;
}

END_NS_LOPHURA()