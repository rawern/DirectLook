#version 120 

uniform sampler2D textures[3];
uniform int textureMode;

varying vec2 texcoord;
varying vec2 texcoordBg;		// Texture coordinates background
varying float isBackground;

void main() 
{	
	if((textureMode == 1) && (isBackground == 0.0f))	// Use camera texture
	{
		gl_FragColor = texture2D( textures[0], texcoord.xy );
	}
	else if(isBackground == 0.0f)	// Use depth texture
	{
		gl_FragColor = texture2D( textures[1], texcoord.xy );
	}
	else
	{
		gl_FragColor = texture2D( textures[2], texcoordBg.xy );
		
		discard;
		//gl_FragColor = vec4( 0.2f, 0.8f, 0.2f, 1.0f );	// Green screen
	}
} 
