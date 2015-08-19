#pragma once

#include <stdint.h>
#include <string>

#ifdef _UNICODE
	typedef std::wstring	kstring;
#else
	typedef std::string		kstring;
#endif

