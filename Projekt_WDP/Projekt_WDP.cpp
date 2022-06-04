﻿#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <ctime>

struct Gracz {
	float x = 0; //wspolrzedne gracza
	float y = 0;
	float vx = 10; //predkosc gracza w poziomie
	float vy = 10; //predkosc gracza w pionie
	int pkt = 0; //zdobyte punkty
	int highscore = 0;
	int zycia = 3; //ilosc zyc
};

struct Przeciwnik { //wspolrzedne i predkosc przeciwnika
	int dx = 1800;
	int dy = 0;
	int vdx = 10;
};

struct Piwo {
	int dx;
	int dy;
	int klatki_spawn; //co ile klatek ma sie piwo spawnowac w danym momencie
	bool piwo_ruch = false; //czy piwo ma sie poruszac w danym momencie
};

int losuj_dy() { //losuje wspolrzedna w pionie wrogow, zeby pojawiali sie na roznych wysokosciach
	int dy = rand() % (950-340);
	return dy;
}

bool zderzenie(struct Przeciwnik p, int x, int y) { //sprawdza czy bylo zderzenie z konkretnym przeciwnikiem
	if ((x + 140 > p.dx && x + 140 < p.dx + 170) && (y + 140 > p.dy && y + 140 < p.dy + 340))
		return true;
	else
		return false;
}

bool zderzenie_piwo(struct Piwo p, int x, int y) {
	if ((x + 140 > p.dx-60 && x + 140 < p.dx + 120+60) && (y + 140 > p.dy-60 && y + 140 < p.dy + 180+60))
		return true;
	else
		return false;
}

