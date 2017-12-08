#include "headers.h"
#include "ppm.h"

#pragma once

#define GRAVITY 0.1
#define FRICTION 0.35
#define TOD_CARDINALITY 6 
#define TRANSITION_RATE_TOD 0.25
#define MAX_PLAYER 4
#define MAX_PLATFORM 4
#define MAX_STAR 40 
#define MAX_CLOUD 7
#define MAX_SPEED 15
#define MAX_STROKE 4
#define CLOUD_GROUP 3
#define CLOUD_START 50
#define CLOUD_RANGE 200
#define CORNERS 4
#define rnd() (float)rand() / (float)RAND_MAX
#define sm_rnd() (rand() - 0.5) / 255
#define M_PI 3.14159265358979323846
#define TRI_NUM 50
#define	HDX 1920
#define HDY 1080

enum State {MAIN, PAUSE, LEVELSEL, CHARSEL, FIELD, NIGHT, TIME, DISCO, POLLUTION};
enum Direction {LEFT, RIGHT};
enum TOD { DAY, AFTERNOON, EVENING, NITE, DNITE, MORNING };

inline void operator++(TOD &ti, int)
{
	const int i = static_cast<int>(ti);
	ti = static_cast<TOD>((i + 1) % TOD_CARDINALITY);
}

class Color {
public:
	float r, g, b, alpha;
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
	void set_color(Color clr);
	Line();
};
class Boundary {
public:
	GLfloat top;
	GLfloat bottom;
	GLfloat left;
	GLfloat right;
};
class Shape { // Make a circle and square inheretance class
public:
	GLfloat width, height;
	GLfloat radius;
	Boundary boundary;
	Color color;
	Vec center;
	Line stroke[MAX_STROKE];
	void stroke_assignment();
	void boundary_assignment();
	void render_quad();
	void render_circle();
	void set_color(Color clr);
};
class Circle : public Shape {
public:
};
class Quad :public Shape {
public:
};
class Resolution;
class Cloud {
public:
	Shape body[3];
	Direction direction;
	int speed;
	void render();
	void physics();
	void set_cloud_group(Resolution res);
	void handler(Resolution res);
};
class Star {
public:
	Shape body;
	GLfloat offset;
	void compute_coordinates(int count, Resolution res);
	void change_color();
};
class Particles {
public:
	Shape s;
	Vec velocity;
};

class Controller {
public:
	unsigned int id;
	bool singlePress[14] = { false };
	int buttonCount;
	const unsigned char *buttons;
};

class Level;
class Player {
public:
	Controller controller;
	bool on_ground;
	Vec	velocity;
	Shape body;
	Shape reflection;
	Shape eye;
	int JUMP_MAX;
	int jumpCount;
	Direction direction;
	void update_reflection_x();
	virtual void render(void) = 0;
	virtual void update_position(Level lvl) = 0;
	virtual void physics(Level lvl) = 0;
	virtual void jump(void) = 0;
	virtual void move(Direction dir) = 0;
	virtual void build(void) = 0;
	void read_input(Controller *c);
	virtual ~Player() {}
};
class Ball: public Player {
public:
	Shape outline;
	void render();
	void update_position(Level lvl);
	void physics(Level lvl);
	void move(Direction dir);
	void jump();
	void exhale();
	void build();
	~Ball() {}
};
class Boxy : public Player {
public:
	void render();
	void update_position(Level lvl);
	void physics(Level lvl);
	void move(Direction dir);
	void jump();
	void build();
	~Boxy() {}
};
class Platform {
public:
	Shape body;
};
class Menu {
public:
	Shape selector;
	virtual void handler() = 0;
	virtual void build() = 0;
};
class MainMenu : public Menu {
public:
	//void handler();
	//void build();
};
class PauseMenu : public Menu {
public:
	void handler();
	void build();
};
class LevelMenu : public Menu {
public:
	void handler();
	void build();
};
class RoundCornerBox {
public:
	GLfloat width, height;
	Vec center;
	Shape corner[CORNERS];
	Shape vRectangle; //vertical
	Shape hRectangle; //horizontal
	void set_color(Color clr);
	void build();
	void render();
};
class CharSelBox {
public:
	RoundCornerBox box;
	RoundCornerBox outline;
	GLfloat stroke;
};
class Palette{
public:
	Color sun;
	Color moon;
	Color platform;
	Color black;
	Color grey;
	Color darkGrey;
	Color lightGrey;
	Color white;
	Color red;
	Color darkRed;
	Color green;
	Color darkGreen;
	Color blue;
	Color darkBlue;
	Palette();
};

