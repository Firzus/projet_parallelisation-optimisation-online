#include <SFML/Graphics.hpp>

#include <string>

using namespace sf;
using namespace std;

class ScoreIndicator
{
public:
	ScoreIndicator(RenderWindow& window);
	virtual ~ScoreIndicator();

	void Draw();
	void Update(int scoreP1, int scoreP2);

private:
	RenderWindow& window;

	Font fontRegular;
	Text textScoreP1;
	Text textScoreP2;

	Texture textureX, textureO;
	Sprite spriteX, spriteO;
};
