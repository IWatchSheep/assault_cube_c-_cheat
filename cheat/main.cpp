#include "memory.h"

// i hide the default folders. i made three new folders: cheat, output, output\intermediates
// project property settings
/*
* configuration = all configuration, platform = win32, solution configuration = release, solution platforms = x86
* 
* general: output directory, i set this to the output folder i made. intermediate directory, i set this to the intermediate directory i made. 
* configuration type = application(.exe), language standard = iso c++ 20 standard
* 
* advanced: character set = multi-byte
* 
* linker: system, subsystem = Console (/SUBSYSTEM:CONSOLE)
* 
*/

int main()
{
	auto mem = Memory("ac_client.exe");

	std::cout << "Process id: " << mem.GetProcessId() << std::endl;
	std::cout << "Module Address: " << std::hex << mem.GetModuleAddress("ac_client.exe") << std::endl;
	
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, mem.GetProcessId());
	
	// "0x17E0A8", this is where i got the number "ac_client.exe + 0x17E0A8", in cheat engine, for my player health with no offset added, the offset for health is EC, so its not the health yet.
	const auto localPlayer = mem.Read<uintptr_t>(mem.GetModuleAddress("ac_client.exe") + 0x17E0A8);

	std::cout << std::dec << localPlayer << std::endl;

	int health = 987;
	while (true)
	{
		WriteProcessMemory(handle, (LPVOID)(localPlayer + 0XEC), &health, sizeof(health), nullptr); // "0XEC" this is my player health offset for the hex number "0x17E0A8"
	}
}