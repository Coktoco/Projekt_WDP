﻿#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main()
{
	// KOLIZJA
	//Nowy komentarz
	//komentarz
	/*al_init();
	al_install_keyboard();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	//jeszcze raz
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 100.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(220, 120);
	ALLEGRO_FONT* font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool nowa_klatka = true, koniec = false;
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	ALLEGRO_EVENT event;
	int x = 10, y = 10;
	ALLEGRO_BITMAP* dino = al_load_bitmap("dino_red.png");

	al_start_timer(timer);
	while (!koniec)   
	{
		al_wait_for_event(queue, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			if (key[ALLEGRO_KEY_UP]) y--;
			if (key[ALLEGRO_KEY_DOWN]) y++;
			if (key[ALLEGRO_KEY_LEFT]) x--;
			if (key[ALLEGRO_KEY_RIGHT]) x++;
			nowa_klatka = true;
			if (key[ALLEGRO_KEY_ESCAPE]) koniec = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			key[event.keyboard.keycode] = 1;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] = 0;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			koniec = true;
		}


		// WPROWADZAM KOLEJNA ZMIANE DO TESTOW


		if (nowa_klatka && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), x, y, 0, "8=====D");
			al_flip_display();

			nowa_klatka = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
	*/

	al_init();
	al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	ALLEGRO_DISPLAY* disp = al_create_display(320, 200);

	ALLEGRO_FONT* font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);

	if (!al_init_image_addon())
	{
		printf("Addon nie dziala!\n");
		return 1;
	}

	ALLEGRO_BITMAP* jetpack = al_load_bitmap("dino_red.png");
	if (!jetpack)
		{
		printf("Nie udalo sie zaladowac zdjecia!\n");
		return 1;
		}


	while (1) {
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
			break;
		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world");
			al_draw_bitmap(jetpack, 100, 100, 0);
			al_flip_display();

			redraw = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	al_destroy_bitmap(jetpack);

	// nowy
	return 0;

}