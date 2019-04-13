#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Creditos{
	public:
		Creditos();
		void InitCreditos(ALLEGRO_BITMAP *);
		void DrawCreditos();
		void ReadyCreditos();
		void UpdateCreditos();
		bool getForaDaTela();
		
	private:
		bool foraDaTela;
		bool live;
		int x;
		int y;
		int yFinal;
		
		ALLEGRO_BITMAP *image;
};
