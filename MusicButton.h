#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class MusicButton
{
public:
	MusicButton();
	~MusicButton();

	void HandleEvent(sf::Event& event, sf::RenderWindow& window);
	void ToggleMusic();

private:
	Texture textureMusicOn;
	Texture textureMusicOff;

	Sprite buttonSprite;
	Music music;
};