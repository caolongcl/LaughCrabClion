//
// Created by Start on 2018/7/5.
//

#pragma once

#include "Service.hpp"
#include "DataModel/Event.hpp"
#include "Ref.hpp"
#include "Task/Task.hpp"
#include <unordered_map>
#include <queue>
#include <functional>
#include <list>

namespace LaughCrab
{
    class EventService : public Service
    {
    public:
        using Filter = std::function<Event(Event &)>;
        static constexpr Event UnKnownEvent = {eUnknownEvent};

        // sync event


    public:
        EventService() = default;

        ~EventService() override = default;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;

        // forward 
        Boolean GetEvent(Integer category, Event &event);

        // return old event job
        EventJob RegisterSyncEventJob(Integer type, const EventJob &job);

        EventJob RegisterSyncEventJob(Integer type, EventJob &&job);

    private:

        Boolean IsValid(Integer type);

        void InitSyncEventPool();

        void ClearSyncEventPool();

        Event FilterEvent(Event &event, Filter &&filter);


    private:
        // sync job
        std::unordered_map<Integer, EventJob> m_syncJobPool;

        // async event
        std::unordered_map<Integer, std::list<Event>> m_asyncEventPool;
        std::unordered_map<Integer, std::list<EventJob>> m_asyncJobPool;
    };

    extern EventService *g_eventService;
}
