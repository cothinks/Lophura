#include "asynrender.h"

using namespace std;

LOPHURA_BEGIN

namespace
{
	void StartAsynRenderThread(AsynRender* asyn_render){
		asyn_render->DoRendering();
	}
};

AsynRender::AsynRender(void)
{
	CreateAsynSupport();
}

AsynRender::~AsynRender(void)
{
	asyn_render_thread_running_ = false;
	asyn_render_thread_.join();
}

void AsynRender::CreateAsynSupport()
{
	asyn_render_thread_ = thread(StartAsynRenderThread,this);
	asyn_render_thread_running_	= true;
}

void AsynRender::CommitCommand()
{
	render_state_buffer_.push_front(state_);
}

void AsynRender::DoRendering()
{
	while ( asyn_render_thread_running_ )
	{
		RenderStatePtr	render_state;
		render_state_buffer_.pop_back(render_state);

		if(render_state)
		{
			render_core_.ProcessRenderRequest(render_state);
		}
	}
}

LOPHURA_END