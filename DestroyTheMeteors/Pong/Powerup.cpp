#include "powerup.h"

#include <cmath>

#include "ship.h"
#include "game.h"
#include "app.h"

using namespace app;
using namespace game;
using namespace ship;

namespace app
{
	namespace powerup
	{
		static const int amount = 1;
		static Powerups resizeShoot[amount];
		static int powerupSpeed;
		static const float speedBoost = 100.0f;
		static int initialCorrection = 150;

		//Imagenes
		static Image resizeShootImage;
		static Texture2D resizeShootTexture;

		//Escalar la textura
		static float resizeShootScale;
		static Vector2 resizeShootScalePos;

		//Sonidos 
		static Sound powerupSound;
		bool pauseSoundPowerup = false;

		bool resizeShootActive = false;
		bool nuclearActive = false;
		bool alreadySpawnShoot = false;

		float timer = 0;

		static int scaleAux = 1600;

		void InitPowerUps()
		{
			resizeShootImage = LoadImage("../res/shoot.png");
			resizeShootTexture = LoadTextureFromImage(resizeShootImage);

			powerupSound = LoadSound("../res/powerup.wav");

			float posx, posy;
			float velx, vely;

			bool correctRange = false;
			resizeShootActive = false;
			alreadySpawnShoot = false;
			timer = 0.0f;

			powerupSpeed = 1;

			for (int i = 0; i < amount; i++)
			{
				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2 - initialCorrection && posx < GetScreenWidth() / 2 + initialCorrection) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2 - initialCorrection && posy < GetScreenHeight() / 2 + initialCorrection)  posy = GetRandomValue(0, GetScreenHeight());
					else correctRange = true;
				}

				resizeShoot[i].position = { posx, posy };

				correctRange = false;
				velx = GetRandomValue(-powerupSpeed, powerupSpeed);
				vely = GetRandomValue(-powerupSpeed, powerupSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = GetRandomValue(-powerupSpeed, powerupSpeed);
						vely = GetRandomValue(-powerupSpeed, powerupSpeed);
					}
					else correctRange = true;
				}

				resizeShoot[i].speed = { velx, vely };
				resizeShoot[i].radius = (10 * GetScreenWidth()) / scaleAux;
				resizeShoot[i].active = false;
				resizeShoot[i].color = BLUE;
			}

			resizeShootScale = (GetScreenWidth() * 2.0f) / scaleAux;
			resizeShootScalePos = { (resizeShootScale * resizeShootImage.width) / 2 ,(resizeShootScale * resizeShootImage.height) / 2 };
		}

		void UpdatePowerUps()
		{
			timer += GetFrameTime();

			if (!gameOver)
			{
				for (int a = 0; a < amount; a++)
				{
					if (!alreadySpawnShoot)
					{
						if (timer >= 5)
						{
							resizeShoot[a].active = true;
							alreadySpawnShoot = true;
						}
					}

					if (CheckCollisionCircles({ ship::shoot[a].rec.x, ship::shoot[a].rec.y }, 10, resizeShoot[a].position, resizeShoot[a].radius) && resizeShoot[a].active)
					{
						if (!pauseSoundShoot)
						{
							PlaySound(powerupSound);
						}
						else
						{
							PauseSound(powerupSound);
						}

  						resizeShoot[a].active = false;
						resizeShootActive = true;
					}
				}

				for (int i = 0; i < amount; i++)
				{
					if (resizeShoot[i].active)
					{
						resizeShoot[i].position.x += resizeShoot[i].speed.x * GetFrameTime() * speedBoost;
						resizeShoot[i].position.y += resizeShoot[i].speed.y * GetFrameTime() * speedBoost;

						if (resizeShoot[i].position.x > GetScreenWidth() + resizeShoot[i].radius) resizeShoot[i].position.x = -(resizeShoot[i].radius);
						else if (resizeShoot[i].position.x < 0 - resizeShoot[i].radius) resizeShoot[i].position.x = GetScreenWidth() + resizeShoot[i].radius;
						if (resizeShoot[i].position.y > GetScreenHeight() + resizeShoot[i].radius) resizeShoot[i].position.y = -(resizeShoot[i].radius);
						else if (resizeShoot[i].position.y < 0 - resizeShoot[i].radius) resizeShoot[i].position.y = GetScreenHeight() + resizeShoot[i].radius;
					}
				}
			}
		}

		void DrawPowerUps()
		{
			for (int i = 0; i < amount; i++)
			{
				if (resizeShoot[i].active)
				{
					DrawCircleV(resizeShoot[i].position, resizeShoot[i].radius, DARKGRAY);
					DrawTextureEx(resizeShootTexture, { resizeShoot[i].position.x - resizeShootScalePos.x - 0.5f,resizeShoot[i].position.y - resizeShootScalePos.y }, 0, resizeShootScale, WHITE);
				}
				else DrawCircleV(resizeShoot[i].position, resizeShoot[i].radius, BLANK);
			}
		}

		void UnloadPowerUps()
		{
			UnloadTexture(resizeShootTexture);
			UnloadImage(resizeShootImage);
			UnloadSound(powerupSound);
		}
	}
}