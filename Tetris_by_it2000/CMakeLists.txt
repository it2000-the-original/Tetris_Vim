find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable (Tetris "Main.cpp" "Tetris.cpp" "Matrix.cpp" "Piece.cpp" "Preview.cpp" "Ghost.cpp" "Status.cpp" "Generator.cpp" "Controls.cpp")

target_link_libraries(Tetris PRIVATE "sfml-system" "sfml-graphics" "sfml-window")

target_include_directories(Tetris PRIVATE "include" "${PROJECT_BINARY_DIR}")

# Check if use or not the executable as a WIN32 application
# to remove the console during the execution

if (WIN32 AND HIDE_CONSOLE)
	set_target_properties(Tetris PROPERTIES WIN32_EXECUTABLE TRUE)
	target_compile_definitions(Tetris PRIVATE "HIDE_CONSOLE")
	message("-- Hide console enabled")
endif(WIN32 AND HIDE_CONSOLE)

# Check if use or not the antialiasing to the font
# the font antialiansing does not work on linux and,
# for this reason I need to filter this function

if (WIN32)
	target_compile_definitions(Tetris PRIVATE "SMOTH_TEXT")
	message("-- Text Antialiasing enabled")
else (WIN32)
	message("-- Text Antialiasing disabled")
endif(WIN32)

if (CMAKE_VERSION VERSION_GREATER 3.21)
  set_property(TARGET Tetris PROPERTY CXX_STANDARD 20)
endif()
