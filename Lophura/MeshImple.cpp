#include "MeshImple.h"

#include "lophura_base/include/math/vector.h"
#include "lophura_base/include/math/math.h"

#include <memory>

using namespace lophura_base;
using namespace std;

LOPHURA_BEGIN

MeshImple::MeshImple(RenderPtr render):Mesh(render),render_(render)
{}

MeshImple::~MeshImple(void)
{}

void MeshImple::Render()
{
	assert(render_.get());

	render_->SetIndexBuffer(index_buffer_,IF_16);
	render_->SetVertexBuffer(vertex_buffer_);

	render_->DrawIndex(0,primcount_);
}

Lophura::BufferPtr MeshImple::CreateBuffer(size_t size)
{
	return render_->CreateBuffer(size);
}

void MeshImple::SetIndexBuffer(BufferPtr buffer,INDEX_FORMAT index_fmt)
{
	index_buffer_	= buffer;
	index_fmt_		= index_fmt;
}

void MeshImple::SetVertexBuffer(BufferPtr buffer,COLOR_FORMAT pixel_fmt)
{
	vertex_buffer_	= buffer;
	pixel_fmt_		= pixel_fmt;
}

void MeshImple::SetPrimitiveCount(size_t count)
{
	primcount_ = count;
}

MeshPtr	CreatBox(RenderPtr render)
{
	MeshImple* mesh	= new MeshImple(render);
	{
		BufferPtr indices	= mesh->CreateBuffer(sizeof(uint16_t)*36);
		BufferPtr verts		= mesh->CreateBuffer(sizeof(vec4)*24);

		uint16_t*    pidxs = reinterpret_cast<uint16_t*>(indices->RawData(0));
		vec4*		pverts = reinterpret_cast<vec4*>(verts->RawData(0));

		{
			//+x
			MakeVec4(pverts[0],1.0f, 0.0f, 0.0f, 1.0f);
			MakeVec4(pverts[1],1.0f, 1.0f, 0.0f, 1.0f);
			MakeVec4(pverts[2],1.0f, 1.0f, 1.0f, 1.0f);
			MakeVec4(pverts[3],1.0f, 0.0f, 1.0f, 1.0f);
			//-x
			MakeVec4(pverts[4],0.0f, 0.0f, 0.0f, 1.0f);
			MakeVec4(pverts[5],0.0f, 0.0f, 1.0f, 1.0f);
			MakeVec4(pverts[6],0.0f, 1.0f, 1.0f, 1.0f);
			MakeVec4(pverts[7],0.0f, 1.0f, 0.0f, 1.0f);
			//+y
			MakeVec4(pverts[8],0.0f, 1.0f, 0.0f, 1.0f);
			MakeVec4(pverts[9],0.0f, 1.0f, 1.0f, 1.0f);
			MakeVec4(pverts[10],1.0f, 1.0f, 1.0f, 1.0f);
			MakeVec4(pverts[11],1.0f, 1.0f, 0.0f, 1.0f);
			//-y
			MakeVec4(pverts[12],0.0f, 0.0f, 0.0f, 1.0f);
			MakeVec4(pverts[13],1.0f, 0.0f, 0.0f, 1.0f);
			MakeVec4(pverts[14],1.0f, 0.0f, 1.0f, 1.0f);
			MakeVec4(pverts[15],0.0f, 0.0f, 1.0f, 1.0f);
			//+z
			MakeVec4(pverts[16],0.0f, 0.0f, 1.0f, 1.0f);
			MakeVec4(pverts[17],1.0f, 0.0f, 1.0f, 1.0f);
			MakeVec4(pverts[18],1.0f, 1.0f, 1.0f, 1.0f);
			MakeVec4(pverts[19],0.0f, 1.0f, 1.0f, 1.0f);
			//-z
			MakeVec4(pverts[20],0.0f, 0.0f, 0.0f, 1.0f);
			MakeVec4(pverts[21],0.0f, 1.0f, 0.0f, 1.0f);
			MakeVec4(pverts[22],1.0f, 1.0f, 0.0f, 1.0f);
			MakeVec4(pverts[23],1.0f, 0.0f, 0.0f, 1.0f);
			//indices
			pidxs[ 0] = 0;	pidxs[ 1] = 1;	pidxs[ 2] = 2;
			pidxs[ 3] = 2;	pidxs[ 4] = 3;	pidxs[ 5] = 0;
			pidxs[ 6] = 4;	pidxs[ 7] = 5;	pidxs[ 8] = 6;
			pidxs[ 9] = 6;	pidxs[10] = 7;	pidxs[11] = 4;
			pidxs[12] = 8;	pidxs[13] = 9;	pidxs[14] = 10;
			pidxs[15] = 10;	pidxs[16] = 11;	pidxs[17] = 8;
			pidxs[18] = 12;	pidxs[19] = 13;	pidxs[20] = 14;
			pidxs[21] = 14;pidxs[22] = 15;pidxs[23] = 12;
			pidxs[24] = 16;pidxs[25] = 17;pidxs[26] = 18;
			pidxs[27] = 18;pidxs[28] = 19;pidxs[29] = 16;
			pidxs[30] = 20;pidxs[31] = 21;pidxs[32] = 22;
			pidxs[33] = 22;pidxs[34] = 23;pidxs[35] = 20;
		}

		mesh->SetVertexBuffer(verts,CF_RGB);
		mesh->SetIndexBuffer(indices,IF_16);

		mesh->SetPrimitiveCount(12);
	}
	return MeshPtr(mesh);
}

LOPHURA_END