class Tile {
	private:
		SDL_Texture* tex;
	public:
		Tile(SDL_Texture* apply_tex);
		void render(SDL_Renderer* r, SDL_Rect* rect);
		SDL_Texture* get_tex();
};

Tile::Tile(SDL_Texture* apply_tex) {
	tex = apply_tex;
}
void Tile::render(SDL_Renderer* r, SDL_Rect* rect) {
	SDL_RenderCopy(r,tex,NULL,rect);
}
SDL_Texture* Tile::get_tex() {
	return tex;
}