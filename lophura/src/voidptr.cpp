#include "lophura/include/voidptr.h"
#include "lophura/include/colors.h"
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

	color_rgba_32f operator+( const color_rgba_32f& lhs, const color_rgba_32f& rhs)
	{
		return color_rgba_32f( lhs.r + rhs.r
			,lhs.g + rhs.g
			,lhs.b + rhs.b
			,lhs.a + rhs.a);
	}

	color_rgba_32f operator-(const color_rgba_32f& lhs, const color_rgba_32f& rhs)
	{
		return color_rgba_32f(lhs.r - rhs.r
			, lhs.g - rhs.g
			, lhs.b - rhs.b
			, lhs.a - rhs.a);
	}

	color_rgba_32f operator*(const color_rgba_32f& lhs, float rhs)
	{
		return color_rgba_32f( lhs.r * rhs
			,lhs.g * rhs
			,lhs.b * rhs
			,lhs.a * rhs);
	}


END_NS_LOPHURA()