#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <SDL2_image/SDL_image.h>

#include "graphics.h"
#include "cam.h"
#include "tile.h"

class Map {
	private:
		int tile_size;
		int width;
		int height;

		std::vector<SDL_Texture*> textures;
		std::vector<std::vector<Tile>> tiles;
		std::vector<std::vector<Tile>> tiles_transposed;
		
		SDL_Renderer *tmp_rend;

		Camera camera;
		
		bool load_texture(std::string path);
		bool build_tiles(std::string &tiles_str);
		void split(std::vector<std::string> &tokens, const std::string &text, char sep);
		
	public:
		Map();
		bool load_map(SDL_Renderer *r, std::string path);
		std::vector<SDL_Texture*> get_texture_vector();
		std::vector<std::vector<Tile>> get_tiles_vector();
		Tile get_tile(int i, int j);
		Camera get_camera();
		int get_tile_size();
		int get_width();
		int get_height();
};
#endif //MAP_H_