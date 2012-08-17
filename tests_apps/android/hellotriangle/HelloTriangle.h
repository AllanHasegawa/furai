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

#ifndef FURAI_HELLOTRIANGLE_H_
#define FURAI_HELLOTRIANGLE_H_


#include <GLES/gl.h>

#include <furai/core/WindowListener.h>
#include <furai/core/Furai.h>

class HelloTriangle : public furai::WindowListener {
 public:
  HelloTriangle() {

  }
  ~HelloTriangle() {

  }

  void OnCreate() {
    furai::Furai::LOG->LogV("On_Create");
  }
  void OnResume() {
    furai::Furai::LOG->LogV("On_Resume");
  }
  void OnDraw(const double delta_time) {
    furai::Furai::LOG->LogV("On_Draw");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat vertices[] =
        { -1.f, -1.f, -3.0f, 1.0f, -1.0f, -3.0f, .0f, 1.f, -3.f };


    glLoadIdentity();

    glColor4f(1, 0, 0, 1);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
  }
  void OnResize(const int width, const int height) {
    furai::Furai::LOG->LogV("On_Resize %dpx by %dpx", width, height);
    glClearColor(0, 0, 0, 1);
  }

  void OnPause() {
    furai::Furai::LOG->LogV("On_Pause");
  }

  void OnDestroy() {
    furai::Furai::LOG->LogV("On_Destroy");
  }
};

#endif /* FURAI_HELLOTRIANGLE_H_ */
