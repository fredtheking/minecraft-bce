#include "ServerApp.hpp"
#include "server-pch.hpp"

#define DEFAULT_PORT "25565"
#define DEFAULT_WORLD_NAME "world"
using namespace ftxui;

void ServerApp::Run() {
  auto port_input = Input(&port_str, DEFAULT_PORT);
  auto world_name_input = Input(&world_name, DEFAULT_WORLD_NAME);

  auto port_element = Renderer(port_input, [&] { return hbox({ text("Port: ") | bold, port_input->Render() }); });
  auto world_name_element = Renderer(world_name_input, [&] { return hbox({ text("World name: ") | bold, world_name_input->Render() }); });
  auto mode_dropdown = Dropdown(default_modes, &default_mode);

  auto main_renderer = Renderer(Container::Vertical({
    port_input,
    world_name_input,
  }), [&] {
    return vbox({
      port_element->Render(),
      world_name_element->Render(),
    }) | border;
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(Container::Vertical({
    main_renderer,
    mode_dropdown
  }));
}
