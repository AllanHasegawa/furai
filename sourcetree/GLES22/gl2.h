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

#include <vector>
#include <functional>
#include <tr1/functional>

#include <GLES2/gl2.h>
#include <furai/core/Furai.h>

namespace furai {

/*
 void GLES2ActiveTexture(){};
 void GLES2AttachShader(){};
 void GLES2BindAttribLocation(){};
 void GLES2BindBuffer(){};
 void GLES2BindFramebuffer(){};
 void GLES2BindRenderbuffer(){};
 void GLES2BindTexture(){};
 void GLES2BlendColor(){};
 void GLES2BlendEquation(){};
 void GLES2BlendEquationSeparate(){};
 void GLES2BlendFunc(){};
 void GLES2BlendFuncSeparate(){};
 void GLES2BufferData(){};
 void GLES2BufferSubData(){};
 void GLES2CheckFramebufferStatus(){};
 void GLES2Clear(){};
 void GLES2ClearColor(){};
 void GLES2ClearDepthf(){};
 void GLES2ClearStencil(){};
 void GLES2ColorMask(){};
 void GLES2CompileShader(){};
 void GLES2CompressedTexImage2D(){};
 void GLES2CompressedTexSubImage2D(){};
 void GLES2CopyTexImage2D(){};(CopyTexImage2D)
 void GLES2CopyTexSubImage2D(){};(CopyTexSubImage2D)
 void GLES2CreateProgram(){};(CreateProgram)
 void GLES2CreateShader(){};(CreateShader)
 void GLES2CullFace(){};(CullFace)
 void GLES2DeleteBuffers(){};(DeleteBuffers)
 void GLES2DeleteFramebuffers(){};(DeleteFramebuffers)
 void GLES2DeleteProgram(){};(DeleteProgram)
 void GLES2DeleteRenderbuffers(){};(DeleteRenderbuffers)
 void GLES2DeleteShader(){};(DeleteShader)
 void GLES2DeleteTextures(){};(DeleteTextures)
 void GLES2DepthFunc(){};(DepthFunc)
 void GLES2DepthMask(){};(DepthMask)
 void GLES2DepthRangef(){};(DepthRangef)
 void GLES2DetachShader(){};(DetachShader)
 void GLES2Disable(){};(Disable)
 void GLES2DisableVertexAttribArray(){};(DisableVertexAttribArray)
 void GLES2DrawArrays(){};(DrawArrays)
 void GLES2DrawElements(){};(DrawElements)
 void GLES2Enable(){};(Enable)
 void GLES2EnableVertexAttribArray(){};(EnableVertexAttribArray)
 void GLES2Finish(){};(Finish)
 void GLES2Flush(){};(Flush)
 void GLES2FramebufferRenderbuffer(){};(FramebufferRenderbuffer)
 void GLES2FramebufferTexture2D(){};(FramebufferTexture2D)
 void GLES2FrontFace(){};(FrontFace)
 void GLES2GenBuffers(){};(GenBuffers)
 void GLES2GenerateMipmap(){};(GenerateMipmap)
 void GLES2GenFramebuffers(){};(GenFramebuffers)
 void GLES2GenRenderbuffers(){};(GenRenderbuffers)
 void GLES2GenTextures(){};(GenTextures)
 void GLES2GetActiveAttrib(){};(GetActiveAttrib)
 void GLES2GetActiveUniform(){};(GetActiveUniform)
 void GLES2GetAttachedShaders(){};(GetAttachedShaders)
 void GLES2GetAttribLocation(){};(GetAttribLocation)
 void GLES2GetBooleanv(){};(GetBooleanv)
 void GLES2GetBufferParameteriv(){};(GetBufferParameteriv)
 void GLES2GetError(){};(GetError)
 void GLES2GetFloatv(){};(GetFloatv)
 void GLES2GetFramebufferAttachmentParameteriv(){};(GetFramebufferAttachmentParameteriv)
 void GLES2GetIntegerv(){};(GetIntegerv)
 void GLES2GetProgramiv(){};(GetProgramiv)
 void GLES2GetProgramInfoLog(){};(GetProgramInfoLog)
 void GLES2GetRenderbufferParameteriv(){};(GetRenderbufferParameteriv)
 void GLES2GetShaderiv(){};(GetShaderiv)
 void GLES2GetShaderInfoLog(){};(GetShaderInfoLog)
 void GLES2GetShaderPrecisionFormat(){};(GetShaderPrecisionFormat)
 void GLES2GetShaderSource(){};(GetShaderSource)
 void GLES2GetString(){};(GetString)
 void GLES2GetTexParameterfv(){};(GetTexParameterfv)
 void GLES2GetTexParameteriv(){};(GetTexParameteriv)
 void GLES2GetUniformfv(){};(GetUniformfv)
 void GLES2GetUniformiv(){};(GetUniformiv)
 void GLES2GetUniformLocation(){};(GetUniformLocation)
 void GLES2GetVertexAttribfv(){};(GetVertexAttribfv)
 void GLES2GetVertexAttribiv(){};(GetVertexAttribiv)
 void GLES2GetVertexAttribPointerv(){};(GetVertexAttribPointerv)
 void GLES2Hint(){};(Hint)
 void GLES2IsBuffer(){};(IsBuffer)
 void GLES2IsEnabled(){};(IsEnabled)
 void GLES2IsFramebuffer(){};(IsFramebuffer)
 void GLES2IsProgram(){};(IsProgram)
 void GLES2IsRenderbuffer(){};(IsRenderbuffer)
 void GLES2IsShader(){};(IsShader)
 void GLES2IsTexture(){};(IsTexture)
 void GLES2LineWidth(){};(LineWidth)
 void GLES2LinkProgram(){};(LinkProgram)
 void GLES2PixelStorei(){};(PixelStorei)
 void GLES2PolygonOffset(){};(PolygonOffset)
 void GLES2ReadPixels(){};(ReadPixels)
 void GLES2ReleaseShaderCompiler(){};(ReleaseShaderCompiler)
 void GLES2RenderbufferStorage(){};(RenderbufferStorage)
 void GLES2SampleCoverage(){};(SampleCoverage)
 void GLES2Scissor(){};(Scissor)
 void GLES2ShaderBinary(){};(ShaderBinary)
 void GLES2ShaderSource(){};(ShaderSource)
 void GLES2StencilFunc(){};(StencilFunc)
 void GLES2StencilFuncSeparate(){};(StencilFuncSeparate)
 void GLES2StencilMask(){};(StencilMask)
 void GLES2StencilMaskSeparate(){};(StencilMaskSeparate)
 void GLES2StencilOp(){};(StencilOp)
 void GLES2StencilOpSeparate(){};(StencilOpSeparate)
 void GLES2TexImage2D(){};(TexImage2D)
 void GLES2TexParameterf(){};(TexParameterf)
 void GLES2TexParameterfv(){};(TexParameterfv)
 void GLES2TexParameteri(){};(TexParameteri)
 void GLES2TexParameteriv(){};(TexParameteriv)
 void GLES2TexSubImage2D(){};(TexSubImage2D)
 void GLES2Uniform1f(){};(Uniform1f)
 void GLES2Uniform1fv(){};(Uniform1fv)
 void GLES2Uniform1i(){};(Uniform1i)
 void GLES2Uniform1iv(){};(Uniform1iv)
 void GLES2Uniform2f(){};(Uniform2f)
 void GLES2Uniform2fv(){};(Uniform2fv)
 void GLES2Uniform2i(){};(Uniform2i)
 void GLES2Uniform2iv(){};(Uniform2iv)
 void GLES2Uniform3f(){};(Uniform3f)
 void GLES2Uniform3fv(){};(Uniform3fv)
 void GLES2Uniform3i(){};(Uniform3i)
 void GLES2Uniform3iv(){};(Uniform3iv)
 void GLES2Uniform4f(){};(Uniform4f)
 void GLES2Uniform4fv(){};(Uniform4fv)
 void GLES2Uniform4i(){};(Uniform4i)
 void GLES2Uniform4iv(){};(Uniform4iv)
 void GLES2UniformMatrix2fv(){};(UniformMatrix2fv)
 void GLES2UniformMatrix3fv(){};(UniformMatrix3fv)
 void GLES2UniformMatrix4fv(){};(UniformMatrix4fv)
 void GLES2UseProgram(){};(UseProgram)
 void GLES2ValidateProgram(){};(ValidateProgram)
 void GLES2VertexAttrib1f(){};(VertexAttrib1f)
 void GLES2VertexAttrib1fv(){};(VertexAttrib1fv)
 void GLES2VertexAttrib2f(){};(VertexAttrib2f)
 void GLES2VertexAttrib2fv(){};(VertexAttrib2fv)
 void GLES2VertexAttrib3f(){};(VertexAttrib3f)
 void GLES2VertexAttrib3fv(){};(VertexAttrib3fv)
 void GLES2VertexAttrib4f(){};(VertexAttrib4f)
 void GLES2VertexAttrib4fv(){};(VertexAttrib4fv)
 void GLES2VertexAttribPointer(){};(VertexAttribPointer)
 void GLES2Viewport(){};(Viewport)
 */

std::vector<std::tr1::function<void()> > v;

void HAHA() {
  v.back()();
  v.pop_back();

}

void GLES2UseProgram(GLuint program) {
  std::tr1::function<void()> f = std::tr1::bind(::GLES2UseProgram, program);

  v.push_back(f);

  HAHA();
}

}  // namespace

#endif /* FURAI_GL2_H_ */
