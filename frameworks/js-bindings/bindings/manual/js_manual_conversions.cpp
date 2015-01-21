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

#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "js_manual_conversions.h"
#include "cocos2d_specifics.hpp"
#include "math/TransformUtils.h"

USING_NS_CC;
using namespace JS;

// JSStringWrapper
JSStringWrapper::JSStringWrapper()
: _buffer(nullptr)
{
}

JSStringWrapper::JSStringWrapper(JSString* str, JSContext* cx/* = NULL*/)
: _buffer(nullptr)
{
    set(str, cx);
}

JSStringWrapper::JSStringWrapper(jsval val, JSContext* cx/* = NULL*/)
: _buffer(nullptr)
{
    set(val, cx);
}

JSStringWrapper::~JSStringWrapper()
{
    CC_SAFE_DELETE_ARRAY(_buffer);
}

void JSStringWrapper::set(jsval val, JSContext* cx)
{
    if (val.isString())
    {
        this->set(val.toString(), cx);
    }
    else
    {
        CC_SAFE_DELETE_ARRAY(_buffer);
    }
}

void JSStringWrapper::set(JSString* str, JSContext* cx)
{
    CC_SAFE_DELETE_ARRAY(_buffer);
    
    if (!cx)
    {
        cx = ScriptingCore::getInstance()->getGlobalContext();
    }
    // JS_EncodeString isn't supported in SpiderMonkey ff19.0.
    //buffer = JS_EncodeString(cx, string);
    //unsigned short* pStrUTF16 = (unsigned short*)JS_GetStringCharsZ(cx, str);
    //_buffer = cc_utf16_to_utf8(pStrUTF16, -1, NULL, NULL);
    _buffer = JS_EncodeString(cx, str);
}

const char* JSStringWrapper::get()
{
    return _buffer ? _buffer : "";
}

// JSFunctionWrapper
JSFunctionWrapper::JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval)
: _cx(cx)
, _jsthis(jsthis)
, _fval(fval)
{
    AddNamedValueRoot(cx, &this->_fval, "JSFunctionWrapper");
    AddNamedObjectRoot(cx, &this->_jsthis, "JSFunctionWrapper");
}

JSFunctionWrapper::~JSFunctionWrapper()
{
    RemoveValueRoot(this->_cx, &this->_fval);
    RemoveObjectRoot(this->_cx, &this->_jsthis);
}

bool JSFunctionWrapper::invoke(unsigned int argc, jsval *argv, MutableHandleValue rval)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::AutoValueVector dummyArr(this->_cx);
    dummyArr.append(argv, argc);
    JS::HandleObject _jsthisHandle(JS::HandleObject::fromMarkedLocation(_jsthis.address()));
    JS::HandleValue _fvalHandle(JS::HandleValue::fromMarkedLocation(_fval.address()));
    return JS_CallFunctionValue(this->_cx, _jsthisHandle, _fvalHandle, dummyArr, rval);
}

static Color3B getColorFromJSObject(JSContext *cx, JSObject *colorObject)
{
    JS::RootedValue jsr(cx);
    JS::HandleObject colorObjectHandle(JS::HandleObject::fromMarkedLocation(&colorObject));
    Color3B out;
    JS_GetProperty(cx, colorObjectHandle, "r", &jsr);
    double fontR = 0.0;
    JS::ToNumber(cx, jsr, &fontR);
    
    JS_GetProperty(cx, colorObjectHandle, "g", &jsr);
    double fontG = 0.0;
    JS::ToNumber(cx, jsr, &fontG);
    
    JS_GetProperty(cx, colorObjectHandle, "b", &jsr);
    double fontB = 0.0;
    JS::ToNumber(cx, jsr, &fontB);
    
    // the out
    out.r = (unsigned char)fontR;
    out.g = (unsigned char)fontG;
    out.b = (unsigned char)fontB;
    
    return out;
}

static Size getSizeFromJSObject(JSContext *cx, JSObject *sizeObject)
{
    JS::RootedValue jsr(cx);
    JS::HandleObject sizeObjectHandle(JS::HandleObject::fromMarkedLocation(&sizeObject));
    Size out;
    JS_GetProperty(cx, sizeObjectHandle, "width", &jsr);
    double width = 0.0;
    JS::ToNumber(cx, jsr, &width);
    
    JS_GetProperty(cx, sizeObjectHandle, "height", &jsr);
    double height = 0.0;
    JS::ToNumber(cx, jsr, &height);
    
    
    // the out
    out.width  = width;
    out.height = height;
    
    return out;
}

bool jsval_to_opaque( JSContext *cx, jsval vp, void **r)
{
#ifdef __LP64__

    // begin
    JS::RootedObject tmp_arg(cx);
	bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, vp), &tmp_arg );
	JSB_PRECONDITION2( ok, cx, false, "Error converting value to object");
	JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, false, "Not a TypedArray object");
	JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(void*), cx, false, "Invalid Typed Array length");

	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	uint64_t ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];

#else
	assert( sizeof(int)==4);
	int32_t ret;
	if( ! jsval_to_int32(cx, vp, &ret ) )
	  return false;
#endif
	*r = (void*)ret;
	return true;
}

bool jsval_to_int( JSContext *cx, jsval vp, int *ret )
{
	// Since this is called to cast uint64 to uint32,
	// it is needed to initialize the value to 0 first
#ifdef __LP64__
	long *tmp = (long*)ret;
	*tmp = 0;
#endif
	return jsval_to_int32(cx, vp, (int32_t*)ret);
}

jsval opaque_to_jsval( JSContext *cx, void *opaque )
{
#ifdef __LP64__
	uint64_t number = (uint64_t)opaque;
	JSObject *typedArray = JS_NewUint32Array( cx, 2 );
	uint32_t *buffer = (uint32_t*)JS_GetArrayBufferViewData(typedArray);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);
#else
	assert(sizeof(int)==4);
	int32_t number = (int32_t) opaque;
	return INT_TO_JSVAL(number);
#endif
}

jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name)
{
	JSObject *jsobj = jsb_get_jsobject_for_proxy(handle);
	if(!jsobj) {
		JS::HandleObject objectHandle(JS::HandleObject::fromMarkedLocation(&object));
		jsobj = JS_NewObject(cx, klass, objectHandle, JS::NullPtr());
		CCASSERT(jsobj, "Invalid object");
		jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
		jsb_set_jsobject_for_proxy(jsobj, handle);
	}
	return OBJECT_TO_JSVAL(jsobj);
}

bool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy)
{
 	JS::RootedObject jsobj(cx);
	JS::RootedValue dummy(cx, vp);
	bool ok = JS_ValueToObject( cx, dummy, &jsobj );
	JSB_PRECONDITION2(ok, cx, false, "Error converting jsval to object");
	
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);
	*out_native = proxy->handle;
	if( out_proxy )
		*out_proxy = proxy;
	return true;
}

bool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *ret )
{
	// Since this is called to cast uint64 to uint32,
	// it is needed to initialize the value to 0 first
#ifdef __LP64__
	long *tmp = (long*)ret;
	*tmp = 0;
#endif
	return jsval_to_int32(cx, vp, (int32_t*)ret);
}

jsval long_to_jsval( JSContext *cx, long number )
{
#ifdef __LP64__
	assert( sizeof(long)==8);

	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%ld", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
#else
	CCASSERT( sizeof(int)==4, "Error!");
	return INT_TO_JSVAL(number);
#endif
}

