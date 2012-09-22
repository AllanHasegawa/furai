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

#ifndef FURAI_NACLMAINTHREADCALLS_H_
#define FURAI_NACLMAINTHREADCALLS_H_

#include <cstring>
#include <vector>

#include <tr1/functional>

#include <GLES2/gl2.h>

#include <ppapi/utility/completion_callback_factory.h>
#include <ppapi/cpp/completion_callback.h>

#include <furai/backends/nacl/graphics/GLES2/gl2.h>
#include <furai/backends/nacl/core/NaClWindow.h>

namespace pp {
class Core;
}  //namespace

namespace furai {

/*

 class NaClVoidFunctionHandlerInterface {
 public:
 virtual ~NaClVoidFunctionHandlerInterface() {

 }
 virtual void Run() = 0;
 };

 template <class R, class... Args>
 class NaClVoidFunctionHandler : public NaClVoidFunctionHandlerInterface {
 public:
 std::tr1::function<R(Args...)> function_;

 NaClVoidFunctionHandler() {

 }

 virtual ~NaClVoidFunctionHandler() {

 }

 void set_function(std::tr1::function<R(Args...)> function) {
 function_ = function;
 }

 void Run() {
 //(*function_)();
 }
 };

 template<class R, class T>
 class NaClReturnFunctionHandler {
 public:
 std::tr1::function<R(T)> function_;

 NaClReturnFunctionHandler(std::tr1::function<R(T)>& function)
 : function_(function) {

 }

 virtual ~NaClReturnFunctionHandler() {

 }

 R run() {
 return function_();
 }
 };
 */

class NaClMainThreadCalls {
 public:
  NaClMainThreadCalls(pp::Core* pp_core, NaClWindow* window);

  virtual ~NaClMainThreadCalls();

  //template<class R, class... Args>
  void CallGLvoidFunction(std::tr1::function<void()> f) {
    /*if (number_gl_void_functions_ == kMaxGLVoidFunctions_) {
     SyncGLVoidFunctions();
     }*/

    //NaClVoidFunctionHandler<R(Args...)> f_h;
    //f_h.set_function(f);
    gl_void_functions_buffer_[number_gl_void_functions_] = f;
    //gl_void_functions_buffer_.push_back(f_h);
    ++number_gl_void_functions_;
  }

  int CallGLintFunction(const std::tr1::function<int()>& f) {
    pthread_mutex_lock(&mutex_waiting_callback_);
    waiting_callback_ = true;

    int return_value;

    pp::CompletionCallback kGLbooleanFunctionCallback = pp_callback_factory_
        .NewCallback(&NaClMainThreadCalls::CallGLintFunctionCallback,
                     return_value, f);
    this->pp_core_->CallOnMainThread(0, kGLbooleanFunctionCallback, 0);

    while (waiting_callback_) {
      pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
    }

    pthread_mutex_lock(&mutex_waiting_callback_);

    return return_value;
  }

  GLenum CallGLenumFunction(const std::tr1::function<GLenum()>& f) {
    pthread_mutex_lock(&mutex_waiting_callback_);
    waiting_callback_ = true;

    GLenum return_value;

    pp::CompletionCallback kGLbooleanFunctionCallback = pp_callback_factory_
        .NewCallback(&NaClMainThreadCalls::CallGLenumFunctionCallback,
                     return_value, f);
    this->pp_core_->CallOnMainThread(0, kGLbooleanFunctionCallback, 0);

    while (waiting_callback_) {
      pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
    }

    pthread_mutex_lock(&mutex_waiting_callback_);

    return return_value;
  }

  GLuint CallGLuintFunction(const std::tr1::function<GLuint()>& f) {
    pthread_mutex_lock(&mutex_waiting_callback_);
    waiting_callback_ = true;

    GLuint return_value;

    pp::CompletionCallback kGLbooleanFunctionCallback = pp_callback_factory_
        .NewCallback(&NaClMainThreadCalls::CallGLuintFunctionCallback,
                     return_value, f);
    this->pp_core_->CallOnMainThread(0, kGLbooleanFunctionCallback, 0);

    while (waiting_callback_) {
      pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
    }

    pthread_mutex_lock(&mutex_waiting_callback_);

    return return_value;
  }

  GLenum CallGLbooleanFunction(const std::tr1::function<GLboolean()>& f) {
    pthread_mutex_lock(&mutex_waiting_callback_);
    waiting_callback_ = true;

    GLboolean return_value;

    pp::CompletionCallback kGLbooleanFunctionCallback = pp_callback_factory_
        .NewCallback(&NaClMainThreadCalls::CallGLbooleanFunctionCallback,
                     return_value, f);
    this->pp_core_->CallOnMainThread(0, kGLbooleanFunctionCallback, 0);

    while (waiting_callback_) {
      pthread_cond_wait(&cond_waiting_callback_, &mutex_waiting_callback_);
    }

    pthread_mutex_lock(&mutex_waiting_callback_);

    return return_value;
  }

  void CallGLContextFlush();
  void SyncGLVoidFunctions();

 private:
  pp::Core* pp_core_;
  NaClWindow* window_;
  const int kMaxGLVoidFunctions_;
  std::tr1::function<void()>* gl_void_functions_buffer_;
  int number_gl_void_functions_;

  pp::CompletionCallbackFactory<NaClMainThreadCalls> pp_callback_factory_;

  pthread_cond_t cond_waiting_callback_;
  pthread_mutex_t mutex_waiting_callback_;
  bool waiting_callback_;

  void* gl_return_func_pointer_;
  GLboolean ret_value_gl_return_;

  void CallGLintFunctionCallback(int32_t result, int& return_value,
                                 const std::tr1::function<int()>& f);
  void CallGLenumFunctionCallback(int32_t result, GLenum& return_value,
                                  const std::tr1::function<GLenum()>& f);
  void CallGLuintFunctionCallback(int32_t result, GLuint& return_value,
                                  const std::tr1::function<GLuint()>& f);
  void CallGLbooleanFunctionCallback(int32_t result, GLboolean& return_value,
                                     const std::tr1::function<GLboolean()>& f);

  void CallGLvoidFunctionsCallback(int32_t result);
  void CallGLContextFlushCallback(int32_t result);

};

}  // namespace furai

#endif /* FURAI_NACLMAINTHREADCALLS_H_ */
