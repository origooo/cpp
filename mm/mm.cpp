#include <stdio.h>
#include <string>
#include <vector>

#include "include/constants.h"
#include "include/graphics.h"
#include "include/cam.h"
#include "include/tile.h"
#include "include/map.h"
#include "include/player.h"
#include "include/world.h"

bool init();
void close();
bool load_tile_textures();
void render_map(Map map, int cam_y, int cam_x);
bool build_map(int level);

World world;

int main() {
	if (!init()) {
		printf("Failed to initialise!\n");
		return 1;
	}

	bool quit = false;
	SDL_Event e;

	world.set_map("level1");
	Camera camera = world.get_map().get_camera();
	Map map = world.get_map();
	world.set_pixel_width(map.get_width() * map.get_tile_size());
	world.set_pixel_height(map.get_height() * map.get_tile_size());


	int scroll_size = map.get_tile_size() / 1;
	int cam_pos_x;
	int cam_pos_y;
	int world_pixel_width = world.get_pixel_width();
	int world_pixel_height = world.get_pixel_height();
	int x_min_offset = 0;
	int y_min_offset = 0;
	int x_max_offset = world_pixel_width - Constants::VIEWPORT_WIDTH;
	int y_max_offset = world_pixel_height - Constants::VIEWPORT_HEIGHT;

	printf("world width: %i, world height: %i\n",world_pixel_width, world_pixel_height);

	while (!quit) {

		cam_pos_x = camera.get_pos_x();
		cam_pos_y = camera.get_pos_y();


		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RIGHT:
		printf("pos: %i, max: %i\n", cam_pos_y + scroll_size,x_max_offset);
						if ((cam_pos_y + scroll_size) < x_max_offset) {
							camera.set_pos_y(cam_pos_y + scroll_size);
						}
						break;
					case SDLK_LEFT:
		printf("pos: %i, max: %i\n", cam_pos_y - scroll_size,x_min_offset);
						if ((cam_pos_y - scroll_size) > x_min_offset) {
							camera.set_pos_y(cam_pos_y - scroll_size);
						}
						break;
					case SDLK_UP:
		printf("pos: %i, max: %i\n", cam_pos_x - scroll_size,y_min_offset);
						if ((cam_pos_x - scroll_size) > y_min_offset) {
							camera.set_pos_x(cam_pos_x - scroll_size);
						}
						break;
					case SDLK_DOWN:
		printf("pos: %i, max: %i\n", cam_pos_x + scroll_size,y_max_offset);
						if ((cam_pos_x + scroll_size) < y_max_offset) {
							camera.set_pos_x(cam_pos_x + scroll_size);
						}
						break;
				}
			}
		}
		SDL_RenderClear(Graphics::gRenderer);
		render_map(map, camera.get_pos_x(),camera.get_pos_y());
		SDL_RenderPresent(Graphics::gRenderer);
	}
	close();
	return 0;
}

int tile_size, start_x, end_x, start_y, end_y;

void render_map(Map map, int cam_y, int cam_x) {
	printf("%i, %i\n", cam_x, cam_y);
	tile_size = map.get_tile_size();
	start_x = cam_x / tile_size;
	end_x = start_x + (Constants::VIEWPORT_WIDTH / tile_size) + 1;
	start_y = cam_y / tile_size;
	end_y = start_y + (Constants::VIEWPORT_HEIGHT / tile_size) + 1;

	// printf("%i, %i, %i, %i\n",start_x, start_y, end_x, end_y);

	for (int i = start_x, i_render = 0; i < end_x; i++, i_render++) {
		for (int j = start_y, j_render = 0; j < end_y; j++, j_render++) {
			Tile tile = map.get_tile(i,j);
			tile.render(Graphics::gRenderer, new SDL_Rect{tile_size*(i_render),tile_size*(j_render),tile_size,tile_size});
		}
	}
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

	SDL_DestroyRenderer(Graphics::gRenderer);
	SDL_DestroyWindow(Graphics::gWindow);
	Graphics::gWindow = NULL;
	Graphics::gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}