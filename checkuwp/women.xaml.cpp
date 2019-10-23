//
// women.xaml.cpp
// Implementation of the women class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "women.xaml.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "variable.h"
#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"

using namespace checkuwp;

using namespace Platform;
using namespace Windows::Devices::Gpio;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Popups;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238
Adafruit_PWMServoDriver servo2 = Adafruit_PWMServoDriver();//ardino code
//#define SERVOMIN  310 // this is the 'minimum' pulse length count (out of 4096) //ardino code 300
//#define SERVOMAX  1100 // this is the 'maximum' pulse length count (out of 4096) //ardino code 900
bool setservo2 = false;
women::women()
{
	InitializeComponent();
	if (setservo2 == false)
	{
		servo2.begin();
		servo2.setPWMFreq(60);
		::servo2live = true;
		setservo2 = true;
	}
	if (::servo2live == true)
	{
		servosysstatus->Text = "ONLINE";
		servosysstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Green);
	}
	if (::servo2live == false)
	{
		servosysstatus->Text = "OFFLINE";
		servosysstatus->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	}
	StartTimerAndRegisterHandler();
	if (::demobool == false)
	{
		demo1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else {
		demo1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::women::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &women::OnTick);
}

void checkuwp::women::OnTick(Object^ sender, Object^ e) {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	timetext->Text = (timePtr->tm_mon + 1).ToString();
	timetext->Text += "/";
	timetext->Text += timePtr->tm_mday.ToString();
	timetext->Text += "/";
	timetext->Text += ((timePtr->tm_year) + 1900).ToString();
	timetext->Text += " | ";
	if (timePtr->tm_hour <= 12)
	{
		timetext->Text += ((timePtr->tm_hour)).ToString();
	}
	else
	{
		timetext->Text += ((timePtr->tm_hour) - 12).ToString();
	}
	timetext->Text += ":";
	if (log10(timePtr->tm_min) + 1 < 2)
	{
		timetext->Text += "0";
		timetext->Text += timePtr->tm_min.ToString();
	}
	else
	{
		timetext->Text += timePtr->tm_min.ToString();
	}
	if (timePtr->tm_hour < 12)
	{
		timetext->Text += " AM";
	}
	else
	{
		timetext->Text += " PM";
	}
	::daynum = timePtr->tm_wday;
	switch (::daynum)
	{
	case 1:
		timetext->Text += " | Monday";
		break;
	case 2:
		timetext->Text += " | Tuesday";
		break;
	case 3:
		timetext->Text += " | Wednesday";
		break;
	case 4:
		timetext->Text += " | Thursday";
		break;
	case 5:
		timetext->Text += " | Friday";
		break;
	case 6:
		timetext->Text += " | Saturday";
		break;
	case 0:
		timetext->Text += " | Sunday";
		break;
	default:
		timetext->Text = nullptr;
		break;
	}
}

void checkuwp::women::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(bathroom::typeid));
}

void checkuwp::women::checkoutfunc() {
	if (nameinput->Text != nullptr)
	{
		if (nameinput->Text->Length() < 13)
		{
			::womenbath = true;
			::womentime = clock();
			for (uint16_t pulselen = ::SERVOMXWOMEN; pulselen > ::SERVOMINWOMEN; pulselen--) {
				servo2.setPWM(::womenservo, 0, pulselen);
			}
			womenname = nameinput->Text;
			concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile ^ log)
				{
					Platform::String^ write = nullptr;
					time_t t = time(NULL);
					tm* timePtr = localtime(&t);
					write += (timePtr->tm_mon + 1).ToString();
					write += "/";
					write += timePtr->tm_mday.ToString();
					write += "/";
					write += ((timePtr->tm_year) + 1900).ToString();
					write += " // ";
					write += timePtr->tm_hour.ToString();
					write += ":";
					if (log10(timePtr->tm_min) + 1 < 2)
					{
						write += "0";
						write += timePtr->tm_min.ToString();
					}
					else
					{
						write += timePtr->tm_min.ToString();
					}
					write += " // Women bathroom - "; // ADD TEXT HERE
					write += womenname;
					write += " - check-OUT";
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
			womensetup = true;
			nameinput->Text = nullptr;
			::textbox = "Your actions have been recorded, " + womenname + ". Your time has started.";
			::textboxbool = true;
			this->Frame->Navigate(TypeName(MainPage::typeid));
		}
		else {
			MessageDialog^ msg1 = ref new MessageDialog("You have entered too many characters. Try again.");
			msg1->ShowAsync();
		}
	}
	else
	{
		MessageDialog^ msg1 = ref new MessageDialog("You have not entered any characters. Try again.");
		msg1->ShowAsync();
	}
}

void checkuwp::women::Confirmbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	checkoutfunc();
}


void checkuwp::women::Nameinput_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs^ args)
{

}


void checkuwp::women::Nameinput_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		checkoutfunc();
	}
}


