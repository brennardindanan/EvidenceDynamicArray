#include "defs.h"

/* 
  Function:  printEvidence
  Purpose:  To print a single line of evidence containing all info on all elements of the EvidenceType structure
  Params:   
	In: ev - pointer to the EvidenceType structure
*/
void printEvidence(EvidenceType* ev) {
	printf("%-4d | %8s%16s | %8s | ", ev->id, " ", ev->room, ev->device);
	
	if (strcmp(ev->device, "EMF") == 0) {
        if (ev->value > 4.0) {
            printf("%9.1f %6s", ev->value, "(HIGH)");
        } else {
            printf("%16.1f", ev->value);
        } 
    } else if (strcmp(ev->device, "THERMAL") == 0) {
        if (ev->value < 0.0) {
            printf("%9.2f %6s", ev->value, "(COLD)");
        } else {
            printf("%16.2f", ev->value);
        }
    } else if (strcmp(ev->device, "SOUND") == 0) {
        if (ev->value < 35.0) {
            printf("%7.1f %9s", ev->value, "(WHISPER)");
        } else if (ev->value > 70.0) {
            printf("%7.1f %8s", ev->value, "(SCREAM)");
        } else {
            printf("%16.1f", ev->value);
        }
    }
	
	printf(" | ");
	
	int hours = ev->timestamp / SECS_IN_HR;
    int minutes = (ev->timestamp % SECS_IN_HR) / SECS_IN_MIN;
    int seconds = ev->timestamp % SECS_IN_MIN;
    
    printf("%02d:%02d:%02d\n", hours, minutes, seconds);
}

/* 
  Function: deviceCodeValidation
  Purpose:  To check whether a passed device code is valid (1-3)
  Params:   
  	In:
  		deviceCode - deviceCode to be checked if it is 1-3
*/
void deviceCodeValidation (int* deviceCode) {
	char c;
	while (*deviceCode != 1 && *deviceCode != 2 && *deviceCode != 3) {
		printf("Your device code is invalid. Please select 1 for EMF, 2 for THERMAL, or 3 for SOUND: ");
		scanf("%d", deviceCode);
		while((c = getchar()) != '\n');
	}
}

/* 
  Function: convertToTimestamp
  Purpose:  Takes hours, minutes, and seconds, and converts what is given into a timestamp, in seconds
  Params:   
  	In:
  		hours - number of hours of a given duration
  		minutes - number of minutes of a given duration
  		seconds - number of seconds of a given duration
  Return: The converted timestamp, in seconds.

*/
int convertToTimestamp(int hours, int minutes, int seconds) {
	int timestamp = hours * SECS_IN_HR + minutes * SECS_IN_MIN + seconds;
	return timestamp;
}

/* 
  Function: copyEvidence
  Purpose:  Performs deep copy of evidence found in src into dest 
  Params:   
  	In:
  		src - a pointer to the EvidenceType structure to be copied
	In/Out:
		dest - a pointer to the EvidenceType structure where src will be copied to
*/
void copyEvidence(EvidenceType* dest, EvidenceType* src) {
	initEvidence(src->id, src->room, src->device, src->value, src->timestamp, dest);
}

/* 
  Function: growEvidenceArray
  Purpose:  Doubles the capacity of the passed EvidenceArray by resizing dynamically.
  Params:   
  	In/Out: evArr - a pointer to the EvidenceArray structure that will be dynamically resized. 	
*/
void growEvidenceArray(EvidenceArray* evArr) {
	EvidenceType* tempEvArr = (EvidenceType*) malloc((2*evArr->capacity) * sizeof(EvidenceType));
	if (evArr->elements == NULL) {
       printf("Memory allocation error.\n");
       exit(1);  
    }
    
    for (int i = 0; i < evArr->size; i++) {
    	copyEvidence(&tempEvArr[i], &evArr->elements[i]);
    }
    
    free(evArr->elements);
    evArr->elements = tempEvArr;
    evArr->capacity = 2*evArr->capacity;
}

/* 
  Function: addEvidence
  Purpose:  To add an EvidenceType structure and all its elements into the evidence collection, an EvidenceArray structure. Will insert into the EvidenceArray based on room name in descending order, and if equal, than by timestamp in ascending order.
  Params:   
	In:
		src - pointer to the EvidenceType structure with all elements to be added
	In/Out:
		dest - pointer to the EvidenceArray structure where the new EvidenceType structure will all its elements will be added
*/
void addEvidence(EvidenceArray* dest, EvidenceType* src) {
	if (dest->size >= dest->capacity) {
		growEvidenceArray(dest);
	}
	
	int insertionPoint = dest->size;
	for (int i = 0; i < dest->size; i++) {
		if (strcmp(src->room, dest->elements[i].room) > 0) { //if greater than 0, meaning the first string comes before the second string
			insertionPoint = i; //insert here for descending alphabetical order
			break;
		} else if (strcmp(src->room, dest->elements[i].room) == 0) { //if alphabetically equal
			if (src->timestamp < dest->elements[i].timestamp) { //sort by ascending timestamp order
				insertionPoint = i;
				break;
			}
		}
	}
	
	for (int i = dest->size; i > insertionPoint; i--) { //shifts elements to the right to make space at the insertion point
		copyEvidence(&dest->elements[i], &dest->elements[i-1]);
	}
	
	copyEvidence(&dest->elements[insertionPoint], src);
	dest->size++;
	
}

/* 
  Function: delEvidence
  Purpose:  To take a room ID desired to be deleted, and remove the corresponding EvidenceType structure from its place in the EvidenceArray structure without any gaps
  Params:   
	In:
		id - the identification number of the EvidenceType to be deleted
	In/Out:
		src - pointer to the EvidenceArray structure where the passed id will be removed, and no gaps will be left.
*/
int delEvidence(EvidenceArray* src, int id) {
	int removalPoint = -1; //set to -1 because 0 is the starting index, code didn't work when set to 0
	for (int i = 0; i < src->size; i++) {
		if (src->elements[i].id == id) { //if id to be removed is found
			removalPoint = i;
			break;
		}
	}
	
	if (removalPoint == -1) {
		return ERROR_FLAG;
	} else { 
		for (int i = removalPoint; i < src->size - 1; i++) { //shifts elements to the right to "overwrite" (delete) desired element
			copyEvidence(&src->elements[i], &src->elements[i + 1]);
		}
		
		src->size--;
	}
	
	return SUCCESS_FLAG;
}

/* 
  Function: printEvidenceArray
  Purpose:  Prints the entire evidence collection, with each individual EvidenceType structure and all the corresponding elements, in an organized and readable table.
  Params:   
	In:
		evArr - pointer to the EvidenceArray structure to be printed
*/
void printEvidenceArray(EvidenceArray* evArr) {
	printf("%4s | %8s%16s | %8s | %16s | %-10s\n", "ID", " ", "Room", "Device", "Value", "Timestamp");
	
	for (int i = 0; i < evArr->size; i++) {
		printEvidence(&evArr->elements[i]);
	}
}

/* 
  Function: cleanupEvidenceArray
  Purpose:  Releases the dynamically allocated memory and sets size and capacity of the passed EvidenceArray structure to 0
  Params:  
  	In/Out: 
  		evArr - pointer to the EvidenceArray structure in which the elements pointer will be null

*/
void cleanupEvidenceArray(EvidenceArray* evArr) {
	free(evArr->elements);
	evArr->size = 0;
	evArr->capacity = 0;
}






















