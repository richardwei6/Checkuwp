//
// checkin.xaml.h
// Declaration of the checkin class
//

#pragma once

#include "checkin.g.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class checkin sealed
	{
	public:
		checkin();
	private:
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkbutton1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkbutton2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkbutton3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
