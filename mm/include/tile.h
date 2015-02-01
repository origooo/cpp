namespace Tiles {

	class Tile;
	
	SDL_Texture* tile_textures[Constants::TILE_TEXTURES_TOTAL];
	std::vector<Tiles::Tile> map;

	class Tile {
		private:
			SDL_Rect* rect;
			SDL_Texture* tex;
			int width = Constants::TILE_SIZE_X;
			int height = Constants::TILE_SIZE_Y;
			// int pos_x;
			// int pos_y;
		public:
			Tile(SDL_Texture* apply_tex, int x_pos, int y_pos);
			void render(SDL_Renderer* r);
			int get_pos_x();
			void set_pos_x(int x);
			int get_pos_y();
			void set_pos_y(int y);
			SDL_Rect* get_rect();
	};

	Tiles::Tile::Tile(SDL_Texture* apply_tex, int x_pos, int y_pos) {
		rect = new SDL_Rect{x_pos,y_pos,Constants::TILE_SIZE_X,Constants::TILE_SIZE_Y};
		tex = apply_tex;
	}
	void Tiles::Tile::render(SDL_Renderer* r) {
		SDL_RenderCopy(r,tex,NULL,rect);
	}
	int Tiles::Tile::get_pos_x() {
		return rect->x;
	}

	int Tiles::Tile::get_pos_y() {
		return rect->y;
	}
	SDL_Rect* Tiles::Tile::get_rect() {
		return rect;
	}
} // End Tiles namespace