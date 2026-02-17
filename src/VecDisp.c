#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Constants.h"
#include "ThingsWithGraph.h"
#include "DrawFuncs.h"
#include "MouseEvents.h"
#include "VertMove.h"

int main(){
	srand(time(NULL));
	InitWindow(WIDTH, HEIGHT, "Playing with vectors");
	
	SetTargetFPS(60);
	Graph graph_1;
	
	int menu_is_displayed = 0;
	
	Init_Graph(&graph_1);
	Vec2 PosOfMouse = {0, 0};
	clock_t last_time = clock();
	while(!WindowShouldClose()){
		clock_t now = clock();
		float delta = (float) (now - last_time) / CLOCKS_PER_SEC;
		
		last_time = now;
		Vert_Moving(&graph_1, delta);
		
		Check_Vert_Pos(&graph_1);
		if(IsKeyPressed(KEY_F5))
			Init_Graph(&graph_1);
		if(IsKeyPressed(KEY_G)){
			if(!menu_is_displayed){
				menu_is_displayed = 1;
				graph_1.grab = 0;
				graph_1.index = -1;
			}else
			{
				menu_is_displayed = 0;
			}
		}
		
		if(!menu_is_displayed)
			Mouse_Events_Outside_Menu(&graph_1, &PosOfMouse, menu_is_displayed);
		if(menu_is_displayed)
			Mouse_Events_In_Menu(&graph_1, &PosOfMouse, menu_is_displayed);
		BeginDrawing();
			ClearBackground(GRAY);
			DrawGraph(graph_1);
			DrawMenu(menu_is_displayed, &graph_1);
		EndDrawing();
	}
	CloseWindow();
}