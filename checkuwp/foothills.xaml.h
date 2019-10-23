//
// foothills.xaml.h
// Declaration of the foothills class
//

#pragma once

#include "foothills.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class foothills sealed
	{
	public:
		foothills();
	private:
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Confirm1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Confirm2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
