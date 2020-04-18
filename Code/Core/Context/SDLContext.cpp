#include <Service/CameraService.hpp>
#include "SDLContext.hpp"
#include "DebugUtils.hpp"
#include "glad.h"
#include "SDL_opengl.h"
#include "DataModel/KeyCode.hpp"

using namespace LaughCrab;

SDLContext::SDLContext()
        : m_window(nullptr),
          m_glContext(nullptr)
{
}

SDLContext::SDLContext(void *)
{

}

SDLContext::~SDLContext()
{

}

void SDLContext::InitRenderDevice()
{
    InitRenderKitFeature();
    InitSDLSystem();
    m_window = CreateSDLWindow(GetWidth(), GetHeight());
    m_glContext = CreateOpenGLContext();
    InitGLADLoader();
}

void SDLContext::DeInitRenderDevice()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLContext::InitKeyBoardInput()
{

}

void SDLContext::DeInitKeyBoardInput()
{

}

// convert context input events
Boolean SDLContext::GetEvent(Event &event)
{
    SDL_Event sdlEvent;
    Boolean ret = SDL_PollEvent(&sdlEvent) != 0;

    if (!ret) return ret;

    switch (sdlEvent.type)
    {
        case SDL_QUIT:
            event.type = EventType::eQuit;
            break;
        case SDL_KEYUP:
            event.keyEvent.type = EventType::eKeyUp;
            event.keyEvent.key = MapKeyCode(sdlEvent.key.keysym.sym);
            break;
        case SDL_KEYDOWN:
            event.keyEvent.type = EventType::eKeyDown;
            event.keyEvent.key = MapKeyCode(sdlEvent.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            event.mouseMoveEvent.type = EventType::eMouseMove;
            event.mouseMoveEvent.xMove = sdlEvent.motion.xrel;
            event.mouseMoveEvent.yMove = sdlEvent.motion.yrel;
            break;
        case SDL_MOUSEWHEEL:
            event.mouseWheelEvent.type = EventType::eMouseWheel;
            event.mouseWheelEvent.x = sdlEvent.wheel.x;
            event.mouseWheelEvent.y = sdlEvent.wheel.y;
            break;
        default:
            ret = false;
            break;
    }
    return ret;
}

void SDLContext::SwapBuffer()
{
    SDL_GL_SwapWindow(m_window);
}

Integer SDLContext::GetWidth()
{
    return 1280;
}

Integer SDLContext::GetHeight()
{
    return 720;
}

Integer SDLContext::GetFPS()
{
    return 16;
}

Float SDLContext::GetVelocity()
{
//    return static_cast<Float>(1) / static_cast<Float >(18);
    return 0.01f;
}

Float SDLContext::GetPitchConstrain()
{
    return 89.0f;
}

Float SDLContext::GetMouseSensitivity()
{
    return 0.25f;
}

Float SDLContext::GetRowSensitivity()
{
    return 0.25f;
}

/*
 * private
 */

Integer SDLContext::MapKeyCode(Integer sdlKey)
{
    return sdlKey;
}

void SDLContext::InitRenderKitFeature()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void SDLContext::InitSDLSystem()
{
    // init video and events
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log::Error("SDLContext", "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
}

SDL_Window *SDLContext::CreateSDLWindow(Integer width, Integer height)
{
    //create window
    m_window = SDL_CreateWindow("SDLContext",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN/* | SDL_WINDOW_RESIZABLE*/);
    if (!m_window)
    {
        Log::Error("SDLContext", "SDL_CreateWindow! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
}

SDL_GLContext SDLContext::CreateOpenGLContext()
{
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext)
    {
        Log::Error("SDLContext", "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);
}

void SDLContext::InitGLADLoader()
{
    gladLoadGL();
}

const Char *SDLContext::ToString()
{
    return "SDLContext";
}