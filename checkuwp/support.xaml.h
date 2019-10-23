//
// support.xaml.h
// Declaration of the support class
//

#pragma once

#include "support.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class support sealed
	{
	public:
		support();
	private:
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Submit_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
