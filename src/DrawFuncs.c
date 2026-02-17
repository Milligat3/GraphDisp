// Drawing functions
#include "Constants.h"
#include "Graph.h"
#include "vectors.h"
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

float line_thickness = 20;

Vector2 MyVec2RayVec2(Vec2 v)
{
	return (Vector2){v.x, v.y};
}

void DrawGraph(Graph graph){
	for(int i = 0; i < graph.size; i++){
		for(int j = i; j < graph.size; j++){
			if(graph.matrix_of_contiguity[i][j] == 1 && i != j){
				DrawLineEx(MyVec2RayVec2(graph.Verts[i].pos), MyVec2RayVec2(graph.Verts[j].pos), line_thickness, WHITE);
			}
			
		}
		
	}
	char to_disp[256];
	for(int k = 0; k < graph.size; k++){
		DrawCircleV(MyVec2RayVec2(graph.Verts[k].pos), CIRCLE_RADIUS, GREEN);
		sprintf(to_disp, "%d", k + 1);
		DrawText(to_disp, graph.Verts[k].pos.x - CIRCLE_RADIUS/2, graph.Verts[k].pos.y - CIRCLE_RADIUS, 40, WHITE);
	}
	if(graph.index != -1){
		sprintf(to_disp, "%d", graph.index + 1);
		DrawCircleV(MyVec2RayVec2(graph.Verts[graph.index].pos), CIRCLE_RADIUS, RED);		
		DrawText(to_disp, graph.Verts[graph.index].pos.x - CIRCLE_RADIUS/2, graph.Verts[graph.index].pos.y - CIRCLE_RADIUS, 40, WHITE);
	}
	for(int i = 0; i < graph.size; i++)
	{
		DrawLineEx(MyVec2RayVec2(graph.Verts[i].pos), (Vector2){graph.Verts[i].pos.x + graph.Verts[i].vel.x, graph.Verts[i].pos.y + graph.Verts[i].vel.y}, 10, YELLOW);
	}
}

void DrawMenu(int is_displayed, Graph *graph){
	if(is_displayed){
		DrawRectangle(0, 0, WIDTH, HEIGHT, (Color) {130, 130, 130, 125});
		for(int i = 0; i < graph->size; i++){
			char disp[3];
			sprintf(disp, "%d", i + 1);
			DrawText(disp, 20, i*40 + 50, 20, WHITE);
			DrawText(disp, i*40 + 70, 10, 20, WHITE);
			for(int j = i; j < graph->size; j++){
				char to_disp[2];
				sprintf(to_disp, "%d", graph->matrix_of_contiguity[i][j]);
				DrawRectangle(i*40 + 60, j*40 + 40, 40, 40, BLACK);
				DrawRectangle(j*40 + 60, i*40 + 40, 40, 40, BLACK);
				DrawText(to_disp, i*40 + 70, j*40 + 50, 20, WHITE);
				DrawText(to_disp, j*40 + 70, i*40 + 50, 20, WHITE);
			}
		}
		for(int i = 0; i < graph->size; i++){
			DrawLine(i*40 + 60, 40, i*40 + 60, 40 + graph->size * 40, WHITE);
			DrawLine(60, i*40 + 40, 60 + graph->size * 40, i*40 + 40, WHITE);
		}
		DrawRectangle(WIDTH - 80, HEIGHT - 40, 40, 40, BLACK);
		DrawRectangle(WIDTH - 40, HEIGHT - 40, 40, 40, BLACK);
		DrawText("-", WIDTH - 75, HEIGHT - 40, 40, WHITE);
		DrawText("+", WIDTH - 35, HEIGHT - 40, 40, WHITE);
		DrawLine(WIDTH - 40, HEIGHT - 40, WIDTH - 40, HEIGHT, WHITE);
		DrawText("Target Distance", WIDTH - 300, 60, 20, WHITE);
		DrawText("Stifness", WIDTH - 300, 140, 20, WHITE);
		DrawText("Repulsion", WIDTH - 300, 220, 20, WHITE);
		DrawText("Line Thickness", WIDTH - 300, 300, 20, WHITE);
		GuiSliderBar((Rectangle){WIDTH - 300, 80, 200, 40}, "0", "400", &(graph->t_g), 0, 400);
		GuiSliderBar((Rectangle){WIDTH - 300, 160, 200, 40}, "0", "40", &(graph->stifness), 0, 40);
		GuiSliderBar((Rectangle){WIDTH - 300, 240, 200, 40}, "0", "1", &(graph->repulsion), 0, 1);
		GuiSliderBar((Rectangle){WIDTH - 300, 320, 200, 40}, "0", "40", &line_thickness, 0, 40);
	}
}