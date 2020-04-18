project(LaughCrab)

set(SUB_CODE_SRC_Application
        Application/Application.hpp
        Application/Application.cpp)

set(SUB_CODE_SRC_Context
        Context/Context.hpp
        Context/SDLContext.hpp
        Context/SDLContext.cpp)

set(SUB_CODE_SRC_DataModel
        DataModel/KeyCode.hpp
        DataModel/Event.hpp
        DataModel/Glob.hpp
        DataModel/Glob.cpp)

set(SUB_CODE_SRC_Life
        Life/Life.hpp
        Life/Life.cpp)

set(SUB_CODE_SRC_Math
        Math/Math.hpp)

set(SUB_CODE_SRC_Memory
        Memory/MemUtils.hpp
        Memory/Allocator.hpp
        Memory/MemPool.hpp
        Memory/MemPool.cpp
        Memory/MemStack.hpp
        Memory/MemStack.cpp)

set(SUB_CODE_SRC_Scene
        Scene/Camera.hpp
        Scene/PerspectiveCamera.cpp
        Scene/PerspectiveCamera.hpp)

set(SUB_CODE_SRC_Service
        Service/Service.hpp
        Service/ServiceHub.hpp
        Service/ServiceHub.cpp
        Service/SysCfgService.hpp
        Service/SysCfgService.cpp
        Service/MemoryService.hpp
        Service/MemoryService.cpp
        Service/ContextService.hpp
        Service/ContextService.cpp
        Service/EventService.hpp
        Service/EventService.cpp
        Service/CameraService.hpp
        Service/CameraService.cpp
        Service/ResourceService.hpp
        Service/ResourceService.cpp)

set(SUB_CODE_SRC_Utils
        Utils/RefHelper.hpp
        Utils/Ref.hpp
        Utils/URefHelper.hpp
        Utils/URef.hpp
        Utils/EncryptMd5.hpp Utils/ResHelper.hpp)

set(SUB_CODE_SRC_Task
        Task/Task.hpp)

set(SUB_CODE_SRC_Test
        TestCore/TestCore.hpp
        TestCore/Shader.hpp
        TestCore/Shader.cpp
        TestCore/ShaderProgram.hpp
        TestCore/ShaderProgram.cpp)

set(SUB_CODE_SRC
        TypeDef.hpp
        DebugUtils.hpp
        Base.hpp
        UnCopyable.hpp
        Runtime.hpp
        Core.cpp
        )

### all src
set(CORE_SRC
        ${SUB_CODE_SRC}
        ${SUB_CODE_SRC_Application}
        ${SUB_CODE_SRC_Context}
        ${SUB_CODE_SRC_DataModel}
        ${SUB_CODE_SRC_Life}
        ${SUB_CODE_SRC_Math}
        ${SUB_CODE_SRC_Memory}
        ${SUB_CODE_SRC_Scene}
        ${SUB_CODE_SRC_Service}
        ${SUB_CODE_SRC_Utils}
        ${SUB_CODE_SRC_Task}
        ${SUB_CODE_SRC_Test}
        )

link_directories(../../ThirdParty/Libs)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


add_library(core SHARED ${CORE_SRC})

target_link_libraries(core glad SDL2d stb)