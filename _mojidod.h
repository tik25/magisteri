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
    sprintf(filePath, "%s/midpoints.txt", OUTDIR);
    std::ofstream outputFile(filePath);

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
    sprintf(filePath, "%s/variables.csv", OUTDIR);
    FILE *file = fopen(filePath, "w");

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
void save_energies() {
    sprintf(filePath, "%s/energy.txt", OUTDIR);
    FILE* fp = fopen(filePath, "w");
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

void directory_setup(){
    //make a new directory for the current run using timestamp
    time_t t;
    struct tm *tmp;
    char runDirName[50];
    t = time(NULL);
    tmp = localtime(&t);
    //just in case
    if (tmp == NULL) {
        perror("localtime");
        exit(EXIT_FAILURE);
    }
    if (strftime(runDirName, sizeof(runDirName), "Run_%Y-%m-%d_%H-%M-%S", tmp) == 0) {
        fprintf(stderr, "strftime returned 0");
        exit(EXIT_FAILURE);
    }

    snprintf(OUTDIR, sizeof(OUTDIR), "%s/%s", BASE_OUTDIR, runDirName);

    //create the main directory
    #ifdef _WIN32
    _mkdir(OUTDIR);
    #else
    mkdir(OUTDIR, 0755);
    #endif


    const char *subdirName = "object";
    char DirPath[100];
    //full path
    snprintf(DirPath, sizeof(DirPath), "%s/%s", OUTDIR, subdirName);
    //operating system specific functions to check if the directory exists and makeit
    #ifdef _WIN32
    struct _stat info;
    if (_stat(DirPath, &info) != 0) {
        _mkdir(DirPath);
    }
    #else
    struct stat info;
    if (stat(DirPath, &info) != 0) {
        mkdir(DirPath, 0755);
    }
    #endif
}

