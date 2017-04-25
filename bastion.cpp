#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "particleSystem.h"


#define COLOR_BEIGE 245.0f / 255.0f, 245.0f / 255.0f, 220.0f / 255.0f
#define COLOR_GRAY 105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f
#define COLOR_CYAN 0.0f, 1.0f, 1.0f
#define COLOR_ORANGE 1.0f ,140.0f / 255.0f , 0.0f
#define COLOR_OLIVE 61.0f / 255.0f, 240.0f / 255.0f , 159.0f / 255.0f
#define COLOR_METAL 224.0f / 255.0f, 224.0f / 255.0f, 224.0f / 255.0f

#define NUM_OF_BTMUZZLE 8

#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))
#define SET(x, val) (ModelerApplication::Instance()->SetControlValue(x, val))

enum SampleModelControls
{
	XPOS, YPOS, ZPOS, XROTATE, YROTATE, ZROTATE, UPPER_BODY_ROTATE, LOWER_BODY_ROTATE, HEAD_ROTATE, HEAD_X_TILT, HEAD_Z_TILT,
	LEFT_SHOULDER_X_ROTATE, LEFT_SHOULDER_Y_ROTATE, LEFT_SHOULDER_Z_ROTATE, LEFT_UPPER_ARM_Y_ROTATE, LEFT_LOWER_ARM_X_ROTATE, LEFT_LOWER_ARM_Y_ROTATE,
	WRIST_X_ROTATE, WRIST_Y_ROTATE, WRIST_Z_ROTATE, THUMB_PROXIMAL_ROTATE, THUMB_MIDDLE_ROTATE, THUMB_DISTAL_ROTATE, INDEX_PROXIMAL_ROTATE, INDEX_MIDDLE_ROTATE, INDEX_DISTAL_ROTATE,
	MIDDLE_PROXIMAL_ROTATE, MIDDLE_MIDDLE_ROTATE, MIDDLE_DISTAL_ROTATE, RING_PROXIMAL_ROTATE, RING_MIDDLE_ROTATE, RING_DISTAL_ROTATE, PINKY_PROXIMAL_ROTATE, PINKY_MIDDLE_ROTATE, PINKY_DISTAL_ROTATE,
	RIGHT_SHOULDER_X_ROTATE, RIGHT_SHOULDER_Y_ROTATE, RIGHT_SHOULDER_Z_ROTATE, RIGHT_UPPER_ARM_Y_ROTATE, GUN_X_ROTATE, GUN_Y_ROTATE, GUN_Z_ROTATE,
	LEFT_UPPER_LEG_X_ROTATE, LEFT_UPPER_LEG_Y_ROTATE, LEFT_MIDDLE_LEG_X_ROTATE, LEFT_LOWER_LEG_X_ROTATE, LEFT_FOOT_X_ROTATE,
	RIGHT_UPPER_LEG_X_ROTATE, RIGHT_UPPER_LEG_Y_ROTATE, RIGHT_MIDDLE_LEG_X_ROTATE, RIGHT_LOWER_LEG_X_ROTATE, RIGHT_FOOT_X_ROTATE,
	DETAILS,
	LIGHT_TEST,
	MOOD,
	ANIMATE,
	NUMCONTROLS
};

// To make a SampleModel, we inherit off of ModelerView
class BastionModel : public ModelerView
{
public:
	BastionModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();

	void reset();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createBastionModel(int x, int y, int w, int h, char *label)
{
	return new BastionModel(x, y, w, h, label);
}

double lshoulderx, lupperarmy, llowerarmx, lwristy;
bool posdeg = true;
bool anibool = false;

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void BastionModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
/*	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();
*/

	if (VAL(MOOD) == 1) {
		reset();
		SET(LOWER_BODY_ROTATE, -31);
		SET(HEAD_Z_TILT, 11);
		SET(LEFT_SHOULDER_X_ROTATE, 53);
		SET(LEFT_LOWER_ARM_X_ROTATE, 125);
		SET(LEFT_LOWER_ARM_Y_ROTATE, 8);
		SET(WRIST_X_ROTATE, 29);
		SET(WRIST_Y_ROTATE, -29);
		SET(RIGHT_SHOULDER_Y_ROTATE, 28);
		SET(RIGHT_SHOULDER_Z_ROTATE, 16);
		SET(RIGHT_UPPER_ARM_Y_ROTATE, -12);
		SET(GUN_X_ROTATE, 45);
		SET(GUN_Y_ROTATE, -20);
		SET(GUN_Z_ROTATE, 1);
		SET(LEFT_UPPER_LEG_X_ROTATE, 40);
		SET(LEFT_UPPER_LEG_Y_ROTATE, 20);
		SET(LEFT_MIDDLE_LEG_X_ROTATE, 90);
		SET(LEFT_LOWER_LEG_X_ROTATE, 60);
		SET(LEFT_FOOT_X_ROTATE, 12);
		SET(RIGHT_UPPER_LEG_X_ROTATE, 15);
		SET(RIGHT_UPPER_LEG_Y_ROTATE, 20);
		SET(RIGHT_MIDDLE_LEG_X_ROTATE, 90);
		SET(RIGHT_LOWER_LEG_X_ROTATE, 60);
		SET(RIGHT_FOOT_X_ROTATE, -19);
	}
	else if (VAL(MOOD) == 2) {
		reset();
		SET(HEAD_X_TILT, -25);
		SET(HEAD_Z_TILT, -15);
		SET(LEFT_SHOULDER_X_ROTATE, -38);
		SET(LEFT_LOWER_ARM_X_ROTATE, 10);
		SET(WRIST_Y_ROTATE, 66);
		SET(WRIST_Z_ROTATE, 71);
		SET(RIGHT_SHOULDER_X_ROTATE, -38);
		SET(RIGHT_UPPER_ARM_Y_ROTATE, -30);
		SET(GUN_X_ROTATE, -15);
		SET(GUN_Y_ROTATE, -16);
		SET(GUN_Z_ROTATE, -36);
		SET(LEFT_UPPER_LEG_X_ROTATE, 90);
		SET(LEFT_MIDDLE_LEG_X_ROTATE, 5);
		SET(LEFT_LOWER_LEG_X_ROTATE, 30);
		SET(RIGHT_UPPER_LEG_X_ROTATE, 90);
		SET(RIGHT_MIDDLE_LEG_X_ROTATE, 5);
		SET(RIGHT_LOWER_LEG_X_ROTATE, 30);
	}
	else if (VAL(MOOD) == 3) {
		reset();
		SET(XROTATE, 25);
		SET(HEAD_X_TILT, 25);
		SET(LEFT_SHOULDER_X_ROTATE, 25);
		SET(LEFT_LOWER_ARM_X_ROTATE, 0);
		SET(RIGHT_SHOULDER_X_ROTATE, 25);
		SET(GUN_X_ROTATE, 45);
		SET(LEFT_UPPER_LEG_X_ROTATE, 55);
		SET(LEFT_MIDDLE_LEG_X_ROTATE, 75);
		SET(LEFT_LOWER_LEG_X_ROTATE, 55);
		SET(RIGHT_UPPER_LEG_X_ROTATE, 55);
		SET(RIGHT_MIDDLE_LEG_X_ROTATE, 75);
		SET(RIGHT_LOWER_LEG_X_ROTATE, 55);
	}
	else if (VAL(MOOD) == 4) {
		reset();
		SET(LOWER_BODY_ROTATE, 10);
		SET(HEAD_ROTATE, -25);
		SET(LEFT_SHOULDER_X_ROTATE, -30);
		SET(LEFT_LOWER_ARM_X_ROTATE, 85);
		SET(GUN_X_ROTATE, 45);
		SET(GUN_Y_ROTATE, -25);
		SET(LEFT_UPPER_LEG_X_ROTATE, 0);
		SET(LEFT_FOOT_X_ROTATE, 25);
		SET(RIGHT_UPPER_LEG_X_ROTATE, 45);
		SET(RIGHT_FOOT_X_ROTATE, 15);
	}

	if (VAL(ANIMATE))
	{
		lshoulderx = 90;
		llowerarmx = 90;
		lwristy = -90;
		if (lupperarmy >= 30)
			posdeg = false;
		else if (lupperarmy <= -30)
			posdeg = true;
		posdeg ? lupperarmy++ : lupperarmy--;
	}
	else
	{
		lshoulderx = VAL(LEFT_SHOULDER_X_ROTATE);
		lupperarmy = VAL(LEFT_UPPER_ARM_Y_ROTATE);
		llowerarmx = VAL(LEFT_LOWER_ARM_X_ROTATE);
		lwristy = VAL(WRIST_Y_ROTATE);
	}
	

	// draw the bastion model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GRAY);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// translate whole body first
		glTranslated(0, 0, 0.5);
		
		glRotated(VAL(YROTATE), 0, 1.0, 0);
		glRotated(VAL(XROTATE), 1.0, 0, 0);
		glRotated(VAL(ZROTATE), 0, 0, 1.0);

