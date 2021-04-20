// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <cstdio>
#include "Addresses.h"
#include <iostream>

class SkillBase
{
public:
	char pad_0000[72]; //0x0000
	int8_t defense; //0x0048
	char pad_0049[7]; //0x0049
	int8_t health; //0x0050
	char pad_0051[7]; //0x0051
	int8_t prayer; //0x0058
	char pad_0059[7]; //0x0059
	int8_t cooking; //0x0060
	char pad_0061[7]; //0x0061
	int8_t fletching; //0x0068
	char pad_0069[7]; //0x0069
	int8_t firemaking; //0x0070
	char pad_0071[7]; //0x0071
	int8_t N00000433; //0x0078
	char pad_0079[15]; //0x0079
	int8_t thieving; //0x0088
	char pad_0089[183]; //0x0089
}; //Size: 0x0140

DWORD WINAPI Oldschool(HMODULE hModule) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    Addresses addresses  = Addresses();

    // Static address is still relative to base module entry point. i.e <dynamic module entry point + staticAddress>
    uintptr_t* skillsAddress = (uintptr_t*)(addresses.getBase() + addresses.getSkillBase());
    // Declare & define pointer to the location in memory where Jagex stores skill levels.
	SkillBase* mySkills      = (SkillBase*)(uintptr_t*)(addresses.getBase() + addresses.getSkillBase());

    // We can now access those values as if they were structs we constructed ourselves.
    std::cout << "Skill list base address: " << skillsAddress << std::endl;
    std::cout << "Defense Level: "  << static_cast<int16_t>(mySkills->defense)  << std::endl;
    std::cout << "Cooking Level: "  << static_cast<int16_t>(mySkills->cooking)  << std::endl;
    std::cout << "Health Level: "   << static_cast<int16_t>(mySkills->health)   << std::endl;
    std::cout << "Thieving Level: " << static_cast<int16_t>(mySkills->thieving) << std::endl;


    for (;;) {
		int* fletchingExp = (int*)(addresses.getBase() + addresses.getFletchingExp());
		std::cout << *fletchingExp << std::endl;

        Sleep(5);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Oldschool, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

