#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Melhoria{
	public:
		Melhoria();
		void InitMelhoria(int, int, int, int, ALLEGRO_BITMAP *);
		void DrawMelhoria();
		
		void setX(int);
		void setY(int);
		void setCurFrame(int);
		void setLive(bool);
		void setJorge(bool);
		
		int getX();
		int getY();
		int getCurFrame();
		int getFrameWidth();
		int getFrameHeight();
		int getCusto();
		bool isLive();
		bool isJorge();
		
		bool operator!=(const Melhoria &) const;
		bool operator==(const Melhoria &) const;
		
	private:
		int id;
		int x;
		int y;
		int custo;
		bool live;
		bool jorge;
		
		int curFrame;
		int maxFrame;
		int frameWidth;
		int frameHeight;
		
		ALLEGRO_BITMAP *image;
};
