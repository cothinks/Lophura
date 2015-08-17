#pragma once

#include "renderimple.h"

LOPHURA_BEGIN

class SynRender :
	public RenderImple
{
public:
	SynRender(void);
	~SynRender(void);
public:
	void	CommitCommand() override;
};

LOPHURA_END