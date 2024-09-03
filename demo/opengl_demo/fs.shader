#version 460

in vec3 position_eye, normal_eye;
in vec2 texcoord;

uniform mat4 view_mat_shader;
uniform bool light1_enabled; // Bi?n ki?m so�t ?�n
uniform sampler2D textureSampler;

out vec4 out_color;

void main() {
    //-----------V? tr� ngu?n s�ng 1 (trong ph�ng)-------------
    vec3 light_position_world_1 = vec3(0.0, 7.0, 0.0);
    vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));

    //-----------V? tr� ngu?n s�ng 2 (b�n ngo�i ph�ng)-------------
    vec3 light_position_world_2 = vec3(0.0, 20.0, -20.0); // ??t ngo�i ph�ng
    vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));

    // V? tr� ng??i xem
    vec3 position_viewer = vec3(0.0, 8.0, 30.0);

    // Chu?n h�a vector ph�p tuy?n
    vec3 n_eye = normalize(normal_eye);

    // T�nh to�n �nh s�ng t? ngu?n 1 (ch? n?u ?�n 1 b?t)
    vec3 Id_1 = vec3(0.0);
    vec3 Is_1 = vec3(0.0);
    if (light1_enabled) {
        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        
        // T�nh �nh s�ng khu?ch t�n t? ngu?n 1
        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        Id_1 = vec3(0.7, 0.7, 0.7) * vec3(1.0, 0.5, 0.0) * dot_prod_1;

        // T�nh �nh s�ng ph?n x? t? ngu?n 1
        vec3 half_way_eye_1 = normalize(direction_to_light_eye_1 + normalize(position_viewer - position_eye));
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 150.0);
        Is_1 = vec3(1.0, 1.0, 1.0) * vec3(1.0, 1.0, 1.0) * specular_factor_1;
    }

    // T�nh to�n �nh s�ng t? ngu?n 2
    vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
    vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
    
    // T�nh �nh s�ng khu?ch t�n t? ngu?n 2
    float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
    vec3 Id_2 = vec3(0.7, 0.7, 0.7) * vec3(1.0, 0.5, 0.0) * dot_prod_2;

    // T�nh �nh s�ng ph?n x? t? ngu?n 2
    vec3 half_way_eye_2 = normalize(direction_to_light_eye_2 + normalize(position_viewer - position_eye));
    float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
    float specular_factor_2 = pow(dot_prod_specular_2, 150.0);
    vec3 Is_2 = vec3(1.0, 1.0, 1.0) * vec3(1.0, 1.0, 1.0) * specular_factor_2;

    // �nh s�ng m�i tr??ng
    vec3 Ia = vec3(0.2, 0.2, 0.2) * vec3(1.0, 0.9, 0.8);

    // T?ng h?p �nh s�ng t? c? hai ngu?n
    vec3 final_color = Id_1 + Is_1 + Id_2 + Is_2 + Ia;

    // T�nh m�u cu?i c�ng v� �p d?ng texture
    vec4 texColor = texture(textureSampler, texcoord);
    out_color = vec4(final_color, 1.0) * texColor;
}
