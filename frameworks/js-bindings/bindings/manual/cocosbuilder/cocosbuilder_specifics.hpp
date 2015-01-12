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

#ifndef __JS_COCOSBUILDER_SPECIFICS_H__
#define __JS_COCOSBUILDER_SPECIFICS_H__

#include "../cocos2d_specifics.hpp"

class JSCCBAnimationWrapper: public JSCallbackWrapper {
public:
    JSCCBAnimationWrapper() {}
    virtual ~JSCCBAnimationWrapper() {}
    
    void animationCompleteCallback() {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retVal = JSVAL_NULL;
        
        if(!_jsCallback.isUndefined() && !_jsThisObj.isUndefined()) {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

            JS::AutoValueVector dummyArr(cx);
            JSObject* obj = _jsThisObj.toObjectOrNull();
            JS::HandleObject objHandle(JS::HandleObject::fromMarkedLocation(&obj));
            JS::HandleValue _jsCallbackHandle(JS::HandleValue::fromMarkedLocation(_jsCallback.address()));
            JS::MutableHandleValue retValHandle(JS::MutableHandleValue::fromMarkedLocation(&retVal));
            JS_CallFunctionValue(cx, objHandle, _jsCallbackHandle, dummyArr, retValHandle);
        }
    }
    
};

#endif
