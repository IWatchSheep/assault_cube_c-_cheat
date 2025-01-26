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
* linker: subsystem = Console (/SUBSYSTEM:CONSOLE)
* 
*/

int main()
{
	auto mem = Memory("ac_client.exe");

	auto process_id = mem.GetProcessId();
	auto module_address = mem.GetModuleAddress("ac_client.exe");

	std::cout << "Process id: " << process_id << std::endl;
	std::cout << "Module Address: " << std::hex << module_address << std::endl;
	
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, mem.GetProcessId());
	
	// "0x17E0A8", this is where i got the number "ac_client.exe + 0x17E0A8", 
	// in cheat engine, for my player health with no offset added, the offset for health is EC, so its not the health yet.

	auto local_player_and_no_offset = 0x17E0A8;

	const auto localPlayer = mem.Read<uintptr_t>(mem.GetModuleAddress("ac_client.exe") + local_player_and_no_offset);

	std::cout << std::dec << localPlayer << std::endl;

	int health = 9999;

	auto local_player_and_offset = (localPlayer + 0XEC); // "0XEC" this is my player health offset for the hex number "0x17E0A8"

	while (true)
	{
		WriteProcessMemory(handle, (LPVOID)local_player_and_offset, &health, sizeof(health), nullptr); 
	}
}