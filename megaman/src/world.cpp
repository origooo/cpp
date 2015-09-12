#include "include/world.h"

World::World() {};

void World::set_map(SDL_Renderer *r, std::string path) {
	if (!map.load_map(r, path.c_str())) {
		printf("Couldn't load world!\n### ERROR: Map load failed!\n");
	}
	pixel_width = map.get_width() * map.get_tile_size();
	pixel_height = map.get_height() * map.get_tile_size();
}

Map World::get_map() {
	return map;
}

void World::destroy_map() {
	for (auto x : map.get_tiles_vector()) {
		for (auto y : x) {
			SDL_DestroyTexture(y.get_tex());
		}
	}
	for (auto x : map.get_texture_vector()) {
		SDL_DestroyTexture(x);
	}
}

Player World::get_player(){
	return player;
}

int World::get_pixel_width() {
	return pixel_width;
}

void World::set_pixel_width(int pw) {
	pixel_width = pw;
}

int World::get_pixel_height() {
	return pixel_height;
}

void World::set_pixel_height(int ph) {
	pixel_height = ph;
}