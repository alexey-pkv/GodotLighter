message(STATUS "Moving ${CMAKE_SOURCE_DIR}/resources/godotlighter.gdextension to ${GODOTLIGHTER_OUT}/godotlighter.gdextension")


configure_file(
	"${CMAKE_SOURCE_DIR}/resources/godotlighter.gdextension"
	"${GODOTLIGHTER_OUT}/godotlighter.gdextension"
	@ONLY
)