#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Controls;
class Preview;
class Status;
class Matrix;
class Ghost;
class Piece;
class Hold;

const sf::Color WColor = sf::Color(15, 15, 15, 255);
const std::string WPath = "textures/background.png";
const std::string BPath = "textures/pieces.png";
const std::string FPath = "fonts/Retro Gaming.ttf";
const std::string IPath = "icon.png";

const int WW = 768;  // Window Width
const int WH = 768;  // Window Height
const int PB = 32;   // Size in pixels of a single block
const int MX = 224;  // The x position in pixels where the matrix starts
const int MY = 64;   // The same thing of before but in y
const int MWW = 384; // Minimum Window Width
const int MWH = 384; // Minimum Window Height

class Tetris {

private:

	sf::Sprite background;
	sf::View WView;

public:

	static sf::RenderWindow* window; // Window of the game
	static sf::Sprite blocks;        // Blocks texture of the game
	static sf::Event event;          // Events of the window
	static sf::Time sTime;           // Step time
	static sf::Font font;            // Font of the game

	static Controls controls; // Read inputs and manage controls
	static Preview preview;   // Show the next tetrominoes in the right-top panel
	static Status status;     // Show the score, the lines and the actual level
	static Matrix matrix;     // Contains and manage the matrix of the blocks
	static Ghost ghost;       // Show the ghost piece during the game
	static Piece piece;       // Contains and manage the falling tetromino
	static Hold hold;         // Manage the hold function of the game

	Tetris();

	void init(const int FPS, std::string title);
	void echeck();
	void update();
	void render();

	void step();

	void checkWindowSize(int _w, int _h);
	void resetView(int w, int h);
	void loadTextures();
	void loadFont();
	void loadIcon();
	bool isRunning();
	void reset();
};