#include "lophura/include/render_state/input_layout.h"

using namespace std;

BEGIN_NS_LOPHURA()

input_layout_ptr input_layout::create(input_element_desc const* desc, size_t desc_count)
{
	input_layout_ptr input_layout_ = make_shared<input_layout>();
	input_layout_->layout_desc_.assign(desc,desc+desc_count);

	return input_layout_;
}

END_NS_LOPHURA()