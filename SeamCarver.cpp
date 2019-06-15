#include "pch.h"

class SeamCarver
{
private:
	int ** bitmap;
public:

	int width()
	{
		
	}
	int height()
	{

	}
	inline int red(int pixel)
	{
		return (pixel & 0xff0000) >> 16;
	}
	inline int green(int pixel)
	{
		return (pixel & 0xff00) >> 8;
	}
	inline int blue(int pixel)
	{
		return (pixel & 0xff) >> 0;
	}
	double energy(int x, int y)
	{
		// is this an border?
		if (x == this->width() - 1 || x == 0 ||
			y == this->height() - 1 || y == 0)
		{
			return 1000;
		}
		// nope, let's find the x delta
		int deltaRedX = abs(red(this->bitmap[x+1][y]) - red(this->bitmap[x - 1][y]));
		int deltaGreenX = abs(green(this->bitmap[x + 1][y]) - green(this->bitmap[x - 1][y]));
		int deltaBlueX = abs(blue(this->bitmap[x + 1][y]) - blue(this->bitmap[x - 1][y]));
		double deltaX2 = (deltaRedX*deltaRedX) + (deltaGreenX*deltaGreenX) + (deltaBlueX*deltaBlueX);
		// and the y delta
		int deltaRedY = abs(red(this->bitmap[x][y+1]) - red(this->bitmap[x][y-1]));
		int deltaGreenY = abs(green(this->bitmap[x][y+1]) - green(this->bitmap[x][y-1]));
		int deltaBlueY = abs(blue(this->bitmap[x][y+1]) - blue(this->bitmap[x][y-1]));
		double deltaY2 = (deltaRedX*deltaRedX) + (deltaGreenX*deltaGreenX) + (deltaBlueX*deltaBlueX);
		// now the energy is the sqrt of those 
		return sqrt(deltaX2 + deltaY2);
	}
};