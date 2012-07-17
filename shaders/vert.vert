// [Vertex shader]
// Circles with GL_POINTS
varying vec2 pos;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
	
	pos = vec2(gl_Position.x,gl_Position.y);
}
