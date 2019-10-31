#include "Assignment4.h"
#include "Body.h"
#include <SDL.h>
#include "GameManager.h"
#include <cmath>
#include <time.h>
#include <cstdlib> 

Assignment4::Assignment4(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	keyCheck = false;
	closeWindow = false;
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[0] = nullptr;
	}

}

Assignment4::~Assignment4(){
}

bool Assignment4::OnCreate() {
	int w, h;
	IMG_Init(IMG_INIT_PNG);
	SDL_GetWindowSize(window,&w,&h);
	
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(-20.0f, 35.0f, -20.0f, 35.0f, 0.0f, 1.0f) ;
	
	bodies[0] = new Body("Sun.png", 150.0f, 1.0f, Vec3(5.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

	bodies[1] = new Body("Moon.png", 50.0f, 1.7f, Vec3(2.0f, -3.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[2] = new Body("Moon.png", 50.0f, 1.7f, Vec3(8.0f, 20.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[3] = new Body("Moon.png", 50.0f, 1.7f, Vec3(17.0f, 25.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[4] = new Body("Moon.png", 50.0f, 1.7f, Vec3(-5.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[5] = new Body("Moon.png", 50.0f, 1.7f, Vec3(-15.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[6] = new Body("Moon.png", 50.0f, 1.7f, Vec3(12.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[7] = new Body("Moon.png", 50.0f, 1.7f, Vec3(30.0f, 12.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment4::OnDestroy() {
	IMG_Quit();
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment4::Update(const float Time) {
	srand(time(NULL));
	elapsedTime += Time;
	// x= -2, y = 5;

	for (int i = 1; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			if (frameCount == 1) {

				for (int io = 1; io < NUM_BODIES; io++) {

					float randx = rand() % 8 + -5;
				    float randy = rand() % 8 + -5;
					bodies[io]->vel.x = randx;
					bodies[io]->vel.y = randy;

					float massRandom = rand() % 100 + 1;
					bodies[io]->mass = massRandom;
				}
			}

			for (int k = 1; k < NUM_BODIES; k++) {
				for (int j = k + 1; j < NUM_BODIES; j++) {
					if (Collider::CheckCollision(*bodies[k], *bodies[j])) {
						printf("Check Collision!!\n");
						Collider::handleCollision(*bodies[k], *bodies[j]);

					}
				}
			}

			direction = bodies[0]->pos - bodies[i]->pos;

			// Get the magnitude
			dis = sqrt(direction.x * direction.x + direction.y * direction.y);


			// get Fgravity 
			fg1 = (1.0f * bodies[i]->mass * bodies[0]->mass) / (dis * dis);

			// normalize it 
			direction /= dis;

			// getting the actual value my multiplaying
			direction *= fg1;

			// adding the two numbers
			gForce = direction;

			bodies[i]->ApplyForce(gForce);

			// Checking for collision for all planets
			if (bodies[i]) bodies[i]->Update(Time);

		}
		frameCount++;
	}
	//frameCount++;
}
 void Assignment4::KeyPress() {
	 SDL_Event event;
	 while (SDL_PollEvent(&event) != 0)
	 {
		 if (event.type == SDL_QUIT) {	 
			 closeWindow = true;
		 }
		 //User presses a key
		 if (event.type == SDL_KEYDOWN)
		 {
			 //Select surfaces based on key press
			 switch (event.key.keysym.sym)
			 {
			 case SDLK_UP:
				 keyCheck = true;

				 break;
			 default:
				 keyCheck = false;
				 break;
			 }
		 }
	 }
}
 bool Assignment4::GetCloseWindow() {
	 return closeWindow;
}
void Assignment4::Render() {
		SDL_Rect imageRectangle;
		SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));

		for (int i = 0; i < NUM_BODIES; i++) {
			Vec3 screenCoords = projectionMatrix * bodies[i]->pos;

			imageRectangle.h = bodies[i]->getImage()->h;
			imageRectangle.w = bodies[i]->getImage()->w;
			imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
			imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning			
			SDL_BlitSurface(bodies[i]->getImage(), nullptr, screenSurface, &imageRectangle);
			
	}
		SDL_UpdateWindowSurface(window);
}