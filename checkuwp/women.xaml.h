//
// women.xaml.h
// Declaration of the women class
//

#pragma once

#include "women.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class women sealed
	{
	public:
		women();
	private:
		void checkoutfunc();
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Confirmbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Nameinput_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs^ args);
		void Nameinput_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
	};
}
