#include <SFML/Graphics.hpp>
#include <array>

struct Block;

class Hold {

private:

	int tetromino;

	const int S = 22;      // Text size
	const int PX = 64;     // X position of the Hold panel
	const int PY = 64;     // Y position of the Hold panel
	const int PW = 96;     // Width of the Hold panel
	const int TH = 32;     // Height of the text area;
	const float SC = 0.6f; // Scale of the blocks;

	std::array<Block, 4> blocks;

	sf::Text holdText;

public:

	void init();
	void update();
	void draw();
	
	int get();
	void set(int t);
};