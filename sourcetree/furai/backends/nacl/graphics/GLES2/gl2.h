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

#ifndef FURAI_GL2_H_
#define FURAI_GL2_H_

#include <GLES2/gl2.h>

#undef glUseProgram
#define glUseProgram(X) furai::GLES2UseProgram(X)

/*
 #define MACRO(X,Y) \
  (__extension__ ( \
    { \
      __typeof__(X) __x = (X); \
      __typeof__(Y) __y = (Y); \
      std::cout << "1st arg is:" << __x << std::endl; \
      std::cout << "2nd arg is:" << __y << std::endl; \
      std::cout << "Sum is:" << (__x + __y) << std::endl; \
      __x + __y; \
    } \
  ))
 */
namespace furai {

void GLES2UseProgram(const GLuint &program);

}  // namespace

#endif /* FURAI_GL2_H_ */
