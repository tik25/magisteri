#include <cmath>
//*******************PARAMETERS***************************
//INPUT PARAMETERS
double ALPHA=2.5; /*apical (upper) surface tension*/
double BETA=0.6; /*basal (lower) surface tension*/
double LENGTH0=1/sqrt(ALPHA+BETA); /*spring resting length*/
double K_SPRING=0.05; /*apical spring coefficient*/
double SINEAMP=5;  /*amplitude of the initial sine peak*/
int SAVE_ALL=0; /*save energy at every step or only last (0/1 , n/y) */
int ONLY_FINAL=1; /*save only the final snapshot of the tissue (0/1 , n/y) */

double DELTA_OUT_TIME=500; /*output frequency*/
double COMPRESSION=-0.001; /*compression (<0) or extension (>0) in %*/
double TOTAL_TIME=100000; /*total integration time (default 80000)*/
double COMPRESSION_TIME=50000.;
const char *BASE_OUTDIR; //base directory of the structure
int CELL_NUMBER=100; /*cell count*/
double dt=0.001; /*time step*/
double CELL_BULK_MODULUS=100; /*cell-area compressibility modulus*/
int RANDOM_SEED=134; /*seed for random number generator*/
double VERTEX_PERTURBATION=0.05; /*magnitude of the initial perturbation from a flat state*/
char* EXP_COMMENT;
char* WHERE;

//*******************DECLARATIONS*************************
#include "_functions.h"
//********************MAIN********************************
int main(int argc, char *argv[]){
    //overwrite parameter values with commandline arguments
    if(argc != 8) { std::cerr << "Error! Wrong number of input elements!" << std::endl; return -1; }
    ALPHA = atof(argv[1]);
    BETA = atof(argv[2]);
    CELL_NUMBER = atoi(argv[3]);
    COMPRESSION = atof(argv[4]);
    K_SPRING = atof(argv[5]);
    TOTAL_TIME = atof(argv[6]);
    WHERE  = argv[7]; // "home" / "ijs"
    EXP_COMMENT = argv[8]; //coment za specific run saved in comment.txt
    //printf("Values updated\n");

    //get directory of the structure
    if (strcmp(WHERE, "ijs") == 0) {BASE_OUTDIR = "/scratch/yap/OutputData";}
    else if (strcmp(WHERE, "home") == 0) {BASE_OUTDIR = "../../OutputData";}
    else {std::cerr << "Error! Cannot determine data path!" << std::endl; return -1;}

    clock_t start_time = clock();/*start the timer*/

    allocate(); /*allocates memory for arrays*/
    set_initial_flat(CELL_NUMBER); /*sets the initial cell configuration*/
    //flat_to_sine(SINEAMP); /*impose a sine like peak shape*/
    perturb_vertex_positions(VERTEX_PERTURBATION); /*perturbs vertex positions*/
    //**************************************************
    directory_setup();

    while(Time<=TOTAL_TIME){
        output_state(!ONLY_FINAL,DELTA_OUT_TIME); /*true=output at t=i*DELTA_OUTPUT_TIME (i=0,1,2...)*/
        integration_step(false); /*integration step t-->t+h) ... true/false=prints in terminal or not*/
        if(Time<=COMPRESSION_TIME) compress(Lx0*(1.+COMPRESSION*Time/COMPRESSION_TIME)); /*compression ... the argument is the new total tissue length*/
    }
    output_final_state(true); /*true=outputs the final state*/
    
    /**************************do additional stuff for analy*******************************/

    //calculate midpoints and save them
    calc_midpoints();

    save_metadata();

    save_comment();

    save_energies();
    //*************************endof******************************


    deallocate(); /*deallocates memory*/
    //*************************
    clock_t end_time = clock(); /*print duration*/
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);

    //getchar(); // Wait for a key press

    return 0;
}
//********************************************************
