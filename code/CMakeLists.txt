cmake_minimum_required(VERSION 3.25)

if (GXZN_CHRONO_GENERATE_INFO_HEADER)
	include(TargetInfoHeader)
	make_target_info_header(
		TARGET golxzn_os_chrono
		OUTPUT_PATH ${GXZN_CHRONO_CODE_DIR}/headers/golxzn
		FILENAME chrono_about
		NAMESPACE golxzn::about
		PARAMETERS
			APP_NAME "golxzn.os.chrono"
			APP_VERSION "${PROJECT_VERSION}"
			APP_DESCRIPTION "${PROJECT_DESCRIPTION}"
	)
endif()

file(GLOB_RECURSE headers RELATIVE ${GXZN_CHRONO_CODE_DIR} CONFIGURE_DEPENDS "*.hpp")
file(GLOB_RECURSE sources RELATIVE ${GXZN_CHRONO_CODE_DIR} CONFIGURE_DEPENDS "*.cpp")

source_group(TREE ${GXZN_CHRONO_CODE_DIR}/headers FILES ${headers})
source_group(TREE ${GXZN_CHRONO_CODE_DIR}/sources FILES ${sources})

add_library(golxzn_os_chrono STATIC ${headers} ${sources})
add_library(golxzn::os::chrono ALIAS golxzn_os_chrono)

if(GXZN_CHRONO_REQUIRES)
	target_link_libraries(golxzn_os_chrono PUBLIC ${GXZN_CHRONO_REQUIRES})
endif()

target_include_directories(golxzn_os_chrono PUBLIC ${GXZN_CHRONO_CODE_DIR}/headers)
target_compile_definitions(golxzn_os_chrono PUBLIC ${GXZN_CHRONO_DEFINITIONS})
set_target_properties(golxzn_os_chrono PROPERTIES
	FOLDER "golxzn/os"
)
