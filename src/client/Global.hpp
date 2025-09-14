#pragma once
#include "src/client/client-pch.hpp"

namespace Global {
  const ConfigFlags WINDOW_DEFAULT_FLAGS = FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE;
  const Vector2 WINDOW_DEFAULT_SIZE = {1280, 720};
  const std::string WINDOW_DEFAULT_TITLE = "MC-BCE Client";
  const Color CLEAR_COLOR = BLACK;
}
