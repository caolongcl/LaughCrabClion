//
// Created by Restart on 6/24/2018.
//

#include "TestUtility.hpp"
#include "Math/Math.hpp"
#include <iostream>
#include "Service/MemoryService.hpp"
#include "Service/SysCfgService.hpp"
#include "Utils/Ref.hpp"
#include "URef.hpp"
#include "SDL.h"
#include "glad.h"
#include "SDL_opengl.h"
#include "CameraCustom.hpp"
#include "TestCore/Shader.hpp"
#include "TestCore/ShaderProgram.hpp"
#include "Life/Life.hpp"
#include "Application/Application.hpp"
#include "DataModel/Glob.hpp"
#include "Utils/EncryptMd5.hpp"
#include <chrono>


using namespace std;
using namespace std::chrono;
using namespace LaughCrab;
using namespace LaughCrab::LaughMath;

namespace LaughCrab
{
    constexpr GLuint WIDTH = 1280, HEIGHT = 720;

    GLfloat lastX = WIDTH / 2;

    GLfloat lastY = HEIGHT / 2;

    GLfloat mixValue = 0.0f;

    CameraCustom camera(Vector3{0.0f, 0.0f, 3.0f});
}

void TestUtility::testTranslate()
{
    Matrix44 matrix44(1);
    Translate(matrix44, {0.f, 1.f, 2.f});
    cout << matrix44 << endl;

    Vector3 vector1{1.f, 2.f, 1.f};
    Vector3 vector2{1.f, 2.f, 1.f};

    cout << Dot(vector1, vector2) << endl;
}

void TestUtility::testMemoryService()
{
    g_sysCfgService = new SysCfgService(nullptr);
    g_sysCfgService->Init();
    g_memoryService = new MemoryService();
    g_memoryService->Init();
    {
        Ref<A> refA = MakeRef<A>(10, false);
        if (refA)
        {
            Log::Debug("testRef", "%d %d", refA->m_a, refA->m_b);
        }
    }
    //    {
    //        Ref<Matrix44> refB = MakeRef<Matrix44>(1);
    //        if (refB)
    //        {
    //            //Log::Debug("testMemoryService", "%d %d", refA->m_a, refA->m_b);
    //            cout << *refB << endl;
    //        }
    //    }

    //    URef<A> urefA = MakeURef<A>(100, true);
    //    if (urefA)
    //    {
    //        Log::Debug("testURef", "%d %d", urefA->m_a, urefA->m_b);
    //    }

    {
//        auto r = MakeRef<Glob<GlobType::eGlobText, 100>>();

//        Log::Debug("test ", "%d", r->GetData()[2]);
    }

    g_memoryService->DeInit();
    g_sysCfgService->DeInit();
    delete g_memoryService;
    delete g_sysCfgService;
}

