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

#include "jsapi.h"
#include "jsfriendapi.h"
#include "extensions/cocos-ext.h"
#include "js_bindings_config.h"
#ifdef JSB_INCLUDE_CHIPMUNK

#include "js_bindings_chipmunk_manual.h"
#include "js_manual_conversions.h"

USING_NS_CC_EXT;
using namespace JS;

// Function declarations
void static freeSpaceChildren(cpSpace *space);

extern CC_BINDING_DLL std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    cobj->autorelease();
    js_type_class_t *p;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    p = typeMapIter->second;
    CCASSERT(p, "The value is null.");
    
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    AddObjectRoot(cx, &pp->obj);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return true;
}

#pragma mark - convertions

/*
 * PhysicsSprite
 */
#pragma mark - PhysicsSprite

JSClass* JSPROXY_CCPhysicsSprite_class = NULL;
JSObject* JSPROXY_CCPhysicsSprite_object = NULL;
// Constructor

// Destructor
void JSPROXY_CCPhysicsSprite_finalize(JSFreeOp *fop, JSObject *obj)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (PhysicsSprite)", obj);
}

// Arguments:
// Ret value: BOOL (b)
bool JSPROXY_CCPhysicsSprite_isDirty(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
    if (real->isDirty()) {
        JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    }
	else JS_SET_RVAL(cx, vp, JSVAL_FALSE);
	return true;
}

// Arguments:
// Ret value: cpBody* (N/A)
bool JSPROXY_CCPhysicsSprite_getCPBody(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
	cpBody* ret_val;
    
	ret_val = real->getCPBody();
	jsval ret_jsval = c_class_to_jsval( cx, ret_val, JSB_cpBody_object, JSB_cpBody_class, "cpBody" );
	JS_SET_RVAL(cx, vp, ret_jsval);
    
	return true;
}

// Arguments:
// Ret value: BOOL (b)
bool JSPROXY_CCPhysicsSprite_ignoreBodyRotation(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	bool ret_val;
    
	ret_val = real->isIgnoreBodyRotation();
	JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret_val));
	return true;
}

