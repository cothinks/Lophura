#pragma once

#include "lophura/include/lophura_forward.h"

#include "lophura/include/render_imple.h"

BEGIN_NS_LOPHURA()

class syn_render :
	public render_imple
{
public:
	syn_render(void);
	~syn_render(void);
public:
	void	commit_command() override;
};

END_NS_LOPHURA()