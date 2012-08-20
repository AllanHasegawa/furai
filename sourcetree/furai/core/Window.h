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

#ifndef FURAI_WINDOW_H_
#define FURAI_WINDOW_H_

#include <egl/egl.h>

#include <furai/core/WindowListener.h>

namespace furai {

class Window {
 public:
  virtual ~Window() {
  }
  ;

  virtual void Initialize() = 0;
  virtual void Destroy() = 0;
  virtual void DrawFrame() = 0;

  uint32_t fps() {
    return this->fps_;
  }

  EGLContext context() const {
    return context_;
  }

  void set_context(EGLContext context) {
    context_ = context;
  }

  EGLDisplay display() const {
    return display_;
  }

  void set_display(EGLDisplay display) {
    display_ = display;
  }

  int32_t height() const {
    return height_;
  }

  void set_height(int32_t height) {
    height_ = height;
  }

  EGLSurface surface() const {
    return surface_;
  }

  void set_surface(EGLSurface surface) {
    surface_ = surface;
  }

  int32_t width() const {
    return width_;
  }

  void set_width(int32_t width) {
    width_ = width;
  }

  bool focus() const {
    return focus_;
  }

  void set_focus(bool focus) {
    this->focus_ = focus;
  }

 protected:
  WindowListener* window_listener_;
  double fps_;
  EGLDisplay display_;
  EGLSurface surface_;
  EGLContext context_;
  GLint width_;
  GLint height_;
  bool focus_;
};

}  // namespace

#endif /* FURAI_WINDOW_H_ */
