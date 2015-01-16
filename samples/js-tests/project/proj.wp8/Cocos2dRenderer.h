#pragma once

#include "Direct3DBase.h"

ref class Cocos2dRenderer sealed : public Direct3DBase
{
public:
	Cocos2dRenderer();

	// Direct3DBase methods.
	virtual void Initialize(Windows::UI::Core::CoreWindow^ window) override;

	void Render();
	
private:

	bool InitializeAngle();
	void CreateGLResources();

	cocos2d::GLViewImpl* m_glView;

	bool m_AngleInitialized;
	bool m_Initialized;

	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;

	Microsoft::WRL::ComPtr<IWinrtEglWindow>         m_eglWindow;
	Microsoft::WRL::ComPtr<IWinPhone8XamlD3DWindow> m_eglPhoneWindow;

	friend ref class PhoneApp;
};
