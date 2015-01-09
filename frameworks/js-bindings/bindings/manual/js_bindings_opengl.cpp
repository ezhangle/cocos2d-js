/*
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

#include "js_bindings_opengl.h"

using namespace JS;

void GLNode::draw(cocos2d::Renderer *renderer, const cocos2d::kmMat4& transform, bool transformUpdated) {
    js_proxy_t* proxy = NULL;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    proxy = js_get_or_create_proxy<cocos2d::Node>(cx, this);

    if( proxy ) {
        JSObject *jsObj = proxy->obj;
        if (jsObj) {
            bool found = false;
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            JS::HandleObject jsObjHandle(JS::HandleObject::fromMarkedLocation(&jsObj));
            JS_HasProperty(cx, jsObjHandle, "draw", &found);
            if (found == true) {
                JS::RootedValue rval(cx);
                JS::RootedValue fval(cx);
                jsval *argv = NULL; unsigned argc=0;

                JS_GetProperty(cx, jsObjHandle, "draw", &fval);
                JS_CallFunctionValue(cx, jsObj, fval, argc, argv, rval.address());
            }
        }
    }
}


JSClass  *js_cocos2dx_GLNode_class;
JSObject *js_cocos2dx_GLNode_prototype;

bool js_cocos2dx_GLNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{

    if (argc == 0) {
        GLNode* cobj = new GLNode();
        cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
        if (_ccobj) {
            _ccobj->autorelease();
        }

        TypeTest<GLNode> t;
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
        js_proxy_t *p = jsb_new_proxy(cobj, obj);

        AddNamedObjectRoot(cx, &p->obj, "cocos2d::GLNode");

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_cocos2dx_GLNode_finalize(JSFreeOp *fop, JSObject *obj) {
}

static bool js_cocos2dx_GLNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    GLNode *nobj = new GLNode();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    AddNamedObjectRoot(cx, &p->obj, "GLNode");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}

bool js_cocos2dx_GLNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    GLNode* ret = new GLNode();
    jsval jsret;
    do {
        if (ret) {
            js_proxy_t *proxy = js_get_or_create_proxy<GLNode>(cx, ret);
            jsret = OBJECT_TO_JSVAL(proxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
    JS_SET_RVAL(cx, vp, jsret);
    return true;
}

extern JSObject* jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_GLNode(JSContext *cx, JSObject *global) {
    js_cocos2dx_GLNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    js_cocos2dx_GLNode_class->name = "GLNode";
    js_cocos2dx_GLNode_class->addProperty = JS_PropertyStub;
    js_cocos2dx_GLNode_class->delProperty = JS_DeletePropertyStub;
    js_cocos2dx_GLNode_class->getProperty = JS_PropertyStub;
    js_cocos2dx_GLNode_class->setProperty = JS_StrictPropertyStub;
    js_cocos2dx_GLNode_class->enumerate = JS_EnumerateStub;
    js_cocos2dx_GLNode_class->resolve = JS_ResolveStub;
    js_cocos2dx_GLNode_class->convert = JS_ConvertStub;
    js_cocos2dx_GLNode_class->finalize = js_cocos2dx_GLNode_finalize;
    js_cocos2dx_GLNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {0, 0, 0, 0, 0}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("ctor", js_cocos2dx_GLNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_GLNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::HandleObject globalHandle(JS::HandleObject::fromMarkedLocation(&global));
    JS::HandleObject prototypeHandle(JS::HandleObject::fromMarkedLocation(&jsb_cocos2d_Node_prototype));
    js_cocos2dx_GLNode_prototype = JS_InitClass(
        cx, globalHandle,
        prototypeHandle,
        js_cocos2dx_GLNode_class,
        js_cocos2dx_GLNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//    bool found;
//    JS_SetPropertyAttributes(cx, global, "GLNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<GLNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = js_cocos2dx_GLNode_class;
        p->proto = js_cocos2dx_GLNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
