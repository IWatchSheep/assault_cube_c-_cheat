#include "memory.h"
#include <thread>

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
	auto mem = Memory("cs2.exe");
	const auto client = reinterpret_cast<uintptr_t>(GetModuleHandleA("client.dll"));

	std::cout << "Process id: " << mem.GetProcessId() << std::endl;
	
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, mem.GetProcessId());

	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x186DE00;
	const auto localPlayer = client + dwLocalPlayerPawn;

	std::cout << std::dec << localPlayer << std::endl;
	
	while (true)
	{

		if (localPlayer)
		{
			constexpr std::ptrdiff_t m_fFlags = 0x3EC;
			// 65665 and 65667 are magic numbers i got from a youtube video below
			// How To Code A CS2 Internal Bunny Hop | C++: https://www.youtube.com/watch?v=Mh18HV1sJJQ
			const auto onGround = mem.Read<bool>(localPlayer + ((m_fFlags == 65665) || (m_fFlags == 65667))); 

			if (GetAsyncKeyState(VK_SPACE) && onGround)
			{
				INPUT space = { 0 };
				space.type = INPUT_KEYBOARD;
				space.ki.wVk = VK_SPACE;
				SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
				space.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &space, sizeof(INPUT)); // Send KeyUp
			}
		}
		

		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	
}