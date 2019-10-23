//
// foothills.xaml.cpp
// Implementation of the foothills class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "foothills.xaml.h"
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

foothills::foothills()
{
	InitializeComponent();
	if (::daynum == 3)
	{
		time1->Text = "9:00 am - 10:00 am";
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


void checkuwp::foothills::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(elective::typeid));
}


void checkuwp::foothills::Confirm1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (arulcheck->IsChecked->Equals(true) || webercheck->IsChecked->Equals(true) || richardcheck->IsChecked->Equals(true))
	{
		if (::fms1checked == false)
		{
			::fms1checked = true;
			if (arulcheck->IsChecked->Equals(true))
			{
				::ArulK = true;
			}
			if (webercheck->IsChecked->Equals(true))
			{
				::WeberL = true;
			}
			if (richardcheck->IsChecked->Equals(true))
			{
				::RichardW = true;
			}
			if (::fms1checked == true)
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
					write += " // FMS band checkOUT - ";
					if (::ArulK == true)
					{
						write += "Arul K ";
					}
					if (::WeberL == true)
					{
						write += "Weber L ";
					}
					if (::RichardW == true)
					{
						write += "Richard W ";
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



void checkuwp::foothills::Confirm2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (ancheck->IsChecked->Equals(true) || nathancheck->IsChecked->Equals(true))
	{
		if (::fms2checked == false)
		{
			::fms2checked = true;
			if (ancheck->IsChecked->Equals(true))
			{
				::AnD = true;
			}
			if (nathancheck->IsChecked->Equals(true))
			{
				::NathanZ = true;
			}
			if (::fms2checked == true)
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
					write += " // FMS orchestra checkOUT - ";
					if (::AnD == true)
					{
						write += "An D ";
					}
					if (::NathanZ == true)
					{
						write += "Nathan Z ";
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
