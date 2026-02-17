//Events logic

#include "raylib.h"
#include "ThingsWithGraph.h"
#include "Constants.h"

void Mouse_Events_Outside_Menu(Graph *graph, Vec2* MousePos, int menu_is_up){
	Vector2 PosMouse = GetMousePosition();
	*MousePos = (Vec2){PosMouse.x, PosMouse.y};
	if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
		if(!graph->grab){
			graph->index = CheckWhichToDrag(*graph, *MousePos);
			graph->grab = CheckIfMouseOnSidesOfVec(*graph, *MousePos);
		}
	}
	if(IsKeyPressed(KEY_E)){
		AddNode(graph, *MousePos, menu_is_up);
	}
	if(IsKeyPressed(KEY_Q)){
		DeleteNode(graph, menu_is_up);
	}
	if(graph->index == -1){
		return;
	}
	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
		graph->index = -1;
		graph->grab = 0;
	}
	if(graph->grab){
		DragNode(graph, *MousePos);
	}
	return;
}

void Mouse_Events_In_Menu(Graph *graph, Vec2* MousePos, int menu_is_up){
	Edge edge_of_m = {-1, -1};
	Vector2 PosMouse = GetMousePosition();
	*MousePos = (Vec2){PosMouse.x, PosMouse.y};
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
		edge_of_m = Check_If_Mouse_On_Matrix(*graph, *MousePos);
		if(MousePos->y > HEIGHT - 40 && MousePos->y < HEIGHT){
		if(MousePos->x > WIDTH - 80 && MousePos->x < WIDTH - 40){
			DeleteNode(graph, menu_is_up);
		}
		if(MousePos->x > WIDTH - 40 && MousePos->x < WIDTH){
			AddNode(graph, (Vec2) {0, 0}, menu_is_up);
		}
	}
	}
	
	if(edge_of_m.x < 0 || edge_of_m.y < 0 ||
	   edge_of_m.x >= graph->size || edge_of_m.y >= graph->size){
		return;
	}
	if(edge_of_m.x >= 0 && edge_of_m.y >= 0){
		graph->matrix_of_contiguity[edge_of_m.x][edge_of_m.y] ^= 1;
		graph->matrix_of_contiguity[edge_of_m.y][edge_of_m.x] = graph->matrix_of_contiguity[edge_of_m.x][edge_of_m.y];
	}
}