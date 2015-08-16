#pragma once

#include "Lophura.h"
#include "DataBuffer.h"
#include "Format.h"
#include "ViewPort.h"
#include "color.h"
#include "vector.h"
#include "SwapChain.h"

LOPHURA_BEGIN

enum class PrimitiveTopology
{
	primitive_triangle_list,
};

enum class CommandId
{
	draw,
	draw_index,
	clear_depth_stencil,
	clear_color
};

struct RenderState
{
	CommandId			command_;

	BufferPtr			index_buffer_;
	INDEX_FORMAT		index_format_;
	BufferPtr			vertex_buffer_;

	BufferPtr			color_target_;
	BufferPtr			depth_stencil_target_;

	ViewPort			view_port_;
	Matrix44			wrold_view_proj_;
	PrimitiveTopology	primitive_topology_;

	size_t				start_index_;
	size_t				primitive_count_;

	COLORRGBA32F		clear_color_;

	//test
	SwapChainPtr		swap_chain_;
};

LOPHURA_DECLARE_PTR(RenderState)

LOPHURA_END