function(define_demo_target)
	if (UNIX)
		set(LIB_NAME libgodotlighter)
		set(LIB_EXT so)
	elseif(WIN32)
		set(LIB_NAME godotlighter)
		set(LIB_EXT dll)
	endif ()
	
	file(GLOB DEMO_DIRS
		"${CMAKE_SOURCE_DIR}/demos/*/*")
	
	set(FROM_FILE_EXT "${GODOTLIGHTER_OUT}/godotlighter.gdextension")
	
	
	foreach (DEMO_DIR ${DEMO_DIRS})
		MESSAGE(STATUS "Demo folder: ${DEMO_DIR}")
		
		
		set(FROM_FILE_LIB "${GODOTLIGHTER_OUT}/${LIB_NAME}.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64.${LIB_EXT}")
		set(TO_FOLDER "${DEMO_DIR}/bin")
		
		
		add_custom_command(
			TARGET godotlighter POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${FROM_FILE_LIB}" "${TO_FOLDER}"
			
			COMMENT "Copying the library file to ${TO_FOLDER}"
		)
		
		add_custom_command(
			TARGET godotlighter POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${FROM_FILE_EXT}" "${TO_FOLDER}"

			COMMENT "Copying the .gdextension file to ${TO_FOLDER}"
		)
	endforeach ()
endfunction()
