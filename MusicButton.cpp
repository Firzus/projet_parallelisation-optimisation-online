#include "MusicButton.h"

MusicButton::MusicButton(RenderWindow& window) : window(window)
{
	textureMusicOn.loadFromFile("assets/icons/music_on.png");
	textureMusicOff.loadFromFile("assets/icons/music_off.png");

    spriteMusicButton.setTexture(textureMusicOn);
    spriteMusicButton.setPosition(Vector2f(444, 444));

    isMusicPlaying = true;
}

MusicButton::~MusicButton() {}

void MusicButton::Draw()
{
    window.draw(spriteMusicButton);
}

void MusicButton::HandleEvent(Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        if (spriteMusicButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            isMusicPlaying = !isMusicPlaying;
            HandleButton();
        }
    }
}

void MusicButton::HandleButton()
{
    if (isMusicPlaying)
    {
        spriteMusicButton.setTexture(textureMusicOn);
    }
    else
    {
        spriteMusicButton.setTexture(textureMusicOff);
    }
}

bool MusicButton::IsMusicPlaying()
{
    return isMusicPlaying;
}
