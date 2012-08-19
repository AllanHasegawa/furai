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

#ifndef FURAI_ANDROIDLOG_H_
#define FURAI_ANDROIDLOG_H_

#include <stdarg.h>
#include <android/log.h>

#include <furai/core/Log.h>

namespace furai {

class AndroidLog : public furai::Log {
 public:
  AndroidLog();
  virtual ~AndroidLog();

  inline void LogE(const char *fmt, ...) {
    if (this->log_level_ >= LOG_ERROR) {
      va_list args;
      va_start(args, fmt);
      __android_log_vprint(ANDROID_LOG_ERROR, this->tag_, fmt, args);
    }
  }

  inline void LogI(const char *fmt, ...) {
    if (this->log_level_ >= LOG_INFO) {
      va_list args;
      va_start(args, fmt);
      __android_log_vprint(ANDROID_LOG_INFO, this->tag_, fmt, args);
    }
  }

  inline void LogV(const char *fmt, ...) {
    if (this->log_level_ == LOG_VERBOSE) {
      va_list args;
      va_start(args, fmt);
      __android_log_vprint(ANDROID_LOG_VERBOSE, this->tag_, fmt, args);
    }
  }

 private:
  char* tag_;
};

}  // namespace furai
#endif /* FURAI_ANDROIDLOG_H_ */
