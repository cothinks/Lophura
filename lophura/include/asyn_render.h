#pragma once

#include "lophura/include/lophura_forward.h"

#include "lophura/include/render_imple.h"
#include "lophura_base/include/memory/bounded_buffer.h"

#include <mutex>
#include <thread>

BEGIN_NS_LOPHURA()

class asyn_render :
	public render_imple
{
public:
	asyn_render(void);
	~asyn_render(void);
public:
	void	commit_command() override;
protected:
	void	create_asyn_support();
public:
	void	do_rendering();
private:
	lophura_base::bounded_buffer<render_state_ptr>	render_state_buffer_;

	std::thread					asyn_render_thread_;
	bool						asyn_render_thread_running_;
};

END_NS_LOPHURA()