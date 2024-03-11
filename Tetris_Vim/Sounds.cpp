#include "Sounds.hpp"
#include "Tetris.hpp"

using namespace sf;

void Sounds::init() {

	loadBuffers();

	for (auto& buffer : buffers) {

		Sound sound;
		sound.setBuffer(buffer);
		sounds.push_back(sound);
	}

	music.openFromFile(MPATH);
}

void Sounds::playMusic() {

	music.play();
	music.setLoop(true);
}

void Sounds::playTetrisSound() {

	sounds[0].play();
}

void Sounds::playSoftDropSound() {

	sounds[1].play();
}

void Sounds::playHardDropSound() {

	sounds[2].play();
}

void Sounds::playRemovedLineSound() {

	sounds[3].play();
}

void Sounds::playGameOverSound() {

	sounds[4].play();
}

void Sounds::loadBuffers() {

	for (int i = 0; i < SPATHS.size(); i++) {

		SoundBuffer buffer;

		if (!buffer.loadFromFile(SPATHS[i])) {

			Tetris::window->close();
		}

		buffers.push_back(buffer);
	}
}