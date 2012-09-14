#version 120 

uniform sampler2D texture;

varying vec2 texcoord;

void main() 
{	
	gl_FragColor = texture2D( texture, texcoord );
	gl_FragColor = vec4(gl_FragColor.xyz, 0.0);
} 
