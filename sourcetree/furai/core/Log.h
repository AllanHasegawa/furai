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

#ifndef FURAI_LOG_H_
#define FURAI_LOG_H_

namespace furai {

enum LogLevel {
  LOG_NONE = 0,
  LOG_ERROR = 1,
  LOG_INFO = 2,
  LOG_VERBOSE = 3
};

class Log {
 public:
  virtual ~Log() {
  }
  ;

  void set_log_level(const LogLevel log_level) {
    Log::log_level_ = log_level;
  }

  LogLevel log_level() {
    return Log::log_level_;
  }

  virtual void LogE(const char *fmt, ...) = 0;

  virtual void LogI(const char *fmt, ...) = 0;

  virtual void LogV(const char *fmt, ...) = 0;

 protected:
  LogLevel log_level_;
};

}  // namespace

#endif /* FURAI_LOG_H_ */
