#version 120

uniform mat4 matVP;				// View projection matrix
uniform mat4 matW;				// GLScene world space matrix

uniform int backgroundPlane;	// Background enable or disable
uniform int textureMode;		// Texture mode camera or depth texture
uniform float minDistance;		// Minmal depth value
uniform float maxDistance;		// Maximal depth value
uniform float nearThreshold;	// Near threshold
uniform float farThreshold;		// Far threshold

uniform float cameraWidth;		// Camera texture width
uniform float cameraHeight;		// Camera texture height
uniform float depthWidth;		// Depth texture width
uniform float depthHeight;		// Depth texture height

attribute vec3 position;		// Vertex buffer values

varying vec2 texcoord;			// Texture coordinates
varying vec2 texcoordBg;		// Texture coordinates background
varying float isBackground;		// Is current pixel value in background plane?

void main()
{
	// Depth segmantation: Remove the kinect depth map shadow
	float depthValue = position.z;
	if(depthValue < nearThreshold)
	{
		depthValue = farThreshold;
	}
	if(depthValue > farThreshold)
	{
		depthValue = farThreshold;
	}
	/*
	// Destroy kinect depth shadow
	float positionZ = position.z;
	if(positionZ < minDistance)
	{
		positionZ = maxDistance;
	}
	*/
	// Transform GLScene to opject space
	float z = depthValue - ((farThreshold - nearThreshold) / 2.0f) - nearThreshold;

	if(depthValue < farThreshold)
	{
		// Transform GLScene to screen space with world matrix
		gl_Position = normalize( matVP * matW * vec4( position.x, position.y, -z, 1.0 ) );
		isBackground = 0.0f;
	}
	else
	{
		// Transform GLScene to screen space without world matrix
		gl_Position = normalize( matVP * vec4( position.x, position.y, -z, 1.0 ) );
		isBackground = 1;
	}
	
	// Background enable or disable
	if(backgroundPlane == 1)
	{
		isBackground = 0.0f;
	}
	
	// Compute texture coordinates from camera- or depth texture
	if(textureMode == 1)	// Use camera texture
	{
		// Flip texture space, because sensor origin upper left and texture origin lower left
		texcoord.x = position.x / cameraWidth;						// RGB map texture
		texcoord.y = (cameraHeight - position.y) / cameraHeight;	// RGB map texture
		texcoord.x += 0.5f;
		texcoord.y -= 0.5f;
	}
	else	// Use depth texture
	{
		texcoord.x = position.x / depthWidth;	// Depth map texture
		texcoord.y = position.y / cameraHeight;	// Depth map texture
		texcoord.x += 0.5f;
		texcoord.y += 0.5f;
	}
	
	// Flip texture space, because sensor origin upper left and texture origin lower left
	texcoordBg.x = position.x / cameraWidth;					// RGB map texture
	texcoordBg.y = (cameraHeight - position.y) / cameraHeight;	// RGB map texture
	texcoordBg.x += 0.5f;
	texcoordBg.y -= 0.5f;
}
