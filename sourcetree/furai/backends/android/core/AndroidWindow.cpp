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

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <furai/backends/android/core/AndroidWindow.h>
#include <furai/core/Furai.h>
#include <furai/backends/android/core/AndroidClock.h>

namespace furai {

AndroidWindow::AndroidWindow(WindowListener* window_listener,
                             android_app* app) {
  this->window_listener_ = window_listener;
  this->android_app_ = app;
  this->fps_ = 61;
  this->frames_ = 0;

  this->android_clock_ = static_cast<AndroidClock*>(Furai::CLOCK);

  this->time_holder = this->frame_start_time = this->android_clock_->NowMS();
}

AndroidWindow::~AndroidWindow() {
}

void AndroidWindow::Initialize() {
  // initialize OpenGL ES and EGL

  /*
   * Here specify the attributes of the desired configuration.
   * Below, we select an EGLConfig with at least 8 bits per color
   * component compatible with on-screen windows
   */

  const EGLint attribs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_NONE };
  EGLint dummy, format;
  EGLint numConfigs;
  EGLConfig config;

  this->display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  eglInitialize(this->display_, 0, 0);

  /* Here, the application chooses the configuration it desires. In this
   * sample, we have a very simplified selection process, where we pick
   * the first EGLConfig that matches our criteria */
  eglChooseConfig(this->display_, attribs, &config, 1, &numConfigs);

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  eglGetConfigAttrib(this->display_, config, EGL_NATIVE_VISUAL_ID, &format);

  ANativeWindow_setBuffersGeometry(this->android_app_->window, 0, 0, format);

  this->surface_ = eglCreateWindowSurface(this->display_, config,
                                          this->android_app_->window, NULL);
  this->context_ = eglCreateContext(this->display_, config, NULL, NULL);

  if (eglMakeCurrent(this->display_, this->surface_, this->surface_,
                     this->context_) == EGL_FALSE) {
    Furai::LOG->LogI("Unable to eglMakeCurrent");
    return;
  }

  eglQuerySurface(this->display_, this->surface_, EGL_WIDTH, &this->width_);
  eglQuerySurface(this->display_, this->surface_, EGL_HEIGHT, &this->height_);

  // VSync
  // Looks broken at this moment for a Galaxy Note stock 4.0.3
  //eglSwapInterval(this->display_, 1);

  Furai::LOG->LogV("Display Size: %dpx by %dpx", (int) this->width_,
                   (int) this->height_);

  // Initialize GL state.
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glDisable(GL_DEPTH_TEST);

  glClearColor(0.3, 0.3, 0.3, 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrthof(-1.0, 1.0, -1.0, 1.0f, 0.01, 10000.0);
  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, this->width_, this->height_);

  this->window_listener_->OnResize(this->width_, this->height_);

  return;
}

void AndroidWindow::Destroy() {
  if (this->display_ != EGL_NO_DISPLAY) {
    eglMakeCurrent(this->display_, EGL_NO_SURFACE, EGL_NO_SURFACE,
                   EGL_NO_CONTEXT);
    if (this->context_ != EGL_NO_CONTEXT) {
      eglDestroyContext(this->display_, this->context_);
    }
    if (this->surface_ != EGL_NO_SURFACE) {
      eglDestroySurface(this->display_, this->surface_);
    }
    eglTerminate(this->display_);
  }
  this->display_ = EGL_NO_DISPLAY;
  this->context_ = EGL_NO_CONTEXT;
  this->surface_ = EGL_NO_SURFACE;
}

void AndroidWindow::DrawFrame() {
  if (this->display_ == NULL || this->android_app_->window == NULL) {
    return;
  }

  AndroidClock* clock = this->android_clock_;

  double delta_t;

  double time_now;

  time_now = clock->NowMS();
  delta_t = time_now - this->time_holder;
  this->time_holder = time_now;

  eglSwapBuffers(this->display_, this->surface_);
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
