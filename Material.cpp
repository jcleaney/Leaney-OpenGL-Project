//
// Material.cpp
//
// See header file for structural information.
//
//
// Created by Scott McDermott (mcdermottscott@yahoo.com)
// 08/16/04
//
// Modified by Scott McDermott (mcdermottscott@yahoo.com)
// 11/13/05
//


#include "Material.h"


Material::Material()
{
	setColor();
	fileIsLoaded = false;
}

bool Material::load(const char *file)
{
	strcpy(filename, file);
	static int lastid;

	id = lastid++;
	if (loadTGA(file, id) == 1)
	{
		fileIsLoaded = true;
		return true;
	}

	// Failed to open the file as a TARGA format image.
	printf("Failed to read Targa file.\n");
	fileIsLoaded = false;
	return false;
}



void Material::setColor(real amb0, real amb1, real amb2,
						real dif0, real dif1, real dif2, 
						real spec0, real spec1, real spec2,
						real specexp)
{
	mat_amb[0] = amb0;
	mat_amb[1] = amb1;
	mat_amb[2] = amb2;
	mat_amb[3] = 1;

	mat_dif[0] = dif0;
	mat_dif[1] = dif1;
	mat_dif[2] = dif2;
	mat_dif[3] = 1;

	mat_spec[0] = spec0;
	mat_spec[1] = spec1;
	mat_spec[2] = spec2;
	mat_spec[3] = 1;

	mat_spec_exp[0] = specexp;

}

void Material::setupMaterial()
{
	bool show_colors = true;
	// Try to go with the texture material first...
	if (fileIsLoaded)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	
	//  Otherwise, fall back on the other stuff...
	else if (show_colors)
	{
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_spec_exp);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glColor3f(mat_amb[0], mat_amb[1], mat_amb[2]);
	}
}

void Material::stopMaterial()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}


