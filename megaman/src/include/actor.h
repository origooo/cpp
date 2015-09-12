#ifndef ACTOR_H_
#define ACTOR_H_

class Actor {
	protected:
		SDL_Texture* tex;
		SDL_Rect* clip;
		int x_pos;
		int y_pos;
		int width;
		int height;
		int unit_type;

		float speed_y;
		float speed_x;
		float gravity;

		bool is_jumping = false;
		bool jump_complete = false;

	public:

		bool load_unit(SDL_Renderer *r, std::string path);
		void render_unit(SDL_Renderer *r, int x_pos, int y_pos);

		int get_x_pos();
		void set_x_pos(int x);
		int get_y_pos();
		void set_y_pos(int y);

		void destroy_unit();
		
};
#endif //ACTOR_H_