void TestUtility::TestMain()
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

    //init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log::Error("TestMain", "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Window *m_window;
    SDL_GLContext m_glContext;

    //create window
    m_window = SDL_CreateWindow("Test Main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        Log::Error("TestMain", "SDL_CreateWindow! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    //create OpenGL context
    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_glContext == nullptr)
    {
        Log::Error("TestMain", "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);

    gladLoadGL();

    //
    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    map<GLenum, const GLchar *> shaderPath;
    shaderPath.emplace(GL_VERTEX_SHADER, "Assets/ShaderSrc/SkyBox/shader.vertex");
    shaderPath.emplace(GL_FRAGMENT_SHADER, "Assets/ShaderSrc/SkyBox/shader.frag");
    ShaderProgram skyBoxShader(shaderPath);

    printf("=======%s \n", shaderPath[GL_VERTEX_SHADER]);

    shaderPath.clear();
    shaderPath.emplace(GL_VERTEX_SHADER, "Assets/ShaderSrc/Cube/shader.vertex");
    shaderPath.emplace(GL_FRAGMENT_SHADER, "Assets/ShaderSrc/Cube/shader.frag");
    ShaderProgram cubeShader(shaderPath);

    GLfloat cubeVertices[] = {
            // Positions          // Normals
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    GLfloat skyboxVertices[] = {
            // Positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    //skybox
    GLuint skyBoxVao, skyBoxVbo;
    glGenVertexArrays(1, &skyBoxVao);
    glGenBuffers(1, &skyBoxVbo);
    glBindVertexArray(skyBoxVbo);

    glBindBuffer(GL_ARRAY_BUFFER, skyBoxVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);

    glBindVertexArray(0);

    //加载skybox纹理
    vector<const GLchar *> skyBoxFace;
    skyBoxFace.push_back("Assets/Texture/SkyBox/right.jpg");
    skyBoxFace.push_back("Assets/Texture/SkyBox/left.jpg");
    skyBoxFace.push_back("Assets/Texture/SkyBox/top.jpg");
    skyBoxFace.push_back("Assets/Texture/SkyBox/bottom.jpg");
    skyBoxFace.push_back("Assets/Texture/SkyBox/back.jpg");
    skyBoxFace.push_back("Assets/Texture/SkyBox/front.jpg");

    GLuint skyBoxTexture = loadCubeMap(skyBoxFace);

    //3D 立方体
    GLuint cubeVao, cubeVbo;
    glGenVertexArrays(1, &cubeVao);
    glGenBuffers(1, &cubeVbo);
    glBindVertexArray(cubeVbo);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    //
    milliseconds deltaTime;
    system_clock::time_point lastFrame = system_clock::now();//上一帧的时间

    //

    SDL_Event sdlEvent;

    Integer keyW = false;
    Integer keyA = false;
    Integer keyS = false;
    Integer keyD = false;

    Boolean isQuit = false;
    while (!isQuit)
    {
        while (SDL_PollEvent(&sdlEvent) != 0)
        {
            //            Log::Debug("testkey", "key %d", sdlEvent.type);
            switch (sdlEvent.type)
            {
                case SDL_KEYDOWN:
                    switch (sdlEvent.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            isQuit = true;
                            break;
                        case SDLK_UP:
                            mixValue += 0.1f;
                            if (mixValue >= 1.0f)
                            {
                                mixValue = 1.0f;
                            }
                            break;
                        case SDLK_DOWN:
                            mixValue -= 0.1f;
                            if (mixValue <= 0.0f)
                            {
                                mixValue = 0.0f;
                            }
                            break;

                        case SDLK_w:
                            keyW = true;
                            break;
                        case SDLK_a:
                            keyA = true;
                            break;
                        case SDLK_s:
                            keyS = true;
                            break;
                        case SDLK_d:
                            keyD = true;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (sdlEvent.key.keysym.sym)
                    {
                        case SDLK_w:
                            keyW = false;
                            break;
                        case SDLK_a:
                            keyA = false;
                            break;
                        case SDLK_s:
                            keyS = false;
                            break;
                        case SDLK_d:
                            keyD = false;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_QUIT:
                    isQuit = true;
                    Log::Debug("testkey", "key %d", sdlEvent.type);
                    break;
                default:
                    break;

            }
        }

        system_clock::time_point now = system_clock::now();
        deltaTime = duration_cast<milliseconds>(now - lastFrame);
        lastFrame = now;

        // Clear buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //摄像机移动
//        Int64 ms = deltaTime.count() / 16;
        Int64 ms = deltaTime.count();
        //Log::Debug("testtime", " %d ", ms);

        //Log::Debug("Test Main", "delta time %ld", deltaTime.count());

        if (keyW)
            camera.processKeyboard(CameraCustom::FORWARD, ms);
        if (keyS)
            camera.processKeyboard(CameraCustom::BACKWARD, ms);
        if (keyA)
            camera.processKeyboard(CameraCustom::LEFT, ms);
        if (keyD)
            camera.processKeyboard(CameraCustom::RIGHT, ms);


        //绘制立方体
        cubeShader.useProgram();

        glBindVertexArray(cubeVao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
        glUniform1i(glGetUniformLocation(cubeShader.getProgramId(), "skybox"), 0);

        Matrix44 model(1.0f), view, projection;;
        view = camera.getViewMatrix();
        projection = PerspectiveRH(camera.getViewZoom(),
                                   static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.01f, 1000.f);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "model"), 1, GL_FALSE, model.Get());
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "projection"), 1, GL_FALSE,
                           projection.Get());

        glUniform3f(glGetUniformLocation(cubeShader.getProgramId(), "cameraPos"), camera.getPositon()[0],
                    camera.getPositon()[1], camera.getPositon()[2]);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        //绘制skybox
        glDepthFunc(GL_LEQUAL);
        skyBoxShader.useProgram();

        glBindVertexArray(skyBoxVao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
        glUniform1i(glGetUniformLocation(skyBoxShader.getProgramId(), "skybox"), 0);

        view = camera.getViewMatrix();
        ClearTranslate(view);

        glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
        glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "projection"), 1, GL_FALSE,
                           projection.Get());

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS);

        SDL_GL_SwapWindow(m_window);
//        SDL_Delay(16);
    }

    glDeleteVertexArrays(1, &skyBoxVao);
    glDeleteBuffers(1, &skyBoxVbo);

    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void TestUtility::TestLife()
{
    Application().Run(nullptr);
}

void TestUtility::TestMD5()
{
    std::string text = "hello baby.";
    std::cout << MD5Digest(text) << std::endl;

    std::cout << MD5Digest("hello bayb.") << std::endl;
}