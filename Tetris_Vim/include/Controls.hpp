#include <SFML/Window.hpp>

const int MOVES = 15; // Max moves

class Controls {

private:

	const sf::Time dTime  = sf::seconds(0.03f);
	const sf::Time rTime  = sf::seconds(0.08f);
	const sf::Time lTime  = sf::seconds(0.08f);
	const sf::Time prTime = sf::seconds(0.15f);
	const sf::Time plTime = sf::seconds(0.15f);

	// Clocks for various actions

	sf::Clock sclock;  // Step
	sf::Clock dclock;  // Move down
	sf::Clock rclock;  // Move right
	sf::Clock lclock;  // Move left
	sf::Clock prclock; // Pre-move right
	sf::Clock plclock; // Pre-move left

	bool rmoved  = false; // Is the first execution of the moveRight function?
	bool lmoved  = false; // Is the first execution of the moveLeft function?
	bool rotated = false; // Already rotated?
	bool dropped = false; // Already dropped?
	bool skClock = false; // Skip the sclock?
	bool holdEnb = true;  // Is the hold function enabled?
	
	int moves = 0; // Number of moves

	void moveRight();
	void moveLeft();
	void moveDown();
	void rotate();
	void drop();
	void hold();

	void _checkHorizontalMoves();
	void _resetRightMove();
	void _resetLeftMove();
	void _checkLookDown();

	// Input checking functions

	bool _checkSpaceInputs();
	bool _checkRightInputs();
	bool _checkLeftInputs();
	bool _checkDownInputs();
	bool _checkHoldInputs();
	bool _checkUpInputs();

public:

	void checkInputs();
	bool isStepReady();
	void enableHold();
	void resetStep();
	bool lookDown();
};
