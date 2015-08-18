LOPHURA_CHECK_BUILD_WITH_UNICODE()

set ( LOPHURA_BASE_HOME_DIR
	${LOPHURA_HOME_DIR}/lophura_base
)


INCLUDE_DIRECTORIES(
	${LOPHURA_HOME_DIR}
	${LOPHURA_BASE_HOME_DIR}
)

set ( MATH_HEADERS
	include/math/math.h
	include/math/matrix.h
	include/math/vector.h
)

set ( MEMORY_HEADERS
	include/memory/bounded_buffer.h
)

set	( PLATFORM_HEADERS
	include/platform/constant.h
	include/platform/typedefs.h
)

set ( UTILITY_HEADERS
	include/utility/shared_declaration.h
)

SOURCE_GROUP( "Header Files\\math" FILES
	${MATH_HEADERS}
)

SOURCE_GROUP( "Header Files\\memory" FILES
	${MEMORY_HEADERS}
)

SOURCE_GROUP( "Header Files\\platform" FILES
	${PLATFORM_HEADERS}
)

SOURCE_GROUP( "Header Files\\utility" FILES
	${UTILITY_HEADERS}
)

set (HEADER_FILES
	${MATH_HEADERS}
	${MEMORY_HEADERS}
	${PLATFORM_HEADERS}
	${UTILITY_HEADERS}
)

set (SOURCE_FILES
	src/math.cpp
)

SOURCE_GROUP( "Header Files" )
SOURCE_GROUP( "Source Files" )

set(LIBRARY_OUTPUT_PATH ${LOPHURA_LIB_DIR})

ADD_LIBRARY(lophura_base STATIC ${HEADER_FILES} ${SOURCE_FILES})

SET_TARGET_PROPERTIES( lophura_base PROPERTIES FOLDER "Render" )

