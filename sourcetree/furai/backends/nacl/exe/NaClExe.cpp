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

#include <stdio.h>

#include <furai/backends/nacl/core/NaClApplication.h>
#include <furai/backends/nacl/core/NaClModule.h>
#include <furai/backends/nacl/exe/HelloTri.h>

class MyModule : public furai::NaClModule {
 public:
  MyModule() {

  }

  virtual ~MyModule() {

  }

  pp::Instance* CreateInstance(PP_Instance instance) {
    return new furai::NaClApplication(furai::NACL_LOG_TYPE_JS_CONSOLE,
                                      new HelloTri(), instance);
  }
};

namespace pp {
/// Factory function called by the browser when the module is first loaded.
/// The browser keeps a singleton of this module.  It calls the
/// CreateInstance() method on the object you return to make instances.  There
/// is one instance per <embed> tag on the page.  This is the main binding
/// point for your NaCl module with the browser.
Module* CreateModule() {
  return new MyModule();  //new MinimalModule();
}
}  // namespace pp

