namespace Constants {
	const int TILE_SIZE_X = 16;
	const int TILE_SIZE_Y = 16;

	const int VIEWPORT_WIDTH = 800;
	const int VIEWPORT_HEIGHT = 600;
	const int SCREEN_WIDTH = VIEWPORT_WIDTH; // Remove SCREEN_WIDTH and refactor it
	const int SCREEN_HEIGHT = VIEWPORT_HEIGHT;  // Remove SCREEN_HEIGHT and refactor it

	const int WORLD_WIDTH = 100; // Deprecated - Should be set in World class
	const int WORLD_HEIGHT = 100; // Deprecated - Should be set in World class
	const int TILES_PER_SCREEN_W = SCREEN_WIDTH / TILE_SIZE_X + 1; // Deprecated
	const int TILES_PER_SCREEN_H = SCREEN_HEIGHT / TILE_SIZE_Y + 1; // Deprecated

	enum Game_states {
		STATE_MENU,
		STATE_PLAY,
		STATE_PAUSE
	};
	
	enum Tile_texture_name {
		NO_TEXTURE,
		CORNER_TEXTURE,
		HORISONTAL_TEXTURE,
		VERTICAL_TEXTURE,
		FILL_TEXTURE,
		TILE_TEXTURES_TOTAL
	};
}