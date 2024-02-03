cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(HIDE_CONSOLE "Use as a WIN32 application if you are on Windows" OFF)

project ("Tetris_by_it2000" VERSION "0.2")

add_subdirectory ("Tetris_by_it2000")

configure_file("Config.h.in" "Config.h")

set(TexturesDir "textures")
set(FontsDir "fonts")

set(Background "${TexturesDir}/background.png")
set(Blocks "${TexturesDir}/pieces.png")
set(Font "${FontsDir}/Retro Gaming.ttf")

# Copy fonts and textures to the build directory
file(COPY "${PROJECT_SOURCE_DIR}/${Background}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${TexturesDir}")
file(COPY "${PROJECT_SOURCE_DIR}/${Blocks}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${TexturesDir}")
file(COPY "${PROJECT_SOURCE_DIR}/${Font}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${FontsDir}")
