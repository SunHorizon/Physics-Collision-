#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Assignment4.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Assignment4(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}


/// Here's the whole game
void GameManager::Run() {
	timer->Start();
	while (isRunning) {
		if (currentScene->GetCloseWindow() == true) {
			isRunning = false;
		}
			timer->UpdateFrameTicks();
			currentScene->Update(timer->GetDeltaTime());
			currentScene->KeyPress();
			currentScene->Render();
			/// Keeep the event loop running at a proper rate
			SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
		
	}
}
GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}