// Arguments: cpBody*
// Ret value: void (None)
bool JSPROXY_CCPhysicsSprite_setCPBody_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
    
    cpBody* arg0;
    
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return false;
    
	real->setCPBody((cpBody*)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Arguments: BOOL
// Ret value: void (None)
bool JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	bool arg0 = JS::ToBoolean( JS::RootedValue(cx, *argvp++) );
    
	real->setIgnoreBodyRotation((bool)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

/*
 * PhysicsDebugNode
 */
//#pragma mark - PhysicsDebugNode

JSClass* JSB_CCPhysicsDebugNode_class = NULL;
JSObject* JSB_CCPhysicsDebugNode_object = NULL;
extern JSObject *js_cocos2dx_CCDrawNode_prototype;

// Constructor

// Destructor
void JSB_CCPhysicsDebugNode_finalize(JSFreeOp *fop, JSObject *obj)
{
	CCLOGINFO("jsbindings: finalizing JS object %p (PhysicsDebugNode)", obj);
}

// Arguments: cpSpace*
// Ret value: PhysicsDebugNode* (o)
bool JSB_CCPhysicsDebugNode_debugNodeForCPSpace__static(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

	PhysicsDebugNode* ret = PhysicsDebugNode::create(arg0);
    jsval jsret;
    do {
        if (ret) {
            TypeTest<PhysicsDebugNode> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            
            JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
            JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p = jsb_new_proxy(ret, obj);
            AddNamedObjectRoot(cx, &p->obj, "CCDebugNode");
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
    JS_SET_RVAL(cx, vp, jsret);

	return true;
}

// Arguments: cpSpace*
// Ret value: void (None)
bool JSB_CCPhysicsDebugNode_setSpace_(JSContext *cx, uint32_t argc, jsval *vp) {

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    PhysicsDebugNode* real = (PhysicsDebugNode *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

	JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

	real->setSpace(arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Arguments: 
// Ret value: cpSpace* (N/A)
bool JSB_CCPhysicsDebugNode_space(JSContext *cx, uint32_t argc, jsval *vp) {

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    PhysicsDebugNode* real = (PhysicsDebugNode *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)
	JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
	cpSpace* ret_val;

	ret_val = real->getSpace();

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
    
	return true;
}

bool JSB_CCPhysicsDebugNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    PhysicsDebugNode* cobj = new (std::nothrow) PhysicsDebugNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<PhysicsDebugNode> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
    JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "PhysicsDebugNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}

void JSB_CCPhysicsDebugNode_createClass(JSContext *cx, JSObject* globalObj, const char* name )
{
	JSB_CCPhysicsDebugNode_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSB_CCPhysicsDebugNode_class->name = name;
	JSB_CCPhysicsDebugNode_class->addProperty = JS_PropertyStub;
	JSB_CCPhysicsDebugNode_class->delProperty = JS_DeletePropertyStub;
	JSB_CCPhysicsDebugNode_class->getProperty = JS_PropertyStub;
	JSB_CCPhysicsDebugNode_class->setProperty = JS_StrictPropertyStub;
	JSB_CCPhysicsDebugNode_class->enumerate = JS_EnumerateStub;
	JSB_CCPhysicsDebugNode_class->resolve = JS_ResolveStub;
	JSB_CCPhysicsDebugNode_class->convert = JS_ConvertStub;
	JSB_CCPhysicsDebugNode_class->finalize = JSB_CCPhysicsDebugNode_finalize;
	JSB_CCPhysicsDebugNode_class->flags = 0;

	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("_setSpace", JSB_CCPhysicsDebugNode_setSpace_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("getSpace", JSB_CCPhysicsDebugNode_space, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FN("_create", JSB_CCPhysicsDebugNode_debugNodeForCPSpace__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FS_END
	};

    TypeTest<cocos2d::DrawNode> t1;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t1.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");

    JSB_CCPhysicsDebugNode_object = JS_InitClass(cx, globalObj, typeClass->proto, JSB_CCPhysicsDebugNode_class, JSB_CCPhysicsDebugNode_constructor, 0,properties,funcs,NULL,st_funcs);

    TypeTest<PhysicsDebugNode> t;
    js_type_class_t *p;
    typeName = t.s_name();
    
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = JSB_CCPhysicsDebugNode_class;
        p->proto = JSB_CCPhysicsDebugNode_object;
        p->parentProto = typeClass->proto;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

// Arguments: NSString*, CGRect
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static(JSContext *cx, uint32_t argc, jsval *vp) {

    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		cocos2d::Rect arg1;
		ok &= jsval_to_ccrect(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        PhysicsSprite* ret = PhysicsSprite::create(arg0, arg1);

		jsval jsret;
		do {
			if (ret) {
                TypeTest<PhysicsSprite> t;
                js_type_class_t *typeClass = nullptr;
                std::string typeName = t.s_name();
                auto typeMapIter = _js_global_type_map.find(typeName);
                CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
                typeClass = typeMapIter->second;
                CCASSERT(typeClass, "The value is null.");
                
                JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
                JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
                jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p = jsb_new_proxy(ret, obj);
                AddNamedObjectRoot(cx, &p->obj, "CCPhysicsSprite");
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
		PhysicsSprite* ret = PhysicsSprite::create(arg0);

		jsval jsret;
		do {
			if (ret) {
				TypeTest<PhysicsSprite> t;
                js_type_class_t *typeClass = nullptr;
                std::string typeName = t.s_name();
                auto typeMapIter = _js_global_type_map.find(typeName);
                CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
                typeClass = typeMapIter->second;
                CCASSERT(typeClass, "The value is null.");
                JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
                JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
                jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p = jsb_new_proxy(ret, obj);
                AddNamedObjectRoot(cx, &p->obj, "CCPhysicsSprite");
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	return false;

}

// Arguments: SpriteFrame*
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	cocos2d::SpriteFrame* arg0;
	if (argc >= 1) {
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = argv[0].toObjectOrNull();
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::SpriteFrame*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, arg0)
		} while (0);
	}
    PhysicsSprite* ret = PhysicsSprite::createWithSpriteFrame(arg0);

	jsval jsret;
	do {
		if (ret) {
            TypeTest<PhysicsSprite> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
            JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p = jsb_new_proxy(ret, obj);
            AddNamedObjectRoot(cx, &p->obj, "CCPhysicsSprite");
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return true;
}

// Arguments: NSString*
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
	const char* arg0;
    std::string arg0_tmp;
	if (argc == 1) {
		ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();

        PhysicsSprite* ret = PhysicsSprite::createWithSpriteFrameName(arg0);

        jsval jsret;
        do {
            if (ret) {
                TypeTest<PhysicsSprite> t;
                js_type_class_t *typeClass = nullptr;
                std::string typeName = t.s_name();
                auto typeMapIter = _js_global_type_map.find(typeName);
                CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
                typeClass = typeMapIter->second;
                CCASSERT(typeClass, "The value is null.");
                JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
                JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
                jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p = jsb_new_proxy(ret, obj);
                AddNamedObjectRoot(cx, &p->obj, "CCPhysicsSprite");
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool JSPROXY_CCPhysicsSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    PhysicsSprite* cobj = new PhysicsSprite();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::extension::PhysicsSprite> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JS::HandleObject protoHandle(JS::HandleObject::fromMarkedLocation(&typeClass->proto));
    JS::HandleObject parentHandle(JS::HandleObject::fromMarkedLocation(&typeClass->parentProto));
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, protoHandle, parentHandle);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::PhysicsSprite");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}

static bool JSPROXY_CCPhysicsSprite_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    PhysicsSprite *nobj = new PhysicsSprite();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::SpriteFrame");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}

void JSPROXY_CCPhysicsSprite_createClass(JSContext *cx, JSObject* globalObj)
{
	JSPROXY_CCPhysicsSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSPROXY_CCPhysicsSprite_class->name = "PhysicsSprite";
	JSPROXY_CCPhysicsSprite_class->addProperty = JS_PropertyStub;
	JSPROXY_CCPhysicsSprite_class->delProperty = JS_DeletePropertyStub;
	JSPROXY_CCPhysicsSprite_class->getProperty = JS_PropertyStub;
	JSPROXY_CCPhysicsSprite_class->setProperty = JS_StrictPropertyStub;
	JSPROXY_CCPhysicsSprite_class->enumerate = JS_EnumerateStub;
	JSPROXY_CCPhysicsSprite_class->resolve = JS_ResolveStub;
	JSPROXY_CCPhysicsSprite_class->convert = JS_ConvertStub;
	JSPROXY_CCPhysicsSprite_class->finalize = JSPROXY_CCPhysicsSprite_finalize;
	JSPROXY_CCPhysicsSprite_class->flags = 0;

	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
        JS_FN("isDirty", JSPROXY_CCPhysicsSprite_isDirty, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("getCPBody", JSPROXY_CCPhysicsSprite_getCPBody, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("getIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_ignoreBodyRotation, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("_setCPBody", JSPROXY_CCPhysicsSprite_setCPBody_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("setIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("ctor", JSPROXY_CCPhysicsSprite_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static, 2, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrame", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrameName", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FS_END
	};

    TypeTest<cocos2d::Sprite> t1;
	js_type_class_t *typeClass = nullptr;
    std::string typeName = t1.s_name();
	auto typeMapIter = _js_global_type_map.find(typeName);
	CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
	typeClass = typeMapIter->second;
	CCASSERT(typeClass, "The value is null.");

	JSPROXY_CCPhysicsSprite_object = JS_InitClass(cx, globalObj, typeClass->proto, JSPROXY_CCPhysicsSprite_class,/* dummy_constructor<PhysicsSprite>*/JSPROXY_CCPhysicsSprite_constructor, 0,properties,funcs,NULL,st_funcs);

    TypeTest<PhysicsSprite> t;
	js_type_class_t *p;
	typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = JSPROXY_CCPhysicsSprite_class;
		p->proto = JSPROXY_CCPhysicsSprite_object;
		p->parentProto = typeClass->proto;
        _js_global_type_map.insert(std::make_pair(typeName, p));
	}
}


void register_CCPhysicsSprite(JSContext *cx, JSObject *obj) {
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS::HandleObject objHandle(JS::HandleObject::fromMarkedLocation(&obj));
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, objHandle, "cc", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;
    JSPROXY_CCPhysicsSprite_createClass(cx, obj);
}

void register_CCPhysicsDebugNode(JSContext *cx, JSObject *obj) {
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS::HandleObject objHandle(JS::HandleObject::fromMarkedLocation(&obj));
    JS_GetProperty(cx, obj, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, objHandle, "cc", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;
    JSB_CCPhysicsDebugNode_createClass(cx, obj, "PhysicsDebugNode");
}

bool jsval_to_cpBB( JSContext *cx, jsval vp, cpBB *ret )
{
    JS::RootedObject jsobj(cx);
	bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, vp), &jsobj );
	JSB_PRECONDITION( ok, "Error converting value to object");
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
	
    JS::RootedValue vall(cx);
    JS::RootedValue valb(cx);
    JS::RootedValue valr(cx);
    JS::RootedValue valt(cx);
	ok = true;
	ok &= JS_GetProperty(cx, jsobj, "l", &vall);
	ok &= JS_GetProperty(cx, jsobj, "b", &valb);
	ok &= JS_GetProperty(cx, jsobj, "r", &valr);
	ok &= JS_GetProperty(cx, jsobj, "t", &valt);
	JSB_PRECONDITION( ok, "Error obtaining point properties");
	
	double l, b, r, t;
	ok &= JS::ToNumber(cx, vall, &l);
	ok &= JS::ToNumber(cx, valb, &b);
	ok &= JS::ToNumber(cx, valr, &r);
	ok &= JS::ToNumber(cx, valt, &t);
	JSB_PRECONDITION( ok, "Error converting value to numbers");
	
	ret->l = l;
	ret->b = b;
	ret->r = r;
	ret->t = t;
	
	return true;
}

jsval cpBB_to_jsval(JSContext *cx, cpBB bb )
{
	JSObject *object = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
	if (!object)
		return JSVAL_VOID;
	JS::HandleObject objectHandle(JS::HandleObject::fromMarkedLocation(&object));
	
	if (!JS_DefineProperty(cx, objectHandle, "l", bb.l, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, objectHandle, "b", bb.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, objectHandle, "r", bb.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, objectHandle, "t", bb.t, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JSVAL_VOID;
	
	return OBJECT_TO_JSVAL(object);
}

// In order to be compatible with Chipmunk-JS API,
// this function expect to receive an array of numbers, and not an array of vects
// OK:  [1,2,  3,4,  5,6]   <- expected
// BAD: [{x:1, y:2}, {x:3,y:4}, {x:5, y:6}]  <- not expected
bool jsval_to_array_of_cpvect( JSContext *cx, jsval vp, cpVect**verts, int *numVerts)
{
	// Parsing sequence
    JS::RootedObject jsobj(cx);
	bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, vp), &jsobj );
	JSB_PRECONDITION( ok, "Error converting value to object");
	
	JSB_PRECONDITION( jsobj && JS_IsArrayObject( cx, jsobj),  "Object must be an array");

	uint32_t len;
	JS_GetArrayLength(cx, jsobj, &len);
	
	JSB_PRECONDITION( len%2==0, "Array lenght should be even");
	
	cpVect *array = (cpVect*)malloc( sizeof(cpVect) * len/2);
	
	for( uint32_t i=0; i< len;i++ ) {
        JS::RootedValue valarg(cx);
		JS_GetElement(cx, jsobj, i, &valarg);

		double value;
		ok = JS::ToNumber(cx, valarg, &value);
		JSB_PRECONDITION( ok, "Error converting value to nsobject");
		
		if(i%2==0)
			array[i/2].x = value;
		else
			array[i/2].y = value;
	}
	
	*numVerts = len/2;
	*verts = array;
	
	return true;
}

#pragma mark - Collision Handler

struct collision_handler {
	cpCollisionType		typeA;
	cpCollisionType		typeB;
	
	JSObject			*begin;
	JSObject			*pre;
	JSObject			*post;
	JSObject			*separate;
	JSObject			*jsthis;
	JSContext			*cx;

	// "owner" of the collision handler
	// Needed when the space goes out of scope, it will remove all the allocated collision handlers for him.
	cpSpace				*space;
	
	unsigned long		hash_key;

	unsigned int		is_oo; // Objected oriented API ?
	UT_hash_handle  hh;
};

// hash
struct collision_handler* collision_handler_hash = NULL;

// helper pair
static unsigned long pair_ints( unsigned long A, unsigned long B )
{
	// order is not important
	unsigned long k1 = MIN(A, B );
	unsigned long k2 = MAX(A, B );
	
	return (k1 + k2) * (k1 + k2 + 1) /2 + k2;
}

static cpBool myCollisionBegin(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
	
	jsval rval;
	bool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, OBJECT_TO_JSVAL(handler->begin), 2, args, &rval);
	JSB_PRECONDITION2(ok, handler->cx, cpFalse, "Error calling collision callback: begin");

	if( rval.isBoolean() ) {
		bool ret = rval.toBoolean();
		return (cpBool)ret;
	}
	return cpTrue;	
}

static cpBool myCollisionPre(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
	
	jsval rval;
	bool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, OBJECT_TO_JSVAL(handler->pre), 2, args, &rval);
	JSB_PRECONDITION2(ok, handler->cx, false, "Error calling collision callback: pre");
	
	if( rval.isBoolean() ) {
		bool ret = rval.toBoolean();
		return (cpBool)ret;
	}
	return cpTrue;	
}

static void myCollisionPost(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
	
	jsval ignore;
	bool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, OBJECT_TO_JSVAL(handler->post), 2, args, &ignore);
	JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Post");
}

static void myCollisionSeparate(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
	
	jsval ignore;
	bool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, OBJECT_TO_JSVAL(handler->separate), 2, args, &ignore);
	JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Separate");}

#pragma mark - cpSpace

#pragma mark constructor / destructor

void JSB_cpSpace_finalize(JSFreeOp *fop, JSObject *jsthis)
{
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	if( proxy ) {
		CCLOGINFO("jsbindings: finalizing JS object %p (cpSpace), handle: %p", jsthis, proxy->handle);
		
		// space
		cpSpace *space = (cpSpace*) proxy->handle;
		
		
		// Remove collision handlers, since the user might have forgotten to manually remove them
		struct collision_handler *current, *tmp;
		HASH_ITER(hh, collision_handler_hash, current, tmp) {
			if( current->space == space ) {

				JSContext *cx = current->cx;

				// unroot it
				if( current->begin ) {
					RemoveObjectRoot(cx, &current->begin);
                }
				if( current->pre )
					RemoveObjectRoot(cx, &current->pre);
				if( current->post )
					RemoveObjectRoot(cx, &current->post);
				if( current->separate )
					RemoveObjectRoot(cx, &current->separate);
				
				HASH_DEL(collision_handler_hash,current);  /* delete; users advances to next */
				free(current);            /* optional- if you want to free  */
			}
		}
		
		// Free Space Children
		freeSpaceChildren(space);
		
		jsb_del_jsobject_for_proxy(space);
		if(proxy->flags == JSB_C_FLAG_CALL_FREE)
			cpSpaceFree(space);
		jsb_del_c_proxy_for_jsobject(jsthis);
	}
}


#pragma mark addCollisionHandler

static
bool __jsb_cpSpace_addCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, cpSpace *space, unsigned int is_oo)
{
	struct collision_handler *handler = (struct collision_handler*) malloc( sizeof(*handler) );

	JSB_PRECONDITION(handler, "Error allocating memory");
	
	bool ok = true;
	
	// args
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeB );
	
	// this is no longer passed, so "this" is going to be "this".
//	ok &= JS_ValueToObject(cx, *argvp++, &handler->jsthis );
	handler->jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	
	handler->begin = !argvp->isNull() ? argvp->toObjectOrNull() : NULL;
	argvp++;
	handler->pre = !argvp->isNull() ? argvp->toObjectOrNull() : NULL;
	argvp++;
	handler->post = !argvp->isNull() ? argvp->toObjectOrNull() : NULL;
	argvp++;
	handler->separate = !argvp->isNull() ? argvp->toObjectOrNull() : NULL;
	argvp++;
	
	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	// Object Oriented API ?
	handler->is_oo = is_oo;
	
	// owner of the collision handler
	handler->space = space;
	
	// Root it
	if( handler->begin )
		AddNamedObjectRoot(cx, &handler->begin, "begin collision_handler");
	if( handler->pre )
		AddNamedObjectRoot(cx, &handler->pre, "pre collision_handler");
	if( handler->post )
		AddNamedObjectRoot(cx, &handler->post, "post collision_handler");
	if( handler->separate )
		AddNamedObjectRoot(cx, &handler->separate, "separate collision_handler");
	
	handler->cx = cx;
	
	cpSpaceAddCollisionHandler(space, handler->typeA, handler->typeB,
							   !handler->begin ? NULL : &myCollisionBegin,
							   !handler->pre ? NULL : &myCollisionPre,
							   !handler->post ? NULL : &myCollisionPost,
							   !handler->separate ? NULL : &myCollisionSeparate,
							   handler );
	
	
	//
	// Already added ? If so, remove it.
	// Then add new entry
	//
	struct collision_handler *hashElement = NULL;
	unsigned long paired_key = pair_ints(handler->typeA, handler->typeB );
	HASH_FIND_INT(collision_handler_hash, &paired_key, hashElement);
    if( hashElement ) {
		HASH_DEL( collision_handler_hash, hashElement );
		free( hashElement );
	}
	
	handler->hash_key = paired_key;
	HASH_ADD_INT( collision_handler_hash, hash_key, handler );
	
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

bool JSB_cpSpaceAddCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==7, cx, false, "Invalid number of arguments");


	jsval *argvp = JS_ARGV(cx,vp);

	// args
	cpSpace *space;
	bool ok = jsval_to_opaque( cx, *argvp++, (void**)&space);
	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	return __jsb_cpSpace_addCollisionHandler(cx, vp, argvp, space, 0);
}

// method
bool JSB_cpSpace_addCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==6, cx, false, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpSpace_addCollisionHandler(cx, vp, JS_ARGV(cx,vp), (cpSpace*)handle, 1);
}

#pragma mark removeCollisionHandler

static
bool __jsb_cpSpace_removeCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, cpSpace *space)
{
	bool ok = true;
	
	cpCollisionType typeA;
	cpCollisionType typeB;
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeB );

	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	cpSpaceRemoveCollisionHandler(space, typeA, typeB );
	
	// Remove it
	struct collision_handler *hashElement = NULL;
	unsigned long key = pair_ints(typeA, typeB );
	HASH_FIND_INT(collision_handler_hash, &key, hashElement);
    if( hashElement ) {
		
		// unroot it
		if( hashElement->begin )
			RemoveObjectRoot(cx, &hashElement->begin);
		if( hashElement->pre )
			RemoveObjectRoot(cx, &hashElement->pre);
		if( hashElement->post )
			RemoveObjectRoot(cx, &hashElement->post);
		if( hashElement->separate )
			RemoveObjectRoot(cx, &hashElement->separate);
		
		HASH_DEL( collision_handler_hash, hashElement );
		free( hashElement );
	}
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Free function
bool JSB_cpSpaceRemoveCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==3, cx, false, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	
	cpSpace* space;
	bool ok = jsval_to_opaque( cx, *argvp++, (void**)&space);
	
	JSB_PRECONDITION(ok, "Error parsing arguments");

	return __jsb_cpSpace_removeCollisionHandler(cx, vp, argvp, space);
}

// method
bool JSB_cpSpace_removeCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpSpace_removeCollisionHandler(cx, vp, JS_ARGV(cx,vp), (cpSpace*)handle);
}

#pragma mark Add functios. Root JSObjects

// Arguments: cpBody*
// Ret value: cpBody*
bool JSB_cpSpace_addBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpBody* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddBody((cpSpace*)arg0 , (cpBody*)arg1  );
	
	// Root it:
	AddNamedObjectRoot(cx, &retproxy->jsobj, "cpBody");
	
	// addBody returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return true;
}

// Arguments: cpConstraint*
// Ret value: cpConstraint*
bool JSB_cpSpace_addConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpConstraint* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	
	// Root it:
	AddNamedObjectRoot(cx, &retproxy->jsobj, "cpConstraint");
	
	// addConstraint returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return true;
}

// Arguments: cpShape*
// Ret value: cpShape*
bool JSB_cpSpace_addShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpShape* arg1;

	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddShape((cpSpace*)arg0 , (cpShape*)arg1  );
	
	// Root it:
	AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape");
	
	// addShape returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return true;
}

// Arguments: cpShape*
// Ret value: cpShape*
bool JSB_cpSpace_addStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpShape* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
	
	// Root it:
	AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape (static)");

	// addStaticShape returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return true;
}

#pragma mark Remove functios. Untoot JSObjects

// Arguments: cpBody*
// Ret value: void
bool JSB_cpSpace_removeBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpBody* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveBody((cpSpace*)arg0 , (cpBody*)arg1  );
	RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Arguments: cpConstraint*
// Ret value: void
bool JSB_cpSpace_removeConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpConstraint* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	RemoveObjectRoot(cx, &retproxy->jsobj);

	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Arguments: cpShape*
// Ret value: void
bool JSB_cpSpace_removeShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpShape* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveShape((cpSpace*)arg0 , (cpShape*)arg1  );
	RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}

// Arguments: cpShape*
// Ret value: void
bool JSB_cpSpace_removeStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpShape* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
	RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}
#pragma mark - Arbiter

#pragma mark getBodies
static
bool __jsb_cpArbiter_getBodies(JSContext *cx, jsval *vp, jsval *argvp, cpArbiter *arbiter, unsigned int is_oo)
{
	cpBody *bodyA;
	cpBody *bodyB;
	cpArbiterGetBodies(arbiter, &bodyA, &bodyB);
	
	JS::RootedValue valA(cx);
	JS::RootedValue valB(cx);
	if( is_oo ) {
		valA = c_class_to_jsval(cx, bodyA, JSB_cpBody_object, JSB_cpBody_class, "cpArbiter");
		valB = c_class_to_jsval(cx, bodyB, JSB_cpBody_object, JSB_cpBody_class, "cpArbiter");
	} else {
		valA = opaque_to_jsval(cx, bodyA);
		valB = opaque_to_jsval(cx, bodyB);		
	}
	
	JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, 2));
	JS::HandleObject jsobjHandle(jsobj);
	JS::HandleValue valAHandle(valA);
	JS::HandleValue valBHandle(valB);
	JS_SetElement(cx, jsobjHandle, 0, valAHandle);
	JS_SetElement(cx, jsobjHandle, 1, valBHandle);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return true;	
}