jsval ulong_to_jsval( JSContext *cx, unsigned long number )
{
#ifdef __LP64__
	assert( sizeof(unsigned long)==8);
    
	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%lu", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
#else
	CCASSERT( sizeof(int)==4, "Error!");
	return UINT_TO_JSVAL(number);
#endif
}

jsval long_long_to_jsval( JSContext *cx, long long number )
{
#if JSB_REPRESENT_LONGLONG_AS_STR
	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%lld", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
    
#else
	CCASSERT( sizeof(long long)==8, "Error!");
	JSObject *typedArray = JS_NewUint32Array( cx, 2 );
	uint32_t *buffer = (uint32_t*)JS_GetArrayBufferViewData(typedArray, cx);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);
#endif
}

bool jsval_to_charptr( JSContext *cx, jsval vp, const char **ret )
{
    JS::RootedValue dummy(cx, vp);
    JSString *jsstr = JS::ToString( cx, dummy );
    JSB_PRECONDITION2( jsstr, cx, false, "invalid string" );

    // root it
    vp = STRING_TO_JSVAL(jsstr);

    JSStringWrapper strWrapper(jsstr);
    
    // XXX: It is converted to String and then back to char* to autorelease the created object.
    __String *tmp = String::create(strWrapper.get());

    JSB_PRECONDITION2( tmp, cx, false, "Error creating string from UTF8");

    *ret = tmp->getCString();

    return true;
}

jsval charptr_to_jsval( JSContext *cx, const char *str)
{
    return c_string_to_jsval(cx, str);
}

bool JSB_jsval_typedarray_to_dataptr(JSContext *cx, jsval vp, GLsizei *count, void **data, js::Scalar::Type t)
{
	JS::RootedObject jsobj(cx);
	JS::RootedValue dummy(cx, vp);
	bool ok = JS_ValueToObject( cx, dummy, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, false, "Error converting value to object");
    
	// WebGL supports TypedArray and sequences for some of its APIs. So when converting a TypedArray, we should
	// also check for a possible non-Typed Array JS object, like a JS Array.
    
	if( JS_IsTypedArrayObject( jsobj ) ) {
        
		*count = JS_GetTypedArrayLength(jsobj);
		js::Scalar::Type type = JS_GetArrayBufferViewType(jsobj);
		JSB_PRECONDITION2(t==type, cx, false, "TypedArray type different than expected type");
        
		switch (t) {
			case js::Scalar::Int8:
			case js::Scalar::Uint8:
				*data = JS_GetUint8ArrayData(jsobj);
				break;
                
			case js::Scalar::Int16:
			case js::Scalar::Uint16:
				*data = JS_GetUint16ArrayData(jsobj);
				break;
                
			case js::Scalar::Int32:
			case js::Scalar::Uint32:
				*data = JS_GetUint32ArrayData(jsobj);
				break;
                
			case js::Scalar::Float32:
				*data = JS_GetFloat32ArrayData(jsobj);
				break;
                
			default:
				JSB_PRECONDITION2(false, cx, false, "Unsupported typedarray type");
				break;
		}
	} else if( JS_IsArrayObject(cx, jsobj)) {
		// Slow... avoid it. Use TypedArray instead, but the spec says that it can receive
		// Sequence<> as well.
		uint32_t length;
		JS_GetArrayLength(cx, jsobj, &length);
        
		for( uint32_t i=0; i<length;i++ ) {
            
            JS::RootedValue valarg(cx);
			JS_GetElement(cx, jsobj, i, &valarg);
            
			switch(t) {
				case js::Scalar::Int32:
				case js::Scalar::Uint32:
				{
					uint32_t e = valarg.toInt32();
					((uint32_t*)data)[i] = e;
					break;
				}
				case js::Scalar::Float32:
				{
					double e = valarg.toDouble();
					((GLfloat*)data)[i] = (GLfloat)e;
					break;
				}
				default:
					JSB_PRECONDITION2(false, cx, false, "Unsupported typedarray type");
					break;
			}
		}
        
	} else
		JSB_PRECONDITION2(false, cx, false, "Object shall be a TypedArray or Sequence");
    
	return true;
}

bool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data )
{
	JS::RootedObject jsobj(cx);
	JS::RootedValue dummy(cx, vp);
	bool ok = JS_ValueToObject( cx, dummy, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, false, "Error converting value to object");
	JSB_PRECONDITION2( JS_IsArrayBufferViewObject(jsobj), cx, false, "Not an Scalar object");
    
	*data = JS_GetArrayBufferViewData(jsobj);
	*count = JS_GetArrayBufferViewByteLength(jsobj);
    
	return true;
}


#pragma mark - Conversion Routines
bool jsval_to_ushort( JSContext *cx, jsval vp, unsigned short *outval )
{
    bool ok = true;
    double dp;
    JS::RootedValue dummy(cx, vp);
    ok &= JS::ToNumber(cx, dummy, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    *outval = (unsigned short)dp;

    return ok;
}

bool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    bool ok = true;
    double dp;
    JS::RootedValue dummy(cx, vp);
    ok &= JS::ToNumber(cx, dummy, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (int32_t)dp;
    
    return ok;
}

bool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    bool ok = true;
    double dp;
    JS::RootedValue dummy(cx, vp);
    ok &= JS::ToNumber(cx, dummy, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (uint32_t)dp;
    
    return ok;
}

bool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    bool ok = true;
    double dp;
    JS::RootedValue dummy(cx, vp);
    ok &= JS::ToNumber(cx, dummy, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (uint16_t)dp;
    
    return ok;
}

// XXX: sizeof(long) == 8 in 64 bits on OS X... apparently on Windows it is 32 bits (???)
bool jsval_to_long( JSContext *cx, jsval vp, long *r )
{
#ifdef __LP64__
	// compatibility check
	assert( sizeof(long)==8);
	JSString *jsstr = JS::ToString(cx, JS::RootedValue(cx, vp));
	JSB_PRECONDITION2(jsstr, cx, false, "Error converting value to string");
    
	char *str = JS_EncodeString(cx, jsstr);
	JSB_PRECONDITION2(str, cx, false, "Error encoding string");
    
	char *endptr;
	long ret = strtol(str, &endptr, 10);
    
	*r = ret;
	return true;
    
#else
	// compatibility check
	assert( sizeof(int)==4);
	long ret = vp.toInt32();
#endif
	
	*r = ret;
	return true;
}


bool jsval_to_ulong( JSContext *cx, jsval vp, unsigned long *out)
{
    if (out == nullptr)
        return false;
    
    long rval = 0;
    bool ret = false;
    ret = jsval_to_long(cx, vp, &rval);
    if (ret)
    {
        *out = (unsigned long)rval;
    }
    return ret;
}

bool jsval_to_long_long(JSContext *cx, jsval vp, long long* r)
{
	JS::RootedObject tmp_arg(cx);
	JS::RootedValue dummy(cx, vp);
	bool ok = JS_ValueToObject( cx, dummy, &tmp_arg );
	JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
	JSB_PRECONDITION3( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, false, "Not a TypedArray object");
	JSB_PRECONDITION3( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, false, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return true;
}

bool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JS::RootedValue dummy(cx, v);
    JSString *tmp = JS::ToString(cx, dummy);
    JSB_PRECONDITION3(tmp, cx, false, "Error processing arguments");
    
    JSStringWrapper str(tmp);
    *ret = str.get();
    return true;
}

bool jsval_to_ccpoint(JSContext *cx, jsval v, Point* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue dummy(cx, v);
    double x, y;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return true;
}

bool jsval_to_ccacceleration(JSContext* cx,jsval v, Acceleration* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    JS::RootedValue jstimestamp(cx);
    JS::RootedValue dummy(cx, v);
    
    double x, y, timestamp, z;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "timestamp", &jstimestamp) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jsz, &z) &&
    JS::ToNumber(cx, jstimestamp, &timestamp);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = x;
    ret->y = y;
    ret->z = z;
    ret->timestamp = timestamp;
    return true;
}

