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
  Window(WindowListener* window_listener)
      : window_listener_(window_listener) {

  }

  virtual ~Window() {
  }
  ;

  virtual void Initialize() = 0;
  virtual void Destroy() = 0;
  virtual void Resize(const GLint width, const GLint height) = 0;
  virtual void DrawFrame() = 0;

  uint32_t fps() {
    return this->fps_;
  }

  GLint height() const {
    return height_;
  }

  void set_height(GLint height) {
    height_ = height;
  }

  GLint width() const {
    return width_;
  }

  void set_width(GLint width) {
    width_ = width;
  }

  bool focus() const {
    return focus_;
  }

  void set_focus(bool has_focus) {
    this->focus_ = has_focus;
    if (has_focus) {
      this->window_listener_->OnFocusGained();
    } else {
      this->window_listener_->OnFocusLost();
    }
  }

 protected:
  WindowListener* window_listener_;
  double fps_;
  GLint width_;
  GLint height_;
  bool focus_;
};

}  // namespace

#endif /* FURAI_WINDOW_H_ */
