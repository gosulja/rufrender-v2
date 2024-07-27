#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include <vector>
#include <memory>
#include "Object.hpp"
#include "Shader.hpp"

class ObjectManager {
public:
    void AddObject(std::unique_ptr<Object> object) {
        m_objects.push_back(std::move(object));
    }

    void DrawObjects(Shader* shader, float dt) {
        for (const auto& object : m_objects) {
            object->Draw(shader, dt);
        }
    }

    std::vector<std::string> GetObjectsInfo() const {
        std::vector<std::string> info;
        for (const auto& object : m_objects) {
            info.push_back(object->GetInfo());
        }
        return info;
    }
private:
    std::vector<std::unique_ptr<Object>> m_objects;
};

#endif // OBJECTMANAGER_HPP