#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class OtavsTitle{
	public:
		OtavsTitle();
		void InitOtavsTitle(int, int, int, int, ALLEGRO_BITMAP *);
		void DrawOtavsTitle();
		
		void setX(int);
		void setY(int);
		void setCurFrame(int);
		
		int getX();
		int getY();
		int getCurFrame();
		int getFrameWidth();
		int getFrameHeight();
		
	private:
		int x;
		int y;
		
		int curFrame;
		int frameWidth;
		int frameHeight;
		
		ALLEGRO_BITMAP *image;
};
