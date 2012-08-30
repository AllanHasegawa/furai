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

#ifndef FURAI_ANDROIDWINDOW_H_
#define FURAI_ANDROIDWINDOW_H_

#include <android_native_app_glue.h>

#include <furai/core/Window.h>
#include <furai/backends/android/core/AndroidClock.h>

namespace furai {

class AndroidWindow : public furai::Window {
 public:
  AndroidWindow(WindowListener* window_listener, android_app* app);
  virtual ~AndroidWindow();

  void Initialize();
  void Destroy();
  void DrawFrame();

 private:
  android_app* android_app_;
  AndroidClock* android_clock_;

  double time_holder;
  uint32_t frames_;
  double frame_start_time;
};

}  // namespace furai
#endif /* FURAI_ANDROIDWINDOW_H_ */
