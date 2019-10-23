//
// maindemo.xaml.h
// Declaration of the maindemo class
//

#pragma once

#include "maindemo.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class maindemo sealed
	{
	public:
		maindemo();
	private:
		void _continue_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
