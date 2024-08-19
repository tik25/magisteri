//****************************************************************************
//****************************************************************************
//******************************OUTPUT****************************************
//****************************************************************************
//****************************************************************************
double out_Tissue(){
    
    kount++;
    int fcount=kount;
    
    
    char filename2[100]; char filename3[100]; char filename4[100];
    snprintf(filename2, sizeof(char) * 100, "%s/object/X_a%g_b%g_k%g_%d.txt", OUTDIR, ALPHA, BETA, K_SPRING, fcount);
    snprintf(filename3, sizeof(char) * 100, "%s/object/Y_a%g_b%g_k%g_%d.txt", OUTDIR, ALPHA, BETA, K_SPRING, fcount);
    snprintf(filename4, sizeof(char) * 100, "%s/object/Lx_a%g_b%g_k%g.txt", OUTDIR, ALPHA, BETA, K_SPRING);
    
    double *dxdy = new double[2];
    dxdy[0]=0; dxdy[1]=0;
    int vert_ref_id, vert_id;
    FILE *file2; file2 = fopen(filename2, "wt");
    FILE *file3; file3 = fopen(filename3, "wt");
    FILE *file4;
    if(fcount==1) file4 = fopen(filename4, "wt");
    else file4 = fopen(filename4, "at");
    
    for(int i=1; i<=Nc; i++) if(cell_edges[i][1]!=0){
            
        fprintf(file2, "%d ", cell_vertices[i][2]);
        fprintf(file3, "%d ", cell_vertices[i][2]);
            
        vert_ref_id=cell_vertices[i][3];
        fprintf(file2, "%g ", v[vert_ref_id][1]);
        fprintf(file3, "%g ", v[vert_ref_id][2]);
            
        for(int j = 4; j <= 2+cell_edges[i][2]; j++){
            vert_id=cell_vertices[i][j];
            torus_dx_dy(dxdy,vert_id,vert_ref_id);
            fprintf(file2, "%g ", v[vert_id][1] + dxdy[0]);
            fprintf(file3, "%g ", v[vert_id][2] + dxdy[1]);
        }
            
        //for(int j = cell_edges[i][2]; j <= 15; j++){  nek zero padding, najbrz zrd mathematice?
        //    fprintf(file2, "0 ");
        //    fprintf(file3, "0 ");
        //}
            
        fprintf(file2, "\n");
        fprintf(file3, "\n");
    }
    
    fprintf(file4, "%.8g\n", perioXY[0]);
    
    fclose(file2);
    fclose(file3);
    fclose(file4);
    
    delete []dxdy;
    
    return 0;
}
//****************************************************************************
void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
//****************************************************************************
void output_state(int printOrNot, double deltaTime){
    if(Time>=time0){
        if(printOrNot==true) out_Tissue();
        time0+=deltaTime;
        //printf("%g  %d\n", Time, kount);
        //printProgress(Time/(1.*TOTAL_TIME)); stupid progress bar
    }
}
//****************************************************************************
void output_final_state(int printOrNot){
    if(printOrNot==true) out_Tissue();
}
//****************************************************************************


//*********************NOVO DODATNO

void output_final(int PrintOrNot){
    char filename2[100];
    snprintf(filename2, sizeof(char) * 200, "%s/object/X_Y_a%g_b%g_k%g.txt", OUTDIR, ALPHA, BETA, K_SPRING);
    FILE *file2; file2 = fopen(filename2, "wt");
    if(PrintOrNot==true){
        int N_vertex = 2*CELL_NUMBER + 2;

        for(int k=0; k<N_vertex; k++){
            fprintf(file2, "%d %f %f \n", v_type[k], v[k][1], v[k][2]);
        }

    }
    fclose(file2);
}
//****************************************************************************


//*****************************************************************************
void output_vertices_edges(int PrintOrNot){
    int count=kount;
    if(PrintOrNot == true){
        char filename[100];
        char filename1[100];
        char filename2[100];
        snprintf(filename, sizeof(char)*200, "%s/object/v_a%g_b%g_k%g_%d.txt", OUTDIR, ALPHA, BETA, K_SPRING, count);
        snprintf(filename1, sizeof(char)*200, "%s/object/e_a%g_b%g_k%g_%d.txt", OUTDIR, ALPHA, BETA, K_SPRING, count);
        snprintf(filename2, sizeof(char)*200, "%s/object/cell_v_a%g_b%g_k%g_%d.txt", OUTDIR, ALPHA, BETA, K_SPRING, count);
        FILE *file; file = fopen(filename, "wt");
        FILE *file1; file1 = fopen(filename1, "wt");
        FILE *file2; file2 = fopen(filename2, "wt");

        int N_vertex = 2*CELL_NUMBER + 2;
        int N_edges = 3*CELL_NUMBER + 1;

        for(int k=0; k<N_vertex; k++){
            fprintf(file, "%d %f %f \n", int(v[k][0]), v[k][1], v[k][2]);}
        fclose(file);

        for(int j = 0; j< N_edges; j++){
            fprintf(file1, "%d %d %d %d \n", e[j][0], e[j][1], e[j][2], e_type[j]);

        }
        fclose(file1);

        for(int j = 1; j<= CELL_NUMBER; j++){
            fprintf(file2, "%d %d %d %d %d %d\n", cell_vertices[j][1], cell_vertices[j][2], cell_vertices[j][3], cell_vertices[j][4], cell_vertices[j][5], cell_vertices[j][6]);

        }
        fclose(file2);

    }
}