#include <SFML/Graphics.hpp>

using namespace sf;

class ScoreIndicator
{
public:
	ScoreIndicator(RenderWindow& window);
	virtual ~ScoreIndicator();

	void Draw();
	void HandleEvent(Event& event);
	void Update();

private:
	RenderWindow& window;

	Font fontRegular;
	Text textScorePlayer;

	Texture textureX, textureO;
	Sprite spriteX, spriteO;
};
