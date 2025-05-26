#include "vec.h"
#include <string>

class entity {
public:
    int health;
    vec3_t pos;
    vec3_t top_origin;
    std::string name;
    int dormant;

    entity() {
        health = -1;
        pos = vec3_t(0.f,0.f,0.f);
        top_origin = pos + vec3_t(0.f, 0.f, 75.f);
        name = "";
        dormant = 0;
    }
    entity(int _health, vec3_t _pos, std::string _name, int _dormant) {
        health = _health;
        pos = _pos;
        top_origin = pos + vec3_t(0.f, 0.f, 75.f);
        name = _name;
        dormant = _dormant;
    }
};