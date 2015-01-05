/*
 * Created by Rohan Kuruvilla
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

#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "js_bindings_core.h"
#include "js_bindings_config.h"
#include "cocos2d.h"
#include "spidermonkey_specifics.h"
#include "chipmunk_private.h"

// just a simple utility to avoid mem leaking when using JSString
class CC_BINDING_DLL JSStringWrapper
{
public:
    JSStringWrapper();
    JSStringWrapper(JSString* str, JSContext* cx = NULL);
    JSStringWrapper(jsval val, JSContext* cx = NULL);
    ~JSStringWrapper();
    
    void set(jsval val, JSContext* cx);
    void set(JSString* str, JSContext* cx);
    const char* get();
    
private:
    const char* _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JSStringWrapper);
};

// wraps a function and "this" object
class CC_BINDING_DLL JSFunctionWrapper
{
public:
    JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval);
    ~JSFunctionWrapper();

    bool invoke(unsigned int argc, jsval *argv, jsval &rval);
private:
    JSContext *_cx;
    JSObject *_jsthis;
    jsval _fval;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JSFunctionWrapper);
};

CC_BINDING_DLL bool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
CC_BINDING_DLL bool jsval_to_int( JSContext *cx, jsval vp, int *out);
CC_BINDING_DLL bool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *out);
CC_BINDING_DLL bool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy);
/** converts a jsval (JS string) into a char */
bool jsval_to_charptr( JSContext *cx, jsval vp, const char **out);

CC_BINDING_DLL jsval opaque_to_jsval( JSContext *cx, void* opaque);
CC_BINDING_DLL jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name);

/* Converts a char ptr into a jsval (using JS string) */
jsval charptr_to_jsval( JSContext *cx, const char *str);
bool JSB_jsval_typedarray_to_dataptr(JSContext *cx, jsval vp, GLsizei *count, void **data, js::Scalar::Type t);
bool JSB_get_arraybufferview_dataptr(JSContext *cx, jsval vp, GLsizei *count, GLvoid **data );

// some utility functions
// to native
CC_BINDING_DLL bool jsval_to_ushort( JSContext *cx, jsval vp, unsigned short *ret );
CC_BINDING_DLL bool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
CC_BINDING_DLL bool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
CC_BINDING_DLL bool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
CC_BINDING_DLL bool jsval_to_long( JSContext *cx, jsval vp, long *out);
CC_BINDING_DLL bool jsval_to_ulong( JSContext *cx, jsval vp, unsigned long *out);
CC_BINDING_DLL bool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
CC_BINDING_DLL bool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);
CC_BINDING_DLL bool jsval_to_ccpoint(JSContext *cx, jsval v, cocos2d::Point* ret);
CC_BINDING_DLL bool jsval_to_ccrect(JSContext *cx, jsval v, cocos2d::Rect* ret);
CC_BINDING_DLL bool jsval_to_ccsize(JSContext *cx, jsval v, cocos2d::Size* ret);
CC_BINDING_DLL bool jsval_to_cccolor4b(JSContext *cx, jsval v, cocos2d::Color4B* ret);
CC_BINDING_DLL bool jsval_to_cccolor4f(JSContext *cx, jsval v, cocos2d::Color4F* ret);
CC_BINDING_DLL bool jsval_to_cccolor3b(JSContext *cx, jsval v, cocos2d::Color3B* ret);
CC_BINDING_DLL bool jsval_cccolor_to_opacity(JSContext *cx, jsval v, int32_t* ret);
CC_BINDING_DLL bool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, cocos2d::Point **points, int *numPoints);
CC_BINDING_DLL bool jsval_to_ccarray(JSContext* cx, jsval v, cocos2d::__Array** ret);
CC_BINDING_DLL bool jsval_to_ccdictionary(JSContext* cx, jsval v, cocos2d::__Dictionary** ret);
CC_BINDING_DLL bool jsval_to_ccacceleration(JSContext* cx,jsval v, cocos2d::Acceleration* ret);
CC_BINDING_DLL bool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, cocos2d::__Array** ret);

// forward declaration
CC_BINDING_DLL js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);

