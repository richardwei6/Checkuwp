//
// logaccess.xaml.cpp
// Implementation of the logaccess class
//

#include "pch.h"
#include "logaccess.xaml.h"
#include "variable.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "admindata.xaml.h"
#include "servo.xaml.h"
using namespace checkuwp;

using namespace Platform;
using namespace concurrency;
using namespace Windows::Storage;
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
using namespace Streams;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

logaccess::logaccess()
{
	InitializeComponent();
}


void checkuwp::logaccess::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(admin::typeid));
}




void checkuwp::logaccess::Newfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
	create_task(storageFolder->CreateFileAsync("rancholog.txt", CreationCollisionOption::ReplaceExisting));
	MessageDialog^ msg = ref new MessageDialog("You have created a new log file.");
	msg->ShowAsync();
	create_task(storageFolder->GetFileAsync("rancholog.txt")).then([](StorageFile^ log)
	{
		String^ write = nullptr;
		time_t t = time(NULL);
		tm* timePtr = localtime(&t);
		write = (timePtr->tm_mon + 1).ToString();
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
		write += " // Log created";
		create_task(FileIO::WriteTextAsync(log, write));
	});
}


void checkuwp::logaccess::Newsupportfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
	create_task(storageFolder->CreateFileAsync("ranchosupport.txt", CreationCollisionOption::ReplaceExisting));
	MessageDialog^ msg = ref new MessageDialog("You have created a new support file.");
	msg->ShowAsync();
	create_task(storageFolder->GetFileAsync("ranchosupport.txt")).then([](StorageFile^ log)
	{
		String^ write = nullptr;
		time_t t = time(NULL);
		tm* timePtr = localtime(&t);
		write = (timePtr->tm_mon + 1).ToString();
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
		write += " // Support Log created";
		create_task(FileIO::WriteTextAsync(log, write));
	});
}
