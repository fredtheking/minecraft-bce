#include "pch.hpp"

int main() {
  InitWindow(1920, 1080, "Minecraft: Better C++ Edition");
  InitAudioDevice();

  Texture2D texture = LoadTexture("assets/dummy_texture.png");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(10, 10);
    DrawText("So, yea, im gonna try making my own minecraft. In, like, full 3D. Thats gonna be my first experience. God, wish me luck.", 10, 50, 20, RAYWHITE);
    DrawText("Also, i am making my own fnaf fan-game as of now, so this repo can be quiet empty for some time.", 10, 70, 20, RAYWHITE);
    DrawText("Gonna work on this project after my game OR when im too bored to code fnaf.", 10, 90, 20, RAYWHITE);
    DrawText("(day.month.year)", 10, 130, 20, DARKGRAY);
    DrawText("11.09.2025 - Started this repo before going to bed.", 10, 150, 20, YELLOW);
    DrawTexture(texture, 10, 200, WHITE);

    EndDrawing();
  }
}