// Free function
bool JSB_cpArbiterGetBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if( ! jsval_to_opaque( cx, *argvp++, (void**)&arbiter ) )
		return false;

	return __jsb_cpArbiter_getBodies(cx, vp, argvp, arbiter, 0);
}

// Method
bool JSB_cpArbiter_getBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	JSB_PRECONDITION( proxy, "Invalid private object");
	void *handle = proxy->handle;
	
	return __jsb_cpArbiter_getBodies(cx, vp, JS_ARGV(cx,vp), (cpArbiter*)handle, 1);
}

#pragma mark getShapes
static
bool __jsb_cpArbiter_getShapes(JSContext *cx, jsval *vp, jsval *argvp, cpArbiter *arbiter, unsigned int is_oo)
{
	cpShape *shapeA;
	cpShape *shapeB;
	cpArbiterGetShapes(arbiter, &shapeA, &shapeB);

	JS::RootedValue valA(cx);
	JS::RootedValue valB(cx);
	if( is_oo ) {
		valA = c_class_to_jsval(cx, shapeA, JSB_cpShape_object, JSB_cpShape_class, "cpShape");
		valB = c_class_to_jsval(cx, shapeB, JSB_cpShape_object, JSB_cpShape_class, "cpShape");
	} else {
		valA = opaque_to_jsval(cx, shapeA);
		valB = opaque_to_jsval(cx, shapeB);
	}
	
	JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, 2));
	JS::HandleObject jsobjHandle(jsobj);
	JS::HandleValue valAHandle(valA);
	JS::HandleValue valBHandle(valB);
	JS_SetElement(cx, jsobjHandle, 0, valAHandle);
	JS_SetElement(cx, jsobjHandle, 1, valBHandle);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return true;
}

