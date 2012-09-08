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

#include <native_app_glue/android_native_app_glue.h>

#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/core/Log.h>
#include <furai/backends/android/core/AndroidLog.h>
#include <furai/core/Furai.h>
#include <furai/core/Clock.h>
#include <furai/backends/android/core/AndroidClock.h>
#include <furai/backends/android/core/AndroidWindow.h>
#include <furai/backends/android/storage/AndroidFileSystem.h>

namespace furai {

AndroidApplication::AndroidApplication(WindowListener* window_listener,
                                       android_app* app) {
  this->log_ = new AndroidLog();
  Furai::LOG = this->log_;
  Furai::LOG->LogV("AndroidLog System failed to load! (not sarcasm)");

  this->clock_ = new AndroidClock();
  Furai::CLOCK = this->clock_;
  Furai::LOG->LogV("AndroidClock System loaded...");

  this->file_system_ = NULL;
  this->file_system_ = new AndroidFileSystem(app->activity->assetManager);
  Furai::FS = this->file_system_;

  this->android_window_ = new AndroidWindow(window_listener, app);
  this->window_ = this->android_window_;
  Furai::WINDOW = this->window_;
  Furai::LOG->LogV("AndroidWindow System loaded...");

  this->android_app_ = app;

  this->pending_window_start_ = false;
  this->pending_window_resume_ = false;

  Furai::APP = this;
  Furai::LOG->LogV("AndroidApplication loaded...");
}

AndroidApplication::~AndroidApplication() {
  delete this->log_;
  delete this->clock_;
  delete this->window_;
  delete this->file_system_;
}

void AndroidApplication::Start() {

  Furai::LOG->LogI("AA Start");
  this->android_app_->onAppCmd = &(AndroidApplication::OnCommand);
  //this->android_app_->onInputEvent = &(AndroidApplication::OnInputEvent);

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

    // by default, if the user did not provide a AndroidWindowListener,
    // the application will not render anything without focus to save battery.
    //
    // First parameter is timeout!
    // If the timeout is zero, returns immediately without blocking.
    // If the timeout is negative, waits indefinitely until an event appears.
    while ((ident = ALooper_pollAll(this->window_->IsRunning() ? 0 : -1, NULL,
                                    &events, (void**) &source)) >= 0) {

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

    this->window()->Draw();
  }
}

void AndroidApplication::OnCommand(android_app* app, int32_t command) {

  AndroidApplication* app_instance =
      static_cast<AndroidApplication*>(Furai::APP);
  AndroidWindow* a_window = app_instance->android_window_;

  Furai::LOG->LogV("AA: cmd<%d>", command);

  switch (command) {
    case APP_CMD_START:
      app_instance->pending_window_start_ = true;
      break;
    case APP_CMD_DESTROY:
      a_window->Destroy();
      break;
    case APP_CMD_SAVE_STATE:
      // The system has asked us to save our current state.  Do so.
      //engine->app->savedState = malloc(sizeof(struct saved_state));
      //*((struct saved_state*) engine->app->savedState) = engine->state;
      //engine->app->savedStateSize = sizeof(struct saved_state);
      break;
    case APP_CMD_INIT_WINDOW:
      // The window is being shown, get it ready.
      if (app_instance->android_app_->window != NULL) {
        a_window->InitializeOpenGLContext();
      }
      if (app_instance->pending_window_start_) {
        a_window->Start();
        app_instance->pending_window_start_ = false;
      }
      if (app_instance->pending_window_resume_) {
        a_window->Resume();
        app_instance->pending_window_resume_ = false;
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      a_window->DestroyOpenGLContext();
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
      a_window->set_focus(true);
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
      a_window->set_focus(false);
      break;
    case APP_CMD_RESUME:
      app_instance->pending_window_resume_ = true;
      break;
    case APP_CMD_PAUSE:
      a_window->Pause();
      break;
    case APP_CMD_STOP:
      a_window->Stop();
      break;
  }
}

int32_t AndroidApplication::OnInputEvent(android_app* app, AInputEvent* event) {
  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    //engine->animating = 1;
    //engine->state.x = AMotionEvent_getX(event, 0);
    //engine->state.y = AMotionEvent_getY(event, 0);
    return 1;
  }

  return 0;
}

}  // namespace furai
