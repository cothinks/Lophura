LOPHURA_CHECK_BUILD_WITH_UNICODE()

INCLUDE_DIRECTORIES(
	${LOPHURA_HOME_DIR}
)

set	( SOURCE_FILES
	src/colorized_triangle.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${LOPHURA_BIN_DIR})

add_executable(colorized_triangle ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(colorized_triangle sample_app)

SET_TARGET_PROPERTIES( colorized_triangle PROPERTIES FOLDER "Samples" )