#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <array>

const std::vector<std::string> SPATHS = { // Sounds pathes

	"sounds/tetris.wav",
	"sounds/soft_drop.wav",
	"sounds/hard_drop.wav",
	"sounds/removed_line.wav",
	"sounds/game_over.wav"
};

const std::string MPATH = "sounds/music.wav"; // Music path

class Sounds {

private:

	sf::Music music;

	std::vector<sf::SoundBuffer> buffers;
	std::vector<sf::Sound> sounds;

	void loadBuffers();

public:

	void init();

	void playMusic();
	void playTetrisSound();
	void playSoftDropSound();
	void playHardDropSound();
	void playRemovedLineSound();
	void playGameOverSound();
};