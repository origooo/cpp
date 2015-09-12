#include <stdio.h>
#include <string>
#include <vector>

#include "include/constants.h"
#include "include/graphics.h"
#include "include/world.h"

bool init();
void close();
bool load_tile_textures();
bool render_map(Map &map, int cam_y, int cam_x);
bool render_player(Player &player, int x_pos, int y_pos);
bool build_map(int level);

World world;
std::vector<std::vector<SDL_Rect>> render_rects;

int tiles_x;
int tiles_y;
bool lock_cam_x_left;
bool lock_cam_x_right;
bool lock_cam_y_top;
bool lock_cam_y_bottom;

int main() {
	if (!init()) {
		printf("Failed to initialise!\n");
		return 1;
	}

	/**************************************************************************
		Creates the selected world with map, player, and enemies.

		TODO: 	Refactor, move to main loop when "select map"-enum exist.
				Refactor creation of render_rects along with it.
	**************************************************************************/

	world.set_map(Graphics::gRenderer, "level1");
	Camera camera = world.get_map().get_camera();
	Map map = world.get_map();
	world.set_pixel_width(map.get_width() * map.get_tile_size());
	world.set_pixel_height(map.get_height() * map.get_tile_size());

	// int scroll_size = map.get_tile_size() / 2;
	int cam_pos_x;
	int cam_pos_y;
	int world_pixel_width = world.get_pixel_width();
	int world_pixel_height = world.get_pixel_height();
	// int x_min_offset = 0;
	// int y_min_offset = 0;
	// int x_max_offset = world_pixel_width - Constants::VIEWPORT_WIDTH;
	// int y_max_offset = world_pixel_height - Constants::VIEWPORT_HEIGHT;
	
	printf("world width: %i, world height: %i\n",world_pixel_width, world_pixel_height);

	Player player = world.get_player();
	player.load_unit(Graphics::gRenderer, "../units/player/unit_settings.txt");

	int player_x_pos;
	int player_y_pos;
	int player_speed = 16;

	/**************************************************************************
		Creates rect's for each tile inside the viewport to be assigned a texture each time the map is rendered
	**************************************************************************/
	tiles_x = Constants::VIEWPORT_WIDTH / map.get_tile_size();
	tiles_y = Constants::VIEWPORT_HEIGHT / map.get_tile_size();

	render_rects.resize(tiles_x + 1);
	for (int i = 0; i < render_rects.size(); ++i) {
		render_rects.at(i).resize(tiles_y + 1);
	}

	printf("%lu, %lu\n",render_rects.size(),render_rects.at(10).size());

	
	/*************************************************************************/

	bool quit = false;
	SDL_Event e;
	
	while (!quit) {

		cam_pos_x = camera.get_x_pos();
		cam_pos_y = camera.get_y_pos();
		player_x_pos = player.get_x_pos();
		player_y_pos = player.get_y_pos();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RIGHT:
						
						player_x_pos += player_speed;
						player.set_x_pos(player_x_pos);
						
						// if ((cam_pos_x + scroll_size) < x_max_offset) {
						// 	camera.set_x_pos(player_x_pos - Constants::VIEWPORT_WIDTH/2);
						// }
						break;
					case SDLK_LEFT:

						player_x_pos -= player_speed;
						player.set_x_pos(player_x_pos);

						// if ((cam_pos_x - scroll_size) > x_min_offset) {
						// 	camera.set_x_pos(cam_pos_x - scroll_size);
						// }
						break;
					case SDLK_UP:

						player_y_pos -= player_speed;
						player.set_y_pos(player_y_pos);

						// if ((cam_pos_x - scroll_size) > y_min_offset) {
						// 	camera.set_x_pos(cam_pos_x - scroll_size);
						// }
						break;
					case SDLK_DOWN:

						player_y_pos += player_speed;
						player.set_y_pos(player_y_pos);

						// if ((cam_pos_x + scroll_size) < y_max_offset) {
						// 	camera.set_x_pos(cam_pos_x + scroll_size);
						// }
						break;
				}
			}
		}
		SDL_RenderClear(Graphics::gRenderer);
		render_map(map, player.get_x_pos(), player.get_y_pos());
		// render_map(map, camera.get_x_pos(),camera.get_y_pos());
		render_player(player, player.get_x_pos(), player.get_y_pos());
		SDL_RenderPresent(Graphics::gRenderer);
	}
	close();
	return 0;
}

