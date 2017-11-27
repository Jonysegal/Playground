uniform float time;
uniform sampler2D texture;


void main(void)
{
vec2 uv = gl_TexCoord[0].xy;


float f = 20.0; //frequency
float a = 0.004; //amplitude

uv.y += a*sin(f*(uv.x + time));

gl_FragColor = texture2D( texture, uv );
}