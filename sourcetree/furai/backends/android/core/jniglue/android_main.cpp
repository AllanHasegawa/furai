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

//#include <furai/backends/android/jniglue/furai_android_native_app_glue.h>
#include <furai/core/Application.h>
#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/backends/android/core/jniglue/MyCycle.h>
#include <furai/backends/android/core/jniglue/furai_android_native_app_glue.h>
#include <android/native_activity.h>

void android_main(struct android_app *app) {
  furai::WindowListener *my_cycle = new MyCycle();
  furai::Application* application = new furai::AndroidApplication(my_cycle,
                                                                  app);
  application->start();
}
