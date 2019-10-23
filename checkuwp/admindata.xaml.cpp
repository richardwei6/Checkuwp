//
// admindata.xaml.cpp
// Implementation of the admindata class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "admindata.xaml.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "variable.h"
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
bool fms1 = false;
bool fms2 = false;
bool ahs = false;
bool dams1 = false;
bool dams2 = false;

void checkuwp::admindata::reset()
{
fms1 = false;
fms2 = false;
ahs = false;
dams1 = false;
dams2 = false;
}

admindata::admindata()
{
	InitializeComponent();
	reset();
	this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}


void checkuwp::admindata::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(admin::typeid));
}


void checkuwp::admindata::Foothills_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	reset();
	this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Visible;
	schoolname->Text = "Foothills";
	this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	if (::fms1checked == true)
	{
		fms1 = true;
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->content1->Visibility = Windows::UI::Xaml::Visibility::Visible;
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
		content1->Content = content;
	}
	if (::fms2checked == true)
	{
		fms2 = true;
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->content2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		String ^ content = "Foothills Middle School - Orchestra | ";
		if (::AnD == true)
		{
			content += "An D ";
		}
		if (::NathanZ == true)
		{
			content += "Nathan Z ";
		}
		content2->Content = content;
	}
	if (::fms1checked == false && ::fms2checked == false)
	{
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::admindata::Dana_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	reset();
	this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Visible;
	schoolname->Text = "Dana";
	this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	if (::dams1checked == true)
	{
		dams1 = true;
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->content1->Visibility = Windows::UI::Xaml::Visibility::Visible;
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
		content1->Content = content;
	}
	if (::dams2checked == true)
	{
		dams2 = true;
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->content2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		content2->Content = "Dana - Drama | Madeline F";
	}
	if (::dams1checked == false && ::dams2checked == false)
	{
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::admindata::Arcadia_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	reset();
	this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Visible;
	schoolname->Text = "Arcadia High";
	this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	if (::ahschecked == true)
	{
		ahs = true;
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		this->content1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		String ^ content = "Arcadia High School - Algebra 2 | ";
		if (::StephanieW == true)
		{
			content += "Stephanie W ";
		}
		if (::CindyL == true)
		{
			content += "Cindy L ";
		}
		content1->Content = content;
	}
	if (::ahschecked == false)
	{
		this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void checkuwp::admindata::Content1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (fms1 == true)
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
					write += " // ADMIN FMS band checkIN - ^"; // ADD TEXT HERE
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
				MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
				msg->ShowAsync();
				this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
	if (ahs = true)
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
						write += " // ADMIN AHS checkIN - ^"; // ADD TEXT HERE
					}
					else
					{
						write += " // ADMIN AHS checkIN - Stephanie W Cindy L";
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
				MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
				msg->ShowAsync();
				this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			}
		}
	}
	if (dams1 = true)
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
					write += " // ADMIN DAMS orchestra 3 checkIN - ^"; // ADD TEXT HERE
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
				MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
				msg->ShowAsync();
				this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
}


void checkuwp::admindata::Content2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (fms2 == true)
	{
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
					write += " // ADMIN FMS orchestra checkIN - ^"; // ADD TEXT HERE
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
				MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
				msg->ShowAsync();
				this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
	if (dams2 == true)
	{
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
					write += " // ADMIN DAMS drama checkIN - Maddie F"; // ADD TEXT HERE
					concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
				});
				if (::MaddieF == true)
				{
					::MaddieF = false;
				}
				MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
				msg->ShowAsync();
				this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
				this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			}
			else
			{
				MessageDialog^ msg = ref new MessageDialog("An error has occurred. Please notify the Logbot team or create a support ticket in the Main Menu.");
				msg->ShowAsync();
			}
		}
	}
}



void checkuwp::admindata::Resetall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// ahs
	::ahschecked = false;
	::StephanieW = false;
	::CindyL = false;
	//
	// fms
	::fms1checked = false;
	::ArulK = false;
	::RichardW = false;
	::WeberL = false;
	//
	::fms2checked = false;
	::AnD = false;
	::NathanZ = false;
	//
	// dams
	::dams1checked = false;
	::ShannonC = false;
	::ErinL = false;
	::AuroraC = false;
	::CarisO = false;
	::PresleyN = false;
	//
	::dams2checked = false;
	::MaddieF = false;
	//End elective list
	MessageDialog^ msg = ref new MessageDialog("Your actions have been recorded.");
	msg->ShowAsync();
	this->schoolname->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->content2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	this->nochecktext->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}
