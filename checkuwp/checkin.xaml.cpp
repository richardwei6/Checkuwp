//
// checkin.xaml.cpp
// Implementation of the checkin class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "checkin.xaml.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
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

checkin::checkin()
{
	InitializeComponent();
	if (::ahschecked == false && ::fms1checked == false && ::fms2checked == false && ::dams1checked == false && ::dams2checked == false)
	{
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Visible;
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	if (::demobool == true) {
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->checkbutton3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		checkbutton1->Content = "Your elective & school here | Your name here";
	}
	if (::ahschecked == true && ::fms1checked == true && ::daynum != 3)
	{
		MessageDialog^ msg = ref new MessageDialog("There has been a conflict. AHS Algebra 2 has been checked in.");
		msg->ShowAsync();
		::ahschecked = false;
		::StephanieW = false;
		::CindyL = false;
	}
	if (::ahschecked == true)
	{
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		String ^ content = "Arcadia High School - Algebra 2 | ";
		if (::StephanieW == true)
		{
			content += "Stephanie W ";
		}
		if (::CindyL == true)
		{
			content += "Cindy L ";
		}
		checkbutton1->Content = content;
	}
	if (::fms1checked == true)
	{
		if (::daynum == 3)
		{
			::label3fms = true;
			this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Visible;
			String ^ content = "Foothills Middle School - Band | ";
			if (::ArulK == true)
			{
				content += "Arul K ";
			}
			if (::WeberL == true)
			{
				content += "Weber L ";
			}
			if (::RichardW == true)
			{
				content += "Richard W ";
			}
			checkbutton2->Content = content;
		}
		else {
			::label3fms = true;
			this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
			String ^ content = "Foothills Middle School - Band | ";
			if (::ArulK == true)
			{
				content += "Arul K ";
			}
			if (::WeberL == true)
			{
				content += "Weber L ";
			}
			if (::RichardW == true)
			{
				content += "Richard W ";
			}
			checkbutton1->Content = content;
		}
	}
	if (::fms2checked == true)
	{
		::label4fms = true;
		this->checkbutton1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		String ^ content = "Foothills Middle School - Orchestra | ";
		if (::AnD == true)
		{
			content += "An D ";
		}
		if (::NathanZ == true)
		{
			content += "Nathan Z ";
		}
		checkbutton1->Content = content;
	}
	if (::dams1checked == true)
	{
		if (::daynum == 3)
		{
			::label3dams = true;
			this->checkbutton3->Visibility = Windows::UI::Xaml::Visibility::Visible;
			String ^ content = "Dana - Orchestra | ";
			if (::ShannonC == true)
			{
				content += "Shannon C ";
			}
			if (::ErinL == true)
			{
				content += "Erin L ";
			}
			if (::AuroraC == true)
			{
				content += "Aurora C ";
			}
			if (::CarisO == true)
			{
				content += "Caris O ";
			}
			if (::PresleyN == true)
			{
				content += "Presley N ";
			}
			checkbutton3->Content = content;
		}
		else
		{
			::label3dams = true;
			this->checkbutton2->Visibility = Windows::UI::Xaml::Visibility::Visible;
			String ^ content = "Dana - Orchestra | ";
			if (::ShannonC == true)
			{
				content += "Shannon C ";
			}
			if (::ErinL == true)
			{
				content += "Erin L ";
			}
			if (::AuroraC == true)
			{
				content += "Aurora C ";
			}
			if (::CarisO == true)
			{
				content += "Caris O ";
			}
			if (::PresleyN == true)
			{
				content += "Presley N ";
			}
			checkbutton2->Content = content;
		}
	}
	if (::dams2checked == true)
	{
		::label4dams = true;
		this->checkbutton3->Visibility = Windows::UI::Xaml::Visibility::Visible;
		checkbutton3->Content = "Dana - Drama | Madeline F";
	}
	if (::demobool == false)
	{
		demo1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else {
		demo1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::checkin::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(elective::typeid));
}


void checkuwp::checkin::Checkbutton1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::ahschecked == true)
	{
		::ahschecked = false;
		if (::ahschecked == false)
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
				if (::daynum == 3)
				{
					write += " // AHS checkIN - ^"; // ADD TEXT HERE
				}
				else
				{
					write += " // AHS checkIN - Stephanie W Cindy L";
				}
				concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
			});
			if (::StephanieW == true)
			{
				::StephanieW = false;
			}
			if (::CindyL == true)
			{
				::CindyL = false;
			}
		}
	}
	if (::daynum != 3)
	{
		if (::fms1checked == true)
		{
			::fms1checked = false;
			if (::fms1checked == false)
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
					write += " // FMS band checkIN - ^"; // ADD TEXT HERE
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				if (::ArulK == true)
				{
					::ArulK = false;
				}
				if (::WeberL == true)
				{
					::WeberL = false;
				}
				if (::RichardW == true)
				{
					::RichardW = false;
				}
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
	if (::fms2checked == true)
	{
		::fms2checked = false;
		if (::fms2checked == false)
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
				write += " // FMS orchestra checkIN - ^"; // ADD TEXT HERE
				concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
			});
			if (::AnD == true)
			{
				::AnD = false;
			}
			if (::NathanZ == true)
			{
				::NathanZ = false;
			}
		}
		else
		{
			MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
			msg->ShowAsync();
		}
	}
	if (::demobool) {
		::textbox = "You have successfuly checked out. The program navigates to main menu.";
	}
	::textboxbool = true;
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::checkin::Checkbutton2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::daynum == 3)
	{
		if (::fms1checked == true)
		{
			::fms1checked = false;
			if (::fms1checked == false)
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
					write += " // FMS band checkIN - ^"; // ADD TEXT HERE
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				if (::ArulK == true)
				{
					::ArulK = false;
				}
				if (::WeberL == true)
				{
					::WeberL = false;
				}
				if (::RichardW == true)
				{
					::RichardW = false;
				}
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
	if (::daynum != 3)
	{
		if (::dams1checked == true)
		{
			::dams1checked = false;
			if (::dams1checked == false)
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
					write += " // DAMS orchestra 3 checkIN - ^"; // ADD TEXT HERE
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				if (::ShannonC == true)
				{
					::ShannonC = false;
				}
				if (::ErinL == true)
				{
					::ErinL = false;
				}
				if (::AuroraC == true)
				{
					::AuroraC = false;
				}
				if (::CarisO == true)
				{
					::CarisO = false;
				}
				if (::PresleyN == true)
				{
					::PresleyN = false;
				}
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
	::textboxbool = true;
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void checkuwp::checkin::Checkbutton3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (::dams1checked == true && ::daynum == 3)
	{
		::dams1checked = false;
		if (::dams1checked == false)
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
				write += " // DAMS orchestra 3 checkIN - ^"; // ADD TEXT HERE
				concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
			});
			if (::ShannonC == true)
			{
				::ShannonC = false;
			}
			if (::ErinL == true)
			{
				::ErinL = false;
			}
			if (::AuroraC == true)
			{
				::AuroraC = false;
			}
			if (::CarisO == true)
			{
				::CarisO = false;
			}
			if (::PresleyN == true)
			{
				::PresleyN = false;
			}
		}
		else
		{
			MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
			msg->ShowAsync();
		}
	}
	if (::dams2checked == true)
	{
		::dams2checked = false;
		if (::dams2checked == false)
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
				write += " // DAMS drama checkIN - Maddie F"; // ADD TEXT HERE
				concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
			});
			if (::MaddieF == true)
			{
				::MaddieF = false;
			}
		}
		else
		{
			MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
			msg->ShowAsync();
		}
	}
	::textboxbool = true;
	this->Frame->Navigate(TypeName(MainPage::typeid));
}

