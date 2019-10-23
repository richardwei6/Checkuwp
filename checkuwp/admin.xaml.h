//
// admin.xaml.h
// Declaration of the admin class
//

#pragma once

#include "admin.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class admin sealed
	{
	public:
		admin();
	private:
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Bathbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Admindata_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showuserpass_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showuserpass_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Servoreset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Logaccess_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Submit_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Shownotes_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Shownotes_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Demomode_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Demomode_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Demobutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
