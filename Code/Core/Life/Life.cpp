#include <thread>
#include "Life.hpp"

#include "SysCfgService.hpp"
#include "MemoryService.hpp"
#include "ContextService.hpp"
#include "EventService.hpp"
#include "CameraService.hpp"
#include "ResourceService.hpp"
#include "Task/Task.hpp"

#include <vector>
#include <Scene/Camera.hpp>
#include "TestCore/ShaderProgram.hpp"
#include "Math.hpp"
#include "stb_image.h"
#include "TestCore/TestCore.hpp"

using namespace LaughCrab;
using namespace LaughCrab::LaughMath;
using namespace std;


Life::Life()
{

}

Life::~Life()
{

}

void Life::Go()
{
    PreBorn();
    Start();

    do
    {
        Cycle();
    } while (Reborn());

    End();
    Bury();
}

// init all service
void Life::PreBorn()
{
    Log::Debug("Life", "------PreBorn------");

    g_sysCfgService = new SysCfgService(nullptr);
    g_memoryService = new MemoryService();
    g_contextService = new ContextService();
    g_eventService = new EventService();
    g_resourceService = new ResourceService();
    g_cameraService = new CameraService();


    Assert(g_sysCfgService->Init());
    Assert(g_memoryService->Init());
    Assert(g_contextService->Init());
    Assert(g_eventService->Init());
    Assert(g_resourceService->Init());
    Assert(g_cameraService->Init());
}

void Life::Bury()
{
    Log::Debug("Life", "------Bury------");

    g_cameraService->DeInit();
    g_resourceService->DeInit();
    g_eventService->DeInit();
    g_contextService->DeInit();
    g_memoryService->DeInit();
    g_sysCfgService->DeInit();


    delete g_cameraService;
    delete g_resourceService;
    delete g_eventService;
    delete g_contextService;
    delete g_memoryService;
    delete g_sysCfgService;
}

Boolean Life::Kill()
{
    Boolean ret = GetState() == LifeState::eKillState;
    if (ret)
    {

        //        Task<int(int)> task([](int i){return i;});
        //        auto result = task.Then([](int i){return i + 1;})
        //                .Then([](int i){return i + 2;})
        //                .Then([](int i){return i + 3;})
        //                .Do(3);
        //        Log::Debug("Life", "---kill---- %d", result);
        Log::Debug("Life", "------kill------");
    }

    return ret;
}

Boolean Life::Reborn()
{
    Boolean ret = GetState() == LifeState::eReBornState;
    if (ret)
    {
        Log::Debug("Life", "------Reborn------");
        g_sysCfgService->Restart();
        g_memoryService->Restart();
        g_contextService->Restart();
        g_eventService->Restart();
        g_resourceService->Restart();
        g_cameraService->Restart();
    }
    return ret;
}

Boolean Life::Start()
{
    Log::Debug("Life", "------Start------");

    g_sysCfgService->Start();
    g_memoryService->Start();
    g_contextService->Start();
    g_eventService->Start();
    g_resourceService->Start();
    g_cameraService->Start();

    // for Life self start
    // register life cycle event
    g_eventService->RegisterSyncEventJob(EventType::eQuit,
                                         EventJob([this](const Event &event)
                                                  {
                                                      this->m_lifeState = LifeState::eKillState;
                                                      return 0;
                                                  }));


    m_lifeState = LifeState::eNormalState;
}

Boolean Life::Cycle()
{
    // go !!!!!
    Log::Debug("Life", "------Cycle------");

    TestCore::preDraw();
    ShaderProgram skyboxshader = TestCore::GetSkyBoxShader();
    ShaderProgram boxShader = TestCore::GetBoxShader();
    GLuint boxvao = TestCore::GetBoxVao();
    GLuint skyboxvao = TestCore::GetSkyBoVao();
    GLuint skyboxTexture = TestCore::GetSkyBoxTexture();

    while (!Kill())
    {
        g_sysCfgService->Update();
        g_memoryService->Update();
        g_contextService->Update();
        g_eventService->Update();
        g_resourceService->Update();
        g_cameraService->Update();
//        Log::Debug("pool", "================");
        TestCore::onDraw(skyboxshader,
                         boxShader,
                         skyboxvao,
                         boxvao,
                         skyboxTexture);

//        std::this_thread::sleep_for(std::chrono::milliseconds(
//                g_contextService->GetContext()->GetFPS()
//        ));
    }

    TestCore::postDraw(skyboxvao, boxvao, skyboxTexture);
}

Boolean Life::End()
{
    Log::Debug("Life", "------End------");

    g_cameraService->Stop();
    g_resourceService->Stop();
    g_eventService->Stop();
    g_contextService->Stop();
    g_memoryService->Stop();
    g_sysCfgService->Stop();
}

const Life::LifeState Life::GetState() const
{
    return m_lifeState;
}