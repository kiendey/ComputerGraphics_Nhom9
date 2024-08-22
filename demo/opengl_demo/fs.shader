#version 460

in vec3
	position_eye,
	normal_eye;

uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

void main() {
	//-----------ch? ??nh c�c v? tr�-------------
		// v? tr� ngu?n s�ng trong th? gi?i
	vec3 light_position_world = vec3(0.0, -1.0, 2.0);
	// bi?n ??i v? tr� ngu?n s�ng sang eye space
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

	// v? tr� viewer
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);

	// chu?n h�a normal_eye
	vec3 n_eye = normalize(normal_eye);

	// t�nh vector kho?ng c�ch t? ngu?n s�ng ??n m?t
	// h??ng vector h??ng t? vertex ??n ngu?n s�ng
	// = v? tr� Light - v? tr� Vertex
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	// chu?n h�a vector kho?ng c�ch t? ngu?n s�ng ??n m?t
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

	// t�nh vector kho?ng c�ch v? tr� viewer v� vertex
	// = v? tr� viewer - v? tr� vertex
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
	// chu?n h�a	
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);

	// --------------c??ng ?? �nh s�ng khu?ch t�n-----------------------
		// t�nh cosin g�c gi?a vector h??ng �nh s�ng v� vector ph�p tuy?n: l.n
	float dot_prod = dot(direction_to_light_eye, n_eye);
	// l?y gi� tr? >=0 ?? lo?i b? gi� tr? �m ?ng v?i g�c >90 ??
	dot_prod = max(dot_prod, 0.0);

	// c??ng ?? �nh s�ng ??n
	// m�u tr?ng m?
	vec3 Ld = vec3(0.7, 0.7, 0.7);

	// h? s? ph?n x? khu?ch t�n
	// m�u cam
	vec3 Kd = vec3(1.0, 0.5, 0.0);

	// c??ng ?? �nh s�ng khu?ch t�n cu?i c�ng
	vec3 Id = Ld * Kd * dot_prod;

	// -----------------c??ng ?? �nh s�ng ph?n x?-------------------		
	// blinn	
		// t�nh vector half way
	vec3 half_way_eye = surface_to_viewer_eye + direction_to_light_eye;
	// chu?n h�a vector half way
	half_way_eye = normalize(half_way_eye);

	// t�nh cosin g�c gi?a vector half_way_eye v� vector ph�p tuy?n: n.h
	float dot_prod_specular = dot(half_way_eye, n_eye);
	// l?y gi� tr? >=0 ?? lo?i b? gi� tr? �m ?ng v?i g�c >90 ??
	dot_prod_specular = max(dot_prod_specular, 0.0);

	// h? s? s�ng b�ng
	float specular_exponent = 100.0;
	// t�nh m? v?i h? s? s�ng b�ng
	float specular_factor = pow(dot_prod_specular, specular_exponent);

	// �nh s�ng ph?n x?
	// m�u tr?ng
	vec3 Ls = vec3(1.0, 1.0, 1.0);

	// h? s? ph?n x?
	// ph?n x? to�n ph?n, m�u tr?ng
	vec3 Ks = vec3(1.0, 1.0, 1.0);

	// c??ng ?? �nh s�ng ph?n x? cu?i c�ng
	vec3 Is = Ls * Ks * specular_factor;

	// --------------c??ng ?? �nh s�ng m�i tr??ng---------------
		// �nh s�ng m�i tr??ng
		// m�u x�m
	vec3 La = vec3(0.2, 0.2, 0.2);

	// h? s? m�i tr??ng
	// ph?n chi?u ho�n to�n
	vec3 Ka = vec3(1.0, 1.0, 1.0);

	// c??ng ?? �nh s�ng m�i tr??ng cu?i c�ng
	vec3 Ia = La * Ka;

	// ------------mau cuoi cung------------
	//out_color = fragment_color;
	//out_color = vec4(Is + Id + Ia, 1.0);
	out_color = vec4(Is + Id + Ia, 1.0) * fragment_color;
}
