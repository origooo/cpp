#include "include/player.h"

Player::Player() {
	rect = new SDL_Rect{};
	gravity = 9.82f;
}

bool Player::load_unit(SDL_Renderer *r, std::string path) {
	std::fstream unit_settings(path);

	if (!unit_settings.is_open()) {
		printf("Couldn't load player file!\n");
		return false;
	} else {
		int i = 0;
		std::string tex_path;
		for (std::string line; getline(unit_settings, line); ++i){
		    switch (i) {
		    	case 0:
		    		unit_type = atoi(line.c_str());
		    		printf("%i ",unit_type);
		    		break;
	    		case 1:
	    			width = atoi(line.c_str());
		    		printf("%i ",width);
	    			break;
	    		case 2:
	    			height = atoi(line.c_str());
		    		printf("%i ",height);
	    			break;
	    		case 3:
	    			x_pos = atoi(line.c_str());
		    		printf("%i ",x_pos);
	    			break;
	    		case 4:
	    			y_pos = atoi(line.c_str());
		    		printf("%i\n",y_pos);
	    			break;
    			case 5:
    				unit_settings >> tex_path;
    				printf("%s\n",tex_path.c_str());
    				if (!load_texture(r,tex_path)) {
    					printf("Couldn't load player texture %s\n### SDL ERROR: %s\n",tex_path.c_str(),SDL_GetError());
    					return false;
    				}
    				break;
		    }
		}
	}
	return true;
}

bool Player::load_texture(SDL_Renderer *r,std::string path) {
	SDL_Surface* tmp = NULL;
	tmp = IMG_Load(path.c_str());
	bool success = true;

	tex = SDL_CreateTextureFromSurface(r,tmp);
	if (tex == NULL) {
		success = false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;

	return success;
}

void Player::render_unit(SDL_Renderer *r, int render_at_x, int render_at_y) {
	printf("render @ x_pos/y_pos: %i/%i\n",render_at_x,render_at_y);
	rect->x = render_at_x;
	rect->y = render_at_y;
	/**********************************************************************
		ADD TO SETTINGS FILE
	**********************************************************************/
	rect->w = width;
	rect->h = height;
// printf("rX %i, rY %i, rW %i, rH %i\n", rect->x,rect->y,rect->w,rect->h);
	SDL_RenderCopy(r,tex,NULL,rect);
}

int Player::get_x_pos() {
	return x_pos;
}

void Player::set_x_pos(int x) {
	x_pos = x;
}

int Player::get_y_pos() {
	return y_pos;
}

void Player::set_y_pos(int y) {
	y_pos = y;
}

void Player::destroy_unit() {
	SDL_DestroyTexture(tex);
	rect = NULL;
}