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
#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/native_activity.h>

#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/log/Log.h>
#include <furai/backends/android/log/AndroidLog.h>
#include <furai/core/Furai.h>

namespace furai {

AndroidApplication* AndroidApplication::instance_ = NULL;

AndroidApplication::AndroidApplication(WindowListener* window_listener,
                                       android_app* app) {

  this->android_app_ = app;

  /*
   * Populate the GLOBAL variables from Furai!
   *
   * Note however, the backend Application class still needs to take
   * care of them :)
   */

  Furai::WINDOW_LISTENER = this->window_listener_ = window_listener;
  Furai::LOG = this->log_ = new AndroidLog();
  Furai::APP = AndroidApplication::instance_ = this;
}

AndroidApplication::~AndroidApplication() {
  delete this->log_;
}

void AndroidApplication::start() {

  this->android_app_->onAppCmd = &(AndroidApplication::OnCommand);
  this->android_app_->onInputEvent = NULL;

  // Prepare to monitor accelerometer
  /*
   engine.sensorManager = ASensorManager_getInstance();
   engine.accelerometerSensor = ASensorManager_getDefaultSensor(
   engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
   engine.sensorEventQueue = ASensorManager_createEventQueue(
   engine.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL);
   */

  //if (state->savedState != NULL) {
  // We are starting with a previous saved state; restore from it.
  //engine.state = *(struct saved_state*) state->savedState;
  //}
  // loop waiting for stuff to do.
  while (1) {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source;

    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident = ALooper_pollAll(true ? 0 : -1, NULL, &events,
                                    (void**) &source)) >= 0) {

      // Process this event.
      if (source != NULL) {
        source->process(this->android_app_, source);
      }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER) {
        /*
         if (engine.accelerometerSensor != NULL) {
         ASensorEvent event;
         while (ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1)
         > 0) {
         LOGI(
         "accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
         }
         }*/
      }

      // Check if we are exiting.
      if (this->android_app_->destroyRequested != 0) {
        this->DestroyNativeWindow();
        return;
      }
    }

    if (true) {
      // Done with events; draw next animation frame.

      // Drawing is throttled to the screen update rate, so there
      // is no need to do timing here.
      this->DrawFrame();
    }
  }
}

void AndroidApplication::InitializeNativeWindow() {
  // initialize OpenGL ES and EGL

  /*
   * Here specify the attributes of the desired configuration.
   * Below, we select an EGLConfig with at least 8 bits per color
   * component compatible with on-screen windows
   */

  const EGLint attribs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_NONE };
  EGLint w, h, dummy, format;
  EGLint numConfigs;
  EGLConfig config;
  EGLSurface surface;
  EGLContext context;

  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  eglInitialize(display, 0, 0);

  /* Here, the application chooses the configuration it desires. In this
   * sample, we have a very simplified selection process, where we pick
   * the first EGLConfig that matches our criteria */
  eglChooseConfig(display, attribs, &config, 1, &numConfigs);

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

  ANativeWindow_setBuffersGeometry(this->android_app_->window, 0, 0, format);

  surface = eglCreateWindowSurface(display, config, this->android_app_->window,
                                   NULL);
  context = eglCreateContext(display, config, NULL, NULL);

  if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
    Furai::LOG->LogI("Unable to eglMakeCurrent");
    return;
  }

  eglQuerySurface(display, surface, EGL_WIDTH, &w);
  eglQuerySurface(display, surface, EGL_HEIGHT, &h);

  AndroidApplication::instance_->window_.set_display(display);
  AndroidApplication::instance_->window_.set_context(context);
  AndroidApplication::instance_->window_.set_surface(surface);
  AndroidApplication::instance_->window_.set_width(w);
  AndroidApplication::instance_->window_.set_height(h);

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
  glViewport(0, 0, w, h);

  this->window_listener_->OnResize(w, h);

  return;
}

void AndroidApplication::DestroyNativeWindow() {
  if (this->window_.display() != EGL_NO_DISPLAY) {
    eglMakeCurrent(this->window_.display(), EGL_NO_SURFACE, EGL_NO_SURFACE,
                   EGL_NO_CONTEXT);
    if (this->window_.context() != EGL_NO_CONTEXT) {
      eglDestroyContext(this->window_.display(), this->window_.context());
    }
    if (this->window_.surface() != EGL_NO_SURFACE) {
      eglDestroySurface(this->window_.display(), this->window_.surface());
    }
    eglTerminate(this->window_.display());
  }
  this->window_.set_display(EGL_NO_DISPLAY);
  this->window_.set_context(EGL_NO_CONTEXT);
  this->window_.set_surface(EGL_NO_SURFACE);
}

void AndroidApplication::DrawFrame() {
  if (this->window_.display() == NULL || this->android_app_->window == NULL) {
    return;
  }

  this->window_listener_->OnDraw(0);

  eglSwapBuffers(this->window_.display(), this->window_.surface());
}

void AndroidApplication::OnCommand(struct android_app* app,
                                          int32_t command) {
  switch (command) {
    case APP_CMD_RESUME:
      Furai::LOG->LogV("AA: APP_CMD_RESUME");
      AndroidApplication::instance_->window_listener_->OnResume();
      break;
    case APP_CMD_PAUSE:
      AndroidApplication::instance_->window_listener_->OnPause();
      break;
    case APP_CMD_START:
      AndroidApplication::instance_->window_listener_->OnCreate();
      break;
    case APP_CMD_DESTROY:
      AndroidApplication::instance_->window_listener_->OnDestroy();
      break;
    case APP_CMD_STOP:
      AndroidApplication::instance_->window_listener_->OnPause();
      break;
    case APP_CMD_SAVE_STATE:
      // The system has asked us to save our current state.  Do so.
      //engine->app->savedState = malloc(sizeof(struct saved_state));
      //*((struct saved_state*) engine->app->savedState) = engine->state;
      //engine->app->savedStateSize = sizeof(struct saved_state);
      break;
    case APP_CMD_INIT_WINDOW:
      // The window is being shown, get it ready.
      if (AndroidApplication::instance_->android_app_->window != NULL) {
        AndroidApplication::instance_->InitializeNativeWindow();
        AndroidApplication::instance_->DrawFrame();
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      AndroidApplication::instance_->DestroyNativeWindow();
      break;
    case APP_CMD_GAINED_FOCUS:
      /*
       // When our app gains focus, we start monitoring the accelerometer.
       if (engine->accelerometerSensor != NULL) {
       ASensorEventQueue_enableSensor(engine->sensorEventQueue,
       engine->accelerometerSensor);
       // We'd like to get 60 events per second (in us).
       ASensorEventQueue_setEventRate(engine->sensorEventQueue,
       engine->accelerometerSensor,
       (1000L / 60) * 1000);
       }
       */
      break;
    case APP_CMD_LOST_FOCUS:
      /*
       // When our app loses focus, we stop monitoring the accelerometer.
       // This is to avoid consuming battery while not being used.
       if (engine->accelerometerSensor != NULL) {
       ASensorEventQueue_disableSensor(engine->sensorEventQueue,
       engine->accelerometerSensor);
       }
       // Also stop animating.
       engine->animating = 0;
       engine_draw_frame (engine);
       */
      break;
  }
}
}  // namespace furai