// function
bool JSB_cpArbiterGetShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &arbiter ) )
	   return false;

	return __jsb_cpArbiter_getShapes(cx, vp, argvp, arbiter, 0);
}

// method
bool JSB_cpArbiter_getShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpArbiter_getShapes(cx, vp, JS_ARGV(cx,vp), (cpArbiter*)handle, 1);
}

#pragma mark - Body

#pragma mark constructor

// Manually added to identify static vs dynamic bodies
bool JSB_cpBody_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");
	JS::HandleObject objHandle(JS::HandleObject::fromMarkedLocation(&JSB_cpBody_object));
	JSObject *jsobj = JS_NewObject(cx, JSB_cpBody_class, objHandle, JS::NullPtr());
	JS::CallArgs argvp = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	double m; double i;
	
	ok &= JS::ToNumber( cx, argvp[0], &m );
	ok &= JS::ToNumber( cx, argvp[1], &i );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpBody *ret_body = NULL;
	if( m == INFINITY && i == INFINITY) {
		ret_body = cpBodyNewStatic();
		
		// XXX: Hack. IT WILL LEAK "rogue" objects., But at least it prevents a crash.
		// The thing is that "rogue" bodies needs to be freed after the its shape, and I am not sure
		// how to do it in a "js" way.
		jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_DO_NOT_CALL_FREE);
	} else {
		ret_body = cpBodyNew((cpFloat)m , (cpFloat)i  );
		jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_CALL_FREE);
	}
	
	jsb_set_jsobject_for_proxy(jsobj, ret_body);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return true;
}

