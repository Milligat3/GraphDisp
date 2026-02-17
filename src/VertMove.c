// Veticies moving logic

#include "VertMove.h"
#include "Constants.h"

void Velocity_Calc(Graph *graph, int index){
	graph->Verts[index].vel = (Vec2) {0, 0};
	float target_distance = graph->t_g;
	float stifness = graph->stifness;
	Vec2 velocity = (Vec2) {0, 0};
	Vec2 posit = graph->Verts[index].pos;
	float len = 0;
	float REPULSION = graph->repulsion;
	Vec2 neigh_pos = make_vector(0, 0);
	for(int i = 0; i < graph->size; i++){
		// PS will check without && graph->matrix_of_contiguity[index][i] == 1
		// Now even isolated verticies are "connected"
		if(i != index){
			
			neigh_pos = graph->Verts[i].pos;
			len = vec_length(vec_sub(posit, neigh_pos));
			if(len > EPSILON){
				graph->Verts[index].dir = (Vec2) {(posit.x - neigh_pos.x)/len, (posit.y - neigh_pos.y)/len};
			}
			else{
				graph->Verts[index].dir = make_vector(1, 0);
			}
			if(graph->matrix_of_contiguity[index][i] == 0 && len > target_distance){
				continue;
			}
			Vec2 target = {neigh_pos.x + graph->Verts[index].dir.x*target_distance, neigh_pos.y + graph->Verts[index].dir.y*target_distance};
			velocity = make_vector(velocity.x + (target.x - posit.x)*stifness,  velocity.y + (target.y - posit.y)*stifness);
		}
	}
	graph->Verts[index].vel = velocity;
	velocity = make_vector(0, 0);
	for (int i = 0; i < graph->size; i++) {
        if (i != index && vec_length(make_vector(posit.x - graph->Verts[i].pos.x, posit.y - graph->Verts[i].pos.y)) <= CIRCLE_RADIUS*2) {
            len = vec_length(make_vector(posit.x - graph->Verts[i].pos.x, posit.y - graph->Verts[i].pos.y));
            // if (len > EPSILON)
				// graph->Verts[i].dir =  make_vector((posit.x - graph->Verts[i].pos.x)/len, (posit.y - graph->Verts[i].pos.y)/len);
			// else 
				// graph->Verts[i].dir = make_vector(1, 0);
            graph->Verts[i].vel = make_vector(graph->Verts[i].vel.x + (posit.x - graph->Verts[i].pos.x)*REPULSION/2, graph->Verts[i].vel.y + (posit.y - graph->Verts[i].pos.y)*REPULSION/2);
			graph->Verts[index].vel = make_vector(graph->Verts[index].vel.x - (posit.x - graph->Verts[index].pos.x)*REPULSION/2, graph->Verts[index].vel.y - (posit.y - graph->Verts[index].pos.y)*REPULSION/2);

		}
		
	}
	
}

void Vert_Moving(Graph *graph, float delta){
	for(int i = 0; i < graph->size; i++){
		Velocity_Calc(graph, i);
		if(graph->index != i){
			graph->Verts[i].pos = make_vector(graph->Verts[i].pos.x + graph->Verts[i].vel.x*delta, graph->Verts[i].pos.y + graph->Verts[i].vel.y*delta);
		}
	}
}