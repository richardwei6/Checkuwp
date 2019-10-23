//
// admin.xaml.cpp
// Implementation of the admin class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "variable.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "admindata.xaml.h"
#include "servo.xaml.h"
#include "logaccess.xaml.h"
#include "maindemo.xaml.h"
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
String ^ notesstring;
admin::admin()
{
	InitializeComponent();
	for each(auto LocalHostName in Windows::Networking::Connectivity::NetworkInformation::GetHostNames())
	{

		if (LocalHostName->IPInformation)
		{

			if (LocalHostName->Type == (Windows::Networking::HostNameType::Ipv4))
			{
				ipaddress->Text = LocalHostName->ToString();
				String^ windash = "https://";
				windash += LocalHostName->ToString();
				windash += ":8080";
				windashtext->Text = windash;
				break;
			}

		}
	}
	::uptime = (clock() / (double)CLOCKS_PER_SEC);
	uptimetext->Text += ::uptime;
	user->Text = "[Hidden]";
	password->Text = "[Hidden]";
	this->submit->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->notes->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	StartTimerAndRegisterHandler();
	if (::demobool == true)
	{
		demomode->IsChecked = true;
	}
	else {
		demobutton->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}


void checkuwp::admin::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &admin::OnTick);
}

void checkuwp::admin::OnTick(Object^ sender, Object^ e) {
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
	::uptime = (clock() / (double)CLOCKS_PER_SEC);
	if (::uptime < 60)
	{
		uptimetext->Text = ::uptime.ToString();
		uptimetext->Text += " seconds";
	}
	if (::uptime >= 60 && ::uptime < 3600)
	{
		::uptime /= 60;
		uptimetext->Text = ::uptime.ToString();
		if (::uptime == 1)
		{
			uptimetext->Text += " minute";
		}
		else 
		{
			uptimetext->Text += " minutes";
		}
	}
	if (::uptime >= 3600)
	{
		::uptime /= 3600;
		uptimetext->Text = ::uptime.ToString();
		if (::uptime == 1)
		{
			uptimetext->Text += " hour";
		}
		else
		{
			uptimetext->Text += " hours";
		}
	}
}

void checkuwp::admin::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::admin::Bathbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Application::Current->Exit();
}


void checkuwp::admin::Admindata_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(admindata::typeid));
}


void checkuwp::admin::Showuserpass_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	user->Text = "[Hidden]";
	password->Text = "[Hidden]";
}


void checkuwp::admin::Showuserpass_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	user->Text = "administrator";
	password->Text = "password";
}


void checkuwp::admin::Servoreset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(servo::typeid));
}


void checkuwp::admin::Logaccess_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(logaccess::typeid));
}


void checkuwp::admin::Submit_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (notes->Text != nullptr)
	{
		notesstring = notes->Text;
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
			write += " // ADMIN NOTES - '";
			write += notesstring + "' ";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
		notes->Text = nullptr;
		this->submit->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->notes->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->uptimetext->Visibility = Windows::UI::Xaml::Visibility::Visible;
		this->textuptime->Visibility = Windows::UI::Xaml::Visibility::Visible;
		shownotes->IsChecked=false;
		MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
		msg->ShowAsync();
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("You have not entered anything.");
		msg->ShowAsync();
	}
}


void checkuwp::admin::Shownotes_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->submit->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->notes->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->uptimetext->Visibility = Windows::UI::Xaml::Visibility::Visible;
	this->textuptime->Visibility = Windows::UI::Xaml::Visibility::Visible;
}


void checkuwp::admin::Shownotes_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->submit->Visibility = Windows::UI::Xaml::Visibility::Visible;
	this->notes->Visibility = Windows::UI::Xaml::Visibility::Visible;
	this->uptimetext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->textuptime->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}


void checkuwp::admin::Demomode_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	demobutton->Visibility = Windows::UI::Xaml::Visibility::Visible;
	concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile ^ log)
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
			write += " // DEMO START - Data may be incorrect.";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
	::demobool = true;
}


void checkuwp::admin::Demomode_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	demobutton->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile ^ log)
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
			write += " // DEMO END";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
	::demobool = false;
}


void checkuwp::admin::Demobutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::demobool == true)
	{
		this->Frame->Navigate(TypeName(maindemo::typeid));
	}
	else {
		MessageDialog^ msg = ref new MessageDialog("Not in demo mode.");
		msg->ShowAsync();
	}
}
