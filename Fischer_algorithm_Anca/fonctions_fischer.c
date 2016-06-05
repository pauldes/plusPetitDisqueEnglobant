#include <stdio.h>
#include <math.h>

#include "hashset.h"
#include "hashset_itr.h"
#include "structures.h"

//calcule la distence entre les points a et b
double distance(POINT a, POINT* b){
	return sqrt((a.x - b->x)*(a.x - b->x) + (a.y - b->y)*(a.y - b->y));
}

hashset_t hashset_difference(hashset_t S, hashset_t T){
    hashset_t result = hashset_create();
    hashset_itr_t iter = hashset_iterator(S);

    while(hashset_iterator_has_next(iter))
    {
    	if(!hashset_is_member(T,(POINT*)hashset_iterator_value(iter)))  
        	hashset_add(result, (POINT*)hashset_iterator_value(iter));
        hashset_iterator_next(iter);
    }
    return result;
}

int appartenance_conv(POINT p, hashset_t T){
	//retourne 1 si p appartient a conv(T), 0 sinon
	//TODO
	return 1;
}

int appartenance_aff(POINT p, hashset_t T){
	//retourne 1 si p appartient a aff(T), 0 sinon
	//TODO
	return 0;
}

void dropping(hashset_t* T){
	//TODO trouver le point q qu'on doit enlever
	//hashset_remove(T, &q)
}

void walking(POINT*c, hashset_t T){
	//TODO deplace c vers cc(T)

}


CERCLE* algorithme_fischer(hashset_t S){

	POINT c; //un point aleatoire de S
	hashset_itr_t iter = hashset_iterator(S);
	c.x = ((POINT*)hashset_iterator_value(iter))->x;
	c.y = ((POINT*)hashset_iterator_value(iter))->y;

	printf("in function c.x = %d c.y = %d\n", c.x, c.y); 
	//TODO resoudre probleme: le point c commence au 2eme point du set au lieu du premier


	POINT* p; // le point le plus eloigne de c
	double max=0;
	while(hashset_iterator_has_next(iter))
    {
    	POINT* q = (POINT*)hashset_iterator_value(iter);
    	printf("in function q.x = %d q.y = %d\n", q->x, q->y);
    	if(max < distance(c,q)){
    		max = distance(c,q);
    		p = q;
    	}
        hashset_iterator_next(iter);
    }

	hashset_t T = hashset_create();
	hashset_add(T, &p);

	while(!appartenance_conv(c,T)){
		if(appartenance_aff(c,T)){
			dropping(&T);
		}
		walking(&c, T);
	}

	CERCLE* resultat;
	resultat = (CERCLE*)malloc(sizeof(CERCLE));
	resultat->x = c.x;
	resultat->y = c.y;
	resultat->d = 2*distance(c,p);
	return resultat;
}
