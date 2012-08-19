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

#include <furai/backends/android/core/AndroidLog.h>

namespace furai {

AndroidLog::AndroidLog() {
  this->tag_ = new char[6];
  this->tag_[0] = 'F';
  this->tag_[1] = 'u';
  this->tag_[2] = 'r';
  this->tag_[3] = 'a';
  this->tag_[4] = 'i';
  this->tag_[5] = '\0';

  this->log_level_ = LOG_VERBOSE;
}

AndroidLog::~AndroidLog() {
  delete this->tag_;
}

}  // namespace furai
