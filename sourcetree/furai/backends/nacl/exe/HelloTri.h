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
#include <furai/backends/nacl/graphics/GLES2/gl2.h>

#include <furai/core/WindowListener.h>
#include <furai/core/Furai.h>

class HelloTriangle : public furai::WindowListener {
 public:
  HelloTriangle() {

  }

  ~HelloTriangle() {

  }

  virtual void OnStart() {
    using namespace furai;

    //Furai::LOG->LogV("HT: OnStart");
    //InternalFile* file = Furai::FS->Internal("geturl_success.html");
    //file->Open();

    //file->WaitOperationToComplete();
    /*
     char buffer[1000];
     int64_t file_size = file->info().size_;
     file->Read(0, file_size, buffer);
     file->WaitOperationToComplete();
     buffer[file_size] = '\0';
     Furai::LOG->LogV("TEXT: %s\n", buffer);
     */
    //delete file;
    //file = NULL;

    /* Error */
    /*
     file = Furai::FS->Internal("hellotriangle_not_exist.txt");
     file->Open();
     file->WaitOperationToComplete();
     if (file->status() != FILE_STATUS_ERROR) {
     file_size = file->info().size_;
     file->Read(0, file_size, buffer);
     file->WaitOperationToComplete();
     if (file->status() != FILE_STATUS_ERROR) {
     buffer[file_size] = '\0';
     Furai::LOG->LogV("TEXT: %s\n", buffer);
     }
     }
     delete file;
     file = NULL;

     */
    /* Error Close twice! */
    /*
     file = Furai::FS->Internal("hellotriangle.txt");
     file->Open();
     file->WaitOperationToComplete();
     if (file->status() != FILE_STATUS_ERROR) {
     file_size = file->info().size_;
     file->Read(0, file_size, buffer);
     file->WaitOperationToComplete();
     if (file->status() != FILE_STATUS_ERROR) {
     buffer[file_size] = '\0';
     Furai::LOG->LogV("TEXT: %s\n", buffer);
     }
     }
     file->Close();
     delete file;
     file = NULL;*/

    this->counter_ = 0;

    /*
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
    GLint linked;*/
    /*

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
        //Furai::LOG->LogE("Error linking program:\n%s\n", infoLog);
        free(infoLog);
      }
      glDeleteProgram(programObject);
      return;
    }
    // Store the program object
    this->programObject_ = programObject;*/
  }

  virtual void OnDraw(const double delta_time) {
    // Not nice to log every frame :3
    this->counter_ += delta_time;
    if (this->counter_ > 3000) {
      //furai::Furai::LOG->LogI("Delta: %g\n", delta_time);
      this->counter_ = 0;
    }

    //glClear(GL_COLOR_BUFFER_BIT);

    /*GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
        0.0f };*/
    // Clear the color buffer
    //glClear(GL_COLOR_BUFFER_BIT);
    // Use the program object
    //glUseProgram(this->programObject_);
    // Load the vertex data
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    //glEnableVertexAttribArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  virtual void OnResize(const GLint width, const GLint height) {
    //furai::Furai::LOG->LogV("Resized %d / %d\n", width, height);
    glViewport(0, 0, width, height);
  }

  virtual void OnDestroy() {

  }

  virtual void OnFocusGained() {
    using namespace furai;
    //furai::Furai::LOG->LogV("OnFocusGained\n");
  }
  virtual void OnFocusLost() {
    //furai::Furai::LOG->LogV("OnFocusLost\n");
  }

 private:
  GLfloat counter_;
  GLuint programObject_;

  GLuint LoadShader(const char *shaderSrc, GLenum type) {
    using namespace furai;

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
        //Furai::LOG->LogE("Error compiling shader:\n%s\n", infoLog);
        free(infoLog);
      }
      glDeleteShader(shader);
      return 0;
    }
    return shader;
  }
};

#endif /* FURAI_HELLOTRI_H_ */
