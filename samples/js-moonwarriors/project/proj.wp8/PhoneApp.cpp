#include "PhoneApp.h"
#include "ppltasks.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace concurrency;

PhoneApp::PhoneApp() :
	m_windowClosed(false),
	m_windowVisible(false)
{
}

void PhoneApp::Initialize(CoreApplicationView^ applicationView)
{
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &PhoneApp::OnActivated);
	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &PhoneApp::OnSuspending);
	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &PhoneApp::OnResuming);

	m_renderer = ref new Cocos2dRenderer();
}

void PhoneApp::SetWindow(CoreWindow^ window)
{
	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &PhoneApp::OnVisibilityChanged);
	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &PhoneApp::OnWindowClosed);
	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &PhoneApp::OnPointerPressed);
	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &PhoneApp::OnPointerMoved);
	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &PhoneApp::OnPointerReleased);

	m_renderer->Initialize(CoreWindow::GetForCurrentThread());
}

void PhoneApp::Load(Platform::String^ entryPoint)
{
}

void PhoneApp::Run()
{
    while (!m_windowClosed)
    {
        if (m_windowVisible)
        {
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
            m_renderer->Render();  // This call is rendered picture into internal buffer.
            m_renderer->Present(); // This call is synchronized internal buffer into display.
        }
        else
        {
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }
}

void PhoneApp::Uninitialize()
{
}

void PhoneApp::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnVisibilityChanged(sender, args);
}

void PhoneApp::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnWindowClosed(sender, args);
}

void PhoneApp::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnPointerPressed(sender, args);
}

void PhoneApp::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnPointerMoved(sender, args);
}

void PhoneApp::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnPointerReleased(sender, args);
}

void PhoneApp::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	CoreWindow::GetForCurrentThread()->Activate();
}

void PhoneApp::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// Save app state asynchronously after requesting a deferral. Holding a deferral
	// indicates that the application is busy performing suspending operations. Be
	// aware that a deferral may not be held indefinitely. After about five seconds,
	// the app will be forced to exit.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
	m_renderer->ReleaseResourcesForSuspending();
	app.applicationDidEnterBackground();
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnSuspending(sender, args);
	create_task([this, deferral]()
	{
		deferral->Complete();
	});
}
 
void PhoneApp::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Restore any data or state that was unloaded on suspend. By default, data
	// and state are persisted when resuming from suspend. Note that this event
	// does not occur if the app was previously terminated.
	m_renderer->CreateWindowSizeDependentResources();
	app.applicationWillEnterForeground();
	if(m_renderer->m_glView)
		m_renderer->m_glView->OnResuming(sender, args);
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
	return ref new PhoneApp();
}
