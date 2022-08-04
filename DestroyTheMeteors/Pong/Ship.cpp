#include "ship.h"

#include <cmath>

#include "pause.h"
#include "game.h"
#include "app.h"
#include "enemy.h"
#include "powerup.h"

using namespace app;
using namespace game;
using namespace pause;
using namespace enemy;
using namespace powerup;

namespace app
{
	namespace ship
	{
		Ship ship;

		Shoot shoot[shootMax];

		//Imagenes y texturas
		static Image shipImage;
		static Image shootImage;
		static Texture2D shootTexture;
		static Texture2D shipTexture;
		static Rectangle sourceRect;
		static Rectangle destRec;

		//Escala las texturas
		static float shipScale;
		static float shootScale;
		static Vector2 shootScalePos;

		//Sonidos 
		static Sound shootSound;
		bool pauseSoundShoot = false;

		static Sound explosionSound;
		bool pauseSoundExplosion = false;

		static int scaleAux = 1600;

		int score;

		void InitShip()
		{
			score = 0;

			explosionSound = LoadSound("../res/explosion.wav");

			shootSound = LoadSound("../res/shoot.wav");
			shootImage = LoadImage("../res/shoot.png");
			shipImage = LoadImage("../res/Nave1.png");

			shipTexture = LoadTextureFromImage(shipImage);
			shootTexture = LoadTextureFromImage(shootImage);
			sourceRect.height = shipTexture.height;
			sourceRect.width = shipTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			ship.rec.x = GetScreenWidth() / 2;
			ship.rec.y = GetScreenHeight() - 30;
			ship.rec.width = 20;
			ship.rec.height = 20;
			ship.speed.x = 300;
			ship.speed.y = 0;
			ship.color = RED;

			for (int i = 0; i < shootMax; i++)
			{
				shoot[i].rec.x = 0;
				shoot[i].rec.y = 0;
				shoot[i].rec.width = 10;
				shoot[i].rec.height = 10;
				shoot[i].speed.x = 0;
				shoot[i].speed.y = 300;
				shoot[i].active = false;
				shoot[i].color = MAROON;
			}

			shipScale = (GetScreenWidth() * 0.10f) / scaleAux;
			shootScale = (GetScreenWidth() * 1.1f) / scaleAux;
			shootScalePos = { (shootScale * shootImage.width) / 2 ,(shootScale * shootImage.height) / 2 };

			destRec.width = shipTexture.width / 2 * shipScale;
			destRec.height = shipTexture.height / 2 * shipScale;
		}

		void UpdateShip()
		{
			if (!gameOver)
			{
				PlayerInput();

				ScreenLimits();

				ShootInitialize();

				ShootLogic();

				PlayerCollisionEnemy();
			}
		}

		void DrawShip()
		{
			//DrawRectangle(ship.rec.x, ship.rec.y, ship.rec.width, ship.rec.height, RED);
			DrawTextureEx(shipTexture, { ship.rec.x - 15, ship.rec.y - 20 }, 0, 1, WHITE);

			for (int i = 0; i < shootMax; i++)
			{
				if (shoot[i].active)
				{
					//DrawRectangleRec(shoot[i].rec, shoot[i].color);
					DrawTextureEx(shootTexture, { shoot[i].rec.x - shootScalePos.x + 5 ,shoot[i].rec.y - shootScalePos.y }, 0, shootScale, WHITE);
				}
			}
		}

		void UnloadShip()
		{
			UnloadTexture(shipTexture);
			UnloadTexture(shootTexture);
			UnloadImage(shootImage);
			UnloadImage(shipImage);
			UnloadSound(shootSound);
		}

		void PlayerInput()
		{
			if (IsKeyDown(KEY_RIGHT))
			{
				ship.rec.x += ship.speed.x * GetFrameTime();
			}
			if (IsKeyDown(KEY_LEFT))
			{
				ship.rec.x -= ship.speed.x * GetFrameTime();
			}
		}

		void ScreenLimits()
		{
			if (ship.rec.x <= 0)
			{
				ship.rec.x = 0;
			}
			if (ship.rec.x + ship.rec.width >= GetScreenWidth())
			{
				ship.rec.x = GetScreenWidth() - ship.rec.width;
			}
		}

		void ShootInitialize()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				if (!pauseSoundShoot)
				{
					PlaySound(shootSound);
				}
				else
				{
					PauseSound(shootSound);
				}

				for (int i = 0; i < shootMax; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].rec.x = ship.rec.x + ship.rec.width / 4;
						shoot[i].rec.y = ship.rec.y + ship.rec.height / 4;
						shoot[i].active = true;
						break;
					}
				}
			}
		}

		void ShootLogic()
		{
			for (int i = 0; i < shootMax; i++)
			{
				if (shoot[i].active)
				{
					if (resizeShootActive)
					{
  						shootScale = (GetScreenWidth() * 2.0f) / scaleAux;
						shootScalePos = { (shootScale * shootImage.width) / 2 ,(shootScale * shootImage.height) / 2 };
					}

					shoot[i].rec.y -= shoot[i].speed.y * GetFrameTime();

					////Collision shoot vs enemy
					for (int j = 0; j < activeEnemies; j++)
					{
						if (enemy::enemy[j].active)
						{
							if (CheckCollisionRecs(shoot[i].rec, enemy::enemy[j].rec))
							{
								if (!pauseSoundExplosion)
								{
									PlaySound(explosionSound);
								}
								else
								{
									PauseSound(explosionSound);
								}

								shoot[i].active = false;
								enemy::enemy[j].rec.x = (float)GetRandomValue(0, GetScreenWidth() - enemy::enemy[i].rec.width);
								enemy::enemy[j].rec.y = (float)GetRandomValue(0, -800);
								enemy::enemiesKill++;
								score += 10;
							}
						}
					}

					if (shoot[i].rec.y + shoot[i].rec.height <= 0)
					{
						shoot[i].active = false;
					}
				}
			}
		}
	}
}