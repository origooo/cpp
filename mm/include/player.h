class Player {
	private:
		// The player's current position (top-left co-ordinate of sprite)
		float playerX, playerY;		 
		// The amount of X acceleration to apply when the player moves left or right
		// The amount of X deceleration to apply when the player does not move left or right
		float accX, decX;
		// The amount of X and Y movement to occur on the next frame
		float speedX, speedY;
		// The maximum movement speed allowed for the player
		float maxSpeedX, maxSpeedY;
		// The amount of upward force to apply when the player first presses jump
		float jumpStartSpeedY;
		// The amount of Y acceleration to apply on each frame due to the force of gravity
		float accY;
		// True if currently jumping (prevents the player jumping while in mid-air)
		bool jumping;
		// True if the jump key is currently held down (key must be released to allow a new jump)
		bool jumpKeyDown;

		SDL_Texture* tex;

	public:
		Player();
};

Player::Player() {
	// Set default player position
	playerX = 200.f;
	playerY = 150.f;
	 
	// Set acceleration and speed
	float mScale = 60.f;
	 
	accX = 0.2f * mScale;
	decX = 0.3f * mScale;
	maxSpeedX = 5.0f * mScale;
	maxSpeedY = 10.0f * mScale;
	 
	speedX = 0.f;
	speedY = 0.f;
	 
	// Set jump and gravity forces
	jumpStartSpeedY = 8.f * mScale;
	accY = 0.5f * mScale;
	 
	jumping = false;
	jumpKeyDown = false;

	SDL_Surface* s = IMG_Load("media/images/player_sprites/pOneFrame.png");
	if (s = NULL) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
}