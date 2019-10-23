//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "MainPage.xaml.h"
#include "elective.xaml.h"
#include "admin.xaml.h"
#include "bathroom.xaml.h"
#include "checkin.xaml.h"
#include "adminlogon.xaml.h"
#include "changelog.xaml.h"
#include "custom.xaml.h"
#include "variable.h"
#include "support.xaml.h"
#include <sysinfoapi.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <cstdio>
#include <thread>
#include <chrono>
#include <stdio.h> 
#include <stdlib.h> 
#include <cmath>
#include <fstream>
#include <Wire.h>//ardino code
#include "Adafruit_PWMServoDriver.h"//ardino code
using namespace checkuwp;

using namespace concurrency;
using namespace Windows::Devices::I2c;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Gpio;
using namespace Windows::Storage;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Popups;

bool demobool = false;

Platform::String^ adminpass = "logbotadmin";
Platform::String^ menname = nullptr;
Platform::String^ womenname = nullptr;
Platform::String^ textbox = nullptr;
bool textboxbool = false;
//
bool mensetup = false;
bool womensetup = false;
int SERVOMINWOMEN = 310;
int SERVOMXWOMEN = 1651;
int SERVOMINMEN = 275;
int SERVOMXMEN = 1651;
int supportticket = 0;
int triesleft = 4;
int uptime = 0;
int menservo = 0;
int womenservo = 1;
int passtrytime = 0;
int passtry = 0;
int daynum = 0;
double mentime = 0;
double womentime = 0;
bool servo1live = false;
bool servo2live = false;
bool womenbath = false;
bool menbath = false;
bool dayvarset = false;
//Start elective list
//
// ahs
bool ahschecked = true;
bool StephanieW = true;
bool CindyL = true;
//
// fms
bool fms1checked = false;
bool ArulK = false;
bool RichardW = false;
bool WeberL = false;
//
bool fms2checked = false;
bool AnD = false;
bool NathanZ = false;
//
// dams
bool dams1checked = false;
bool ShannonC = false;
bool ErinL = false;
bool AuroraC = false;
bool CarisO = false;
bool PresleyN = false;
//
bool dams2checked = false;
bool MaddieF = false;
//End elective list
bool label3fms = false;
bool label3dams = false;
bool label4fms = false;
bool label4dams = false;

//
int textboxtime = 0;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409


/*!
	@brief  Instantiates a new PCA9685 PWM driver chip with the I2C address on the Wire interface. On Due we use Wire1 since its the interface on the 'default' I2C pins.
	@param  addr The 7-bit I2C address to locate this chip, default is 0x40
*/
/**************************************************************************/
Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(uint8_t addr) {
	_i2caddr = addr;

#if defined(ARDUINO_SAM_DUE)
	_i2c = &Wire1;
#else
	_i2c = &Wire;
#endif
}


/*!
	@brief  Instantiates a new PCA9685 PWM driver chip with the I2C address on a TwoWire interface
	@param  i2c  A pointer to a 'Wire' compatible object that we'll use to communicate with
	@param  addr The 7-bit I2C address to locate this chip, default is 0x40
*/
/**************************************************************************/
Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(TwoWire *i2c, uint8_t addr) {
	_i2c = i2c;
	_i2caddr = addr;
}

/**************************************************************************/
/*!
	@brief  Setups the I2C interface and hardware
*/
/**************************************************************************/
void Adafruit_PWMServoDriver::begin(void) {
	_i2c->begin();
	reset();
	// set a default frequency
	setPWMFreq(1000);
}


/**************************************************************************/
/*!
	@brief  Sends a reset command to the PCA9685 chip over I2C
*/
/**************************************************************************/
void Adafruit_PWMServoDriver::reset(void) {
	write8(PCA9685_MODE1, 0x80);
	delay(10);
}

