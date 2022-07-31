#pragma once
#include "raylib.h"

namespace app
{
	namespace enemy
	{
		void InitEnemy();
		void UpdateEnemy();
		void DrawEnemy();
		void UnloadEnemy();
		void WavesSpawn();
		void EnemyMovement();
		void PlayerCollisionEnemy();

		struct Enemy
		{
			Rectangle rec;
			Vector2 speed;
			bool active;
			Color color;
		};

		const int maxEnemies = 50;

		enum EnemyWave {First, Second, Third};

		extern Enemy enemy[maxEnemies];
		extern int activeEnemies;
		extern int enemiesKill;

		const int firstWave = 15;
		const int secondWave = 30;
		const int thirdWave = 50;
	}
}