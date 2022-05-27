#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void must_init(bool test, const char* description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

int main()
{
	int move = 900;
	int move2 = 1400;

	float x, y;
	x = 100;
	y = 100;

	al_init();
	al_install_keyboard();
	al_init_image_addon();
	must_init(al_init_primitives_addon(), "primitives");	


	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(800, 440);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_BITMAP* background = al_load_bitmap("background1.png");
	ALLEGRO_BITMAP* jetpack = al_load_bitmap("jetpackman.png");
	ALLEGRO_KEYBOARD_STATE ks;

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;

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
		
		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				al_get_keyboard_state(&ks);

				if (al_key_down(&ks, ALLEGRO_KEY_UP))
					y=y-5;
				if (al_key_down(&ks, ALLEGRO_KEY_DOWN))
					y=y+2;
				if (al_key_down(&ks, ALLEGRO_KEY_LEFT))
					x=x-2;
				if (al_key_down(&ks, ALLEGRO_KEY_RIGHT))
					x=x+2;
					redraw = true;
					break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}
		
		if (done)
			break;

		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true,
			y=y+2;
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_scaled_bitmap(background, 0, 0, 1920, 1080,0 ,0 ,800 ,480 ,0 );
			al_draw_scaled_bitmap(jetpack, 0, 0, 500, 500, x, y, 160, 160, 0);
			/* ENEMIES  1. */
			al_draw_filled_circle(move, 370, 30, al_map_rgb_f(0, 0, 0));
			al_draw_filled_circle(move, 270, 30, al_map_rgb_f(0, 0, 0));
			al_draw_filled_circle(move, 70, 30, al_map_rgb_f(0, 0, 0));

			/* ENEMIES  2. */
			al_draw_filled_circle(move2, 70, 30, al_map_rgb_f(0, 0, 0));
			al_draw_filled_circle(move2, 170, 30, al_map_rgb_f(0, 0, 0));
			al_draw_filled_circle(move2, 370, 30, al_map_rgb_f(0, 0, 0));

			al_draw_text(font, al_map_rgb(255, 255, 255), 17, 10, 0, "EPIc Adventure");

			al_flip_display();


			redraw = false;
		}
		/* MOVEMENT OF ENEMIES */
		move = move - 4;
		move2 = move2 - 4;
	}

	al_destroy_bitmap(jetpack);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	// nowy
	return 0;

}