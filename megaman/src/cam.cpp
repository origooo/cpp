#include "include/cam.h"

Camera::Camera() {

}
void Camera::set_x_pos(int x) {
	pos_x = x;
}
int Camera::get_x_pos() {
	return pos_x;
}
void Camera::set_y_pos(int y) {
	pos_y = y;
}
int Camera::get_y_pos() {
	return pos_y;
}