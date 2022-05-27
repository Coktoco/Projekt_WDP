﻿#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main()
{

	al_init();
	al_install_keyboard();
	al_init_image_addon();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(1880, 1020);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_BITMAP* background = al_load_bitmap("background1.png");
	ALLEGRO_BITMAP* jetpack = al_load_bitmap("jetpackman.png");

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

	if (!jetpack)

	{
		printf("Nie udalo sie zaladowac zdjecia!\n");
		return 1;
	}

	al_start_timer(timer);
	while (1) {

		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
			break;

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world");
			al_draw_bitmap(background, 0, 0,0);
			al_draw_bitmap(jetpack, 100, 100, 0);
			al_flip_display();


			redraw = false;
		}
	}

	al_destroy_bitmap(jetpack);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	// nowy
	return 0;

}