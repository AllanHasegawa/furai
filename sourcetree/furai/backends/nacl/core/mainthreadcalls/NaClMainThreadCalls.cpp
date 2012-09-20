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

  this->gl_void_functions_buffer_ =
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
      .NewCallback(&furai::NaClMainThreadCalls::CallGLVoidFunctionsCallback);
  this->pp_core_->CallOnMainThread(0, kGLVoidFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);
}

//inline void NaClMainThreadCalls::CallGLVoidFunction();

GLenum NaClMainThreadCalls::CallGLenumFunction(
    std::tr1::function<GLenum()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  gl_enum_func_pointer_ = &f;
  waiting_callback_ = true;

  pp::CompletionCallback kGLenumFunctionCallback = pp_callback_factory_
      .NewCallback(&NaClMainThreadCalls::CallGLenumFunctionCallback);
  this->pp_core_->CallOnMainThread(0, kGLenumFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);

  return ret_value_gl_enum_;
}


GLint NaClMainThreadCalls::CallGLintFunction(
    std::tr1::function<GLint()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  gl_int_func_pointer_ = &f;
  waiting_callback_ = true;

  pp::CompletionCallback kGLintFunctionCallback = pp_callback_factory_
      .NewCallback(&NaClMainThreadCalls::CallGLIntFunctionCallback);
  this->pp_core_->CallOnMainThread(0, kGLintFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);

  return ret_value_gl_int_;
}

GLuint NaClMainThreadCalls::CallGLuintFunction(
    std::tr1::function<GLuint()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  gl_uint_func_pointer_ = &f;
  waiting_callback_ = true;

  pp::CompletionCallback kGLuintFunctionCallback = pp_callback_factory_
      .NewCallback(&NaClMainThreadCalls::CallGLuintFunctionCallback);
  this->pp_core_->CallOnMainThread(0, kGLuintFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);

  return ret_value_gl_uint_;
}

GLboolean NaClMainThreadCalls::CallGLbooleanFunction(
    auto f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  gl_boolean_func_pointer_ = &f;
  waiting_callback_ = true;

  pp::CompletionCallback kGLbooleanFunctionCallback = pp_callback_factory_
      .NewCallback(&NaClMainThreadCalls::CallGLbooleanFunctionCallback);
  this->pp_core_->CallOnMainThread(0, kGLbooleanFunctionCallback, 0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_lock(&mutex_waiting_callback_);

  return ret_value_gl_boolean_;
}

void NaClMainThreadCalls::CallGLVoidFunctionsCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
  }
  number_gl_void_functions_ = 0;
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLenumFunctionCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
  }
  number_gl_void_functions_ = 0;

  ret_value_gl_enum_ = (*gl_enum_func_pointer_)();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLIntFunctionCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
  }
  number_gl_void_functions_ = 0;

  ret_value_gl_int_ = (*gl_int_func_pointer_)();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLuintFunctionCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
  }
  number_gl_void_functions_ = 0;

  ret_value_gl_uint_ = (*gl_uint_func_pointer_)();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLbooleanFunctionCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
  }
  number_gl_void_functions_ = 0;

  ret_value_gl_boolean_ = (*gl_boolean_func_pointer_)();
  waiting_callback_ = false;
  pthread_cond_signal(&cond_waiting_callback_);
  pthread_mutex_lock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLContextFlushCallback(int32_t result) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  const int n = number_gl_void_functions_;
  const std::tr1::function<void()>* fs = gl_void_functions_buffer_;
  for (int i = 0; i < n; i++) {
    fs[i]();
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
