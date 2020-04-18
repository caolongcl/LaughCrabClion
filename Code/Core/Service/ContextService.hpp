#pragma once

#include "Service.hpp"
#include "Context/Context.hpp"
#include "URef.hpp"
#include <chrono>

namespace LaughCrab
{

    class ContextService : public Service
    {
    public:

        ContextService();

        ~ContextService() override;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;

        std::chrono::milliseconds GetFrameDeltaTime();

        const URef<Context> &GetContext() const;

    private:
        URef<Context> m_context;
        std::chrono::milliseconds m_deltaTime;
        std::chrono::system_clock::time_point m_lastTime;
    };

    extern ContextService *g_contextService;
}