		// draw upper body
		// draw waist
		glPushMatrix();
		glRotated(VAL(UPPER_BODY_ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0, 0); // x' = x, y' = -z, z' = y
		if (VAL(DETAILS) >= 3) {
			drawCylinder(0.2, 0.75, 0.75);
			glTranslated(0, 0, 0.2);
			drawCylinder(1, 0.5, 0.5);
		}
		else {
			drawCylinder(1.2, 0.5, 0.5);
			glTranslated(0, 0, 0.2);
		}
		if (VAL(DETAILS) >= 4) {
			glTranslated(0, 0, 0.25);
			drawTorus(0.1, 0.35, 200, 100, 0);
			glTranslated(0, 0, -0.25);
		}

		// return to origin, reset axis
		glRotated(90, 1.0, 0, 0);
		glTranslated(0, -2, -0.5);

		// draw body (beige)
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_BEIGE);
		if (VAL(DETAILS) < 4) {
			glTranslated(-1, 2.5, -0.75);
			drawBox(2, 1.5, 3);
			glTranslated(1, -2.5, 0.75);
		}
		else {
			// front
			drawTriangle(-1, 4, -0.5, -1, 4, 1.5, 1, 4, -0.5);
			drawTriangle(-1, 4, 1.5, 1, 4, 1.5, 1, 4, -0.5);
			drawTriangle(1, 4, 1.5, -1, 4, 1.5, 0.75, 3.25, 2.5);
			drawTriangle(0.75, 3.25, 2.5, -1, 4, 1.5, -0.75, 3.25, 2.5);
			drawTriangle(0.75, 3.25, 2.5, -0.75, 3.25, 2.5, 0.75, 2.75, 2.25);
			drawTriangle(-0.75, 3.25, 2.5, -0.75, 2.75, 2.25, 0.75, 2.75, 2.25);
			// right side
			drawTriangle(-1, 2.75, 1.75, -0.75, 2.75, 2.25, -0.75, 3.25, 2.5);
			drawTriangle(-0.75, 3.25, 2.5, -1, 4, 1.5, -1, 2.75, 1.75);
			drawTriangle(-1, 4, 1.5, -1, 3, 0.5, -1, 2.75, 1.75);
			drawTriangle(-1, 2.75, 1.75, -1, 3, 0.5, -1, 2.5, 1.25);
			drawTriangle(-1, 3, 0.5, -1, 4, 1.5, -1, 4, 0.5);
			// left side
			drawTriangle(1, 2.75, 1.75, 0.75, 3.25, 2.5, 0.75, 2.75, 2.25);
			drawTriangle(0.75, 3.25, 2.5, 1, 2.75, 1.75, 1, 4, 1.5);
			drawTriangle(1, 4, 1.5, 1, 2.75, 1.75, 1, 3, 0.5);
			drawTriangle(1, 2.75, 1.75, 1, 2.5, 1.25, 1, 3, 0.5);
			drawTriangle(1, 3, 0.5, 1, 4, 0.5, 1, 4, 1.5);
			// bottom
			drawTriangle(-0.75, 2.75, 2.25, -1, 2.75, 1.75, 1, 2.75, 1.75);
			drawTriangle(-0.75, 2.75, 2.25, 1, 2.75, 1.75, 0.75, 2.75, 2.25);
			drawTriangle(-1, 2.75, 1.75, 1, 2.5, 1.25, 1, 2.75, 1.75);
			drawTriangle(-1, 2.75, 1.75, -1, 2.5, 1.25, 1, 2.5, 1.25);
			drawTriangle(-1, 2.5, 1.25, 1, 3, 0.5, 1, 2.5, 1.25);
			drawTriangle(-1, 2.5, 1.25, -1, 3, 0.5, 1, 3, 0.5);
			// gray part
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			// left
			drawTriangle(-1, 4, -0.5, -1, 3, 0.5, -1, 4, 0.5);
			drawTriangle(-1, 4, -0.5, -1, 3, -0.5, -1, 3, 0.5);
			// right
			drawTriangle(1, 4, 0.5, 1, 3, -0.5, 1, 4, -0.5);
			drawTriangle(1, 4, 0.5, 1, 3, 0.5, 1, 3, -0.5);
			// bottom
			drawTriangle(-1, 3, 0.5, -1, 3, -0.5, 1, 3, -0.5);
			drawTriangle(-1, 3, 0.5, 1, 3, -0.5, 1, 3, 0.5);
			// back
			drawTriangle(1, 4, -0.5, -1, 3, -0.5, -1, 4, -0.5);
			drawTriangle(1, 4, -0.5, 1, 3, -0.5, -1, 3, -0.5);
		}


			// draw neck
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(-0.375, 4, 0.25);
			glScaled(0.75, 0.5, 0.5);
			drawBox(1, 1, 1);

			// draw head
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glScaled(0.85 / 0.75, 2, 2);
			glTranslated(-0.05, 0.5, -0.25);
			glTranslated(0.5, 0, 0.5);
			glRotated(VAL(HEAD_ROTATE), 0.0, 1.0, 0.0);
			glRotated(VAL(HEAD_X_TILT), 1.0, 0, 0);
			glRotated(VAL(HEAD_Z_TILT), 0, 0, 1.0);
			glTranslated(-0.5, 0, -0.5);
			drawBox(1, 1, 1);

