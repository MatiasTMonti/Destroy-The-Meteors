#pragma once

#include "raylib.h";

namespace app
{
	namespace ship
	{
		void InitShip();
		void UpdateShip();
		void DrawShip();
		void UnloadShip();
		void PlayerInput();
		void ScreenLimits();
		void ShootInitialize();
		void ShootLogic();

		struct Ship
		{
			Rectangle rec;
			Vector2 speed;
			Color color;
		};

		struct Shoot
		{
			Rectangle rec;
			Vector2 speed;
			bool active;
			Color color;
		};

		const int shootMax = 50;

		extern Ship ship;

		extern Shoot shoot[];

		extern bool pauseSoundShoot;
		extern bool pauseSoundExplosion;
		extern int score;
	}
}