bool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, __Array** ret)
{
    bool ok = true;
    __Array* pArray = Array::create();
    for( int i=0; i < argc; i++ )
    {
        double num = 0.0;
        // optimization: JS::ToNumber is expensive. And can convert an string like "12" to a number
        if (vp->isNumber()) {
            JS::RootedValue dummy(cx, *vp);
            ok &= JS::ToNumber(cx, dummy, &num );
            if (!ok) {
                break;
            }
            pArray->addObject(Integer::create((int)num));
        }
        else if (vp->isString())
        {
            JSStringWrapper str(vp->toString(), cx);
            pArray->addObject(String::create(str.get()));
        }
        else
        {
            js_proxy_t* p;
            JSObject* obj = vp->toObjectOrNull();
            p = jsb_get_js_proxy(obj);
            if (p) {
                pArray->addObject((Ref*)p->ptr);
            }
        }
        // next
        vp++;
    }
    *ret = pArray;
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    return ok;
}

bool jsvals_variadic_to_ccvaluevector( JSContext *cx, jsval *vp, int argc, cocos2d::ValueVector* ret)
{
    for (int i = 0; i < argc; i++)
    {
        jsval value = *vp;
        if (value.isObject())
        {
            JSObject* jsobj = value.toObjectOrNull();
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            JS::HandleObject jsobjHandle(JS::HandleObject::fromMarkedLocation(&jsobj));
            if (!JS_IsArrayObject(cx, jsobjHandle))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    ret->push_back(cocos2d::Value(dictVal));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    ret->push_back(cocos2d::Value(arrVal));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            ret->push_back(cocos2d::Value(valueWapper.get()));
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            JS::RootedValue dummy(cx, value);
            bool ok = JS::ToNumber(cx, dummy, &number);
            if (ok)
            {
                ret->push_back(cocos2d::Value(number));
            }
        }
        else if (value.isBoolean())
        {
            JS::RootedValue dummy(cx, value);
            bool boolVal = JS::ToBoolean(dummy);
            ret->push_back(cocos2d::Value(boolVal));
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
        // next
        vp++;
    }
    
    return true;
}

bool jsval_to_ccrect(JSContext *cx, jsval v, Rect* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jswidth(cx);
    JS::RootedValue jsheight(cx);
    JS::RootedValue dummy(cx, v);
    
    double x, y, width, height;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "width", &jswidth) &&
    JS_GetProperty(cx, tmp, "height", &jsheight) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jswidth, &width) &&
    JS::ToNumber(cx, jsheight, &height);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->origin.x = x;
    ret->origin.y = y;
    ret->size.width = width;
    ret->size.height = height;
    return true;
}

bool jsval_to_ccsize(JSContext *cx, jsval v, Size* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsw(cx);
    JS::RootedValue jsh(cx);
    JS::RootedValue dummy(cx, v);
    double w, h;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "width", &jsw) &&
    JS_GetProperty(cx, tmp, "height", &jsh) &&
    JS::ToNumber(cx, jsw, &w) &&
    JS::ToNumber(cx, jsh, &h);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ret->width = w;
    ret->height = h;
    return true;
}

bool jsval_to_cccolor4b(JSContext *cx, jsval v, Color4B* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    JS::RootedValue dummy(cx, v);
    
    double r, g, b, a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->r = (GLubyte)r;
    ret->g = (GLubyte)g;
    ret->b = (GLubyte)b;
    ret->a = (GLubyte)a;
    return true;
}

bool jsval_to_cccolor4f(JSContext *cx, jsval v, Color4F* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    JS::RootedValue dummy(cx, v);
    double r, g, b, a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ret->r = (float)r / 255;
    ret->g = (float)g / 255;
    ret->b = (float)b / 255;
    ret->a = (float)a / 255;
    return true;
}

bool jsval_to_cccolor3b(JSContext *cx, jsval v, Color3B* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue dummy(cx, v);
    double r, g, b;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->r = (GLubyte)r;
    ret->g = (GLubyte)g;
    ret->b = (GLubyte)b;
    return true;
}

bool jsval_cccolor_to_opacity(JSContext *cx, jsval v, int32_t* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsa(cx);
    JS::RootedValue dummy(cx, v);
    
    double a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_LookupProperty(cx, tmp, "a", &jsa) &&
    !jsa.isUndefined() &&
    JS::ToNumber(cx, jsa, &a);
    
    if (ok) {
        *ret = (int32_t)a;
        return true;
    }
    else return false;
}

bool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, Point **points, int *numPoints) {
    // Parsing sequence
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, v);
    bool ok = v.isObject() && JS_ValueToObject( cx, dummy, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");
    
    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);
    
    Point *array = new Point[len];

    for( uint32_t i=0; i< len;i++ ) {
        JS::RootedValue valarg(cx);
        JS_GetElement(cx, jsobj, i, &valarg);
        
        ok = jsval_to_ccpoint(cx, valarg, &array[i]);
        JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    }
    
    *numPoints = len;
    *points = array;
    
    return true;
}


bool jsval_to_ccarray(JSContext* cx, jsval v, __Array** ret)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, v);
    bool ok = v.isObject() && JS_ValueToObject( cx, dummy, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    __Array* arr = __Array::createWithCapacity(len);
    for (uint32_t i=0; i < len; i++) {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value)) {
            if (value.isObject())
            {
                js_proxy_t *proxy;
                JSObject *tmp = value.toObjectOrNull();
                JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
                proxy = jsb_get_js_proxy(tmp);
                cocos2d::Ref* cobj = (cocos2d::Ref *)(proxy ? proxy->ptr : NULL);
                // Don't test it.
                //TEST_NATIVE_OBJECT(cx, cobj)
                if (cobj) {
                    // It's a native js object.
                    arr->addObject(cobj);
                }
                else if (!JS_IsArrayObject(cx, tmpHandle)){
                    // It's a normal js object.
                    __Dictionary* dictVal = NULL;
                    ok = jsval_to_ccdictionary(cx, value, &dictVal);
                    if (ok) {
                        arr->addObject(dictVal);
                    }
                }
                else {
                    // It's a js array object.
                    __Array* arrVal = NULL;
                    ok = jsval_to_ccarray(cx, value, &arrVal);
                    if (ok) {
                        arr->addObject(arrVal);
                    }
                }
            }
            else if (value.isString()) {
                JSStringWrapper valueWapper(value.toString(), cx);
                arr->addObject(String::create(valueWapper.get()));
                //                CCLOG("iterate array: value = %s", valueWapper.get().c_str());
            }
            else if (value.isNumber()) {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok) {
                    arr->addObject(Double::create(number));
                    //                    CCLOG("iterate array: value = %lf", number);
                }
            }
            else if (value.isBoolean()) {
                bool boolVal = JS::ToBoolean(value);
                arr->addObject(Bool::create(boolVal));
                // CCLOG("iterate object: value = %d", boolVal);
            }
            else {
                CCASSERT(false, "not supported type");
            }
        }
    }
    *ret = arr;
    return true;
}

