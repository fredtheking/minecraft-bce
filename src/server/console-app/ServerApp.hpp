#pragma once
#include "src/common/Interfaces.hpp"

class ServerApp final : public IRun {
private:
  //...
public:
  void Run() override;

private:
  std::string port_str;
  std::string world_name;
  int default_mode = 0;
  const std::vector<std::string> default_modes = {"Survival", "Creative", "Adventure"};
public:
  //...

private:
  ServerApp() = default;
public:
  ServerApp(const ServerApp&) = delete;
  ServerApp& operator=(const ServerApp&) = delete;

  static ServerApp& Instance() {
    static ServerApp singleton;
    return singleton;
  }
};
