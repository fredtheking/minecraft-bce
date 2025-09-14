#pragma once
#include "src/client/client-pch.hpp"

class ClientApp final : public ISystemSetup, public ISetup, public IInitialiastion, public IPrelude, public IRun, public IUpdate, public IRender {
private:
  void CreateWindow();
public:
  void SystemSetup() override;
  void Setup() override;
  void Initialiastion() override;

  void Prelude();
  void Run() override;

  void Update() override;
  void Render() override;

private:
  //...
public:
  //...

private:
  ClientApp() = default;
public:
  ClientApp(const ClientApp&) = delete;
  ClientApp& operator=(const ClientApp&) = delete;

  static ClientApp& Instance() {
    static ClientApp singleton;
    return singleton;
  }
};
