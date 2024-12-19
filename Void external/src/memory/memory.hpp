#pragma once
#define WIN32_LEAN_AND_MEAN
#define STATUS ((NTSTATUS)0x00000000L)
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>
#include <ntstatus.h>

/*typedef NTSTATUS(NTAPI* NtReadVirtualMemory) (
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_Out_writes_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
	);*/

class Memory
{
private:
	std::uintptr_t processId = 0;
	void* processHandle = nullptr;
	HMODULE hNtDll = 0;
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
				processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
				break;
			}
		}

		// Free handle
		if (snapShot)
			::CloseHandle(snapShot);

		//hNtdll = GetModuleHandleW(L"ntdll.dll");
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
		::ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
		return value;
	}

	// Write process memory
	template <typename T>
	void Write(const std::uintptr_t address, const T& value) const noexcept
	{
		::WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}

	void PatchEx(BYTE* dest, BYTE* source, unsigned int size)
	{
		DWORD oldProtect;
		VirtualProtectEx(processHandle ,dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		WriteProcessMemory(processHandle, dest, source, size, NULL);
		VirtualProtectEx(processHandle, dest, size, oldProtect, &oldProtect);
	}
};