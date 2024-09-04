#version 460

in vec3 position_eye, normal_eye; 
in vec2 texcoord;

uniform mat4 view_mat_shader;
uniform bool light1_enabled; // bien kiem tra bat tat den
uniform sampler2D textureSampler;// bo sampler2D cua texture

out vec4 out_color;

void main() {
    //-----------Vi tri nguon sang 1 (trong phòng)-------------
    vec3 light_position_world_1 = vec3(0.0, 7.0, 0.0);// trong kg the gioi
    vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0)); //trong kg mat

    //-----------Vi trí nguon sáng 2 (bên ngoài phòng)-------------
    vec3 light_position_world_2 = vec3(-6.0, 0.0, -15.0);
    vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));

    // Vi tri cam
    vec3 position_viewer = vec3(0.0, 8.0, 30.0);

    // chuan hoa phap tuyen
    vec3 n_eye = normalize(normal_eye);

    // Tính toán ánh sáng tai nguon 1
    vec3 Id_1 = vec3(0.0);// thanh phan khuech tan
    vec3 Is_1 = vec3(0.0);// thanh phan phan xa
    if (light1_enabled) {
        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        
        // Tính ánh sáng khu?ch tán t? ngu?n 1
        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        Id_1 = vec3(0.7, 0.7, 0.7) * vec3(0.8, 0.5, 0.3) * dot_prod_1;

        // Tính ánh sáng ph?n x? t? ngu?n 1
        vec3 half_way_eye_1 = normalize(direction_to_light_eye_1 + normalize(position_viewer - position_eye));
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 150.0);
        Is_1 = vec3(0.7, 0.7, 0.7) * vec3(0.8, 0.5, 0.3) * specular_factor_1;
    }

    // Tính toán ánh sáng t? ngu?n 2
    vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
    vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
    
    // Tính ánh sáng khu?ch tán t? ngu?n 2
    float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
    vec3 Id_2 = vec3(0.7, 0.7, 0.7) * vec3(1.0, 0.6, 0.3) * dot_prod_2;

    // Tính ánh sáng ph?n x? t? ngu?n 2
    vec3 half_way_eye_2 = normalize(direction_to_light_eye_2 + normalize(position_viewer - position_eye));
    float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
    float specular_factor_2 = pow(dot_prod_specular_2, 150.0);
    vec3 Is_2 = vec3(1.0, 1.0, 1.0) * vec3(1.0, 0.8, 0.5) * specular_factor_2;

    if (!light1_enabled) {
    Id_2 *= 0.5;  // Gi?m c??ng ?? ánh sáng khu?ch tán
    Is_2 *= 0.5;  // Gi?m c??ng ?? ánh sáng ph?n x?
}
    // Ánh sáng môi truong
    vec3 Ia = vec3(1.0, 0.9, 0.6) * vec3(1.0, 0.9, 0.8);

    // Tong hop ánh sáng tu ca hai nguon
    vec3 final_color = (light1_enabled ? (Id_1 + Is_1) : vec3(0.0)) + Id_2 + Is_2 + Ia;

    // Tính màu cuoi cùng và áp dung texture
    vec4 texColor = texture(textureSampler, texcoord);
    out_color = vec4(final_color, 1.0) * texColor;
}
