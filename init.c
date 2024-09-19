#include "defs.h"

/*
void addEvidence(EvidenceArray* dest, EvidenceType* src) {
  // Empty function provided to avoid compiler warnings.
  // Remove these comments and remember to write your own code here
  // and to document this function with comments.
}
*/

void loadEvidenceData(EvidenceArray* arr)
{
  EvidenceType a;
  // Add sample evidence data
  // Evidence has an ID, room location, type (EMF/THERMAL/SOUND), value, and timestamp in seconds
  initEvidence(1000, "Living Room", "EMF", 4.869, 19554, &a);
  addEvidence(arr, &a);
  initEvidence(1001, "Nursery", "EMF", 2.08, 4260, &a);
  addEvidence(arr, &a);
  initEvidence(1002, "Nursery", "SOUND", 88.8, 4120, &a);
  addEvidence(arr, &a);
  initEvidence(1003, "Living Room", "EMF", 4.9, 17157, &a);
  addEvidence(arr, &a);
  initEvidence(1004, "Living Room", "SOUND", 35.154, 20970, &a);
  addEvidence(arr, &a);
  initEvidence(1005, "Bathroom", "THERMAL", 16.22806, 15936, &a);
  addEvidence(arr, &a);
  initEvidence(1006, "Kitchen", "EMF", 0.439, 609, &a);
  addEvidence(arr, &a);
  initEvidence(1007, "Kitchen", "THERMAL", 9.3643, 11797, &a);
  addEvidence(arr, &a);
  initEvidence(1008, "Bathroom", "EMF", 2.1254, 20166, &a);
  addEvidence(arr, &a);
  initEvidence(1009, "Living Room", "SOUND", 44.8, 12701, &a);
  addEvidence(arr, &a);
  initEvidence(1010, "Dining Room", "EMF", 3.871087, 17593, &a);
  addEvidence(arr, &a);
  initEvidence(1011, "Main Bedroom", "SOUND", 79.0739, 2862, &a);
  addEvidence(arr, &a);
  initEvidence(1012, "Bathroom", "THERMAL", 10.649717, 9292, &a);
  addEvidence(arr, &a);
  initEvidence(1013, "Living Room", "EMF", 4.142, 8384, &a);
  addEvidence(arr, &a);
  initEvidence(1014, "Nursery", "THERMAL", -8.2, 328, &a);
  addEvidence(arr, &a);
  initEvidence(1015, "Dining Room", "SOUND", 49.9, 20757, &a);
  addEvidence(arr, &a);
  initEvidence(1016, "Living Room", "THERMAL", 3.4364, 16043, &a);
  addEvidence(arr, &a);
  initEvidence(1017, "Dining Room", "THERMAL", -1.462089, 14241, &a);
  addEvidence(arr, &a);
  initEvidence(1018, "Living Room", "EMF", 3.484842, 6222, &a);
  addEvidence(arr, &a);
  initEvidence(1019, "Living Room", "EMF", 2.87804, 15926, &a);
  addEvidence(arr, &a);
  initEvidence(1020, "Living Room", "EMF", 4.782, 19880, &a);
  addEvidence(arr, &a);
  initEvidence(1021, "Nursery", "THERMAL", -6.9681, 2905, &a);
  addEvidence(arr, &a);

}

/* 
  Function: initEvidence
  Purpose:  Initializes an EvidenceType structure
  Params:   
	In:
		id - identification number for evidence
		room - description of room that contained evidence
		device - description of device used to gather evidence 
		timestamp - time evidence collected
	Out:
		dest - initialized EvidenceType
*/
void initEvidence(int id, char* room, char* device, float value, int timestamp, EvidenceType* dest) {
	dest->id = id; //sets EvidenceType id to passed id
	strncpy(dest->room, room, MAX_STR - 1); //sets EvidenceType room to passed room
	dest->room[MAX_STR - 1] = '\0'; //ensures null termination
	strncpy(dest->device, device, MAX_STR - 1); //sets EvidenceType device to passed device
	dest->device[MAX_STR - 1] = '\0'; //ensures null termination
	dest->value = value; //sets EvidenceType value to passed value
	dest->timestamp = timestamp; //sets EvidenceType timestamp to passed timestamp
}

/* 
  Function: initEvidenceArray
  Purpose:  Initializes an EvidenceArray structure
  Params:   
  	In:
  		cap - desired capacity
	Out:
		evArr - initialized EvidenceArray	
*/
void initEvidenceArray(EvidenceArray* evArr, int cap) {
	evArr->capacity = cap; //sets EvidenceArray capacity from the passed cap
	evArr->size = 0; //sets EvidenceArray to 0
	
	//Performs dynamic memory allocation to fit the capacity size and checks for successful malloc
	evArr->elements = (EvidenceType*) malloc(cap * sizeof(EvidenceType));
	if (evArr->elements == NULL) {
       printf("Memory allocation error.\n");
       exit(1);  
    }
}




















