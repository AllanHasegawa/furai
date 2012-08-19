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

#ifndef FURAI_ANDROIDHELLOTRIANGLE_H_
#define FURAI_ANDROIDHELLOTRIANGLE_H_

#include <furai/backends/android/core/AndroidFullWindowListener.h>
#include <furai/core/Furai.h>

class AndroidHelloTriangle : public furai::AndroidFullWindowListener {
 public:
  AndroidHelloTriangle() {

  }
  ~AndroidHelloTriangle() {

  }

  void OnResume() {
    furai::Furai::LOG->LogV("On_Resume");
  }

  void OnPause() {
    furai::Furai::LOG->LogV("On_Pause");
  }

  void OnStop() {
    furai::Furai::LOG->LogV("On_Stop");
  }
};

#endif /* FURAI_ANDROIDHELLOTRIANGLE_H_ */
