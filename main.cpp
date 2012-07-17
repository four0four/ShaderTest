#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string.h>
#include "shaders.h"

shader *testShader;
int videoFlags, yres, xres;
bool running = true;
std::string vertexFile;
std::string fragmentFile;

#define _DEFAULT_XRES 480
#define _DEFAULT_YRES 480

/* function to release/destroy our resources and restoring the old desktop */
void quit(int returnCode) {
    SDL_Quit();
    exit(returnCode);
}

void reloadShaders(){
	testShader->deleteSources();
	testShader->useShader(false);
	testShader->loadFromFile(vertexFile,fragmentFile);
	testShader->compileShader();
	testShader->linkShader();
	testShader->printLog(testShader->programObject);
	testShader->useShader(true);
}

/* function to handle key press events */
void handleKeyPress(SDL_keysym *keysym) {
    switch (keysym->sym)
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    quit(0);
	    break;
	case SDLK_r:
		reloadShaders();
		break;
	default:
	    break;
	}

    return;
}


void render() {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_QUADS);
			glColor3f(1.0f,0.0f,0.0f);  
			glVertex2d(-1,-1);
			glColor3f(1.0f,1.0f,0.0f);
			glVertex2d(1,-1);
			glColor3f(1.0f,0.0f,1.0f);
			glVertex2d(1,1);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex2d(-1,1);
		glEnd();
		SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) {
	if (argc < 3 || argc > 5) {
		printf("Usage: %s <vertexfile> <fragmentfile> [(xres) (yres)]\n",argv[0]);
		quit(0);
	}

	if (argc > 3) {
		xres = atoi(argv[3]);
		yres = atoi(argv[4]);
	}
	else
	{
		xres = _DEFAULT_XRES;
		yres = _DEFAULT_YRES;
	}

	testShader = new shader;

	SDL_Surface * surface;
	SDL_Event event;

	printf("\n(r) to reload and recompile the shader from disk\n[esc] to close\n\n");

	fragmentFile = argv[2];
	vertexFile = argv[1];

	SDL_Init(SDL_INIT_VIDEO);
	/* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */

	SDL_SetVideoMode(xres,yres,32,videoFlags);
	SDL_WM_SetCaption("GLSL Shader Test Bed", NULL);

	glewInit();
	glViewport(0,0,xres,480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	testShader->loadFromFile(argv[1],argv[2]);
	testShader->compileShader();
	testShader->linkShader();
	testShader->printLog(testShader->programObject);

	testShader->useShader(true);

	while(running) 	{
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_KEYDOWN:
				handleKeyPress(&event.key.keysym);
				break;
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
	render();
	}
	
	return 0;
}
