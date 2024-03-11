cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(HIDE_CONSOLE "Use as a WIN32 application if you are on Windows" OFF)

project ("Tetris_Vim" VERSION "0.2")

add_subdirectory(${PROJECT_NAME})

configure_file("Config.h.in" "Config.h")

set(TEXTURES_DIR "textures")
set(SOUNDS_DIR "sounds")
set(FONTS_DIR "fonts")

set(EXE_ICON "icon.ico")
set(WIN_ICON "icon.png")

# Copy fonts and textures to the build directory
file(COPY "${PROJECT_SOURCE_DIR}/${TEXTURES_DIR}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
file(COPY "${PROJECT_SOURCE_DIR}/${SOUNDS_DIR}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
file(COPY "${PROJECT_SOURCE_DIR}/${FONTS_DIR}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")

file(COPY "${PROJECT_SOURCE_DIR}/${EXE_ICON}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
file(COPY "${PROJECT_SOURCE_DIR}/${WIN_ICON}" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}")
