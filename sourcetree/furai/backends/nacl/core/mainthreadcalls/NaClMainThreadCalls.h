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

/**
 * Ugly solution. Temporary until NaCl supports OpenGL context off-main thread.
 */
class NaClMainThreadCalls {
 public:
  NaClMainThreadCalls(pp::Core* pp_core);
  virtual ~NaClMainThreadCalls();

  void CallGLvoidFunction(const std::tr1::function<void()>& f);
  int CallGLintFunction(const std::tr1::function<int()>& f);
  GLenum CallGLenumFunction(const std::tr1::function<GLenum()>& f);
  GLuint CallGLuintFunction(const std::tr1::function<GLuint()>& f);
  GLboolean CallGLbooleanFunction(const std::tr1::function<GLboolean()>& f);

  void CallGLContextFlush();
  void SyncGLVoidFunctions();

  void CallPostMessage(const std::string& message);

  void set_window(NaClWindow* window) {
    window_ = window;
  }

 private:
  pp::Core* pp_core_;
  NaClWindow* window_;
  const int kMaxGLVoidFunctions_;
  std::tr1::function<void()>* gl_void_functions_buffer_;
  int number_gl_void_functions_;

  pthread_cond_t cond_waiting_callback_;
  pthread_mutex_t mutex_waiting_callback_;
  bool waiting_callback_;

  std::tr1::function<int()> gl_int_f_;
  int gl_int_return_value_;
  std::tr1::function<GLenum()> gl_enum_f_;
  GLenum gl_enum_return_value_;
  std::tr1::function<GLuint()> gl_uint_f_;
  GLuint gl_uint_return_value_;
  std::tr1::function<GLboolean()> gl_boolean_f_;
  GLboolean gl_boolean_return_value_;

  int number_post_messages_;
  std::string* post_message_buffer_;
  const int kMaxPostMessages_;
  bool post_message_sync_pending_;

  static void CallGLvoidFunctionsCallback(void* data, int32_t result);
  static void CallGLintFunctionCallback(void* data, int32_t result);
  static void CallGLenumFunctionCallback(void* data, int32_t result);
  static void CallGLuintFunctionCallback(void* data, int32_t result);
  static void CallGLbooleanFunctionCallback(void* data, int32_t result);

  static void CallGLContextFlushCallback(void* data, int32_t result);

  static void CallPostMessageCallback(void* data, int32_t result);

};

}  // namespace furai

#endif /* FURAI_NACLMAINTHREADCALLS_H_ */
