#include "SDK/moneyhack.hpp"

int main()
{
	Memory_X->Attach(L"cs2.exe");
	SDK::game_x->UpdateClientDll();
	SDK::localplayer_X->start();

	SDK::localplayer_X->gethealth();
}	