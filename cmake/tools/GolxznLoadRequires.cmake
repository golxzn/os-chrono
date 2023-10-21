
function(golxzn_load_requires filename out)
	if (EXISTS ${filename})
		file(STRINGS ${filename} _requires)
		list(REMOVE_DUPLICATES _requires)
		set(${out} ${_requires} PARENT_SCOPE)
		unset(_requires)
	endif()
endfunction()

function(golxzn_fetch target)
	include(FetchContent)

	string(REPLACE "::" ";" splitted_require ${target})
	list(POP_BACK splitted_require submodule)
	list(POP_BACK splitted_require module)

	message(STATUS "Fetching ${target}")
	FetchContent_Declare(${module}.${submodule}
		GIT_REPOSITORY https://github.com/golxzn/${module}-${submodule}.git
		GIT_TAG        main
	)
	FetchContent_MakeAvailable(${module}.${submodule})
endfunction()
