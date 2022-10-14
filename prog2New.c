#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define LSIZ 901
#define RSIZ 901

#define NUM_OF_CLUSTERS 5

void random_Cluster(int numM,int *clusters){  
    float range = 900 - 0;
    srand(time(NULL)); 
    for (int i=0; i<numM; i++){
        clusters[i] = range * ((((int) random()) / (float) RAND_MAX))  ;
    }
}

void readFile_parser(float Buff[901][2]){
    char line[RSIZ][LSIZ];
    FILE *fptr = NULL; 
    int i = 0;
    char * pch;
    int flag = 0;

    printf("->[1] Read the file and store the lines into an array :\n");
	printf("------------------------------------------------------\n"); 

    fptr = fopen("set_team.txt", "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    for (int j=0; j<900; j++){
        pch = strtok (line[j]," ");
        while (pch != NULL && (flag == 0 || flag == 1))
        {
            if (flag == 1){
                Buff[j][flag] = atof(pch) ; 
                //printf("Buff[%d][%d] = %f\n",j+1,flag,Buff[j][flag]);
            }
            else if (flag == 0){
                Buff[j][flag] = atof(pch) ;
            }
            flag ++;
            pch = strtok (NULL, " ");
        }
        flag = 0;
    }
}

void euclidian_distance_random_cluster(int numM,float array[900],float matrix[900][2],int typeOfCluster[900],float eucl_distance[900],
                         float Buff[901][2],int *cluster){
    
    float sum1 = 0.0 ;
    float sum2 = 0.0 ;
    float sum = 0.0 ;
    float min = 1.0 ;
    int counter = 0 ;

    for (int j=0; j<900; j++){
        array[j]  = 3;
        matrix[j][0] = 0;
        matrix[j][1] = 0;
        typeOfCluster[j] = 9;
    }

    for (int j=0; j<numM; j++){
        for (int m=0; m<900; m++){
            sum1 = Buff[m][0] - Buff[cluster[j]][0]; 
            sum2 = Buff[m][1] - Buff[cluster[j]][1];

            float sum1InPow = powf(sum1,2);
            float sum2InPow = powf(sum2,2);

            sum = sum1InPow + sum2InPow;
            eucl_distance[m] = sqrt(sum);
            
            if (eucl_distance[m] < array[m] ){
                matrix[m][0] = Buff[m][0];
                matrix[m][1] = Buff[m][1];
                array[m] = eucl_distance[m];
                typeOfCluster[m] = j; 
                counter ++;              
            }
        }   
    }    

    FILE *fp ,*fd, *fr;
    if ((fp = fopen("matrix.txt","w")) == NULL ) exit(1);
    if ((fd = fopen("typeOfCluster.txt","w")) == NULL ) exit(1);
    if ((fr = fopen("Buff.txt","w")) == NULL ) exit(1);

    for (int i=0; i<900; i++){
        fprintf(fp,"%f\t %f\n",matrix[i][0],matrix[i][1]);
        fprintf(fd,"%d\n",typeOfCluster[i]);
    }

    for (int j=0; j<numM; j++){
        fprintf(fr,"%f\t %f\n",Buff[cluster[j]][0],Buff[cluster[j]][1]);
    }

}

void euclidian_distance_mean_cluster(FILE *fp,FILE *fd,FILE *fr,int numM,float array[900],float matrix[900][2],int typeOfCluster[900],float eucl_distance[900],float Buff[901][2],float meanTable[numM][2]){
    
    float sum1 = 0 ;
    float sum2 = 0 ;
    float sum = 0 ;
    float min = 1 ;
    int counter = 0 ;
    
    for (int j=0; j<900; j++){
        array[j]  = 3;
        matrix[j][0] = 0;
        matrix[j][1] = 0;
        typeOfCluster[j] = 9;
    }
    
    for (int j=0; j<numM; j++){
        for (int m=0; m<900; m++){
            sum1 = Buff[m][0] - meanTable[j][0];
            sum2 = Buff[m][1] - meanTable[j][1];

            float sum1InPow = pow(sum1,2);
            float sum2InPow = pow(sum2,2);

            sum = sum1InPow + sum2InPow;
            eucl_distance[m] = sqrt(sum);

            if (eucl_distance[m] < array[m] ){
                matrix[m][0] = Buff[m][0];
                matrix[m][1] = Buff[m][1];
                array[m] = eucl_distance[m];
                typeOfCluster[m] = j; 
                counter ++;              
            }
        }   
    }    

    
    for (int i=0; i<900; i++){
        fprintf(fp,"%f\t %f\n",matrix[i][0],matrix[i][1]);
        fprintf(fd,"%d\n",typeOfCluster[i]);
    }

    for (int j=0; j<numM; j++){
        fprintf(fr,"%f\t %f\n",meanTable[j][0],meanTable[j][1]);
    }

}