template <class T>
bool jsvals_variadic_to_ccvector( JSContext *cx, jsval *vp, int argc, cocos2d::Vector<T>* ret)
{
    bool ok = true;

    for (int i = 0; i < argc; i++)
    {
        js_proxy_t* p;
        JSObject* obj = vp->toObjectOrNull();
        p = jsb_get_js_proxy(obj);
        CCASSERT(p, "Native object not found!");
        if (p) {
            ret->pushBack((T)p->ptr);
        }
        
        // next
        vp++;
    }

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    return ok;
}

bool jsvals_variadic_to_ccvaluevector( JSContext *cx, jsval *vp, int argc, cocos2d::ValueVector* ret);

bool jsval_to_ccaffinetransform(JSContext* cx, jsval v, cocos2d::AffineTransform* ret);
bool jsval_to_FontDefinition( JSContext *cx, jsval vp, cocos2d::FontDefinition* ret );

template <class T>
bool jsval_to_ccvector(JSContext* cx, jsval v, cocos2d::Vector<T>* ret)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue jsval(cx, v);

    bool ok = jsval.isObject() && JS_ValueToObject( cx, jsval, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);

    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            CCASSERT(value.isObject(), "the element in Vector isn't a native object.");

            js_proxy_t *proxy;
            JSObject *tmp = value.toObjectOrNull();
            proxy = jsb_get_js_proxy(tmp);
            T cobj = (T)(proxy ? proxy->ptr : nullptr);
            if (cobj)
            {
                ret->pushBack(cobj);
            }
        }
    }

    return true;
}

CC_BINDING_DLL bool jsval_to_ccvalue(JSContext* cx, jsval v, cocos2d::Value* ret);
CC_BINDING_DLL bool jsval_to_ccvaluemap(JSContext* cx, jsval v, cocos2d::ValueMap* ret);
CC_BINDING_DLL bool jsval_to_ccvaluemapintkey(JSContext* cx, jsval v, cocos2d::ValueMapIntKey* ret);
CC_BINDING_DLL bool jsval_to_ccvaluevector(JSContext* cx, jsval v, cocos2d::ValueVector* ret);
CC_BINDING_DLL bool jsval_to_ssize( JSContext *cx, jsval vp, ssize_t* ret);
CC_BINDING_DLL bool jsval_to_std_vector_string( JSContext *cx, jsval vp, std::vector<std::string>* ret);
CC_BINDING_DLL bool jsval_to_std_vector_int( JSContext *cx, jsval vp, std::vector<int>* ret);
CC_BINDING_DLL bool jsval_to_matrix(JSContext *cx, jsval vp, cocos2d::Mat4* ret);
CC_BINDING_DLL bool jsval_to_vector2(JSContext *cx, jsval vp, cocos2d::Vec2* ret);
CC_BINDING_DLL bool jsval_to_vector3(JSContext *cx, jsval vp, cocos2d::Vec3* ret);
CC_BINDING_DLL bool jsval_to_blendfunc(JSContext *cx, jsval vp, cocos2d::BlendFunc* ret);

template <class T>
bool jsval_to_ccmap_string_key(JSContext *cx, jsval v, cocos2d::Map<std::string, T>* ret)
{
    if (JSVAL_IS_NULL(v) || v.isUndefined())
    {
        return true;
    }
    
    JSObject* tmp = v.toObjectOrNull();
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return false;
    }
    
    JSObject* it = JS_NewPropertyIterator(cx, tmp);
    
    while (true)
    {
        jsid idp;
        jsval key;
        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
            return false; // error
        }
        
        if (key == JSVAL_VOID) {
            break; // end of iteration
        }
        
        if (!JSVAL_IS_STRING(key)) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            js_proxy_t *proxy = nullptr;
            JSObject* jsobj = value.toObjectOrNull();
            proxy = jsb_get_js_proxy(jsobj);
            CCASSERT(proxy, "Native object should be added!");
            T cobj = (T)(proxy ? proxy->ptr : nullptr);
            ret->insert(keyWrapper.get(), cobj);
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
}

