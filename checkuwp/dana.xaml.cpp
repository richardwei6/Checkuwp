//
// dana.xaml.cpp
// Implementation of the dana class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "dana.xaml.h"
#include "elective.xaml.h"
#include "MainPage.xaml.h"
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

dana::dana()
{
	InitializeComponent();
	switch (::daynum)
	{
	case 1:
		maddietime->Text = "2:00 pm - [Goes home]";
		break;
	case 2:
		maddietime->Text = "1:00 pm - 2:20 pm";
		break;
	case 3:
		maddietime->Text = "9:50 am - 11:00 am";
		break;
	case 4:
		maddietime->Text = "9:30 am - 10:45 am";
		break;
	case 5:
		maddietime->Text = "8:30 am - 9:50 am";
		break;
	default:
		maddietime->Text = "Time not available.";
		break;
	}
	if (::demobool == false)
	{
		demo->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else {
		demo->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::dana::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(elective::typeid));
}


void checkuwp::dana::Confirm1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (shannoncheck->IsChecked->Equals(true) || erincheck->IsChecked->Equals(true) || carischeck->IsChecked->Equals(true) || presleycheck->IsChecked->Equals(true) || auroracheck->IsChecked->Equals(true))
	{
		if (::dams1checked == false)
		{
			::dams1checked = true;
			if (shannoncheck->IsChecked->Equals(true))
			{
				::ShannonC = true;
			}
			if (erincheck->IsChecked->Equals(true))
			{
				::ErinL = true;
			}
			if (auroracheck->IsChecked->Equals(true))
			{
				::AuroraC = true;
			}
			if (carischeck->IsChecked->Equals(true))
			{
				::CarisO = true;
			}
			if (presleycheck->IsChecked->Equals(true))
			{
				::PresleyN = true;
			}
			if (::dams1checked == true)
			{
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
					write += " // DAMS orchestra 3 checkOUT - ";
					if (::ShannonC == true)
					{
						write += "Shannon C ";
					}
					if (::ErinL == true)
					{
						write += "Erin L ";
					}
					if (::AuroraC == true)
					{
						write += "Aurora C ";
					}
					if (::CarisO == true)
					{
						write += "Caris O ";
					}
					if (::PresleyN == true)
					{
						write += "Presley N ";
					}
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				::textboxbool = true;
				this->Frame->Navigate(TypeName(MainPage::typeid));
			}
		}
		else
		{
			MessageDialog^ msg = ref new MessageDialog("Error: This group is already checked out. Try Again.");
			msg->ShowAsync();
		}
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Error: You have not checked anything. Try Again.");
		msg->ShowAsync();
	}
}


void checkuwp::dana::Confirm2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (maddiecheck->IsChecked->Equals(true))
	{
		if (::dams2checked == false)
		{
			::dams2checked = true;
			::MaddieF == true;
			if (::dams2checked == true)
			{
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
					write += " // DAMS drama checkOUT - Maddie F";
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				::textboxbool = true;
				this->Frame->Navigate(TypeName(MainPage::typeid));
			}
		}
		else
		{
			MessageDialog^ msg = ref new MessageDialog("Error: This group is already checked out. Try Again.");
			msg->ShowAsync();
		}
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Error: You have not checked anything. Try Again.");
		msg->ShowAsync();
	}
}
