#include "../moneyhack.hpp"


namespace SDK
{

	class localplayer
	{
	private:
		void cachelocal()
		{
			while (true)
			{
				this->DwLocalPlayerPawn = Memory_X->read<DWORD64>(game_x->clientdll + offsets::client_dll::dwLocalPlayerPawn);
				this->health = Memory_X->read<DWORD64>(this->DwLocalPlayerPawn + offsets::client_dll::C_BaseEntity::m_iHealth);
				this->teamid = Memory_X->read<DWORD64>(this->DwLocalPlayerPawn + offsets::client_dll::C_BaseEntity::m_iTeamNum);
				this->viewmatrix = Memory_X->read<VIEW_MATRIX_MONEY>(game_x->clientdll + offsets::client_dll::dwViewMatrix);
			}
		}
	public:
		DWORD64 health = 0;
		DWORD64 teamid = 0;
		uintptr_t DwLocalPlayerPawn = NULL;
		VIEW_MATRIX_MONEY viewmatrix;
		bool started = false;
		inline bool isdead()
		{
			if (this->health < 0)
				return true;

			return false;
		}
		inline bool isplayer()
		{
			if (DwLocalPlayerPawn == NULL)
				return false;

			return true;
		}
		inline bool hasteam()
		{
			if (teamid != 2 && teamid != 3)
				return false;

			return true;
		}
		inline void gethealth()
		{
			printf("Health -> %i\n", this->health);
		}
		inline void start()
		{
			if (started == true)
			{

			}
			else
			{
				std::thread([&]() {this->cachelocal(); }).detach();
			}
		}

	};

	inline std::unique_ptr<localplayer> localplayer_X = std::make_unique<localplayer>();
}