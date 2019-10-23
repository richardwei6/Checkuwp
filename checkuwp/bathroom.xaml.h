//
// bathroom.xaml.h
// Declaration of the bathroom class
//

#pragma once

#include "bathroom.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class bathroom sealed
	{
	public:
		bathroom();
	private:
		void resetmsg();
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Womenbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Menbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkbutton1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkbutton2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
