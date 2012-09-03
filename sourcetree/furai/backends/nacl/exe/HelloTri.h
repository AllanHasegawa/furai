/*
 -----------------------------------------------------------------------------
 This source file is part of the Project Furai.
 For more information, go to:
 http://code.google.com/p/furai/
 -----------------------------------------------------------------------------

 Copyright 2012 Allan Yoshio Hasegawa

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 -----------------------------------------------------------------------------
 */

#ifndef FURAI_HELLOTRI_H_
#define FURAI_HELLOTRI_H_

#include <stdio.h>

#include <GLES2/gl2.h>
#include <furai/core/WindowListener.h>
#include <furai/core/Furai.h>

class HelloTri : public furai::WindowListener {
 public:
  HelloTri() {

  }

  ~HelloTri() {

  }

  virtual void OnCreate() {

    GLchar vShaderStr[] = "attribute vec4 vPosition; \n"
        "void main() \n"
        "{ \n"
        " gl_Position = vPosition; \n"
        "} \n";
    GLchar fShaderStr[] = "precision mediump float; \n"
        "void main() \n"
        "{ \n"
        " gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
        "} \n";
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = this->LoadShader(vShaderStr, GL_VERTEX_SHADER);
    fragmentShader = this->LoadShader(fShaderStr, GL_FRAGMENT_SHADER);
    // Create the program object
    programObject = glCreateProgram();
    if (programObject == 0)
      return;  // 0;
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");
    // Link the program
    glLinkProgram(programObject);
    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!linked) {
      GLint infoLen = 0;
      glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
      if (infoLen > 1) {
        char* infoLog = (char*) malloc(sizeof(char) * infoLen);
        glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
        printf("Error linking program:\n%s\n", infoLog);
        free(infoLog);
      }
      glDeleteProgram(programObject);
      return;  // FALSE;
    }
    // Store the program object
    this->programObject_ = programObject;
  }

  virtual void OnDraw(const double delta_time) {
    //glClearColor(0.3f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
        0.0f };
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // Use the program object
    glUseProgram(this->programObject_);
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  virtual void OnResize(const GLint width, const GLint height) {
    glViewport(0, 0, 10, 10);
  }

  virtual void OnDestroy() {

  }

  virtual void OnFocusGained() {

  }
  virtual void OnFocusLost() {

  }

 private:
  GLuint programObject_;

  GLuint LoadShader(const char *shaderSrc, GLenum type) {
    GLuint shader;
    GLint compiled;
    // Create the shader object
    shader = glCreateShader(type);
    if (shader == 0)
      return 0;
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);
    // Compile the shader
    glCompileShader(shader);
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      GLint infoLen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
      if (infoLen > 1) {
        char* infoLog = (char*) malloc(sizeof(char) * infoLen);
        glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
        printf("Error compiling shader:\n%s\n", infoLog);
        free(infoLog);
      }
      glDeleteShader(shader);
      return 0;
    }
    return shader;
  }
};

#endif /* FURAI_HELLOTRI_H_ */
