//
// Created by Restart on 7/6/2018.
//
#pragma once

#include "Camera.hpp"

namespace LaughCrab
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera();

        PerspectiveCamera(const Frustum &frustum,
                          const CameraCoords &cameraCoords);

        ~PerspectiveCamera() override;

        void UpdateCameraPos(const LaughMath::Vector3 &dir) override;

        void UpdateCameraOrientation(const EulerAngles &angles) override;

        void UpdateCameraFov(const ZoomParams &zoomParams) override;

        LaughMath::Matrix44 GetView() override;

        LaughMath::Matrix44 GetPerspective() override;
    };
}