void find_Mean_of_each_cluster(int numM,float clusterPoints[numM][2],int typeOfCluster[900],float Buff[901][2],float meanTable[numM][2]){

    float meanMidTable[numM][2];
    int counterPoints[numM];
    
    for (int j=0; j<numM; j++){
        counterPoints[j] = 0;
        meanMidTable[j][0] = 0;
        meanMidTable[j][1] = 0;
        clusterPoints[j][0] = 0;
        clusterPoints[j][1] = 0;
    }

    for (int i=0; i<900; i++){
        for (int j=0; j<=10; j++){
            if (typeOfCluster[i] == j){
            counterPoints[typeOfCluster[i]]++;
            meanMidTable[typeOfCluster[i]][0] += Buff[i][0];
            meanMidTable[typeOfCluster[i]][1] += Buff[i][1];
            clusterPoints[typeOfCluster[i]][0] = Buff[i][0];
            clusterPoints[typeOfCluster[i]][1] = Buff[i][1];
            }
        } 
    }
  
    for (int j=0; j<numM; j++){
        meanTable[j][0] = 0;
        meanTable[j][1] = 0;
    }

    for (int k=0; k<numM; k++){
        meanTable[k][0] = meanMidTable[k][0]/counterPoints[k];
        meanTable[k][1] = meanMidTable[k][1]/counterPoints[k];
        //printf("meanMinTable %f / counterPoints %d = %f meantable \n",meanMidTable[k][0],counterPoints[k],meanTable[k][0]);
    }
    
    for (int j=0; j<numM; j++){
        //printf("Mean is %f %f %d %d\n",meanTable[j][0],meanTable[j][1],counterPoints[j],j);
    }
}

void team_error_function(int numM,double typeEucleid[numM],float clusterPoints[numM][2],int typeOfCluster[900],float Buff[901][2] ,float meanTable[numM][2]){
    
    float sum1[numM][2];
    float power1[numM][2];

    for(int j=0; j<numM; j++){
        typeEucleid[j] = 0.0;
        
        sum1[j][0] = 0;
        sum1[j][1] = 0;
        
        power1[j][0] = 0;
        power1[j][1] = 0;
    }

    double help ;

    for(int j=0; j<900; j++){
        for (int k=0; k<9; k++){
            if (typeOfCluster[j] == k ){
            help = 0.0;
            sum1[typeOfCluster[j]][0] = clusterPoints[typeOfCluster[j]][0] - meanTable[typeOfCluster[j]][0];
            sum1[typeOfCluster[j]][1] = clusterPoints[typeOfCluster[j]][1] - meanTable[typeOfCluster[j]][1];
                                    //+= kai ektos for powf kai meta ssto error_team 
            power1[typeOfCluster[j]][0] = powf(sum1[typeOfCluster[j]][0],2);
            power1[typeOfCluster[j]][1] = powf(sum1[typeOfCluster[j]][1],2);

            help = power1[typeOfCluster[j]][0] + power1[typeOfCluster[j]][1];
          
            typeEucleid[typeOfCluster[j]] += sqrt(help); //////auksano to d ka8e shmiou gia thn 0 omada
           
            }
        }
    }  
}

int main(){
    //1  //ask M , M is number of clusters
    //2  //random select M (x1,x2)
    //3  //count the euclidian distance for each point and M clusters 
    //4  // min distance and point belong to the nearest cluster
    //5  // calculate the mean of each cluster
    //6  // ----repeat from step 3----
    //7  // if not chance then stop 

    float Buff[901][2];
    readFile_parser(Buff);

    int numM;
    printf("**Please insert number of clusters below (0 <= Clusters <= 10):\n");
    scanf("%d",&numM);
    //numM = NUM_OF_CLUSTERS;
    int iteration = 100;
    printf("------------------------------------------------------\n"); 

    if (numM > 10){
        printf("You can choose only 10 clusters with this algorithm. Try it.\n");
        return 0;
    }
    else if (numM <= 0){
        printf("You can't choose 0 clusters. Try clusters from 1 to 10 with this algorithm.\n");
        return 0;
    }

    int cluster[numM];
    printf("->[2] Finding random clusters\n");
    random_Cluster(numM,cluster);

    float array[900];
    float matrix[900][2];
    int  typeOfCluster[900];
    float eucl_distance[900];

    printf("->[3] Count euclidian distance\n");
    euclidian_distance_random_cluster(numM,array,matrix,typeOfCluster,eucl_distance,Buff,cluster);

    float meanTable[numM][2];
    float clusterPoints[numM][2];

    printf("->[4] Find mean of each cluster\n");
    find_Mean_of_each_cluster(numM,clusterPoints,typeOfCluster,Buff,meanTable);

    float error_team[numM][2];
    
    float summuryx;
    float summuryy;
    double final;
    double distance;
    double typeEucleid[numM];

    FILE  *fq; // 141
    if ((fq = fopen("iter_distance.txt","w")) == NULL ) exit(1);


    printf("->[5] Repeat the proccess from 3 step\n");
    for (int i=0; i<iteration; i++){

        FILE *fp ,*fd, *fr; // 111 121 131
        if ((fp = fopen("NewMatrix.txt","w")) == NULL ) exit(1);
        if ((fd = fopen("NewTypeOfCluster.txt","w")) == NULL ) exit(1);
        if ((fr = fopen("NewBuff.txt","w")) == NULL ) exit(1);
        
        
     
        euclidian_distance_mean_cluster(fp,fd,fr,numM,array,matrix,typeOfCluster,eucl_distance,Buff,meanTable);
        find_Mean_of_each_cluster(numM,clusterPoints,typeOfCluster,Buff,meanTable);
        
        fclose(fp);
        fclose(fd);
        fclose(fr);
    
        team_error_function(numM,typeEucleid,clusterPoints,typeOfCluster,Buff,meanTable);
        
        summuryx = 0;
        summuryy = 0;
        final = 0;
        distance = 0.0;

        for(int j=0; j<numM; j++){
            distance += typeEucleid[j];
        }
        fprintf(fq,"%d %f\n",i,distance); 
        //printf("iteration-%d error x1 = %f\n",i,summuryx); 
        //printf("Distance_error-%d = %f\n",i+1,distance); 
        
    }
    fclose(fq);
    printf("->[6] End of execution.\n--- Run team_first.py , team_first.py and error.py. Thank you.\n");
    return 0;

}