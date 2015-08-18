#include "lophura/include/asyn_render.h"

using namespace std;

namespace
{
	void start_asyn_render_thread(lophura::asyn_render* asyn_render){
		asyn_render->do_rendering();
	}
};

BEGIN_NS_LOPHURA()

asyn_render::asyn_render(void)
{
	create_asyn_support();
}

asyn_render::~asyn_render(void)
{
	asyn_render_thread_running_ = false;
	asyn_render_thread_.join();
}

void asyn_render::create_asyn_support()
{
	asyn_render_thread_ = thread(start_asyn_render_thread,this);
	asyn_render_thread_running_	= true;
}

void asyn_render::commit_command()
{
	render_state_buffer_.push_front(state_);
}

void asyn_render::do_rendering()
{
	while ( asyn_render_thread_running_ )
	{
		render_state_ptr	render_state;
		render_state_buffer_.pop_back(render_state);

		if(render_state){
			render_core_.process_render_request(render_state);
		}
	}
}

END_NS_LOPHURA()