//
// Created by Start on 2018/7/6.
//

#pragma once

#include "Math/Math.hpp"
#include "DataModel/Event.hpp"

namespace LaughCrab
{
    typedef enum CameraType
    {
        eCameraPerspective = 0,
        eCameraOrthogonal = 1,
        eCameraCustom,
    } CameraType;

    typedef enum CameraMode
    {
        eCameraModeNormal = 0,
        eCameraModeEditor = 1,
    } CameraMode;

    typedef struct
    {
        LaughMath::Vector3 pos;
        LaughMath::Vector3 front;
        LaughMath::Vector3 up;
        LaughMath::Vector3 right;
        LaughMath::Vector3 worldUp;
    } CameraCoords;

    typedef struct
    {
        Float fov;
        Float aspect;
        Float nearClip;
        Float farClip;
    } Frustum;

    typedef struct
    {
        Float pitch; //x
        Float yaw; // y
        Float row; //z
    } EulerAngles;

    typedef enum
    {
        eCoordsX = 0,
        eCoordsY = 1,
        eCoordsZ = 2,
        eCoordsW = 3,
        eCoordsUnknown,
    } Coordinates;

    typedef struct
    {
        Coordinates coord;
        Float zoom;
    } ZoomParams;

    /**
     * abstract camera base class
     */
    class Camera
    {
    public:

        virtual ~Camera() = default;

        virtual void UpdateCameraPos(const LaughMath::Vector3 &dir) = 0;

        virtual void UpdateCameraOrientation(const EulerAngles &angles) = 0;

        virtual void UpdateCameraFov(const ZoomParams &zoomParams) = 0;

        virtual LaughMath::Matrix44 GetView() = 0;

        virtual LaughMath::Matrix44 GetPerspective() = 0;

        virtual void SetFrustum(const Frustum &frustum)
        {
            m_frustum = frustum;
        }

        virtual void SetCameraCoords(const CameraCoords &cameraCoords)
        {
            m_coords = cameraCoords;
        }

        virtual void SetFrustumFov(Float fov)
        {
            m_frustum.fov = fov;
        }

        virtual void SetFrustumAspect(Float aspect)
        {
            m_frustum.aspect = aspect;
        }

        virtual void SetFrustumNear(Float nearClip)
        {
            m_frustum.nearClip = nearClip;
        }

        virtual void SetFrustumFar(Float farClip)
        {
            m_frustum.farClip = farClip;
        }

        virtual void SetCameraCoordsPos(const LaughMath::Vector3 &pos)
        {
            m_coords.pos = pos;
        }

        virtual void SetCameraCoordsFront(const LaughMath::Vector3 &front)
        {
            m_coords.front = front;
        }

        virtual void SetCameraCoordsUp(const LaughMath::Vector3 &up)
        {
            m_coords.up = up;
        }

        virtual void SetCameraCoordsRight(const LaughMath::Vector3 &right)
        {
            m_coords.right = right;
        }

        virtual void SetCameraCoordsWorldUp(const LaughMath::Vector3 &worldUp)
        {
            m_coords.worldUp = worldUp;
        }

        virtual void SetConstrainPitch(Boolean on)
        {
            m_isConstrainPitch = on;
        }

        virtual Frustum &GetFrustum()
        {
            return m_frustum;
        }

        virtual CameraCoords &GetCameraCoords()
        {
            return m_coords;
        }

        virtual EulerAngles &GetEulerAngles()
        {
            return m_eulerAngles;
        }

        virtual ZoomParams &GetZoomParams()
        {
            return m_zoom;
        }

        virtual Boolean IsConstrainPitch()
        {
            return m_isConstrainPitch;
        }

    protected:
        Frustum m_frustum;
        CameraCoords m_coords;
        EulerAngles m_eulerAngles;
        ZoomParams m_zoom;
        Boolean m_isConstrainPitch;
    };


}
