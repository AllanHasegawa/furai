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

#include <tr1/functional>

#include <furai/backends/nacl/graphics/GLES2/gl2.h>
#include <furai/backends/nacl/core/mainthreadcalls/NaClMainThreadCalls.h>
#include <furai/backends/nacl/core/NaClFurai.h>

namespace furai {

void GLES2ActiveTexture(GLenum texture) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ActiveTexture);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2AttachShader(GLuint program, GLuint shader) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2AttachShader, program,
                                                shader);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BindAttribLocation(GLuint program, GLuint index, const GLchar* name) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BindAttribLocation,
                                                program, index, name);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BindBuffer(GLenum target, GLuint buffer) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BindBuffer, target,
                                                buffer);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BindFramebuffer(GLenum target, GLuint framebuffer) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BindFramebuffer, target,
                                                framebuffer);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BindRenderbuffer(GLenum target, GLuint renderbuffer) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BindRenderbuffer, target,
                                                renderbuffer);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BindTexture(GLenum target, GLuint texture) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BindTexture, target,
                                                texture);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BlendColor(GLclampf red, GLclampf green, GLclampf blue,
                     GLclampf alpha) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BlendColor, red, green,
                                                blue, alpha);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BlendEquation(GLenum mode) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BlendEquation);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BlendEquationSeparate,
                                                modeRGB, modeAlpha);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BlendFunc(GLenum sfactor, GLenum dfactor) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BlendFunc, sfactor,
                                                dfactor);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
                            GLenum dstAlpha) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BlendFuncSeparate,
                                                srcRGB, dstRGB, srcAlpha,
                                                dstAlpha);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BufferData(GLenum target, GLsizeiptr size, const GLvoid* data,
                     GLenum usage) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BufferData, target, size,
                                                data, usage);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size,
                        const GLvoid* data) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2BufferSubData, target,
                                                offset, size, data);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

GLenum GLES2CheckFramebufferStatus(GLenum target) {
  std::tr1::function<GLenum()> f = std::tr1::bind(
      ::GLES2CheckFramebufferStatus);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLenumFunction(f);
}

void GLES2Clear(GLbitfield mask) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Clear);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ClearColor(GLclampf red, GLclampf green, GLclampf blue,
                     GLclampf alpha) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ClearColor, red, green,
                                                blue, alpha);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ClearDepthf(GLclampf depth) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ClearDepthf);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ClearStencil(GLint s) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ClearStencil);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ColorMask(GLboolean red, GLboolean green, GLboolean blue,
                    GLboolean alpha) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ColorMask, red, green,
                                                blue, alpha);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2CompileShader(GLuint shader) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CompileShader);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2CompressedTexImage2D(GLenum target, GLint level,
                               GLenum internalformat, GLsizei width,
                               GLsizei height, GLint border, GLsizei imageSize,
                               const GLvoid* data) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CompressedTexImage2D,
                                                target, level, internalformat,
                                                width, height, border,
                                                imageSize, data);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                                  GLint yoffset, GLsizei width, GLsizei height,
                                  GLenum format, GLsizei imageSize,
                                  const GLvoid* data) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CompressedTexSubImage2D,
                                                target, level, xoffset, yoffset,
                                                width, height, format,
                                                imageSize, data);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2CopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
                         GLint x, GLint y, GLsizei width, GLsizei height,
                         GLint border) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CopyTexImage2D, target,
                                                level, internalformat, x, y,
                                                width, height, border);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                            GLint yoffset, GLint x, GLint y, GLsizei width,
                            GLsizei height) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CopyTexSubImage2D,
                                                target, level, xoffset, yoffset,
                                                x, y, width, height);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

GLuint GLES2CreateProgram(void) {
  std::tr1::function<GLuint()> f = std::tr1::bind(::GLES2CreateProgram);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLuintFunction(f);
}

GLuint GLES2CreateShader(GLenum type) {
  std::tr1::function<GLuint()> f = std::tr1::bind(::GLES2CreateShader);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLuintFunction(f);
}

