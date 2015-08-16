#pragma once

LOPHURA_BEGIN

class SwapChain
{
public:
	SwapChain(void);
	virtual ~SwapChain(void);
public:
	virtual BufferPtr	GetBuffer()	= 0;
	virtual	void		Present()	= 0;
};

LOPHURA_DECLARE_PTR(SwapChain)

LOPHURA_END



extern "C"
{
	void LophuraCreateSwapchain(Lophura::SwapChainPtr& swap_chain);
};