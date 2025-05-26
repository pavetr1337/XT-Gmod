#define _CRT_SECURE_NO_WARNINGS
#include "src/overlay.h"
#include "src/util/memory.h"
#include "src/settings.h"
#include "src/offsets.h"
#include <thread>

namespace globals {
	inline HANDLE process_handle{};

	inline std::uint32_t process_id{};
	inline std::uintptr_t module_base{};
	inline std::uintptr_t engine_base{};

	inline std::uint32_t process_size{};
	inline std::uintptr_t copied_buffer{};
}

std::uint32_t dump_sig(const char* signature, int extra, int offset)
{
	std::uintptr_t instruction_offset = memory::signature_scan(globals::copied_buffer, globals::process_size, signature);
	return memory::read<std::uint32_t>(globals::process_handle, globals::module_base + instruction_offset + offset) + extra - globals::module_base;
}

void triggerbot() {
	if (settings::aimbot::trigger) {
		int target = memory::read<int>(globals::process_handle, offsets::LocalPlayer + offset_shifts::Crosshair);
		if (target <= 128 and target != 0) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}

void bhop() {
	if (settings::settings::bhop && GetAsyncKeyState(VK_SPACE) & 0x8000) {
		int flag = memory::read<int>(globals::process_handle, offsets::LocalPlayer + 0x440);
		if (flag == 257 or flag == 263 or flag == 33025 or flag == 1280 or flag == 1281)
		{
			memory::write<int>(globals::process_handle, globals::module_base + offset_shifts::ForceJump, 5);
		}
		else {
			memory::write<int>(globals::process_handle, globals::module_base + offset_shifts::ForceJump, 4);
		}
	}
}

void capture_offsets() {
	globals::process_id = memory::find_process_id("gmod.exe");

	if (!globals::process_id)
	{
		printf("[-] failed to find process id\n");
		return;
	}

	//std::printf("[+] process id [%i]\n", globals::process_id);

	globals::module_base = memory::get_module_base(globals::process_id, "client.dll");
	globals::engine_base = memory::get_module_base(globals::process_id, "engine.dll");

	if (!globals::module_base)
	{
		printf("[-] failed to find module base\n");
		return;
	}
	if (!globals::engine_base)
	{
		printf("[-] failed to find engine base\n");
		return;
	}

	//std::printf("[+] module base [%p]\n", globals::module_base);

	globals::process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, globals::process_id);

	if (!globals::process_handle)
	{
		printf("[-] failed to open handle to process [run as admin]\n");
		return;
	}

	//std::printf("[+] handle to process [%p]\n\n", globals::process_handle);

	offsets::LocalPlayer = memory::read<std::uint64_t>(globals::process_handle, globals::module_base + offset_shifts::LocalPlayer);

	//std::printf("[+] localplayer addr [%p]\n", offsets::LocalPlayer);
	
	if (offsets::LocalPlayer) {
		std::uint64_t view_matrix_base = memory::read<std::uint64_t>(globals::process_handle, globals::engine_base + offset_shifts::ViewMatrix) + 0x2D4;
		//std::printf("[+] viewmatrix base [%p]\n", view_matrix_base);
		offsets::ViewMatrix = memory::read<view_matrix_t>(globals::process_handle, view_matrix_base);
		float vm = memory::read<float>(globals::process_handle, view_matrix_base);
		//std::printf("[+] viewmatrix val %f\n", vm);

		for (size_t i = 0; i < 128; i++)
		{
			std::uint64_t ent_addr = memory::read<std::uint64_t>(globals::process_handle, globals::module_base + offset_shifts::EntityList + 0x38 + (i * 0x10));
			if (ent_addr && offsets::LocalPlayer != ent_addr) {
				int health = memory::read<int>(globals::process_handle, ent_addr + netvar_shifts::health);
				vec3_t pos = memory::read<vec3_t>(globals::process_handle, ent_addr + netvar_shifts::pos);
				std::string name = "???";
				int dormant = memory::read<int>(globals::process_handle, ent_addr + netvar_shifts::dormant);
				try {
					char cname[32];
					memory::read_string(globals::process_handle, ent_addr + netvar_shifts::name, cname);
					//std::printf("[+] nick %s\n", cname);
					name = cname;
				}
				catch (...) {}
				
				entity ent(health,pos,name,dormant);
				globals::entlist[i] = ent;
			}
		}

		bhop();
		triggerbot();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
#ifndef NDEBUG
	AllocConsole();
	freopen("conout$", "w", stdout);
#endif

	std::thread read_ent_info([&]() -> void {
		while (1) {
			capture_offsets();
		}
	});

	overlay::render();

	return 0;
}