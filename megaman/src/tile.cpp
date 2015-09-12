#include "include/tile.h"

Tile::Tile(SDL_Texture* apply_tex) {
	tex = apply_tex;
}
void Tile::render(SDL_Renderer* r, SDL_Rect &rect) {
	SDL_RenderCopy(r,tex,NULL,&rect);
}
SDL_Texture* Tile::get_tex() {
	return tex;
}