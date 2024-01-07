#include <array>

class Block;

class Preview {

private:

	static std::array<Block, 4> blocks;

public:

	void update();
	void draw();
};