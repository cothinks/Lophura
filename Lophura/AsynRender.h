#pragma once

#include "renderimple.h"

#include "lophura_base/include/memory/bounded_buffer.h"

#include <mutex>
#include <thread>

LOPHURA_BEGIN

class AsynRender :
	public RenderImple
{
public:
	AsynRender(void);
	~AsynRender(void);
public:
	void	CommitCommand() override;
protected:
	void	CreateAsynSupport();
public:
	void	DoRendering();
private:
	lophura_base::bounded_buffer<RenderStatePtr>	render_state_buffer_;

	std::thread					asyn_render_thread_;
	bool						asyn_render_thread_running_;
};

LOPHURA_END