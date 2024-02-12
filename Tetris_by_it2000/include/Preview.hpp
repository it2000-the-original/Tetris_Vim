#include <array>

struct Block;
class Generator;

using namespace std;

class Preview {

private:

	// Random generator of tetrominoes
	static Generator generator;

	// Next pieces that will be loaded
	array<int, 4> nexts;

	// Drawig parameters
	static array<array<Block, 4>, 3> blocks;

	const float SC = 0.6f; // Scale of a block
	const int CX = 608;    // X position of the preview panel
	const int CY = 64;     // Y position of the preview panel
	const int CS = 96;     // Size of the area for a single tetromino

public:

	void init();
	void update();
	void draw();
	void generate();
	int get();

	int findWidth(int p);
	int findHeight(int p);
};