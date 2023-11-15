#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class MusicButton
{
public:
	MusicButton(RenderWindow& window);
	~MusicButton();

	void Draw();
	void HandleEvent(Event& event);
	void HandleButton();
	bool IsMusicPlaying();

private:
	RenderWindow& window;

	Texture textureMusicOn;
	Texture textureMusicOff;

	Sprite spriteMusicButton;

	bool isMusicPlaying;
};