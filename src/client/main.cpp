#include "client-pch.hpp"

int main() {
  InitWindow(1920, 1080, "Minecraft: Better C++ Edition");
  InitAudioDevice();

  Texture2D texture = LoadTexture("assets/dummy_texture.png");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(10, 10);
    DrawTexture(texture, 10, 200, WHITE);

    EndDrawing();
  }
}