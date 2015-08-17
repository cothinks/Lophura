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
	void	Lanche(RenderStatePtr state);
protected:
	void	Prepare();
	void	Draw();
private:
	RenderStatePtr	state_;
	Buffer			transformed_verts_;
};

LOPHURA_DECLARE_PTR(PipeLine)

LOPHURA_END

