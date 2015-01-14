/*
 * Created by ucchen on 2/12/14.
 * Copyright (c) 2014 Chukong Technologies Inc.
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

#include "jsb_cocos2dx_spine_manual.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "spine/spine-cocos2dx.h"

using namespace spine;

jsval speventdata_to_jsval(JSContext* cx, spEventData& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    JS::Value name(c_string_to_jsval(cx, v.name));
    JS::HandleValue nameHandle(JS::HandleValue::fromMarkedLocation(&name));
    JS::Value stringValue(c_string_to_jsval(cx, v.stringValue));
    JS::HandleValue stringValueHandle(JS::HandleValue::fromMarkedLocation(&stringValue));
    bool ok = JS_DefineProperty(cx, tmpHandle, "name", nameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "intValue", v.intValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "floatValue", v.floatValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "stringValue", stringValueHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval spevent_to_jsval(JSContext* cx, spEvent& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JS::Value data(speventdata_to_jsval(cx, *v.data));
    JS::HandleValue dataHandle(JS::HandleValue::fromMarkedLocation(&data));
    JS::Value stringValue(c_string_to_jsval(cx, v.stringValue));
    JS::HandleValue stringValueHandle(JS::HandleValue::fromMarkedLocation(&stringValue));
    bool ok = JS_DefineProperty(cx, tmpHandle, "data", dataHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "intValue", v.intValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "floatValue", v.floatValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "stringValue", stringValueHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbonedata_to_jsval(JSContext* cx, const spBoneData* v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    // root haven't parent
    jsval parentVal = JSVAL_NULL;
    if (strcmp(v->name, "root"))
        parentVal = spbonedata_to_jsval(cx, v->parent);
    
    JS::Value name(c_string_to_jsval(cx, v->name));
    JS::HandleValue nameHandle(JS::HandleValue::fromMarkedLocation(&name));
    JS::HandleValue parentValHandle(JS::HandleValue::fromMarkedLocation(&parentVal));
    bool ok = JS_DefineProperty(cx, tmpHandle, "name", nameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "parent", parentValHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "length", v->length, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "x", v->x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v->y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "rotation", v->rotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "scaleX", v->scaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "scaleY", v->scaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "inheritScale", v->inheritScale, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "inheritRotation", v->inheritRotation, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbone_to_jsval(JSContext* cx, spBone& v)
{
    JSObject* tmp =JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    // root haven't parent
    jsval parentVal = JSVAL_NULL;
    if (strcmp(v.data->name, "root"))
        parentVal = spbone_to_jsval(cx, *v.parent);
    
    JS::Value data(spbonedata_to_jsval(cx, v.data));
    JS::HandleValue dataHandle(JS::HandleValue::fromMarkedLocation(&data));
    JS::HandleValue parentValHandle(JS::HandleValue::fromMarkedLocation(&parentVal));
    bool ok = JS_DefineProperty(cx, tmpHandle, "data", dataHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "parent", parentValHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "rotation", v.rotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "scaleX", v.scaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "scaleY", v.scaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "m00", v.m00, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "m01", v.m01, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "worldX", v.worldX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "m10", v.m10, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "m11", v.m11, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "worldY", v.worldY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "worldRotation", v.worldRotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "worldScaleX", v.worldScaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "worldScaleY", v.worldScaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spskeleton_to_jsval(JSContext* cx, spSkeleton& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    bool ok = JS_DefineProperty(cx, tmpHandle, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "flipX", v.flipX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "flipY", v.flipY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "time", v.time, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "boneCount", v.boneCount, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "slotCount", v.slotCount, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spattachment_to_jsval(JSContext* cx, spAttachment& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JS::Value name(c_string_to_jsval(cx, v.name));
    JS::HandleValue nameHandle(JS::HandleValue::fromMarkedLocation(&name));
    bool ok = JS_DefineProperty(cx, tmpHandle, "name", nameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "type", v.type, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spslotdata_to_jsval(JSContext* cx, spSlotData& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));

    JS::Value name(c_string_to_jsval(cx, v.name));
    JS::HandleValue nameHandle(JS::HandleValue::fromMarkedLocation(&name));
    JS::Value attachmentName(c_string_to_jsval(cx, v.attachmentName));
    JS::HandleValue attachmentNameHandle(JS::HandleValue::fromMarkedLocation(&attachmentName));
    JS::Value boneData(spbonedata_to_jsval(cx, v.boneData));
    JS::HandleValue boneDataHandle(JS::HandleValue::fromMarkedLocation(&boneData));
    bool ok = JS_DefineProperty(cx, tmpHandle, "name", nameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "attachmentName", attachmentNameHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "r", v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "g", v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "a", v.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "additiveBlending", v.additiveBlending, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "boneData", boneDataHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spslot_to_jsval(JSContext* cx, spSlot& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JS::Value bone(spbone_to_jsval(cx, *v.bone));
    JS::HandleValue boneHandle(JS::HandleValue::fromMarkedLocation(&bone));
    JS::Value skeleton(spskeleton_to_jsval(cx, *v.skeleton));
    JS::HandleValue skeletonHandle(JS::HandleValue::fromMarkedLocation(&skeleton));
    JS::Value attachment(spattachment_to_jsval(cx, *v.attachment));
    JS::HandleValue attachmentHandle(JS::HandleValue::fromMarkedLocation(&attachment));
    JS::Value slotdata(spslotdata_to_jsval(cx, *v.data));
    JS::HandleValue slotdataHandle(JS::HandleValue::fromMarkedLocation(&slotdata));
    bool ok = JS_DefineProperty(cx, tmpHandle, "r", v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "g", v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "b", v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "a", v.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "bone", boneHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "skeleton", skeletonHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "attachment", attachmentHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "data", slotdataHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval sptimeline_to_jsval(JSContext* cx, spTimeline& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    bool ok = JS_DefineProperty(cx, tmpHandle, "type", v.type, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimationstate_to_jsval(JSContext* cx, spAnimationState& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    bool ok = JS_DefineProperty(cx, tmpHandle, "timeScale", v.timeScale, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "trackCount", v.trackCount, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimation_to_jsval(JSContext* cx, spAnimation& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    JS::Value cStr(c_string_to_jsval(cx, v.name));
    JS::Value sptimeline(sptimeline_to_jsval(cx, **v.timelines));
    JS::HandleValue cStrHandle(JS::HandleValue::fromMarkedLocation(&cStr));
    JS::HandleValue sptimelineHandle(JS::HandleValue::fromMarkedLocation(&sptimeline));
    bool ok = JS_DefineProperty(cx, tmpHandle, "duration", v.duration, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "timelineCount", v.timelineCount, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "name", cStrHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "timelines", sptimelineHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval sptrackentry_to_jsval(JSContext* cx, spTrackEntry& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
    if (!tmp) return JSVAL_NULL;
    JS::HandleObject tmpHandle(JS::HandleObject::fromMarkedLocation(&tmp));
    
    jsval nextVal = JSVAL_NULL;
    if (v.next)
        nextVal = sptrackentry_to_jsval(cx, *v.next);
    
    jsval previousVal = JSVAL_NULL;
    if (v.previous)
        previousVal = sptrackentry_to_jsval(cx, *v.previous);
    
    JS::HandleValue nextValHandle(JS::HandleValue::fromMarkedLocation(&nextVal));
    JS::HandleValue previousValHandle(JS::HandleValue::fromMarkedLocation(&previousVal));
    JS::Value spanimation(spanimation_to_jsval(cx, *v.animation));
    JS::HandleValue spanimationHandle(JS::HandleValue::fromMarkedLocation(&spanimation));
    bool ok = JS_DefineProperty(cx, tmpHandle, "delay", v.delay, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "time", v.time, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "lastTime", v.lastTime, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "endTime", v.endTime, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "timeScale", v.timeScale, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "mixTime", v.mixTime, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "mixDuration", v.mixDuration, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "animation", spanimationHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "next", nextValHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmpHandle, "previous", previousValHandle, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

bool jsb_cocos2dx_spine_findBone(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::Skeleton* cobj = (spine::Skeleton *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		spBone* ret = cobj->findBone(arg0);
		jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spbone_to_jsval(cx, *ret);
            }
        } while (0);
        
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_findSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::Skeleton* cobj = (spine::Skeleton *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		spSlot* ret = cobj->findSlot(arg0);
		jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spslot_to_jsval(cx, *ret);
            }
        } while (0);
        
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_setDebugBones(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::Skeleton* cobj = (spine::Skeleton *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		bool enable = argv[0].toBoolean();
		cobj->debugBones = enable;
        
		JS_SET_RVAL(cx, vp, JSVAL_NULL);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_setDebugSolots(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::Skeleton* cobj = (spine::Skeleton *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		bool enable = argv[0].toBoolean();
		cobj->debugSlots = enable;
        
		JS_SET_RVAL(cx, vp, JSVAL_NULL);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_getAttachment(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::Skeleton* cobj = (spine::Skeleton*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spAttachment* ret = cobj->getAttachment(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spattachment_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_getCurrent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		spTrackEntry* ret = cobj->getCurrent(arg0);
		jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while (0);
        
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    else if (argc == 0) {
        spTrackEntry* ret = cobj->getCurrent();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while (0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_setAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        JS::RootedValue dummy(cx, argv[2]);
        bool arg2 = JS::ToBoolean(dummy);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->setAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

bool jsb_cocos2dx_spine_addAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        JS::RootedValue dummy(cx, argv[2]);
        bool arg2 = JS::ToBoolean(dummy);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    } else if (argc == 4) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        JS::RootedValue dummy2(cx, argv[2]);
        bool arg2 = JS::ToBoolean(dummy2);
        
        double arg3;
        JS::RootedValue dummy3(cx, argv[3]);
        ok &= JS::ToNumber(cx, dummy3, &arg3);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }    
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}


class JSSkeletonAnimationWrapper: public JSCallbackWrapper
{
public:
    JSSkeletonAnimationWrapper() {}
    virtual ~JSSkeletonAnimationWrapper() {}
    
    void animationCallbackFunc(spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount) const {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject *thisObj = _jsThisObj.isUndefined() ? NULL : _jsThisObj.toObjectOrNull();
        JS::HandleObject thisObjHandle(JS::HandleObject::fromMarkedLocation(&thisObj));
        js_proxy_t *proxy = js_get_or_create_proxy(cx, node);
        jsval retVal;
        if (_jsCallback != JSVAL_VOID)
        {
            jsval nodeVal = OBJECT_TO_JSVAL(proxy->obj);
            jsval trackIndexVal = INT_TO_JSVAL(trackIndex);
            int tmpType = (int)type;
            jsval typeVal = INT_TO_JSVAL(tmpType);
            jsval eventVal = JSVAL_NULL;
            if (event)
                eventVal = spevent_to_jsval(cx, *event);
            jsval loopCountVal = INT_TO_JSVAL(loopCount);
            
            JS::Heap<JS::Value> valArr[5];
            valArr[0] = nodeVal;
            valArr[1] = trackIndexVal;
            valArr[2] = typeVal;
            valArr[3] = eventVal;
            valArr[4] = loopCountVal;
            JS::AutoValueVector dummyArr(cx);
            dummyArr.append(valArr[0].get());
            dummyArr.append(valArr[1].get());
            dummyArr.append(valArr[2].get());
            dummyArr.append(valArr[3].get());
            dummyArr.append(valArr[4].get());
            JS::HandleValue _jsCallbackHandle(JS::HandleValue::fromMarkedLocation(_jsCallback.address()));
            
            AddValueRoot(cx, valArr);
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            JS::MutableHandleValue retValHandle(JS::MutableHandleValue::fromMarkedLocation(&retVal));
            JS_CallFunctionValue(cx, thisObjHandle, _jsCallbackHandle, dummyArr, retValHandle);
            RemoveValueRoot(cx, valArr);
        }
    }
};

static bool jsb_cocos2dx_spine_setAnimationListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
    
    spine::SkeletonAnimation* node = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( node, cx, false, "Invalid Native Object");
    if (argc == 2) {
        JSSkeletonAnimationWrapper *tmpCobj = new JSSkeletonAnimationWrapper();
        jsval *argv = JS_ARGV(cx, vp);
        
        tmpCobj->setJSCallbackFunc(argv[1]);
        tmpCobj->setJSCallbackThis(argv[0]);
        
        node->setAnimationListener(tmpCobj, animationStateEvent_selector(JSSkeletonAnimationWrapper::animationCallbackFunc));
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        
        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

extern JSObject* jsb_spine_Skeleton_prototype;
extern JSObject* jsb_spine_SkeletonAnimation_prototype;

void register_all_cocos2dx_spine_manual(JSContext* cx, JSObject* global)
{
    JS::HandleObject SkeletonProtoHandle(JS::HandleObject::fromMarkedLocation(&jsb_spine_Skeleton_prototype));
    JS::HandleObject SkeletonAnimationProtoHandle(JS::HandleObject::fromMarkedLocation(&jsb_spine_SkeletonAnimation_prototype));
    JS_DefineFunction(cx, SkeletonProtoHandle, "findBone", jsb_cocos2dx_spine_findBone, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonProtoHandle, "findSlot", jsb_cocos2dx_spine_findSlot, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonProtoHandle, "setDebugBones", jsb_cocos2dx_spine_setDebugBones, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonProtoHandle, "setDebugSolots", jsb_cocos2dx_spine_setDebugSolots, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonProtoHandle, "getAttachment", jsb_cocos2dx_spine_getAttachment, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonAnimationProtoHandle, "getCurrent", jsb_cocos2dx_spine_getCurrent, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonAnimationProtoHandle, "setAnimation", jsb_cocos2dx_spine_setAnimation, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonAnimationProtoHandle, "addAnimation", jsb_cocos2dx_spine_addAnimation, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, SkeletonAnimationProtoHandle, "setAnimationListener", jsb_cocos2dx_spine_setAnimationListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