void GLES2CullFace(GLenum mode) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2CullFace);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteBuffers(GLsizei n, const GLuint* buffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteBuffers, n,
                                                buffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteFramebuffers(GLsizei n, const GLuint* framebuffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteFramebuffers, n,
                                                framebuffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteProgram(GLuint program) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteProgram);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteRenderbuffers, n,
                                                renderbuffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteShader(GLuint shader) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteShader);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DeleteTextures(GLsizei n, const GLuint* textures) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DeleteTextures, n,
                                                textures);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DepthFunc(GLenum func) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DepthFunc);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DepthMask(GLboolean flag) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DepthMask);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DepthRangef(GLclampf zNear, GLclampf zFar) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DepthRangef, zNear,
                                                zFar);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DetachShader(GLuint program, GLuint shader) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DetachShader, program,
                                                shader);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Disable(GLenum cap) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Disable);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DisableVertexAttribArray(GLuint index) {
  std::tr1::function<void()> f = std::tr1::bind(
      ::GLES2DisableVertexAttribArray);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DrawArrays(GLenum mode, GLint first, GLsizei count) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DrawArrays, mode, first,
                                                count);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2DrawElements(GLenum mode, GLsizei count, GLenum type,
                       const GLvoid* indices) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2DrawElements, mode,
                                                count, type, indices);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Enable(GLenum cap) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Enable);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2EnableVertexAttribArray(GLuint index) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2EnableVertexAttribArray);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Finish(void) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Finish);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Flush(void) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Flush);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2FramebufferRenderbuffer(GLenum target, GLenum attachment,
                                  GLenum renderbuffertarget,
                                  GLuint renderbuffer) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2FramebufferRenderbuffer,
                                                target, attachment,
                                                renderbuffertarget,
                                                renderbuffer);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2FramebufferTexture2D(GLenum target, GLenum attachment,
                               GLenum textarget, GLuint texture, GLint level) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2FramebufferTexture2D,
                                                target, attachment, textarget,
                                                texture, level);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2FrontFace(GLenum mode) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2FrontFace);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GenBuffers(GLsizei n, GLuint* buffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GenBuffers, n, buffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GenerateMipmap(GLenum target) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GenerateMipmap);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GenFramebuffers(GLsizei n, GLuint* framebuffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GenFramebuffers, n,
                                                framebuffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GenRenderbuffers, n,
                                                renderbuffers);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GenTextures(GLsizei n, GLuint* textures) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GenTextures, n,
                                                textures);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize,
                          GLsizei* length, GLint* size, GLenum* type,
                          GLchar* name) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetActiveAttrib, program,
                                                index, bufsize, length, size,
                                                type, name);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetActiveUniform(GLuint program, GLuint index, GLsizei bufsize,
                           GLsizei* length, GLint* size, GLenum* type,
                           GLchar* name) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetActiveUniform,
                                                program, index, bufsize, length,
                                                size, type, name);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count,
                             GLuint* shaders) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetAttachedShaders,
                                                program, maxcount, count,
                                                shaders);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

int GLES2GetAttribLocation(GLuint program, const GLchar* name) {
  std::tr1::function<int()> f = std::tr1::bind(::GLES2GetAttribLocation,
                                               program, name);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLintFunction(f);
}

