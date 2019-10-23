//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
namespace checkuwp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void textboxclear();
		void Quicklistrefresh();
		void Electivebutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Bathbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Adminbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Versiontext_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Custombutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Supportbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showquicklistelectives_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showquicklistelectives_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showquicklistbathroom_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Showquicklistbathroom_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
