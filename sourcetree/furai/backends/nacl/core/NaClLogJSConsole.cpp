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

#include <string>
#include "furai/backends/nacl/core/NaClLogJSConsole.h"

namespace furai {

NaClLogJSConsole::NaClLogJSConsole(NaClMainThreadCalls* nacl_main_thread_calls)
    : nacl_main_thread_calls_(nacl_main_thread_calls),
      kLogErrorTag_("[LOG|E] "),
      kLogInfoTag_("[LOG|I] "),
      kLogVerboseTag_("[LOG|V] ") {
  this->log_level_ = LOG_VERBOSE;
  this->buffer_ = new char[5000];
}

NaClLogJSConsole::~NaClLogJSConsole() {
  delete this->buffer_;
}

}  // namespace furai
