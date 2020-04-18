//
// Created by Start on 2018/7/5.
//

#include "EventService.hpp"
#include "ContextService.hpp"
#include "CameraService.hpp"
#include <algorithm>

using namespace LaughCrab;

void EventService::Start()
{}

void EventService::Stop()
{}

void EventService::Restart()
{
}

Boolean EventService::Init()
{
    InitSyncEventPool();
    return true;
}

// dispatch event to event pool

void EventService::Update()
{
    Event event;
    //  input event and system events
    while (g_contextService->GetContext()->GetEvent(event))
    {
        m_syncJobPool[event.type].Do(event);
    }

    // dispatch async event
}

EventJob EventService::RegisterSyncEventJob(Integer type, const EventJob &job)
{
    EventJob old;
    if (IsValid(type))
    {
        old = m_syncJobPool[type];
        m_syncJobPool[type] = job;
    }

    return old;
}

EventJob EventService::RegisterSyncEventJob(Integer type, EventJob &&job)
{
    EventJob old;
    if (IsValid(type))
    {
        old = m_syncJobPool[type];
        m_syncJobPool[type] = std::move(job);
    }

    return old;
}

void EventService::DeInit()
{
    ClearSyncEventPool();
}


Boolean EventService::GetEvent(Integer category, Event &event)
{
//    if (IsValid(category))
//    {
//        std::queue<Event> &queue = m_asyncEventPool.at(category);
//        if (!queue.empty())
//        {
//            event = queue.front();
//            queue.pop();
//            return true;
//        }
//    }

    return false;
}

Boolean EventService::IsValid(Integer type)
{
    return type >= EventType::eQuit && type < EventType::eUnknownEvent;
}

void EventService::InitSyncEventPool()
{
    m_syncJobPool[EventType::eQuit] = EventJob();
    m_syncJobPool[EventType::eKeyDown] = EventJob();
    m_syncJobPool[EventType::eKeyUp] = EventJob();
    m_syncJobPool[EventType::eMouseMove] = EventJob();
    m_syncJobPool[EventType::eMouseButtonDown] = EventJob();
    m_syncJobPool[EventType::eMouseButtonUp] = EventJob();
    m_syncJobPool[EventType::eMouseWheel] = EventJob();
}

void EventService::ClearSyncEventPool()
{
    std::for_each(m_syncJobPool.begin(), m_syncJobPool.end(),
                  [](std::pair<const Integer, EventJob> &pair)
                  {
                      pair.second = EventJob();
                  });
}

Event EventService::FilterEvent(Event &event, Filter &&filter)
{
    return std::forward<Filter>(filter)(event);
}