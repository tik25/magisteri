//****************************************************************************
//****************************************************************************
//***********************CREATE***********************************************
//****************************************************************************
//****************************************************************************
void createListOfVertices(int i){
    cell_vertices[i][1]=i; cell_vertices[i][2]=4;
    for(int j=3; j<=2+cell_vertices[i][2]; j++){
        if(cell_edges[i][j]<0) cell_vertices[i][j]=e[abs(cell_edges[i][j])][2];
        else cell_vertices[i][j]=e[cell_edges[i][j]][1];
    }
}
//****************************************************************************
int createVertex(int i, double v_x, double v_y, int vtype){
    
    if(i>Nv) Nv++;
    
    v[i][0]=i;
    v[i][1]=v_x;
    v[i][2]=v_y;
    
    v_type[i]=vtype;
    
    return i;
}
//****************************************************************************
int createEdge(int i, int v1, int v2, int etype){
    
    if(i>Ne) Ne++;
    
    e[i][0]=i;
    e[i][1]=v1;
    e[i][2]=v2;
    
    //ATTRIBUTES
    e_type[i]=etype;
    e_length[i]=edge_Length(i);
    
    return i;
}
//****************************************************************************
int createCell(int i, int e1, int e2, int e3, int e4, int ctype){
    
    if(i>Nc) Nc++;
    
    cell_edges[i][1]=i; cell_edges[i][2]=4;
    cell_edges[i][3]=e1;
    cell_edges[i][4]=e2;
    cell_edges[i][5]=e3;
    cell_edges[i][6]=e4;
    
    //LIST OF VERTICES
    createListOfVertices(i);
    
    //ATTRIBUTES
    c_area[i]=CellArea_new(i);
    
    //EDGE ATTRIBUTE
    e_cell[abs(e1)]=i;
    
    return i;
}
//****************************************************************************
