//
// elective.xaml.h
// Declaration of the elective class
//

#pragma once

#include "elective.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class elective sealed
	{
	public:
		elective();
	private:
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Checkin_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Foothills_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Dana_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Arcadia_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}