#ifndef __cocos2dx_ui_h__
#define __cocos2dx_ui_h__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "js_bindings_config.h"

extern JSClass  *jsb_cocos2d_ui_LayoutParameter_class;
extern JSObject *jsb_cocos2d_ui_LayoutParameter_prototype;

bool js_cocos2dx_ui_LayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_LayoutParameter_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_LayoutParameter(JSContext *cx, JSObject *global);
CC_BINDING_GUI_DLL void register_all_cocos2dx_ui(JSContext* cx, JSObject* obj);
bool js_cocos2dx_ui_LayoutParameter_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LayoutParameter_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LayoutParameter_createCloneInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LayoutParameter_copyProperties(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LayoutParameter_LayoutParameter(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_LinearLayoutParameter_class;
extern JSObject *jsb_cocos2d_ui_LinearLayoutParameter_prototype;

bool js_cocos2dx_ui_LinearLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_LinearLayoutParameter_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_LinearLayoutParameter(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_LinearLayoutParameter_setGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LinearLayoutParameter_getGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LinearLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LinearLayoutParameter_LinearLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RelativeLayoutParameter_class;
extern JSObject *jsb_cocos2d_ui_RelativeLayoutParameter_prototype;

bool js_cocos2dx_ui_RelativeLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RelativeLayoutParameter_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RelativeLayoutParameter(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RelativeLayoutParameter_setAlign(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_getRelativeName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_getRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_getAlign(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeLayoutParameter_RelativeLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Widget_class;
extern CC_BINDING_GUI_DLL JSObject *jsb_cocos2d_ui_Widget_prototype;

bool js_cocos2dx_ui_Widget_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Widget_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Widget(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Widget_setSizePercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getCustomSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getLeftBoundary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setFlippedX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getVirtualRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setPropagateTouchEvents(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getSizePercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setPositionPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setSwallowTouches(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getLayoutSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setPositionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getVirtualRendererSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_hitTest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getPositionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getTopBoundary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_findNextFocusedWidget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isFocused(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getTouchBeganPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getWorldPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isFocusEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setFocused(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setFlippedY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getRightBoundary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setBrightStyle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setFocusEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getBottomBoundary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isBright(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isPropagateTouchEvents(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getCurrentFocusedWidget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_requestFocus(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_updateSizeAndPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_onFocusChange(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getTouchMovePosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getSizeType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_interceptTouchEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getTouchEndPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_getPositionPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_propagateTouchEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_addClickEventListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isFlippedX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isFlippedY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isClippingParentContainsPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setSizeType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_dispatchFocusEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_setBright(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_isSwallowTouches(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_enableDpadNavigation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Widget_Widget(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Layout_class;
extern JSObject *jsb_cocos2d_ui_Layout_prototype;

bool js_cocos2dx_ui_Layout_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Layout_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Layout(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Layout_setBackGroundColorVector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setClippingType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundColorType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setLoopFocus(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundImageColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundColorVector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getClippingType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_isLoopFocus(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_removeBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundColorOpacity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_isClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundImageOpacity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_requestDoLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundImageCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundImageColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_isBackGroundImageScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundColorType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundEndColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundColorOpacity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundImageOpacity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_isPassFocusToChild(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundImageCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundImageTextureSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_forceDoLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setPassFocusToChild(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_getBackGroundStartColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_setLayoutType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Layout_Layout(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Button_class;
extern JSObject *jsb_cocos2d_ui_Button_prototype;

bool js_cocos2dx_ui_Button_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Button_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Button(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Button_getTitleText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getTitleRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getCapInsetsDisabledRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setTitleColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_loadTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setTitleText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setCapInsetsNormalRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_loadTexturePressed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setTitleFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getCapInsetsNormalRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getCapInsetsPressedRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_loadTextures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_loadTextureNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setCapInsetsPressedRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getTitleFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_getTitleColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setPressedActionEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Button_Button(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_CheckBox_class;
extern JSObject *jsb_cocos2d_ui_CheckBox_prototype;

bool js_cocos2dx_ui_CheckBox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_CheckBox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_CheckBox(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_setSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_loadTextureFrontCross(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_isSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_loadTextures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_loadTextureBackGround(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_CheckBox_CheckBox(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_ImageView_class;
extern JSObject *jsb_cocos2d_ui_ImageView_prototype;

bool js_cocos2dx_ui_ImageView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_ImageView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_ImageView(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_ImageView_loadTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_setTextureRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ImageView_ImageView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Text_class;
extern JSObject *jsb_cocos2d_ui_Text_prototype;

bool js_cocos2dx_ui_Text_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Text_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Text(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Text_enableShadow(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_disableEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getTextColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_isTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getStringLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_enableOutline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setTextColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_enableGlow(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_getTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_setTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Text_Text(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_TextAtlas_class;
extern JSObject *jsb_cocos2d_ui_TextAtlas_prototype;

bool js_cocos2dx_ui_TextAtlas_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_TextAtlas_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_TextAtlas(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_TextAtlas_getStringLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_setProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_adaptRenderers(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextAtlas_TextAtlas(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_LoadingBar_class;
extern JSObject *jsb_cocos2d_ui_LoadingBar_prototype;

bool js_cocos2dx_ui_LoadingBar_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_LoadingBar_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_LoadingBar(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_LoadingBar_setPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_loadTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_setDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_getDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_getPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_LoadingBar_LoadingBar(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_ScrollView_class;
extern JSObject *jsb_cocos2d_ui_ScrollView_prototype;

bool js_cocos2dx_ui_ScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_ScrollView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_ScrollView(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_ScrollView_scrollToTop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_isInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_getInnerContainer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToBottom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToTopLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToTopRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_setInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_getInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_isBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToTopLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToBottomRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_setBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToTop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToBottom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToBottomRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToLeft(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_jumpToRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_scrollToTopRight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ScrollView_ScrollView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_ListView_class;
extern JSObject *jsb_cocos2d_ui_ListView_prototype;

bool js_cocos2dx_ui_ListView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_ListView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_ListView(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_ListView_getIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_removeAllItems(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_setGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_pushBackCustomItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_getItems(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_removeItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_getCurSelectedIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_insertDefaultItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_requestRefreshView(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_setItemsMargin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_refreshView(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_removeLastItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_getItemsMargin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_getItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_setItemModel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_doLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_pushBackDefaultItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_insertCustomItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_ListView_ListView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Slider_class;
extern JSObject *jsb_cocos2d_ui_Slider_prototype;

bool js_cocos2dx_ui_Slider_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Slider_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Slider(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Slider_setPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadSlidBallTextureNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadBarTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadProgressBarTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadSlidBallTextures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_setCapInsetsBarRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_getCapInsetsProgressBarRebderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_loadSlidBallTexturePressed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_getCapInsetsBarRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_getPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Slider_Slider(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_TextField_class;
extern JSObject *jsb_cocos2d_ui_TextField_prototype;

bool js_cocos2dx_ui_TextField_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_TextField_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_TextField(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_TextField_setAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getInsertText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setInsertText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_didNotSelectSelf(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getFontName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_attachWithIME(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getStringLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getPlaceHolderColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_isPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setPlaceHolderColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTextColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_isMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTouchAreaEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_hitTest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_setTouchSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_getTouchSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextField_TextField(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_TextBMFont_class;
extern JSObject *jsb_cocos2d_ui_TextBMFont_prototype;

bool js_cocos2dx_ui_TextBMFont_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_TextBMFont_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_TextBMFont(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_TextBMFont_setFntFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_getStringLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_TextBMFont_TextBMFont(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_PageView_class;
extern JSObject *jsb_cocos2d_ui_PageView_prototype;

bool js_cocos2dx_ui_PageView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_PageView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_PageView(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_PageView_getCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_getCurPageIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_addWidgetToPage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_isUsingCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_getPage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_removePage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_setCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_insertPage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_scrollToPage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_removePageAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_getPages(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_removeAllPages(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_addPage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_PageView_PageView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_Helper_class;
extern JSObject *jsb_cocos2d_ui_Helper_prototype;

bool js_cocos2dx_ui_Helper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_Helper_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_Helper(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_Helper_getSubStringOfUTF8String(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Helper_seekWidgetByTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Helper_seekActionWidgetByActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_Helper_seekWidgetByName(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RichElement_class;
extern JSObject *jsb_cocos2d_ui_RichElement_prototype;

bool js_cocos2dx_ui_RichElement_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RichElement_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RichElement(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RichElement_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElement_RichElement(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RichElementText_class;
extern JSObject *jsb_cocos2d_ui_RichElementText_prototype;

bool js_cocos2dx_ui_RichElementText_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RichElementText_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RichElementText(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RichElementText_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementText_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementText_RichElementText(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RichElementImage_class;
extern JSObject *jsb_cocos2d_ui_RichElementImage_prototype;

bool js_cocos2dx_ui_RichElementImage_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RichElementImage_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RichElementImage(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RichElementImage_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementImage_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementImage_RichElementImage(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RichElementCustomNode_class;
extern JSObject *jsb_cocos2d_ui_RichElementCustomNode_prototype;

bool js_cocos2dx_ui_RichElementCustomNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RichElementCustomNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RichElementCustomNode(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RichElementCustomNode_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementCustomNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichElementCustomNode_RichElementCustomNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RichText_class;
extern JSObject *jsb_cocos2d_ui_RichText_prototype;

bool js_cocos2dx_ui_RichText_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RichText_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RichText(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RichText_insertElement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_pushBackElement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_ignoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_setVerticalSpace(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_formatText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_removeElement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RichText_RichText(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_HBox_class;
extern JSObject *jsb_cocos2d_ui_HBox_prototype;

bool js_cocos2dx_ui_HBox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_HBox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_HBox(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_HBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_HBox_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_HBox_HBox(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_VBox_class;
extern JSObject *jsb_cocos2d_ui_VBox_prototype;

bool js_cocos2dx_ui_VBox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_VBox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_VBox(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_VBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_VBox_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_VBox_VBox(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ui_RelativeBox_class;
extern JSObject *jsb_cocos2d_ui_RelativeBox_prototype;

bool js_cocos2dx_ui_RelativeBox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ui_RelativeBox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ui_RelativeBox(JSContext *cx, JSObject *global);
bool js_cocos2dx_ui_RelativeBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeBox_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ui_RelativeBox_RelativeBox(JSContext *cx, uint32_t argc, jsval *vp);
#endif

