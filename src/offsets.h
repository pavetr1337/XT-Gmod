namespace offsets {
    inline std::uint64_t LocalPlayer = 0;
    inline view_matrix_t ViewMatrix;
    //inline std::uint64_t ForceJump = 0;
    //inline std::uint64_t MatFullbright = 0;
    //inline std::uint64_t Crosshair = 0;
    //inline std::uint64_t BoneMatrix = 0;
    //inline std::uint64_t m_hObserverTarget = 0;
    //inline std::uint64_t m_hActiveWeapon = 0;
    //inline std::uint64_t Weaponname = 0;
    //inline std::uint64_t Playername = 0;
    //inline std::uint64_t SteamID = 0;
    //inline std::uint64_t lastupdate = 0;
}

namespace offset_shifts {
    inline std::uint64_t LocalPlayer = 0x9432d0;
    inline std::uint64_t ViewMatrix = 0x7bf5e8;
    inline std::uint64_t EntityList = 0x9E5418;
    inline std::uint64_t ForceJump = 0xa32970;
    inline std::uint64_t Crosshair = 0x3700;
}

namespace netvar_shifts {
    inline std::uint64_t health = 0xC8 - 0x10;
    inline std::uint64_t pos = 0x308 - 0x10;
    inline std::uint64_t name = 0x3744 - 0x10;
    inline std::uint64_t dormant = 0xB4 - 0x10;
}