#include <string>
#include <SFML/Graphics.hpp>

class Status {

private:

	const int CX = 608; // Status panel x position
	const int CY = 416; // Status panel y position 
	const int CS = 96;  // Size of a single box in the panel

	const int TPADDING = 20;
	const int NPADDING = 55;

	const int S = 22;  // Text font size
	const int NS = 15; // Number font size

	const int LEVEL_LINES = 10; // The lines to remove to increase the level

	sf::Text scoreText;
	sf::Text levelText;
	sf::Text linesText;

	sf::Text numScoreText;
	sf::Text numLevelText;
	sf::Text numLinesText;

public:

	int score = 0;
	int level = 1;
	int lines = 0;

	void init();
	void update();
	void draw();
	void reset();
};