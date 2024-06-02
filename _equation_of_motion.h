#include <math.h>

//****************************************************************************
//****************************************************************************
//***********************EQUATION OF MOTION***********************************
//****************************************************************************
void calc_forces(){
    
    //CALC EDGE LENGTHS
    for(int i = 1; i <= Ne; i++){
        if(LENGTH0==-1 && e_type[i]==2) LENGTH0 = edge_Length(i); // set resting spring length to something realistic if not already set in main.c
        e_length[i]=edge_Length(i);
    }
    
    //CALC CELL AREAS
    for(int i = 1; i <= Nc; i++){
        c_area[i]=CellArea_new(i);
    }

    //AREA TERM
    wA=0; for(int i = 1; i <= Nc; i++){
        wA += c_AreaCompressibility_force_New(i);
    }
    
    //LINE-TENSION TERM
    wL=0; for(int i = 1; i <= Ne; i++){
        wL += e_Length_force(i);
    }

    //HOOKEAN TERM
    wH=0; for(int i = 1; i <= Ne; i++){
        if(e_type[i]==2) wH += e_Hook_force(i);//ALPHA (apikalna)
    }
    
}
//****************************************************************************
//definethe structure for energy saving
typedef struct OutputNode {
    double Time, wA, wL, wH, totalW, max_move;
    struct OutputNode* next;
} OutputNode;

OutputNode* head = NULL;
OutputNode* tail = NULL;
//****************************************************************************
double integration_step(int printout){
    
    //CALCULATE FORCES
    calc_forces();

    //EQUATION OF MOTION
    for(int i = 1; i <= Nv; i++){
        
        //MOVES VERTICES
        double FORCE=0;
        for(int j=1; j<=2; j++){
            v[i][j] += dt*v_F[i][j];
            FORCE += pow(v_F[i][j], 2);
        }
        double dr = dt*sqrt(FORCE);
        if(dr>max_move) max_move=dr; //zakaj
        
        
        //PERIODIC BOUNDARY CONDITIONS
        torus_vertex(i);
        
            
        //RESETS FORCE
        for(int j=1; j<=2; j++) v_F[i][j] = 0;

    }
    
    
    //OUTPUT
    if(printout==true) printf("%g \t\t wA=%.20g \t\t wL=%.20g \t\t wH=%.20g \t\t w=%.20g \t\t %g\n", Time, wA, wL, wH, wA+wL+wH, max_move);
    //APPEND ENERGIES TO LINKED LIST
    if(SAVE_ALL == 1 || Time >= TOTAL_TIME-dt) {
        OutputNode *newNode = (OutputNode *) malloc(sizeof(OutputNode));
        newNode->Time = Time;
        newNode->wA = wA;
        newNode->wL = wL;
        newNode->wH = wH;
        newNode->totalW = wA + wL + wH;
        newNode->max_move = max_move;
        newNode->next = NULL;

        if (tail) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
    }
    //t=t+dt
    Time+=dt;
    
    
    return 0;
}
//****************************************************************************
