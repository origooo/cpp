class Camera {
	private:
		int pos_x;
		int pos_y;
	public:
		Camera();
		void set_pos_x(int x);
		int get_pos_x();
		void set_pos_y(int y);
		int get_pos_y();
};
Camera::Camera() {

}
void Camera::set_pos_x(int x) {
	pos_x = x;
}
int Camera::get_pos_x() {
	return pos_x;
}
void Camera::set_pos_y(int y) {
	pos_y = y;
}
int Camera::get_pos_y() {
	return pos_y;
}