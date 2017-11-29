#include "headers.h"

//Devil==========================================================================
void ImageSet::set_attributes()
{
	title.filename = "./resources/jpg/title.jpg";
	pill.filename = "./resources/jpg/pill.jpg";
	play.unselected.filename = "./resources/jpg/play_u.jpg";
	play.selected.filename = "./resources/jpg/play_s.jpg";
	options.unselected.filename = "./resources/jpg/options_u.jpg";
	options.selected.filename = "./resources/jpg/options_s.jpg";
	exit.unselected.filename = "./resources/jpg/exit_u.jpg";
	exit.selected.filename = "./resources/jpg/exit_s.jpg";
	resume.unselected.filename = "./resources/jpg/resume_u.jpg";
	resume.selected.filename = "./resources/jpg/resume_s.jpg";
	quit.unselected.filename = "./resources/jpg/quit_u.jpg";
	quit.selected.filename = "./resources/jpg/quit_s.jpg";
	level1.filename = "./resources/jpg/level1.jpg";
	level2.filename = "./resources/jpg/level2.jpg";

	title.texture_map();
	pill.texture_map();
	play.unselected.texture_map();
	play.selected.texture_map();
	options.unselected.texture_map();
	options.selected.texture_map();
	exit.unselected.texture_map();
	exit.selected.texture_map();
	resume.unselected.texture_map();
	resume.selected.texture_map();
	quit.unselected.texture_map();
	quit.unselected.texture_map();
	level1.texture_map();
	level2.texture_map();
}

void Image::texture_map()
{
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	success = ilLoadImage(filename);

	if (success)
	{
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		}

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());
		w = (GLfloat)ilGetInteger(IL_IMAGE_WIDTH);
		h = (GLfloat)ilGetInteger(IL_IMAGE_HEIGHT);
	}
	else
	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	std::cout << "Texture creation successful." << std::endl;
}

//PPM============================================================================
void pImageSet::set_attributes()
{
	cout << "***Loading Assets***" << endl;

	title.filename = "./resources/ppm/title.ppm";
	pill.filename = "./resources/ppm/pill.ppm";
	play.filename = "./resources/ppm/play_u.ppm";
	play.selected.filename = "./resources/ppm/play_s.ppm";
	options.filename = "./resources/ppm/options_u.ppm";
	options.selected.filename = "./resources/ppm/options_s.ppm";
	exit.filename = "./resources/ppm/exit_u.ppm";
	exit.selected.filename = "./resources/ppm/exit_s.ppm";
	resume.filename = "./resources/ppm/resume_u.ppm";
	resume.selected.filename = "./resources/ppm/resume_s.ppm";
	quit.filename = "./resources/ppm/quit_u.ppm";
	quit.selected.filename = "./resources/ppm/quit_s.ppm";
	level1.filename = "./resources/ppm/level1.ppm";
	level2.filename = "./resources/ppm/level2.ppm";

	title.texture_map();
	pill.texture_map();
	play.texture_map();
	play.selected.texture_map();
	options.texture_map();
	options.selected.texture_map();
	exit.texture_map();
	exit.selected.texture_map();
	resume.texture_map();
	resume.selected.texture_map();
	quit.texture_map();
	quit.selected.texture_map();
	level1.texture_map();
	level2.texture_map();
}

pImage::~pImage()
{
	ppm6CleanupImage(img);
}

void pImage::texture_map()
{
	//Load Images
	this->img = ppm6GetImage(this->filename);

	//Aspect Ratio
	this->w = img->width;
	this->h = img->height;

	this->ratio = (GLfloat)img->width / (GLfloat)img->height;

	//Texture
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->w, this->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
		img->data);

	//Silhouette
	glBindTexture(GL_TEXTURE_2D, this->sil);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char *sData = buildAlphaData(img);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->width, img->height,
		GL_RGBA, GL_UNSIGNED_BYTE, sData);

	free(sData);
}

//SOIL===========================================================================

void sImageSet::set_attributes()
{
	title.filename = "./resources/jpg/title.jpg";
	pill.filename = "./resources/jpg/pill.jpg";
	play.unselected.filename = "./resources/jpg/play_u.jpg";
	play.selected.filename = "./resources/jpg/play_s.jpg";
	options.unselected.filename = "./resources/jpg/options_u.jpg";
	options.selected.filename = "./resources/jpg/options_s.jpg";
	exit.unselected.filename = "./resources/jpg/exit_u.jpg";
	exit.selected.filename = "./resources/jpg/exit_s.jpg";
	resume.unselected.filename = "./resources/jpg/resume_u.jpg";
	resume.selected.filename = "./resources/jpg/resume_s.jpg";
	quit.unselected.filename = "./resources/jpg/quit_u.jpg";
	quit.selected.filename = "./resources/jpg/quit_s.jpg";
	level1.filename = "./resources/jpg/level1.jpg";
	level2.filename = "./resources/jpg/level2.jpg";

	title.texture_map();
	pill.texture_map();
	play.unselected.texture_map();
	play.selected.texture_map();
	options.unselected.texture_map();
	options.selected.texture_map();
	exit.unselected.texture_map();
	exit.selected.texture_map();
	resume.unselected.texture_map();
	resume.selected.texture_map();
	quit.unselected.texture_map();
	quit.unselected.texture_map();
	level1.texture_map();
	level2.texture_map();
}

void sImage::texture_map()
{
	//texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture == 0) { "ERROR"; };
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//Render==========================================================================
void Image::render()
{
	GLfloat A = this->box.center.x - this->box.width / 2;
	GLfloat B = this->box.center.y - this->box.height / 2;
	GLfloat C = this->box.center.y + this->box.height / 2;
	GLfloat D = this->box.center.x + this->box.width / 2;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(A, B);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(A, C);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(D, C);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(D, B);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void pImage::render()
{
	GLfloat A = this->box.center.x - this->box.width / 2;
	GLfloat B = this->box.center.y - this->box.height / 2;
	GLfloat C = this->box.center.y + this->box.height / 2;
	GLfloat D = this->box.center.x + this->box.width / 2;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(A, B);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(A, C);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(D, C);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(D, B);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void sImage::render()
{
	GLfloat A = this->box.center.x - this->box.width / 2;
	GLfloat B = this->box.center.y - this->box.height / 2;
	GLfloat C = this->box.center.y + this->box.height / 2;
	GLfloat D = this->box.center.x + this->box.width / 2;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(A, B);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(A, C);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(D, C);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(D, B);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}