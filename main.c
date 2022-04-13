#include <stdio.h>
#include <string.h>
#include "Queue.h"

int main(){
    FILE *fileIn = NULL;
    fileIn = fopen("p2Input.txt", "r");
    if(fileIn == NULL){
        printf("Unable to open input file.");
        return -1;
    }
    
    Queue checkinQ = newQueue();
    Queue vaccineQ = newQueue();

    int currentTime = 2;
    int checkinTableTime[5] = {0};
    int vaccineTableTime[10] = {0};
    int observationTime[60] = {0};
    Patient* checkinTable[5] = {NULL};
    Patient* vaccineTable[10] = {NULL};
    Patient* observationTable[60] = {NULL};
    int lastTime = 0;
    int i = 0, j = 0;
    while(currentTime - lastTime  <= 100 ){ 
        int arrivalTime, id;
        char eCheckInStr[4];
        if(fscanf(fileIn,"%d%d%s", &arrivalTime, &id, eCheckInStr) != EOF) {
            int eCheckIn ;
            if (!strcmp(eCheckInStr, "yes"))
                eCheckIn = 1;
            else
                eCheckIn = 0;

            Patient patient;
            patient.eCheckIn = eCheckIn;
            patient.patientID = id;
            if(currentTime == 0){
                currentTime = arrivalTime;
            }
            lastTime = arrivalTime;
            patient.arrivalTime = arrivalTime;
            enqueue(checkinQ, patient);
        }

        //decrement checkin table time
        for(i = 0; i <= 4; i++){
            if(checkinTable[i]!=NULL){
                checkinTableTime[i]  -= 1;
            }
        }
        // check if a patient completed electronic checkin time
        for(i = 0; i <= 4; i++){
            if(checkinTable[i] != NULL && checkinTableTime[i] == 0){
                enqueue(vaccineQ, *(checkinTable[i]));
                checkinTable[i] = NULL;
            }
        }

        for(i = 0 ; i <= 4; i++){
            if(checkinTable[i] == NULL){
                if(!isEmpty(checkinQ)) {
                    Patient *patient = (Patient*) malloc(sizeof(Patient));
                    dequeue(checkinQ, patient);
                    checkinTable[i] = patient;
                    if(patient->eCheckIn == 0)
                        checkinTableTime[i] = 10;
                    else
                        checkinTableTime[i] = 4;
                }
                else{
                    break;
                }
            }
        }
        //decrement time for vaccination
        for(i=0; i<=10; i++){
            if(vaccineTable[i] != NULL) {
                vaccineTableTime[i] -= 1;
            }
        }

        //check if anyone completed vaccination. if completed, remove from vaccination table and insert in observation table
        for(i = 0; i <= 10; i++){
            if(vaccineTable[i] != NULL && vaccineTableTime[i] == 0){
                for(j = 0; j < 1000; j++){
                    if(observationTable[j] == NULL){
                        observationTable[j] = vaccineTable[i];
                        vaccineTable[i] = NULL;
                        observationTime[j] = 30;
                        break;
                    }
                }
            }
        }

        for(i = 0; i <= 10; i++){
            if(vaccineTable[i] == NULL ) {
                if(!isEmpty(vaccineQ)) {
                    Patient *patient = (Patient*) malloc(sizeof(Patient));
                    dequeue(vaccineQ, patient);
                    vaccineTable[i] = patient;
                    vaccineTableTime[i] = 10;
                }
                else{
                    break;
                }
            }
        }
        //decrement observation time from 30 mins
        for(j = 0; j <= 30; j++){
            if(observationTable[j] != NULL)
                observationTime[j] -= 1;
        }
        //check if patients completed observation period and update time;
        for(j = 0; j <= 30; j++){
            if(observationTable[j] != NULL && observationTime[j] == 0){
                printf("Patient %d arrived at time %d and completed observation at time %d.\n",
                        observationTable[j]->patientID, observationTable[j]->arrivalTime, currentTime);
                observationTable[j] = NULL;
            }
        }
        currentTime ++;
    }
    fclose(fileIn);
    return 0;
}