void GLES2GetBooleanv(GLenum pname, GLboolean* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetBooleanv, pname,
                                                params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetBufferParameteriv(GLenum target, GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetBufferParameteriv,
                                                target, pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

GLenum GLES2GetError(void) {
  std::tr1::function<GLenum()> f = std::tr1::bind(::GLES2GetError);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLenumFunction(f);
}

void GLES2GetFloatv(GLenum pname, GLfloat* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetFloatv, pname,
                                                params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment,
                                              GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(
      ::GLES2GetFramebufferAttachmentParameteriv, target, attachment, pname,
      params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetIntegerv(GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetIntegerv, pname,
                                                params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetProgramiv(GLuint program, GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetProgramiv, program,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length,
                            GLchar* infolog) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetProgramInfoLog,
                                                program, bufsize, length,
                                                infolog);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetRenderbufferParameteriv(GLenum target, GLenum pname,
                                     GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(
      ::GLES2GetRenderbufferParameteriv, target, pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetShaderiv(GLuint shader, GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetShaderiv, shader,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length,
                           GLchar* infolog) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetShaderInfoLog, shader,
                                                bufsize, length, infolog);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype,
                                   GLint* range, GLint* precision) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetShaderPrecisionFormat,
                                                shadertype, precisiontype,
                                                range, precision);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length,
                          GLchar* source) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetShaderSource, shader,
                                                bufsize, length, source);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

const GLubyte* GLES2GetString(GLenum name) {
//std::tr1::function<const GLubyte*()> f = std::tr1::bind(::GLES2GetString);
//return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->Callconst GLubyte*Function(f);
  return NULL;
}

void GLES2GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetTexParameterfv,
                                                target, pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetTexParameteriv(GLenum target, GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetTexParameteriv,
                                                target, pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetUniformfv(GLuint program, GLint location, GLfloat* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetUniformfv, program,
                                                location, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetUniformiv(GLuint program, GLint location, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetUniformiv, program,
                                                location, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

int GLES2GetUniformLocation(GLuint program, const GLchar* name) {
  std::tr1::function<int()> f = std::tr1::bind(::GLES2GetUniformLocation,
                                               program, name);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLintFunction(f);
}

void GLES2GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetVertexAttribfv, index,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetVertexAttribiv(GLuint index, GLenum pname, GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetVertexAttribiv, index,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2GetVertexAttribPointerv(GLuint index, GLenum pname,
                                  GLvoid** pointer) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2GetVertexAttribPointerv,
                                                index, pname, pointer);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Hint(GLenum target, GLenum mode) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Hint, target, mode);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

GLboolean GLES2IsBuffer(GLuint buffer) {
  auto f = std::tr1::bind(::GLES2IsBuffer);
  decltype(f) ff;
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsEnabled(GLenum cap) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsEnabled);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsFramebuffer(GLuint framebuffer) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsFramebuffer);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsProgram(GLuint program) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsProgram);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsRenderbuffer(GLuint renderbuffer) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsRenderbuffer);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsShader(GLuint shader) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsShader);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

GLboolean GLES2IsTexture(GLuint texture) {
  std::tr1::function<GLboolean()> f = std::tr1::bind(::GLES2IsTexture);
  return furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLbooleanFunction(f);
}

