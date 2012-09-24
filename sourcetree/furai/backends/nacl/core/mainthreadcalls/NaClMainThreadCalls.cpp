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

NaClMainThreadCalls::NaClMainThreadCalls(pp::Core* pp_core)
    : pp_core_(pp_core),
      kMaxGLVoidFunctions_(1000),
      number_gl_void_functions_(0),
      number_post_messages_(0),
      kMaxPostMessages_(100),
      post_message_sync_pending_(false) {

  pthread_cond_init(&cond_waiting_callback_, NULL);
  pthread_mutex_init(&mutex_waiting_callback_, NULL);

  gl_void_functions_buffer_ =
      new std::tr1::function<void()>[kMaxGLVoidFunctions_];

  post_message_buffer_ = new std::string[kMaxPostMessages_];
}

NaClMainThreadCalls::~NaClMainThreadCalls() {
  delete[] this->gl_void_functions_buffer_;
  delete[] this->post_message_buffer_;

  pthread_cond_destroy(&cond_waiting_callback_);
  pthread_mutex_destroy(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLvoidFunction(
    const std::tr1::function<void()>& f) {
  if (number_gl_void_functions_ == kMaxGLVoidFunctions_) {
    SyncGLVoidFunctions();
  }

  gl_void_functions_buffer_[number_gl_void_functions_] = f;
  ++number_gl_void_functions_;
}

int NaClMainThreadCalls::CallGLintFunction(const std::tr1::function<int()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  gl_int_f_ = f;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(&NaClMainThreadCalls::CallGLintFunctionCallback,
                             this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }

  pthread_mutex_unlock(&mutex_waiting_callback_);

  return gl_int_return_value_;
}

GLenum NaClMainThreadCalls::CallGLenumFunction(
    const std::tr1::function<GLenum()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  gl_enum_f_ = f;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(&NaClMainThreadCalls::CallGLenumFunctionCallback,
                             this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }

  pthread_mutex_unlock(&mutex_waiting_callback_);

  return gl_enum_return_value_;
}

GLuint NaClMainThreadCalls::CallGLuintFunction(
    const std::tr1::function<GLuint()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  gl_uint_f_ = f;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(&NaClMainThreadCalls::CallGLuintFunctionCallback,
                             this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }

  pthread_mutex_unlock(&mutex_waiting_callback_);

  return gl_uint_return_value_;
}

GLboolean NaClMainThreadCalls::CallGLbooleanFunction(
    const std::tr1::function<GLboolean()>& f) {
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  gl_boolean_f_ = f;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(
          &NaClMainThreadCalls::CallGLbooleanFunctionCallback, this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }

  pthread_mutex_unlock(&mutex_waiting_callback_);

  return gl_boolean_return_value_;
}

void NaClMainThreadCalls::CallGLContextFlush() {
  pthread_mutex_lock(&mutex_waiting_callback_);
  waiting_callback_ = true;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(&NaClMainThreadCalls::CallGLContextFlushCallback,
                             this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_unlock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::SyncGLVoidFunctions() {
  pthread_mutex_lock(&mutex_waiting_callback_);
  if (number_gl_void_functions_ == 0) {
    pthread_mutex_unlock(&mutex_waiting_callback_);
    return;
  }
  waiting_callback_ = true;

  this->pp_core_->CallOnMainThread(
      0,
      pp::CompletionCallback(&NaClMainThreadCalls::CallGLvoidFunctionsCallback,
                             this),
      0);

  while (waiting_callback_) {
    pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
  }
  pthread_mutex_unlock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallPostMessage(const std::string& message) {
  pthread_mutex_lock(&mutex_waiting_callback_);

  if (number_post_messages_ == kMaxPostMessages_) {
    number_post_messages_--;
  }

  this->post_message_buffer_[number_post_messages_] = message;
  number_post_messages_++;

  if (!post_message_sync_pending_) {
    this->pp_core_->CallOnMainThread(
        0,
        pp::CompletionCallback(&NaClMainThreadCalls::CallPostMessageCallback,
                               this),
        0);
  }

  pthread_mutex_unlock(&mutex_waiting_callback_);
}

void NaClMainThreadCalls::CallGLvoidFunctionsCallback(void* data,
                                                      int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallGLintFunctionCallback(void* data,
                                                    int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->gl_int_return_value_ = instance->gl_int_f_();
  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallGLenumFunctionCallback(void* data,
                                                     int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->gl_enum_return_value_ = instance->gl_enum_f_();
  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallGLuintFunctionCallback(void* data,
                                                     int32_t result) {

  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->gl_uint_return_value_ = instance->gl_uint_f_();
  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallGLbooleanFunctionCallback(void* data,
                                                        int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;

  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->gl_boolean_return_value_ = instance->gl_boolean_f_();
  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallGLContextFlushCallback(void* data,
                                                     int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_gl_void_functions_;
  for (int i = 0; i < n; i++) {
    instance->gl_void_functions_buffer_[i]();
  }
  instance->number_gl_void_functions_ = 0;

  instance->window_->opengl_context()->MakeContextCurrent(
      static_cast<pp::Instance*>(static_cast<furai::NaClApplication*>(furai::Furai::APP)));
  instance->window_->opengl_context()->FlushContext();
  instance->waiting_callback_ = false;
  pthread_cond_signal(&(instance->cond_waiting_callback_));
  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

void NaClMainThreadCalls::CallPostMessageCallback(void* data, int32_t result) {
  NaClMainThreadCalls* instance = static_cast<NaClMainThreadCalls*>(data);
  pthread_mutex_lock(&(instance->mutex_waiting_callback_));

  const int n = instance->number_post_messages_;
  pp::Instance* pp_instance =
      static_cast<pp::Instance*>(static_cast<furai::NaClApplication*>(furai::Furai::APP));

  for (int i = 0; i < n; i++) {
    pp_instance->PostMessage(instance->post_message_buffer_[i]);
  }

  instance->number_post_messages_ = 0;
  instance->post_message_sync_pending_ = false;

  pthread_mutex_unlock(&(instance->mutex_waiting_callback_));
}

}  // namespace furai
