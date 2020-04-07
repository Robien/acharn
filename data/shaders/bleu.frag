form sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;


void main ( void )
{
	vec4 color = texture2D ( Texture1 , gl_TexCoord[0] );
	color = vec4 ( 0.0 , 0.0 , 0.2 , 0.0 ) + color;
	gl_FragColor = color;
}
