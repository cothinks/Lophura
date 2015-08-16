#pragma once
#include"Lophura.h"

LOPHURA_BEGIN

class IWindowDelegate;
class NativeWindow
{
public:
	NativeWindow(IWindowDelegate* delegate);
	virtual ~NativeWindow();
public:
	virtual bool	CreateWindow()	= 0;
	virtual void	RunWindow()		= 0;
protected:
	IWindowDelegate*	window_delegate_;
};

NativeWindow* CreateNativeWindow(IWindowDelegate* delegate);

LOPHURA_END