// from native
CC_BINDING_DLL jsval int32_to_jsval( JSContext *cx, int32_t l);
CC_BINDING_DLL jsval uint32_to_jsval( JSContext *cx, uint32_t number );
CC_BINDING_DLL jsval ushort_to_jsval( JSContext *cx, unsigned short number );
CC_BINDING_DLL jsval long_to_jsval( JSContext *cx, long number );
CC_BINDING_DLL jsval ulong_to_jsval(JSContext* cx, unsigned long v);
CC_BINDING_DLL jsval long_long_to_jsval(JSContext* cx, long long v);
CC_BINDING_DLL jsval std_string_to_jsval(JSContext* cx, const std::string& v);
CC_BINDING_DLL jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);
CC_BINDING_DLL jsval ccpoint_to_jsval(JSContext* cx, const cocos2d::Point& v);
CC_BINDING_DLL jsval ccrect_to_jsval(JSContext* cx, const cocos2d::Rect& v);
CC_BINDING_DLL jsval ccsize_to_jsval(JSContext* cx, const cocos2d::Size& v);
CC_BINDING_DLL jsval cccolor4b_to_jsval(JSContext* cx, const cocos2d::Color4B& v);
CC_BINDING_DLL jsval cccolor4f_to_jsval(JSContext* cx, const cocos2d::Color4F& v);
CC_BINDING_DLL jsval cccolor3b_to_jsval(JSContext* cx, const cocos2d::Color3B& v);
CC_BINDING_DLL jsval ccdictionary_to_jsval(JSContext* cx, cocos2d::__Dictionary *dict);
CC_BINDING_DLL jsval ccarray_to_jsval(JSContext* cx, cocos2d::__Array *arr);
CC_BINDING_DLL jsval ccacceleration_to_jsval(JSContext* cx, const cocos2d::Acceleration& v);
CC_BINDING_DLL jsval ccaffinetransform_to_jsval(JSContext* cx, const cocos2d::AffineTransform& t);
CC_BINDING_DLL jsval FontDefinition_to_jsval(JSContext* cx, const cocos2d::FontDefinition& t);

CC_BINDING_DLL bool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *out );
CC_BINDING_DLL jsval CGPoint_to_jsval( JSContext *cx, cpVect p );

#define cpVect_to_jsval CGPoint_to_jsval
#define jsval_to_cpVect jsval_to_CGPoint


template<class T>
js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj);

template <class T>
jsval ccvector_to_jsval(JSContext* cx, const cocos2d::Vector<T>& v)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    
    int i = 0;
    for (const auto& obj : v)
    {
        JS::RootedValue arrElement(cx);
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy(cx, obj);
        if (jsproxy) {
            arrElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }

        if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

template <class T>
jsval ccmap_string_key_to_jsval(JSContext* cx, const cocos2d::Map<std::string, T>& v)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue element(cx);
        
        std::string key = iter->first;
        T obj = iter->second;
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy(cx, obj);
        if (jsproxy) {
            element = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRet, key.c_str(), element);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

CC_BINDING_DLL jsval ccvalue_to_jsval(JSContext* cx, const cocos2d::Value& v);
CC_BINDING_DLL jsval ccvaluemap_to_jsval(JSContext* cx, const cocos2d::ValueMap& v);
CC_BINDING_DLL jsval ccvaluemapintkey_to_jsval(JSContext* cx, const cocos2d::ValueMapIntKey& v);
CC_BINDING_DLL jsval ccvaluevector_to_jsval(JSContext* cx, const cocos2d::ValueVector& v);
CC_BINDING_DLL jsval ssize_to_jsval(JSContext *cx, ssize_t v);
CC_BINDING_DLL jsval std_vector_string_to_jsval( JSContext *cx, const std::vector<std::string>& v);
CC_BINDING_DLL jsval std_vector_int_to_jsval( JSContext *cx, const std::vector<int>& v);
CC_BINDING_DLL jsval matrix_to_jsval(JSContext *cx, const cocos2d::Mat4& v);
CC_BINDING_DLL jsval vector2_to_jsval(JSContext *cx, const cocos2d::Vec2& v);
CC_BINDING_DLL jsval vector3_to_jsval(JSContext *cx, const cocos2d::Vec3& v);
CC_BINDING_DLL jsval blendfunc_to_jsval(JSContext *cx, const cocos2d::BlendFunc& v);

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

