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
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <furai/core/Window.h>
#include <furai/backends/android/core/AndroidWindow.h>
#include <furai/core/Furai.h>
#include <furai/backends/android/core/AndroidClock.h>
#include <furai/graphics/EGLConfigChooser.h>

namespace furai {

AndroidWindow::AndroidWindow(WindowListener* window_listener, android_app* app)
    : furai::Window(window_listener) {

  this->paused_ = true;
  this->stopped_ = true;

  this->window_listener_ = window_listener;
  this->android_app_ = app;
  this->fps_ = 61;
  this->frames_ = 0;

  this->android_clock_ = static_cast<AndroidClock*>(Furai::CLOCK);

  this->android_window_listener_ =
      dynamic_cast<AndroidWindowListener*>(window_listener);

  this->time_holder_ = this->frame_start_time = this->android_clock_->NowMS();

  Furai::LOG->LogV(
      this->HasAndroidWindowListener() ?
          "AndroidWindow: Advanced" : "AndroidWindow: Simple");
}

AndroidWindow::~AndroidWindow() {
}

void AndroidWindow::Start() {
  this->window_listener_->OnStart();
}

void AndroidWindow::Resize(const GLint width, const GLint height) {
  this->width_ = width;
  this->height_ = height;

  /**
   * GLESv1_CM NOT ALLOWED! NaCl compatibility
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(-1.0, 1.0, -1.0, 1.0f, 0.01, 10000.0);
   glMatrixMode(GL_MODELVIEW);
   */
  glViewport(0, 0, this->width_, this->height_);

  this->window_listener_->OnResize(width, height);
}

void AndroidWindow::Destroy() {
  this->window_listener_->OnDestroy();
}

void AndroidWindow::Draw() {
  if (this->display_ == NULL || this->android_app_->window == NULL) {
    return;
  }

  AndroidClock* clock = this->android_clock_;

  double delta_t;

  double time_now;

  time_now = clock->NowMS();
  delta_t = time_now - this->time_holder_;
  this->time_holder_ = time_now;

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

void AndroidWindow::Resume() {
  this->paused_ = this->stopped_ = false;
  if (this->HasAndroidWindowListener()) {
    this->android_window_listener_->OnResume();
  }
}

void AndroidWindow::Pause() {
  this->paused_ = true;
  if (this->HasAndroidWindowListener()) {
    this->android_window_listener_->OnPause();
  }
}

void AndroidWindow::Stop() {
  this->stopped_ = true;
  if (this->HasAndroidWindowListener()) {
    this->android_window_listener_->OnStop();
  }
}

bool AndroidWindow::IsRunning() {
  return !this->paused_ || this->HasAndroidWindowListener();
}

void AndroidWindow::InitializeOpenGLContext() {
  // initialize OpenGL ES and EGL
  Furai::LOG->LogV("AW: Initializing OpenGL Context");

  EGLint dummy, format;
  EGLint width, height;
  EGLConfig config;
  EGLint major_version, minor_version;

  this->display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  eglInitialize(this->display_, &major_version, &minor_version);
  Furai::LOG->LogI("AW: Display %d . %d\n", major_version, minor_version);

  /*
   * Try finding a EGLConfig with at least 8 bits per color compatible with
   * on-screen windows
   */

  EGLConfigChooser config_chooser(display_, 8, 8, 8, 8, 0, 0);
  config_chooser.PrintConfigs();

  if (config_chooser.GetNumberConfigs() == 0) {
    Furai::LOG->LogE("AW: No configuration found!");
  }

  // Let's grab for now the first available option :3
  config = config_chooser.GetConfig(0);

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  eglGetConfigAttrib(this->display_, config, EGL_NATIVE_VISUAL_ID, &format);

  ANativeWindow_setBuffersGeometry(this->android_app_->window, 0, 0, format);

  this->surface_ = eglCreateWindowSurface(this->display_, config,
                                          this->android_app_->window, NULL);

  const EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
  this->context_ = eglCreateContext(this->display_, config, EGL_NO_CONTEXT,
                                    context_attribs);

  Furai::LOG->LogV("AW Context: %d\n", this->context_);

  if (eglMakeCurrent(this->display_, this->surface_, this->surface_,
                     this->context_) == EGL_FALSE) {
    Furai::LOG->LogE("AW: Unable to eglMakeCurrent");
    return;
  }

  eglQuerySurface(this->display_, this->surface_, EGL_WIDTH, &width);
  eglQuerySurface(this->display_, this->surface_, EGL_HEIGHT, &height);

  // VSync
  // Looks broken at this moment for a Galaxy Note stock 4.0.3
  //eglSwapInterval(this->display_, 1);

  // Initialize GL state.
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  glClearColor(0.3, 0.3, 0.3, 1);

  this->Resize(width, height);

  return;
}

void AndroidWindow::DestroyOpenGLContext() {
  Furai::LOG->LogV("AW: Destroying OpenGL Context");

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

}  // namespace furai