#pragma mark getUserData

static
bool __jsb_cpBody_getUserData(JSContext *cx, jsval *vp, jsval *argvp, cpBody *body)
{
	JSObject *data = (JSObject*) cpBodyGetUserData(body);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(data));
	
	return true;
}

// free function
bool JSB_cpBodyGetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	cpBody *body;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &body ) )
		return false;

	return __jsb_cpBody_getUserData(cx, vp, argvp, body);
}

// method
bool JSB_cpBody_getUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpBody_getUserData(cx, vp, JS_ARGV(cx,vp), (cpBody*)handle);
}


#pragma mark setUserData

static
bool __jsb_cpBody_setUserData(JSContext *cx, jsval *vp, jsval *argvp, cpBody *body)
{
    JS::RootedObject jsobj(cx);

	bool ok = JS_ValueToObject(cx, JS::RootedValue(cx, *argvp), &jsobj);

	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	cpBodySetUserData(body, jsobj);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	
	return true;
}

// free function
bool JSB_cpBodySetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	cpBody *body;
	bool ok = jsval_to_opaque( cx, *argvp++, (void**) &body );
	JSB_PRECONDITION(ok, "Error parsing arguments");
	return __jsb_cpBody_setUserData(cx, vp, argvp, body);
}

// method
bool JSB_cpBody_setUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpBody_setUserData(cx, vp, JS_ARGV(cx,vp), (cpBody*)handle);
}

