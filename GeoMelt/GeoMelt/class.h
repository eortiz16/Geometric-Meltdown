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
#define MAX_CLOUD 10
#define MAX_SPEED 10
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
enum PlayerState { ALIVE, DEAD, ELIMINATED };

inline void operator++(TOD &ti, int)
{
	const int i = static_cast<int>(ti);
	ti = static_cast<TOD>((i + 1) % TOD_CARDINALITY);
}

class Attributes {
public:
	bool initDeath;
	double deathTimer;
	float health;
	int lifeCount;
	PlayerState lifeState;
	Attributes();
};
class Color {
public:
	float r, g, b, alpha;
	Color() {}
	Color(const Color &obj);
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
	void render();
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
};
class Circle : public Shape {
public:
	void render();
};
class Quad :public Shape {
public:
	void render();
	//Line stroke[MAX_STROKE];
	//void stroke_assignment();
};
class Resolution;
class Cloud {
public:
	Circle body[3];
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

class Controller {
public:
	unsigned int id;
	bool singlePress[14] = { false };
	int buttonCount;
	const unsigned char *buttons;
};

class Level;
class Platform;
class Assets;
class Player {
public:
	Controller controller;
	Attributes stats;
	bool on_ground;
	Vec	velocity;
	Shape body;
	Shape reflection;
	Shape eye;
	int JUMP_MAX;
	int jumpCount;
	Direction direction;
	void update_reflection_x();
	void respawn();
	void death_handler();
	virtual void render(void) = 0;
	virtual void update_position(Level lvl) = 0;
	virtual void physics(Platform *plat) = 0;
	virtual void jump(void) = 0;
	virtual void move(Direction dir) = 0;
	virtual void build(Assets assets) = 0;
	void read_input(Controller *c);
	virtual ~Player() {}
};
class Ball: public Player {
public:
	Shape outline;
	void render();
	void update_position(Level lvl);
	void physics(Platform *plat);
	void move(Direction dir);
	void jump();
	void exhale();
	void build(Assets assets);
	~Ball() {}
};
class Boxy : public Player {
public:
	void render();
	void update_position(Level lvl);
	void physics(Platform *plat);
	void move(Direction dir);
	void jump();
	void build(Assets assets);
	~Boxy() {}
};
class Platform {
public:
	Quad body;
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
	Circle corner[CORNERS];
	Quad vRectangle; //vertical
	Quad hRectangle; //horizontal
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
class Palette_CHAR {
public:
	// "_b" flag represents body color
	// "_r" flag represents reflection color
	Color red_b;
	Color red_r;
	Color green_b;
	Color green_r;
	Color blue_b;
	Color blue_r;
	Color yellow_b;
	Color yellow_r;
	Color pink_b;
	Color pink_r;
	Color purple_b;
	Color purple_r;
	Color white_b;
	Color white_r;
	Color black_b;
	Color black_r;
	Palette_CHAR();
};
class Background {
public:
	Quad body;
	Color color[4];
	bool transition_done[4];
	void render();
	void set_color(Color *clr);
};

class Resolution;
class Assets;
class CharacterSelectMenu {
public:
	Background background;
	CharSelBox selectBox[MAX_PLAYER];
	Shape cursor[MAX_PLAYER];
	void handler();
	void build(Assets assets);
};

class Assets;
class Level {
public:
	Background background;
	void physics(Level lvl);
	void camera(Level lvl);
	Platform platform[MAX_PLATFORM];
	Player *player[MAX_PLAYER] = {NULL}; //Polymorphism
	virtual ~Level() {}
};
class Field_Level : public Level {
public:
	Shape sun;
	Cloud clouds[MAX_CLOUD];
	void render();
	void handler();
	
	void build(Assets assets);
	~Field_Level();
};
class Night_Level : public Level {
public:
	Star stars[MAX_STAR];
	Shape moon;
	void render();
	void handler();

	void build(Assets assets);
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
	void handler();
	
	void transition_handler(Palette_BG pal);
	void transition_to(Color *clr);
	void build(Assets assets);
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
	Palette_CHAR characterPalette;
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
