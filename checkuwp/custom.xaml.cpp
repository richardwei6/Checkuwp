//
// custom.xaml.cpp
// Implementation of the custom class
//

#include "pch.h"
#include "custom.xaml.h"
#include "MainPage.xaml.h"
#include "variable.h"

using namespace checkuwp;

using namespace Windows::Storage;
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
String ^ namestring;
String ^ reasonstring;
bool returnlater;
custom::custom()
{
	InitializeComponent();
	StartTimerAndRegisterHandler();
}

void checkuwp::custom::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &custom::OnTick);
}

void checkuwp::custom::OnTick(Object^ sender, Object^ e) {
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


void checkuwp::custom::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::custom::Confirmbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (namein->Text != nullptr && reason->Text != nullptr && (yesreturn->IsChecked->Equals(true) || noreturn->IsChecked->Equals(true)))
	{
		namestring = namein->Text;
		reasonstring = reason->Text;
		if (yesreturn->IsChecked->Equals(true))
		{
			returnlater = true;
		}
		else
		{
			returnlater = false;
		}
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
			write += " // Custom checkOUT - "; // ADD TEXT HERE
			write += namestring + " - '";
			write += reasonstring + "' - ";
			if (returnlater == true)
			{
				write += "Is returning - True";
			}
			else
			{
				write += "Is returning - False";
			}
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
		::textboxbool = true;
		this->Frame->Navigate(TypeName(MainPage::typeid));
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("You may not have completed one or more boxes. Please go back and try again.");
		msg->ShowAsync();
	}
}


void checkuwp::custom::Warningrestart_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}
