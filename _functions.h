//DECLARATIONS
#include <stdio.h>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <time.h>
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

//GEOMETRIC ELEMENTS
int Nv, Ne, Nc;
double **v;
int **e;
int **cell_edges;
int **cell_vertices;

//ATTRIBUTES
//vertices
double **v_F;
int **v_edges;
int *v_type;
//edges
int *e_type;
int *e_cell;
double *e_length;

//cells
double *c_area;

//MISC
double *perioXY;
double Lx0;
double Time=0, max_move=0;
double wA=0, wL=0, wH=0;
int kount=0;
double time0=0;
double lthBM=0.005;
int array_max=10000;
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
#include "_periodic_boundaries.h"
#include "_output.h"
#include "_allocate.h"
#include "_rndom.h"
#include "_force_area.h"
#include "_force_length.h"
#include "_create.h"
#include "_initial_structure.h"
#include "_equation_of_motion.h"
//****************************************************************************
//****************************************************************************
#include "_mojidod.h"
