//
// logaccess.xaml.h
// Declaration of the logaccess class
//

#pragma once

#include "logaccess.g.h"

namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class logaccess sealed
	{
	public:
		logaccess();
	private:
		void Backbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Newfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Newsupportfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
