//
// changelog.xaml.cpp
// Implementation of the changelog class
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "changelog.xaml.h"
#include "MainPage.xaml.h"
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

changelog::changelog()
{
	InitializeComponent();
}


void checkuwp::changelog::Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}
