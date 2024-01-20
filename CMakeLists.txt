cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Tetris_by_it2000" VERSION "0.1")

add_subdirectory ("Tetris_by_it2000")

set(Background "textures/background.png")
set(Blocks "textures/pieces.png")
set(Font "fonts/Retro Gaming.ttf")

configure_file("${PROJECT_SOURCE_DIR}/${Background}" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${Background}" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/${Blocks}" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${Blocks}" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/${Font}" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${Font}" COPYONLY)