bool jsval_to_ccvalue(JSContext* cx, jsval v, cocos2d::Value* ret)
{
    if (v.isObject())
    {
        JSObject* jsobj = v.toObjectOrNull();
        CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
        JS::HandleObject jsobjHandle(JS::HandleObject::fromMarkedLocation(&jsobj));
        if (!JS_IsArrayObject(cx, jsobjHandle))
        {
            // It's a normal js object.
            ValueMap dictVal;
            bool ok = jsval_to_ccvaluemap(cx, v, &dictVal);
            if (ok)
            {
                *ret = cocos2d::Value(dictVal);
            }
        }
        else {
            // It's a js array object.
            ValueVector arrVal;
            bool ok = jsval_to_ccvaluevector(cx, v, &arrVal);
            if (ok)
            {
                *ret = cocos2d::Value(arrVal);
            }
        }
    }
    else if (v.isString())
    {
        JSStringWrapper valueWapper(v.toString(), cx);
        *ret = cocos2d::Value(valueWapper.get());
    }
    else if (v.isNumber())
    {
        double number = 0.0;
        JS::RootedValue dummy(cx, v);
        bool ok = JS::ToNumber(cx, dummy, &number);
        if (ok) {
            *ret = cocos2d::Value(number);
        }
    }
    else if (v.isBoolean())
    {
        JS::RootedValue dummy(cx, v);
        bool boolVal = JS::ToBoolean(dummy);
        *ret = cocos2d::Value(boolVal);
    }
    else {
        CCASSERT(false, "not supported type");
    }

    return true;
}

bool jsval_to_ccvaluemap(JSContext* cx, jsval v, cocos2d::ValueMap* ret)
{
    if (v.isNull() || v.isUndefined())
    {
        return true;
    }
    
    JSObject* tmp = v.toObjectOrNull();
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return false;
    }
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JSObject* it = JS_NewPropertyIterator(cx, tmpHandle);
    JS::HandleObject itHandle(JS::HandleObject::fromMarkedLocation(&it));
    
    ValueMap& dict = *ret;
    
    while (true)
    {
        jsid idp;
        jsval key;
        JS::HandleId idpHandle(JS::HandleId::fromMarkedLocation(&idp));
        JS::MutableHandleValue keyHandle(JS::MutableHandleValue::fromMarkedLocation(&key));
        if (!JS_NextProperty(cx, itHandle, &idp) || !JS_IdToValue(cx, idp, keyHandle)) {
            return false; // error
        }
        
        if (key == JSVAL_VOID) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmpHandle, idpHandle, &value);
        if (value.isObject())
        {
            JSObject* jsobj = value.toObjectOrNull();
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            JS::HandleObject jsobjHandle(JS::HandleObject::fromMarkedLocation(&jsobj));
            if (!JS_IsArrayObject(cx, jsobjHandle))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    dict.insert(ValueMap::value_type(keyWrapper.get(), cocos2d::Value(dictVal)));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    dict.insert(ValueMap::value_type(keyWrapper.get(), cocos2d::Value(arrVal)));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict.insert(ValueMap::value_type(keyWrapper.get(), cocos2d::Value(valueWapper.get())));
            //            CCLOG("iterate object: key = %s, value = %s", keyWrapper.get().c_str(), valueWapper.get().c_str());
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict.insert(ValueMap::value_type(keyWrapper.get(), cocos2d::Value(number)));
                // CCLOG("iterate object: key = %s, value = %lf", keyWrapper.get().c_str(), number);
            }
        }
        else if (value.isBoolean())
        {
            bool boolVal = JS::ToBoolean(value);
            dict.insert(ValueMap::value_type(keyWrapper.get(), cocos2d::Value(boolVal)));
            // CCLOG("iterate object: key = %s, value = %d", keyWrapper.get().c_str(), boolVal);
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
}

bool jsval_to_ccvaluemapintkey(JSContext* cx, jsval v, cocos2d::ValueMapIntKey* ret)
{
    if (v.isNull() || v.isUndefined())
    {
        return true;
    }
    
    JSObject* tmp = v.toObjectOrNull();
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return false;
    }
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JSObject* it = JS_NewPropertyIterator(cx, tmpHandle);
    JS::HandleObject itHandle(JS::HandleObject::fromMarkedLocation(&it));
    
    ValueMapIntKey& dict = *ret;
    
    while (true)
    {
        jsid idp;
        jsval key;
        JS::HandleId idpHandle(JS::HandleId::fromMarkedLocation(&idp));
        JS::MutableHandleValue keyHandle(JS::MutableHandleValue::fromMarkedLocation(&key));
        if (!JS_NextProperty(cx, itHandle, &idp) || !JS_IdToValue(cx, idp, keyHandle)) {
            return false; // error
        }
        
        if (key == JSVAL_VOID) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        int keyVal = key.toInt32();
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmpHandle, idpHandle, &value);
        if (value.isObject())
        {
            JSObject* jsobj = value.toObjectOrNull();
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            JS::HandleObject jsobjHandle(JS::HandleObject::fromMarkedLocation(&jsobj));
            if (!JS_IsArrayObject(cx, jsobjHandle))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    dict.insert(ValueMapIntKey::value_type(keyVal, cocos2d::Value(dictVal)));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    dict.insert(ValueMapIntKey::value_type(keyVal, cocos2d::Value(arrVal)));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict.insert(ValueMapIntKey::value_type(keyVal, cocos2d::Value(valueWapper.get())));
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict.insert(ValueMapIntKey::value_type(keyVal, cocos2d::Value(number)));
            }
        }
        else if (value.isBoolean())
        {
            bool boolVal = JS::ToBoolean(value);
            dict.insert(ValueMapIntKey::value_type(keyVal, cocos2d::Value(boolVal)));
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
}

bool jsval_to_ccvaluevector(JSContext* cx, jsval v, cocos2d::ValueVector* ret)
{
    JS::RootedObject jsArr(cx);
    JS::RootedValue dummy(cx, v);
    bool ok = v.isObject() && JS_ValueToObject( cx, dummy, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);

    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            if (value.isObject())
            {
                JSObject* jsobj = value.toObjectOrNull();
                CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
                JS::HandleObject jsobjHandle(JS::HandleObject::fromMarkedLocation(&jsobj));
                if (!JS_IsArrayObject(cx, jsobjHandle))
                {
                    // It's a normal js object.
                    ValueMap dictVal;
                    ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                    if (ok)
                    {
                        ret->push_back(cocos2d::Value(dictVal));
                    }
                }
                else {
                    // It's a js array object.
                    ValueVector arrVal;
                    ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                    if (ok)
                    {
                        ret->push_back(cocos2d::Value(arrVal));
                    }
                }
            }
            else if (value.isString())
            {
                JSStringWrapper valueWapper(value.toString(), cx);
                ret->push_back(cocos2d::Value(valueWapper.get()));
            }
            else if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->push_back(cocos2d::Value(number));
                }
            }
            else if (value.isBoolean())
            {
                bool boolVal = JS::ToBoolean(value);
                ret->push_back(cocos2d::Value(boolVal));
            }
            else
            {
                CCASSERT(false, "not supported type");
            }
        }
    }

    return true;
}

