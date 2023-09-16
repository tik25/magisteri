//****************************************************************************
//****************************************************************************
//***********************EQUATION OF MOTION***********************************
//****************************************************************************
void calc_forces(){
    
    //CALC EDGE LENGTHS
    for(int i = 1; i <= Ne; i++){
        if(LENGTH0==-1 && e_type[i]==2) LENGTH0 = edge_Length(i); // set resting spring lenght to something realistic
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
        wH += e_Hook_force(i);
    }
    
}
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
    //APPEND ENERGIES FOR SAVING
    append_energies();
    
    //t=t+dt
    Time+=dt;
    
    
    return 0;
}
//****************************************************************************
