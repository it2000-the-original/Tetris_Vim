#include <array>

struct Block;

class Ghost {

private:

	static std::array<Block, 4> blocks;

public:

	void update();
	void draw();
};