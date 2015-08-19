#include "samples/sample_app/include/window/window.h"
#include "samples/sample_app/include/window/native_window.h"

#include "samples/sample_app/include/window/native_window_declaration.h"

using namespace std;

namespace sample_app{

native_window::native_window(window_delegate* delegate)
{
	window_delegate_ = delegate;
}

native_window::~native_window()
{}

native_window_ptr create_native_window(window_delegate* delegate)
{
	return  make_shared<ms_window>(delegate);
}

};