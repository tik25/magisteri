//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
double edge_Length(int i){
    double *dxdy = new double[2];
    dxdy[0]=0; dxdy[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy(dxdy,v1,v2);
    double ddx=v[v2][1]-(v[v1][1]+dxdy[0]);
    double ddy=v[v2][2]-(v[v1][2]+dxdy[1]);
    double lb=sqrt(ddx*ddx+ddy*ddy);
    delete []dxdy;
    return lb;
}
//****************************************************************************
double e_Length_force(int i){
    
    double eg;
    if(e_type[i]==1) eg=BETA;
    if(e_type[i]==2) eg=ALPHA;
    if(e_type[i]==3) eg=1;
    
    double ddx,ddy;
    double *dxdy = new double[2];
    dxdy[0]=0; dxdy[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy(dxdy,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdy[0]);
    ddy=v[v2][2]-(v[v1][2]+dxdy[1]);
    delete []dxdy;
    
    double c0;
    if(e_length[i]<0.00000001) c0=0;
    else c0 = -eg/e_length[i];
    
    //v1
    v_F[v1][1]+=-c0*ddx;
    v_F[v1][2]+=-c0*ddy;
    
    //v2
    v_F[v2][1]+=c0*ddx;
    v_F[v2][2]+=c0*ddy;
    
    return eg*e_length[i];
}
//****************************************************************************

double e_Hook_force(int i){
    double ddx,ddy;
    double *dxdy = new double[2];
    dxdy[0]=0; dxdy[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy(dxdy,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdy[0]);
    ddy=v[v2][2]-(v[v1][2]+dxdy[1]);
    delete []dxdy;
    
    double c0;
    c0 = -2*K_SPRING*(e_length[i]-LENGTH0);
    
    //v1
    v_F[v1][1]+=-c0*ddx;
    v_F[v1][2]+=-c0*ddy;
    
    //v2
    v_F[v2][1]+=c0*ddx;
    v_F[v2][2]+=c0*ddy;
    
    return K_SPRING*pow(e_length[i]-LENGTH0,2);
}

