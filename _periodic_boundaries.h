//****************************************************************************
//****************************************************************************
//*******************************TORUS****************************************
//****************************************************************************
//****************************************************************************
void torus_dx_dy(double *dxdy, int vert_id, int vert_ref_id){
    
    dxdy[0]=0;
    dxdy[1]=0;
    
    //x
    if(fabs(v[vert_id][1]-v[vert_ref_id][1])>0.5*perioXY[0]){
        if      (v[vert_id][1]<v[vert_ref_id][1])   dxdy[0]=perioXY[0];
        else if (v[vert_id][1]>v[vert_ref_id][1])   dxdy[0]=-perioXY[0];
    }
    else dxdy[0]=0;
    //y
    if(fabs(v[vert_id][2]-v[vert_ref_id][2])>0.5*perioXY[1]){
        if      (v[vert_id][2]<v[vert_ref_id][2])   dxdy[1]=perioXY[1];
        else if (v[vert_id][2]>v[vert_ref_id][2])   dxdy[1]=-perioXY[1];
    }
    else dxdy[1]=0;
}
//****************************************************************************
void torus_vertex(int i){
    //x
    if      (v[i][1]<0)             v[i][1] += perioXY[0];
    else if (v[i][1]>perioXY[0])   v[i][1] -= perioXY[0];
    //y
    if      (v[i][2]<0)             v[i][2] += perioXY[1];
    else if (v[i][2]>perioXY[1])   v[i][2] -= perioXY[1];
}
//****************************************************************************
