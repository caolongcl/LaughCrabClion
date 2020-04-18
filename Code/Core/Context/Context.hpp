#pragma once

#include "TypeDef.hpp"
#include "DataModel/Event.hpp"

namespace LaughCrab
{
    // window ,linux platform common

    class Context
    {
    public:
        enum class PlatformType : Integer
        {
            eWindowsPlatform = 0,
            eLinuxPlatform = 1,
            eAndroidPlatform = 2,
            eIOSPlatform = 3,
            eUnknownPlatform
        };

        enum class ContextType : Integer
        {
            eDirectXContext = 1,
            eOpenGLContext = 2,
            eUnknownContext
        };

        virtual const Char *ToString() = 0;

        // window , config render device
        virtual void InitRenderDevice() = 0;

        virtual void DeInitRenderDevice() = 0;

        // keyboard input key map
        virtual void InitKeyBoardInput() = 0;

        virtual void DeInitKeyBoardInput() = 0;

        virtual Boolean GetEvent(Event &) = 0;

        virtual Integer MapKeyCode(Integer sdlKey) = 0;

        virtual Integer MapKeyCategory(Integer keyCode) = 0;

        virtual void SwapBuffer() = 0;

        virtual Integer GetWidth() = 0;

        virtual Integer GetHeight() = 0;
        virtual Integer GetFPS() = 0;

        virtual Float GetVelocity() = 0;

        virtual Float GetPitchConstrain() = 0;

        virtual Float GetMouseSensitivity() = 0;

        virtual Float GetRowSensitivity() = 0;
    };
}