#pragma mark - Poly related

// cpFloat cpAreaForPoly(const int numVerts, const cpVect *verts);
bool JSB_cpAreaForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{	
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpVect *verts;
	int numVerts;
	
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	JSB_PRECONDITION2(ok, cx, false, "Error parsing array");
	
	cpFloat area = cpAreaForPoly(numVerts, verts);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(area));
	return true;
}

// cpFloat cpMomentForPoly(cpFloat m, int numVerts, const cpVect *verts, cpVect offset);
bool JSB_cpMomentForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==3, cx, false, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpVect *verts; cpVect offset;
	int numVerts;
	double m;
	
	ok &= JS::ToNumber(cx, JS::RootedValue(cx, *argvp++), &m);
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &offset );

	JSB_PRECONDITION2(ok, cx, false, "Error parsing args");
	
	cpFloat moment = cpMomentForPoly((cpFloat)m, numVerts, verts, offset);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(moment));
	return true;
}

// cpVect cpCentroidForPoly(const int numVerts, const cpVect *verts);
bool JSB_cpCentroidForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpVect *verts;
	int numVerts;
	
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	JSB_PRECONDITION2(ok, cx, false, "Error parsing args");
	
	cpVect centroid = cpCentroidForPoly(numVerts, verts);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, cpVect_to_jsval(cx, (cpVect)centroid));
	return true;
}