			if (VAL(DETAILS) > 4) {
				// draw eye
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_CYAN);
				glTranslated(1.5*0.25, 0.5*0.6, 5*0.2);
				drawBox(.25, .6, .1);
			}
				glPopMatrix();



			// draw back turret
			glPushMatrix();

			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0, 3, -1.25);
			glRotated(-90, 1.0, 0, 0);
			drawCylinder(0.75, 0.75, 0.75);

			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0, 0, 0.75);
			drawCylinder(2.5, 0.6, 0.6);

			if (VAL(DETAILS) > 2) {
				// draw back turret muzzle
				glTranslated(0, 0, 2.5);
				
				drawCylinder(0.2, 0.7, 0.7);
				if (VAL(DETAILS) > 3) {
					glTranslated(0, 0, 0.2);
					for (int i = 0; i < NUM_OF_BTMUZZLE; i++)
					{
						glTranslated(0, 0.45, 0);
						drawCylinder(0.2, 0.15, 0.15);
						glTranslated(0, -0.45, 0);
						glRotated(360 / NUM_OF_BTMUZZLE, 0.0, 0.0, 1.0);
					}
				}
			}

			glPopMatrix();

			// draw left limb
			// draw left shoulders (movable & shoulder plates)
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_ORANGE);
			glTranslated(1, 3.25, -0.375);
			
			glTranslated(0, 0.5, 0);
			glRotated(VAL(LEFT_SHOULDER_Z_ROTATE), 0.0, 0.0, 1.0);
			glTranslated(0, -0.5, 0);

			glTranslated(0, 0, 0.5);
			glRotated(VAL(LEFT_SHOULDER_Y_ROTATE), 0.0, 1.0, 0.0);
			glTranslated(0, 0, -0.5);

			glTranslated(0, 0.5, 0.5);
			glRotated(-lshoulderx, 1.0, 0.0, 0.0);
			glTranslated(0, -0.5, -0.5);

			glScaled(1, 0.5, 0.75);
			drawBox(1, 1, 1);

			// draw shoulder plates
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0.5, 1.25, 0);
			glScaled(1, 0.5, 1); // 1, .25, .75
			drawBox(1, 1, 1);
			glTranslated(0.75, 0, 0);
			glScaled(0.25, -4, 1); // .25, -1, .75
			drawBox(1, 1, 1);

			// reset transformation to start of shoulder
			glScaled(4, -0.25, 1);
			glTranslated(-0.75, 0, 0);
			glScaled(1, 2, 1);
			glTranslated(-0.5, -1.25, 0);
			glScaled(1, 2, 1/0.75); 

				// draw left upper arm
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_OLIVE);
				glTranslated(0.5, 0, 0.125);

				glTranslated(0.25, 0, 0.25);
				glRotated(lupperarmy, 0.0, -1.0, 0.0);
				glTranslated(-0.25, 0, -0.25);

				glScaled(0.5, -1.5, 0.5);
				drawBox(1, 1, 1);
				// reset scale
				glScaled(2, 1 / -1.5, 2);

					// draw left lower arm
					glPushMatrix();

					glTranslated(0.25, -1.5, 0.25);
					glRotated(VAL(LEFT_LOWER_ARM_Y_ROTATE), 0, 1.0, 0);
					if (VAL(DETAILS) > 1) {
						glTranslated(-0.275, 0, 0);
						glRotated(90, 0, 1.0, 0);
						drawCylinder(.55, .275, .275);
						glRotated(-90, 0, 1.0, 0);
						glTranslated(0.275, 0, 0);
					}
					glRotated(llowerarmx, -1.0, 0, 0);
					glTranslated(-0.25, 0, -0.25);

					glScaled(0.5, -1.5, 0.5);
					drawBox(1, 1, 1);
					// reset scale
					glScaled(2, 1 / -1.5, 2);
					
						// draw hand
						// draw palm
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glPushMatrix();
						glTranslated(0.125, -1.6, 0);

						glTranslated(0.125, 0, 0.25);
						glRotated(lwristy, 0, 1.0, 0);
						glRotated(VAL(WRIST_X_ROTATE), 1.0, 0, 0);
						glRotated(VAL(WRIST_Z_ROTATE), 0, 0, 1.0);
						glTranslated(-0.125, 0, -0.25);

						drawBox(0.25, -0.5, 0.5);
						if(VAL(DETAILS) > 1) {
							// draw thumb
							// proximal phalanx
							glPushMatrix();
							glTranslated(0.1, -0.1, 0.6);
							if(VAL(DETAILS)>4)
								drawSphere(0.075);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							glRotated(VAL(THUMB_PROXIMAL_ROTATE), -1.0, 0, 0);
							glRotated(30, 0, 0, 1.0);
							if (VAL(DETAILS) > 3) {
								drawCylinder(0.175, 0.075, 0.075);
							}
							else if (VAL(DETAILS) > 2) {
								glTranslated(-0.075, -0.075, 0);
								drawBox(0.15, 0.15, 0.175);
								glTranslated(0.075, 0.075, 0);
							}
							else {
								glTranslated(-0.075, -0.075, 0);
								drawBox(0.15, 0.15, 0.475);
								glTranslated(0.075, 0.075, 0);
							}
								// middle phalanx
								glPushMatrix();
								glTranslated(0, 0, 0.2);
								if (VAL(DETAILS)>4)
									drawSphere(0.075);
								glRotated(VAL(THUMB_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								if (VAL(DETAILS) > 3) {
									drawCylinder(0.15, 0.075, 0.07);
								}
								else if (VAL(DETAILS) > 2) {
									glTranslated(-0.07, -0.07, 0);
									drawBox(0.14, 0.14, 0.15);
									glTranslated(0.07, 0.07, 0);
								}
									// distal phalanx
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									if (VAL(DETAILS)>4)
										drawSphere(0.07);
									glRotated(VAL(THUMB_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									if (VAL(DETAILS) > 3) {
										drawCylinder(0.1, 0.07, 0.065);
									}
									else if (VAL(DETAILS) > 2) {
										glTranslated(-0.065, -0.065, 0);
										drawBox(0.13, 0.13, 0.1);
										glTranslated(0.065, 0.065, 0);
									}
									glTranslated(0, 0, 0.1);
									if (VAL(DETAILS)>4)
										drawSphere(0.065);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// draw 4 fingers
							// index
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.44);
							if (VAL(DETAILS)>4)
								drawSphere(0.06);
							glRotated(VAL(INDEX_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							if (VAL(DETAILS) > 3) {
								drawCylinder(0.15, 0.06, 0.06);
							}
							else if (VAL(DETAILS) > 2) {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.15);
								glTranslated(0.06, 0.06, 0);
							}
							else {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.45);
								glTranslated(0.06, 0.06, 0);
							}
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.175);
								if (VAL(DETAILS)>4)
									drawSphere(0.06);
								glRotated(VAL(INDEX_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								if (VAL(DETAILS) > 3) {
									drawCylinder(0.15, 0.06, 0.05);
								}
								else if (VAL(DETAILS) > 2) {
									glTranslated(-0.05, -0.05, 0);
									drawBox(0.1, 0.1, 0.15);
									glTranslated(0.05, 0.05, 0);
								}
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									if (VAL(DETAILS)>4)
										drawSphere(0.05);
									glRotated(VAL(INDEX_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									if (VAL(DETAILS) > 3) {
										drawCylinder(0.1, 0.05, 0.04);
									}
									else if (VAL(DETAILS) > 2) {
										glTranslated(-0.04, -0.04, 0);
										drawBox(0.08, 0.08, 0.1);
										glTranslated(0.04, 0.04, 0);
									}
									glTranslated(0, 0, 0.1);
									if (VAL(DETAILS)>4)
										drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// middle
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.3);
							if (VAL(DETAILS)>4)
								drawSphere(0.06);
							glRotated(VAL(MIDDLE_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							if (VAL(DETAILS) > 3) {
								drawCylinder(0.2, 0.06, 0.06);
							}
							else if (VAL(DETAILS) > 2) {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.2);
								glTranslated(0.06, 0.06, 0);
							}
							else {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.5);
								glTranslated(0.06, 0.06, 0);
							}
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.225);
								if (VAL(DETAILS)>4)
									drawSphere(0.06);
								glRotated(VAL(MIDDLE_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								if (VAL(DETAILS) > 3) {
									drawCylinder(0.15, 0.06, 0.05);
								}
								else if (VAL(DETAILS) > 2) {
									glTranslated(-0.05, -0.05, 0);
									drawBox(0.1, 0.1, 0.15);
									glTranslated(0.05, 0.05, 0);
								}
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									if (VAL(DETAILS)>4)
										drawSphere(0.05);
									glRotated(VAL(MIDDLE_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									if (VAL(DETAILS) > 3) {
										drawCylinder(0.1, 0.05, 0.04);
									}
									else if (VAL(DETAILS) > 2) {
										glTranslated(-0.04, -0.04, 0);
										drawBox(0.08, 0.08, 0.1);
										glTranslated(0.04, 0.04, 0);
									}
									glTranslated(0, 0, 0.1);
									if (VAL(DETAILS)>4)
										drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// ring
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.16);
							if (VAL(DETAILS)>4)
								drawSphere(0.06);
							glRotated(VAL(RING_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							if (VAL(DETAILS) > 3) {
								drawCylinder(0.15, 0.06, 0.06);
							}
							else if (VAL(DETAILS) > 2) {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.15);
								glTranslated(0.06, 0.06, 0);
							}
							else {
								glTranslated(-0.06, -0.06, 0);
								drawBox(0.12, 0.12, 0.45);
								glTranslated(0.06, 0.06, 0);
							}
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.175);
								if (VAL(DETAILS)>4)
									drawSphere(0.06);
								glRotated(VAL(RING_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								if (VAL(DETAILS) > 3) {
									drawCylinder(0.15, 0.06, 0.05);
								}
								else if (VAL(DETAILS) > 2) {
									glTranslated(-0.05, -0.05, 0);
									drawBox(0.1, 0.1, 0.15);
									glTranslated(0.05, 0.05, 0);
								}
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									if (VAL(DETAILS)>4)
										drawSphere(0.05);
									glRotated(VAL(RING_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									if (VAL(DETAILS) > 3) {
										drawCylinder(0.1, 0.05, 0.04);
									}
									else if (VAL(DETAILS) > 2) {
										glTranslated(-0.04, -0.04, 0);
										drawBox(0.08, 0.08, 0.1);
										glTranslated(0.04, 0.04, 0);
									}
									glTranslated(0, 0, 0.1);
									if (VAL(DETAILS)>4)
										drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// pinky
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.52, 0.04);
							if (VAL(DETAILS)>4)
								drawSphere(0.04);
							glRotated(VAL(PINKY_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.02, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							if (VAL(DETAILS) > 3) {
								drawCylinder(0.1, 0.04, 0.04);
							}
							else if (VAL(DETAILS) > 2) { 
								glTranslated(-0.04, -0.04, 0);
								drawBox(0.08, 0.08, 0.1);
								glTranslated(0.04, 0.04, 0);
							}
							else {
								glTranslated(-0.04, -0.04, 0);
								drawBox(0.08, 0.08, 0.33);
								glTranslated(0.04, 0.04, 0);
							}
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.115);
								if (VAL(DETAILS)>4)
									drawSphere(0.04);
								glRotated(VAL(PINKY_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.015);
								if (VAL(DETAILS) > 3) {
									drawCylinder(0.1, 0.04, 0.03);
								}
								else if (VAL(DETAILS) > 2) {
									glTranslated(-0.03, -0.03, 0);
									drawBox(0.06, 0.06, 0.1);
									glTranslated(0.03, 0.03, 0);
								}
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.115);
									if (VAL(DETAILS)>4)
										drawSphere(0.03);
									glRotated(VAL(PINKY_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.015);
									if (VAL(DETAILS) > 3) {
										drawCylinder(0.1, 0.03, 0.02);
									}
									else if (VAL(DETAILS) > 2) {
										glTranslated(-0.02, -0.02, 0);
										drawBox(0.04, 0.04, 0.1);
										glTranslated(0.02, 0.02, 0);
									}
									glTranslated(0, 0, 0.1);
									if (VAL(DETAILS)>4)
										drawSphere(0.02);
									glPopMatrix();// pinky distal
								glPopMatrix(); // pinky middle
							glPopMatrix(); // pinky proximal
						}
						glPopMatrix(); // hand
					glPopMatrix(); // left lower arm
				glPopMatrix(); // left upper arm
			glPopMatrix(); // left shoulder

			// draw right limb
			// draw right shoulders (movable & shoulder plates)
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_ORANGE);
			glTranslated(-1, 3.25, -0.375);
			//rotations
			glTranslated(0, 0.5, 0);
			glRotated(VAL(RIGHT_SHOULDER_Z_ROTATE), 0.0, 0.0, -1.0);
			glTranslated(0, -0.5, 0);

			glTranslated(0, 0, 0.5);
			glRotated(VAL(RIGHT_SHOULDER_Y_ROTATE), 0.0, -1.0, 0.0);
			glTranslated(0, 0, -0.5);

			glTranslated(0, 0.5, 0.5);
			glRotated(VAL(RIGHT_SHOULDER_X_ROTATE), -1.0, 0.0, 0.0);
			glTranslated(0, -0.5, -0.5);

			glScaled(-1, 0.5, 0.75); // x' = -x
			drawBox(1, 1, 1);

			// draw shoulder plates
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0.5, 1.25, 0);
			glScaled(1, 0.5, 1); // -1, .25, .75
			drawBox(1, 1, 1);
			glTranslated(0.75, 0, 0);
			glScaled(0.25, -4, 1); // -.25, -1, .75
			drawBox(1, 1, 1);

			// reset transformation to start of shoulder
			glScaled(4, -0.25, 1);
			glTranslated(-0.75, 0, 0);
			glScaled(1, 2, 1);
			glTranslated(-0.5, -1.25, 0);
			glScaled(1, 2, 1 / 0.75);

				// draw right upper arm
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_OLIVE);
				glTranslated(0.5, 0, 0.125);

				glTranslated(0.25, 0, 0.25);
				glRotated(VAL(RIGHT_UPPER_ARM_Y_ROTATE), 0.0, -1.0, 0.0);
				glTranslated(-0.25, 0, -0.25);

				drawBox(.5, -1.5, .5);
				glScaled(-1, 1, 1);
				glTranslated(-0.25, -1.5, 0);

				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_GRAY);
				glTranslated(0, 0, 0.25);
				if (VAL(DETAILS) > 1)
					drawSphere(.25);
				glRotated(VAL(GUN_X_ROTATE), 1.0, 0, 0);
				glRotated(VAL(GUN_Y_ROTATE), 0, 1.0, 0);
				glRotated(VAL(GUN_Z_ROTATE), 0, 0, 1.0);
				glTranslated(0, 0, -0.25);

				glTranslated(0, -0.5, 0);
					// draw gun
					// cylinders
					glPushMatrix();
					drawCylinder(.5, 0.25, 0.25);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					glTranslated(0, -0.25, 0.3);
					drawCylinder(.5, .15, .15);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_METAL);
					glTranslated(0, 0, 0.5);
					drawCylinder(.9, .1, .1);
					glTranslated(0, 0, .9);
					
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					if (VAL(DETAILS) > 3) {
						drawCylinder(.1, .1, .15);
					}
					else {
						drawCylinder(.1, .15, .15);
					}
					glTranslated(0, 0, .1);
					drawCylinder(.6, .15, .15);
					glTranslated(0, 0, .6);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_METAL);
					drawCylinder(.2, .15, .15);
					glTranslated(0, 0, .2);
					if (VAL(DETAILS) > 3) {
						drawCylinder(.1, .15, .125);
					}
					else {
						drawCylinder(.1, .15, .15);
					}
					glTranslated(0, 0, .1);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					drawCylinder(0.3, .1, .1);
					glTranslated(0, 0, .3);
					if (VAL(DETAILS) > 3) {
						drawCylinder(.05, .1, .125);
					}
					else {
						drawCylinder(.05, .125, .125);
					}
					glTranslated(0, 0, .05);
					drawCylinder(.3, .125, .125);
					glTranslated(0, 0.25, -3.1);


					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_OLIVE);
					if (VAL(DETAILS) > 4) {
						// left (olive) outside
						drawTriangle(-0.3, 0.05, 0, -0.3, -0.25, 0, -0.3, -0.25, 0.25);
						drawTriangle(-0.3, 0.05, 0.5, -0.3, 0.05, 0, -0.3, -0.25, 0.25);
						drawTriangle(-0.3, 0.05, 0.5, -0.3, -0.25, 0.25, -0.3, -0.25, 0.65);
						drawTriangle(-0.3, -0.25, 0.65, -0.3, -0.25, 0.25, -0.3, -0.55, 0.65);
						drawTriangle(-0.3, -0.25, 0.65, -0.3, -0.55, 0.65, -0.3, -0.25, 0.9);
						drawTriangle(-0.3, -0.25, 0.9, -0.3, -0.55, 0.65, -0.3, -0.45, 1.15);
						drawTriangle(-0.3, -0.45, 1.15, -0.3, -0.55, 0.65, -0.3, -0.55, 1.15);
						// inside
						drawTriangle(-0.25, 0.05, 0, -0.25, -0.25, 0.25, -0.25, -0.25, 0);
						drawTriangle(-0.25, 0.05, 0.5, -0.25, -0.25, 0.25, -0.25, 0.05, 0);
						drawTriangle(-0.25, 0.05, 0.5, -0.25, -0.25, 0.65, -0.25, -0.25, 0.25);
						drawTriangle(-0.25, -0.25, 0.65, -0.25, -0.55, 0.65, -0.25, -0.25, 0.25);
						drawTriangle(-0.25, -0.25, 0.65, -0.25, -0.25, 0.9, -0.25, -0.55, 0.65);
						drawTriangle(-0.25, -0.25, 0.9, -0.25, -0.45, 1.15, -0.25, -0.55, 0.65);
						drawTriangle(-0.25, -0.45, 1.15, -0.25, -0.55, 1.15, -0.25, -0.55, 0.65);
						// sides
						drawTriangle(-0.3, 0.05, 0, -0.3, 0.05, 0.5, -0.25, 0.05, 0);
						drawTriangle(-0.25, 0.05, 0, -0.3, 0.05, 0.5, -0.25, 0.05, 0.5);
						drawTriangle(-0.25, 0.05, 0.5, -0.3, 0.05, 0.5, -0.3, -0.25, 0.65);
						drawTriangle(-0.25, 0.05, 0.5, -0.3, -0.25, 0.65, -0.25, -0.25, 0.65);
						drawTriangle(-0.25, -0.25, 0.65, -0.3, -0.25, 0.65, -0.3, -0.25, 0.9);
						drawTriangle(-0.25, -0.25, 0.65, -0.3, -0.25, 0.9, -0.25, -0.25, 0.9);
						drawTriangle(-0.25, -0.25, 0.9, -0.3, -0.25, 0.9, -0.3, -0.45, 1.15);
						drawTriangle(-0.25, -0.25, 0.9, -0.3, -0.45, 1.15, -0.25, -0.45, 1.15);
						drawTriangle(-0.25, -0.45, 1.15, -0.3, -0.45, 1.15, -0.3, -0.55, 1.15);
						drawTriangle(-0.25, -0.45, 1.15, -0.3, -0.55, 1.15, -0.25, -0.55, 1.15);
						drawTriangle(-0.25, -0.55, 1.15, -0.3, -0.55, 1.15, -0.3, -0.55, 0.65);
						drawTriangle(-0.25, -0.55, 1.15, -0.3, -0.55, 0.65, -0.25, -0.55, 0.65);
						drawTriangle(-0.25, -0.55, 0.65, -0.3, -0.55, 0.65, -0.3, -0.25, 0.25);
						drawTriangle(-0.25, -0.55, 0.65, -0.3, -0.25, 0.25, -0.25, -0.25, 0.25);
						drawTriangle(-0.25, -0.25, 0.25, -0.3, -0.25, 0.25, -0.3, -0.25, 0);
						drawTriangle(-0.25, -0.25, 0.25, -0.3, -0.25, 0, -0.25, -0.25, 0);
						drawTriangle(-0.25, -0.25, 0, -0.3, -0.25, 0, -0.3, 0.05, 0);
						drawTriangle(-0.25, -0.25, 0, -0.3, 0.05, 0, -0.25, 0.05, 0);

						// right (olive) outside
						drawTriangle(0.3, 0.05, 0, 0.3, -0.25, 0.25, 0.3, -0.25, 0);
						drawTriangle(0.3, 0.05, 0.5, 0.3, -0.25, 0.25, 0.3, 0.05, 0);
						drawTriangle(0.3, 0.05, 0.5, 0.3, -0.25, 0.65, 0.3, -0.25, 0.25);
						drawTriangle(0.3, -0.25, 0.65, 0.3, -0.55, 0.65, 0.3, -0.25, 0.25);
						drawTriangle(0.3, -0.25, 0.65, 0.3, -0.25, 0.9, 0.3, -0.55, 0.65);
						drawTriangle(0.3, -0.25, 0.9, 0.3, -0.45, 1.15, 0.3, -0.55, 0.65);
						drawTriangle(0.3, -0.45, 1.15, 0.3, -0.55, 1.15, 0.3, -0.55, 0.65);
						// inside
						drawTriangle(0.25, 0.05, 0, 0.25, -0.25, 0, 0.25, -0.25, 0.25);
						drawTriangle(0.25, 0.05, 0.5, 0.25, 0.05, 0, 0.25, -0.25, 0.25);
						drawTriangle(0.25, 0.05, 0.5, 0.25, -0.25, 0.25, 0.25, -0.25, 0.65);
						drawTriangle(0.25, -0.25, 0.65, 0.25, -0.25, 0.25, 0.25, -0.55, 0.65);
						drawTriangle(0.25, -0.25, 0.65, 0.25, -0.55, 0.65, 0.25, -0.25, 0.9);
						drawTriangle(0.25, -0.25, 0.9, 0.25, -0.55, 0.65, 0.25, -0.45, 1.15);
						drawTriangle(0.25, -0.45, 1.15, 0.25, -0.55, 0.65, 0.25, -0.55, 1.15);
						// sides
						drawTriangle(0.3, 0.05, 0, 0.25, 0.05, 0, 0.3, 0.05, 0.5);
						drawTriangle(0.25, 0.05, 0, 0.25, 0.05, 0.5, 0.3, 0.05, 0.5);
						drawTriangle(0.25, 0.05, 0.5, 0.3, -0.25, 0.65, 0.3, 0.05, 0.5);
						drawTriangle(0.25, 0.05, 0.5, 0.25, -0.25, 0.65, 0.3, -0.25, 0.65);
						drawTriangle(0.25, -0.25, 0.65, 0.3, -0.25, 0.9, 0.3, -0.25, 0.65);
						drawTriangle(0.25, -0.25, 0.65, 0.25, -0.25, 0.9, 0.3, -0.25, 0.9);
						drawTriangle(0.25, -0.25, 0.9, 0.3, -0.45, 1.15, 0.3, -0.25, 0.9);
						drawTriangle(0.25, -0.25, 0.9, 0.25, -0.45, 1.15, 0.3, -0.45, 1.15);
						drawTriangle(0.25, -0.45, 1.15, 0.3, -0.55, 1.15, 0.3, -0.45, 1.15);
						drawTriangle(0.25, -0.45, 1.15, 0.25, -0.55, 1.15, 0.3, -0.55, 1.15);
						drawTriangle(0.25, -0.55, 1.15, 0.3, -0.55, 0.65, 0.3, -0.55, 1.15);
						drawTriangle(0.25, -0.55, 1.15, 0.25, -0.55, 0.65, 0.3, -0.55, 0.65);
						drawTriangle(0.25, -0.55, 0.65, 0.3, -0.25, 0.25, 0.3, -0.55, 0.65);
						drawTriangle(0.25, -0.55, 0.65, 0.25, -0.25, 0.25, 0.3, -0.25, 0.25);
						drawTriangle(0.25, -0.25, 0.25, 0.3, -0.25, 0, 0.3, -0.25, 0.25);
						drawTriangle(0.25, -0.25, 0.25, 0.25, -0.25, 0, 0.3, -0.25, 0);
						drawTriangle(0.25, -0.25, 0, 0.3, 0.05, 0, 0.3, -0.25, 0);
						drawTriangle(0.25, -0.25, 0, 0.25, 0.05, 0, 0.3, 0.05, 0);
					}
					else {
						glRotated(25, 1.0, 0, 0);
						glTranslated(-0.3, -0.25, 0);
						drawBox(0.05, 0.3, 1.15);
						glTranslated(0.3, 0.25, 0);
						glTranslated(0.25, -0.25, 0);
						drawBox(0.05, 0.3, 1.15);
						glTranslated(-0.25, 0.25, 0);
						glRotated(-25, 1.0, 0, 0);
					}

					
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					if (VAL(DETAILS) > 3) {
						// left black bar
						drawTriangle(-0.2, -0.6, 0.65, -0.25, -0.65, 0.75, -0.25, -0.45, 0.75);
						drawTriangle(-0.2, -0.6, 0.65, -0.25, -0.45, 0.75, -0.2, -0.45, 0.65);
						drawTriangle(-0.2, -0.45, 0.65, -0.25, -0.45, 0.75, -0.2, -0.4, 0.75);
						drawTriangle(-0.2, -0.4, 0.75, -0.25, -0.45, 0.75, -0.2, -0.4, 2);
						drawTriangle(-0.25, -0.45, 0.75, -0.25, -0.45, 2, -0.2, -0.4, 2);
						drawTriangle(-0.25, -0.45, 0.75, -0.25, -0.65, 2, -0.25, -0.45, 2);
						drawTriangle(-0.25, -0.45, 0.75, -0.25, -0.65, 0.75, -0.25, -0.65, 2);
						drawTriangle(-0.25, -0.65, 2, -0.2, -0.4, 2, -0.25, -0.45, 2);
						drawTriangle(-0.25, -0.65, 2, -0.2, -0.65, 2, -0.2, -0.4, 2);
						drawTriangle(-0.25, -0.65, 2, -0.2, -0.65, 0.75, -0.2, -0.65, 2);
						drawTriangle(-0.25, -0.65, 2, -0.25, -0.65, 0.75, -0.2, -0.65, 0.75);
						drawTriangle(-0.2, -0.65, 0.75, -0.25, -0.65, 0.75, -0.2, -0.6, 0.65);
						drawTriangle(-0.2, -0.4, 0.75, -0.2, -0.4, 2, -0.2, -0.65, 2);
						drawTriangle(-0.2, -0.4, 0.75, -0.2, -0.65, 2, -0.2, -0.65, 0.75);
						drawTriangle(-0.2, -0.4, 0.75, -0.2, -0.65, 0.75, -0.2, -0.6, 0.65);
						drawTriangle(-0.2, -0.4, 0.75, -0.2, -0.6, 0.65, -0.2, -0.45, 0.65);

						// right black bar
						drawTriangle(0.2, -0.6, 0.65, 0.25, -0.45, 0.75, 0.25, -0.65, 0.75);
						drawTriangle(0.2, -0.6, 0.65, 0.2, -0.45, 0.65, 0.25, -0.45, 0.75);
						drawTriangle(0.2, -0.45, 0.65, 0.2, -0.4, 0.75, 0.25, -0.45, 0.75);
						drawTriangle(0.2, -0.4, 0.75, 0.2, -0.4, 2, 0.25, -0.45, 0.75);
						drawTriangle(0.25, -0.45, 0.75, 0.2, -0.4, 2, 0.25, -0.45, 2);
						drawTriangle(0.25, -0.45, 0.75, 0.25, -0.45, 2, 0.25, -0.65, 2);
						drawTriangle(0.25, -0.45, 0.75, 0.25, -0.65, 2, 0.25, -0.65, 0.75);
						drawTriangle(0.25, -0.65, 2, 0.25, -0.45, 2, 0.2, -0.4, 2);
						drawTriangle(0.25, -0.65, 2, 0.2, -0.4, 2, 0.2, -0.65, 2);
						drawTriangle(0.25, -0.65, 2, 0.2, -0.65, 2, 0.2, -0.65, 0.75);
						drawTriangle(0.25, -0.65, 2, 0.2, -0.65, 0.75, 0.25, -0.65, 0.75);
						drawTriangle(0.2, -0.65, 0.75, 0.2, -0.6, 0.65, 0.25, -0.65, 0.75);
						drawTriangle(0.2, -0.4, 0.75, 0.2, -0.65, 2, 0.2, -0.4, 2);
						drawTriangle(0.2, -0.4, 0.75, 0.2, -0.65, 0.75, 0.2, -0.65, 2);
						drawTriangle(0.2, -0.4, 0.75, 0.2, -0.6, 0.65, 0.2, -0.65, 0.75);
						drawTriangle(0.2, -0.4, 0.75, 0.2, -0.45, 0.65, 0.2, -0.6, 0.65);
					}
					else{
						// left black
						glTranslated(-0.25, -0.65, 0.65);
						drawBox(0.05, 0.25, 1.35);
						glTranslated(0.45, 0, 0);
						// right black
						drawBox(0.05, 0.25, 1.35);
						glTranslated(-0.2, 0.65, -0.65);
					}
					if (VAL(DETAILS) > 2) {
						// back black box
						drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.85, 0.7, -0.2, -0.675, 0.85);
						drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.675, 0.85, -0.2, -0.4, 0.85);
						drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.4, 0.85, -0.2, -0.45, 0.475);
						drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.45, 0.475, -0.2, -0.65, 0.35);

						drawTriangle(-0.2, -0.85, 0.6, 0.2, -0.85, 0.6, 0.2, -0.85, 0.7);
						drawTriangle(-0.2, -0.85, 0.6, 0.2, -0.85, 0.7, -0.2, -0.85, 0.7);
						drawTriangle(-0.2, -0.85, 0.7, 0.2, -0.85, 0.7, 0.2, -0.675, 0.85);
						drawTriangle(-0.2, -0.85, 0.7, 0.2, -0.675, 0.85, -0.2, -0.675, 0.85);
						drawTriangle(-0.2, -0.675, 0.85, 0.2, -0.675, 0.85, 0.2, -0.4, 0.85);
						drawTriangle(-0.2, -0.675, 0.85, 0.2, -0.4, 0.85, -0.2, -0.4, 0.85);
						drawTriangle(-0.2, -0.4, 0.85, 0.2, -0.4, 0.85, 0.2, -0.45, 0.475);
						drawTriangle(-0.2, -0.4, 0.85, 0.2, -0.45, 0.475, -0.2, -0.45, 0.475);
						drawTriangle(-0.2, -0.45, 0.475, 0.2, -0.45, 0.475, 0.2, -0.65, 0.35);
						drawTriangle(-0.2, -0.45, 0.475, 0.2, -0.65, 0.35, -0.2, -0.65, 0.35);
						drawTriangle(-0.2, -0.65, 0.35, 0.2, -0.65, 0.35, 0.2, -0.85, 0.6);
						drawTriangle(-0.2, -0.65, 0.35, 0.2, -0.85, 0.6, -0.2, -0.85, 0.6);

						drawTriangle(0.2, -0.85, 0.6, 0.2, -0.675, 0.85, 0.2, -0.85, 0.7);
						drawTriangle(0.2, -0.85, 0.6, 0.2, -0.4, 0.85, 0.2, -0.675, 0.85);
						drawTriangle(0.2, -0.85, 0.6, 0.2, -0.45, 0.475, 0.2, -0.4, 0.85);
						drawTriangle(0.2, -0.85, 0.6, 0.2, -0.65, 0.35, 0.2, -0.45, 0.475);
					}
					else {
						// back black
						glTranslated(-0.2, -0.85, 0.6);
						glRotated(-30, 1.0, 0, 0);
						drawBox(0.4, 0.325, 0.45);
						glRotated(30, 1.0, 0, 0);
						glTranslated(0.2, 0.85, -0.6);
					}
						// black clip
						glTranslated(-0.15, -0.8, 1.15);
						drawBox(0.3, 0.3, 0.5);
						glTranslated(0.15, 0.8, -1.15);
					
					// black front
					/*double z = 2.3;
					drawTriangle(-0.3, -0.1, z, -0.2, -0.1, z, -0.2, 0.15, z);
					drawTriangle(-0.2, 0.15, z, -0.2, -0.1, z, 0.2, -0.1, z);
					drawTriangle(-0.2, 0.15, z, 0.2, -0.1, z, 0.2, 0.1, z);
					drawTriangle(-0.2, 0.15, z, 0.2, 0.1, z, 0.15, 0.15, z);
					drawTriangle(0.15, 0.15, z, 0.2, 0.1, z, 0.25, 0.15, z);
					drawTriangle(0.15, 0.15, z, 0.25, 0.15, z, 0.265, 0.19, z);
					drawTriangle(0.15, 0.15, z, 0.265, 0.19, z, 0.225, 0.22, z);
					drawTriangle(0.15, 0.15, z, 0.225, 0.22, z, 0.185, 0.2, z);*/

					glTranslated(-0.25, -0.8, 2.1);
					drawBox(0.5, 1, 0.2);
					glTranslated(0.25, 0.8, -2.1);
					

					// beige clip holder
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					if (VAL(DETAILS) > 3) {
						drawTriangle(-0.2, -0.25, 1.3, -0.2, -0.1, 1.3, -0.2, -0.1, 1.15);
						drawTriangle(-0.2, -0.25, 1.3, -0.2, -0.1, 1.15, -0.2, -0.4, 1.15);
						drawTriangle(-0.2, -0.25, 1.3, -0.2, -0.4, 1.15, -0.2, -0.4, 1.5);
						drawTriangle(-0.2, -0.4, 1.5, -0.2, -0.4, 1.15, -0.2, -0.5, 1.3);
						drawTriangle(-0.2, -0.4, 1.5, -0.2, -0.5, 1.3, -0.2, -0.8, 1.5);
						drawTriangle(-0.2, -0.8, 1.5, -0.2, -0.5, 1.3, -0.2, -0.8, 1.3);
						drawTriangle(-0.2, -0.8, 1.5, -0.2, -0.8, 1.3, -0.2, -0.85, 1.35);
						drawTriangle(-0.2, -0.8, 1.5, -0.2, -0.85, 1.35, -0.2, -0.85, 1.65);
						drawTriangle(-0.2, -0.8, 1.5, -0.2, -0.85, 1.65, -0.2, -0.8, 1.7);

						drawTriangle(-0.2, -0.1, 1.3, -0.15, -0.1, 1.3, -0.15, -0.1, 1.15);
						drawTriangle(-0.2, -0.1, 1.3, -0.15, -0.1, 1.15, -0.2, -0.1, 1.15);
						drawTriangle(-0.2, -0.1, 1.15, -0.15, -0.1, 1.15, -0.15, -0.4, 1.15);
						drawTriangle(-0.2, -0.1, 1.15, -0.15, -0.4, 1.15, -0.2, -0.4, 1.15);
						drawTriangle(-0.2, -0.4, 1.15, -0.15, -0.4, 1.15, -0.15, -0.5, 1.3);
						drawTriangle(-0.2, -0.4, 1.15, -0.15, -0.5, 1.3, -0.2, -0.5, 1.3);
						drawTriangle(-0.2, -0.5, 1.3, -0.15, -0.5, 1.3, -0.15, -0.8, 1.3);
						drawTriangle(-0.2, -0.5, 1.3, -0.15, -0.8, 1.3, -0.2, -0.8, 1.3);
						drawTriangle(-0.2, -0.8, 1.5, -0.15, -0.8, 1.5, -0.15, -0.4, 1.5);
						drawTriangle(-0.2, -0.8, 1.5, -0.15, -0.4, 1.5, -0.2, -0.4, 1.5);
						drawTriangle(-0.2, -0.4, 1.5, -0.15, -0.4, 1.5, -0.15, -0.25, 1.3);
						drawTriangle(-0.2, -0.4, 1.5, -0.15, -0.25, 1.3, -0.2, -0.25, 1.3);
						drawTriangle(-0.2, -0.25, 1.3, -0.15, -0.25, 1.3, -0.15, -0.1, 1.3);
						drawTriangle(-0.2, -0.25, 1.3, -0.15, -0.1, 1.3, -0.2, -0.1, 1.3);

						drawTriangle(-0.15, -0.25, 1.3, -0.15, -0.1, 1.15, -0.15, -0.1, 1.3);
						drawTriangle(-0.15, -0.25, 1.3, -0.15, -0.4, 1.15, -0.15, -0.1, 1.15);
						drawTriangle(-0.15, -0.25, 1.3, -0.15, -0.4, 1.5, -0.15, -0.4, 1.15);
						drawTriangle(-0.15, -0.4, 1.5, -0.15, -0.5, 1.3, -0.15, -0.4, 1.15);
						drawTriangle(-0.15, -0.4, 1.5, -0.15, -0.8, 1.5, -0.15, -0.5, 1.3);
						drawTriangle(-0.15, -0.8, 1.5, -0.15, -0.8, 1.3, -0.15, -0.5, 1.3);

						drawTriangle(-0.2, -0.8, 1.7, 0.2, -0.8, 1.7, 0.2, -0.8, 1.3);
						drawTriangle(-0.2, -0.8, 1.7, 0.2, -0.8, 1.3, -0.2, -0.8, 1.3);
						drawTriangle(-0.2, -0.8, 1.3, 0.2, -0.8, 1.3, 0.2, -0.85, 1.35);
						drawTriangle(-0.2, -0.8, 1.3, 0.2, -0.85, 1.35, -0.2, -0.85, 1.35);
						drawTriangle(-0.2, -0.85, 1.35, 0.2, -0.85, 1.35, 0.2, -0.85, 1.65);
						drawTriangle(-0.2, -0.85, 1.35, 0.2, -0.85, 1.65, -0.2, -0.85, 1.65);
						drawTriangle(-0.2, -0.85, 1.65, 0.2, -0.85, 1.65, 0.2, -0.8, 1.7);
						drawTriangle(-0.2, -0.85, 1.65, 0.2, -0.8, 1.7, -0.2, -0.8, 1.7);

						drawTriangle(0.2, -0.25, 1.3, 0.2, -0.1, 1.15, 0.2, -0.1, 1.3);
						drawTriangle(0.2, -0.25, 1.3, 0.2, -0.4, 1.15, 0.2, -0.1, 1.15);
						drawTriangle(0.2, -0.25, 1.3, 0.2, -0.4, 1.5, 0.2, -0.4, 1.15);
						drawTriangle(0.2, -0.4, 1.5, 0.2, -0.5, 1.3, 0.2, -0.4, 1.15);
						drawTriangle(0.2, -0.4, 1.5, 0.2, -0.8, 1.5, 0.2, -0.5, 1.3);
						drawTriangle(0.2, -0.8, 1.5, 0.2, -0.8, 1.3, 0.2, -0.5, 1.3);
						drawTriangle(0.2, -0.8, 1.5, 0.2, -0.85, 1.35, 0.2, -0.8, 1.3);
						drawTriangle(0.2, -0.8, 1.5, 0.2, -0.85, 1.65, 0.2, -0.85, 1.35);
						drawTriangle(0.2, -0.8, 1.5, 0.2, -0.8, 1.7, 0.2, -0.85, 1.65);

						drawTriangle(0.2, -0.1, 1.3, 0.15, -0.1, 1.15, 0.15, -0.1, 1.3);
						drawTriangle(0.2, -0.1, 1.3, 0.2, -0.1, 1.15, 0.15, -0.1, 1.15);
						drawTriangle(0.2, -0.1, 1.15, 0.15, -0.4, 1.15, 0.15, -0.1, 1.15);
						drawTriangle(0.2, -0.1, 1.15, 0.2, -0.4, 1.15, 0.15, -0.4, 1.15);
						drawTriangle(0.2, -0.4, 1.15, 0.15, -0.5, 1.3, 0.15, -0.4, 1.15);
						drawTriangle(0.2, -0.4, 1.15, 0.2, -0.5, 1.3, 0.15, -0.5, 1.3);
						drawTriangle(0.2, -0.5, 1.3, 0.15, -0.8, 1.3, 0.15, -0.5, 1.3);
						drawTriangle(0.2, -0.5, 1.3, 0.2, -0.8, 1.3, 0.15, -0.8, 1.3);
						drawTriangle(0.2, -0.8, 1.5, 0.15, -0.4, 1.5, 0.15, -0.8, 1.5);
						drawTriangle(0.2, -0.8, 1.5, 0.2, -0.4, 1.5, 0.15, -0.4, 1.5);
						drawTriangle(0.2, -0.4, 1.5, 0.15, -0.25, 1.3, 0.15, -0.4, 1.5);
						drawTriangle(0.2, -0.4, 1.5, 0.2, -0.25, 1.3, 0.15, -0.25, 1.3);
						drawTriangle(0.2, -0.25, 1.3, 0.15, -0.1, 1.3, 0.15, -0.25, 1.3);
						drawTriangle(0.2, -0.25, 1.3, 0.2, -0.1, 1.3, 0.15, -0.1, 1.3);

						drawTriangle(0.15, -0.25, 1.3, 0.15, -0.1, 1.3, 0.15, -0.1, 1.15);
						drawTriangle(0.15, -0.25, 1.3, 0.15, -0.1, 1.15, 0.15, -0.4, 1.15);
						drawTriangle(0.15, -0.25, 1.3, 0.15, -0.4, 1.15, 0.15, -0.4, 1.5);
						drawTriangle(0.15, -0.4, 1.5, 0.15, -0.4, 1.15, 0.15, -0.5, 1.3);
						drawTriangle(0.15, -0.4, 1.5, 0.15, -0.5, 1.3, 0.15, -0.8, 1.5);
						drawTriangle(0.15, -0.8, 1.5, 0.15, -0.5, 1.3, 0.15, -0.8, 1.3);
					}
					
					
					if (VAL(DETAILS) > 2) {
						// beige top
						drawTriangle(-0.2, 0.25, 0.8, -0.2, 0.25, 0.55, -0.2, -0.25, 0.55);
						drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.25, 0.55, -0.2, -0.25, 0.65);
						drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.25, 0.65, -0.2, -0.1, 0.85);
						drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.1, 0.85, -0.2, 0.15, 0.9);
						drawTriangle(-0.2, 0.15, 0.9, -0.2, -0.1, 0.85, -0.2, -0.1, 2.1);
						drawTriangle(-0.2, 0.15, 0.9, -0.2, -0.1, 2.1, -0.2, 0.15, 2.1);

						drawTriangle(-0.2, 0.25, 0.55, 0.2, 0.25, 0.8, 0.2, 0.25, 0.55);
						drawTriangle(-0.2, 0.25, 0.55, -0.2, 0.25, 0.8, 0.2, 0.25, 0.8);
						drawTriangle(-0.2, 0.25, 0.8, 0.2, 0.15, 0.9, 0.2, 0.25, 0.8);
						drawTriangle(-0.2, 0.25, 0.8, -0.2, 0.15, 0.9, 0.2, 0.15, 0.9);
						drawTriangle(-0.2, 0.15, 0.9, 0.2, 0.15, 2.1, 0.2, 0.15, 0.9);
						drawTriangle(-0.2, 0.15, 0.9, -0.2, 0.15, 2.1, 0.2, 0.15, 2.1);
						drawTriangle(-0.2, 0.15, 2.1, 0.2, -0.1, 2.1, 0.2, 0.15, 2.1);
						drawTriangle(-0.2, 0.15, 2.1, -0.2, -0.1, 2.1, 0.2, -0.1, 2.1);
						drawTriangle(-0.2, -0.1, 2.1, 0.2, -0.1, 0.85, 0.2, -0.1, 2.1);
						drawTriangle(-0.2, -0.1, 2.1, -0.2, -0.1, 0.85, 0.2, -0.1, 0.85);
						drawTriangle(-0.2, -0.1, 0.85, 0.2, -0.25, 0.65, 0.2, -0.1, 0.85);
						drawTriangle(-0.2, -0.1, 0.85, -0.2, -0.25, 0.65, 0.2, -0.25, 0.65);
						drawTriangle(-0.2, -0.25, 0.65, 0.2, -0.25, 0.6, 0.2, -0.25, 0.65);
						drawTriangle(-0.2, -0.25, 0.65, -0.2, -0.25, 0.6, 0.2, -0.25, 0.6);
						drawTriangle(-0.2, -0.25, 0.6, 0.2, 0.25, 0.6, 0.2, -0.25, 0.6);
						drawTriangle(-0.2, -0.25, 0.6, -0.2, 0.25, 0.6, 0.2, 0.25, 0.6);

						drawTriangle(0.2, 0.25, 0.8, 0.2, -0.25, 0.55, 0.2, 0.25, 0.55);
						drawTriangle(0.2, 0.25, 0.8, 0.2, -0.25, 0.65, 0.2, -0.25, 0.55);
						drawTriangle(0.2, 0.25, 0.8, 0.2, -0.1, 0.85, 0.2, -0.25, 0.65);
						drawTriangle(0.2, 0.25, 0.8, 0.2, 0.15, 0.9, 0.2, -0.1, 0.85);
						drawTriangle(0.2, 0.15, 0.9, 0.2, -0.1, 2.1, 0.2, -0.1, 0.85);
						drawTriangle(0.2, 0.15, 0.9, 0.2, 0.15, 2.1, 0.2, -0.1, 2.1);

						// beige bottom
						drawTriangle(-0.2, -0.45, 1.8, -0.2, -0.525, 1.725, -0.2, -0.625, 1.725);
						drawTriangle(-0.2, -0.45, 1.8, -0.2, -0.625, 1.725, -0.2, -0.7, 1.8);
						drawTriangle(-0.2, -0.45, 1.8, -0.2, -0.7, 1.8,		-0.2, -0.7, 2.1);
						drawTriangle(-0.2, -0.45, 1.8, -0.2, -0.7, 2.1,		-0.2, -0.45, 2.1);

						drawTriangle(-0.2, -0.45, 2.1,		0.2, -0.45, 2.1,	0.2, -0.45, 1.8);
						drawTriangle(-0.2, -0.45, 2.1,		0.2, -0.45, 1.8,	-0.2, -0.45, 1.8);
						drawTriangle(-0.2, -0.45, 1.8,		0.2, -0.45, 1.8,	0.2, -0.525, 1.725);
						drawTriangle(-0.2, -0.45, 1.8,		0.2, -0.525, 1.725, -0.2, -0.525, 1.725);
						drawTriangle(-0.2, -0.525, 1.725,	0.2, -0.525, 1.725, 0.2, -0.625, 1.725);
						drawTriangle(-0.2, -0.525, 1.725,	0.2, -0.625, 1.725, -0.2, -0.625, 1.725);
						drawTriangle(-0.2, -0.625, 1.725,	0.2, -0.625, 1.725, 0.2, -0.7, 1.8);
						drawTriangle(-0.2, -0.625, 1.725,	0.2, -0.7, 1.8,		-0.2, -0.7, 1.8);
						drawTriangle(-0.2, -0.7, 1.8,		0.2, -0.7, 1.8,		0.2, -0.7, 2.1);
						drawTriangle(-0.2, -0.7, 1.8,		0.2, -0.7, 2.1,		-0.2, -0.7, 2.1);
						drawTriangle(-0.2, -0.7, 2.1,		0.2, -0.7, 2.1,		0.2, -0.45, 2.1);
						drawTriangle(-0.2, -0.7, 2.1,		0.2, -0.45, 2.1,	-0.2, -0.45, 2.1);

						drawTriangle(0.2, -0.45, 1.8, 0.2, -0.625, 1.725,	0.2, -0.525, 1.725);
						drawTriangle(0.2, -0.45, 1.8, 0.2, -0.7, 1.8,		0.2, -0.625, 1.725);
						drawTriangle(0.2, -0.45, 1.8, 0.2, -0.7, 2.1,		0.2, -0.7, 1.8);
						drawTriangle(0.2, -0.45, 1.8, 0.2, -0.45, 2.1,		0.2, -0.7, 2.1);
					}
					else {
						// beige top
						glTranslated(-0.2, -0.25, 0.55);
						drawBox(0.4, 0.5, 0.25);
						glTranslated(0, 0.15, 0.25);
						drawBox(0.4, 0.25, 1.3);
						glTranslated(0.2, 0.1, -0.8);
						// beige bottom
						glTranslated(-0.2, -0.7, 1.725);
						drawBox(0.4, 0.25, 0.375);
						glTranslated(0.2, 0.7, -1.725);
					}

					glPopMatrix(); // gun
				glPopMatrix(); // right upper arm
			glPopMatrix(); // right shouler
		glPopMatrix(); // upper body

		
		// draw lower body
		glPushMatrix();
			// draw pelvis
		glRotated(VAL(LOWER_BODY_ROTATE), 0, 1.0, 0);
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_OLIVE);
			glTranslated(-0.45, -0.9, -0.45);
			glScaled(0.9, 0.9, 0.9);
			drawBox(1, 1, 1);
			glPopMatrix();

			//draw left leg
			glPushMatrix();
			//draw joint
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0.0, -0.45, 0.0);
			glRotated(90 + VAL(LEFT_UPPER_LEG_Y_ROTATE), 0.0, 1.0, 0.0);
			if (VAL(DETAILS) > 1) {
				drawCylinder(1.45, 0.25, 0.25);

				glTranslated(0.0, 0.0, 0.65);
				drawCylinder(0.8, 0.4, 0.4);
				glTranslated(0.0, 0.0, -0.65);
			}
				
			glRotated(-90, 0.0, 1.0, 0.0);
				
				//draw left upper leg
				glPushMatrix();	

				glRotated(-VAL(LEFT_UPPER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
				glTranslated(0.65, -1.1, -0.3);

				drawBox(0.8, 1.25, 0.6);

					//draw left upper leg plates
					glPushMatrix();
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					glTranslated(-0.1, 0.0, 0.75);
					drawBox(1, 1.1, 0.25);

					glTranslated(0.0, 1.1, 0.0);
					if (VAL(DETAILS) > 3) {
						drawTriangle(0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.25, 0.0);
						drawTriangle(0.0, 0.0, 0.25, 0.5, 0.0, 0.25, 0.5, 0.25, 0.25);
						drawTriangle(0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.5, 0.25, 0.25);
						drawTriangle(0.0, 0.0, 0.0, 0.5, 0.25, 0.25, 0.5, 0.25, 0.0);
					}

					glTranslated(0.5, 0.0, 0.0);
					drawBox(0.5, 0.5, 0.25);
					glPopMatrix();


				//draw joint
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_GRAY);
				glTranslated(0.0, 0.0, 0.3);
				if (VAL(DETAILS) > 1) {
					glRotated(90, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.3, 0.3);
					glRotated(-90, 0.0, 1.0, 0.0);
				}

					
					//draw left middle leg
					glPushMatrix();
					glRotated(VAL(LEFT_MIDDLE_LEG_X_ROTATE), 1.0, 0.0, 0.0);
					glTranslated(0.0, -1.25, -0.3);
					drawBox(0.8, 1.25, 0.6);

						//draw left middle leg plates
						glPushMatrix();
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_OLIVE);
						glTranslated(-0.1, 0.35, 0.75);
						drawBox(1, 0.9, 0.25);
						glPopMatrix();

					//draw joint
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					glTranslated(0.0, 0.0, 0.3);
					if (VAL(DETAILS) > 1) {
						glRotated(90, 0.0, 1.0, 0.0);
						drawCylinder(0.8, 0.35, 0.35);
						glRotated(-90, 0.0, 1.0, 0.0);
					}



						//draw left lower leg
						glPushMatrix();
						glRotated(-VAL(LEFT_LOWER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
						glTranslated(0.0, -1.25, -0.3);
							//draw left lower leg
							glPushMatrix();
							glTranslated(0.075, 0.0, 0.05);
							drawBox(0.65, 1.25, 0.5);
							glPopMatrix();
							//draw left lower leg plates
							glPushMatrix();
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_OLIVE);
							glTranslated(-0.1, 0.0, 0.75);
							drawBox(1, 0.9, 0.25);
							glPopMatrix();

						//draw joint
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glTranslated(0.0, 0.0, 0.3);
						if (VAL(DETAILS) > 1) {
							glRotated(90, 0.0, 1.0, 0.0);
							drawCylinder(0.8, 0.3, 0.3);
							glRotated(-90, 0.0, 1.0, 0.0);
						}


							//draw left foot
							glPushMatrix();
							glRotated(VAL(LEFT_FOOT_X_ROTATE), 1.0, 0.0, 0.0);
							glTranslated(-0.225, -0.6, -0.75);

							//draw left foot
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_ORANGE);
							drawBox(1.25, 0.3, 1.5);
							if (VAL(DETAILS) > 3) {
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
								drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
								drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, -0.3, 1.25, 0.0, 0.0);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.3, -0.3, 1.25, 0.0, 0.0);
								drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
								drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

								glRotated(180, 0.0, 1.0, 0.0);
								glTranslated(-1.25, 0.0, -1.5);
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
								drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
								drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.0, 0.0, 1.25, 0.0, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.0, 0.0, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
								drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);
							}

							glPopMatrix(); // finish foot

						glPopMatrix(); // finish lower leg

					glPopMatrix(); // finish middle leg

				glPopMatrix(); //finish upper leg

			glPopMatrix();// finish left leg



			//draw right leg
			glPushMatrix();
			//draw joint
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0.0, -0.45, 0.0);
			glRotated(-90 - VAL(RIGHT_UPPER_LEG_Y_ROTATE), 0.0, 1.0, 0.0);
			if (VAL(DETAILS) > 1) {
				drawCylinder(1.45, 0.25, 0.25);

				glTranslated(0.0, 0.0, 0.65);
				drawCylinder(0.8, 0.4, 0.4);
				glTranslated(0.0, 0.0, -0.65);
			}

			glRotated(90, 0.0, 1.0, 0.0);

				//draw right upper leg
				glPushMatrix();

				glRotated(-VAL(RIGHT_UPPER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
				glTranslated(-0.65-0.8, -1.1, -0.3);

				drawBox(0.8, 1.25, 0.6);

				//draw right upper leg plates
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_BEIGE);
				glTranslated(-0.1, 0.0, 0.75);
				drawBox(1, 1.1, 0.25);

				glTranslated(0.0, 1.1, 0.0);
				drawBox(0.5, 0.5, 0.25);

				glTranslated(0.5, 0.0, 0.0);
				if (VAL(DETAILS) > 3) {
					drawTriangle(0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.25, 0.0);
					drawTriangle(0.0, 0.0, 0.25, 0.5, 0.0, 0.25, 0.0, 0.25, 0.25);
					drawTriangle(0.0, 0.25, 0.0, 0.5, 0.0, 0.25, 0.5, 0.0, 0.0);
					drawTriangle(0.0, 0.25, 0.25, 0.5, 0.0, 0.25, 0.0, 0.25, 0.0);
				}
				glPopMatrix();


				//draw joint
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_GRAY);
				glTranslated(0.0, 0.0, 0.3);
				if (VAL(DETAILS) > 1) {
					glRotated(90, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.3, 0.3);
					glRotated(-90, 0.0, 1.0, 0.0);
				}


					//draw right middle leg
					glPushMatrix();
					glRotated(VAL(RIGHT_MIDDLE_LEG_X_ROTATE), 1.0, 0.0, 0.0);
					glTranslated(0.0, -1.25, -0.3);
					drawBox(0.8, 1.25, 0.6);

						//draw right middle leg plates
						glPushMatrix();
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_OLIVE);
						glTranslated(-0.1, 0.35, 0.75);
						drawBox(1, 0.9, 0.25);
						glPopMatrix();

					//draw joint
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					glTranslated(0.0, 0.0, 0.3);
					if (VAL(DETAILS) > 1) {
						glRotated(90, 0.0, 1.0, 0.0);
						drawCylinder(0.8, 0.35, 0.35);
						glRotated(-90, 0.0, 1.0, 0.0);
					}



						//draw right lower leg
						glPushMatrix();
						glRotated(-VAL(RIGHT_LOWER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
						glTranslated(0.0, -1.25, -0.3);
							//draw right lower leg
							glPushMatrix();
							glTranslated(0.075, 0.0, 0.05);
							drawBox(0.65, 1.25, 0.5);
							glPopMatrix();
							//draw right lower leg plates
							glPushMatrix();
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_OLIVE);
							glTranslated(-0.1, 0.0, 0.75);
							drawBox(1, 0.9, 0.25);
							glPopMatrix();

						//draw joint
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glTranslated(0.0, 0.0, 0.3);
						if (VAL(DETAILS) > 1) {
							glRotated(90, 0.0, 1.0, 0.0);
							drawCylinder(0.8, 0.3, 0.3);
							glRotated(-90, 0.0, 1.0, 0.0);
						}


							//draw right foot
							glPushMatrix();
							glRotated(VAL(RIGHT_FOOT_X_ROTATE), 1.0, 0.0, 0.0);
							glTranslated(-0.225, -0.6, -0.75);

							//draw right foot
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_ORANGE);
							drawBox(1.25, 0.3, 1.5);
							if (VAL(DETAILS) > 3) {
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
								drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
								drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, -0.3, 1.25, 0.0, 0.0);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.3, -0.3, 1.25, 0.0, 0.0);
								drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
								drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

								glRotated(180, 0.0, 1.0, 0.0);
								glTranslated(-1.25, 0.0, -1.5);
								drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
								drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
								drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.0, 0.0, 1.25, 0.0, 0.0, 0.0, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.0, 0.0, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
								drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
								drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);
							}

							glPopMatrix(); // finish foot

						glPopMatrix(); // finish lower leg

					glPopMatrix(); // finish middle leg

				glPopMatrix(); //finish upper leg

			glPopMatrix();// finish left leg

		glPopMatrix();
		//finish drawing lower body


	glPopMatrix();
}

