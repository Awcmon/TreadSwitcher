//treadswitcher

#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

//0x31
void pressScan(short _key)
{
	//Structure for the keyboard event
	INPUT ip;

	//Set up the INPUT structure
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0; //We're doing scan codes instead
	ip.ki.dwExtraInfo = 0;

	//This let's you do a hardware scan instead of a virtual keypress
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = _key;  

	Sleep(5 + (rand() % 5));

	//Send the press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(5 + (rand() % 5));

	//Prepare a keyup event
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(10 + (rand() % 10));
}

int switchToState(int oldstate, int newstate)
{
	while (oldstate != newstate)
	{
		pressScan(0x31);
		oldstate = (oldstate + 1) % 3;
	}
	return newstate;
}

int main()
{
	srand(time(NULL));

	//0 = str
	//1 = int
	//2 = agi
	int state = 0;
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD0)) { state = 0; }
		if (GetAsyncKeyState(VK_NUMPAD1)) { state = switchToState(state, 0); }
		if (GetAsyncKeyState(VK_NUMPAD2)) { state = switchToState(state, 1); }
		if (GetAsyncKeyState(VK_NUMPAD3)) { state = switchToState(state, 2); }
		if (GetAsyncKeyState(VK_RBUTTON)) { state = switchToState(state, 0); }
		if (GetAsyncKeyState(0x41)) { state = switchToState(state, 2); } //A
		if (GetAsyncKeyState(0x51)) { state = switchToState(state, 1); } //Q
		if (GetAsyncKeyState(0x57)) { state = switchToState(state, 1); } //W
		if (GetAsyncKeyState(0x45)) { state = switchToState(state, 1); } //E
		if (GetAsyncKeyState(0x52)) { state = switchToState(state, 1); } //R

	}

	return 0;
}
