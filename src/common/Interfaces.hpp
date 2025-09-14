#pragma once
#include "pch.hpp"

#define MAKE_INTERFACE(TEXT) struct I##TEXT { virtual ~I##TEXT() = default; virtual void TEXT() = 0; }; \
                             struct IArgs##TEXT { virtual ~IArgs##TEXT() = default; virtual void TEXT(std::any args) = 0; };

MAKE_INTERFACE(SystemSetup)
MAKE_INTERFACE(Setup)
MAKE_INTERFACE(Update)
MAKE_INTERFACE(Render)
MAKE_INTERFACE(Initialiastion)
MAKE_INTERFACE(Prelude)
MAKE_INTERFACE(Run)

#undef MAKE_INTERFACE