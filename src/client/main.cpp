#include "client-pch.hpp"
#include "app/ClientApp.hpp"

int main() {
  ClientApp& app = ClientApp::Instance();
  app.Prelude();
  app.Run();
}
