include(FetchContent)


set(GODOTLIGHTER_SQLIGHTER_VERISON "v0.3.0")


message(STATUS "Fetching SQLighter ${GODOTLIGHTER_SQLIGHTER_VERISON}")

FetchContent_Declare(
	sqlighter
	GIT_REPOSITORY	https://github.com/alexey-pkv/sqlighter.git
	GIT_TAG			${GODOTLIGHTER_SQLIGHTER_VERISON}
)

set(SQLIGHTER_BUILD_STATIC_LIBS ON)

FetchContent_MakeAvailable(sqlighter)
set_target_properties(sqlighter PROPERTIES POSITION_INDEPENDENT_CODE ON)