#include "Lights.h"

#include <algorithm>

std::vector<PointLight> LightScene::get_nearest_point_lights(glm::vec3 target, size_t max_count, size_t min_count) const {
    return get_nearest_lights(point_lights, target, max_count, min_count);
}
//Dl
std::vector<DirectionalLight> LightScene::get_nearest_directional_lights(glm::vec3 target, size_t max_count, size_t min_count) const {
    return get_nearest_lights(directional_lights, target, max_count, min_count);
}

template<typename Light>
std::vector<Light> LightScene::get_nearest_lights(const std::unordered_set<std::shared_ptr<Light>>& lights, glm::vec3 target, size_t max_count, size_t min_count) {
    if (lights.size() <= max_count) {
        // No need to store if we are just going to return them all anyway.

        std::vector<Light> result{};
        result.reserve(std::max(lights.size(), min_count));
        for (const auto& point_light: lights) {
            result.push_back(*point_light);
        }
        while (result.size() < min_count) {
            result.push_back(Light::off());
        }

        return result;
    }

    size_t result_count = std::min(lights.size(), max_count);

    std::vector<std::pair<float, Light>> sorted_vector{};
   

    sorted_vector.reserve(lights.size());

    // 点光源
 for (const auto& light : lights) {
    glm::vec3 diff;
    if constexpr (std::is_same_v<Light, PointLight>) {
        diff = light->position - target;
    } else if constexpr (std::is_same_v<Light, DirectionalLight>) {
        diff = -light->direction;
    }
    float distance_squared = glm::dot(diff, diff);
    sorted_vector.emplace_back(distance_squared, *light);
}

    // Can use partial_sort to just get the `result_count` smallest, best used with smallish max_count
    std::partial_sort(sorted_vector.begin(), sorted_vector.begin() + (long) result_count, sorted_vector.end(), [](const std::pair<float, Light>& lhs, const std::pair<float, Light>& rhs) -> bool {
        return lhs.first < rhs.first;
    });

    std::vector<Light> result{};
    result.reserve(std::max(result_count, min_count));
    for (auto i = 0u; i < result_count; ++i) {
        result.push_back(sorted_vector[i].second);
    }
    while (result.size() < min_count) {
        result.push_back(Light::off());
    }
    return result;
}
