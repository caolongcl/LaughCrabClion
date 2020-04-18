#pragma once

#include "Base.hpp"
#include <vector>
#include "CameraCustom.hpp"
#include "stb_image.h"
#include <map>
#include "ShaderProgram.hpp"
#include "CameraService.hpp"
#include "ContextService.hpp"
#include "Math.hpp"

namespace LaughCrab
{
    class TestCore
    {
    public:
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

        static ShaderProgram &&GetSkyBoxShader()
        {
            std::map<GLenum, const GLchar *> shaderPath;
            shaderPath.emplace(GL_VERTEX_SHADER, "Assets/ShaderSrc/SkyBox/shader.vertex");
            shaderPath.emplace(GL_FRAGMENT_SHADER, "Assets/ShaderSrc/SkyBox/shader.frag");
            ShaderProgram skyBoxShader(shaderPath);
            return std::move(skyBoxShader);
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

            return skyBoxVao;
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

            return loadCubeMap(skyBoxFace);
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
            glViewport(0, 0, g_contextService->GetContext()->GetWidth(), g_contextService->GetContext()->GetHeight());
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }

        static void onDraw(ShaderProgram skyBoxShader,
                           ShaderProgram cubeShader,
                           GLuint skyBoxVao,
                           GLuint cubeVao,
                           GLuint skyBoxTexture)
        {
//            Log::Debug("onDraw", "shader %d vao %d texture %d", cubeShader.getProgramId(), cubeVao, skyBoxTexture);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            cubeShader.useProgram();

            glBindVertexArray(cubeVao);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
            glUniform1i(glGetUniformLocation(cubeShader.getProgramId(), "skybox"), 0);

            LaughMath::Matrix44 model(1.0f), view, projection;
//            LaughMath::Translate(model, LaughMath::Vector3{0.0f, 0.0f, 2.0f});
            view = g_cameraService->GetCurCamera()->GetView();
            projection = g_cameraService->GetCurCamera()->GetPerspective();

            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "model"), 1, GL_FALSE, model.Get());
            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgramId(), "projection"), 1, GL_FALSE,
                               projection.Get());

            LaughMath::Vector3 coords = g_cameraService->GetCurCamera()->GetCameraCoords().pos;
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

//            LaughMath::Matrix44 model(1.0f), view, projection;;
            view = g_cameraService->GetCurCamera()->GetView();
            ClearTranslate(view);

            glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "view"), 1, GL_FALSE, view.Get());
            glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.getProgramId(), "projection"), 1, GL_FALSE,
                               projection.Get());

            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            glDepthFunc(GL_LESS);

            g_contextService->GetContext()->SwapBuffer();

        }

        static void postDraw(GLuint skyBoxVao, GLuint boxvo, GLuint texture)
        {
            glDeleteVertexArrays(1, &skyBoxVao);
            glDeleteVertexArrays(1, &boxvo);
            glDeleteTextures(1, &texture);
        }
    };
}