// void cpRecenterPoly(const int numVerts, cpVect *verts);
bool JSB_cpRecenterPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCASSERT(false, "NOT IMPLEMENTED");
	return false;
}

#pragma mark - Object Oriented Chipmunk

/*
 * Chipmunk Base Object
 */

JSClass* JSB_cpBase_class = NULL;
JSObject* JSB_cpBase_object = NULL;
// Constructor
bool JSB_cpBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc==1, cx, false, "Invalid arguments. Expecting 1");
	JS::HandleObject objHandle(JS::HandleObject::fromMarkedLocation(&JSB_cpBase_object));
	JSObject *jsobj = JS_NewObject(cx, JSB_cpBase_class, objHandle, JS::NullPtr());
	
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	
	void *handle = NULL;
	
	ok = jsval_to_opaque(cx, *argvp++, &handle);
	
	JSB_PRECONDITION(ok, "Error converting arguments for JSB_cpBase_constructor");

	jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsobj, handle);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return true;
}

// Destructor
void JSB_cpBase_finalize(JSFreeOp *fop, JSObject *obj)
{
	CCLOGINFO("jsbindings: finalizing JS object %p (cpBase)", obj);
	
	// should not delete the handle since it was manually added
}

bool JSB_cpBase_getHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");

	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	jsval ret_val = opaque_to_jsval(cx, handle);
	JS_SET_RVAL(cx, vp, ret_val);
	return true;
}

