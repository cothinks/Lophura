#pragma once

#include "lophura_base/include/utility/shared_declaration.h"
#include "lophura_base/include/platform/typedefs.h"

namespace sample_app
{
	LOPHURA_DECLARE_CLASS_SHARED_PTR(native_window);
	
	class window_delegate;
	class native_window
	{
	public:
		native_window(window_delegate* delegate);
		virtual ~native_window();
	public:
		virtual bool	create_window(uint32_t windth,uint32_t height) = 0;
		virtual void	run_window() = 0;
		virtual void	set_title(const kstring title) = 0;

		virtual bool	get_any_data(uint64_t& data) = 0;
	protected:
		window_delegate*	window_delegate_;
	};

	native_window_ptr create_native_window(window_delegate* delegate);
};


