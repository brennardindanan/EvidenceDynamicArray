#include <stdio.h>
#include <string.h>

#include "defs.h"

int main() {
	EvidenceType ev;
	int userChoice;
	
	EvidenceArray evArr;
    initEvidenceArray(&evArr, MAX_CAP);
    
    loadEvidenceData(&evArr);
	
	while (1) {
		printMenu(&userChoice);
		
		if (userChoice == 0) { //frees memory before exiting
			cleanupEvidenceArray(&evArr); 
			break;
		} else if (userChoice == 1) { //if user wishes to add evidence
			int id;
			char room[MAX_STR];
			char device[MAX_STR];
			int deviceCode;
			float value;
			int timestamp;
			int hours;
			int minutes;
			int seconds;
			char c;
	
		
			printf("Enter the evidence ID: ");
			scanf("%d", &id);
			while((c = getchar()) != '\n');
			
			printf("Enter the room name: ");
			fgets(room, MAX_STR, stdin);
			if (room[strlen(room) - 1] == '\n') {
				room[strlen(room) - 1] = '\0';
			}
			
			printf("Enter the device code [EMF: 1, THERMAL 2, SOUND: 3]: ");
			scanf("%d", &deviceCode);
			while((c = getchar()) != '\n');
			deviceCodeValidation(&deviceCode);
			if (deviceCode == 1) {
				strcpy(device, "EMF");
			} else if (deviceCode == 2) {
				strcpy(device, "THERMAL");
			} else if (deviceCode == 3) {
				strcpy(device, "SOUND");
			}
			
			printf("Enter the evidence value: ");
			scanf("%f", &value);
			while((c = getchar()) != '\n');
			
			printf("Enter the timestamp (Hours minutes seconds, space separated): ");
			scanf("%d %d %d", &hours, &minutes, &seconds);
			while((c = getchar()) != '\n');
            timestamp = convertToTimestamp(hours, minutes, seconds);
            
            initEvidence(id, room, device, value, timestamp, &ev);
			addEvidence(&evArr, &ev);
			printf("Your evidence with ID %d was successfully added!\n", id);
			
		} else if (userChoice == 2) { //if user wishes to delete evidence
			int evIdToDel; 
			char c;
			
			printf("Enter the evidence ID: ");
			scanf("%d", &evIdToDel);
			while((c = getchar()) != '\n');
			
			if (delEvidence(&evArr, evIdToDel) == ERROR_FLAG) {
				printf("Error: Failure to remove specified ID %d because ID %d does not exist.\n", evIdToDel, evIdToDel);
			} else {
				printf("Evidence deleted successfully.\n");
			}
			
		} else if (userChoice == 3) { //if user wishes to print the evidence collection
			printEvidenceArray(&evArr);
		} else { //if user does not input 1, 2, 3, or 0
			printf("Error. Please input a valid option.\n");
		}	
	}
  	return(0);
}

/* 
  Function: Print Menu
  Purpose:  Print the main menu and get the user's choice via user input
  Params:   
    Output: int* choice - the choice typed by the user
*/
void printMenu(int* choice)
{
  // NOTE: Do not make _any_ modifications to this function.
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

