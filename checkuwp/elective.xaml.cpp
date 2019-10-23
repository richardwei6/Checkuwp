//
// elective.xaml.cpp
// Implementation of the elective class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "elective.xaml.h"
#include "MainPage.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "checkin.xaml.h"
#include "ahs.xaml.h"
#include "dana.xaml.h"
#include "elective.xaml.h"
#include "foothills.xaml.h"
#include "variable.h"
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

elective::elective()
{
	InitializeComponent();
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

void checkuwp::elective::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &elective::OnTick);
}

void checkuwp::elective::OnTick(Object^ sender, Object^ e) {
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

void checkuwp::elective::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::elective::Checkin_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(checkin::typeid));
}


void checkuwp::elective::Foothills_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(foothills::typeid));
}


void checkuwp::elective::Dana_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(dana::typeid));
}


void checkuwp::elective::Arcadia_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::ahschecked == false)
	{
		this->Frame->Navigate(TypeName(ahs::typeid));
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Error: This group is already checked out. Try again.");
		msg->ShowAsync();
	}
}
