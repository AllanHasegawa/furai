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

#include <functional>
#include <tr1/functional>

#include <furai/core/Furai.h>
#include <furai/backends/nacl/graphics/GLES2/gl2.h>
#include <furai/backends/nacl/core/NaClApplication.h>
#include <furai/backends/nacl/core/mainthreadcalls/NaClMainThreadCalls.h>

namespace furai {

void GLES2UseProgram(const GLuint &program) {

  NaClApplication* kNaClApp = static_cast<NaClApplication*>(furai::Furai::APP);
  NaClMainThreadCalls* kNaClMainThreadCalls = kNaClApp->main_thread_calls();
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UseProgram, program);
  kNaClMainThreadCalls->CallGLVoidFunction(f);
}

}
