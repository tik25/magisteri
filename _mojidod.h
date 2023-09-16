//#include <iostream> should be in alrd
#include <fstream>

// Define a structure to represent a point with x and y coordinates
struct Point {
    double x;
    double y;
};

// Function to calculate middle points of vertical cell sides and save
void calc_midpoints() {
    // Create an output file stream
    std::ofstream outputFile("output/midpoints.txt");

    // Loop through the cells and calculate midpoints
    for (int i = 1; i <= Nc; i++) {
        int v1 = cell_vertices[i][2];
        int v2 = cell_vertices[i][3];
        Point midpoint;
        midpoint.x = (v[v1][1] + v[v2][1]) / 2.0;
        midpoint.y = (v[v1][2] + v[v2][2]) / 2.0;
        
        // Save the midpoint to the file
        outputFile << midpoint.x << " " << midpoint.y << std::endl;
    }

    // Close the output file
    outputFile.close();
}


void save_metadata(){
    // Open a file for writing
    FILE *file = fopen("variables.csv", "w");

    // Save the variables to CSV
    fprintf(file, "Variable,Value\n");
    fprintf(file, "ALPHA,%f\n", ALPHA);
    fprintf(file, "BETA,%f\n", BETA);
    fprintf(file, "K_SPRING,%f\n", K_SPRING);
    fprintf(file, "SINEAMP,%f\n", SINEAMP);
    fprintf(file, "DELTA_OUT_TIME,%f\n", DELTA_OUT_TIME);
    fprintf(file, "COMPRESSION,%f\n", COMPRESSION);
    fprintf(file, "TOTAL_TIME,%f\n", TOTAL_TIME);
    fprintf(file, "COMPRESSION_TIME,%f\n", COMPRESSION_TIME);
    fprintf(file, "CELL_NUMBER,%d\n", CELL_NUMBER);

    fclose(file);
}

/**************************saving energies*****************************/

//definethe structure
void make_struct(){
    typedef struct OutputNode {
        double Time, wA, wL, wH, totalW, max_move;
        struct OutputNode* next;
    } OutputNode;

    OutputNode* head = NULL;
    OutputNode* tail = NULL;
}

// Append to linked list instead of printing
void append_energies(){
    OutputNode* newNode = malloc(sizeof(OutputNode));

    newNode->Time = Time;
    newNode->wA = wA;
    newNode->wL = wL;
    newNode->wH = wH;
    newNode->totalW = wA + wL;
    newNode->max_move = max_move;
    newNode->next = NULL;

    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
}


void save_energies() {
    FILE* fp = fopen("energy.txt", "w");
    //header
    fprintf(fp, "Time\twA\twL\twH\tw\tmax_move\n");

    OutputNode* current = head;
    while (current) {
        fprintf(fp, "%g\t%.20g\t%.20g\t%.20g\t%.20g\t%g\n", 
            current->Time, current->wA, current->wL, current->wH, current->totalW, current->max_move);
        
        OutputNode* toFree = current;
        current = current->next;
        free(toFree);
    }

    fclose(fp);
}




