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

#ifndef FURAI_WINDOWLISTENER_H_
#define FURAI_WINDOWLISTENER_H_

namespace furai {

class WindowListener {
 public:
  virtual ~WindowListener() {
  }
  ;

  virtual void OnCreate() = 0;
  virtual void OnResume() = 0;
  virtual void OnDraw(const double delta_time) = 0;
  virtual void OnResize(const int width, const int height) = 0;
  virtual void OnPause() = 0;
  virtual void OnDestroy() = 0;
};

}  // namespace
#endif /* FURAI_WINDOWLISTENER_H_ */
