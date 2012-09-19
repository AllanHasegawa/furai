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

#ifndef FURAI_FURAI_H_
#define FURAI_FURAI_H_

#include <GLES2/gl2.h>
#include <furai/backends/nacl/graphics/GLES2/gl2.h>

#include <furai/core/Log.h>
#include <furai/core/Application.h>
#include <furai/core/WindowListener.h>
#include <furai/core/Clock.h>
#include <furai/core/Window.h>
#include <furai/storage/FileSystem.h>

namespace furai {

class Furai {
 public:
  static Application* APP;
  static Log* LOG;
  static WindowListener* WINDOW_LISTENER;
  static Clock* CLOCK;
  static Window* WINDOW;
  static FileSystem* FS;
};

}  // namespace

#endif /* FURAI_FURAI_H_ */
