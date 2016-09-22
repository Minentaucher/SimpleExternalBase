
#ifndef MMANAGER_H
#define MMANAGER_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <Psapi.h>
#include <stdarg.h>
#include <stdint.h>

struct Vector {
	float x, y, z;
};

struct Module {
	DWORD dwBase;
	DWORD dwSize;
};

class Memory {
public:
	Memory();
	~Memory();

	bool Attached;
	bool Attach(char* pName, DWORD rights = PROCESS_ALL_ACCESS);
	void Detach();

	Module GetModule(char* moduleName);

	template <class T>
	T Read(DWORD addr) {
		T _read;
		ReadProcessMemory(_process, (LPVOID)addr, &_read, sizeof(T), NULL);
		return _read;
	}
	template <class T>
	void Write(DWORD addr, T val) {
		WriteProcessMemory(_process, (LPVOID)addr, &val, sizeof(T), NULL);
	}

private:
	HANDLE _process;
	DWORD pID;
};
#endif