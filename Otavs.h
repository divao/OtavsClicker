#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Otavs{
	public:
		Otavs();
		void InitOtavs(int, int, ALLEGRO_BITMAP *);
		void DrawOtavs();
		
		void setX(int);
		void setY(int);
		void setScale(double);
		
		int getX();
		int getY();
		int getMaxFrame();
		int getFrameWidth();
		int getFrameHeight();
		double getScale();
		
	private:
		int x;
		int y;
		
		int maxFrame;
		int frameWidth;
		int frameHeight;
		double scale;
		
		ALLEGRO_BITMAP *image;
};
