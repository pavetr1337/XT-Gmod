#include "visuals.h"
#include <windows.h>
#include "settings.h"
#include "offsets.h"

vec3_t screen_size(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0);

ImColor float_to_col(float* col) {
	return ImColor(col[0], col[1], col[2], col[3]);
}

void visuals::draw_visuals() {
	vec3_t screen_bottom, screen_top;

	ImGui::SetNextWindowPos(ImVec2(0.f,0.f));
	ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
	ImGui::Begin("vis", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs);
	{
		if (settings::visuals::players::enabled)
		for (const auto& pair : globals::entlist) {
			int i = pair.first;
			entity ent = pair.second;
			if (ent.health > 0 and (settings::visuals::players::dormant || ent.dormant != -65536)) {
				if (!world_to_screen(screen_size, ent.pos, screen_bottom, offsets::ViewMatrix) || !world_to_screen(screen_size, ent.top_origin, screen_top, offsets::ViewMatrix))
					continue;

				int box_height = screen_bottom.y - screen_top.y;
				int box_width = box_height / 2;

				//ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screen_top.x, screen_top.y - 14), ImColor(255, 255, 0, 255), "1", 0, 0.0f, 0);
				if (settings::visuals::players::box.enabled) {
					ImGui::GetWindowDrawList()->AddRect(ImVec2(screen_top.x - box_width / 2, screen_top.y), ImVec2(screen_top.x - box_width / 2 + box_width, screen_top.y + box_height), float_to_col(settings::visuals::players::box.col));
				}
				if (settings::visuals::players::name.enabled) {
					const char* ename = ent.name.c_str();
					ImVec2 namesz = ImGui::CalcTextSize(ename);
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screen_top.x - namesz.x/2, screen_top.y - 14), float_to_col(settings::visuals::players::name.col), ename, 0, 0.0f, 0);
				}
				if (settings::visuals::players::hp.enabled) {
					std::string hptxt = std::to_string(ent.health);
					hptxt += "hp";
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screen_top.x + box_width / 2 + 1.f, screen_top.y), float_to_col(settings::visuals::players::hp.col), hptxt.c_str(), 0, 0.0f, 0);
				}
			}
		}
	}
	ImGui::End();
}