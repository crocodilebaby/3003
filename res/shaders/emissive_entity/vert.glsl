#version 410 core

// Per vertex data
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 texture_coordinate;

out VertexOut {
    vec3 ws_position;
    vec3 ws_normal;
    vec2 texture_coordinate;
} vertex_out;

// Per instance data
uniform mat4 model_matrix;

// Global data
uniform mat4 projection_view_matrix;
uniform vec3 diffuse_tint;
uniform vec3 specular_tint;
uniform vec3 ambient_tint;
uniform float shininess;

void main() {
    vertex_out.ws_position = (model_matrix * vec4(vertex_position, 1.0f)).xyz;
    vertex_out.ws_normal = mat3(transpose(inverse(model_matrix))) * vertex_normal;
    vertex_out.texture_coordinate = texture_coordinate;

    gl_Position = projection_view_matrix * vec4(vertex_out.ws_position, 1.0f);
}
