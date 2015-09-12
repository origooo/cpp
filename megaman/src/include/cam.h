#ifndef CAM_H_
#define CAM_H_

class Camera {
	private:
		int pos_x;
		int pos_y;
	public:
		Camera();
		void set_x_pos(int x);
		int get_x_pos();
		void set_y_pos(int y);
		int get_y_pos();
};
#endif //CAM_H_