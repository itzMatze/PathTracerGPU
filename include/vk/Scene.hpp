#pragma once

#include "vk/Model.hpp"
#include "Storage.hpp"
#include "Timer.hpp"
#include "vk/PathTracer.hpp"

namespace ve
{
    class Scene
    {
    public:
        Scene(const VulkanMainContext& vmc, VulkanCommandContext& vcc, Storage& storage);
        void construct();
        void self_destruct();
        void load(const std::string& path);

        bool loaded = false;

    private:
        struct MeshRenderData {
            int32_t mat_idx;
            uint32_t indices_idx;
        };

        struct ModelInfo {
            std::vector<uint32_t> mesh_index_offsets;
            std::vector<uint32_t> mesh_index_count;
            uint32_t index_buffer_idx;
            uint32_t num_indices;
            uint32_t blas_idx;
            uint32_t instance_idx;
            uint32_t mesh_render_data_idx;
        };

        const VulkanMainContext& vmc;
        VulkanCommandContext& vcc;
        Storage& storage;
        uint32_t vertex_buffer;
        uint32_t index_buffer;
        // use -1 to encode missing material buffer and/or textures as they are not required
        int32_t material_buffer = -1;
        int32_t texture_image = -1;
        int32_t light_buffer = -1;
        uint32_t mesh_render_data_buffer;
        uint32_t model_mrd_indices_buffer;
        PathTracer path_tracer;
    };
} // namespace ve
