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

#include "furai/graphics/EGLConfigChooser.h"

#include <map>
#include <furai/core/Furai.h>

namespace furai {

EGLConfigChooser::EGLConfigChooser(const EGLDisplay display, const EGLint r,
                                   const EGLint g, const EGLint b,
                                   const EGLint a, const EGLint depth,
                                   const EGLint stencil)
    : display_(display),
      run_fallback_(true),
      kConfigListSize_(50) {

  // Force the use of OpenGLES2
  SetEGLAttribute(EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT);
  SetEGLAttribute(EGL_RED_SIZE, r);
  SetEGLAttribute(EGL_GREEN_SIZE, g);
  SetEGLAttribute(EGL_BLUE_SIZE, b);
  SetEGLAttribute(EGL_ALPHA_SIZE, a);
  SetEGLAttribute(EGL_DEPTH_SIZE, depth);
  SetEGLAttribute(EGL_STENCIL_SIZE, stencil);

  configs_ = new EGLConfig[kConfigListSize_];
}

EGLConfigChooser::~EGLConfigChooser() {
  delete[] configs_;
}

void EGLConfigChooser::UpdateConfigList() {

  const int n_attribs = attributes_map_.size();

  // Each element of the map holds a pair<attribute,value>;
  // +1 is for the EGL_NONE, end of the attributes array.
  int* attribs = new int[n_attribs * 2 + 1];
  int attribs_counter = 0;

  for (std::map<int, int>::iterator i = attributes_map_.begin();
      i != attributes_map_.end(); i++) {
    attribs[attribs_counter++] = i->first;
    attribs[attribs_counter++] = i->second;
  }
  attribs[attribs_counter++] = EGL_NONE;

  eglChooseConfig(display_, attribs, configs_, kConfigListSize_, &num_configs_);

  delete[] attribs;

  pending_update_ = false;
}

void EGLConfigChooser::SetEGLAttribute(const EGLint attribute,
                                       const EGLint value) {
  attributes_map_[attribute] = value;
  pending_update_ = true;
}

EGLint EGLConfigChooser::GetEGLAtrribute(const EGLint config,
                                         const EGLint attribute) {
  if (pending_update_) {
    this->UpdateConfigList();
  }

  EGLint value[1];
  if (eglGetConfigAttrib(display_, configs_[config], attribute, value)) {
    return value[0];
  } else {
    while (eglGetError() != EGL_SUCCESS)
      ;
    return EGL_BAD_ATTRIBUTE;
  }
}

EGLint EGLConfigChooser::GetNumberConfigs() {
  if (pending_update_) {
    this->UpdateConfigList();
  }
  return num_configs_;
}

EGLConfig EGLConfigChooser::GetConfig(const EGLint config) {
  if (pending_update_) {
    UpdateConfigList();
  }
  return configs_[config];
}

void EGLConfigChooser::PrintConfigs() {
  if (pending_update_) {
    UpdateConfigList();
  }

  Furai::LOG->LogV("EGLConfig list size: %d\n", num_configs_);
  for (int i = 0; i < num_configs_; i++) {
    Furai::LOG->LogV("Configuration %d:\n", i);
    PrintConfig(i);
  }
}

void EGLConfigChooser::PrintConfig(const EGLint config) {
  int attributes[] = { EGL_BUFFER_SIZE, EGL_ALPHA_SIZE, EGL_BLUE_SIZE,
      EGL_GREEN_SIZE, EGL_RED_SIZE, EGL_DEPTH_SIZE, EGL_STENCIL_SIZE,
      EGL_CONFIG_CAVEAT, EGL_CONFIG_ID, EGL_LEVEL, EGL_MAX_PBUFFER_HEIGHT,
      EGL_MAX_PBUFFER_PIXELS, EGL_MAX_PBUFFER_WIDTH, EGL_NATIVE_RENDERABLE,
      EGL_NATIVE_VISUAL_ID, EGL_NATIVE_VISUAL_TYPE,
      0x3030,  // EGL_PRESERVED_RESOURCES,
      EGL_SAMPLES, EGL_SAMPLE_BUFFERS, EGL_SURFACE_TYPE, EGL_TRANSPARENT_TYPE,
      EGL_TRANSPARENT_RED_VALUE, EGL_TRANSPARENT_GREEN_VALUE,
      EGL_TRANSPARENT_BLUE_VALUE,
      0x3039,  // EGL_BIND_TO_TEXTURE_RGB,
      0x303A,  // EGL_BIND_TO_TEXTURE_RGBA,
      0x303B,  // EGL_MIN_SWAP_INTERVAL,
      0x303C,  // EGL_MAX_SWAP_INTERVAL,
      EGL_LUMINANCE_SIZE, EGL_ALPHA_MASK_SIZE, EGL_COLOR_BUFFER_TYPE,
      EGL_RENDERABLE_TYPE, 0x3042  // EGL_CONFORMANT
      };
  const char* names[] = { "EGL_BUFFER_SIZE", "EGL_ALPHA_SIZE", "EGL_BLUE_SIZE",
      "EGL_GREEN_SIZE", "EGL_RED_SIZE", "EGL_DEPTH_SIZE", "EGL_STENCIL_SIZE",
      "EGL_CONFIG_CAVEAT", "EGL_CONFIG_ID", "EGL_LEVEL",
      "EGL_MAX_PBUFFER_HEIGHT", "EGL_MAX_PBUFFER_PIXELS",
      "EGL_MAX_PBUFFER_WIDTH", "EGL_NATIVE_RENDERABLE", "EGL_NATIVE_VISUAL_ID",
      "EGL_NATIVE_VISUAL_TYPE", "EGL_PRESERVED_RESOURCES", "EGL_SAMPLES",
      "EGL_SAMPLE_BUFFERS", "EGL_SURFACE_TYPE", "EGL_TRANSPARENT_TYPE",
      "EGL_TRANSPARENT_RED_VALUE", "EGL_TRANSPARENT_GREEN_VALUE",
      "EGL_TRANSPARENT_BLUE_VALUE", "EGL_BIND_TO_TEXTURE_RGB",
      "EGL_BIND_TO_TEXTURE_RGBA", "EGL_MIN_SWAP_INTERVAL",
      "EGL_MAX_SWAP_INTERVAL", "EGL_LUMINANCE_SIZE", "EGL_ALPHA_MASK_SIZE",
      "EGL_COLOR_BUFFER_TYPE", "EGL_RENDERABLE_TYPE", "EGL_CONFORMANT" };

  EGLint value;

  int n_attributes = sizeof(attributes) / sizeof(int);
  for (int i = 0; i < n_attributes; i++) {
    int attribute = attributes[i];

    value = GetEGLAtrribute(config, attribute);
    if (value == EGL_BAD_ATTRIBUTE) {
      Furai::LOG->LogV("  %s: failed\n", names[i]);
    } else {
      Furai::LOG->LogV("  %s: %d\n", names[i], value);
    }
  }
}

}  // namespace furai
