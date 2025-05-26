#include <cstdint>
#include "util/entity.h"
#include <map>

struct vis_t {
	bool enabled;
	float col[4] = {1.f,1.f,1.f,1.f};
};

namespace settings {
	namespace aimbot {
		inline bool trigger = false;
	}
	namespace visuals {
		namespace players {
			inline bool enabled;
			inline bool dormant;
			inline vis_t box;
			inline vis_t name;
			inline vis_t hp;
		}
	}
	namespace settings {
		inline bool bhop = false;
	}
}

namespace globals {
	inline std::map<int, entity> entlist;
}