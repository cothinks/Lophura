#pragma once

#include "samples/sample_app/include/window/native_window.h"
#include <windows.h>

namespace sample_app
{
	class ms_window : public native_window
	{
		static const TCHAR*		class_name;
		static const uint32_t	class_style;
		static const TCHAR*		window_name;
		static const uint32_t	window_style;
	public:
		ms_window(window_delegate* delegate) : native_window(delegate)
		{}
		~ms_window()
		{}
	public:
		bool	create_window(uint32_t width,uint32_t height) override;
		void	set_title(const kstring title) override;
		void	run_window() override;

		bool	get_any_data(uint64_t& data) override;
	private:
		bool	register_class(HINSTANCE instance);
		LRESULT	handle_message(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void	run_message_loop();

		static LRESULT CALLBACK win32_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		HWND	win32_handle_;
	};
};