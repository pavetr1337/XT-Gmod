#include "overlay.h"
#include <imgui.h>
#include <windows.h>
#include "settings.h"
#include <string>

void imgui_vis(const char* label, vis_t& visual) {
    ImGui::Checkbox(label, &visual.enabled);
    std::string lbl = "##";
    lbl += label;
    ImVec2 tsize = ImGui::CalcTextSize(label);
    ImGui::SameLine(tsize.x+50.f);
    ImGui::ColorEdit4(lbl.c_str(), visual.col, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
}

void overlay::draw_gui()
{
	ImGui::SetNextWindowSize(ImVec2(600, 400));

#ifndef NDEBUG
    ImGui::ShowDemoWindow();
#endif

	ImGui::Begin("gui", nullptr, ImGuiWindowFlags_NoDecoration);
	{
        if (ImGui::BeginTabBar("maintabbar", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Aim"))
            {
                ImGui::SeparatorText("Trigger");
                ImGui::Checkbox("Triggerbot", &settings::aimbot::trigger);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Visuals"))
            {
                ImGui::SeparatorText("Players");
                ImGui::Checkbox("Enabled", &settings::visuals::players::enabled);
                ImGui::Checkbox("Dormant", &settings::visuals::players::dormant);
                imgui_vis("Box", settings::visuals::players::box);
                //imgui_vis("Name", settings::visuals::players::name);
                imgui_vis("Health", settings::visuals::players::hp);

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Entities"))
            {
                ImGui::Text("Placeholder for Entities");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Players"))
            {
                ImGui::Text("Placeholder for Players");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Settings"))
            {
                ImGui::SeparatorText("General");
                ImGui::Checkbox("Bunny Hop", &settings::settings::bhop);
                ImGui::Spacing();
                ImGui::SeparatorText("Info");
                ImGui::Text("Press [END] to unload\nCheat by pavetr\nThanks pa1n-dev for help\nWant cheap and undetectable internal hack? Buy ignitecheat.xyz!");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
            ImVec2 cpos = ImGui::GetWindowPos();
            ImVec2 csize = ImGui::GetWindowSize();
            ImVec2 wsize = ImGui::CalcTextSize("XTGmod by pavetr.ru/ds");
            ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(cpos.x+csize.x-wsize.x-5.f, cpos.y+wsize.y/2), ImColor(200, 200, 200, 255), "XTGmod by pavetr.ru/ds", 0, 0.0f, 0);
        }
	}
	ImGui::End();
}