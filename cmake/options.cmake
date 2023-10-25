
set(USE_FOLDERS ON)
set(CMAKE_REQUIRED_QUIET ON)

list(APPEND CMAKE_MODULE_PATH
	${GXZN_CHRONO_ROOT}/cmake
	${GXZN_CHRONO_ROOT}/cmake/tools
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(GXZN_CHRONO_IS_TOPLEVEL_PROJECT TRUE)
else()
	set(GXZN_CHRONO_IS_TOPLEVEL_PROJECT FALSE)
endif()

option(GXZN_CHRONO_SHOW_SUBMODULE_INFO   "Show submodule info"        ${GXZN_CHRONO_IS_TOPLEVEL_PROJECT})
option(GXZN_CHRONO_MULTITHREADING_SUPPORT "Multithreading support"    ON)
option(GXZN_CHRONO_BUILD_TEST           "Build chrono's tests"        ${GXZN_CHRONO_IS_TOPLEVEL_PROJECT})
option(GXZN_CHRONO_DEV_MODE             "Developer mode"              ${GXZN_CHRONO_IS_TOPLEVEL_PROJECT})
option(GXZN_CHRONO_GENERATE_INFO_HEADER "Generate info header"        OFF)
option(GXZN_CHRONO_GENERATE_DOCS        "Generate MCSS documentation" OFF)
mark_as_advanced(GXZN_CHRONO_DEV_MODE GXZN_CHRONO_GENERATE_INFO_HEADER GXZN_CHRONO_GENERATE_DOCS)

include(GetSystemInfo)

get_system_info(GXZN_CHRONO_SYSTEM GXZN_CHRONO_ARCH)

set(GXZN_CHRONO_OUTPUT_DIRECTORY ${GXZN_CHRONO_ROOT}/bin CACHE PATH "Output directory")
set(GXZN_CHRONO_CODE_DIR ${GXZN_CHRONO_ROOT}/code  CACHE PATH "Code directory")
set(GXZN_CHRONO_TEST_DIR ${GXZN_CHRONO_ROOT}/tests CACHE PATH "Tests directory")
set(GXZN_CHRONO_DOCS_DIR ${GXZN_CHRONO_ROOT}/docs  CACHE PATH "Documentation directory")
set(GXZN_CHRONO_DOCS_PROJECT_NAME "⏱️ golxzn::os::chrono ⏱️")

# App info
set(GXZN_CHRONO_APP_AUTHOR         "Ruslan Golovinskii")

if (NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_CXX_STANDARD LESS 17)
	message(FATAL_ERROR "CMAKE_CXX_STANDARD must be at least 17")
endif()

if (GXZN_CHRONO_SHOW_SUBMODULE_INFO)
	message(STATUS "-- -- -- -- -- -- -- chrono configuration -- -- -- -- -- -- -- --")
	message(STATUS "System:                 ${GXZN_CHRONO_SYSTEM} (${GXZN_CHRONO_ARCH})")
	message(STATUS "C++ Standard:           ${CMAKE_CXX_STANDARD}")
	message(STATUS "C Standard:             ${CMAKE_C_STANDARD}")
	message(STATUS "Compiler (ID):          ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_ID})")
	message(STATUS "Root directory:         ${GXZN_CHRONO_ROOT}")
	message(STATUS "Output directory:       ${GXZN_CHRONO_OUTPUT_DIRECTORY}")
	message(STATUS "Code directory:         ${GXZN_CHRONO_CODE_DIR}")
	message(STATUS "Top level:              ${GXZN_CHRONO_IS_TOPLEVEL_PROJECT}")

	if(GXZN_CHRONO_DEV_MODE)
		message(STATUS "Tests:                  ${GXZN_CHRONO_BUILD_TEST}")
		message(STATUS "Generate info header:   ${GXZN_CHRONO_GENERATE_INFO_HEADER}")
		message(STATUS "Generate documentation: ${GXZN_CHRONO_GENERATE_DOCS}")
		message(STATUS "Documentation directory:${GXZN_CHRONO_DOCS_DIR}")
	endif()

	message(STATUS "-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --")
endif()

find_program(ccache_program ccache)
if (NOT ${ccache_program} MATCHES "NOTFOUND")
	set(CMAKE_C_COMPILER_LAUNCHER ccache)
	set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

include(GolxznLoadRequires)

golxzn_load_requires(${GXZN_CHRONO_ROOT}/grequires GXZN_CHRONO_REQUIRES)

# @todo: Enable this when we'll finish golxzn::os::multithreading repository
# if (GXZN_CHRONO_MULTITHREADING_SUPPORT)
# 	list(APPEND GXZN_CHRONO_REQUIRES golxzn::os::multithreading)
# endif()

if(GXZN_CHRONO_DEV_MODE)
	foreach(_require IN LISTS GXZN_CHRONO_REQUIRES)
		golxzn_fetch(${_require})
	endforeach()
endif()
