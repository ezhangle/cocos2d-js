/*
* AUTOGENERATED FILE. DO NOT EDIT IT
* Generated by "generate_js_bindings.py -c system_jsb.ini" on 2012-12-17
* Script version: v0.5
*/
#include "../js_bindings_config.h"
//#ifdef JSB_INCLUDE_SYSTEM

//#include "LocalStorage.h"
JS::HandleObject system_handle(JS::HandleObject::fromMarkedLocation(&system));
JS_DefineFunction(_cx, system_handle, "getItem", JSB_localStorageGetItem, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
JS_DefineFunction(_cx, system_handle, "removeItem", JSB_localStorageRemoveItem, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
JS_DefineFunction(_cx, system_handle, "setItem", JSB_localStorageSetItem, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );

//#endif // JSB_INCLUDE_SYSTEM
