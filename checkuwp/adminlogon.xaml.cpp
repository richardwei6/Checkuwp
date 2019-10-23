//
// adminlogon.xaml.cpp
// Implementation of the adminlogon class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "adminlogon.xaml.h"
#include "MainPage.g.h"
#include "admin.xaml.h"
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
adminlogon::adminlogon()
{
	InitializeComponent();
}

void checkuwp::adminlogon::login() {
	if (passinput->Password != nullptr)
	{
		if (::passtry <= 3)
		{
			if (passinput->Password == adminpass)
			{
				::passtry = 0;
				::passtrytime = 0;
				::triesleft = 4;
				logadd();
				this->Frame->Navigate(TypeName(admin::typeid));
			}
			else
			{
				statusbox->Text = "Password incorrect. Try Again. ";
				statusbox->Text += triesleft.ToString();
				statusbox->Text += " tries left.";
				::passtry = ::passtry + 1;
				::triesleft = ::triesleft - 1;
			}
		}
		else
		{
			::passtrytime = clock();
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
					write += " // Admin Log in FAIL";
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
			::textboxbool = true;
			::textbox = "You have exceeded five tries. Please wait 5 minutes before trying again.";
			this->Frame->Navigate(TypeName(MainPage::typeid));
		}
	}
	else
	{
		statusbox->Text = "You have not entered any characters. Please try again.";
	}
}

void checkuwp::adminlogon::logadd() {
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
			write += " // Admin Log in success";
			concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
		});
}

void checkuwp::adminlogon::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::adminlogon::Passinput_PasswordChanged_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	statusbox->Text = "";
	if (passinput->Password == adminpass)
	{
		::passtry = 0;
		::passtrytime = 0;
		triesleft = 4;
		logadd();
		this->Frame->Navigate(TypeName(admin::typeid));
	}
}


void checkuwp::adminlogon::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	login();
}


void checkuwp::adminlogon::RevealModeCheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	passinput->PasswordRevealMode = PasswordRevealMode::Visible;
}


void checkuwp::adminlogon::RevealModeCheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	passinput->PasswordRevealMode = PasswordRevealMode::Hidden;
}


void checkuwp::adminlogon::Passinput_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		login();
	}
}
