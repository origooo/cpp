#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "actor.h"

class Player : public Actor {
	private:
		SDL_Rect* rect; // Maybe move to actor.h
		bool load_texture(SDL_Renderer *r, std::string path);

	public:
		Player();

		bool load_unit(SDL_Renderer *r, std::string path);
		void render_unit(SDL_Renderer *r, int render_at_x, int render_at_y);

		int get_x_pos();
		void set_x_pos(int x);
		int get_y_pos();
		void set_y_pos(int y);

		void destroy_unit();
};
#endif //PLAYER_H_