#include "lophura/include/voidptr.h"
#include <map>

using namespace lophura_base;
using namespace std;

BEGIN_NS_LOPHURA()

	const pair<int, size_t> g_typeinfo[] =
	{
		 pair<int,size_t>( type_encode<vec4>::id		,type_encode<vec4>::size)
		,pair<int,size_t>( type_encode<matrix44>::id	,type_encode<matrix44>::size)
	};

	const map<int,size_t> g_type_mapping(
		g_typeinfo,g_typeinfo+_countof(g_typeinfo)
	);

END_NS_LOPHURA()