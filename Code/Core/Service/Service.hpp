#pragma once

#include "UnCopyable.hpp"
#include "Base.hpp"
#include "Runtime.hpp"

namespace LaughCrab {
    enum ServiceType {
        eSysCfgService = 0,
        eMemoryService = 1,
        eUnknownService,
    };

    /// service interface
    struct Service : public Runtime, public UnCopyable {
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void Restart() = 0;
    };
}