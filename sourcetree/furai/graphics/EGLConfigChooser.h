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

#ifndef FURAI_EGLCONFIGCHOOSER_H_
#define FURAI_EGLCONFIGCHOOSER_H_

#include <map>
#include <egl/egl.h>

namespace furai {

class EGLConfigChooser {
 public:
  EGLConfigChooser(const EGLDisplay display, const EGLint r, const EGLint g,
                   const EGLint b, const EGLint a, const EGLint depth,
                   const EGLint stencil);
  virtual ~EGLConfigChooser();

  void UpdateConfigList();

  void SetEGLAttribute(const EGLint attribute, const EGLint value);
  EGLint GetEGLAtrribute(const EGLint config, const EGLint attribute);
  EGLint GetNumberConfigs();

  EGLConfig GetConfig(const EGLint config);
  void PrintConfigs();
  void PrintConfig(const EGLint config);

 private:
  const EGLDisplay display_;
  bool run_fallback_;

  std::map<int, int> attributes_map_;

  bool pending_update_;

  const int kConfigListSize_;
  EGLConfig* configs_;
  EGLint num_configs_;
};

}  // namespace furai
#endif /* FURAI_EGLCONFIGCHOOSER_H_ */
