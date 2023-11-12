#include "MusicButton.h"

MusicButton::MusicButton()
{
	textureMusicOn.loadFromFile("assets/icons/music_on.png");
	textureMusicOff.loadFromFile("assets/icons/music_off.png");
}

MusicButton::~MusicButton() {}

void MusicButton::HandleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            ToggleMusic();
        }
    }
}

void MusicButton::ToggleMusic() {
    if (music.getStatus() == sf::Music::Playing) {
        music.stop();
        buttonSprite.setTexture(textureMusicOff);
    }
    else {
        music.play();
        buttonSprite.setTexture(textureMusicOn);
    }
}