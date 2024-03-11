find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Set the resource file if we are on Windows

if (WIN32)
	set(RESOURCE "../Resource.rc")
endif(WIN32)

add_executable(tvim ${RESOURCE} 
	"Main.cpp"
	"Hold.cpp" 
	"Ghost.cpp" 
	"Status.cpp" 
	"Tetris.cpp"
	"Sounds.cpp"
	"Matrix.cpp"
	"Preview.cpp" 
	"Controls.cpp" 
	"Generator.cpp" 
	"Tetromino.cpp" 
)

target_link_libraries(tvim PRIVATE "sfml-system" "sfml-graphics" "sfml-window" "sfml-audio")

target_include_directories(tvim PRIVATE "include" "${PROJECT_BINARY_DIR}")

# Check if use or not the executable as a WIN32 application
# to remove the console during the execution

if (WIN32 AND HIDE_CONSOLE)
	set_target_properties(tvim PROPERTIES WIN32_EXECUTABLE TRUE)
	target_compile_definitions(tvim PRIVATE "HIDE_CONSOLE")
	message("-- Hide console enabled")

endif(WIN32 AND HIDE_CONSOLE)

# Check if use or not the antialiasing to the font
# the font antialiansing does not work on linux and,
# for this reason I need to filter this function

if (WIN32)
	target_compile_definitions(tvim PRIVATE "SMOTH_TEXT")
	message("-- Text Antialiasing enabled")
else (WIN32)
	message("-- Text Antialiasing disabled")
endif(WIN32)

if (CMAKE_VERSION VERSION_GREATER 3.21)
  set_property(TARGET tvim PROPERTY CXX_STANDARD 20)
endif()
