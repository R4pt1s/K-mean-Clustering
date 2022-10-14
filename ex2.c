#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define EXAMPLES   150

struct points {
   float  x1;
   float  x2;
} ;


void set_team(struct points *point1){
    FILE *fp ,*fd;
    srand(time(NULL)); 
    if ((fp = fopen("set_team.txt","w")) == NULL ) exit(1);
    float range = 1.25 - 0.75;
    int i;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range * ((((float) random()) / (float) RAND_MAX)) + 0.75 ;
        point1->x2 = range * ((((float) random()) / (float) RAND_MAX)) + 0.75 ;
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }
    float range2 = 0.5;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range2 * ((((float) random()) / (float) RAND_MAX));
        point1->x2 = range2 * ((((float) random()) / (float) RAND_MAX));
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }
    float range3 = 2.0 - 1.5 ;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range3 * ((((float) random()) / (float) RAND_MAX)) + 1.5;
        point1->x2 = range3 * ((((float) random()) / (float) RAND_MAX)) + 1.5;
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }

    float range4 = 0.5 ;
    float range5 = 2.0 - 1.5;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range4 * ((((float) random()) / (float) RAND_MAX));
        point1->x2 = range5 * ((((float) random()) / (float) RAND_MAX)) + 1.5;
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }

    float range6 = 2.0 - 1.5 ;
    float range7 = 0.5;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range6 * ((((float) random()) / (float) RAND_MAX)) + 1.5;
        point1->x2 = range7 * ((((float) random()) / (float) RAND_MAX)) ;
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }

    float range8 = 2.0 ;
    for (i=0; i<EXAMPLES; i++){
        point1->x1 = range8 * ((((float) random()) / (float) RAND_MAX));
        point1->x2 = range8 * ((((float) random()) / (float) RAND_MAX));
        fprintf(fp,"%lf\t %lf\n",point1->x1,point1->x2);
    }
}

int main() {
    struct points pnts;   
     
    set_team(&pnts);

    return 0;
}

