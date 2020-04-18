#pragma once

#include "Context.hpp"
#include "Runtime.hpp"
#include "SDL.h"
#include <chrono>

namespace LaughCrab
{
    // SDL create a window

    class SDLContext final : public Context
    {
    public:
        SDLContext();

        // todo read context config
        SDLContext(void *);

        ~SDLContext();

        const Char *ToString() override;

        void InitRenderDevice() override;

        void DeInitRenderDevice() override;

        void InitKeyBoardInput() override;

        void DeInitKeyBoardInput() override;

        Boolean GetEvent(Event &) override;

        void SwapBuffer() override;

        Integer GetWidth() override;

        Integer GetHeight() override;

        Integer GetFPS() override;

        Float GetVelocity() override;

        Float GetPitchConstrain() override;

        Float GetMouseSensitivity() override;

        Float GetRowSensitivity() override;

    private:
        void InitRenderKitFeature();

        void InitSDLSystem();

        SDL_Window *CreateSDLWindow(Integer width, Integer height);

        SDL_GLContext CreateOpenGLContext();

        void InitGLADLoader();

        // key map
        Integer MapKeyCode(Integer sdlKey) override;

        Integer MapKeyCategory(Integer keyCode)
        {}

    private:
        SDL_Window *m_window;
        SDL_GLContext m_glContext;
    };

}
