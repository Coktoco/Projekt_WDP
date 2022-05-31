#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <ctime>

struct Gracz { //punkty i zycie gracza
	int pkt = 0;
	int zycia = 3;
};

struct Przeciwnik { //wspolrzedne przeciwnika
	int dx = 800;
	int dy = 0;
};

bool zderzenie(struct Przeciwnik p, int x, int y) { //sprawdza czy bylo zderzenie z konkretnym przeciwnikiem
	if ((x + 80 > p.dx && x + 80 < p.dx + 160) && (y + 80 > p.dy && y + 80 < p.dy + 160))
		return true;
	else
		return false;
}

int losuj_dy() { //losuje wspolrzedna w pionie wrogow, zeby pojawiali sie na roznych wysokosciach
	int dy = rand() % (480-160);
	return dy;
}

int main()
{
	struct Gracz player; //tworzymy strukture na punkty i zycie gracza
	//tworzymy trzech wrogow
	struct Przeciwnik enemy1;
	struct Przeciwnik enemy2;
	struct Przeciwnik enemy3;

	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(800, 440);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_BITMAP* background = al_load_bitmap("background1.png");
	ALLEGRO_BITMAP* jetpack = al_load_bitmap("jetpackman.png");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));


	int xb1 = 0;
	int xb2 = 800;

	bool redraw = true;
	bool done = false;
	ALLEGRO_EVENT event;
	int x = 0, y = 0; //wspolrzedne gracza
	int vx = 10, vy = 10; //predkosc gracza
	int vdx = 10; //predkosc w poziomie wrogow
	int counter = 0; //licznik fps
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	srand(time(0));

	if (!al_init_image_addon())
	{
		printf("Addon nie dziala!\n");
		return 1;
	}

	if (!jetpack)
	{
		printf("Nie udalo sie zaladowac zdjecia!\n");
		return 1;
	}

	al_start_timer(timer);
	while (1) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			if (key[ALLEGRO_KEY_UP])
				y -= vy;
			if (key[ALLEGRO_KEY_DOWN])
				y += vy;
			if (key[ALLEGRO_KEY_RIGHT])
				x += vx;
			if (key[ALLEGRO_KEY_LEFT])
				x -= vx;
			if (key[ALLEGRO_KEY_ESCAPE])
				done = true;

			//jesli wrog wyszedl za lewa krawedz mapy to spawnuje sie z powrotem z prawej strony
			if (enemy1.dx < -160) {
				enemy1.dx = 800; //dla kazdego z trzech wrogow jest przesuniecie o 200 w poziomie, zeby atakowali w odstepach
				enemy1.dy = losuj_dy();
			}
			if (enemy2.dx < -160) {
				enemy2.dx = 1000;
				enemy2.dy = losuj_dy();
			}
			if (enemy3.dx < -160) {
				enemy3.dx = 1200;
				enemy3.dy = losuj_dy();
			}
			
			//jesli nastapilo zderzenie to wrog sie respawnuje z prawej, a gracz traci zycie 
			if (zderzenie(enemy1, x, y)) {
				enemy1.dx = 800;
				enemy1.dy = losuj_dy();
				player.zycia--;
			}
			if (zderzenie(enemy2, x, y)) {
				enemy2.dx = 1000;
				enemy2.dy = losuj_dy();
				player.zycia--;
			}
			if (zderzenie(enemy3, x, y)) {
				enemy3.dx = 1200;
				enemy3.dy = losuj_dy();
				player.zycia--;
			}

			//jesli gracz traci wszystkie zycia to wychodzimy z petli i koniec
			if (player.zycia <= 0)
				done = true;

			//granice mapy na oko, jesli gracz je przekroczy to od razu przegrywa
			if (x < -50 || x > 750 || y < -50 || y > 480 - 160)
				done = true;
			
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			key[event.keyboard.keycode] = 1;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] = 0;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}
		if (done)
			break;

		//wrogowie sie przesuwaja
		enemy1.dx -= vdx;
		enemy2.dx -= vdx;
		enemy3.dx -= vdx;

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world");
			//al_draw_bitmap(jetpack, dx, dy, 1);
			//al_draw_filled_rectangle(0, 0, 330, 330, al_map_rgb(50, 58, 168));
			al_draw_scaled_bitmap(background, 0, 0, 1920, 1080,xb1 ,0 ,800 ,480 ,0 );
			al_draw_scaled_bitmap(background, 0, 0, 1920, 1080,xb2 , 0, 800, 480, 0);
			al_draw_scaled_bitmap(jetpack, 0, 0, 500, 500, x, y, 160, 160, 0);
			al_draw_scaled_bitmap(jetpack, 0, 0, 500, 500, enemy1.dx, enemy1.dy, 160, 160, 1);
			al_draw_scaled_bitmap(jetpack, 0, 0, 500, 500, enemy2.dx, enemy2.dy, 160, 160, 1);
			al_draw_scaled_bitmap(jetpack, 0, 0, 500, 500, enemy3.dx, enemy3.dy, 160, 160, 1);

			al_draw_text(font, al_map_rgb(255, 255, 255), 17, 10, 0, "EPIc Adventure");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 17, 20, 0, "Score: %d", player.pkt);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 17, 30, 0, "Lives: %d", player.zycia);

			al_flip_display();

			redraw = false;
		}
		//liczymy fpsy
		counter++;
		//liczymy sekundy
		if (counter % 30 == 0) {
			player.pkt++; //kazda sekunda to +1 pkt dla gracza
		}
		// Przesuwanie tla
		xb1-=4;
		xb2-=4;
		if (xb1 == -800) {
			xb1 = 0;
			xb2 = 800;
		}
	}

	al_destroy_bitmap(jetpack);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}