void BastionModel::reset()
{
	SET(XPOS, 0);
	SET(YPOS, 0);
	SET(ZPOS, 0);
	SET(XROTATE, 0);
	SET(YROTATE, 0);
	SET(ZROTATE, 0);
	SET(UPPER_BODY_ROTATE, 0);
	SET(LOWER_BODY_ROTATE, 0);
	SET(HEAD_ROTATE, 0);
	SET(HEAD_X_TILT, 0);
	SET(HEAD_Z_TILT, 0);
	SET(LEFT_SHOULDER_X_ROTATE, 0);
	SET(LEFT_SHOULDER_Y_ROTATE, 0);
	SET(LEFT_SHOULDER_Z_ROTATE, 10);
	SET(LEFT_UPPER_ARM_Y_ROTATE, 0);
	SET(LEFT_LOWER_ARM_X_ROTATE, 45);
	SET(LEFT_LOWER_ARM_Y_ROTATE, 0);
	SET(WRIST_X_ROTATE, 0);
	SET(WRIST_Y_ROTATE, 0);
	SET(WRIST_Z_ROTATE, 0);
	SET(THUMB_PROXIMAL_ROTATE, 10);
	SET(THUMB_MIDDLE_ROTATE, 10);
	SET(THUMB_DISTAL_ROTATE, 10);
	SET(INDEX_PROXIMAL_ROTATE, 10);
	SET(INDEX_MIDDLE_ROTATE, 10);
	SET(INDEX_DISTAL_ROTATE, 10);
	SET(MIDDLE_PROXIMAL_ROTATE, 10);
	SET(MIDDLE_MIDDLE_ROTATE, 10);
	SET(MIDDLE_DISTAL_ROTATE, 10);
	SET(RING_PROXIMAL_ROTATE, 10);
	SET(RING_MIDDLE_ROTATE, 10);
	SET(RING_DISTAL_ROTATE, 10);
	SET(PINKY_PROXIMAL_ROTATE, 10);
	SET(PINKY_MIDDLE_ROTATE, 10);
	SET(PINKY_DISTAL_ROTATE, 10);
	SET(RIGHT_SHOULDER_X_ROTATE, 0);
	SET(RIGHT_SHOULDER_Y_ROTATE, 0);
	SET(RIGHT_SHOULDER_Z_ROTATE, 10);
	SET(RIGHT_UPPER_ARM_Y_ROTATE, 0);
	SET(GUN_X_ROTATE, 30);
	SET(GUN_Y_ROTATE, 0);
	SET(GUN_Z_ROTATE, 0);
	SET(LEFT_UPPER_LEG_X_ROTATE, 30);
	SET(LEFT_UPPER_LEG_Y_ROTATE, 15);
	SET(LEFT_MIDDLE_LEG_X_ROTATE, 60);
	SET(LEFT_LOWER_LEG_X_ROTATE, 40);
	SET(LEFT_FOOT_X_ROTATE, 10);
	SET(RIGHT_UPPER_LEG_X_ROTATE, 30);
	SET(RIGHT_UPPER_LEG_Y_ROTATE, 15);
	SET(RIGHT_MIDDLE_LEG_X_ROTATE, 60);
	SET(RIGHT_LOWER_LEG_X_ROTATE, 40);
	SET(RIGHT_FOOT_X_ROTATE, 10);
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", -5, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[XROTATE] = ModelerControl("X Rotate", -180, 180, 1, 0);
	controls[YROTATE] = ModelerControl("Y Rotate", -180, 180, 1, 0);
	controls[ZROTATE] = ModelerControl("Z Rotate", -180, 180, 1, 0);
	controls[UPPER_BODY_ROTATE] = ModelerControl("Upper Body Rotate", -135, 135, 1, 0);
	controls[LOWER_BODY_ROTATE] = ModelerControl("Lower Body Rotate", -135, 135, 1, 0);
	controls[HEAD_ROTATE] = ModelerControl("Head Rotate", -90, 90, 1, 0);
	controls[HEAD_X_TILT] = ModelerControl("Head X Tilt", -45, 45, 1, 0);
	controls[HEAD_Z_TILT] = ModelerControl("Head Z Tilt", -30, 30, 1, 0);
	controls[LEFT_SHOULDER_X_ROTATE] = ModelerControl("Left Shoulder X Rotate", -70, 150, 1, 0);
	controls[LEFT_SHOULDER_Y_ROTATE] = ModelerControl("Left Shoulder Y Rotate", -30, 30, 1, 0);
	controls[LEFT_SHOULDER_Z_ROTATE] = ModelerControl("Left Shoulder Z Rotate", 0, 30, 1, 10);
	controls[LEFT_UPPER_ARM_Y_ROTATE] = ModelerControl("Left Upper Arm Y Rotate", -30, 30, 1, 0);
	controls[LEFT_LOWER_ARM_X_ROTATE] = ModelerControl("Left Lower Arm X Rotate", 0, 150, 1, 45);
	controls[LEFT_LOWER_ARM_Y_ROTATE] = ModelerControl("Left Lower Arm Y Rotate", -30, 30, 1, 0);
	controls[WRIST_X_ROTATE] = ModelerControl("Wrist X Rotate", -30, 30, 1, 0);
	controls[WRIST_Y_ROTATE] = ModelerControl("Wrist Y Rotate", -90, 90, 1, 0);
	controls[WRIST_Z_ROTATE] = ModelerControl("Wrist Z Rotate", -90, 90, 1, 0);
	controls[THUMB_PROXIMAL_ROTATE] = ModelerControl("Thumb Proximal Phalanx Rotate", 0, 80, 1, 10);
	controls[THUMB_MIDDLE_ROTATE] = ModelerControl("Thumb Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[THUMB_DISTAL_ROTATE] = ModelerControl("Thumb Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_PROXIMAL_ROTATE] = ModelerControl("Index Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_MIDDLE_ROTATE] = ModelerControl("Index Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_DISTAL_ROTATE] = ModelerControl("Index Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_PROXIMAL_ROTATE] = ModelerControl("Middle Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_MIDDLE_ROTATE] = ModelerControl("Middle Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_DISTAL_ROTATE] = ModelerControl("Middle Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_PROXIMAL_ROTATE] = ModelerControl("Ring Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_MIDDLE_ROTATE] = ModelerControl("Ring Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_DISTAL_ROTATE] = ModelerControl("Ring Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_PROXIMAL_ROTATE] = ModelerControl("Pinky Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_MIDDLE_ROTATE] = ModelerControl("Pinky Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_DISTAL_ROTATE] = ModelerControl("Pinky Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[RIGHT_SHOULDER_X_ROTATE] = ModelerControl("Right Shoulder X Rotate", -70, 150, 1, 0);
	controls[RIGHT_SHOULDER_Y_ROTATE] = ModelerControl("Right Shoulder Y Rotate", -30, 30, 1, 0);
	controls[RIGHT_SHOULDER_Z_ROTATE] = ModelerControl("Right Shoulder Z Rotate", 0, 30, 1, 10);
	controls[RIGHT_UPPER_ARM_Y_ROTATE] = ModelerControl("Right Upper Arm Y Rotate", -30, 30, 1, 0);
	controls[GUN_X_ROTATE] = ModelerControl("Gun X Rotate", -15, 45, 1, 30);
	controls[GUN_Y_ROTATE] = ModelerControl("Gun Y Rotate", -30, 30, 1, 0);
	controls[GUN_Z_ROTATE] = ModelerControl("Gun Z Rotate", -45, 45, 1, 0);
	controls[LEFT_UPPER_LEG_X_ROTATE] = ModelerControl("Left Upper Leg X Rotate", 0, 90, 1, 30);
	controls[LEFT_UPPER_LEG_Y_ROTATE] = ModelerControl("Left Upper Leg Y Rotate", -20, 20, 1, 15);
	controls[LEFT_MIDDLE_LEG_X_ROTATE] = ModelerControl("Left Middle Leg X Rotate", 0, 90, 1, 60);
	controls[LEFT_LOWER_LEG_X_ROTATE] = ModelerControl("Left Lower Leg X Rotate", 0, 60, 1, 40);
	controls[LEFT_FOOT_X_ROTATE] = ModelerControl("Left Foot X Rotate", -30, 30, 1, 10);
	controls[RIGHT_UPPER_LEG_X_ROTATE] = ModelerControl("Right Upper Leg X Rotate", 0, 90, 1, 30);
	controls[RIGHT_UPPER_LEG_Y_ROTATE] = ModelerControl("Right Upper Leg Y Rotate", -20, 20, 1, 15);
	controls[RIGHT_MIDDLE_LEG_X_ROTATE] = ModelerControl("Right Middle Leg X Rotate", 0, 90, 1, 60);
	controls[RIGHT_LOWER_LEG_X_ROTATE] = ModelerControl("Right Lower Leg X Rotate", 0, 60, 1, 40);
	controls[RIGHT_FOOT_X_ROTATE] = ModelerControl("Right Foot X Rotate", -30, 30, 1, 10);
	controls[DETAILS] = ModelerControl("Level of Details", 1, 5, 1, 5);
	controls[LIGHT_TEST] = ModelerControl("Lighting", -25, 25, 1, -2);
	controls[MOOD] = ModelerControl("Mood", 0, 4, 1, 0);
	controls[ANIMATE] = ModelerControl("Enable animation", 0, 1, 1, 0);

	ModelerApplication::Instance()->Init(&createBastionModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}