//
// Created by Restart on 7/4/2018.
//

#include "ContextService.hpp"
#include "Context/SDLContext.hpp"

using namespace LaughCrab;

ContextService::ContextService()
        : m_context(nullptr)
{

}

ContextService::~ContextService()
{

}

void ContextService::Start()
{
    m_lastTime = std::chrono::system_clock::now();
}

void ContextService::Stop()
{
}

void ContextService::Restart()
{
    m_lastTime = std::chrono::system_clock::now();
    m_deltaTime = std::chrono::milliseconds(0);
}

Boolean ContextService::Init()
{
    m_context = MakeDynamicURef<Context, SDLContext>(nullptr);
    Log::Debug("ContextService", "%s", m_context->ToString());
    m_context->InitRenderDevice();

    return true;
}

void ContextService::Update()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //GetContext()->SwapBuffer();

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTime);
    m_lastTime = now;

}

void ContextService::DeInit()
{
    m_context->DeInitRenderDevice();

    m_context = nullptr;
}

std::chrono::milliseconds ContextService::GetFrameDeltaTime()
{
    return m_deltaTime;
}

const URef<Context> &ContextService::GetContext() const
{
    return m_context;
}