bool JSB_cpBase_setHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	void *handle;
	bool ok = jsval_to_opaque(cx, *argvp++, &handle);
	JSB_PRECONDITION( ok, "Invalid parsing arguments");

	jsb_set_c_proxy_for_jsobject(jsthis, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsthis, handle);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
}


void JSB_cpBase_createClass(JSContext *cx, JSObject* globalObj, const char* name )
{
	JSB_cpBase_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSB_cpBase_class->name = name;
	JSB_cpBase_class->addProperty = JS_PropertyStub;
	JSB_cpBase_class->delProperty = JS_DeletePropertyStub;
	JSB_cpBase_class->getProperty = JS_PropertyStub;
	JSB_cpBase_class->setProperty = JS_StrictPropertyStub;
	JSB_cpBase_class->enumerate = JS_EnumerateStub;
	JSB_cpBase_class->resolve = JS_ResolveStub;
	JSB_cpBase_class->convert = JS_ConvertStub;
	JSB_cpBase_class->finalize = JSB_cpBase_finalize;
	JSB_cpBase_class->flags = JSCLASS_HAS_PRIVATE;
	
	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("getHandle", JSB_cpBase_getHandle, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FN("setHandle", JSB_cpBase_setHandle, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};
	
	JSB_cpBase_object = JS_InitClass(cx, globalObj, NULL, JSB_cpBase_class, JSB_cpBase_constructor,0,properties,funcs,NULL,st_funcs);
//	bool found;
//	JS_SetPropertyAttributes(cx, globalObj, name, JSPROP_ENUMERATE | JSPROP_READONLY, &found);
}

// Manual "methods"
// Constructor
bool JSB_cpPolyShape_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==3, cx, false, "Invalid number of arguments");
	JS::HandleObject objectHandle(JS::HandleObject::fromMarkedLocation(&JSB_cpPolyShape_object));
	JSObject *jsobj = JS_NewObject(cx, JSB_cpPolyShape_class, objectHandle, JS::NullPtr());
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	cpBody* body; cpVect *verts; cpVect offset;
	int numVerts;
	
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&body, NULL );
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &offset );
	JSB_PRECONDITION(ok, "Error processing arguments");
	cpShape *shape = cpPolyShapeNew(body, numVerts, verts, offset);

	jsb_set_c_proxy_for_jsobject(jsobj, shape, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsobj, shape);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	free(verts);
	
	return true;
}


#pragma mark Space Free functions
//
// When the space is removed, it should all remove its children. But not "free" them.
// "free" will be performed by the JS Garbage Collector
//
// Functions copied & pasted from ChipmunkDemo.c
// https://github.com/slembcke/Chipmunk-Physics/blob/master/Demo/ChipmunkDemo.c#L89
//

static void unroot_jsobject_from_handle(void *handle)
{
	JSObject *jsobj = jsb_get_jsobject_for_proxy(handle);
    //2014.9.19 by joshua
    //add safe guard
    if(jsobj)
    {
        struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);
	
	    // HACK context from global
	    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	    RemoveObjectRoot(cx, &proxy->jsobj);
    }
	
}
static void shapeFreeWrap(cpSpace *space, cpShape *shape, void *unused){
	cpSpaceRemoveShape(space, shape);
	unroot_jsobject_from_handle(shape);
//	cpShapeFree(shape);
}

static void postShapeFree(cpShape *shape, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)shapeFreeWrap, shape, NULL);
}

static void constraintFreeWrap(cpSpace *space, cpConstraint *constraint, void *unused){
	cpSpaceRemoveConstraint(space, constraint);
	unroot_jsobject_from_handle(constraint);
//	cpConstraintFree(constraint);
}

static void postConstraintFree(cpConstraint *constraint, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)constraintFreeWrap, constraint, NULL);
}

static void bodyFreeWrap(cpSpace *space, cpBody *body, void *unused){
	cpSpaceRemoveBody(space, body);
	unroot_jsobject_from_handle(body);
//	cpBodyFree(body);
}

static void postBodyFree(cpBody *body, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)bodyFreeWrap, body, NULL);
}

// Safe and future proof way to remove and free all objects that have been added to the space.
void static freeSpaceChildren(cpSpace *space)
{
	// Must remove these BEFORE freeing the body or you will access dangling pointers.
	cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)postShapeFree, space);
	cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)postConstraintFree, space);
	
	cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)postBodyFree, space);
}

#endif // JSB_INCLUDE_CHIPMUNK