/**************************************************************************/
/*!
	@brief  Sets the PWM frequency for the entire chip, up to ~1.6 KHz
	@param  freq Floating point frequency that we will attempt to match
*/
/**************************************************************************/
void Adafruit_PWMServoDriver::setPWMFreq(float freq) {
#ifdef ENABLE_DEBUG_OUTPUT
	Serial.print("Attempting to set freq ");
	Serial.println(freq);
#endif

	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;

#ifdef ENABLE_DEBUG_OUTPUT
	Serial.print("Estimated pre-scale: "); Serial.println(prescaleval);
#endif

	uint8_t prescale = floor(prescaleval + 0.5);
#ifdef ENABLE_DEBUG_OUTPUT
	Serial.print("Final pre-scale: "); Serial.println(prescale);
#endif

	uint8_t oldmode = read8(PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	delay(5);
	write8(PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.

#ifdef ENABLE_DEBUG_OUTPUT
	Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
#endif
}

/**************************************************************************/
/*!
	@brief  Sets the PWM output of one of the PCA9685 pins
	@param  num One of the PWM output pins, from 0 to 15
	@param  on At what point in the 4096-part cycle to turn the PWM output ON
	@param  off At what point in the 4096-part cycle to turn the PWM output OFF
*/
/**************************************************************************/
void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
#ifdef ENABLE_DEBUG_OUTPUT
	Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
#endif

	_i2c->beginTransmission(_i2caddr);
	_i2c->write(LED0_ON_L + 4 * num);
	_i2c->write(on);
	_i2c->write(on >> 8);
	_i2c->write(off);
	_i2c->write(off >> 8);
	_i2c->endTransmission();
}

/**************************************************************************/
/*!
	@brief  Helper to set pin PWM output. Sets pin without having to deal with on/off tick placement and properly handles a zero value as completely off and 4095 as completely on.  Optional invert parameter supports inverting the pulse for sinking to ground.
	@param  num One of the PWM output pins, from 0 to 15
	@param  val The number of ticks out of 4096 to be active, should be a value from 0 to 4095 inclusive.
	@param  invert If true, inverts the output, defaults to 'false'
*/
/**************************************************************************/
void Adafruit_PWMServoDriver::setPin(uint8_t num, uint16_t val, bool invert)
{
	// Clamp value between 0 and 4095 inclusive.
	val = min(val, (uint16_t)4095);
	if (invert) {
		if (val == 0) {
			// Special value for signal fully on.
			setPWM(num, 4096, 0);
		}
		else if (val == 4095) {
			// Special value for signal fully off.
			setPWM(num, 0, 4096);
		}
		else {
			setPWM(num, 0, 4095 - val);
		}
	}
	else {
		if (val == 4095) {
			// Special value for signal fully on.
			setPWM(num, 4096, 0);
		}
		else if (val == 0) {
			// Special value for signal fully off.
			setPWM(num, 0, 4096);
		}
		else {
			setPWM(num, 0, val);
		}
	}
}

/*******************************************************************************************/


uint8_t Adafruit_PWMServoDriver::read8(uint8_t addr) {
	_i2c->beginTransmission(_i2caddr);
	_i2c->write(addr);
	_i2c->endTransmission();

	_i2c->requestFrom((uint8_t)_i2caddr, (uint8_t)1);
	return _i2c->read();
}

void Adafruit_PWMServoDriver::write8(uint8_t addr, uint8_t d) {
	_i2c->beginTransmission(_i2caddr);
	_i2c->write(addr);
	_i2c->write(d);
	_i2c->endTransmission();
}

MainPage::MainPage()
{
	StartTimerAndRegisterHandler();
	InitializeComponent();
	if (::demobool == true)
	{
		::ahschecked = false;
		::StephanieW = false;
		::CindyL = false;
	}
	else if (::daynum == 3 && ::dayvarset == false)
	{
		::dayvarset = true;
		::ahschecked = false;
		::StephanieW = false;
		::CindyL = false;
	}
	quicklistbathroom->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	quicklistelectives->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	Quicklistrefresh();
	if (::demobool == false)
	{
		demo->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else {
		demo->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo3->Visibility = Windows::UI::Xaml::Visibility::Visible;
		demo4->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void MainPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (dynamic_cast<Platform::String^>(e->Parameter) != nullptr)
	{
		if (::womenbath == true && womensetup == true) {
			womenname = e->Parameter->ToString();
			womensetup = false;
		}
		if (::menbath == true && mensetup == true) {
			menname = e->Parameter->ToString();
			mensetup = false;
		}
	}
	if (::textboxbool == true)
	{
		if (::textbox == nullptr)
		{
			textboxtext->Text = "Your actions have been recorded.";
		}
		else
		{
			textboxtext->Text = ::textbox;
		}
		::textbox = nullptr;
	}
	::Windows::UI::Xaml::Controls::Page::OnNavigatedTo(e);
}

void checkuwp::MainPage::Quicklistrefresh() {
	if (::ahschecked == false && ::fms1checked == false && ::fms2checked == false && ::dams1checked == false && ::dams2checked == false)
	{
		quicklistelectives->Text += "\n No one is currently checked out.";
	}
	if (::ahschecked == true)
	{
		quicklistelectives->Text += "\n AHS Alg 2 ";
		if (::StephanieW == true)
		{
			quicklistelectives->Text += "Steph. W ";
		}
		if (::CindyL == true)
		{
			quicklistelectives->Text += "Cindy L ";
		}
	}
	if (::fms1checked == true)
	{
		quicklistelectives->Text += "\n FMS Band ";
		if (::ArulK == true)
		{
			quicklistelectives->Text += "Arul K ";
		}
		if (::WeberL == true)
		{
			quicklistelectives->Text += "Web. L ";
		}
		if (::RichardW == true)
		{
			quicklistelectives->Text += "Rich. W ";
		}
	}
	if (::fms2checked == true)
	{
		quicklistelectives->Text += "\n FMS Orch ";
		if (::AnD == true)
		{
			quicklistelectives->Text += "An D ";
		}
		if (::NathanZ == true)
		{
			quicklistelectives->Text += "Nath. Z ";
		}
	}
	if (::dams1checked == true)
	{
		quicklistelectives->Text += "\n Dana Orch ";
		if (::ShannonC == true)
		{
			quicklistelectives->Text += "Shan. C ";
		}
		if (::ErinL == true)
		{
			quicklistelectives->Text += "Erin. L ";
		}
		if (::AuroraC == true)
		{
			quicklistelectives->Text += "Aur. C ";
		}
		if (::CarisO == true)
		{
			quicklistelectives->Text += "Car. O ";
		}
		if (::PresleyN == true)
		{
			quicklistelectives->Text += "Pres. N ";
		}
	}
	if (::dams2checked == true)
	{
		quicklistelectives->Text += "\n Dana Drama Maddie F";
	}
	if (::menbath == false && ::womenbath == false)
	{
		quicklistbathroom->Text += "\n No one is currently checked out.";
	}
	if (::menbath == true)
	{
		quicklistbathroom->Text += "\n Men's - " + menname;
	}
	if (::womenbath == true)
	{
		quicklistbathroom->Text += "\n Women's - " + womenname;
	}
}

void checkuwp::MainPage::StartTimerAndRegisterHandler() {
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTick);
}

void checkuwp::MainPage::OnTick(Object^ sender, Object^ e) {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	timetext->Text = (timePtr->tm_mon + 1).ToString();
	timetext->Text += "/";
	timetext->Text += timePtr->tm_mday.ToString();
	timetext->Text += "/";
	timetext->Text += ((timePtr->tm_year) + 1900).ToString();
	timetext->Text += " | ";
	if (timePtr->tm_hour <= 12)
	{
		timetext->Text += ((timePtr->tm_hour)).ToString();
	}
	else
	{
		timetext->Text += ((timePtr->tm_hour) - 12).ToString();
	}
	timetext->Text += ":";
	if (log10(timePtr->tm_min) + 1 < 2)
	{
		timetext->Text += "0";
		timetext->Text += timePtr->tm_min.ToString();
	}
	else
	{
		timetext->Text += timePtr->tm_min.ToString();
	}
	if (timePtr->tm_hour < 12)
	{
		timetext->Text += " AM";
	}
	else
	{
		timetext->Text += " PM";
	}
	if (::daynum != timePtr->tm_wday)
	{
		::dayvarset = false;
		//
		::ahschecked = true;
		::StephanieW = true;
		::CindyL = true;
		//
		// fms
		::fms1checked = false;
		::ArulK = false;
		::RichardW = false;
		::WeberL = false;
		//
		::fms2checked = false;
		::AnD = false;
		::NathanZ = false;
		//
		// dams
		::dams1checked = false;
		::ShannonC = false;
		::ErinL = false;
		::AuroraC = false;
		::CarisO = false;
		::PresleyN = false;
		//
		::dams2checked = false;
		::MaddieF = false;
		//End elective list
		MainPage::MainPage();
		concurrency::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->GetFileAsync("rancholog.txt")).then([](Windows::Storage::StorageFile ^ log)
			{
				Platform::String^ write = nullptr;
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				write += (timePtr->tm_mon + 1).ToString();
				write += "/";
				write += timePtr->tm_mday.ToString();
				write += "/";
				write += ((timePtr->tm_year) + 1900).ToString();
				write += " // ";
				write += timePtr->tm_hour.ToString();
				write += ":";
				if (log10(timePtr->tm_min) + 1 < 2)
				{
					write += "0";
					write += timePtr->tm_min.ToString();
				}
				else
				{
					write += timePtr->tm_min.ToString();
				}
				write += " // Auto data reset - new day";
				concurrency::create_task(Windows::Storage::FileIO::AppendTextAsync(log, "\n" + write));
			});
		::daynum = timePtr->tm_wday;
	}
	switch (::daynum)
	{
	case 1:
		timetext->Text += " | Monday";
		break;
	case 2:
		timetext->Text += " | Tuesday";
		break;
	case 3:
		timetext->Text += " | Wednesday";
		break;
	case 4:
		timetext->Text += " | Thursday";
		break;
	case 5:
		timetext->Text += " | Friday";
		break;
	case 6:
		timetext->Text += " | Saturday";
		break;
	case 0:
		timetext->Text += " | Sunday";
		break;
	default:
		timetext->Text = nullptr;
		break;
	}
	if (::textboxbool == true)
	{
		++textboxtime;
		if (textboxtime >= 150)
		{
			textboxtext->Text = nullptr;
			::textboxbool = false;
		}
	}
}

void checkuwp::MainPage::textboxclear() {
	::textboxbool = false;
	textboxtext->Text = nullptr;
	::textbox = nullptr;
	textboxtime = 0;
}

void checkuwp::MainPage::Electivebutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	this->Frame->Navigate(TypeName(elective::typeid));
}


