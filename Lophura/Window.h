#pragma once
#include"Lophura.h"

LOPHURA_BEGIN

class IWindowDelegate
{
public:
	virtual bool	OnCreate()	= 0;
	virtual void	OnDraw()	= 0;
	virtual void	OnIdle()	= 0;
};

class Window : public IWindowDelegate
{
public:
	Window();
	virtual ~Window();
public:
	virtual bool	OnCreate();
	virtual void	OnDraw();
	virtual void	OnIdle();
public:
	void	RunApp();
};

LOPHURA_END

