#pragma once
void LoadAnimition() {
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"resou/atlas/player_" + std::to_wstring(i) + L".png";
		loadimage(&atlas_player[i], path.c_str());

	}

	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"resou/atlas/player_r_" + std::to_wstring(i) + L".png";
		loadimage(&atlas_player_r[i], path.c_str());

	}
}