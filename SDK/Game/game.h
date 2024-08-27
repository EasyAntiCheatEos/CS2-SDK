/*
Discord -> @saneman
Discord Inivte -> https://discord.gg/f7PW6fUrkK
Youtube -> https://www.youtube.com/@nurmolo-fedded
Site (AS OF 8/27/2024) -> https://moneyhack.online

 Compiler yap 2024

 Made by nurmolo credit is due where it is due...
*/

#include "../moneyhack.hpp"


namespace SDK
{
	class game
	{
	public:
		uintptr_t clientdll;
		uintptr_t engine2dll;
		HWND cs2window;

		inline uintptr_t UpdateClientDll()
		{
			this->clientdll = Memory_X->GetModuleBase(L"client.dll");
		}
		inline uintptr_t UpdateEngine2DLL()
		{
			this->engine2dll = Memory_X->GetModuleBase(L"engine2.dll");
		}
		inline HWND UpdateCS2Window()
		{
			this->cs2window = FindWindowA(NULL, "Counter-Strike 2");
		}

		inline bool NullCheck()
		{
			if (this->clientdll == NULL)
			{
				printf("Client.dll is invaild\n");
				return true;
			}
			if (this->engine2dll == NULL)
			{
				printf("engine2.dll is invaild\n");
				return true;
			}
			if (this->cs2window == NULL)
			{
				printf("cs2 HWND is invaild\n");
				return true;
			}
			// success no issues!
			return false;
		}

	};

	std::unique_ptr<game> game_x = std::make_unique<game>();
}