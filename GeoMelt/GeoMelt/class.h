#include "headers.h"
#include "ppm.h"
#pragma once
/*
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_ACTIVE_TEXTURE 0x84E0
*/
#define TRANSITION_RATE 1
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
#define M_PI 3.14159265358979323846
#define TRI_NUM 50
#define	HDX 1920
#define HDY 1080
enum State {MAIN, PAUSE, LEVELSEL, CHARSEL, FIELD, NIGHT, TIME, DISCO, POLLUTION};
enum Direction {LEFT, RIGHT};
enum TOD { DAY, OVERCA, NITE, DNITE };

inline TOD operator++(TOD &eDOW, int)
{
	const int i = static_cast<int>(eDOW);
	eDOW = static_cast<TOD>((i + 1) % 4);
	return (TOD)0;
}

class Color {
public:
	int r, g, b;
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
	void handler();
	void render();
	void build_main_menu();
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
class Palette_Character {
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
class Palette_BG {
public:
	Color day[CORNERS];
	Color night[CORNERS];
	Color dark_night[CORNERS];
	Color overcast[CORNERS];
	Palette_BG();
};
class Background {
public:
	Shape body;
	Color color[4];
	bool transition_done[4];
	void render();
};
class Level {
public:
	Background background;
	Palette_BG palette;
	Player player[MAX_PLAYER];
	Platform platform[MAX_PLATFORM];
};
class Game;
class Field_Level : public Level {
public:
	Shape sun;
	Cloud clouds[MAX_CLOUD];
	Ball player1;
	Boxy player2;
	void render();
	void handler();
	Field_Level();
};
class Night_Level : public Level {
public:
	Star stars[MAX_STAR];
	Shape moon;
	Ball player1;
	Boxy player2;
	void render();
	void handler();
	Night_Level();
};
class Time_Level : public Level {
public:
	bool change;
	TOD time_of_day;
	Shape sun;
	Shape moon;
	Star stars[MAX_STAR]; //change opacity during day
	Cloud clouds[MAX_CLOUD];
	Ball player1;
	Boxy player2;
	void render();
	void handler();
	void transition_to(Color *clr);
	Time_Level();
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
	void loadImg();
	void render();
};
class SelectImage : public Image {
public:
	//_s flag designates selected icon
	bool selected;
	Image img_s;
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
class Resolution {
public:
	int width, height;
	GLfloat ratio;
};
class Initialize {
public:
	Initialize();
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
	//_s flag designates selected icon
	pImage selected;
};
class pImageSet {
public:
	//absence of _s flag designates unselected icon
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
	//_s flag designates selected icon
	sImage unselected;
	sImage selected;
};
class sImageSet {
public:
	//absence of _s flag designates unselected icon
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
class Game {
public:
	void game_inita();
	void game_initb();
	void game_details();
	Initialize init;
	MainMenu mainMenu;
	Palette_Character palette;
	Resolution monitor;
	Resolution win;
	State render;
	GLFWwindow *window;
	ImageSet icons;
	pImageSet picons;
	sImageSet sicons;
	Field_Level level1;
	Night_Level level2;
	Time_Level level3;
	Game();
};