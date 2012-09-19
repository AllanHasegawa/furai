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

class NaClMainThreadCalls {
 public:
  NaClMainThreadCalls(pp::Core* pp_core, NaClWindow* window);

  virtual ~NaClMainThreadCalls();

  void CallGLVoidFunction(std::tr1::function<void()>&);
  GLenum CallGLenumFunction(std::tr1::function<GLenum()>&);
  GLuint CallGLuintFunction(std::tr1::function<GLuint()>&);
  int CallGLIntFunction(std::tr1::function<int()>&);
  GLboolean CallGLbooleanFunction(std::tr1::function<GLboolean()>&);
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

  std::tr1::function<GLenum()>* gl_enum_func_pointer_;
  GLenum ret_value_gl_enum_;

  std::tr1::function<GLuint()>* gl_uint_func_pointer_;
  GLuint ret_value_gl_uint_;

  std::tr1::function<int()>* gl_int_func_pointer_;
  int ret_value_gl_int_;

  std::tr1::function<GLboolean()>* gl_boolean_func_pointer_;
  GLboolean ret_value_gl_boolean_;

  void CallGLVoidFunctionsCallback(int32_t result);
  void CallGLenumFunctionCallback(int32_t result);
  void CallGLuintFunctionCallback(int32_t result);
  void CallGLIntFunctionCallback(int32_t result);
  void CallGLbooleanFunctionCallback(int32_t result);

  void CallGLContextFlushCallback(int32_t result);

};

inline void NaClMainThreadCalls::CallGLVoidFunction(
    std::tr1::function<void()>& f) {
  if (number_gl_void_functions_ == kMaxGLVoidFunctions_) {
    SyncGLVoidFunctions();
  }
  gl_void_functions_buffer_[number_gl_void_functions_] = f;
  ++number_gl_void_functions_;
}

}  // namespace furai

#endif /* FURAI_NACLMAINTHREADCALLS_H_ */
