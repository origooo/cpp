#ifndef WORLD_H_
#define WORLD_H_

#include "map.h"
#include "player.h"

class World {
	private:
		int pixel_width;
		int pixel_height;
		Map map;
		Player player;
		
	public:
		World();

		Map get_map();
		void set_map(SDL_Renderer *r, std::string path);
		void destroy_map();

		Player get_player();
		
		int get_pixel_width();
		void set_pixel_width(int pw);
		int get_pixel_height();
		void set_pixel_height(int ph);

		int get_cam_pos_x();
		void set_cam_pos_x(int i);
		int get_cam_pos_y();
		void set_cam_pos_y(int i);
};
#endif //WORLD_H_