//
// Created by Start on 2018/7/6.
//

#pragma once

#include "Service/Service.hpp"
#include "Ref.hpp"
#include "Scene/Camera.hpp"
#include <string>
#include <unordered_map>

namespace LaughCrab
{
    class CameraService : public Service
    {
    public:
        CameraService();

        ~CameraService() override;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;

        const Ref<Camera> &GetCurCamera() const;

    private:
        LaughMath::Vector3 ParseTransition();

        EulerAngles ParseEulerAngles();

        ZoomParams ParseZoomParams();

        void ParseKeyDown(const Event &);

        void ParseKeyUp(const Event &);

        // mouse
        void ParseMouseMove(const Event &);

        void ParseMouseButtonDown(const Event &);

        void ParseMouseButtonUp(const Event &);

        void ParseMouseWheel(const Event &);

        std::unordered_map<std::string, Ref<Camera>> m_cameraList;
        Ref<Camera> m_curCamera;

        LaughMath::Vector3 m_transition;
        EulerAngles m_eulerAngles;
        ZoomParams m_zoomParams;

        typedef struct
        {
            Boolean keyClick;
            Boolean mouseMove;
            Boolean mouseClick;
            Boolean mouseWheel;
        } InputState;

        InputState m_inputState;
    };

    extern CameraService *g_cameraService;
}