int main()
{
	struct Gracz player; //tworzymy strukture na punkty i zycie gracza
	srand(time(0));

	//tworzymy trzech wrogow
	struct Przeciwnik enemy1;
	enemy1.dx = 1800;
	enemy1.dy = losuj_dy();
	struct Przeciwnik enemy2;
	enemy2.dx = 2200;
	enemy2.dy = losuj_dy();
	struct Przeciwnik enemy3;
	enemy3.dx = 2600;
	enemy3.dy = losuj_dy();

	struct Piwo beer;
	beer.dx = 1800;
	beer.dy = losuj_dy();

	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(1800, 950);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_BITMAP* background = al_load_bitmap("Background_v2.png");
	ALLEGRO_BITMAP* enemy = al_load_bitmap("Enemy.png");
	ALLEGRO_BITMAP* jetpack = al_load_bitmap("jetpackman_v2.png");
	ALLEGRO_BITMAP* ekran_start1 = al_load_bitmap("Ekran_start1.png");
	ALLEGRO_BITMAP* ekran_start2 = al_load_bitmap("Ekran_start2.png");
	ALLEGRO_BITMAP* ekran_koniec = al_load_bitmap("Ekran_koniec.png");
	ALLEGRO_BITMAP* cien_jetpack = al_load_bitmap("Cien_jetpackman.png");
	ALLEGRO_BITMAP* cien_enemy = al_load_bitmap("Cien_enemy.png");
	ALLEGRO_BITMAP* piwo = al_load_bitmap("Piwo.png");
	ALLEGRO_BITMAP* serca1 = al_load_bitmap("1serca.png");
	ALLEGRO_BITMAP* serca2 = al_load_bitmap("2serca.png");
	ALLEGRO_BITMAP* serca3 = al_load_bitmap("3serca.png");


	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));


	int xb1 = 0;
	int xb2 = 1800;

	// Zmienne cienia
	int yc = 728;
	int w_c = 150, h_c = 30;

	// Zmienna ekranu
	int ek = 0;

	bool redraw = true;
	bool done = false;
	ALLEGRO_EVENT event;

	int counter = 0; //licznik klatek
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	 
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
				if (key[ALLEGRO_KEY_UP]) {
					player.y -= player.vy;
						yc -= 2;
					if (yc < 728) {
						yc = 728;
					}
  					w_c -= 2;
					if (w_c < 150)
						w_c = 150;
					h_c -= 1;
					if (h_c < 30)
						h_c = 30;
				}
				if (key[ALLEGRO_KEY_DOWN]) {
					player.y += player.vy;
						yc += 2;
						if (yc > 860) {
							yc = 860;
						}
						w_c += 2;
						if (w_c > 300)
							w_c = 300;
						h_c+=1;
						if (h_c > 100)
							h_c = 100;
				}
				if (key[ALLEGRO_KEY_RIGHT]) 
					player.x += player.vx;
				if (key[ALLEGRO_KEY_LEFT])
					player.x -= player.vx;
				if (key[ALLEGRO_KEY_ESCAPE])
					done = true;
				// Zmienne od zmiany ekranu
				if (key[ALLEGRO_KEY_ENTER])
					ek = 1;

				//spawnowanie piwa
				beer.klatki_spawn = (rand() % 600) + 600;
				if(counter % beer.klatki_spawn == 0) {
					beer.dx = 1800;
					beer.dy = losuj_dy();
					beer.piwo_ruch = true;
				}
				if (beer.dx < -120) {
					beer.dx = 1800;
					beer.dy = losuj_dy();
					beer.piwo_ruch = false;
				}
				if (zderzenie_piwo(beer, player.x, player.y)) {
					if (player.zycia < 3) {
						beer.piwo_ruch = false;
						beer.dx = 1800;
						beer.dy = losuj_dy();
						player.zycia++;
					}
				}

				//jesli wrog wyszedl za lewa krawedz mapy to spawnuje sie z powrotem z prawej strony
				if (enemy1.dx < -340) {
					enemy1.dx = 1800; //dla kazdego z trzech wrogow jest przesuniecie o 200 w poziomie, zeby atakowali w odstepach
					enemy1.dy = losuj_dy();
				}
				if (enemy2.dx < -340) {
					enemy2.dx = 2200;
					enemy2.dy = losuj_dy();
				}
				if (enemy3.dx < -340) {
					enemy3.dx = 2600;
					enemy3.dy = losuj_dy();
				}
			
				//jesli nastapilo zderzenie to wrog sie respawnuje z prawej, a gracz traci jedno zycie
				if (zderzenie(enemy1, player.x, player.y)) {
					enemy1.dx = 1800;
					enemy1.dy = losuj_dy();
					player.zycia--;
				}
				if (zderzenie(enemy2, player.x, player.y)) {
					enemy2.dx = 2000;
					enemy2.dy = losuj_dy();
					player.zycia--;
				}
				if (zderzenie(enemy3, player.x, player.y)) {
					enemy3.dx = 2200;
					enemy3.dy = losuj_dy();
					player.zycia--;
				}

				//jesli gracz traci wszystkie zycia to wychodzimy z petli i koniec
				// if (player.zycia <= 0)
				//	done = true;

				//blokowanie gracza zeby nie przekroczyl granic mapy
				if (player.y < 0)
					player.y = 0;
				if (player.y > 950 - 280)
					player.y = 950 - 280;
				if (player.x < 0)
					player.x = 0;
				if (player.x > 1800 - 280)
					player.x = 1800 - 280;
			
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
			enemy1.dx -= enemy1.vdx;
			enemy2.dx -= enemy2.vdx;
			enemy3.dx -= enemy3.vdx;

			if(beer.piwo_ruch)
				beer.dx -= enemy1.vdx;

			if (redraw && al_is_event_queue_empty(queue)) {
				// EDIT !!!!!! JUZ OGARNIAM LOL, Po prostu wartosci od naszych zmiennych (wspolrzedne rozne etc) dalej normalnie sie zmienialy i wgl,
				// tylko grafika jest wstrzymana
				// takze takie rzeczy jak scory, hitboxy, etc normalnie sie przesuwaly, a jak juz mialo sie wyrenderowac to mialo te nowe poloopowane wartosci !!!
				
				if (ek == 0) {
					al_draw_scaled_bitmap(background, 0, 0, 1920, 1080, xb1, 0, 1800, 950, 0);
					al_draw_scaled_bitmap(background, 0, 0, 1920, 1080, xb2, 0, 1800, 950, 0);
					al_draw_scaled_bitmap(ekran_start2, 0, 0, 1920, 1080, 0, 0, 1800, 950, 0);
					if (counter%60>0 && counter%60<30)
						al_draw_scaled_bitmap(ekran_start1, 0, 0, 1920, 1080, 0, 0, 1800, 950, 0);
					enemy1.dx = -300;
					enemy2.dx = -300;
					enemy3.dx = -300;
					player.pkt = 0;
					al_flip_display();
					redraw = false;

				}
				else {
					if (player.zycia <= 0) {
						// al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_scaled_bitmap(ekran_koniec, 0, 0, 1920, 1080, 0, 0, 1800, 950, 0);

						//zapisywanie nowego rekordu do pliku 
						/*FILE* plik = fopen_s("highscore.txt", "r+");
						int bufor; //bufor do zmiennej z pliku
						fscanf_s(plik, "%d", bufor);
						if (player.highscore > bufor)
							fprintf(plik,"%d",player.highscore);
						fclose(plik);*/
					}
					else {
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_scaled_bitmap(background, 0, 0, 1920, 1080, xb1, 0, 1800, 950, 0);
						al_draw_scaled_bitmap(background, 0, 0, 1920, 1080, xb2, 0, 1800, 950, 0);
						// Dodanie cienia TEST
						al_draw_tinted_scaled_bitmap(cien_jetpack, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 960, 320, player.x + 20, yc, w_c, h_c, 0);
						al_draw_tinted_scaled_bitmap(cien_enemy, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 750, 350, enemy1.dx + 140, 840, 150, 70, 0);
						al_draw_tinted_scaled_bitmap(cien_enemy, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 750, 350, enemy2.dx + 140, 840, 150, 70, 0);
						al_draw_tinted_scaled_bitmap(cien_enemy, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 750, 350, enemy3.dx + 140, 840, 150, 70, 0);
						// JetPackMan
						al_draw_scaled_bitmap(jetpack, 0, 0, 866, 883, player.x, player.y, 280, 280, 0);
						// Enemies 
						al_draw_scaled_bitmap(enemy, 0, 0, 1000, 1000, enemy1.dx, enemy1.dy, 340, 340, 0);
						al_draw_scaled_bitmap(enemy, 0, 0, 1000, 1000, enemy2.dx, enemy2.dy, 340, 340, 0);
						al_draw_scaled_bitmap(enemy, 0, 0, 1000, 1000, enemy3.dx, enemy3.dy, 340, 340, 0);
						// Piwo
						al_draw_scaled_bitmap(piwo, 0, 0, 254, 367, beer.dx, beer.dy, 120, 180, 0);
						// Serca
						if (player.zycia == 3) {
							al_draw_tinted_scaled_bitmap(serca3, al_map_rgba_f(1, 1, 1, 0.8), 0, 0, 1800, 950, 0, 170, 1360, 800, 0);
						}
						if (player.zycia == 2) {
							al_draw_tinted_scaled_bitmap(serca2, al_map_rgba_f(1, 1, 1, 0.8), 0, 0, 1800, 950, 0, 170, 1360, 800, 0);
						}
						if (player.zycia == 1) {
							al_draw_tinted_scaled_bitmap(serca1, al_map_rgba_f(1, 1, 1, 0.8), 0, 0, 1800, 950, 0, 170, 1360, 800, 0);
						}
						al_draw_text(font, al_map_rgb(255, 255, 255), 40, 25, 0, "EPIc Adventure");
						al_draw_textf(font, al_map_rgb(255, 255, 255), 40, 50, 0, "Score: %d", player.pkt);
						al_draw_textf(font, al_map_rgb(255, 255, 255), 40, 75, 0, "Lives: %d", player.zycia);
					}
					al_flip_display();
				}
					redraw = false;
			}
		//liczymy fpsy
		counter++;
		//liczymy sekundy
		if (counter % 60 == 0) {
			player.pkt++; //kazda sekunda to +1 pkt dla gracza
			if (player.pkt > player.highscore)
				player.highscore = player.pkt;
		}
		// Przesuwanie tla
		xb1-=5;
		xb2-=5;
		if (xb1 == -1800) {
			xb1 = 0;
			xb2 = 1800;
		}
	}

	al_destroy_bitmap(jetpack);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}