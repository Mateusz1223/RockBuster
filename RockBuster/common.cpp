#include "common.h"

void initCommon()
{
	srand(time(NULL));
}

int randInRange(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

bool rectCircleCollision(const sf::FloatRect rect, const sf::FloatRect circle)
{
	if (rect.intersects(circle))
	{
		if (circle.left + circle.width / 2 > rect.left && circle.left + circle.width / 2 < rect.left + rect.width)
			return true;

		if (circle.top + circle.height / 2 > rect.top && circle.top + circle.height / 2 < rect.top + rect.height)
			return true;

		float deltaX, deltaY, Z;

		if(circle.top + circle.height / 2 > rect.top + rect.height)
			deltaY = circle.top + circle.height / 2 - (rect.top + rect.height);
		else
			deltaY = rect.top - (circle.top + circle.height / 2);
		
		if (circle.left + circle.width / 2 < rect.left) // circle on the left of rectangle
			deltaX = rect.left - (circle.left + circle.width / 2);
		else // circle on the right of rectangle
			deltaX = circle.left + circle.width / 2 - (rect.left + rect.width);

		Z = static_cast <float> (sqrt(static_cast <double> (deltaX*deltaX + deltaY*deltaY)));

		if (Z < circle.width/2) // circle.width / 2 as a radius of circle
			return true;
	}

	return false;
}
