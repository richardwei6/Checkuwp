//
// bathroom.xaml.cpp
// Implementation of the bathroom class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "men.xaml.h"
#include "women.xaml.h"
#include "variable.h"
#include <cmath>
using namespace checkuwp;

using namespace Platform;
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
String^ success = "You've checked back in. Return your key. Your time was: ";
String ^ menstringtime;
String ^ womenstringtime;
bathroom::bathroom()
{
	InitializeComponent();
	this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	if (::menbath == true)
	{
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		checkbutton1->Content = menname;
	}
	if (::womenbath == true)
	{
		this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		checkbutton2->Content = womenname;
	}
	StartTimerAndRegisterHandler();
	if (::demobool == false)
	{
		demo5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else {
		if (::menbath == false)
		{
			this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
			checkbutton1->Content = "Your name here";
		}
		demo5->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}

void checkuwp::bathroom::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &bathroom::OnTick);
}

void checkuwp::bathroom::OnTick(Object^ sender, Object^ e) {
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

float float_one_point_round(float value)
{
	return ((float)((int)(value * 10))) / 10;
}

void checkuwp::bathroom::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::bathroom::Womenbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::womenbath == false)
	{
		this->Frame->Navigate(TypeName(women::typeid));
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Someone has already checked out. Please wait for them to return.");
		msg->ShowAsync();
	}
}


void checkuwp::bathroom::Menbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::menbath == false)
	{
		this->Frame->Navigate(TypeName(men::typeid));
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Someone has already checked out. Please wait for them to return.");
		msg->ShowAsync();
	}
}

void checkuwp::bathroom::resetmsg()
{
	success = "You've checked back in. Return your key. Your time was: ";
}

void checkuwp::bathroom::Checkbutton1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::menbath == true)
	{
		::menbath = false;
		::mentime = (clock() - ::mentime)/ (double)CLOCKS_PER_SEC;
		::mentime = float_one_point_round(::mentime);
		if (::mentime <= 60)
		{
			success += ::mentime.ToString();
			success += " seconds.";
			menstringtime += ::mentime.ToString();
			menstringtime += " seconds.";
		}
		else
		{
			::mentime /= 60;
			success += ::mentime.ToString();
			success += " minutes.";
			menstringtime += ::mentime.ToString();
			menstringtime += " minutes.";
		}
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile^ log)
		{
			String^ write = nullptr;
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
			write += " // Men bathroom check-IN - ";
			write += menstringtime;
			write += " - ^";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
		::textboxbool = true;
		::textbox = success;
		menstringtime = nullptr;
		resetmsg();
		this->Frame->Navigate(TypeName(MainPage::typeid));
	}
	else if (::demobool == true){
		::textboxbool = true;
		::textbox = "You've checked in. Program navigates to main menu.";
		this->Frame->Navigate(TypeName(MainPage::typeid));
	}
}


void checkuwp::bathroom::Checkbutton2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::womenbath == true)
	{
		::womenbath = false;
		::womentime = (clock() - ::womentime) / (double)CLOCKS_PER_SEC;
		::womentime = float_one_point_round(::womentime);
		if (::womentime <= 60)
		{
			success += ::womentime.ToString();
			success += " seconds.";
			womenstringtime += ::womentime.ToString();
			womenstringtime += " seconds.";
		}
		else
		{
			::womentime /= 60;
			success += ::womentime.ToString();
			success += " minutes.";
			womenstringtime += ::womentime.ToString();
			womenstringtime += " minutes.";
		}
		this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile^ log)
		{
			String^ write = nullptr;
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
			write += " // Women bathroom check-IN - ";
			write += womenstringtime;
			write += " - ^";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
		::textboxbool = true;
		::textbox = success;
		resetmsg();
		womenstringtime = nullptr;
		this->Frame->Navigate(TypeName(MainPage::typeid));
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("ERROR: This is a bug. Please let Richard know.");
		msg->ShowAsync();
	}
}
