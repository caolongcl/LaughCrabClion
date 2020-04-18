//
// Created by Restart on 7/6/2018.
//

#include "PerspectiveCamera.hpp"
#include "ContextService.hpp"
#include "EventService.hpp"
#include "Camera.hpp"

using namespace LaughCrab;
using namespace LaughMath;

PerspectiveCamera::PerspectiveCamera()
{
    m_frustum.fov = 45.f;
    m_frustum.aspect = (Float) g_contextService->GetContext()->GetWidth()
                       / g_contextService->GetContext()->GetHeight();
    m_frustum.nearClip = 0.01f;
    m_frustum.farClip = 1000.0f;

    m_coords.worldUp = Vector3{0.0f, 1.0f, 0.0f};
    m_coords.pos = Vector3{0.f, 0.f, 3.f};
    m_coords.front = Vector3{0.0f, 0.0f, 1.0f};

    m_coords.right = Normalize(Cross(m_coords.front, m_coords.worldUp));

    m_coords.up = Normalize(Cross(m_coords.right, m_coords.front));

    m_eulerAngles = {0.f, -90.f, 0.f};

    UpdateCameraOrientation(m_eulerAngles);

    m_isConstrainPitch = true;
}

PerspectiveCamera::PerspectiveCamera(const Frustum &frustum,
                                     const CameraCoords &cameraCoords)
{
    m_frustum = frustum;
    m_coords = cameraCoords;

    m_isConstrainPitch = true;
}

PerspectiveCamera::~PerspectiveCamera()
{}

void PerspectiveCamera::UpdateCameraPos(const Vector3 &dir)
{
    m_coords.pos = dir;
}

void PerspectiveCamera::UpdateCameraOrientation(const EulerAngles &angles)
{
    if (m_eulerAngles.pitch != angles.pitch ||
        m_eulerAngles.yaw != angles.yaw ||
        m_eulerAngles.row != angles.row)
    {

        m_eulerAngles = angles;
        Vector3 vector3;
        vector3[i_x] = static_cast<Float >(cos(Radians(m_eulerAngles.yaw)) * cos(Radians(m_eulerAngles.pitch)));
        vector3[i_y] = static_cast<Float >(sin(Radians(m_eulerAngles.pitch)));
        vector3[i_z] = static_cast<Float >(sin(Radians(m_eulerAngles.yaw)) * cos(Radians(m_eulerAngles.pitch)));

        m_coords.front = Normalize(vector3);
        m_coords.right = Normalize(Cross(m_coords.front, m_coords.worldUp));
        m_coords.up = Normalize(Cross(m_coords.right, m_coords.front));
    }
}

void PerspectiveCamera::UpdateCameraFov(const ZoomParams &zoomParams)
{
    m_zoom = zoomParams;
    if (m_zoom.coord == Coordinates::eCoordsY)
    {
        m_frustum.fov = m_zoom.zoom;
    }
}

Matrix44 PerspectiveCamera::GetView()
{
    return LookAtViewRH(m_coords.pos, m_coords.pos + m_coords.front, m_coords.up);
}

Matrix44 PerspectiveCamera::GetPerspective()
{
    return PerspectiveRH(m_frustum.fov, m_frustum.aspect, m_frustum.nearClip, m_frustum.farClip);
}

