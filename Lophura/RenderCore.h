#pragma once
#include "Lophura.h"
#include "RenderState.h"
#include "PipeLine.h"

LOPHURA_BEGIN

class RenderCore
{
public:
	RenderCore(void);
	virtual ~RenderCore(void);
public:
	void Update(RenderStatePtr const& state);
	void Execute();
protected:
	void ClearColor();
	void Draw();
protected:
	RenderStatePtr	state_;
	PipeLinePtr		pipe_line_;
};

LOPHURA_END