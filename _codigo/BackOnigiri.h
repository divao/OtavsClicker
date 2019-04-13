#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class BackOnigiri{
	public:
		BackOnigiri();
		void InitBackOnigiri(float, float, ALLEGRO_BITMAP *);
		void DrawBackOnigiri();
			
		float x;
		float y;
		
		int maxFrameX;
		int maxFrameY;
		int curFrameX;
		int curFrameY;
		int frameCountX;
		int frameCountY;
		int frameDelay;
		int frameWidth;
		int frameHeight;
	
		ALLEGRO_BITMAP *image;
};
