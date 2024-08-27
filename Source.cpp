#include "SDK/moneyhack.hpp"
/*
Discord -> @saneman
Discord Inivte -> https://discord.gg/f7PW6fUrkK
Youtube -> https://www.youtube.com/@nurmolo-fedded
Site (AS OF 8/27/2024) -> https://moneyhack.online

 Compiler yap 2024

 Made by nurmolo credit is due where it is due...
*/


int main()
{
	Memory_X->Attach(L"cs2.exe");
	SDK::game_x->UpdateClientDll();
	SDK::localplayer_X->start();

	while (1)
	{
		SDK::localplayer_X->gethealth();
		std::cin.get();
	}
	
}	