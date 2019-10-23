//
// changelog.xaml.h
// Declaration of the changelog class
//

#pragma once

#include "changelog.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class changelog sealed
	{
	public:
		changelog();
	private:
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
