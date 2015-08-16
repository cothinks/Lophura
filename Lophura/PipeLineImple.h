#pragma once
#include "pipeline.h"

LOPHURA_BEGIN

class PipeLineImple :
	public PipeLine
{
public:
	PipeLineImple(void);
	~PipeLineImple(void);
public:
	virtual void Lanche(RenderStatePtr state) override;
protected:
	void	Prepare();
	void	Draw();
private:
	RenderStatePtr	state_;

	Buffer		transformed_verts;
};

LOPHURA_END