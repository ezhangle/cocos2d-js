/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "js_bindings_config.h"
#include "js_bindings_core.h"
#include "jsfriendapi.h"
#include "jsb_opengl_manual.h"
#include "js_bindings_opengl.h"

#include "jsb_opengl_registration.h"

// system
#include "jsb_opengl_functions.h"

void JSB_register_opengl(JSContext *_cx, JSObject *object)
{
    //
    // gl
    //
    JSObject *opengl = JS_NewObject(_cx, NULL, JS::NullPtr(), JS::NullPtr());
    JS::HandleObject openglHandle(JS::HandleObject::fromMarkedLocation(&opengl));
    JS::HandleObject objectHandle(JS::HandleObject::fromMarkedLocation(&object));
    JS::RootedValue openglVal(_cx);
    openglVal = OBJECT_TO_JSVAL(opengl);
    JS_SetProperty(_cx, objectHandle, "gl", openglVal);

    JS::RootedValue nsval(_cx);
    JS::RootedObject ccns(_cx);
    JS_GetProperty(_cx, objectHandle, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ccns = JS_NewObject(_cx, NULL, JS::NullPtr(), JS::NullPtr());
        nsval = OBJECT_TO_JSVAL(ccns);
        JS_SetProperty(_cx, objectHandle, "cc", nsval);
    } else {
        JS_ValueToObject(_cx, nsval, &ccns);
    }
    
    js_register_cocos2dx_GLNode(_cx, ccns);
    
    // New WebGL functions, not present on OpenGL ES 2.0
    JS_DefineFunction(_cx, openglHandle, "getSupportedExtensions", JSB_glGetSupportedExtensions, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "activeTexture", JSB_glActiveTexture, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_attachShader", JSB_glAttachShader, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_bindAttribLocation", JSB_glBindAttribLocation, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_bindBuffer", JSB_glBindBuffer, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_bindFramebuffer", JSB_glBindFramebuffer, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_bindRenderbuffer", JSB_glBindRenderbuffer, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_bindTexture", JSB_glBindTexture, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "blendColor", JSB_glBlendColor, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "blendEquation", JSB_glBlendEquation, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "blendEquationSeparate", JSB_glBlendEquationSeparate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "blendFunc", JSB_glBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "blendFuncSeparate", JSB_glBlendFuncSeparate, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "bufferData", JSB_glBufferData, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "bufferSubData", JSB_glBufferSubData, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "checkFramebufferStatus", JSB_glCheckFramebufferStatus, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "clear", JSB_glClear, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "clearColor", JSB_glClearColor, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "clearDepthf", JSB_glClearDepthf, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "clearStencil", JSB_glClearStencil, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "colorMask", JSB_glColorMask, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_compileShader", JSB_glCompileShader, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "compressedTexImage2D", JSB_glCompressedTexImage2D, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "compressedTexSubImage2D", JSB_glCompressedTexSubImage2D, 9, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "copyTexImage2D", JSB_glCopyTexImage2D, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "copyTexSubImage2D", JSB_glCopyTexSubImage2D, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createProgram", JSB_glCreateProgram, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createShader", JSB_glCreateShader, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "cullFace", JSB_glCullFace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteBuffer", JSB_glDeleteBuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteFramebuffer", JSB_glDeleteFramebuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteProgram", JSB_glDeleteProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteRenderbuffer", JSB_glDeleteRenderbuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteShader", JSB_glDeleteShader, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_deleteTexture", JSB_glDeleteTextures, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "depthFunc", JSB_glDepthFunc, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "depthMask", JSB_glDepthMask, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "depthRangef", JSB_glDepthRangef, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "detachShader", JSB_glDetachShader, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "disable", JSB_glDisable, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "disableVertexAttribArray", JSB_glDisableVertexAttribArray, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "drawArrays", JSB_glDrawArrays, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "drawElements", JSB_glDrawElements, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "enable", JSB_glEnable, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "enableVertexAttribArray", JSB_glEnableVertexAttribArray, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "finish", JSB_glFinish, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "flush", JSB_glFlush, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "framebufferRenderbuffer", JSB_glFramebufferRenderbuffer, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "framebufferTexture2D", JSB_glFramebufferTexture2D, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "frontFace", JSB_glFrontFace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createBuffer", JSB_glGenBuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createFramebuffer", JSB_glGenFramebuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createRenderbuffer", JSB_glGenRenderbuffers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_createTexture", JSB_glGenTextures, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "generateMipmap", JSB_glGenerateMipmap, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getActiveAttrib", JSB_glGetActiveAttrib, 7, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getActiveUniform", JSB_glGetActiveUniform, 7, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getAttachedShaders", JSB_glGetAttachedShaders, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getAttribLocation", JSB_glGetAttribLocation, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "getError", JSB_glGetError, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getProgramInfoLog", JSB_glGetProgramInfoLog, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getProgramParameter", JSB_glGetProgramiv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getShaderInfoLog", JSB_glGetShaderInfoLog, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getShaderSource", JSB_glGetShaderSource, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getShaderParameter", JSB_glGetShaderiv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "getTexParameter", JSB_glGetTexParameterfv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getUniformLocation", JSB_glGetUniformLocation, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_getUniform", JSB_glGetUniformfv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "hint", JSB_glHint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isBuffer", JSB_glIsBuffer, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isEnabled", JSB_glIsEnabled, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isFramebuffer", JSB_glIsFramebuffer, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isProgram", JSB_glIsProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isRenderbuffer", JSB_glIsRenderbuffer, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isShader", JSB_glIsShader, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "isTexture", JSB_glIsTexture, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "lineWidth", JSB_glLineWidth, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_linkProgram", JSB_glLinkProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "pixelStorei", JSB_glPixelStorei, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "polygonOffset", JSB_glPolygonOffset, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "readPixels", JSB_glReadPixels, 7, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "releaseShaderCompiler", JSB_glReleaseShaderCompiler, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "renderbufferStorage", JSB_glRenderbufferStorage, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "sampleCoverage", JSB_glSampleCoverage, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "scissor", JSB_glScissor, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_shaderSource", JSB_glShaderSource, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilFunc", JSB_glStencilFunc, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilFuncSeparate", JSB_glStencilFuncSeparate, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilMask", JSB_glStencilMask, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilMaskSeparate", JSB_glStencilMaskSeparate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilOp", JSB_glStencilOp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "stencilOpSeparate", JSB_glStencilOpSeparate, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_texImage2D", JSB_glTexImage2D, 9, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "texParameterf", JSB_glTexParameterf, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "texParameteri", JSB_glTexParameteri, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_texSubImage2D", JSB_glTexSubImage2D, 9, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform1f", JSB_glUniform1f, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform1fv", JSB_glUniform1fv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform1i", JSB_glUniform1i, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform1iv", JSB_glUniform1iv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform2f", JSB_glUniform2f, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform2fv", JSB_glUniform2fv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform2i", JSB_glUniform2i, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform2iv", JSB_glUniform2iv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform3f", JSB_glUniform3f, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform3fv", JSB_glUniform3fv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform3i", JSB_glUniform3i, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform3iv", JSB_glUniform3iv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform4f", JSB_glUniform4f, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform4fv", JSB_glUniform4fv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform4i", JSB_glUniform4i, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniform4iv", JSB_glUniform4iv, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniformMatrix2fv", JSB_glUniformMatrix2fv, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniformMatrix3fv", JSB_glUniformMatrix3fv, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "uniformMatrix4fv", JSB_glUniformMatrix4fv, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_useProgram", JSB_glUseProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "_validateProgram", JSB_glValidateProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib1f", JSB_glVertexAttrib1f, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib1fv", JSB_glVertexAttrib1fv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib2f", JSB_glVertexAttrib2f, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib2fv", JSB_glVertexAttrib2fv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib3f", JSB_glVertexAttrib3f, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib3fv", JSB_glVertexAttrib3fv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib4f", JSB_glVertexAttrib4f, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttrib4fv", JSB_glVertexAttrib4fv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "vertexAttribPointer", JSB_glVertexAttribPointer, 6, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, openglHandle, "viewport", JSB_glViewport, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    
}

