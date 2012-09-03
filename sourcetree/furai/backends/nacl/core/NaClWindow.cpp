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

#include "furai/backends/nacl/core/NaClWindow.h"

#include <opengl_context/opengl_context.h>
#include <furai/backends/nacl/core/NaClClock.h>

namespace furai {

NaClWindow::NaClWindow(pp::Instance* pp_instance, NaClClock* clock,
                       WindowListener* window_listener)
    : Window(window_listener),
      pp_instance_(pp_instance),
      clock_(clock) {

  this->fps_ = 60;
  this->frames_ = 0;
  this->time_holder = this->frame_start_time = this->clock_->NowMS();
}

NaClWindow::~NaClWindow() {
  this->Destroy();
}

void NaClWindow::Initialize() {
  if (opengl_context_ == NULL)
    opengl_context_.reset(new tumbler::OpenGLContext(this->pp_instance_));
  opengl_context_->InvalidateContext(this->pp_instance_);
  if (!opengl_context_->MakeContextCurrent(this->pp_instance_))
    return;

  glClearColor(0.3f, 0.3f, 0.3f, 1.f);
}

void NaClWindow::Destroy() {
  opengl_context_->MakeContextCurrent(this->pp_instance_);
}

void NaClWindow::Resize(const GLint width, const GLint height) {
  this->width_ = width;
  this->height_ = height;

  if (opengl_context_ == NULL)
    opengl_context_.reset(new tumbler::OpenGLContext(this->pp_instance_));
  opengl_context_->InvalidateContext(this->pp_instance_);
  opengl_context_->ResizeContext(pp::Rect(this->width_, this->height_).size());
  if (!opengl_context_->MakeContextCurrent(this->pp_instance_))
    return;

  glViewport(0, 0, this->width_, this->height_);
}

void NaClWindow::DrawFrame() {
  if (opengl_context_ == NULL)
    return;
  opengl_context_->MakeContextCurrent(this->pp_instance_);

  NaClClock* clock = this->clock_;

  double delta_t;

  double time_now;

  time_now = clock->NowMS();
  delta_t = time_now - this->time_holder;
  this->time_holder = time_now;

  opengl_context_->FlushContext();
  this->window_listener_->OnDraw(delta_t);

  ++this->frames_;
  // Every second update "fps_"
  if ((time_now = clock->NowMS()) - this->frame_start_time >= 1000.f) {
    this->fps_ = this->frames_;
    this->frame_start_time = time_now;
    this->frames_ = 0;
  }
}

}  // namespace furai
