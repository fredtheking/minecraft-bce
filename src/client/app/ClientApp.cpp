#include "ClientApp.hpp"

#include "src/client/Global.hpp"
#include "src/server/console-app/Global.hpp"


ClientApp::ClientApp() {

}


void ClientApp::CreateWindow() {
  SetTargetFPS(Global::WINDOW_DEFAULT_FLAGS);
  InitWindow(
    Global::WINDOW_DEFAULT_SIZE.x,
    Global::WINDOW_DEFAULT_SIZE.y,
    Global::WINDOW_DEFAULT_TITLE.c_str());
  InitAudioDevice();
}


void ClientApp::SystemSetup() {

}
void ClientApp::Setup() {
  CreateWindow();
}
void ClientApp::Initialiastion() {

}

void ClientApp::Prelude() {
  SystemSetup();
  Setup();
  Initialiastion();
}
void ClientApp::Run() {
  while (!WindowShouldClose()) {
    Update();
    Render();
  }
}

void ClientApp::Update() {

}
void ClientApp::Render() {
  BeginDrawing();
  ClearBackground(Global::CLEAR_COLOR);
}