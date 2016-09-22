#include <Windows.h>
#include <iostream>
#include <thread>
#include "MManager.h"
using namespace std;

/*
-- Credits --
Minentaucher
*/

Memory Mem;
Module Client;

int main()
{
	SetConsoleTitle("ExternalBase by reaLD");
	
	//too lazy to add any checks :P do it yourself.
	Mem.Attach("csgo.exe");
	Client = Mem.GetModule("client.dll");
}