#include <array>

class Block;
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
	const int CX = 459;
	const int CY = 64;
	const int CS = 96;

public:

	void init();
	void update();
	void draw();
	void generate();
	int get();

	int findWidth(int p);
	int findHeight(int p);
};