#include <array>

using Blocks = std::array<Block, 4>;

struct Block;

class Ghost {

private:

	static Blocks blocks;

public:

	void update();
	void draw();
};