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

#ifndef FURAI_ANDROIDAPPLICATION_H_
#define FURAI_ANDROIDAPPLICATION_H_

#include <jni.h>
#include <android/native_activity.h>

namespace furai {

class AndroidApplication {
 public:
  AndroidApplication();
  virtual ~AndroidApplication();

 protected:
  static void OnDestroy(ANativeActivity* activity);
  static void OnStart(ANativeActivity* activity);
  static void OnResume(ANativeActivity* activity);
  static void OnSaveInstanceState(ANativeActivity* activity);
  static void OnPause(ANativeActivity* activity);
  static void OnStop(ANativeActivity* activity);
  static void OnConfigurationChanged(ANativeActivity* activity);
  static void OnLowMemory(ANativeActivity* activity);
  static void OnWindowFocusChanged(ANativeActivity* activity);
  static void OnNativeWindowCreated(ANativeActivity* activity);
  static void OnNativeWindowDestroyed(ANativeActivity* activity);
  static void OnInputQueueCreated(ANativeActivity* activity);
  static void OnInputQueueDestroyed(ANativeActivity* activity);
};

}  // namespace furai

#endif /* FURAI_ANDROIDAPPLICATION_H_ */
