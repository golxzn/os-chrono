cmake_minimum_required(VERSION 3.25)
set(gxzn_chrono_root ${CMAKE_CURRENT_SOURCE_DIR})

project(golxzn::os::chrono
	VERSION 1.0.0
	DESCRIPTION "Chrono for golxzn's projects."
	LANGUAGES CXX
	HOMEPAGE_URL https://github.com/golxzn/os-chrono.git
)

include(${gxzn_chrono_root}/cmake/options.cmake)
include(${gxzn_chrono_root}/cmake/tools.cmake)

golxzn_load_requires(${gxzn_chrono_root}/grequires gxzn_chrono_requires)
golxzn_load_code(${gxzn_chrono_root}/code gxzn_chrono_headers gxzn_chrono_sources)
list(LENGTH gxzn_chrono_sources gxzn_chrono_sources_count)

add_library(golxzn_os_chrono STATIC ${gxzn_chrono_headers} ${gxzn_chrono_sources})
add_library(golxzn::os::chrono ALIAS golxzn_os_chrono)

target_link_libraries(golxzn_os_chrono PUBLIC ${gxzn_chrono_requires})
set_target_properties(golxzn_os_chrono PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS ON

	UNITY_BUILD ON
	UNITY_BUILD_BATCH_SIZE ${gxzn_chrono_sources_count}
	FOLDER "golxzn/os"
)
target_compile_definitions(golxzn_os_chrono PUBLIC GOLXZN_OS_CHRONO ${GOLXZN_CONFIG_DEFINITIONS})
target_include_directories(golxzn_os_chrono PUBLIC ${gxzn_chrono_root}/code/include)

unset(gxzn_chrono_sources)
unset(gxzn_chrono_headers)
unset(gxzn_chrono_sources_count)
unset(gxzn_chrono_lib_visability)