bool jsval_to_ssize( JSContext *cx, jsval vp, ssize_t* size)
{
    bool ret = false;
    int32_t sizeInt32 = 0;
    ret = jsval_to_int32(cx, vp, &sizeInt32);
    *size = sizeInt32;
    return ret;
}

bool jsval_to_std_vector_string( JSContext *cx, jsval vp, std::vector<std::string>* ret)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, vp);
    bool ok = vp.isObject() && JS_ValueToObject( cx, dummy, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isString())
            {
                JSStringWrapper valueWapper(value.toString(), cx);
                ret->push_back(valueWapper.get());
            }
            else
            {
                JS_ReportError(cx, "not supported type in array");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_std_vector_int( JSContext *cx, jsval vp, std::vector<int>* ret)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, vp);
    bool ok = vp.isObject() && JS_ValueToObject( cx, dummy, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->push_back(static_cast<int>(number));
                }
            }
            else
            {
                JS_ReportError(cx, "not supported type in array");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_matrix(JSContext *cx, jsval vp, cocos2d::Mat4* ret)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, vp);
    bool ok = vp.isObject() && JS_ValueToObject( cx, dummy, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an matrix");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    
    if (len != 16)
    {
        JS_ReportError(cx, "array length error: %d, was expecting 16", len);
    }
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->m[i] = static_cast<float>(number);
                }
            }
            else
            {
                JS_ReportError(cx, "not supported type in matrix");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_vector2(JSContext *cx, jsval vp, cocos2d::Vec2* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue dummy(cx, vp);
    double x, y;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return true;
}

bool jsval_to_vector3(JSContext *cx, jsval vp, cocos2d::Vec3* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    JS::RootedValue dummy(cx, vp);
    double x, y, z;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jsz, &z);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    ret->z = (float)z;
    return true;
}

bool jsval_to_blendfunc(JSContext *cx, jsval vp, cocos2d::BlendFunc* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jssrc(cx);
    JS::RootedValue jsdst(cx);
    JS::RootedValue dummy(cx, vp);
    double src, dst;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "src", &jssrc) &&
    JS_GetProperty(cx, tmp, "dst", &jsdst) &&
    JS::ToNumber(cx, jssrc, &src) &&
    JS::ToNumber(cx, jsdst, &dst);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->src = (unsigned int)src;
    ret->dst = (unsigned int)dst;
    return true;
    return true;
}

// native --> jsval

jsval ccarray_to_jsval(JSContext* cx, __Array *arr)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    JS::HandleObject jsretArrHandle(JS::HandleObject::fromMarkedLocation(&jsretArr));
    Ref* obj;
    int i = 0;
    CCARRAY_FOREACH(arr, obj)
    {
        JS::RootedValue arrElement(cx);
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Ref>(cx, obj);
        if (jsproxy) {
            arrElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        else {
            __String* strVal = NULL;
            __Dictionary* dictVal = NULL;
            __Array* arrVal = NULL;
            __Double* doubleVal = NULL;
            __Bool* boolVal = NULL;
            __Float* floatVal = NULL;
            __Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::__String *>(obj))) {
                arrElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<cocos2d::__Dictionary*>(obj))) {
                arrElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<cocos2d::__Array*>(obj))) {
                arrElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
                arrElement = INT_TO_JSVAL(intVal->getValue());
            }  else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
                arrElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? true : false);
            } else {
                CCASSERT(false, "the type isn't suppored.");
            }
        }
        JS::HandleValue arrElementHandle(arrElement);
        if (!JS_SetElement(cx, jsretArrHandle, i, arrElementHandle)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ccdictionary_to_jsval(JSContext* cx, __Dictionary* dict)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    JS::HandleObject jsRetHandle(JS::HandleObject::fromMarkedLocation(&jsRet));
    DictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        JS::RootedValue dictElement(cx);
        Ref* obj = pElement->getObject();
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Ref>(cx, obj);
        if (jsproxy) {
            dictElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        else {
            __String* strVal = NULL;
            __Dictionary* dictVal = NULL;
            __Array* arrVal = NULL;
            __Double* doubleVal = NULL;
            __Bool* boolVal = NULL;
            __Float* floatVal = NULL;
            __Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::__String *>(obj))) {
                dictElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<__Dictionary*>(obj))) {
                dictElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<__Array*>(obj))) {
                dictElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
                dictElement = INT_TO_JSVAL(intVal->getValue());
            } else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
                dictElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? true : false);
            } else {
                CCASSERT(false, "the type isn't suppored.");
            }
        }
        const char* key = pElement->getStrKey();
        if (key && strlen(key) > 0)
        {
            JS_SetProperty(cx, jsRetHandle, key, dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

bool jsval_to_ccdictionary(JSContext* cx, jsval v, __Dictionary** ret)
{
    if (v.isNull() || v.isUndefined())
    {
        *ret = NULL;
        return true;
    }
    
    JSObject* tmp = v.toObjectOrNull();
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccdictionary: the jsval is not an object.");
        return false;
    }
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JSObject* it = JS_NewPropertyIterator(cx, tmpHandle);
    JS::HandleObject itHandle(JS::HandleObject::fromMarkedLocation(&it));
    __Dictionary* dict = NULL;
    
    while (true)
    {
        jsid idp;
        jsval key;
        JS::HandleId idpHandle(JS::HandleId::fromMarkedLocation(&idp));
        JS::MutableHandleValue keyHandle(JS::MutableHandleValue::fromMarkedLocation(&key));
        if (!JS_NextProperty(cx, itHandle, &idp) || !JS_IdToValue(cx, idp, keyHandle)) {
            return false; // error
        }
        
        if (key == JSVAL_VOID) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        if (!dict) {
            dict = __Dictionary::create();
        }
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmpHandle, idpHandle, &value);
        if (value.isObject())
        {
            js_proxy_t *proxy;
            tmp = value.toObjectOrNull();
            proxy = jsb_get_js_proxy(tmp);
            cocos2d::Ref* cobj = (cocos2d::Ref *)(proxy ? proxy->ptr : NULL);
            // Don't test it.
            //TEST_NATIVE_OBJECT(cx, cobj)
            if (cobj) {
                // It's a native <-> js glue object.
                dict->setObject(cobj, keyWrapper.get());
            }
            else if (!JS_IsArrayObject(cx, tmpHandle)){
                // It's a normal js object.
                __Dictionary* dictVal = NULL;
                bool ok = jsval_to_ccdictionary(cx, value, &dictVal);
                if (ok) {
                    dict->setObject(dictVal, keyWrapper.get());
                }
            }
            else {
                // It's a js array object.
                __Array* arrVal = NULL;
                bool ok = jsval_to_ccarray(cx, value, &arrVal);
                if (ok) {
                    dict->setObject(arrVal, keyWrapper.get());
                }
            }
        }
        else if (value.isString()) {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict->setObject(String::create(valueWapper.get()), keyWrapper.get());
            //            CCLOG("iterate object: key = %s, value = %s", keyWrapper.get().c_str(), valueWapper.get().c_str());
        }
        else if (value.isNumber()) {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict->setObject(Double::create(number), keyWrapper.get());
                //                CCLOG("iterate object: key = %s, value = %lf", keyWrapper.get().c_str(), number);
            }
        }
        else if (value.isBoolean()) {
            bool boolVal = JS::ToBoolean(value);
            dict->setObject(Bool::create(boolVal), keyWrapper.get());
            // CCLOG("iterate object: key = %s, value = %d", keyWrapper.get().c_str(), boolVal);
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    *ret = dict;
    return true;
}

bool jsval_to_ccaffinetransform(JSContext* cx, jsval v, AffineTransform* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsa(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsc(cx);
    JS::RootedValue jsd(cx);
    JS::RootedValue jstx(cx);
    JS::RootedValue jsty(cx);
    JS::RootedValue dummy(cx, v);
    double a, b, c, d, tx, ty;
    bool ok = JS_ValueToObject(cx, dummy, &tmp) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "c", &jsc) &&
    JS_GetProperty(cx, tmp, "d", &jsd) &&
    JS_GetProperty(cx, tmp, "tx", &jstx) &&
    JS_GetProperty(cx, tmp, "ty", &jsty) &&
    JS::ToNumber(cx, jsa, &a) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsc, &c) &&
    JS::ToNumber(cx, jsd, &d) &&
    JS::ToNumber(cx, jstx, &tx) &&
    JS::ToNumber(cx, jsty, &ty);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *ret = AffineTransformMake(a, b, c, d, tx, ty);
    return true;
}

