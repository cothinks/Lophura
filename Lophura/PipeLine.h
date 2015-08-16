#pragma once

#include "Lophura.h"
#include "RenderState.h"

LOPHURA_BEGIN

class PipeLine
{
public:
	PipeLine(void);
	~PipeLine(void);
public:
	virtual void Lanche(RenderStatePtr state) = 0;
};

LOPHURA_DECLARE_PTR(PipeLine)

LOPHURA_END

