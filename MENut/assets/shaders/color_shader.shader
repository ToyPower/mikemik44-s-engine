#type vertex
#version 410 core
layout(location = 0) in vec3 position;
uniform mat4 u_proj;
uniform mat4 u_mesh;
uniform vec4 u_color;
out vec4 color; 
void main() {
	color = u_color;			
	gl_Position = u_proj * u_mesh * vec4(position,1);
}

#type pixel
#version 410 core
in vec4 color;	
void main() {
	vec4 col = color;		
	if (col.a == 0) {
		discard;
	}
	gl_FragColor = col;

}