void GLES2LineWidth(GLfloat width) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2LineWidth);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2LinkProgram(GLuint program) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2LinkProgram);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2PixelStorei(GLenum pname, GLint param) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2PixelStorei, pname,
                                                param);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2PolygonOffset(GLfloat factor, GLfloat units) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2PolygonOffset, factor,
                                                units);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                     GLenum format, GLenum type, GLvoid* pixels) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ReadPixels, x, y, width,
                                                height, format, type, pixels);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ReleaseShaderCompiler(void) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ReleaseShaderCompiler);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2RenderbufferStorage(GLenum target, GLenum internalformat,
                              GLsizei width, GLsizei height) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2RenderbufferStorage,
                                                target, internalformat, width,
                                                height);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2SampleCoverage(GLclampf value, GLboolean invert) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2SampleCoverage, value,
                                                invert);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Scissor, x, y, width,
                                                height);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat,
                       const GLvoid* binary, GLsizei length) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ShaderBinary, n, shaders,
                                                binaryformat, binary, length);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ShaderSource(GLuint shader, GLsizei count, const GLchar** string,
                       const GLint* length) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ShaderSource, shader,
                                                count, string, length);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilFunc(GLenum func, GLint ref, GLuint mask) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilFunc, func, ref,
                                                mask);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilFuncSeparate(GLenum face, GLenum func, GLint ref,
                              GLuint mask) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilFuncSeparate,
                                                face, func, ref, mask);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilMask(GLuint mask) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilMask);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilMaskSeparate(GLenum face, GLuint mask) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilMaskSeparate,
                                                face, mask);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilOp, fail, zfail,
                                                zpass);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2StencilOpSeparate(GLenum face, GLenum fail, GLenum zfail,
                            GLenum zpass) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2StencilOpSeparate, face,
                                                fail, zfail, zpass);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexImage2D(GLenum target, GLint level, GLint internalformat,
                     GLsizei width, GLsizei height, GLint border, GLenum format,
                     GLenum type, const GLvoid* pixels) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexImage2D, target,
                                                level, internalformat, width,
                                                height, border, format, type,
                                                pixels);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexParameterf(GLenum target, GLenum pname, GLfloat param) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexParameterf, target,
                                                pname, param);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexParameterfv(GLenum target, GLenum pname, const GLfloat* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexParameterfv, target,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexParameteri(GLenum target, GLenum pname, GLint param) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexParameteri, target,
                                                pname, param);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexParameteriv(GLenum target, GLenum pname, const GLint* params) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexParameteriv, target,
                                                pname, params);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2TexSubImage2D(GLenum target, GLint level, GLint xoffset,
                        GLint yoffset, GLsizei width, GLsizei height,
                        GLenum format, GLenum type, const GLvoid* pixels) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2TexSubImage2D, target,
                                                level, xoffset, yoffset, width,
                                                height, format, type, pixels);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform1f(GLint location, GLfloat x) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform1f, location, x);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform1fv(GLint location, GLsizei count, const GLfloat* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform1fv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform1i(GLint location, GLint x) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform1i, location, x);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform1iv(GLint location, GLsizei count, const GLint* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform1iv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform2f(GLint location, GLfloat x, GLfloat y) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform2f, location, x,
                                                y);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform2fv(GLint location, GLsizei count, const GLfloat* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform2fv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform2i(GLint location, GLint x, GLint y) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform2i, location, x,
                                                y);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform2iv(GLint location, GLsizei count, const GLint* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform2iv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform3f, location, x,
                                                y, z);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform3fv(GLint location, GLsizei count, const GLfloat* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform3fv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform3i(GLint location, GLint x, GLint y, GLint z) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform3i, location, x,
                                                y, z);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform3iv(GLint location, GLsizei count, const GLint* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform3iv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z,
                    GLfloat w) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform4f, location, x,
                                                y, z, w);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform4fv(GLint location, GLsizei count, const GLfloat* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform4fv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform4i, location, x,
                                                y, z, w);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Uniform4iv(GLint location, GLsizei count, const GLint* v) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Uniform4iv, location,
                                                count, v);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose,
                           const GLfloat* value) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UniformMatrix2fv,
                                                location, count, transpose,
                                                value);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                           const GLfloat* value) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UniformMatrix3fv,
                                                location, count, transpose,
                                                value);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                           const GLfloat* value) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UniformMatrix4fv,
                                                location, count, transpose,
                                                value);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2UseProgram(GLuint program) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UseProgram);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2ValidateProgram(GLuint program) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2ValidateProgram);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib1f(GLuint indx, GLfloat x) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib1f, indx, x);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib1fv(GLuint indx, const GLfloat* values) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib1fv, indx,
                                                values);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib2f(GLuint indx, GLfloat x, GLfloat y) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib2f, indx, x,
                                                y);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib2fv(GLuint indx, const GLfloat* values) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib2fv, indx,
                                                values);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib3f, indx, x,
                                                y, z);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib3fv(GLuint indx, const GLfloat* values) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib3fv, indx,
                                                values);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z,
                         GLfloat w) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib4f, indx, x,
                                                y, z, w);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttrib4fv(GLuint indx, const GLfloat* values) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttrib4fv, indx,
                                                values);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2VertexAttribPointer(GLuint indx, GLint size, GLenum type,
                              GLboolean normalized, GLsizei stride,
                              const GLvoid* ptr) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2VertexAttribPointer,
                                                indx, size, type, normalized,
                                                stride, ptr);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

void GLES2Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2Viewport, x, y, width,
                                                height);
  furai::NaClFurai::NACL_MAIN_THREAD_CALLS->CallGLvoidFunction(f);
}

}  //namespace
