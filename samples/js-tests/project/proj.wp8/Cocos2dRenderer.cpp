#include "pch.h"
#include "Cocos2dRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

USING_NS_CC;

Cocos2dRenderer::Cocos2dRenderer() :
	m_glView(nullptr),
	m_AngleInitialized(false),
	m_Initialized(false),
	m_eglDisplay(EGL_NO_DISPLAY),
	m_eglContext(EGL_NO_CONTEXT),
	m_eglSurface(EGL_NO_SURFACE)
{
}

void Cocos2dRenderer::Initialize(Windows::UI::Core::CoreWindow^ window)
{
	Direct3DBase::Initialize(window);

	InitializeAngle();

	CreateGLResources();

	m_glView = GLViewImpl::sharedOpenGLView();
}

bool Cocos2dRenderer::InitializeAngle()
{
	// setup EGL
	EGLint configAttribList[] = {
		EGL_RED_SIZE,       8,
		EGL_GREEN_SIZE,     8,
		EGL_BLUE_SIZE,      8,
		EGL_ALPHA_SIZE,     8,
		EGL_DEPTH_SIZE,     8,
		EGL_STENCIL_SIZE,   8,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};
	EGLint surfaceAttribList[] = {
		EGL_NONE, EGL_NONE
	};

	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// we need to select the correct DirectX feature level depending on the platform
	// default is D3D_FEATURE_LEVEL_9_3 Windows Phone 8.0
	ANGLE_D3D_FEATURE_LEVEL featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_3;

	switch(m_featureLevel)
	{
	case ANGLE_D3D_FEATURE_LEVEL_9_3:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_3;
		break;

	case ANGLE_D3D_FEATURE_LEVEL_9_2:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_2;
		break;

	case ANGLE_D3D_FEATURE_LEVEL_9_1:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_1;
		break;
	}		

	if(m_eglPhoneWindow == nullptr)
	{
		DX::ThrowIfFailed(
			CreateWinPhone8XamlWindow(&m_eglPhoneWindow)
			);
	}

	m_eglPhoneWindow->Update(m_d3dDevice.Get(), m_d3dContext.Get(), m_renderTargetView.Get());

	ComPtr<IUnknown> u;
	HRESULT r = m_eglPhoneWindow.As(&u);

	if(m_eglWindow == nullptr)
	{ 	
		DX::ThrowIfFailed(
			CreateWinrtEglWindow(u.Get(), featureLevel, m_eglWindow.GetAddressOf())
			);
	}

	display = eglGetDisplay(m_eglWindow);
	if(display == EGL_NO_DISPLAY){
		//ofLogError("ofAppWinRTWindow") << "couldn't get EGL display";
		return false;
	}

	if(!eglInitialize(display, &majorVersion, &minorVersion)){
		//ofLogError("ofAppWinRTWindow") << "failed to initialize EGL";
		return false;
	}

	// Get configs
	if ( !eglGetConfigs(display, NULL, 0, &numConfigs) ){
		//ofLogError("ofAppWinRTWindow") << "failed to get configurations";
		return false;
	}

	// Choose config
	if(!eglChooseConfig(display, configAttribList, &config, 1, &numConfigs)){
		//ofLogError("ofAppWinRTWindow") << "failed to choose configuration";
		return false;
	}

	// Create a surface
	surface = eglCreateWindowSurface(display, config, m_eglWindow, surfaceAttribList);
	if(surface == EGL_NO_SURFACE){
		//ofLogError("ofAppWinRTWindow") << "failed to create EGL window surface";
		return false;
	}  

	// Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if(context == EGL_NO_CONTEXT){
		//ofLogError("ofAppWinRTWindow") << "failed to create EGL context";
		return false;
	}   

	// Make the context current
	if (!eglMakeCurrent(display, surface, surface, context)){
		//ofLogError("ofAppWinRTWindow") << "failed to make EGL context current";
		return false;
	}

	m_eglDisplay = display;
	m_eglSurface = surface;
	m_eglContext = context;

	m_AngleInitialized = true;
	return true;
}

// Creates and restores Cocos2d-x after DirectX and Angle contexts are created or updated
void Cocos2dRenderer::CreateGLResources()
{
	auto director = cocos2d::Director::getInstance();

	if (!m_Initialized)
	{
		m_Initialized = true;
		GLViewImpl* glview = GLViewImpl::create("js-tests");
		director->setOpenGLView(glview);
		glview->setDesignResolutionSize(m_renderTargetSize.Width, m_renderTargetSize.Height, ResolutionPolicy::SHOW_ALL);
		glview->Create(m_eglDisplay, m_eglContext, m_eglSurface, m_renderTargetSize.Width, m_renderTargetSize.Height, m_orientation);
		//glview->SetXamlEventDelegate(m_delegate);
		//glview->SetXamlMessageBoxDelegate(m_messageBoxDelegate);
		//glview->SetXamlEditBoxDelegate(m_editBoxDelegate);
		CCApplication::getInstance()->run();
	}
	else
	{
		cocos2d::GL::invalidateStateCache();
		cocos2d::ShaderCache::getInstance()->reloadDefaultGLPrograms();
		cocos2d::DrawPrimitives::init();
		cocos2d::VolatileTextureMgr::reloadAllTextures();
		cocos2d::EventCustom recreatedEvent(EVENT_RENDERER_RECREATED);
		director->getEventDispatcher()->dispatchEvent(&recreatedEvent);
		cocos2d::Application::getInstance()->applicationWillEnterForeground();
		director->setGLDefaultValues();
	}
}

void Cocos2dRenderer::Render()
{
	if(m_glView)
		m_glView->Render();
}
