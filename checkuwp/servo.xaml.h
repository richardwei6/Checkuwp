//
// servo.xaml.h
// Declaration of the servo class
//

#pragma once

#include "servo.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class servo sealed
	{
	public:
		servo();
	private:
		void refresh();
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Servomenon_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Resetall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Servowomenon_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TextBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Resetdefault_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Womenminslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void Womenmaxslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void Menminslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void Menmaxslider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void Refresh_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Refreshbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Menmaxinput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void Menmininput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void Womenmaxinput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void Womenmininput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void Refreshall_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
