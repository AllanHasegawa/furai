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

#ifndef FURAI_NACLLOGJSCONSOLE_H_
#define FURAI_NACLLOGJSCONSOLE_H_

#include <utility>
#include <string>
#include <cstdarg>
#include <stdio.h>

#include <ppapi/utility/completion_callback_factory.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/var.h>

#include <furai/backends/nacl/core/NaClApplication.h>
#include <furai/core/Log.h>
#include <furai/core/Furai.h>

namespace furai {

class NaClLogJSConsole : public furai::Log {
 public:
  NaClLogJSConsole(NaClMainThreadCalls* nacl_main_thread_calls);
  virtual ~NaClLogJSConsole();

  virtual inline void LogE(const char *fmt, ...) {
    if (this->log_level_ <= LOG_ERROR) {
      va_list args;
      va_start(args, fmt);
      vsprintf(this->buffer_, fmt, args);
      va_end(args);
      std::string buffer_str(this->buffer_);

      std::string log_message = kLogErrorTag_ + buffer_str + "\n";

      this->nacl_main_thread_calls_->CallPostMessage(log_message);
    }
  }

  virtual inline void LogI(const char *fmt, ...) {
    if (this->log_level_ <= LOG_INFO) {
      va_list args;
      va_start(args, fmt);
      vsprintf(this->buffer_, fmt, args);
      va_end(args);
      std::string buffer_str(this->buffer_);
      std::string log_message = kLogInfoTag_ + buffer_str + "\n";

      this->nacl_main_thread_calls_->CallPostMessage(log_message);
    }
  }

  virtual inline void LogV(const char *fmt, ...) {
    if (this->log_level_ <= LOG_VERBOSE) {
      va_list args;
      va_start(args, fmt);
      vsprintf(this->buffer_, fmt, args);
      va_end(args);
      std::string buffer_str(this->buffer_);

      std::string log_message = kLogVerboseTag_ + buffer_str + "\n";

      this->nacl_main_thread_calls_->CallPostMessage(log_message);

    }
  }

 private:
  NaClMainThreadCalls* nacl_main_thread_calls_;
  char* buffer_;
  const std::string kLogErrorTag_;
  const std::string kLogInfoTag_;
  const std::string kLogVerboseTag_;
};

}  // namespace furai
#endif /* FURAI_NACLLOGJSCONSOLE_H_ */
