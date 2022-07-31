#include "credits.h"

#include <raylib.h>

#include "game.h"
#include "app.h"
#include "menu.h"

using namespace app;
using namespace game;
using namespace menu;

namespace app
{
	namespace credits
	{
		static char text1[] = "Using Raylib library";
		static char text2[] = "Images & assets:";
		static char text3[] = "-Ship and shoot: Yoel Mottillo La Pira";
		static char text4[] = "MENU";
		static char text5[] = "Created by Monti Matias";
		static char text6[] = "-Menu image: 'http://www.freepik.com/vectorpouch'";
		static char text7[] = "'Shoot', Author: Kenney, 'https://www.kenney.nl/assets/sci-fi-sounds'";
		static char text8[] = "-'Blue and White Milky Way', Author: Frank Cone, 'https://www.pexels.com/photo/blue-and-white-milky-way-3214110/'";
		static char text9[] = "'Explosion meteorite', Author: GFX sound, 'https://www.youtube.com/watch?v=gzwq0ue2qJ8&ab_channel=GFXSounds' ";
		static char text10[] = "'Instant Crush', Author: Corbyn Kites, 'https://www.youtube.com/watch?v=hMIKFsFzeU0&ab_channel=CorbynKites'";
		static int sizeText = 0;
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int textPositionX = 0;
		static int textPositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static int text6PositionX = 0;
		static int text6PositionY = 0;
		static int text7PositionX = 0;
		static int text7PositionY = 0;
		static int text8PositionX = 0;
		static int text8PositionY = 0;
		static int text9PositionX = 0;
		static int text9PositionY = 0;
		static int text10PositionX = 0;
		static int text10PositionY = 0;

		static int halfScreen = 0;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;

		static Vector2 mousePoint;
		static Rectangle rect1;
		static Color colorRect1;

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 20) / scaleAux1;
			sizeText2 = (GetScreenWidth() * 15) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 12.f) / scaleAux1;
			halfScreen = GetScreenWidth() / 2;

			textPositionX = halfScreen - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.13;
			text2PositionX = halfScreen - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.21;
			text6PositionX = halfScreen - MeasureText(text6, sizeText) / 2;
			text6PositionY = GetScreenHeight() * 0.29;
			text3PositionX = halfScreen - MeasureText(text3, sizeText) / 2;
			text3PositionY = GetScreenHeight() * 0.37;
			text4PositionX = halfScreen - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() * 0.80;
			text5PositionX = halfScreen - MeasureText(text5, sizeText) / 2;
			text5PositionY = GetScreenHeight() * 0.05;
			text7PositionX = halfScreen - MeasureText(text7, sizeText) / 2;
			text7PositionY = GetScreenHeight() * 0.45;
			text8PositionX = halfScreen - MeasureText(text8, sizeText3) / 2;
			text8PositionY = GetScreenHeight() * 0.53;
			text9PositionX = halfScreen - MeasureText(text9, sizeText3) / 2;
			text9PositionY = GetScreenHeight() * 0.60;
			text10PositionX = halfScreen - MeasureText(text10, sizeText3) / 2;
			text10PositionY = GetScreenHeight() * 0.67;

			colorRect1 = RED;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 170) / scaleAux2;
			rect1.x = halfScreen - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;
		}

		void UpdateCredits()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					InitMenu();
				}
			}
			else colorRect1.a = 255;
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawText(text1, textPositionX, textPositionY, sizeText, BLUE);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, BLUE);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, BLUE);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText, BLUE);
			DrawText(text6, text6PositionX, text6PositionY, sizeText, BLUE);
			DrawText(text7, text7PositionX, text7PositionY, sizeText, BLUE);
			DrawText(text8, text8PositionX, text8PositionY, sizeText3, BLUE);
			DrawText(text9, text9PositionX, text9PositionY, sizeText3, BLUE);
			DrawText(text10, text10PositionX, text10PositionY, sizeText3, BLUE);
		}
	}
}