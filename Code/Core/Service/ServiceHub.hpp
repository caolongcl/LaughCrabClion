#pragma once

#include "Service.hpp"

namespace LaughCrab {

    class ServiceHub {
    public:
        void Create();

        Service *Get(ServiceType type);

        void Destroy();
    private:

        Service *service[eUnknownService];
    };
}