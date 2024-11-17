#include <stdlib.h>
#include <stdio.h>

double main(int argc, char **argv) {
    int choice=atoi(argv[5]);
    char* ptr;
    double N1 = strtod(argv[1],&ptr); 
    double TN1 = strtod(argv[2],&ptr); 
    double N2 = strtod(argv[3],&ptr); 
    double TN2 = strtod(argv[4],&ptr); 
    switch (choice) {
        case 1: 
            printf("%lf", (N2-N1)/((N2/TN2)-(N1/TN1)));
        break;
        case 2:
            printf("%lf",((N1/TN1)*N2-((N2/TN2)*N1))/(N2-N1));
        break;
        default:
        break;
    }
    

}