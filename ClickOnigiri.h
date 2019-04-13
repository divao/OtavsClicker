#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class ClickOnigiri{
	public:
		ClickOnigiri();
		void InitClickOnigiri(ALLEGRO_BITMAP *);
		void DrawClickOnigiri();
		void ClickClickOnigiri(int mouseX, int mouseY);
		void UpdateClickOnigiri();
	private:
		bool live;
		int x;
		int y;
		
		int maxFrameX;
		int curFrameX;
		int frameCountX;
		int frameWidth;
	
		ALLEGRO_BITMAP *image;
};
