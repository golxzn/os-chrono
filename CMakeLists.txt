cmake_minimum_required(VERSION 3.25)

set(GXZN_GXZN_CHRONO_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

project(golxzn.os.chrono
	VERSION 1.2.1
	DESCRIPTION "Chrono for golxzn's projects."
	LANGUAGES CXX
	HOMEPAGE_URL https://github.com/golxzn/os-chrono.git
)

include(${GXZN_GXZN_CHRONO_ROOT}/cmake/options.cmake)
include(${GXZN_GXZN_CHRONO_ROOT}/cmake/definitions.cmake)

add_subdirectory(${GXZN_GXZN_CHRONO_CODE_DIR})

include(${GXZN_GXZN_CHRONO_ROOT}/cmake/dev-mode.cmake)
