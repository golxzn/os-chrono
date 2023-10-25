
if(NOT GXZN_CHRONO_BUILD_TEST)
	return()
endif()

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

message(CHECK_START "Fetching Catch2...")
FetchContent_Declare(Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.3.2
)

FetchContent_MakeAvailable(Catch2)
message(CHECK_PASS "Catch2 fetched")

include(CTest)
include(Catch)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${GXZN_CHRONO_TEST_DIR}/code/*.cpp")

foreach(file IN LISTS sources)
	get_filename_component(file_name ${file} NAME_WE)
	add_executable(${file_name} ${sources})
	target_link_libraries(${file_name} PRIVATE
		golxzn::os::chrono
		Catch2::Catch2WithMain
	)
	set_target_properties(${file_name} PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${GXZN_CHRONO_OUTPUT_DIRECTORY}
		RUNTIME_OUTPUT_DIRECTORY ${GXZN_CHRONO_OUTPUT_DIRECTORY}
		ARCHIVE_OUTPUT_DIRECTORY ${GXZN_CHRONO_OUTPUT_DIRECTORY}

		FOLDER "golxzn/tests/${file_name}"
	)
	add_test(NAME ${file_name} COMMAND ${file_name}
		WORKING_DIRECTORY ${GXZN_CHRONO_OUTPUT_DIRECTORY}
	)
endforeach()
