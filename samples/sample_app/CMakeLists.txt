LOPHURA_CHECK_BUILD_WITH_UNICODE()

INCLUDE_DIRECTORIES(
	${LOPHURA_HOME_DIR}
)

set	( WINDOW_HEADERS
	include/window/window.h
	include/window/native_window.h
)

SOURCE_GROUP( "Header Files\\window" FILES
	${WINDOW_HEADERS}
)

set	( HEADER_FILES
	${WINDOW_HEADERS}
)

set	( WINDOW_SOURCES
	src/window/window.cpp
	src/window/native_window.cpp
	src/window/ms_window.cpp
)

SOURCE_GROUP( "Source Files\\window" FILES
	${WINDOW_SOURCES}
)

set	( SOURCE_FILES
	${WINDOW_SOURCES}
)

SOURCE_GROUP( "Header Files" )
SOURCE_GROUP( "Source Files" )

set(LIBRARY_OUTPUT_PATH ${LOPHURA_LIB_DIR})

ADD_LIBRARY(sample_app STATIC ${HEADER_FILES} ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(sample_app lophura)

SET_TARGET_PROPERTIES( sample_app PROPERTIES FOLDER "Samples" )
