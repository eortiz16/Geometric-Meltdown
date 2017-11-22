#include "Headers.h"
#include "ppm.h"
#pragma once
#define MAX_PLAYER 4
#define MAX_PLATFORM 4
#define MAX_STAR 40 
#define MAX_CLOUD 7
#define MAX_SPEED 15
#define MAX_STROKE 4
#define CLOUD_GROUP 3
#define CLOUD_START 50
#define CLOUD_RANGE 200
#define rnd() (float)rand() / (float)RAND_MAX
#define M_PI 3.14159265358979323846
#define TRI_NUM 50
#define	HDX 1920
#define HDY 1080
enum State {MAIN, PAUSE, LEVELSEL, CHARSEL, FIELD, NIGHT, DISCO, POLLUTION};
enum Direction {LEFT, RIGHT};
class Color {
public:
	int r, g, b;
};
class Colors {
public: 
	Color Pink;
	Color red;
	Color green;
	Color blue;
	Color darkRed;
	Color darkGreen;
	Color darkBlue;
	Color Purple;
};
class Vec {
public:
	GLfloat x, y, z;
};
class Line {
public:
	GLfloat width;
	Vec from, to;
	Color color;
	void render_line();
	Line();
};
class Shape {
public:
	GLfloat width, height;
	GLfloat radius;
	Vec center;
	Line stroke[MAX_STROKE];
	void stroke_assignment();
	void render_quad();
	void render_circle();
	Color color;
};
class Cloud {
public:
	//if small go slow
	//if big go faster
	Shape body[3];
	Direction direction;
	int speed;
	void render();
	void physics();
	void set_cloud_group();
	void handler();
};
class Star {
public:
	Shape body;
	GLfloat offset;
	void compute_coordinates(int count);
	void change_color();
};
class Particles {
public:
	Shape s;
	Vec velocity;
};
class Player {
public:
	Shape body;
	Shape reflection;
	Shape eye;
	int JUMP_MAX;
	int jumpCount;
	Direction direction;
	void update_reflection_x();
};
class Ball: public Player {
public:
	Shape outline;
	void render();
	void update_position();
	Ball();
};
class Boxy : public Player {
public:
	void render();
	void update_position();
	Boxy();
};
class Platform {
public:
	Shape body;
};
class Menu {
public:
	Shape selector;
};
class MainMenu : public Menu {
public:
	Shape title;
	Shape play;
	Shape options;
	Shape quit;
	void handler();
	void render();
	MainMenu();
};
class PauseMenu : public Menu {
public:
};
class LevelMenu : public Menu {
public:
};
class CharacterSelect {
public:
	Shape selection[MAX_PLAYER];
};
class Background {
public:
	Shape body;
	Color color[4];
	void render();
};
class Level {
public:
	Player player[MAX_PLAYER];
	Platform platform[MAX_PLATFORM];
	Background background;
	Level() {}
};
class Game;
class Field_Level : public Level {
public:
	void render();
	void handler();
	Shape sun;
	Cloud clouds[MAX_CLOUD];
	Ball player1;
	Boxy player2;
	Field_Level();
};
class Night_Level : public Level {
public:
	GLfloat w, h;
	GLfloat starOffset[MAX_STAR];
	Star stars[MAX_STAR];
	Shape moon;
	void render();
	void handler();
	Ball player1;
	Boxy player2;
	Night_Level();
};
class Image {
public:
	Ppmimage *img;
	GLuint sil;
	GLuint texture;
	GLfloat ratio;
	void texture_map();
};
class ImageSet {
public:
	//_u flag designates unselected icon
	//_s flag designates selected icon
	Image title;
	Image pill;
	Image play_u;
	Image play_s;
	Image options_u;
	Image options_s;
	Image exit_u;
	Image exit_s;
	Image resume_u;
	Image resume_s;
	Image quit_u;
	Image quit_s;
	Image level1;
	Image level2;
	ImageSet();
};
class Resolution {
public:
	int width, height;
	GLfloat ratio;
};
class Game {
public:
	void game_inita();
	void game_initb();
	void game_details();
	MainMenu mainMenu;
	Colors palette;
	Resolution monitor;
	Resolution win;
	State render;
	GLFWwindow *window;
	ImageSet icons;
	Field_Level level1;
	Night_Level level2;
	Game();
};