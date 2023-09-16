//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
double dA_new(int cellID, int j){
    
    int vert_ref_id=cell_vertices[cellID][3];
    double vrefx = v[vert_ref_id][1];
    double vrefy = v[vert_ref_id][2];
    
    
    //vertices
    int v1, v2;
    if(j==2+cell_vertices[cellID][2]){
        v1=cell_vertices[cellID][j];
        v2=cell_vertices[cellID][3];
    }
    else {
        v1=cell_vertices[cellID][j];
        v2=cell_vertices[cellID][j+1];
    }
    
    //v1
    double v1x=v[v1][1];
    double v1y=v[v1][2];
    //x
    if(fabs(v1x-vrefx)>perioXY[0]/2.){
        if(v1x<vrefx) v1x+=perioXY[0];
        else if(v1x>vrefx) v1x-=perioXY[0];
    }
    //y
    if(fabs(v1y-vrefy)>perioXY[1]/2.){
        if(v1y<vrefy) v1y+=perioXY[1];
        else if(v1y>vrefy) v1y-=perioXY[1];
    }
    
    //v2
    double v2x=v[v2][1];
    double v2y=v[v2][2];
    //x
    if(fabs(v2x-vrefx)>perioXY[0]/2.){
        if(v2x<vrefx) v2x+=perioXY[0];
        else if(v2x>vrefx) v2x-=perioXY[0];
    }
    //y
    if(fabs(v2y-vrefy)>perioXY[1]/2.){
        if(v2y<vrefy) v2y+=perioXY[1];
        else if(v2y>vrefy) v2y-=perioXY[1];
    }
    
    return 0.5*(-v2x*v1y + v1x*v2y);
}
//****************************************************************************
double CellArea_new(int i){
    double areaSum=0;
    for(int j=3; j<=2+cell_vertices[i][2]; j++ ) areaSum += dA_new(i,j);
    return areaSum;
}
//****************************************************************************
void v_AreaCompressibility_force_New(int j, int cellID, double _Cellarea){
    
    int vert_ref_id=cell_vertices[cellID][3];
    double vrefx = v[vert_ref_id][1];
    double vrefy = v[vert_ref_id][2];
    
    
    //vertices
    int v1, v2;
    if(j==2+cell_vertices[cellID][2]){
        v1=cell_vertices[cellID][j];
        v2=cell_vertices[cellID][3];
    }
    else {
        v1=cell_vertices[cellID][j];
        v2=cell_vertices[cellID][j+1];
    }
    
    //v1
    double v1x=v[v1][1];
    double v1y=v[v1][2];
    //x
    if(fabs(v1x-vrefx)>perioXY[0]/2.){
        if(v1x<vrefx) v1x+=perioXY[0];
        else if(v1x>vrefx) v1x-=perioXY[0];
    }
    //y
    if(fabs(v1y-vrefy)>perioXY[1]/2.){
        if(v1y<vrefy) v1y+=perioXY[1];
        else if(v1y>vrefy) v1y-=perioXY[1];
    }
    
    //v2
    double v2x=v[v2][1];
    double v2y=v[v2][2];
    //x
    if(fabs(v2x-vrefx)>perioXY[0]/2.){
        if(v2x<vrefx) v2x+=perioXY[0];
        else if(v2x>vrefx) v2x-=perioXY[0];
    }
    //y
    if(fabs(v2y-vrefy)>perioXY[1]/2.){
        if(v2y<vrefy) v2y+=perioXY[1];
        else if(v2y>vrefy) v2y-=perioXY[1];
    }
    
    
    //GRADIENT
    double _deriv = -2.*CELL_BULK_MODULUS*(_Cellarea-1.);
    //v1
    v_F[v1][1] += _deriv*(v2y/2.);
    v_F[v1][2] += _deriv*(-v2x/2.);
    //v2
    v_F[v2][1] += _deriv*(-v1y/2.);
    v_F[v2][2] += _deriv*(v1x/2.);
    
}
//****************************************************************************
double c_AreaCompressibility_force_New(const int cellID){
    
    double _Cellarea=c_area[cellID];
    
    for(int j=3; j<=2+cell_vertices[cellID][2]; j++ ){
        v_AreaCompressibility_force_New(j,cellID,_Cellarea);
    }
    
    return CELL_BULK_MODULUS*pow(_Cellarea-1.,2);
}
//****************************************************************************
