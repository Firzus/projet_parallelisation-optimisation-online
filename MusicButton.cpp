#include "MusicButton.h"
#include <iostream>

MusicButton::MusicButton(RenderWindow& window) : window(window)
{
	textureMusicOn.loadFromFile("assets/icons/music_on.png");
	textureMusicOff.loadFromFile("assets/icons/music_off.png");

    spriteButton.setTexture(textureMusicOn);
    spriteButton.setPosition(Vector2f(444, 444));

    isMusicPlaying = true;
}

MusicButton::~MusicButton() {}

void MusicButton::Draw()
{
    window.draw(spriteButton);
}

void MusicButton::HandleEvent(Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        if (spriteButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            isMusicPlaying = !isMusicPlaying;
            HandleButton();
        }
    }
}

void MusicButton::HandleButton()
{
    if (isMusicPlaying)
    {
        spriteButton.setTexture(textureMusicOn);
    }
    else
    {
        spriteButton.setTexture(textureMusicOff);
    }
}

bool MusicButton::IsMusicPlaying()
{
    return isMusicPlaying;
}
