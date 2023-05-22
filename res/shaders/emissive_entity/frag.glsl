#version 410 core

in VertexOut {
    vec3 ws_position;
    vec2 texture_coordinate;
    vec3 ws_normal;
} frag_in;

layout(location = 0) out vec4 out_colour;

// Material properties
uniform vec3 emissive_tint;
uniform float specular_intensity; // 反光强度
uniform float shininess; // 反光度

// Global Data
uniform float inverse_gamma;
uniform vec3 light_direction;
uniform sampler2D emissive_texture;

void main() {
    vec3 texture_colour = texture(emissive_texture, frag_in.texture_coordinate).rgb;
    vec3 emissive_colour = emissive_tint * texture_colour;

    // 计算视线方向
    vec3 view_direction = normalize(-frag_in.ws_position);

    // 计算光照方向
    vec3 direction = normalize(light_direction); // 光源方向

    // 计算法线
    vec3 normal = normalize(frag_in.ws_normal);

    // 计算反射方向
    vec3 reflection_direction = reflect(direction, normal);

    // 计算反光颜色
    float specular = pow(max(dot(reflection_direction, view_direction), 0.0), shininess) * specular_intensity;

    // 最终颜色 = 发光颜色 + 反光颜色
    vec3 final_colour = emissive_colour + specular;

    out_colour = vec4(final_colour, 1.0);
    out_colour.rgb = pow(out_colour.rgb, vec3(inverse_gamma));
}
