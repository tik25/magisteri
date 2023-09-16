#include <cmath>
//*******************PARAMETERS***************************
//INPUT PARAMETERS
double ALPHA=2.1; /*apical surface tension*/
double BETA=0.6; /*basal surface tension*/
double LENGTH0=1/sqrt(ALPHA+BETA); /*spring resting length*/
double K_SPRING=0.05; /*apical spring coefficient*/
double SINEAMP=5;  /*amplitude of the initial sine peak*/

double DELTA_OUT_TIME=500; /*output frequency*/
double COMPRESSION=-0.04; /*compression (<0) or extension (>0) in %*/
double TOTAL_TIME=80000; /*total integration time*/
double COMPRESSION_TIME=50000.;

int CELL_NUMBER=50; /*cell count*/
double dt=0.001; /*time step*/
double CELL_BULK_MODULUS=100; /*cell-area compressibility modulus*/
int RANDOM_SEED=1; /*seed for random number generator*/
double VERTEX_PERTURBATION=0.05; /*magnitude of the initial perturbation from a flat state*/


//*******************DECLARATIONS*************************
#include "_functions.h"
//********************MAIN********************************
int main(int argc, char *argv[]){
    clock_t start_time = clock();/*start the timer*/

    allocate(); /*allocates memory for arrays*/
    set_initial_flat(CELL_NUMBER); /*sets the initial cell configuration*/
    flat_to_sine(SINEAMP); /*impose a sine like peak shape*/
    perturb_vertex_positions(VERTEX_PERTURBATION); /*perturbs vertex positions*/
    make_struct(); /*prepare for saving the energies*/
    //**************************************************
    
    
    while(Time<=TOTAL_TIME){
        output_state(true,DELTA_OUT_TIME); /*true=output at t=i*DELTA_OUTPUT_TIME (i=0,1,2...)*/
        integration_step(false); /*integration step t-->t+h) ... true/false=prints in terminal or not*/
        if(Time<=COMPRESSION_TIME) compress(Lx0*(1.+COMPRESSION*Time/COMPRESSION_TIME)); /*compression ... the argument is the new total tissue length*/
    }
    output_final_state(false); /*true=outputs the final state*/
    
    /**************************do additional stuff for analy*******************************/

    //calculate midpoints and save them
    calc_midpoints();

    save_metadata();

    save_energies();
    //*************************endof******************************


    deallocate(); /*deallocates memory*/
    //*************************
    clock_t end_time = clock(); /*print duration*/
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);
    
    getchar(); // Wait for a key press

    return 0;
}
//********************************************************
