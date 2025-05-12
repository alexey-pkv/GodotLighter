include(FetchContent)


set(GODOTLIGHTER_SQLIGHTER_VERSION "v0.3.0")


message(STATUS "Fetching SQLighter ${GODOTLIGHTER_SQLIGHTER_VERSION}")

FetchContent_Declare(
	sqlighter
	GIT_REPOSITORY	https://github.com/alexey-pkv/sqlighter.git
	GIT_TAG			${GODOTLIGHTER_SQLIGHTER_VERSION}
)

set(SQLIGHTER_BUILD_STATIC_LIBS ON)

FetchContent_MakeAvailable(sqlighter)
set_target_properties(sqlighter PROPERTIES POSITION_INDEPENDENT_CODE ON)