class Palette_BG {
public:
	Color day[CORNERS];
	Color afternoon[CORNERS];
	Color evening[CORNERS];
	Color night[CORNERS];
	Color dark_night[CORNERS];
	Color morning[CORNERS];
	Color overcast[CORNERS];
	Palette_BG();
};
class Background {
public:
	Shape body;
	Color color[4];
	bool transition_done[4];
	void render();
	void set_color(Color *clr);
};

class Resolution;
class CharacterSelectMenu {
public:
	Background background;
	CharSelBox selectBox[MAX_PLAYER];
	Shape cursor[MAX_PLAYER];
	void handler();
	void build(Resolution res, Palette pal);
};

class Assets;
class Level {
public:
	Background background;
	
	Platform platform[MAX_PLATFORM];
	Player *player[MAX_PLAYER] = {NULL}; //Polymorphism
	virtual ~Level() {}
};
class Field_Level : public Level {
public:
	Shape sun;
	Cloud clouds[MAX_CLOUD];
	void render();
	void handler(Level lvl, Resolution res);
	void build(Resolution res, Assets assets);
	~Field_Level();
};
class Night_Level : public Level {
public:
	Star stars[MAX_STAR];
	Shape moon;
	void render();
	void handler(Level lvl, Resolution res);
	void build(Resolution res, Assets assets);
	~Night_Level();
};
class Time_Level : public Level {
public:
	TOD time_of_day;
	bool transition;
	Shape sun;
	Shape moon;
	Star stars[MAX_STAR]; //change opacity during day
	Cloud clouds[MAX_CLOUD];
	void render();
	void handler(Level lvl, Resolution res, Assets assets);
	void transition_handler(Palette_BG palbg);
	void transition_to(Color *clr);
	void build(Resolution res, Assets assets);
	~Time_Level();
};

class Resolution {
public:
	int width, height;
	GLfloat ratio;
};

class Assets {
public:
	Palette palette;
	Palette_BG backgroundPalette;
	//ImageSet icons;
	//pImageSet picons;
	//sImageSet sicons;
};

class Menus {
public:
	//MainMenu mainMenu;
	CharacterSelectMenu chacterSelection;
};

class Levels {
public:
	Field_Level field;
	Night_Level night;
	Time_Level time;
};

class Game {
public:
	const GLFWvidmode *monitor;
	Resolution window;
	State render;
	Assets assets;
	Menus menus;
	Levels levels;
	void display_details();
	void set_resolution();
	Game();
};
















class Image {
public:
	char* filename;
	GLfloat w, h;
	GLfloat ratio;
	Shape box;
	ILuint imageID;
	GLuint textureID;
	ILboolean success;
	ILenum error;
	ILinfo ImageInfo;
	void texture_map();
	void render();
};
class SelectImage : public Image {
public:
	//_s flag designates selected icon
	bool chosen;
	Image selected;
	Image unselected;
};
class ImageSet {
public:
	//absence of _s flag designates unselected icon
	Image title;
	Image pill;
	SelectImage play;
	SelectImage options;
	SelectImage exit;
	SelectImage resume;
	SelectImage quit;
	Image level1;
	Image level2;
	void set_attributes();
};

class pImage {
public:
	Shape box;
	Ppmimage *img;
	GLuint sil;
	GLuint texture;
	GLuint w, h;
	GLfloat ratio;
	char* filename;
	void texture_map();
	void render();
	~pImage();
};
class pSelectImage : public pImage {
public:
	pImage selected;
};
class pImageSet {
public:
	pImage title;
	pImage pill;
	pSelectImage play;
	pSelectImage options;
	pSelectImage exit;
	pSelectImage resume;
	pSelectImage quit;
	pImage level1;
	pImage level2;
	void set_attributes();
};

class sImage {
public:
	Shape box;
	char *filename;
	GLint w, h;
	GLuint texture;
	void texture_map();
	void render();
};
class sSelectImage {
public:
	sImage unselected;
	sImage selected;
};
class sImageSet {
public:
	sImage title;
	sImage pill;
	sSelectImage play;
	sSelectImage options;
	sSelectImage exit;
	sSelectImage resume;
	sSelectImage quit;
	sImage level1;
	sImage level2;
	void set_attributes();
};
