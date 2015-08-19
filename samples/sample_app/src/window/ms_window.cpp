#include "samples/sample_app/include/window/ms_window.h"
#include "samples/sample_app/include/window/window.h"

#include <tchar.h>
#include <string>
#include <assert.h>

namespace sample_app
{
	const	TCHAR*		ms_window::class_name	= _T("ms_window");
	const	uint32_t	ms_window::class_style	= ( CS_VREDRAW | CS_HREDRAW );
	const	TCHAR*		ms_window::window_name	= _T("lophura_sample");
	const	uint32_t	ms_window::window_style	= ( WS_VISIBLE | WS_OVERLAPPEDWINDOW );

	LRESULT CALLBACK ms_window::win32_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		ms_window* pThis = NULL;
		if( uMsg == WM_NCCREATE ) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<ms_window*>(lpcs->lpCreateParams);
			pThis->win32_handle_ = hWnd;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
		} 
		else {
			pThis = reinterpret_cast<ms_window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if( uMsg == WM_NCDESTROY && pThis != NULL ) {
				LRESULT lRes = ::CallWindowProc(DefWindowProc, hWnd, uMsg, wParam, lParam);
				::SetWindowLongPtr(pThis->win32_handle_, GWLP_USERDATA, 0L);
				pThis->win32_handle_ = NULL;
				return lRes;
			}
		}
		if( pThis != NULL ) {
			return pThis->handle_message(uMsg, wParam, lParam);
		} 
		else {
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	bool ms_window::create_window(uint32_t width,uint32_t height)
	{
		HINSTANCE instance = ::GetModuleHandle(NULL);
		if (!register_class(instance)) return false;

		win32_handle_ = ::CreateWindowEx(NULL, class_name, window_name, window_style, 0, 0, width, height, NULL, NULL,instance, this);
		assert(win32_handle_!=NULL);
		
		return NULL != win32_handle_;
	}

	void ms_window::set_title(const kstring title)
	{
		::SetWindowText(win32_handle_,title.c_str());
	}

	void ms_window::run_window()
	{
		run_message_loop();
	}

	bool ms_window::register_class(HINSTANCE instance)
	{
		WNDCLASS wc = { 0 };

		wc.style			= class_style;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hIcon			= NULL;
		wc.lpfnWndProc		= ms_window::win32_proc;
		wc.hInstance		= instance;
		wc.hCursor			= ::LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= NULL;
		wc.lpszClassName	= class_name;

		ATOM ret = ::RegisterClass(&wc);
		assert(ret!=NULL || ::GetLastError()==ERROR_CLASS_ALREADY_EXISTS);
		return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	LRESULT ms_window::handle_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if ( WM_CREATE == uMsg ){
			window_delegate_->on_create();
		}else if( WM_PAINT == uMsg ){
			window_delegate_->on_draw();
		}else if( WM_DESTROY == uMsg ){
			::PostQuitMessage(0);
		}

		return ::DefWindowProc(win32_handle_, uMsg, wParam, lParam);
	}

	void ms_window::run_message_loop()
	{
		while (TRUE) 
		{ 
			MSG msg;
			if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) 
			{ 
				if (msg.message == WM_QUIT) 
					break ; 
				TranslateMessage (&msg) ; 
				DispatchMessage (&msg) ; 
			} 
			else 
			{ 
				window_delegate_->on_idle();
			} 
		} 
	}

	bool ms_window::get_any_data(uint64_t& data)
	{
		if(NULL != win32_handle_){
			data = (uint64_t)win32_handle_;
			return true;
		}

		return false;
	}

};