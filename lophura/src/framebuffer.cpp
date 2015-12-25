#include "lophura/include/framebuffer.h"
#include "lophura/include/shader_regs.h"

BEGIN_NS_LOPHURA()

template <uint32_t Format>
class depth_stencil_accessor
{
public:
	static float 	read_depth(void const* /*ds_data*/)
	{
	}

	static uint32_t	read_stencil(void const* /*ds_data*/)
	{
	}

	static void 	read_depth_stencil(float& /*depth*/, uint32_t& /*stencil*/, void const* /*ds_data*/)
	{
	}

	static void 	write_depth(void* /*ds_data*/, float /*depth*/)
	{
	}

	static void		write_stencil(void* /*ds_data*/, uint32_t /*stencil*/)
	{
	}

	static void 	write_depth_stencil(void* /*ds_data*/, float /*depth*/, uint32_t /*stencil*/)
	{
	}
};

template <> class depth_stencil_accessor<fmt_r32g32b32a32_unit>
{
public:
	static float 	read_depth(void const* ds_data)
	{
		return reinterpret_cast<color_rgba_32f const*>(ds_data)->r;
	}

	static uint32_t	read_stencil(void const* ds_data)
	{
		union
		{
			float stencil_f;
			uint32_t stencil_u;
		};
		stencil_f = reinterpret_cast<color_rgba_32f const*>(ds_data)->g;
		return stencil_u;
	}

	static void 	read_depth_stencil(float& depth, uint32_t& stencil, void const* ds_data)
	{
		depth = reinterpret_cast<color_rgba_32f const*>(ds_data)->r;
		union
		{
			float stencil_f;
			uint32_t stencil_u;
		};
		stencil_f = reinterpret_cast<color_rgba_32f const*>(ds_data)->g;
		stencil = stencil_u;
	}

	static void 	write_depth(void* ds_data, float depth)
	{
		reinterpret_cast<color_rgba_32f*>(ds_data)->r = depth;
	}

	static void		write_stencil(void* ds_data, uint32_t stencil)
	{
		union
		{
			float stencil_f;
			uint32_t stencil_u;
		};
		stencil_u = stencil;
		reinterpret_cast<color_rgba_32f*>(ds_data)->g = stencil_f;
	}

	static void 	write_depth_stencil(void* ds_data, float depth, uint32_t stencil)
	{
		reinterpret_cast<color_rgba_32f*>(ds_data)->r = depth;
		union
		{
			float stencil_f;
			uint32_t stencil_u;
		};
		stencil_u = stencil;
		reinterpret_cast<color_rgba_32f*>(ds_data)->g = stencil_f;
	}
};

framebuffer::framebuffer()// :early_z_enable_(false)
{}

framebuffer::~framebuffer()
{}

void framebuffer::initialize(render_stages const* stages)
{}

void framebuffer::update(render_state const* state)
{
	color_target_	= state->color_target_.get();
	ds_target_		= state->depth_stencil_target_.get();

// 	for(size_t y = 0; y < 600; ++y)
// 	{
// 		for(size_t x = 0; x < 800; ++x)
// 		{
// 			pixel_accessor target_pixel(nullptr, ds_target_);
// 			target_pixel.set_pos(x, y);
// 			for(size_t sample = 0; sample < 1; ++sample)
// 			{
// 				void* addr = target_pixel.depth_stencil_address(sample);
// 				depth_stencil_accessor<fmt_r32g32b32a32_unit>::write_depth(addr,0xFFFFFFFFU);
// 			}
// 		}
// 	}
}

void framebuffer::render_sample(size_t x, size_t y, float depth,color_rgba_32f const& clr)
{
	pixel_accessor target_pixel(&color_target_, ds_target_);
	target_pixel.set_pos(x, y);

	void* ds_data = target_pixel.depth_stencil_address(0);
	float       old_depth;
	uint32_t    old_stencil;

	if (early_z_enable())
	{
		old_depth = depth_stencil_accessor<fmt_r32g32b32a32_unit>::read_depth(ds_data);
		if (depth > old_depth)
		{
			depth_stencil_accessor<fmt_r32g32b32a32_unit>::write_depth(ds_data, depth);
			color_target_->fill_texels(x, y, 1, 1, clr);
			return;
		}
	}
}

END_NS_LOPHURA()