#pragma once

#include "TypeDef.hpp"

namespace LaughCrab {
    /// runtime module interface
    struct Runtime {
        virtual Boolean Init() = 0;
        virtual void Update() = 0;
        virtual void DeInit() = 0;
    };
}