int tile_size, start_x, end_x, start_y, end_y;

bool render_map(Map &map, int player_x_pos, int player_y_pos) {
	tile_size = map.get_tile_size();

	// int draw_x = (player_x_pos - Constants::VIEWPORT_WIDTH/2);
	// int draw_y = (player_y_pos - Constants::VIEWPORT_HEIGHT/2);

	start_x = (player_x_pos - Constants::VIEWPORT_WIDTH/2) / tile_size;
	end_x = start_x + (Constants::VIEWPORT_WIDTH / tile_size) + 1;
	
	0 < start_x ? 
		lock_cam_x_left = false,
		map.get_width() < end_x ?
			(
				end_x = map.get_width() - 1,
				start_x = end_x - tiles_x,
				lock_cam_x_right = true
			) :
			lock_cam_x_right = false
			:
		(
			start_x = 0,
			end_x = tiles_x,
			lock_cam_x_left = true
		);

// printf("Lock camera X: %i\n",lock_cam_x);

	start_y = (player_y_pos - Constants::VIEWPORT_HEIGHT/2) / tile_size;
	end_y = start_y + (Constants::VIEWPORT_HEIGHT / tile_size) + 1;

	0 <= start_y ?
		lock_cam_y_top = false,
		map.get_height() - 1 < end_y ?
			(
				end_y = map.get_height() - 1,
				start_y = end_y - tiles_y,
				lock_cam_y_bottom = true
			) :
			lock_cam_y_bottom = false
			:
		(
			start_y = 0,
			end_y = tiles_y + 1,
			lock_cam_y_top = true
		);
	// map.get_height() - 1 < end_y ? (end_y = map.get_height() - 1, start_y = end_y - tiles_y) : 0;

	for (int i = start_x, i_render = 0; i < end_x; i++, i_render++) {
		for (int j = start_y, j_render = 0; j < end_y; j++, j_render++) {
			Tile tile = map.get_tile(i,j);
			render_rects.at(i_render).at(j_render).x = tile_size * i_render;
			render_rects.at(i_render).at(j_render).y = tile_size * j_render;
			render_rects.at(i_render).at(j_render).w = tile_size;
			render_rects.at(i_render).at(j_render).h = tile_size;
			tile.render(Graphics::gRenderer, render_rects.at(i_render).at(j_render));
		}
	}
	return true;
}

bool render_player(Player &player, int x_pos, int y_pos) {
	printf("Lock Y bottom: %i, x_pos: %i, y_pos: %i\n",lock_cam_y_bottom,x_pos,y_pos);
	if (lock_cam_x_left) {
		// x_pos = x_pos; // Do nothing to x_pos!
	} else if (lock_cam_x_right) {
		x_pos = x_pos - Constants::VIEWPORT_WIDTH;
	} else if (!lock_cam_x_left && !lock_cam_x_right) {
		x_pos = Constants::VIEWPORT_WIDTH/2;
	}
	if (lock_cam_y_top) {
		// y_pos = y_pos; // Do nothing to y_pos!
	} else if (lock_cam_y_bottom) {
		y_pos = 1600 - y_pos;
	} else if (!lock_cam_y_top && !lock_cam_y_bottom) {
		y_pos = Constants::VIEWPORT_HEIGHT/2;
	}
	// if (!lock_cam_x_left && !lock_cam_y) {
	// 	player.render_unit(Graphics::gRenderer, Constants::VIEWPORT_WIDTH/2, Constants::VIEWPORT_HEIGHT/2);
	// }
	player.render_unit(Graphics::gRenderer, x_pos, y_pos);
	return true;
}

bool init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    Graphics::gWindow = SDL_CreateWindow("Lazy Reader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::VIEWPORT_WIDTH, Constants::VIEWPORT_HEIGHT, SDL_WINDOW_SHOWN);
    if (Graphics::gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

	Graphics::gRenderer = SDL_CreateRenderer(Graphics::gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (Graphics::gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    
    return true;
}

void close() {
	world.destroy_map();

	for (int i = 0; i < render_rects.size(); ++i) {
		render_rects.at(i).clear();
	}
	render_rects.clear();

	SDL_DestroyRenderer(Graphics::gRenderer);
	SDL_DestroyWindow(Graphics::gWindow);
	Graphics::gWindow = NULL;
	Graphics::gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}