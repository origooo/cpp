class World {
	private:
		int pixel_width;
		int pixel_height;
		Map map;
		Player player;
		
	public:
		World();

		Map get_map();
		void set_map(std::string path);
		void destroy_map();

		int get_pixel_width();
		void set_pixel_width(int pw);
		int get_pixel_height();
		void set_pixel_height(int ph);

		int get_cam_pos_x();
		void set_cam_pos_x(int i);
		int get_cam_pos_y();
		void set_cam_pos_y(int i);
};

World::World() {};

void World::set_map(std::string path) {
	if (!map.load_map(path.c_str())) {
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