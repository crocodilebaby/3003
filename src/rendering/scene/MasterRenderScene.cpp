#include "MasterRenderScene.h"

void MasterRenderScene::use_camera(const CameraInterface& camera_interface) {
    entity_scene.global_data.use_camera(camera_interface);
    animated_entity_scene.global_data.use_camera(camera_interface);
    emissive_entity_scene.global_data.use_camera(camera_interface);
}

void MasterRenderScene::insert_entity(std::shared_ptr<EntityRenderer::Entity> entity) {
    entity_scene.entities.insert(std::move(entity));
}

void MasterRenderScene::insert_entity(std::shared_ptr<AnimatedEntityRenderer::Entity> entity) {
    animated_entity_scene.entities.insert(std::move(entity));
}

void MasterRenderScene::insert_entity(std::shared_ptr<EmissiveEntityRenderer::Entity> entity) {
    emissive_entity_scene.entities.insert(std::move(entity));
}

bool MasterRenderScene::remove_entity(const std::shared_ptr<EntityRenderer::Entity>& entity) {
    return entity_scene.entities.erase(entity) != 0;
}

bool MasterRenderScene::remove_entity(const std::shared_ptr<AnimatedEntityRenderer::Entity>& entity) {
    return animated_entity_scene.entities.erase(entity) != 0;
}

bool MasterRenderScene::remove_entity(const std::shared_ptr<EmissiveEntityRenderer::Entity>& entity) {
    return emissive_entity_scene.entities.erase(entity) != 0;
}

void MasterRenderScene::insert_light(std::shared_ptr<PointLight> point_light) {
    light_scene.point_lights.insert(std::move(point_light));
}

bool MasterRenderScene::remove_light(const std::shared_ptr<PointLight>& point_light) {
    return light_scene.point_lights.erase(point_light) != 0;
}

//Dl
void MasterRenderScene::insert_directional_light(std::shared_ptr<DirectionalLight> D_light) {
    light_scene.directional_lights.insert(std::move(D_light));
}
//DL
bool MasterRenderScene::remove_directional_light(const std::shared_ptr<DirectionalLight>& D_light) {
    return light_scene.directional_lights.erase(D_light) != 0;
}