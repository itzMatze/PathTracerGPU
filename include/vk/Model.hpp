#pragma once

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

#include "json.hpp"

#include "vk/Image.hpp"
#include "vk/Mesh.hpp"
#include "Storage.hpp"

namespace ve
{
    struct Material {
        glm::vec4 base_color = glm::vec4(1.0f);
        glm::vec4 emission = glm::vec4(0.0f);
        float metallic = 0.0f;
        float roughness = 0.0f;
        alignas(8) int32_t base_texture = -1;
        //int32_t metallic_roughness_texture = -1;
        //int32_t normal_texture = -1;
        //int32_t occlusion_texture = -1;
        //int32_t emissive_texture = -1;
    };

    struct Light {
        glm::vec3 dir;
        float intensity = 0.0f;
        glm::vec3 pos;
        float innerConeAngle;
        glm::vec3 color;
        float outerConeAngle;
    };

    struct Model
    {
        void apply_transformation(const glm::mat4& transformation);

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<uint32_t> texture_indices;
        std::vector<Material> materials;
        std::vector<Light> lights;
        std::vector<std::vector<unsigned char>> texture_data;
        vk::Extent2D texture_dimensions;
        std::vector<Mesh> meshes;
    };

    namespace ModelLoader
    {
        Model load(const VulkanMainContext& vmc, Storage& storage, const std::string& path, uint32_t idx_count, uint32_t vertex_count, uint32_t material_count, uint32_t texture_count);
        Model load(const VulkanMainContext& vmc, Storage& storage, const nlohmann::json& model, uint32_t idx_count, uint32_t vertex_count, uint32_t material_count);
    };
} // namespace ve
