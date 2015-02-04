#include <fstream>
#include <iostream>
#include <sstream>

class Map {
	private:
		int tile_size;
		int width;
		int height;

		std::vector<SDL_Texture*> textures;
		std::vector<std::vector<Tile>> tiles;
		std::vector<std::vector<Tile>> tiles_transposed;
		
		Camera camera;
		
		bool load_texture(std::string path);
		bool build_tiles(std::string tiles_str);
		void split(std::vector<std::string> &tokens, const std::string &text, char sep);
		
	public:
		Map();
		bool load_map(std::string path);
		std::vector<SDL_Texture*> get_texture_vector();
		std::vector<std::vector<Tile>> get_tiles_vector();
		Tile get_tile(int i, int j);
		Camera get_camera();
		int get_tile_size();
		int get_width();
		int get_height();
};

Map::Map() {}

bool Map::load_map(std::string path) {
	
	// path should be "level1", "level2" etc (folder containing map data)
	std::string map_settings_path(std::string("maps/") + std::string(path) + std::string("/settings.txt"));
	std::fstream map_settings(map_settings_path);

	printf("%s\n",map_settings_path.c_str());
	if (!map_settings.is_open()) {
		printf("Couldn't load map file!\n");
		return false;
	} else {
		int i = 0;
		std::string tex_path;
		for (std::string line; getline(map_settings, line); ++i){
		    switch (i) {
		    	case 0:
		    		tile_size = std::atoi(line.c_str());
		    		printf("%i ",tile_size);
		    		break;
	    		case 1:
	    			width = std::atoi(line.c_str());
		    		printf("%i ",width);
	    			break;
	    		case 2:
	    			height = std::atoi(line.c_str());
		    		printf("%i ",height);
	    			break;
	    		case 3:
	    			camera.set_pos_x(std::atoi(line.c_str()));
		    		printf("%i ",camera.get_pos_x());
	    			break;
	    		case 4:
	    			camera.set_pos_y(std::atoi(line.c_str()));
		    		printf("%i\n",camera.get_pos_y());
	    			break;
    			case 5:
    			case 6:
    			case 7:
    			case 8:
    			case 9:
    				map_settings >> tex_path;
    				printf("%s\n",tex_path.c_str());
    				if (!load_texture(tex_path)) {
    					printf("Couldn't load texture %s\n",tex_path.c_str());
    					return false;
    				}
    				break;
				case 10:
					std::string tiles_str;
					std::getline(map_settings,tiles_str);
					build_tiles(tiles_str);
					break;
		    }
		}
	}

	return true;
}

bool Map::load_texture(std::string path) {

	SDL_Surface* tmp = NULL;
	tmp = IMG_Load(path.c_str());

	textures.emplace_back(SDL_CreateTextureFromSurface(Graphics::gRenderer,tmp));
	if (textures.back() == NULL) {
		printf("Couldn't load texture from %s\n",path.c_str());
		return false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;

	return true;
}

bool Map::build_tiles(std::string tiles_str) {

	std::vector<std::string> digits;
	split(digits, tiles_str, ' ');

	// std::vector<Tile> temp_vec;
	int col = 0;

	tiles.resize(100);

	for (int i = 0; i < digits.size(); ++i) {

		if (i % width == 0 && i != 0) {
			// tiles.emplace_back(temp_vec);
			// temp_vec.clear();
			col = 0;
		}

		int x_int = std::atoi(digits.at(i).c_str());
		if (x_int < textures.size()) {
			tiles.at(col).emplace_back(Tile(textures[x_int]));
		} else {
			tiles.at(col).emplace_back(Tile(textures[0]));
		}
		++col;
	}
	printf("Tiles: %lu, %lu\n", tiles.size(), tiles.at(0).size());
	digits.clear();
	
	return true;
}

std::vector<SDL_Texture*> Map::get_texture_vector() {
	return textures;
}

std::vector<std::vector<Tile>> Map::get_tiles_vector() {
	return tiles;
}

void Map::split(std::vector<std::string> &tokens, const std::string &text, char sep) {
	int start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
}

Camera Map::get_camera() {
	return camera;
}

int Map::get_tile_size() {
	return tile_size;	
}

Tile Map::get_tile(int i, int j) {
	return tiles.at(i).at(j);
}

int Map::get_width() {
	return width;
}
int Map::get_height() {
	return height;
}