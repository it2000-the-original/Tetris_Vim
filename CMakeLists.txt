cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(HIDE_CONSOLE "Use as a WIN32 application if you are on Windows" OFF)

project ("Tetris_by_it2000" VERSION "0.2")

add_subdirectory("Tetris_by_it2000")

configure_file("Config.h.in" "Config.h")

set(TEXTURES_DIR "textures")
set(FONTS_DIR "fonts")

set(BACKGROUND "${TEXTURES_DIR}/background.png")
set(BLOCKS "${TEXTURES_DIR}/pieces.png")
set(FONT "${FONTS_DIR}/Retro Gaming.ttf")
set(EXECUTABLE_ICON "icon.ico")
set(WINDOW_ICON "icon.png")

# Copy fonts and textures to the build directory
file(COPY "${PROJECT_SOURCE_DIR}/${BACKGROUND}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${TEXTURES_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/${BLOCKS}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${TEXTURES_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/${FONT}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${FONTS_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/${EXECUTABLE_ICON}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
file(COPY "${PROJECT_SOURCE_DIR}/${WINDOW_ICON}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
