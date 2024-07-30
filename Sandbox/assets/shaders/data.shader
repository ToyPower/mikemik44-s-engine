#type vertex
#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color1;
layout(location = 2) in vec2 texCoord;
uniform mat4 u_proj;
uniform mat4 u_mesh;
uniform vec4 u_color;
out vec4 color; 
out vec2 v_texCoord;
void main() {
	color = color1 * u_color;			
	v_texCoord = texCoord;
	gl_Position = u_proj * u_mesh * vec4(position,1);
}

#type pixel
#version 410 core
in vec4 color;
in vec2 v_texCoord;
uniform sampler2D u_tex;	
void main() {
			
	gl_FragColor = texture(u_tex, v_texCoord) * color;

}