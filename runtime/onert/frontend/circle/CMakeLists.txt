if (NOT BUILD_CIRCLE_LOADER)
    return()
endif ()

set(CIRCLE_LOADER_SOURCES src/circle_loader.cc)

add_library(circle_loader STATIC ${CIRCLE_LOADER_SOURCES})
set_target_properties(circle_loader PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(circle_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(circle_loader PRIVATE onert_core)
target_link_libraries(circle_loader PRIVATE base_loader nnfw_common nnfw_coverage)
target_link_libraries(circle_loader PRIVATE circle_schema)