void checkuwp::MainPage::Bathbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	this->Frame->Navigate(TypeName(bathroom::typeid));
}


void checkuwp::MainPage::Adminbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	if (::passtry >= 4)
	{
		::passtrytime = (clock() - ::passtrytime) / (double)CLOCKS_PER_SEC;
		if (::passtrytime >= 300)
		{
			::passtry = 0;
			::passtrytime = 0;
		}
		else
		{
			::triesleft = 4;
			::textboxbool = true;
			textboxtext->Text = "You have exceeded password try attempts. Please wait 5 minutes.";
		}
	}
	if (::passtry < 4)
	{
		this->Frame->Navigate(TypeName(adminlogon::typeid));
	}
}


void checkuwp::MainPage::Versiontext_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	this->Frame->Navigate(TypeName(changelog::typeid));
}


void checkuwp::MainPage::Custombutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	this->Frame->Navigate(TypeName(custom::typeid));
}


void checkuwp::MainPage::Supportbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textboxclear();
	this->Frame->Navigate(TypeName(support::typeid));
}


void checkuwp::MainPage::Showquicklistelectives_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	quicklistelectives->Visibility = Windows::UI::Xaml::Visibility::Visible;
}


void checkuwp::MainPage::Showquicklistelectives_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	quicklistelectives->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}


void checkuwp::MainPage::Showquicklistbathroom_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	quicklistbathroom->Visibility = Windows::UI::Xaml::Visibility::Visible;
}


void checkuwp::MainPage::Showquicklistbathroom_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	quicklistbathroom->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}
