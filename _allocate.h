//****************************************************************************
//****************************************************************************
//******************************ALLOCATE**************************************
//****************************************************************************
//****************************************************************************
void reset_arrays(){
    
    for(int i = 1; i<=array_max; i++){
        
        //***********************
        //GEOMETRIC ELEMENTS*****
        //***********************
        for(int j = 0; j < 3; j++){
            v[i][j]=0;
            e[i][j]=0;
        }
        //***********************
        //CELL ARRAYS************
        //***********************
        //cell_edges
        cell_edges[i][1]=0;
        cell_edges[i][2]=0;
        //cell_vertices
        cell_vertices[i][1]=0;
        cell_vertices[i][2]=0;
        //***********************
        
        
        //***********************
        //ATTRIBUTES*************
        //***********************
        for(int j = 1; j < 3; j++){
            v_F[i][j]=0;
            v_edges[i][j]=0;
        }
        //***********************
        //vertices
        v_type[i]=0;
        //edges
        e_length[i]=0;
        e_type[i]=0;
        e_cell[i]=0;
        //***********************
        //cells
        c_area[i]=0;
        //***********************
    }
}
//****************************************************************************
void allocate(){// allocate space
    
    srand(RANDOM_SEED);
    
    int arrayMax=array_max+1;
    
    //GEOMETRIC ELEMENTS
    Nv      = 0;
    Ne      = 0;
    Nc      = 0;
    v        = new double*[arrayMax];
    e = new int*[arrayMax];
    cell_edges    = new int*[arrayMax];
    cell_vertices = new int*[arrayMax];
    for(int i=0; i < arrayMax; i++){
        v[i]        = new double[3];
        e[i]   = new int[3];
        cell_edges[i]    = new int[25];
        cell_vertices[i] = new int[25];
    }
    
    //ATTRIBUTES
    //vertices
    v_F      = new double*[arrayMax];
    v_edges      = new int*[arrayMax];
    for(int i=0; i < arrayMax; i++){
        v_F[i]      = new double[3];
        v_edges[i]      = new int[3];
    }
    v_type = new int[arrayMax];

    //edges
    e_length = new double[arrayMax];
    e_type = new int[arrayMax];
    e_cell = new int[arrayMax];

    //cells
    c_area = new double[arrayMax];
    
    //MISC
    perioXY = new double[2];
    
    //RESET ARRAYS
    reset_arrays();

    return ;
}
//****************************************************************************
void deallocate(){// Deallocate space
    
    printProgress(Time/(1.*TOTAL_TIME));
    printf("\n");
    
    int arrayMax=array_max+1;

    //GEOMETRIC ELEMENTS
    for(int i=0; i < arrayMax; i++){
        delete [] v[i]      ;
        delete [] e[i];
        delete [] cell_edges[i]   ;
        delete [] cell_vertices[i];
    }
    delete [] v;
    delete [] e;
    delete [] cell_edges   ;
    delete [] cell_vertices;

    //vertices
    for(int i=0; i < arrayMax; i++){
        delete [] v_F[i]    ;
        delete [] v_edges[i]    ;
    }
    delete [] v_F    ;
    delete [] v_edges    ;
    delete [] v_type;
    
    //edges
    delete [] e_length;
    delete [] e_type;
    delete [] e_cell;
    
    //cells
    delete [] c_area;
    
    //MISC
    delete [] perioXY;

    return ;
}
//****************************************************************************
