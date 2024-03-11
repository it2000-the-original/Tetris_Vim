#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Tetromino;
class Controls;
class Preview;
class Sounds;
class Status;
class Matrix;
class Ghost;
class Hold;

const sf::Color WColor = sf::Color(15, 15, 15, 255);
const std::string WPath = "textures/background.png"; // Wallpaper path
const std::string BPath = "textures/blocks.png";     // Blocks texture path
const std::string FPath = "fonts/Retro Gaming.ttf";  // Font path
const std::string IPath = "icon.png";                // Window icon path

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
	static sf::Font font;            // Font of the game

	static Tetromino tetromino; // Contains and manage the falling tetromino
	static Controls controls;   // Read inputs and manage controls
	static Preview preview;     // Show the next tetrominoes in the right-top panel
	static Sounds sounds;       // Play the music and sounds
	static Status status;       // Show the score, the lines and the actual level
	static Matrix matrix;       // Contains and manage the matrix of the blocks
	static Ghost ghost;         // Show the ghost tetromino during the game
	static Hold hold;           // Manage the hold function of the game

	Tetris();

	void init(const int FPS, std::string title);
	void echeck();
	void update();
	void render();

	void checkWindowSize(int _w, int _h);
	void resetView(int w, int h);
	void loadTextures();
	void loadFont();
	void loadIcon();
	bool isRunning();

	static void reset();
};