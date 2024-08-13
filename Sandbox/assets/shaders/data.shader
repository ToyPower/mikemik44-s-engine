#type vertex
#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;
layout(location = 4) in float v_tileFactor;

uniform mat4 u_proj = mat4(1.0f);
out vec2 v_texCoord;
out vec4 color;
out float textureIndex;
out float tileFactor;
void main() {
	color = colour;
	textureIndex = texIndex;
	v_texCoord = texCoord;
	gl_Position = u_proj * vec4(position,1);
	tileFactor = v_tileFactor;
}

#type pixel
#version 410 core
in vec4 color;
in vec2 v_texCoord;
in float textureIndex;
in float tileFactor;
uniform sampler2D u_tex[32];	
void main() {
	vec4 col = color;
	col *= texture(u_tex[int(textureIndex)], v_texCoord*tileFactor);
	
	if (col.a == 0) {
		discard;
	}
	gl_FragColor = col;

}