# Adding sfml packages...
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable (Tetris "Main.cpp"  "Tetris.cpp" "Matrix.cpp" "Piece.cpp" "Nexts.cpp" "include/Preview.hpp" "Preview.cpp" "Status.cpp")

# Linking sfml libraries
target_link_libraries(Tetris PRIVATE "sfml-system" "sfml-graphics" "sfml-window")

# Adding additional include directories
target_include_directories(Tetris PRIVATE "include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tetris PROPERTY CXX_STANDARD 20)
endif()
