#include "Grid.h"

Grid::Grid(RenderWindow& window) : window(window)
{
    horizontalLine1.setSize(Vector2f(lineLength, lineThickness));
    horizontalLine2.setSize(Vector2f(lineLength, lineThickness));

    horizontalLine1.setPosition(100, 198);
    horizontalLine2.setPosition(100, 298);

    verticalLine1.setSize(Vector2f(lineThickness, lineLength));
    verticalLine2.setSize(Vector2f(lineThickness, lineLength));

    verticalLine1.setPosition(198, 100);
    verticalLine2.setPosition(298, 100);

    horizontalLine1.setFillColor(Color(133, 94, 194));
    horizontalLine2.setFillColor(Color(133, 94, 194));
    verticalLine1.setFillColor(Color(133, 94, 194));
    verticalLine2.setFillColor(Color(133, 94, 194));
}

Grid::~Grid() {}

void Grid::Draw()
{
    window.draw(horizontalLine1);
    window.draw(horizontalLine2);
    window.draw(verticalLine1);
    window.draw(verticalLine2);
}