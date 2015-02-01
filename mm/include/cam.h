namespace Camera {
	class Camera {
		private:
			int pos_x;
			int pos_y;
			int cam_width = Constants::VIEWPORT_WIDTH;
			int cam_height = Constants::VIEWPORT_HEIGHT;
		public:
			Camera(int x, int y);
			int get_width();
			int get_height();
			void set_pos_x(int x);
			int get_pos_x();
			void set_pos_y(int y);
			int get_pos_y();
	};
	Camera::Camera::Camera(int x, int y) {
		pos_x = x;
		pos_y = y;
	}
	int Camera::Camera::get_width() {
		return cam_width;
	}
	int Camera::Camera::get_height() {
		return cam_height;
	}
	void Camera::Camera::set_pos_x(int x) {
		pos_x = x;
	}
	int Camera::Camera::get_pos_x() {
		return pos_x;
	}
	void Camera::Camera::set_pos_y(int y) {
		pos_y = y;
	}
	int Camera::Camera::get_pos_y() {
		return pos_y;
	}
} // End Camera namespace