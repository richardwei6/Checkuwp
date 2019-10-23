//
// admindata.xaml.h
// Declaration of the admindata class
//

#pragma once

#include "admindata.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class admindata sealed
	{
	public:
		admindata();
	private:
		void reset();
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Foothills_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Dana_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Arcadia_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Content1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Content2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Resetall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
