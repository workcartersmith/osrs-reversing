#pragma once
#include <Windows.h>


class Addresses {
private:
	// Game module entry point
	uintptr_t os_base = (uintptr_t)GetModuleHandle(L"osclient.exe");

	// Start of skill levels in memory. Static as of 4/19/2021
	uintptr_t skillLevelBase = 0x58A9CC;

	// Will organize later.
	uintptr_t mining_exp = 0x58A9D8;
	uintptr_t fletching_exp = 0x58A9C4;
	uintptr_t player_health = 0x58AA1C;
	uintptr_t woodcutting_exp = 0x176D078;

public:
	uintptr_t getMiningExp() {
		return mining_exp;
	}
	uintptr_t getWoodcuttingExp() {
		return woodcutting_exp;
	}
	uintptr_t getFletchingExp() {
		return fletching_exp;
	}
	uintptr_t getBase() {
		return os_base;
	}
	uintptr_t getSkillBase() {
		return skillLevelBase;
	}
};
