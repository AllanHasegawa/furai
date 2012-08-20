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

#include <android/native_activity.h>

#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/core/Log.h>
#include <furai/backends/android/core/AndroidLog.h>
#include <furai/core/Furai.h>
#include <furai/core/Clock.h>
#include <furai/backends/android/core/AndroidClock.h>
#include <furai/backends/android/core/AndroidWindow.h>

namespace furai {

AndroidApplication::AndroidApplication(WindowListener* window_listener,
                                       android_app* app) {
  AndroidApplication(window_listener, NULL, app);
}

AndroidApplication::AndroidApplication(
    WindowListener* window_listener,
    AndroidFullWindowListener* full_window_listener, android_app* app) {

  this->log_ = new AndroidLog();
  Furai::LOG = this->log_;

  this->clock_ = new AndroidClock();
  Furai::CLOCK = this->clock_;

  this->window_ = new AndroidWindow(window_listener, app);
  Furai::WINDOW = this->window_;

  this->android_app_ = app;
  this->window_listener_ = window_listener;
  this->full_window_listener_ = full_window_listener;

  Furai::WINDOW_LISTENER = this->window_listener_;
  Furai::APP = this;

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
        this->window()->Destroy();
        return;
      }
    }

    this->window()->DrawFrame();
  }
}

void AndroidApplication::OnCommand(struct android_app* app, int32_t command) {
  AndroidApplication* app_instance =
      static_cast<AndroidApplication*>(Furai::APP);
  WindowListener* listener = app_instance->window_listener();
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
        app_instance->window()->Initialize();
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      app_instance->window()->Destroy();
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
