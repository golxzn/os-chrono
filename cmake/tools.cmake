
function(golxzn_load_requires filename out)
	file(STRINGS ${filename} _requires)
	list(REMOVE_DUPLICATES _requires)
	set(${out} ${_requires} PARENT_SCOPE)
	unset(_requires)
endfunction()

function(golxzn_load_code directory headers sources)
	file(GLOB_RECURSE _headers CONFIGURE_DEPENDS "${directory}/include/*.hpp")
	file(GLOB_RECURSE _sources CONFIGURE_DEPENDS "${directory}/sources/*.cpp")
	list(LENGTH _sources _sources_count)

	if(_sources_count EQUAL 0)
		message(STATUS "Set header only flag")
		set_source_files_properties(${_headers} PROPERTIES HEADER_FILE_ONLY TRUE)
	endif()

	set(${headers} ${_headers} PARENT_SCOPE)
	set(${sources} ${_sources} PARENT_SCOPE)

	unset(_headers)
	unset(_sources)
	unset(_sources_count)
endfunction()