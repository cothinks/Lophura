#ifndef _LOPHURA_H_
#define _LOPHURA_H_
#include <memory>

//type
#include <cstdint>

//define
enum COLOR_FORMAT
{
	CF_RGB,
	CF_RGBA
};

enum INDEX_FORMAT
{
	IF_16,
	IF_32
};

#define LOPHURA_DECLARE_PTR(OBJ) typedef std::shared_ptr<OBJ> OBJ##Ptr; 

#define LOPHURA_BEGIN	namespace Lophura {
#define LOPHURA_END		};

#define USING_LOPHURA	using namespace Lophura;

#endif