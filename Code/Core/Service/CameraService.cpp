//
// Created by Start on 2018/7/6.
//

#include <Scene/Camera.hpp>
#include "Scene/Camera.hpp"
#include "CameraService.hpp"
#include "EventService.hpp"
#include "ContextService.hpp"
#include "Scene/PerspectiveCamera.hpp"
#include "DataModel/KeyCode.hpp"
#include "Math.hpp"

using namespace LaughCrab;
using namespace LaughCrab::LaughMath;

CameraService::CameraService()
{
    m_inputState = {false, false, false, false};
}

CameraService::~CameraService()
{

}

void CameraService::Start()
{

}

void CameraService::Stop()
{}

void CameraService::Restart()
{}

Boolean CameraService::Init()
{
    m_cameraList["default"] = MakeDynamicRef<Camera, PerspectiveCamera>();
    m_curCamera = m_cameraList["default"];

    g_eventService->RegisterSyncEventJob(EventType::eKeyDown,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseKeyDown(event);
                                                      return 0;
                                                  }));
    g_eventService->RegisterSyncEventJob(EventType::eKeyUp,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseKeyUp(event);
                                                      return 0;
                                                  }));
    g_eventService->RegisterSyncEventJob(EventType::eMouseMove,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseMouseMove(event);
                                                      return 0;
                                                  }));
    g_eventService->RegisterSyncEventJob(EventType::eMouseButtonDown,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseMouseButtonDown(event);
                                                      return 0;
                                                  }));
    g_eventService->RegisterSyncEventJob(EventType::eMouseButtonUp,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseMouseButtonUp(event);
                                                      return 0;
                                                  }));
    g_eventService->RegisterSyncEventJob(EventType::eMouseWheel,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->ParseMouseWheel(event);
                                                      return 0;
                                                  }));
    return true;
}

void CameraService::Update()
{
    m_curCamera->UpdateCameraOrientation(ParseEulerAngles());
    m_curCamera->UpdateCameraPos(ParseTransition());
    m_curCamera->UpdateCameraFov(ParseZoomParams());
}

void CameraService::DeInit()
{
    g_eventService->RegisterSyncEventJob(EventType::eKeyDown, EventJob());
    m_cameraList["default"] = nullptr;
    m_curCamera = nullptr;
}

const Ref<Camera> &CameraService::GetCurCamera() const
{
    return m_curCamera;
}

Vector3 CameraService::ParseTransition()
{
    Vector3 delta = m_transition *
                    (g_contextService->GetFrameDeltaTime().count() *
                     g_contextService->GetContext()->GetVelocity());

    CameraCoords cameraCoords = m_curCamera->GetCameraCoords();

    cameraCoords.pos += cameraCoords.front * delta[i_z] +
                        cameraCoords.right * delta[i_x] +
                        cameraCoords.up * delta[i_y];

    return cameraCoords.pos;
}

EulerAngles CameraService::ParseEulerAngles()
{
    if (m_curCamera->IsConstrainPitch())
    {
        Float constrain = g_contextService->GetContext()->GetPitchConstrain();
        if (m_eulerAngles.pitch > constrain)
        {
            m_eulerAngles.pitch = constrain;
        }
        if (m_eulerAngles.pitch < -constrain)
        {
            m_eulerAngles.pitch = -constrain;
        }
    }

    return m_eulerAngles;
}

ZoomParams CameraService::ParseZoomParams()
{
    return m_zoomParams;
}

void CameraService::ParseKeyDown(const Event &event)
{
    switch (event.keyEvent.key)
    {
        case KeyCode::eKey_w:
            m_transition[i_z] = 1.f;
            break;
        case KeyCode::eKey_s:
            m_transition[i_z] = -1.f;
            break;
        case KeyCode::eKey_a:
            m_transition[i_x] = -1.f;
            break;
        case KeyCode::eKey_d:
            m_transition[i_x] = 1.f;
            break;
        case KeyCode::eKeySpace:
            m_transition[i_y] = 1.f;
            break;
        case KeyCode::eKey_c:
            m_transition[i_y] = -1.f;
            break;
        default:
            break;
    }
}

void CameraService::ParseKeyUp(const Event &event)
{
    switch (event.keyEvent.key)
    {
        case KeyCode::eKey_w:
            m_transition[i_z] = 0.f;
            break;
        case KeyCode::eKey_s:
            m_transition[i_z] = 0.f;
            break;
        case KeyCode::eKey_a:
            m_transition[i_x] = 0.f;
            break;
        case KeyCode::eKey_d:
            m_transition[i_x] = 0.f;
            break;
        case KeyCode::eKeySpace:
            m_transition[i_y] = 0.f;
            break;
        case KeyCode::eKey_c:
            m_transition[i_y] = 0.f;
            break;
        default:
            break;
    }
}


void CameraService::ParseMouseMove(const Event &event)
{
    Float mouseSensitivity = g_contextService->GetContext()->GetMouseSensitivity();

    EulerAngles eulerAngles = m_curCamera->GetEulerAngles();

    eulerAngles.yaw += event.mouseMoveEvent.xMove * mouseSensitivity;
    eulerAngles.pitch -= event.mouseMoveEvent.yMove * mouseSensitivity;

    m_eulerAngles = eulerAngles;
}

void CameraService::ParseMouseButtonDown(const Event &event)
{
}

void CameraService::ParseMouseButtonUp(const Event &event)
{
}

void CameraService::ParseMouseWheel(const Event &event)
{
    ZoomParams zoomParams = m_curCamera->GetZoomParams();

    if (zoomParams.zoom >= 1.0f && zoomParams.zoom <= 45.0f)
        zoomParams.zoom -= event.mouseWheelEvent.y;
    if (zoomParams.zoom <= 1.0f)
        zoomParams.zoom = 1.0f;
    if (zoomParams.zoom >= 45.0f)
        zoomParams.zoom = 45.0f;

    zoomParams.coord = Coordinates::eCoordsY;
    m_zoomParams = zoomParams;
}