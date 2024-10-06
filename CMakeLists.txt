cmake_minimum_required(VERSION 3.16)

# declare project
project(boyblue)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME}
	PRIVATE
	src/main.c
)

# SDL building / linking
add_subdirectory(./libs/SDL EXCLUDE_FROM_ALL)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3)
target_compile_definitions(${EXECUTABLE_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)
