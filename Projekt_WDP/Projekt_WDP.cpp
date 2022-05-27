#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main()
{
	//komentarz
	al_init();
	al_install_keyboard();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

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
}