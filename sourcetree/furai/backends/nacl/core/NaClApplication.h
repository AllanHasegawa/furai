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

#ifndef FURAI_NACLAPPLICATION_H_
#define FURAI_NACLAPPLICATION_H_

#include <ppapi/cpp/core.h>
#include <ppapi/cpp/instance.h>
#include <opengl_context/opengl_context_ptrs.h>

#include <furai/core/Application.h>
#include <furai/core/WindowListener.h>
#include <furai/backends/nacl/core/mainthreadcalls/NaClMainThreadCalls.h>

namespace furai {

enum NaClLogType {
  NACL_LOG_TYPE_JS_CONSOLE,
  NACL_LOG_TYPE_ENV_VARS
};

class NaClApplication : public Application, public pp::Instance {
 public:
  NaClApplication(NaClLogType log_type, WindowListener* window_listener,
                  PP_Instance pp_instance);
  virtual ~NaClApplication();

  void Start() {
  }
  ;

  NaClMainThreadCalls* main_thread_calls() {
    return main_thread_calls_;
  }
  pp::Core* pp_core_;
  static void Lala(void* data, int32_t result) {
    NaClApplication* app = static_cast<NaClApplication*>(data);
    app->PostMessage("DONE!\n\n");
  }
  static void Lalh(void* data, int32_t result) {
    NaClApplication* app = static_cast<NaClApplication*>(data);
    app->PostMessage("DONSADASDASDE!\n\n");
  }

  static void MainLoopDealy(void* data, int32_t result) {
    NaClApplication* app = static_cast<NaClApplication*>(data);
    pthread_create(&(app->thread_mainloop_), NULL, NaClApplication::MainLoop,
                   app);
  }

 private:
  bool started_;
  bool destroy_;

  pthread_t thread_mainloop_;

  NaClMainThreadCalls* main_thread_calls_;

  bool Init(uint32_t argc, const char* argn[], const char* argv[]);
  void DidChangeView(const pp::View& view);
  void DidChangeFocus(bool has_focus);

  void Update();

  static void *MainLoop(void* data);

  void UpdateScheduler(int32_t delay_in_milliseconds);
  static void UpdateCallback(void* instance, int32_t result);
};

}  // namespace furai
#endif /* FURAI_NACLAPPLICATION_H_ */
