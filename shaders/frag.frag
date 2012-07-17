// [Fragment shader]
// Circles with GL_POINTS
varying vec2 pos;

#define radius2 0.1

void main() {
	
	if (pos.x < -0.02 && pos.x > -0.7)
		gl_FragColor = vec4(0.0,pow((0.9-(-10.0*pos.x)),0.77),0.0,0.0);
	if(pos.x > 0.02 && pos.x < 0.4)
		gl_FragColor = vec4(0.0,pow((0.9-(10.0*pos.x)),0.77),0.0,0.0);
	if(pos.x > -0.02 && pos.x < 0.02)
		gl_FragColor = vec4(0.0,0.76,0.0,0.0);
//	else
//	   	gl_FragColor = vec4(1.0,0.0,0.4,0.0); 
	
}
