#include "memory.hpp"
#define SystemHandleInformation 0x10 //enum for ntquerysysteminformation


HANDLE Memory::HijackHandle()
{
	HANDLE hijackedHandle = NULL;
	NTSTATUS status = NULL;

	ULONG returnLength = 100;
	std::vector<BYTE> handleMemory(returnLength, 0);
	int i = 0;
	while ((status = NtQuerySystemInformation(SystemHandleInformation, handleMemory.data(), returnLength, &returnLength)), !NT_SUCCESS(status))
	{
		if (NT_SUCCESS(status))
			break;

		handleMemory.resize(returnLength);

		if (++i >= 150) //if it fails too many times break cuz i saw it on a random handle hijack project 
		{
			std::cout << "[-] Failed to get the handle info\n";
			return 0;
		}
	}

	auto handleInfo = reinterpret_cast<PSYSTEM_HANDLE_INFORMATION>(handleMemory.data()); //convert to this type so i can access its members

	int handleIndex = -1; //index of a handle i want 
	for (int i = 0; i < handleInfo->HandleCount; i++)
	{
		if (handleInfo->Handles[i].HandleValue == 0) //filtering out the wrong handles and shi
			continue;
		if ((HANDLE)handleInfo->Handles[i].HandleValue == INVALID_HANDLE_VALUE)
			continue;
		
		HANDLE hOwnerProc = OpenProcess(PROCESS_DUP_HANDLE, FALSE, handleInfo->Handles[i].UniqueProcessId); //this is so i can duplicate the handle
		if (!hOwnerProc)
			continue;

		HANDLE dupHandle = NULL;				//duplicate the handle so i can see if the pid matches with mine
		status = NtDuplicateObject(hOwnerProc, (HANDLE)handleInfo->Handles[i].HandleValue, GetCurrentProcess(), &dupHandle, PROCESS_ALL_ACCESS, NULL, NULL);

		if (status != STATUS_SUCCESS)
				continue;

		if (GetProcessId(dupHandle) != processId) //check if the handle points at a desired process using pids
		{
			CloseHandle(dupHandle); //if not close the duplicated handle
			continue;
		}
		

		std::vector<BYTE> objectBuffer(1024, 0);
		ULONG returnLength;									//this is so i can filter the handles by their type (process/thread/file...)
		status = NtQueryObject((HANDLE)handleInfo->Handles[i].HandleValue, ObjectTypeInformation, objectBuffer.data(), objectBuffer.size(), &returnLength);
		if (status != STATUS_SUCCESS)
			continue;
		auto object = reinterpret_cast<POBJECT_TYPE_INFORMATION>(objectBuffer.data());
		if (object->TypeIndex != 0x8) //0x8 is HandleTypeProcess or smth like that so i dont hijack a file/thread handle
			continue;
		hijackedHandle = dupHandle;
	}
	return hijackedHandle;
}

