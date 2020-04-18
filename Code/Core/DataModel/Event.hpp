#pragma once

#include "TypeDef.hpp"
#include "Task/Task.hpp"

namespace LaughCrab
{
    typedef enum EventType
    {
        eQuit = 0, // system quit

        eKeyDown, // keyboard
        eKeyUp,
        eMouseMove,
        eMouseButtonDown,
        eMouseButtonUp,
        eMouseWheel,

        eUnknownEvent,
    } EventType;

    typedef struct KeyBoardEvent
    {
        EventType type;
        Integer key;
    } KeyBoardEvent;

    typedef struct MouseMoveEvent
    {
        EventType type;
        Integer x;
        Integer y;
        Integer xMove;
        Integer yMove;
    } MouseMoveEvent;

    typedef struct MouseButtonEvent
    {
        EventType type;
        UInt8 button;
        UInt8 state;
        UInt8 clicks;
        UInt8 reserved;
        Integer x;
        Integer y;
    } MouseButtonEvent;

    typedef struct MouseWheelEvent
    {
        EventType type;
        Integer x;
        Integer y;
        UInteger direction;
    } MouseWheelEvent;


    typedef union Event
    {
        EventType type;
        KeyBoardEvent keyEvent;
        MouseMoveEvent mouseMoveEvent;
        MouseButtonEvent mouseButtonEvent;
        MouseWheelEvent mouseWheelEvent;
    } Event;

    using EventJob = Task<Integer(const Event &)>;
    //
}