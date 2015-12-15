#pragma once

#include <stdint.h>
#include <string>

namespace lophura_base
{

#ifdef _UNICODE
	typedef std::wstring	kstring;
#else
	typedef std::string		kstring;
#endif
	typedef uint8_t			byte;
};