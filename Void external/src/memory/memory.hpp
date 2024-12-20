#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>
#include <ntstatus.h>
#include <iostream>
#include <vector>
#include <thread>
#include "nt.hpp"




class Memory
{
private:
	std::uintptr_t processId = 0;
	HANDLE processHandle = nullptr;
	HMODULE hNtDll = nullptr;

	_NtReadVirtualMemory NtReadVirtualMemory;
	_NtWriteVirtualMemory NtWriteVirtualMemory;
	_NtQuerySystemInformation NtQuerySystemInformation;
	_NtQueryObject NtQueryObject;
	_NtDuplicateObject NtDuplicateObject;
public:
	
	
	Memory(std::wstring_view processName) noexcept
	{
		::PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(::PROCESSENTRY32);

		const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		while (::Process32Next(snapShot, &entry))
		{
			if (!processName.compare(entry.szExeFile))
			{
				processId = entry.th32ProcessID;
				break;
			}
		}

		// Free handle
		if (snapShot)
			::CloseHandle(snapShot);

		hNtDll = GetModuleHandleW(L"ntdll.dll");

		NtReadVirtualMemory = (_NtReadVirtualMemory)GetProcAddress(hNtDll, "NtReadVirtualMemory");
		NtWriteVirtualMemory = (_NtWriteVirtualMemory)GetProcAddress(hNtDll, "NtWriteVirtualMemory");
		NtQuerySystemInformation = (_NtQuerySystemInformation)GetProcAddress(hNtDll, "NtQuerySystemInformation");
		NtQueryObject = (_NtQueryObject)GetProcAddress(hNtDll, "NtQueryObject");
		NtDuplicateObject = (_NtDuplicateObject)GetProcAddress(hNtDll, "NtDuplicateObject");

		processHandle = HijackHandle();
		if (!processHandle)
			abort();
		else
			std::cout << "[+] Handle successfully hijacked\n";
	}

	
	~Memory()
	{
		if (processHandle)
			::CloseHandle(processHandle);
	}

	
	std::uintptr_t GetModuleAddress(std::wstring_view moduleName) const noexcept
	{
		::MODULEENTRY32 entry = { };
		entry.dwSize = sizeof(::MODULEENTRY32);

		const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

		std::uintptr_t result = 0;

		while (::Module32Next(snapShot, &entry))
		{
			if (!moduleName.compare(entry.szModule))
			{
				result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
				break;
			}
		}

		if (snapShot)
			::CloseHandle(snapShot);

		return result;
	}

	// Read process memory
	template <typename T>
	const T Read(const std::uintptr_t address) const noexcept
	{
		T value = { };
		NtReadVirtualMemory(processHandle, reinterpret_cast<PVOID>(address), &value, sizeof(T), NULL);
		return value;
	}

	// Write process memory
	template <typename T>
	void Write(const std::uintptr_t address, const T& value) const noexcept
	{
		NtWriteVirtualMemory(processHandle, reinterpret_cast<PVOID>(address), (PVOID)&value, sizeof(T), NULL);
	}

	void PatchEx(BYTE* dest, BYTE* source, unsigned int size)
	{
		DWORD oldProtect;
		VirtualProtectEx(processHandle ,dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		WriteProcessMemory(processHandle, dest, source, size, NULL);
		VirtualProtectEx(processHandle, dest, size, oldProtect, &oldProtect);
	}

	HANDLE HijackHandle();
};


