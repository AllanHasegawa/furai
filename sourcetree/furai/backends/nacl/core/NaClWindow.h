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

#ifndef FURAI_NACLWINDOW_H_
#define FURAI_NACLWINDOW_H_

#include <ppapi/cpp/instance.h>
#include <opengl_context/opengl_context_ptrs.h>

#include <furai/core/Window.h>
#include <furai/backends/nacl/core/NaClClock.h>

namespace furai {

class NaClWindow : public furai::Window {
 public:
  NaClWindow(pp::Instance* instance, NaClClock* clock,
             WindowListener* window_listener);
  virtual ~NaClWindow();

  void Start();
  void Destroy();
  void Resize(const GLint width, const GLint height);
  void Draw();

  bool IsRunning() {
    return true;
  }

 private:
  tumbler::SharedOpenGLContext opengl_context_;
  pp::Instance* pp_instance_;

  NaClClock* clock_;
  double time_holder;
  uint32_t frames_;
  double frame_start_time;
};

}  // namespace furai
#endif /* FURAI_NACLWINDOW_H_ */