// From native type to jsval
jsval int32_to_jsval( JSContext *cx, int32_t number )
{
    return INT_TO_JSVAL(number);
}

jsval uint32_to_jsval( JSContext *cx, uint32_t number )
{
    return UINT_TO_JSVAL(number);
}

jsval ushort_to_jsval( JSContext *cx, unsigned short number )
{
    return UINT_TO_JSVAL(number);
}

jsval std_string_to_jsval(JSContext* cx, const std::string& v)
{
    return c_string_to_jsval(cx, v.c_str(), v.size());
}

jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length /* = -1 */)
{
    if (v == NULL)
    {
        return JSVAL_NULL;
    }
    if (length == -1)
    {
        length = strlen(v);
    }
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    if (0 == length)
    {
        auto emptyStr = JS_NewStringCopyZ(cx, "");
        return STRING_TO_JSVAL(emptyStr);
    }
    
    jsval ret = JSVAL_NULL;
    int utf16_size = 0;
    jschar* strUTF16 = (jschar*)cc_utf8_to_utf16(v, (int)length, &utf16_size);
    
    if (strUTF16 && utf16_size > 0) {
        JSString* str = JS_NewUCStringCopyN(cx, strUTF16, utf16_size);
        if (str) {
            ret = STRING_TO_JSVAL(str);
        }
        delete[] strUTF16;
    }
    return ret;
}

