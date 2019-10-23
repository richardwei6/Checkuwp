//
// servo.xaml.cpp
// Implementation of the servo class
//

#include "pch.h"
#include "servo.xaml.h"
#include "variable.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "admindata.xaml.h"
#include <Wire.h>//ardino code
#include "Adafruit_PWMServoDriver.h" //ardino code
using namespace checkuwp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Devices::I2c;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Gpio;
using namespace concurrency;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Popups;

Adafruit_PWMServoDriver servom = Adafruit_PWMServoDriver();//ardino code
Adafruit_PWMServoDriver servow = Adafruit_PWMServoDriver();//ardino code*/

servo::servo()
{
	InitializeComponent();
	if (::servo1live == false)
	{
		servom.begin();//ardino code
		servom.setPWMFreq(60);//ardino code
	}
	if (::servo2live == false)
	{
		servow.begin();//ardino code
		servow.setPWMFreq(60);//ardino code
	}
	refresh();
}

long ToLong(Platform::String^ str) {
	const wchar_t* begin = str->Data();
	const wchar_t* end = str->Data() + std::wcslen(str->Data());
	wchar_t* last_interpreted{ nullptr };
	long l = std::wcstol(begin, &last_interpreted, 10);
	if (last_interpreted != end) {
		MessageDialog^ msg = ref new MessageDialog("Invalid Character.");
		msg->ShowAsync();
	}
	if (l > 2000)
	{
		MessageDialog^ msg = ref new MessageDialog("Too large of a value.");
		msg->ShowAsync();
		l = 0;
	}
	return l;
}

void checkuwp::servo::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(admin::typeid));
}


void checkuwp::servo::Servomenon_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (uint16_t pulselen = ::SERVOMXMEN; pulselen > ::SERVOMINMEN; pulselen--) {
		servom.setPWM(::menservo, 0, pulselen);
	}
	::servo1live = true;
	refresh();
}

void checkuwp::servo::Servowomenon_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (uint16_t pulselen = ::SERVOMXWOMEN; pulselen > ::SERVOMINWOMEN; pulselen--) {
		servow.setPWM(::womenservo, 0, pulselen);
	}
	::servo2live = true;
	refresh();
}

void checkuwp::servo::Resetall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (uint16_t pulselen = ::SERVOMXWOMEN; pulselen > ::SERVOMINWOMEN; pulselen--) {
		servow.setPWM(::womenservo, 0, pulselen);
	}
	for (uint16_t pulselen = ::SERVOMXMEN; pulselen > ::SERVOMINMEN; pulselen--) {
		servom.setPWM(::menservo, 0, pulselen);
	}
	::servo1live = true;
	::servo2live = true;
	refresh();
}


void checkuwp::servo::Resetdefault_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	::SERVOMINWOMEN = 310;
	::SERVOMXWOMEN = 1100;
	::SERVOMINMEN = 310; // 290
	::SERVOMXMEN = 1100;
	for (uint16_t pulselen = ::SERVOMXWOMEN; pulselen > ::SERVOMINWOMEN; pulselen--) {
		servow.setPWM(::womenservo, 0, pulselen);
	}
	for (uint16_t pulselen = ::SERVOMXMEN; pulselen > ::SERVOMINMEN; pulselen--) {
		servom.setPWM(::menservo, 0, pulselen);
	}
	::servo1live = true;
	::servo2live = true;
	refresh();
}


void checkuwp::servo::Womenminslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	::SERVOMINWOMEN = womenminslider->Value;
	refresh();
}


void checkuwp::servo::Womenmaxslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	::SERVOMXWOMEN = womenmaxslider->Value;
	refresh();
}


void checkuwp::servo::Menminslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	::SERVOMINMEN = menminslider->Value;
	refresh();
}


void checkuwp::servo::Menmaxslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	::SERVOMXMEN = menmaxslider->Value;
	refresh();
}

void checkuwp::servo::refresh()
{
	if (::servo1live == true)
	{
		menstatus->Text = "ONLINE";
		menstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Green);
	}
	if (::servo1live == false)
	{
		menstatus->Text = "OFFLINE";
		menstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	}
	if (::servo2live == true)
	{
		womenstatus->Text = "ONLINE";
		womenstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Green);
	}
	if (::servo2live == false)
	{
		womenstatus->Text = "OFFLINE";
		womenstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	}
	menmaxslider->Value = ::SERVOMXMEN;
	menminslider->Value = ::SERVOMINMEN;
	womenmaxslider->Value = ::SERVOMXWOMEN;
	womenminslider->Value = ::SERVOMINWOMEN;
	menmaxinput->Text = ::SERVOMXMEN.ToString();
	menmininput->Text = ::SERVOMINMEN.ToString();
	womenmaxinput->Text = ::SERVOMXWOMEN.ToString();
	womenmininput->Text = ::SERVOMINWOMEN.ToString();
}

void checkuwp::servo::Menmaxinput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	::SERVOMXMEN = ToLong(menmaxinput->Text);
	refresh();
}


void checkuwp::servo::Menmininput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	::SERVOMINMEN = ToLong(menmininput->Text);
	refresh();
}


void checkuwp::servo::Womenmaxinput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	::SERVOMXWOMEN = ToLong(womenmaxinput->Text);
	refresh();
}


void checkuwp::servo::Womenmininput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	::SERVOMINWOMEN = ToLong(womenmininput->Text);
	refresh();
}


void checkuwp::servo::Refreshall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	refresh();
}
