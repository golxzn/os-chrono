
if(NOT GXZN_GXZN_CHRONO_DEV_MODE)
	return()
endif()

if(GXZN_GXZN_CHRONO_BUILD_TEST)
	enable_testing()
	add_subdirectory(${GXZN_GXZN_CHRONO_TEST_DIR})
endif()

if(GXZN_GXZN_CHRONO_GENERATE_DOCS)
	include(${GXZN_GXZN_CHRONO_ROOT}/cmake/automatics/docs.cmake)
endif()
