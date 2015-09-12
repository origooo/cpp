#ifndef TILE_H_
#define TILE_H_

#include <stdio.h>
#include <SDL2/SDL.h>

struct SDL_Texture;
struct SDL_Rect;
struct SDL_Renderer;

class Tile {
	private:
		SDL_Texture* tex;
	public:
		Tile(SDL_Texture* apply_tex);
		void render(SDL_Renderer* r, SDL_Rect &rect);
		SDL_Texture* get_tex();
};
#endif //TILE_H_