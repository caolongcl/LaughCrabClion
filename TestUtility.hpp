#pragma once

#include "base.hpp"
#include <vector>
#include "CameraCustom.hpp"
#include "stb_image.h"
#include <map>
#include "TestCore/ShaderProgram.hpp"
#include "CameraService.hpp"
#include "ContextService.hpp"
#include "Math.hpp"

namespace LaughCrab
{
    class CameraCustom;

    extern CameraCustom camera;

    extern GLfloat lastX, lastY;

    extern GLfloat mixValue;

    class TestUtility
    {
    public:
        static void testTranslate();

        static void testMemoryService();

        static void TestMain();

        static void TestLife();

        static void TestMD5();

        static GLuint loadCubeMap(std::vector<const GLchar *> &cubeMap)
        {
            GLuint textureId;
            glGenTextures(1, &textureId);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

            int width, height;
            unsigned char *image = nullptr;
            for (std::vector<const GLchar *>::size_type i = 0; i < cubeMap.size(); i++)
            {
                int width, height, nrChannels;
                //unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

                image = stbi_load(cubeMap[i], &width, &height, 0, 0);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                             image);

                stbi_image_free(image);
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

            return textureId;
        }
        /*
                static ShaderProgram GetSkyBoxShader()
                {
                    std::map<GLenum, const GLchar *> shaderPath;
                    shaderPath.emplace(GL_VERTEX_SHADER, "Assets/ShaderSrc/SkyBox/shader.vertex");
                    shaderPath.emplace(GL_FRAGMENT_SHADER, "Assets/ShaderSrc/SkyBox/shader.frag");
                    ShaderProgram skyBoxShader(shaderPath);
                    return skyBoxShader;
                }

                static ShaderProgram GetBoxShader()
                {
                    std::map<GLenum, const GLchar *> shaderPath;
                    shaderPath.emplace(GL_VERTEX_SHADER, "Assets/ShaderSrc/Cube/shader.vertex");
                    shaderPath.emplace(GL_FRAGMENT_SHADER, "Assets/ShaderSrc/Cube/shader.frag");
                    ShaderProgram cubeShader(shaderPath);
                    return cubeShader;
                }

                static GLuint GetSkyBoVao()
                {
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
                }

                static GLuint GetSkyBoxTexture()
                {
                    //加载skybox纹理
                    std::vector<const GLchar *> skyBoxFace;
                    skyBoxFace.push_back("Assets/Texture/SkyBox/right.jpg");
                    skyBoxFace.push_back("Assets/Texture/SkyBox/left.jpg");
                    skyBoxFace.push_back("Assets/Texture/SkyBox/top.jpg");
                    skyBoxFace.push_back("Assets/Texture/SkyBox/bottom.jpg");
                    skyBoxFace.push_back("Assets/Texture/SkyBox/back.jpg");
                    skyBoxFace.push_back("Assets/Texture/SkyBox/front.jpg");

                    return TestUtility::loadCubeMap(skyBoxFace);
                }

                static GLuint GetBoxVao()
                {
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

                    return cubeVao;
                }

                static void preDraw()
                {
                    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                    glViewport(0, 0, 1920, 1080);
                    glEnable(GL_DEPTH_TEST);
                    glDepthFunc(GL_LESS);
                }

                static void onDraw(ShaderProgram skyBoxShader,
                                   ShaderProgram cubeShader,
                                   GLuint skyBoxVao,
                                   GLuint cubeVao,
                                   GLuint skyBoxTexture)
                {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    cubeShader.useProgram();

                    glBindVertexArray(cubeVao);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
                    glUniform1i(glGetUniformLocation(cubeShader.getProgramId(), "skybox"), 0);

                    LaughMath::Matrix44 model(1.0f), view, projection;;
                    view = g_cameraService->GetCurCamera().GetView();
                    projection = g_cameraService->GetCurCamera().GetPerspective();

                    glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "model"), 1, GL_FALSE, model.Get());
                    glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
                    glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "projection"), 1, GL_FALSE,
                                       projection.Get());

                    LaughMath::Vector3 coords = g_cameraService->GetCurCamera().GetCameraCoords().pos;
                    glUniform3f(glGetUniformLocation(cubeShader.getProgramId(), "cameraPos"), coords[0],
                                coords[1], coords[2]);

                    glDrawArrays(GL_TRIANGLES, 0, 36);

                    glBindVertexArray(0);

                    //绘制skybox
                    glDepthFunc(GL_LEQUAL);
                    skyBoxShader.useProgram();

                    glBindVertexArray(skyBoxVao);
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
                    glUniform1i(glGetUniformLocation(skyBoxShader.getProgramId(), "skybox"), 0);

                    view = g_cameraService->GetCurCamera().GetView();
                    ClearTranslate(view);

                    glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
                    glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "projection"), 1, GL_FALSE,
                                       projection.Get());

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    glBindVertexArray(0);

                    glDepthFunc(GL_LESS);
                    g_contextService->GetContext()->SwapBuffer();
                }

                //        static void do_movement(Int64 deltaTime)
                //        {
                //            if (keys[GLFW_KEY_W])
                //                camera.processKeyboard(CameraCustom::FORWARD, deltaTime);
                //            if (keys[GLFW_KEY_S])
                //                camera.processKeyboard(CameraCustom::BACKWARD, deltaTime);
                //            if (keys[GLFW_KEY_A])
                //                camera.processKeyboard(CameraCustom::LEFT, deltaTime);
                //            if (keys[GLFW_KEY_D])
                //                camera.processKeyboard(CameraCustom::RIGHT, deltaTime);
                //        }

                //        static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
                //        {
                //            static bool firstMouse = true;
                //            if (firstMouse)
                //            {
                //                lastX = xpos;
                //                lastY = ypos;
                //                firstMouse = false;
                //            }
                //
                //            GLfloat xoffset = xpos - lastX;
                //            GLfloat yoffset = lastY - ypos;
                //            lastX = xpos;
                //            lastY = ypos;
                //
                //            camera.processMouseMovement(xoffset, yoffset);
                //        }
                //
                //        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
                //        {
                //            camera.processMouseScroll(yoffset);
                //        }

                */
    };

    class A
    {
    public:
        A(int a, bool b)
        {
            m_a = a;
            m_b = b;
        }

        int m_a;
        int m_b;
    };
}
