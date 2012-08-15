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

#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/backends/android/core/config.h>

namespace furai {

AndroidApplication::AndroidApplication() {
  // TODO Auto-generated constructor stub

}

AndroidApplication::~AndroidApplication() {
  // TODO Auto-generated destructor stub
}

void AndroidApplication::OnDestroy(ANativeActivity* activity) {
  LOGV("Native OnDestroy");
}

void AndroidApplication::OnStart(ANativeActivity* activity) {
  LOGV("Native OnStart");
}

void AndroidApplication::OnResume(ANativeActivity* activity) {
  LOGV("Native OnResume");
}

void AndroidApplication::OnSaveInstanceState(ANativeActivity* activity) {

}

void AndroidApplication::OnPause(ANativeActivity* activity) {

}

void AndroidApplication::OnStop(ANativeActivity* activity) {

}

void AndroidApplication::OnConfigurationChanged(ANativeActivity* activity) {

}

void AndroidApplication::OnLowMemory(ANativeActivity* activity) {

}

void AndroidApplication::OnWindowFocusChanged(ANativeActivity* activity) {

}

void AndroidApplication::OnNativeWindowCreated(ANativeActivity* activity) {

}

void AndroidApplication::OnNativeWindowDestroyed(ANativeActivity* activity) {

}

void AndroidApplication::OnInputQueueCreated(ANativeActivity* activity) {

}

void AndroidApplication::OnInputQueueDestroyed(ANativeActivity* activity) {

}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState,
                              size_t savedStateSize) {

  LOGV("Creating: %p\n", activity);
  activity->callbacks->onDestroy = &furai::AndroidApplication::OnDestroy;
  activity->callbacks->onStart = &furai::AndroidApplication::OnStart;
  activity->callbacks->onResume = &furai::AndroidApplication::OnResume;
  activity->callbacks->onSaveInstanceState =
      &furai::AndroidApplication::OnSaveInstanceState;
  activity->callbacks->onPause = &furai::AndroidApplication::OnPause;
  activity->callbacks->onStop = &furai::AndroidApplication::OnStop;
  activity->callbacks->onConfigurationChanged =
      &furai::AndroidApplication::OnConfigurationChanged;
  activity->callbacks->onLowMemory = &furai::AndroidApplication::OnLowMemory;
  activity->callbacks->onWindowFocusChanged =
      &furai::AndroidApplication::OnWindowFocusChanged;
  activity->callbacks->onNativeWindowCreated =
      &furai::AndroidApplication::OnNativeWindowCreated;
  activity->callbacks->onNativeWindowDestroyed =
      &furai::AndroidApplication::OnNativeWindowDestroyed;
  activity->callbacks->onInputQueueCreated =
      &furai::AndroidApplication::OnInputQueueCreated;
  activity->callbacks->onInputQueueDestroyed =
      &furai::AndroidApplication::OnInputQueueDestroyed;

  //activity->instance = android_app_create(activity, savedState, savedStateSize);
}

}  // namespace furai
