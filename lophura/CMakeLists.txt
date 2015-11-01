LOPHURA_CHECK_BUILD_WITH_UNICODE()

set	( LOPHURAS_HOME_DIR
	${LOPHURA_HOME_DIR}/lophura
)

INCLUDE_DIRECTORIES(
	${LOPHURA_HOME_DIR}
	${LOPHURAS_HOME_DIR}
)

set	( COMMON_HEADERS
	include/colors.h
	include/format.h
	include/viewport.h
	include/lophura_declaration.h
	include/lophura_define.h
	include/lophura_forward.h
	include/voidptr.h
)

set	( PIPELINE_HEADERS
	include/pipeline.h
	include/index_fetcher.h
	include/data_addressing.h
	include/render_stages.h
	include/stream_assembler.h
)

set ( RENDER_STATE_HEADERS
	include/render_state/input_assembly_state.h
	include/render_state/input_layout.h
	include/render_state/render_state.h
)

set	( RENDER_HEADERS
	include/render.h
	include/render_imple.h
	include/syn_render.h
	include/asyn_render.h
	include/render_core.h
	include/swap_chain.h
	include/data_buffer.h
)

set ( RESOURCE_HEADERS
	include/mesh.h
	include/mesh_imple.h
)

set ( SHADER_HEADERS
	include/shader.h
	include/shader_regs.h
)

SOURCE_GROUP( "Header Files\\common" FILES
	${COMMON_HEADERS}
)

SOURCE_GROUP( "Header Files\\pipeline" FILES
	${PIPELINE_HEADERS}
)

SOURCE_GROUP( "Header Files\\render" FILES
	${RENDER_HEADERS}
)

SOURCE_GROUP( "Header Files\\render\\render_state" FILES
	${RENDER_STATE_HEADERS}
)

SOURCE_GROUP( "Header Files\\resource" FILES
	${RESOURCE_HEADERS}
)

SOURCE_GROUP( "Header Files\\shader" FILES
	${SHADER_HEADERS}
)

set	( HEADER_FILES
	${COMMON_HEADERS}
	${PIPELINE_HEADERS}
	${RENDER_HEADERS}
	${RENDER_STATE_HEADERS}
	${RESOURCE_HEADERS}
	${SHADER_HEADERS}
)

set ( COMMON_SOURCES
	src/voidptr.cpp
)

set ( PIPELINE_SOURCES
	src/pipeline.cpp
	src/index_fetcher.cpp
	src/data_addressing.cpp
	src/stream_assembler.cpp
)

set ( RENDER_STATE_SOURCES 
	src/render_state/input_assembly_state.cpp
	src/render_state/input_layout.cpp
)

set	( RENDER_SOURCES
	src/data_buffer.cpp
	src/render_imple.cpp
	src/syn_render.cpp
	src/asyn_render.cpp
	src/render_core.cpp
	src/swap_chain.cpp
)

set	( RESOURCE_SOURCES
	src/mesh.cpp
	src/mesh_imple.cpp
)

set	( SHADER_SOURCES
	src/shader.cpp
)

SOURCE_GROUP( "Header Files" )
SOURCE_GROUP( "Source Files" )

SOURCE_GROUP( "Source Files\\common" FILES
	${COMMON_SOURCES}
)

SOURCE_GROUP( "Source Files\\pipeline" FILES
	${PIPELINE_SOURCES}
)
SOURCE_GROUP( "Source Files\\render" FILES
	${RENDER_SOURCES}
)
SOURCE_GROUP( "Source Files\\render\\render_state" FILES
	${RENDER_STATE_SOURCES}
)
SOURCE_GROUP( "Source Files\\resource" FILES
	${RESOURCE_SOURCES}
)
SOURCE_GROUP( "Source Files\\shader" FILES
	${SHADER_SOURCES}
)


set (SOURCE_FILES
	${COMMON_SOURCES}
	${PIPELINE_SOURCES}
	${RENDER_SOURCES}
	${RENDER_STATE_SOURCES}
	${RESOURCE_SOURCES}
	${SHADER_SOURCES}
)

set(LIBRARY_OUTPUT_PATH ${LOPHURA_LIB_DIR})

ADD_LIBRARY( lophura STATIC
	${HEADER_FILES}
	${SOURCE_FILES}
)

TARGET_LINK_LIBRARIES(lophura lophura_base)

SET_TARGET_PROPERTIES( lophura PROPERTIES FOLDER "Render" )
