//
// ahs.xaml.cpp
// Implementation of the ahs class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "ahs.xaml.h"
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

ahs::ahs()
{
	InitializeComponent();
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


void checkuwp::ahs::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(elective::typeid));
}


void checkuwp::ahs::Confirm1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (stephaniecheck->IsChecked->Equals(true) || cindycheck->IsChecked->Equals(true))
	{
		if (::ahschecked == false)
		{
			::ahschecked = true;
			if (stephaniecheck->IsChecked->Equals(true))
			{
				::StephanieW = true;
			}
			if (cindycheck->IsChecked->Equals(true))
			{
				::CindyL = true;
			}
			if (::ahschecked == true)
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
					write += " // AHS checkOUT - ";
					if (::StephanieW == true)
					{
						write += "Stephanie W ";
					}
					if (::CindyL == true)
					{
						write += "Cindy L ";
					}
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				::textboxbool = true;
				this->Frame->Navigate(TypeName(MainPage::typeid));
			}
		}
	}
	else
	{
		MessageDialog^ msg = ref new MessageDialog("Error: You have not checked anything. Try Again.");
		msg->ShowAsync();
	}
}