jsval ccpoint_to_jsval(JSContext* cx, const Point& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccacceleration_to_jsval(JSContext* cx, const Acceleration& v)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "z", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "timestamp", v.timestamp, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccrect_to_jsval(JSContext* cx, const Rect& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.origin.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.origin.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "width", v.size.width, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "height", v.size.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccsize_to_jsval(JSContext* cx, const Size& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "width", v.width, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "height", v.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4b_to_jsval(JSContext* cx, const Color4B& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "r", v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "g", v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "a", v.a, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4f_to_jsval(JSContext* cx, const Color4F& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "r", (int)(v.r * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "g", (int)(v.g * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", (int)(v.b * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "a", (int)(v.a * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor3b_to_jsval(JSContext* cx, const Color3B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "r", v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "g", v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccaffinetransform_to_jsval(JSContext* cx, const AffineTransform& t)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "a", t.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", t.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "c", t.c, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "d", t.d, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "tx", t.tx, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "ty", t.ty, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval FontDefinition_to_jsval(JSContext* cx, const FontDefinition& t)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = true;
    
    JS::Value fontName(std_string_to_jsval(cx, t._fontName));
    JS::HandleValue fontNameHandle(JS::HandleValue::fromMarkedLocation(&fontName));
    ok &= JS_DefineProperty(cx, tmpHandle, "fontName", fontNameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "fontSize", t._fontSize, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "textAlign", (int32_t)t._alignment, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "verticalAlign", (int32_t)t._vertAlignment, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS::Value fontFillColor(cccolor3b_to_jsval(cx, t._fontFillColor));
    JS::HandleValue fontFillColorHandle(JS::HandleValue::fromMarkedLocation(&fontFillColor));
    ok &= JS_DefineProperty(cx, tmpHandle, "fillStyle", fontFillColorHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "boundingWidth", t._dimensions.width, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "boundingHeight", t._dimensions.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Shadow
    JS::Value shadowEnabled;
    shadowEnabled.setBoolean(t._shadow._shadowEnabled);
    JS::HandleValue shadowEnabledHandle(JS::HandleValue::fromMarkedLocation(&shadowEnabled));
    ok &= JS_DefineProperty(cx, tmpHandle, "shadowEnabled", shadowEnabledHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "shadowOffsetX", t._shadow._shadowOffset.width, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "shadowOffsetY", t._shadow._shadowOffset.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "shadowBlur", t._shadow._shadowBlur, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "shadowOpacity", t._shadow._shadowOpacity, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Stroke
    JS::Value strokeEnabled;
    strokeEnabled.setBoolean(t._stroke._strokeEnabled);
    JS::HandleValue strokeEnabledHandle(JS::HandleValue::fromMarkedLocation(&strokeEnabled));
    ok &= JS_DefineProperty(cx, tmpHandle, "strokeEnabled", strokeEnabledHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS::Value strokeColor(cccolor3b_to_jsval(cx, t._stroke._strokeColor));
    JS::HandleValue strokeColorHandle(JS::HandleValue::fromMarkedLocation(&strokeColor));
    ok &= JS_DefineProperty(cx, tmpHandle, "strokeStyle", strokeColorHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmpHandle, "lineWidth", t._stroke._strokeSize, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

bool jsval_to_FontDefinition( JSContext *cx, jsval vp, FontDefinition *out )
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue dummy(cx, vp);
    if (!JS_ValueToObject( cx, dummy, &jsobj ) )
        return false;
	
    JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
    // defaul values
    const char *            defautlFontName         = "Arial";
    const int               defaultFontSize         = 32;
    TextHAlignment         defaultTextAlignment    = TextHAlignment::LEFT;
    TextVAlignment defaultTextVAlignment   = TextVAlignment::TOP;
    
    // by default shadow and stroke are off
    out->_shadow._shadowEnabled = false;
    out->_stroke._strokeEnabled = false;
    
    // white text by default
    out->_fontFillColor = Color3B::WHITE;
    
    // font name
    JS::RootedValue jsr(cx);
    JS_GetProperty(cx, jsobj, "fontName", &jsr);
    JS::ToString(cx, jsr);
    JSStringWrapper wrapper(jsr);
    const char* fontName = wrapper.get();
    
    if (fontName && strlen(fontName) > 0)
    {
        out->_fontName  = fontName;
    }
    else
    {
        out->_fontName  = defautlFontName;
    }
    
    // font size
    bool hasProperty, hasSecondProp;
    JS_HasProperty(cx, jsobj, "fontSize", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontSize", &jsr);
        double fontSize = 0.0;
        JS::ToNumber(cx, jsr, &fontSize);
        out->_fontSize  = fontSize;
    }
    else
    {
        out->_fontSize  = defaultFontSize;
    }
    
    // font alignment horizontal
    JS_HasProperty(cx, jsobj, "textAlign", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "textAlign", &jsr);
        double fontAlign = 0.0;
        JS::ToNumber(cx, jsr, &fontAlign);
        out->_alignment = (TextHAlignment)(int)fontAlign;
    }
    else
    {
        out->_alignment  = defaultTextAlignment;
    }
    
    // font alignment vertical
    JS_HasProperty(cx, jsobj, "verticalAlign", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "verticalAlign", &jsr);
        double fontAlign = 0.0;
        JS::ToNumber(cx, jsr, &fontAlign);
        out->_vertAlignment = (TextVAlignment)(int)fontAlign;
    }
    else
    {
        out->_vertAlignment  = defaultTextVAlignment;
    }
    
    // font fill color
    JS_HasProperty(cx, jsobj, "fillStyle", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fillStyle", &jsr);
        
        JS::RootedObject jsobjColor(cx);
        JS::RootedValue dummy(cx, jsr);
        if (!JS_ValueToObject( cx, dummy, &jsobjColor ) )
            return false;
        
        out->_fontFillColor = getColorFromJSObject(cx, jsobjColor);
    }
    
    // font rendering box dimensions
    JS_HasProperty(cx, jsobj, "boundingWidth", &hasProperty);
    JS_HasProperty(cx, jsobj, "boundingHeight", &hasSecondProp);
    if ( hasProperty && hasSecondProp )
    {
        JS_GetProperty(cx, jsobj, "boundingWidth", &jsr);
        double boundingW = 0.0;
        JS::ToNumber(cx, jsr, &boundingW);
        
        JS_GetProperty(cx, jsobj, "boundingHeight", &jsr);
        double boundingH = 0.0;
        JS::ToNumber(cx, jsr, &boundingH);
        
        Size dimension;
        dimension.width = boundingW;
        dimension.height = boundingH;
        out->_dimensions = dimension;
    }
    
    // shadow
    JS_HasProperty(cx, jsobj, "shadowEnabled", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "shadowEnabled", &jsr);
        out->_shadow._shadowEnabled  = ToBoolean(jsr);
        
        if ( out->_shadow._shadowEnabled )
        {
            // default shadow values
            out->_shadow._shadowOffset  = Size(5, 5);
            out->_shadow._shadowBlur    = 1;
            out->_shadow._shadowOpacity = 1;
            
            // shado offset
            JS_HasProperty(cx, jsobj, "shadowOffsetX", &hasProperty);
            JS_HasProperty(cx, jsobj, "shadowOffsetY", &hasSecondProp);
            if ( hasProperty && hasSecondProp )
            {
                JS_GetProperty(cx, jsobj, "shadowOffsetX", &jsr);
                double offx = 0.0;
                JS::ToNumber(cx, jsr, &offx);
                
                JS_GetProperty(cx, jsobj, "shadowOffsetY", &jsr);
                double offy = 0.0;
                JS::ToNumber(cx, jsr, &offy);
                
                Size offset;
                offset.width = offx;
                offset.height = offy;
                out->_shadow._shadowOffset = offset;
            }
            
            // shadow blur
            JS_HasProperty(cx, jsobj, "shadowBlur", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowBlur", &jsr);
                double shadowBlur = 0.0;
                JS::ToNumber(cx, jsr, &shadowBlur);
                out->_shadow._shadowBlur = shadowBlur;
            }
            
            // shadow intensity
            JS_HasProperty(cx, jsobj, "shadowOpacity", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowOpacity", &jsr);
                double shadowOpacity = 0.0;
                JS::ToNumber(cx, jsr, &shadowOpacity);
                out->_shadow._shadowOpacity = shadowOpacity;
            }
        }
    }
    
    // stroke
    JS_HasProperty(cx, jsobj, "strokeEnabled", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "strokeEnabled", &jsr);
        out->_stroke._strokeEnabled  = ToBoolean(jsr);
        
        if ( out->_stroke._strokeEnabled )
        {
            // default stroke values
            out->_stroke._strokeSize  = 1;
            out->_stroke._strokeColor = Color3B::BLUE;
            
            // stroke color
            JS_HasProperty(cx, jsobj, "strokeStyle", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "strokeStyle", &jsr);
                
                JS::RootedObject jsobjStrokeColor(cx);
                if (!JS_ValueToObject( cx, jsr, &jsobjStrokeColor ) )
                    return false;
                out->_stroke._strokeColor = getColorFromJSObject(cx, jsobjStrokeColor);
            }
            
            // stroke size
            JS_HasProperty(cx, jsobj, "lineWidth", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "lineWidth", &jsr);
                double strokeSize = 0.0;
                JS::ToNumber(cx, jsr, &strokeSize);
                out->_stroke._strokeSize = strokeSize;
            }
        }
    }
    
    // we are done here
	return true;
}

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

bool jsval_to_CCPoint( JSContext *cx, jsval vp, Point *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JS::RootedObject jsobj(cx);
	JS::RootedValue dummy(cx, vp);
	if( ! JS_ValueToObject( cx, dummy, &jsobj ) )
		return false;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
	JS::RootedValue valx(cx);
	JS::RootedValue valy(cx);
	bool ok = true;
	ok &= JS_GetProperty(cx, jsobj, "x", &valx);
	ok &= JS_GetProperty(cx, jsobj, "y", &valy);
    
	if( ! ok )
		return false;
	
	double x, y;
	ok &= JS::ToNumber(cx, valx, &x);
	ok &= JS::ToNumber(cx, valy, &y);
	
	if( ! ok )
		return false;
	
	ret->x = x;
	ret->y = y;
    
	return true;
    
#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return false;
	
	JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
	
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");
	
	*ret = *(Point*)JS_GetArrayBufferViewData( tmp_arg, cx );
	
	return true;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


bool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JS::RootedObject jsobj(cx);
	JS::RootedValue dummy(cx, vp);
	if( ! JS_ValueToObject( cx, dummy, &jsobj ) )
		return false;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
    JS::RootedValue valx(cx);
    JS::RootedValue valy(cx);
	bool ok = true;
	ok &= JS_GetProperty(cx, jsobj, "x", &valx);
	ok &= JS_GetProperty(cx, jsobj, "y", &valy);
    
	if( ! ok )
		return false;
	
	double x, y;
	ok &= JS::ToNumber(cx, valx, &x);
	ok &= JS::ToNumber(cx, valy, &y);
	
	if( ! ok )
		return false;
	
	ret->x = x;
	ret->y = y;
    
	return true;
    
#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return false;
	
	JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
	
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");
	
	*ret = *(cpVect*)JS_GetArrayBufferViewData( tmp_arg, cx );
	
	return true;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


jsval CGPoint_to_jsval( JSContext *cx, cpVect p)
{
	
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *object = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
	if (!object)
		return JSVAL_VOID;
	JS::HandleObject objectHandle(JS::HandleObject::fromMarkedLocation(&object));
    
	if (!JS_DefineProperty(cx, objectHandle, "x", p.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, objectHandle, "y", p.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JSVAL_VOID;
	
	return OBJECT_TO_JSVAL(object);
    
#else // JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
	
#ifdef __LP64__
	JSObject *typedArray = JS_NewFloat64Array( cx, 2 );
#else
	JSObject *typedArray = JS_NewFloat32Array( cx, 2 );
#endif
    
	cpVect *buffer = (cpVect*)JS_GetArrayBufferViewData(typedArray, cx );
	*buffer = p;
	return OBJECT_TO_JSVAL(typedArray);
#endif // ! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

jsval ccvalue_to_jsval(JSContext* cx, const cocos2d::Value& v)
{
    jsval ret = JSVAL_NULL;
    const cocos2d::Value& obj = v;
    
    switch (obj.getType())
    {
        case cocos2d::Value::Type::BOOLEAN:
            ret = BOOLEAN_TO_JSVAL(obj.asBool());
            break;
        case cocos2d::Value::Type::FLOAT:
        case cocos2d::Value::Type::DOUBLE:
            ret = DOUBLE_TO_JSVAL(obj.asDouble());
            break;
        case cocos2d::Value::Type::INTEGER:
            ret = INT_TO_JSVAL(obj.asInt());
            break;
        case cocos2d::Value::Type::STRING:
            ret = std_string_to_jsval(cx, obj.asString());
            break;
        case cocos2d::Value::Type::VECTOR:
            ret = ccvaluevector_to_jsval(cx, obj.asValueVector());
            break;
        case cocos2d::Value::Type::MAP:
            ret = ccvaluemap_to_jsval(cx, obj.asValueMap());
            break;
        case cocos2d::Value::Type::INT_KEY_MAP:
            ret = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
            break;
        default:
            break;
    }
    
    return ret;
}

jsval ccvaluemap_to_jsval(JSContext* cx, const cocos2d::ValueMap& v)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    JS::HandleObject jsRetHandle(JS::HandleObject::fromMarkedLocation(&jsRet));
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue dictElement(cx);

        std::string key = iter->first;
        const cocos2d::Value& obj = iter->second;
        
        switch (obj.getType())
        {
            case cocos2d::Value::Type::BOOLEAN:
                dictElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case cocos2d::Value::Type::FLOAT:
            case cocos2d::Value::Type::DOUBLE:
                dictElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case cocos2d::Value::Type::INTEGER:
                dictElement = INT_TO_JSVAL(obj.asInt());
                break;
            case cocos2d::Value::Type::STRING:
                dictElement = std_string_to_jsval(cx, obj.asString());
                break;
            case cocos2d::Value::Type::VECTOR:
                dictElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case cocos2d::Value::Type::MAP:
                dictElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case cocos2d::Value::Type::INT_KEY_MAP:
                dictElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRetHandle, key.c_str(), dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

jsval ccvaluemapintkey_to_jsval(JSContext* cx, const cocos2d::ValueMapIntKey& v)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    JS::HandleObject jsRetHandle(JS::HandleObject::fromMarkedLocation(&jsRet));
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue dictElement(cx);
        std::stringstream keyss;
        keyss << iter->first;
        std::string key = keyss.str();
        
        const cocos2d::Value& obj = iter->second;
        
        switch (obj.getType())
        {
            case cocos2d::Value::Type::BOOLEAN:
                dictElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case cocos2d::Value::Type::FLOAT:
            case cocos2d::Value::Type::DOUBLE:
                dictElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case cocos2d::Value::Type::INTEGER:
                dictElement = INT_TO_JSVAL(obj.asInt());
                break;
            case cocos2d::Value::Type::STRING:
                dictElement = std_string_to_jsval(cx, obj.asString());
                break;
            case cocos2d::Value::Type::VECTOR:
                dictElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case cocos2d::Value::Type::MAP:
                dictElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case cocos2d::Value::Type::INT_KEY_MAP:
                dictElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRetHandle, key.c_str(), dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

jsval ccvaluevector_to_jsval(JSContext* cx, const cocos2d::ValueVector& v)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    JS::HandleObject jsretArrHandle(JS::HandleObject::fromMarkedLocation(&jsretArr));
    int i = 0;
    for (const auto& obj : v)
    {
        JS::RootedValue arrElement(cx);
        
        switch (obj.getType())
        {
            case cocos2d::Value::Type::BOOLEAN:
                arrElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case cocos2d::Value::Type::FLOAT:
            case cocos2d::Value::Type::DOUBLE:
                arrElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case cocos2d::Value::Type::INTEGER:
                arrElement = INT_TO_JSVAL(obj.asInt());
                break;
            case cocos2d::Value::Type::STRING:
                arrElement = std_string_to_jsval(cx, obj.asString());
                break;
            case cocos2d::Value::Type::VECTOR:
                arrElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case cocos2d::Value::Type::MAP:
                arrElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case cocos2d::Value::Type::INT_KEY_MAP:
                arrElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }
        JS::HandleValue arrElementHandle(arrElement);
        if (!JS_SetElement(cx, jsretArrHandle, i, arrElementHandle)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ssize_to_jsval(JSContext *cx, ssize_t v)
{
    CCASSERT(v < INT_MAX, "The size should not bigger than 32 bit (int32_t).");
    return int32_to_jsval(cx, static_cast<int>(v));
}

jsval std_vector_string_to_jsval( JSContext *cx, const std::vector<std::string>& v)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    JS::HandleObject jsretArrHandle(JS::HandleObject::fromMarkedLocation(&jsretArr));
    int i = 0;
    for (const std::string obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = std_string_to_jsval(cx, obj);
        JS::HandleValue arrElementHandle(arrElement);
        if (!JS_SetElement(cx, jsretArrHandle, i, arrElementHandle)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval std_vector_int_to_jsval( JSContext *cx, const std::vector<int>& v)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    JS::HandleObject jsretArrHandle(JS::HandleObject::fromMarkedLocation(&jsretArr));
    
    int i = 0;
    for (const int obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = int32_to_jsval(cx, obj);
        JS::HandleValue arrElementHandle(arrElement);
        if (!JS_SetElement(cx, jsretArrHandle, i, arrElementHandle)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval matrix_to_jsval(JSContext *cx, const cocos2d::Mat4& v)
{
    /*JSObject *jsretArr = JS_NewArrayObject(cx, 0);
    
    for (int i = 0; i < 16; i++) {
        JS::RootedValue arrElement(cx);
        arrElement = DOUBLE_TO_JSVAL(v.m[i]);
        
        if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
    }
    
    return OBJECT_TO_JSVAL(jsretArr);*/
    
    //convert Mat4 to AffineTransform to be compatible with html5
    cocos2d::AffineTransform affineTransform;
    cocos2d::GLToCGAffine(v.m, &affineTransform);
    return ccaffinetransform_to_jsval(cx, affineTransform);
}

jsval vector2_to_jsval(JSContext *cx, const cocos2d::Vec2& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval vector3_to_jsval(JSContext *cx, const cocos2d::Vec3& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "z", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval blendfunc_to_jsval(JSContext *cx, const cocos2d::BlendFunc& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    bool ok = JS_DefineProperty(cx, tmpHandle, "src", v.src, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "dst", v.dst, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}
