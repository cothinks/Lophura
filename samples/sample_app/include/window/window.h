#pragma once

#include "lophura_base/include/utility/shared_declaration.h"

namespace sample_app
{
	LOPHURA_DECLARE_CLASS_SHARED_PTR(native_window);

	class window_delegate
	{
	public:
		virtual ~window_delegate();
	public:
		virtual bool	on_create()	= 0;
		virtual void	on_draw()	= 0;
		virtual void	on_idle()	= 0;
	};

	class window : public window_delegate
	{
	public:
		window();
		virtual ~window();
	public:
		virtual bool	on_create();
		virtual void	on_draw();
		virtual void	on_idle();
	public:
	public:
		void	create_window(uint32_t width,uint32_t height);
		void	run_app();
	protected:
		native_window_ptr	native_window_;
	};
};