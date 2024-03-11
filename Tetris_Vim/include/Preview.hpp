#include <array>

struct Block;
class Generator;

using Tetrominos = std::array<Blocks, 3>;

class Preview {

private:

	std::array<int, 4> next; // Next tetrominoes that will be loaded

	static Tetrominos tetrominos; // Blocks of the tetrominos that will be loaded
	static Generator generator;   // Random generator of tetrominoes

	const float SC = 0.6f; // Scale of a block
	const int PX = 608;    // X position of the preview panel
	const int PY = 64;     // Y position of the preview panel
	const int PS = 96;     // Size of the area for a single tetromino

public:

	void init();
	void update();
	void draw();

	void generate();
	int get();
};