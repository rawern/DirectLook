#version 120

attribute vec2 position;

varying vec2 texcoord;

void main()
{
	vec4 pos = vec4( position.x, position.y, 0.0, 1.0 );
	gl_Position = pos;
	texcoord = vec2( pos.x, pos.y ) * vec2( 0.5 ) + vec2( 0.5 );
}











