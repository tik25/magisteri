//****************************************************************************
//****************************************************************************
//***********************INITIAL STRUCTURE************************************
//****************************************************************************
//****************************************************************************
void set_initial_flat(int _Nc){
    
    Nc=_Nc-1;
    Nv=2+2*Nc;
    Ne=1+3*Nc+2;
    
    double d0=1./sqrt(ALPHA+BETA);
    double h0=1./d0;
    
    perioXY[0] = _Nc*d0;
    Lx0=perioXY[0];
    perioXY[1] = 100;
    printf("ALPHA=%g  BETA=%g\n", ALPHA, BETA);
    
    double dx=0.1*d0, dy=0.5*perioXY[1];
    
    
    //VERTICES
    int vID;
    for(int i=1; i<=Nv/2; i++){
        vID=2*(i-1)+1; createVertex(vID,dx+(i-1)*d0,dy,1);
        vID=2*(i-1)+2; createVertex(vID,dx+(i-1)*d0,dy+h0,2);
    }

    
    //EDGES
    int vID1, vID2, vID3, vID4, eID=1;
    createEdge(eID,1,2,3);
    for(int i=1; i<Nv/2; i++){
        vID1=2*(i-1)+1;
        vID2=2*(i-1)+2;
        vID3=2*i+1;
        vID4=2*i+2;
        
        eID++; createEdge(eID,vID1,vID3,1);
        eID++; createEdge(eID,vID3,vID4,3);
        eID++; createEdge(eID,vID4,vID2,2);
    }
    eID++; createEdge(eID,Nv-1,1,1);
    eID++; createEdge(eID,2,Nv,2);
    
    
    
    //CELLS
    createCell(1,2,3,4,-1,1);
    int eIDstart=0;
    for(int i=2; i<=Nc; i++){
        eIDstart=2+3*(i-1);
        createCell(i,eIDstart,eIDstart+1,eIDstart+2,-(eIDstart+2-4),1);
    }
    createCell(Nc+1,eID-1,1,eID,-(eID-3),1);
    
    
    
    //VERY IMPORTANT!!!!
    for(int i=1; i<=Ne; i++) if(e_type[i]==1 || e_type[i]==2){
        int v1=e[i][1]; int v2=e[i][2];
        //v1
        if(v_edges[v1][1]==0) v_edges[v1][1]=i;
        else v_edges[v1][2]=i;
        //v2
        if(v_edges[v2][1]==0) v_edges[v2][1]=i;
        else v_edges[v2][2]=i;
    }
    
}
//****************************************************************************

void flat_to_sine(double amplitude){
    // midpoint of the chain in x
    double mid_x = perioXY[0] / 2.0;
    
    // Iterate over vertices
    for(int i=1; i<=Nv; i++){
        // Normalize the x to interval [0, pi]
        double normalized_x = (v[i][1] / perioXY[0]) * M_PI;

        // sine to y
        v[i][2] += amplitude * sin(normalized_x);
        
        // periodic boundary conditions
        torus_vertex(i);
    }
}
  



//******************


void perturb_vertex_positions(double pert){
    for(int i=1; i<=Nv; i++){
        v[i][1]+=pert*(-1.+2.*rnd());
        v[i][2]+=pert*(-1.+2.*rnd());
        torus_vertex(i);
    }
}
//****************************************************************************
void compress(double desiredL){
    for(int i=1; i<=Nv; i++) v[i][1]*=desiredL/perioXY[0];
    perioXY[0] = desiredL;
    //for(int i=1; i<=Nv; i++) torus_vertex(i);
}
//****************************************************************************
