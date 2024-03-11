#include <string>
#include <SFML/Graphics.hpp>

class Status {

private:

	const int PX = 608; // Status panel x position
	const int PY = 416; // Status panel y position 
	const int PS = 96;  // Size of a single box in the panel

	const int TPADDING = 20;
	const int NPADDING = 55;

	const int TS = 22; // Text font size
	const int NS = 15; // Number font size

	const int LEVEL_LINES = 10; // The lines to remove to increase the level

	sf::Text scoreText;
	sf::Text levelText;
	sf::Text linesText;

	sf::Text scoreNumber;
	sf::Text levelNumber;
	sf::Text linesNumber;

	// For all texts

	void _setFont();
	void _setFontSize();
	void _setFontColor();
	void _setPositions();

public:

	int score = 0;
	int level = 1;
	int lines = 0;

	void init();
	void update();
	void draw();
	void reset();
};