#version 410 core
#include "../common/lights.glsl"

// Per instance data
uniform mat4 model_matrix;

// Material properties
uniform vec3 diffuse_tint;
uniform vec3 specular_tint;
uniform vec3 ambient_tint;
uniform float shininess;

// Light Data
#if NUM_PL > 0
layout (std140) uniform PointLightArray {
    PointLightData point_lights[NUM_PL];
};
#endif

// Directional light data
#if NUM_DL > 0
layout (std140) uniform DirectionalLightArray {
    DirectionalLightData directional_lights[NUM_DL];
};
#endif

in VertexOut {
    vec2 texture_coordinate;
    vec3 ws_position;
    vec3 ws_normal;
} frag_in;

layout(location = 0) out vec4 out_colour;

// Global Data
uniform float inverse_gamma;
uniform vec3 ws_view_position;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_map_texture;

void main() {
    vec3 ws_view_dir = normalize(ws_view_position - frag_in.ws_position);
    LightCalculatioData light_calculation_data = LightCalculatioData(frag_in.ws_position, ws_view_dir, frag_in.ws_normal);
    Material material = Material(diffuse_tint, specular_tint, ambient_tint, shininess);

    LightingResult lighting_result = total_light_calculation(light_calculation_data, material
        #if NUM_PL > 0
        ,point_lights
        #endif
        #if NUM_DL > 0
        ,directional_lights
        #endif
    );

    // Resolve the per vertex lighting with per fragment texture sampling.
    vec3 resolved_lighting = resolve_textured_light_calculation(lighting_result, diffuse_texture, specular_map_texture, frag_in.texture_coordinate);

    out_colour = vec4(resolved_lighting, 1.0f);
    out_colour.rgb = pow(out_colour.rgb, vec3(inverse_gamma));
}