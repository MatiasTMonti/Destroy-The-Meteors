#include "Enemy.h"

#include "app.h"
#include "game.h"
#include "ship.h"

using namespace app;
using namespace game;
using namespace ship;

namespace app
{
	namespace enemy
	{
		Enemy enemy[maxEnemies] = { 0 };
		EnemyWave wave;

		int activeEnemies = 0;
		int enemiesKill;

		//Imagenes y texturas
		static Image meteorImage;
		static Texture2D meteorTexture;

		static float smallMeteorScale;
		static Vector2 smallMeteorScalePos;

		static int scaleAux = 1600;

		void InitEnemy()
		{
			wave = First;
			activeEnemies = firstWave;
			enemiesKill = 0;

			meteorImage = LoadImage("../res/asteroide.png");

			meteorTexture = LoadTextureFromImage(meteorImage);

			for (int i = 0; i < maxEnemies; i++)
			{
				enemy[i].rec.width = 15;
				enemy[i].rec.height = 15;
				enemy[i].rec.x = (float)GetRandomValue(0, GetScreenWidth() - enemy[i].rec.width);
				enemy[i].rec.y = (float)GetRandomValue(0, -800);
				enemy[i].speed.x = 0;
				enemy[i].speed.y = 300;
				enemy[i].active = true;
				enemy[i].color = GRAY;
			}

			smallMeteorScale = (GetScreenWidth() * 0.08f) / scaleAux;
			smallMeteorScalePos = { (smallMeteorScale * meteorImage.width) / 2 ,(smallMeteorScale * meteorImage.height) / 2 };
		}

		void UpdateEnemy()
		{
			if (!gameOver)
			{
				WavesSpawn();

				EnemyMovement();
			}
		}

		void DrawEnemy()
		{
			for (int i = 0; i < activeEnemies; i++)
			{
				if (enemy[i].active) //DrawRectangleRec(enemy[i].rec, enemy[i].color);
				DrawTextureEx(meteorTexture, { enemy[i].rec.x - smallMeteorScalePos.x / 2,enemy[i].rec.y - smallMeteorScalePos.y / 2 }, 0, smallMeteorScale, WHITE);
			}

			switch (wave)
			{
			case First:
				DrawText("FIRST WAVE", GetScreenWidth() / 2 - MeasureText("FIRST WAVE", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(RED, 0.1f));
				break;
			case Second:
				DrawText("SECOND WAVE", GetScreenWidth() / 2 - MeasureText("SECOND WAVE", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(RED, 0.1f));
				break;
			case Third:
				DrawText("THIRD WAVE", GetScreenWidth() / 2 - MeasureText("THIRD WAVE", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(RED, 0.1f));
				break;
			}
		}

		void UnloadEnemy()
		{
			UnloadTexture(meteorTexture);
			UnloadImage(meteorImage);
		}

		void WavesSpawn()
		{
			switch (wave)
			{
			case First:
				if (enemiesKill == activeEnemies)
				{
					enemiesKill = 0;

					for (int i = 0; i < activeEnemies; i++)
					{
						if (!enemy[i].active)
						{
							enemy[i].active = true;
						}
					}

					activeEnemies = secondWave;
					wave = Second;
				}
				break;
			case Second:
				if (enemiesKill == activeEnemies)
				{
					enemiesKill = 0;

					for (int i = 0; i < activeEnemies; i++)
					{
						if (!enemy[i].active)
						{
							enemy[i].active = true;
						}
					}

					activeEnemies = thirdWave;
					wave = Third;
				}
				break;
			case Third:
				if (enemiesKill == activeEnemies)
				{
					victory = true;
				}
				break;
			default:
				break;
			}
		}

		void EnemyMovement()
		{
			for (int i = 0; i < activeEnemies; i++)
			{
				if (enemy[i].active)
				{
					enemy[i].rec.y += enemy[i].speed.y * GetFrameTime();

					if (enemy[i].rec.y > GetScreenHeight())
					{
						enemy[i].rec.x = (float)GetRandomValue(0, GetScreenWidth() - enemy[i].rec.width);
						enemy[i].rec.y = (float)GetRandomValue(0, -800);
					}
				}
			}
		}

		void PlayerCollisionEnemy()
		{
			for (int i = 0; i < activeEnemies; i++)
			{
				if (CheckCollisionRecs(ship::ship.rec, enemy[i].rec))
				{
					gameOver = true;
					currentScreen = GameOver;
				}
			}
		}
	}
}