#include "MManager.h"

Memory::Memory() {}
Memory::~Memory() {}

bool Memory::Attach(char* pName, DWORD rights) 
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	do 
	{
		if (!strcmp(entry.szExeFile, pName)) 
		{
			pID = entry.th32ProcessID;
			CloseHandle(handle);

			_process = OpenProcess(rights, false, pID);

			Attached = true;

			return true;
		}
	}
	while (Process32Next(handle, &entry));
	
	return false;
}

void Memory::Detach() 
{
	Attached = false;
	CloseHandle(_process);
}

Module Memory::GetModule(char* moduleName) 
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do 
	{
		if (!strcmp(mEntry.szModule, (LPSTR)moduleName)) 
		{
			CloseHandle(module);

			Module mod = { (DWORD)mEntry.hModule, mEntry.modBaseSize };
			return mod;
		}
	} 
	while (Module32Next(module, &mEntry));

	Module mod = { (DWORD)false, (DWORD)false };
	return mod;
}