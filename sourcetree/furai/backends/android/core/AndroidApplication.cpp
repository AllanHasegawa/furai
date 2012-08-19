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
#include <furai/core/Log.h>
#include <furai/backends/android/core/AndroidLog.h>
#include <furai/core/Furai.h>
#include <furai/core/Clock.h>
#include <furai/backends/android/core/AndroidClock.h>

namespace furai {

AndroidApplication::AndroidApplication(WindowListener* window_listener,
                                       android_app* app) {
  AndroidApplication(window_listener, NULL, app);
}

AndroidApplication::AndroidApplication(
    WindowListener* window_listener,
    AndroidFullWindowListener* full_window_listener, android_app* app) {

  this->log_ = new AndroidLog();
  this->clock_ = new AndroidClock();
  this->android_app_ = app;
  this->window_listener_ = window_listener;
  this->full_window_listener_ = full_window_listener;

  /*
   * Populate the GLOBAL variables from Furai!
   *
   * Note however, the backend Application class still needs to take
   * care of them :)
   */

  Furai::WINDOW_LISTENER = this->window_listener_;
  Furai::LOG = this->log_;
  Furai::APP = this;
  Furai::CLOCK = this->clock_;

  this->paused_ = true;
  this->stopped_ = true;
}

AndroidApplication::~AndroidApplication() {
  delete this->log_;
  delete this->clock_;
}

void AndroidApplication::start() {

  this->android_app_->onAppCmd = &(AndroidApplication::OnCommand);
  this->android_app_->onInputEvent = &(AndroidApplication::OnInputEvent);

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
  double t1, t2, delta_t;

  AndroidClock* clock = static_cast<AndroidClock*>(this->clock_);

  t1 = clock->now_ms();

  while (1) {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source;

    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident = ALooper_pollAll(this->paused_ ? -1 : 0, NULL, &events,
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

    t2 = clock->now_ms();
    delta_t = t2 - t1;
    this->DrawFrame(delta_t);
    t1 = clock->now_ms();
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

  Furai::LOG->LogV("Display Sizee: %dpx by %dpx", (int) w, (int) h);

  Furai::APP->window()->set_display(display);
  Furai::APP->window()->set_context(context);
  Furai::APP->window()->set_surface(surface);
  Furai::APP->window()->set_width(w);
  Furai::APP->window()->set_height(h);

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

void AndroidApplication::DrawFrame(const double delta_time) {
  if (this->window_.display() == NULL || this->android_app_->window == NULL) {
    return;
  }

  this->window_listener_->OnDraw(delta_time);

  eglSwapBuffers(this->window_.display(), this->window_.surface());
}

void AndroidApplication::OnCommand(struct android_app* app, int32_t command) {
  AndroidApplication* app_instance =
      static_cast<AndroidApplication*>(Furai::APP);
  WindowListener* listener = app_instance->window_listener_;
  AndroidFullWindowListener* alistener = app_instance->full_window_listener_;

  switch (command) {
    case APP_CMD_RESUME:
      app_instance->paused_ = false;
      app_instance->stopped_ = false;
      if (alistener != NULL) {
        alistener->OnResume();
      }
      break;
    case APP_CMD_PAUSE:
      app_instance->paused_ = true;
      if (alistener != NULL) {
        alistener->OnPause();
      }
      break;
    case APP_CMD_START:
      listener->OnCreate();
      break;
    case APP_CMD_DESTROY:
      listener->OnDestroy();
      break;
    case APP_CMD_STOP:
      app_instance->stopped_ = true;
      if (alistener != NULL) {
        alistener->OnStop();
      }
      break;
    case APP_CMD_SAVE_STATE:
      // The system has asked us to save our current state.  Do so.
      //engine->app->savedState = malloc(sizeof(struct saved_state));
      //*((struct saved_state*) engine->app->savedState) = engine->state;
      //engine->app->savedStateSize = sizeof(struct saved_state);
      break;
    case APP_CMD_INIT_WINDOW:
      // The window is being shown, get it ready.
      Furai::LOG->LogV("AndroidApplication: INIT WINDOW");
      if (app_instance->android_app_->window != NULL) {
        app_instance->InitializeNativeWindow();
        app_instance->DrawFrame(0);
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      app_instance->DestroyNativeWindow();
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
      //app_instance->get_window()->set_focus(true);
      listener->OnFocusGained();
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
      //app_instance->get_window()->set_focus(false);
      listener->OnFocusLost();
      break;
  }
}

int32_t AndroidApplication::OnInputEvent(struct android_app* app,
                                         AInputEvent* event) {
  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    //engine->animating = 1;
    //engine->state.x = AMotionEvent_getX(event, 0);
    //engine->state.y = AMotionEvent_getY(event, 0);
    return 1;
  }

  return 0;
}

}  // namespace furai
