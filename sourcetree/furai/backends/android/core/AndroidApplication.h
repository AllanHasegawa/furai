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

#include <android_native_app_glue.h>
#include <furai/core/Application.h>
#include <furai/core/WindowListener.h>
#include <furai/backends/android/core/AndroidFullWindowListener.h>

namespace furai {

class AndroidApplication : public Application {
 public:

  AndroidApplication(WindowListener* window_listener, android_app* app);
  AndroidApplication(WindowListener* window_listener,
                     AndroidFullWindowListener* full_window_listener,
                     android_app* app);
  virtual ~AndroidApplication();

  void start();

 private:
  AndroidFullWindowListener* full_window_listener_;
  android_app* android_app_;
  bool paused_;
  bool stopped_;

  static void OnCommand(struct android_app* app, int32_t command);
  static int32_t OnInputEvent(struct android_app* app, AInputEvent* event);
};

}  // namespace furai

#endif /* FURAI_ANDROIDAPPLICATION_H_ */
