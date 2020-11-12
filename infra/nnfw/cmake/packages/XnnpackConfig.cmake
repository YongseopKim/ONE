function(_Xnnpack_Build)
  nnas_find_package(XnnpackSource QUIET)

  # NOTE This line prevents multiple definitions of cpuinfo target
  if(TARGET xnnpack)
    set(XnnpackSource_DIR ${XnnpackSource_DIR} PARENT_SCOPE)
    set(Xnnpack_FOUND TRUE PARENT_SCOPE)
    return()
  endif(TARGET xnnpack)

  if(NOT XnnpackSource_FOUND)
    message(STATUS "XNNPACK: Source not found")
    set(Xnnpack_FOUND FALSE PARENT_SCOPE)
    return()
  endif(NOT XnnpackSource_FOUND)

  set(XNNPACK_BUILD_TESTS OFF CACHE BOOL "Build XNNPACK unit tests")
  set(XNNPACK_BUILD_BENCHMARKS OFF CACHE BOOL "Build XNNPACK benchmarks")
  set(XNNPACK_USE_SYSTEM_LIBS ON CACHE BOOL "Use system-provided dependency libraries")

  add_extdirectory("${XnnpackSource_DIR}" XNNPACK EXCLUDE_FROM_ALL)
  set_target_properties(XNNPACK PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set(XnnpackSource_DIR ${XnnpackSource_DIR} PARENT_SCOPE)
  set(Xnnpack_FOUND TRUE PARENT_SCOPE)
endfunction(_Xnnpack_Build)

if(BUILD_XNNPACK)
  _Xnnpack_Build()
else(BUILD_XNNPACK)
  set(Xnnpack_FOUND FALSE)
endif(BUILD_XNNPACK)
