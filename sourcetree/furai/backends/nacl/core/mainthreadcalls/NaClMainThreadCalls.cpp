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

#include "furai/backends/nacl/core/mainthreadcalls/NaClMainThreadCalls.h"

#include <ppapi/cpp/instance.h>
#include <furai/backends/nacl/core/NaClApplication.h>
#include <furai/core/Furai.h>

namespace furai {

NaClMainThreadCalls::NaClMainThreadCalls(pp::Core* pp_core, NaClWindow* window)
    : pp_core_(pp_core),
      window_(window),
      kMaxGLVoidFunctions_(1000),
      number_gl_void_functions_(0),
      pp_callback_factory_(this) {

  pthread_cond_init(&cond_waiting_callback_, NULL);
  pthread_mutex_init(&mutex_waiting_callback_, NULL);

  gl_void_functions_buffer_ =
      new std::tr1::function<void()>[kMaxGLVoidFunctions_];
}

NaClMainThreadCalls::~NaClMainThreadCalls() {
  delete[] this->gl_void_functions_buffer_;

  pthread_cond_destroy(&cond_waiting_callback_);
  pthread_mutex_destroy(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLContextFlush() {
  SyncGLVoidFunctions();
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  pp::CompletionCallback kGLContextFlushCallback = pp_callback_factory_
      .NewCallback(&NaClMainThreadCalls::CallGLContextFlushCallback);
  this->pp_core_->CallOnMainThread(0, kGLContextFlushCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::SyncGLVoidFunctions() {
  if (number_gl_void_functions_ == 0) {
    return;
  }
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  pp::CompletionCallback kGLVoidFunctionCallback = pp_callback_factory_
      .NewCallback(&furai::NaClMainThreadCalls::CallGLvoidFunctionsCallback);
  this->pp_core_->CallOnMainThread(0, kGLVoidFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLvoidFunctionsCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  const int n = number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }

  number_gl_void_functions_ = 0;
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLintFunctionCallback(
    int32_t result, int& return_value, const std::tr1::function<int()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }
  number_gl_void_functions_ = 0;

  return_value = f();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLenumFunctionCallback(
    int32_t result, GLenum& return_value,
    const std::tr1::function<GLenum()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }
  number_gl_void_functions_ = 0;

  return_value = f();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLuintFunctionCallback(
    int32_t result, GLuint& return_value,
    const std::tr1::function<GLuint()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }
  number_gl_void_functions_ = 0;

  return_value = f();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLbooleanFunctionCallback(
    int32_t result, GLboolean& return_value,
    const std::tr1::function<GLboolean()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }
  number_gl_void_functions_ = 0;

  return_value = f();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLContextFlushCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  for (int i = 0; i < n; i++) {
    gl_void_functions_buffer_[i]();
  }
  number_gl_void_functions_ = 0;

  this->window_->opengl_context()->MakeContextCurrent(
      static_cast<pp::Instance*>(static_cast<furai::NaClApplication*>(furai::Furai::APP)));
  this->window_->opengl_context()->FlushContext();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

}  // namespace furai
