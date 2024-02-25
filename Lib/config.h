#ifndef CONFIG_H
#define CONFIG_H

/* Macros */
#define Name_Size       30
#define Gender_Size     10

#define Slot_Size       5
#define Slot_Time_Size  30
#define Reserved        0

#define Not_Exist       0
#define Exist           1

#define First_Index     0
#define Array_Factor    1

#define Not_Found       0
#define Empty_List      0

#define TRUE            1
#define FALSE           0

#define Exit            0
#define Admin_Mode      1
#define User_Mode       2

#define Admin_Password  1234
#define Number_Of_Try   3


/* struct */

typedef struct PatientNode  PatientNode;
typedef struct SlotNode     Slot;         

struct PatientNode{
	u8 Name[Name_Size];
	u8 Gender[Gender_Size];
	u8 Age;
	u8 ID;
	PatientNode* Next;
};

struct SlotNode {
	u8 ID;
	u8 Slot_Number;
	u8 Slot_Time[Slot_Time_Size];
	Slot* Next;
};

/*Function Prototype*/
void Add_New_Patient(PatientNode ** head_ref, u8 name[], u8 age , u8 gender[] , u8 id);
u8 Check_Id(PatientNode** head_ref, u8 id);
void Edit_Patient(PatientNode* head_ref , u8 id , u8 age , u8 name[] , u8 gender[]);
void Reserve_Slot(Slot**head_ref , u8 id ,u8 slot_id, u8 slot_time[]);
u8 Check_Slot_Id(Slot** head_ref, u8 id);
u8 Cancel_Reservation(Slot**head_ref , u8 id);
void PrintPatientRecord(PatientNode* head_ref , u8 id);
void PrintTodayReservation(Slot* head_ref);



#endif










