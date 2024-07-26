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

    void DrawObjects(Shader* shader) {
        for (const auto& object : m_objects) {
            object->Draw(shader);
        }
    }

private:
    std::vector<std::unique_ptr<Object>> m_objects;
};

#endif // OBJECTMANAGER_HPP