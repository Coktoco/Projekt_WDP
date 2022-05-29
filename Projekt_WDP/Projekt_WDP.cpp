#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <ctime>

int losuj_dy() {
	int dy = rand() % 500;
	return dy;
}

int main()
{
	int move = 900;
	int move2 = 1400;

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

	bool redraw = true;
	bool done = false;
	ALLEGRO_EVENT event;
	int x = 0, y = 0;
	int dx=2000, dy=0;
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	srand(time(0));

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

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			if (key[ALLEGRO_KEY_UP])
				y-=10;
			if (key[ALLEGRO_KEY_DOWN])
				y+=10;
			if (key[ALLEGRO_KEY_RIGHT])
				x+=10;
			if (key[ALLEGRO_KEY_LEFT])
				x-=10;
			if (key[ALLEGRO_KEY_ESCAPE])
				done = true;
			if (dx < -500) {
				dx = 2000;
				dy = losuj_dy();
			}

			if ((x+150>dx && x+150<dx+300) && (y+150>dy && y+150<dy+300))
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

		dx-=5;

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world");
			al_draw_bitmap(background, 0, 0, 0);
			al_draw_bitmap(jetpack, x, y, 0);
			al_draw_bitmap(jetpack, dx, dy, 1);
			//al_draw_filled_rectangle(0, 0, 330, 330, al_map_rgb(50, 58, 168));
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

	return 0;
}