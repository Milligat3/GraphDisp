// Operations with Verticies and shit
#include <stdlib.h>
#include <raylib.h>
#include "ThingsWithGraph.h"
#include "Constants.h"
#include "vectors.h"

int CheckIfMouseOnSidesOfVec(Graph graph, Vec2 MousePos){
	if(vec_length(make_vector(graph.Verts[graph.index].pos.x - MousePos.x, 
							  graph.Verts[graph.index].pos.y - MousePos.y)) < CIRCLE_RADIUS){
		return 1;
	}
	return 0;
}
int CheckWhichToDrag(Graph graph, Vec2 MousePos){
	for(int i = 0; i < graph.size; i++){
		if(vec_length(make_vector(graph.Verts[i].pos.x - MousePos.x, 
								  graph.Verts[i].pos.y - MousePos.y)) < CIRCLE_RADIUS){
			return i;
		}
	}
	return -1;
}
void DragNode(Graph *graph, Vec2 MousePos){
	if(MousePos.x > WIDTH || MousePos.y > HEIGHT || MousePos.x < 0 || MousePos.y < 0)
		return;
	graph->Verts[graph->index].pos = MousePos;
}

void AddNode(Graph *graph, Vec2 MousePos, int menu_is_up){
	// if(graph->size >= 10)
		// return;
	graph->size += 1;
	graph->Verts = realloc(graph->Verts, graph->size*sizeof(Vert));
	if(menu_is_up)
		graph->Verts[graph->size - 1] = (Vert) {.pos = {GetRandomValue(50, WIDTH - 50),GetRandomValue(50, HEIGHT - 50)}, .dir = {0, 0}, .vel = {0, 0}};
	else{
		graph->Verts[graph->size - 1].pos = MousePos;
	}
	graph->matrix_of_contiguity = realloc(graph->matrix_of_contiguity, graph->size * sizeof(int *));
	graph->matrix_of_contiguity[graph->size - 1] = malloc(sizeof(int) * graph->size);
	for(int i = 0; i < graph->size; i++){
		graph->matrix_of_contiguity[i] = realloc(graph->matrix_of_contiguity[i], graph->size * sizeof(int));
		graph->matrix_of_contiguity[i][graph->size - 1] = 0;
	}
	for(int i = 0; i < graph->size; i++){
		graph->matrix_of_contiguity[graph->size - 1][i] = 0;
	}
	if(graph->grab == 1){
		graph->matrix_of_contiguity[graph->index][graph->size - 1] = 1;
		graph->matrix_of_contiguity[graph->size - 1][graph->index] = graph->matrix_of_contiguity[graph->index][graph->size - 1];
		
		graph->Verts[graph->size - 1].pos = (Vec2) {GetRandomValue(graph->Verts[graph->index].pos.x - 40, graph->Verts[graph->index].pos.x + 40), 
													   GetRandomValue(graph->Verts[graph->index].pos.y - 40, graph->Verts[graph->index].pos.y + 40)};
		
	}
}

void DeleteNode(Graph *graph, int menu_is_up){
	if(graph->size <= 2)
		return;
	graph->grab = 0;
	if(graph->index != -1 && graph->index < graph->size - 1){
		for(int i = 0; i < graph->size - 1; i++){
			
			for(int j = graph->index; j < graph->size - 1; j++)
				
				graph->matrix_of_contiguity[i][j] = graph->matrix_of_contiguity[i][j + 1];
			if(graph->index + i < graph->size - 1){
				graph->Verts[graph->index + i] = graph->Verts[graph->index + i + 1];
				graph->matrix_of_contiguity[graph->index + i] = graph->matrix_of_contiguity[graph->index + i + 1];
			}
		}
		graph->index = -1;
	}
	graph->size -= 1;
	graph->Verts = realloc(graph->Verts, graph->size*sizeof(Vert));
	graph->matrix_of_contiguity = realloc(graph->matrix_of_contiguity, graph->size * sizeof(int *));
	for(int i = 0; i < graph->size; i++){
		graph->matrix_of_contiguity[i] = realloc(graph->matrix_of_contiguity[i], graph->size * sizeof(int));
	}
}

void Init_Graph(Graph *graph){
	graph->size = rand() % 6 + 2;
	graph->grab = 0;
	graph->index = -1;
	graph->Verts = malloc(graph->size * sizeof(Vert));
	graph->matrix_of_contiguity = malloc(graph->size * sizeof(int *));
	graph->stifness = 20;
	graph->t_g = 100;
	graph->repulsion = 0.5;
	for(int i = 0; i < graph->size; i++){
		graph->matrix_of_contiguity[i] = calloc(graph->size, sizeof(int));
		graph->Verts[i] = (Vert) {.pos = {GetRandomValue(50, WIDTH - 50),GetRandomValue(50, HEIGHT - 50)}, .dir = {0, 0}, .vel = {0, 0}};
		for(int j = i; j < graph->size; j++){
			int random_num = GetRandomValue(0, 1);
			if(i == j){
				graph->matrix_of_contiguity[i][j] = random_num;
				
			}
			if(i != j){
				graph->matrix_of_contiguity[i][j] = random_num;
			}
		}
	}
	for(int i = 0; i < graph->size; i++){
		for(int j = i; j < graph->size; j++){
			if(i == j){
				continue;
			}
			if(i != j){
				graph->matrix_of_contiguity[j][i] = graph->matrix_of_contiguity[i][j];
			}
		}
	}
	
}

Edge Check_If_Mouse_On_Matrix(Graph graph, Vec2 MousePos){
	Edge edge_to_ret = {(MousePos.x + 60)/40 - 3, (MousePos.y + 40)/40 - 2};
	for(int i = 0; i < graph.size; i++){
		for(int j = 0; j < graph.size; j++){
			if((edge_to_ret.x == j && edge_to_ret.y == i) || (edge_to_ret.y == j && edge_to_ret.x == i)){
				
				return (Edge) {i, j};
			}
		}
	}
	return (Edge) {-1, -1};
}

void Check_Vert_Pos(Graph *graph){
	for(int i = 0; i < graph->size; i++){
		if(graph->Verts[i].pos.x < 0)
			graph->Verts[i].pos.x = 0;
		if(graph->Verts[i].pos.x > WIDTH)
			graph->Verts[i].pos.x = WIDTH;
		if(graph->Verts[i].pos.y < 0)
			graph->Verts[i].pos.y = 0;
		if(graph->Verts[i].pos.y > HEIGHT)
			graph->Verts[i].pos.y = HEIGHT;
		
	}
}