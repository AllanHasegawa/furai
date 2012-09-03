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

#ifndef FURAI_NACLLOG_H_
#define FURAI_NACLLOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <furai/core/Log.h>

namespace furai {

class NaClLog : public furai::Log {
 public:
  NaClLog();
  virtual ~NaClLog();

  virtual inline void LogE(const char *fmt, ...) {
    if (this->log_level_ <= LOG_ERROR) {
      va_list args;
      va_start(args, fmt);
      vfprintf(stderr, fmt, args);
      va_end(args);
    }
  }

  virtual inline void LogI(const char *fmt, ...) {
    if (this->log_level_ <= LOG_INFO) {
      va_list args;
      va_start(args, fmt);
      vfprintf(stdout, fmt, args);
      va_end(args);
    }
  }

  virtual inline void LogV(const char *fmt, ...) {
    if (this->log_level_ <= LOG_VERBOSE) {
      va_list args;
      va_start(args, fmt);
      vfprintf(stdout, fmt, args);
      va_end(args);
    }

  }
};

}  // namespace furai
#endif /* FURAI_NACLLOG_H_ */
