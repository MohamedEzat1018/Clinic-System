/*include libraries */
#include <stdio.h>
#include <stdlib.h>
#include "Lib/Std_Type.h"
#include "Lib/config.h"

/*define counter variable*/
u8 counter ;

void Add_New_Patient(PatientNode ** head_ref, u8 name[], u8 age , u8 gender[] , u8 id)
{
	/* create copy of head pointer */
	PatientNode* Last = *head_ref;
	/* create new patient node*/
	PatientNode* New_PatientNode = (PatientNode*)malloc(sizeof(PatientNode));
	/* put data in new patient node */
	New_PatientNode -> ID = id;
	New_PatientNode -> Age = age;
	for(counter = First_Index ; counter < Name_Size ; counter++)
	{
		New_PatientNode -> Name[counter] = name[counter];
	}
	for(counter = First_Index ; counter < Gender_Size ; counter++)
	{
		New_PatientNode -> Gender[counter] = gender[counter];
	}
	/* make next pointers to Null*/
	New_PatientNode -> Next = NULL;
	/* check the list empty or not*/
	if(*head_ref == NULL)
	{
		/* make head points to New_PatientNode */
		*head_ref = New_PatientNode;
		return;
	}
	else
	{
		/* make Last PatientNode points to New_PatientNode*/
		while(Last -> Next != NULL)
		{
			Last = Last -> Next;
		}
		Last -> Next = New_PatientNode;
		return;
	}
}

u8 Check_Id(PatientNode** head_ref, u8 id)
{
	/*create copy of head pointer */
	PatientNode* last = *head_ref;
	/*check if list is empty */
	if (*head_ref == NULL)
	{
		return Not_Exist;
	}
	else
	{
		while(last -> ID != id)
		{
			last = last -> Next;
			if (last == NULL)
			{
				return Not_Exist ;
			}
		}
		return Exist;
	}
}

void Edit_Patient(PatientNode* head_ref , u8 id , u8 age , u8 name[] , u8 gender[])
{
	/* search about PatientNode that has entered id */
	while(head_ref -> ID != id)
	{
		head_ref = head_ref -> Next;
	}
	/* put new data in searching PatientNode */
	for (counter = First_Index ; counter < Name_Size ; counter++)
	{
		head_ref -> Name[counter] = name[counter];
	}
	for (counter = First_Index ; counter < Gender_Size ; counter++ )
	{
		head_ref -> Gender[counter] = gender[counter];
	}
	head_ref -> Age = age;
	
	return;
}

void Reserve_Slot(Slot**head_ref , u8 id ,u8 slot_num, u8 slot_time[])
{
	/* create copy from head pointer to move on slot list*/
	Slot* last = *head_ref;
	/* create new Slot Node*/
	Slot* New_Slot = (Slot*)malloc(sizeof(Slot));
	/*put data in new slot node*/
	New_Slot -> ID = id;
	New_Slot -> Slot_Number = slot_num;
	for(counter = First_Index ; counter < Slot_Time_Size; counter++)
	{
		New_Slot -> Slot_Time[counter] = slot_time[counter];
	}
	New_Slot -> Next = NULL;
	/* check from list(empty or not)*/
	if(*head_ref == NULL)
	{
		/*make head pointers to New_Slot Node*/
		*head_ref = New_Slot;
		return;
	}
	else
	{
		while(last -> Next != NULL)
		{
			last = last -> Next;
		}
		/*make the last node from list pointers to new slot node */
		last -> Next = New_Slot;
		return;
	}
}

u8 Check_Slot_Id(Slot** head_ref, u8 id)
{
	/*create copy of head pointer */
	Slot* last = *head_ref;
	/*check if list is empty */
	if (*head_ref == NULL)
	{
		return Not_Exist;
	}
	else
	{
		while(last -> ID != id)
		{
			last = last -> Next;
			if (last == NULL)
			{
				return Not_Exist ;
			}
		}
		return Exist;
	}
}

u8 Cancel_Reservation(Slot**head_ref , u8 id)
{
	/*create variable to hold slot id*/
	u8 slot_num;
	/* create copy from head pointer to move in slot list*/
	Slot* delete_slot = *head_ref;
	Slot* after_delete = NULL;
	Slot* before_delete = *head_ref;
	/* searching about slot that has id */
	/*case 1: if the list is empty */
	if(delete_slot == NULL)
	{
		return Empty_List;
	}
	/*case 2: if the list not empty*/
	while(delete_slot -> ID != id)
	{
		if(delete_slot -> Next == NULL)
		{
			return Not_Found;
		}
		delete_slot = delete_slot -> Next;
	}
	/* cancel reservation case 1 : if the Slot list contain one Node*/
	if ((before_delete -> Next == NULL) || (before_delete == delete_slot))
	{
		slot_num = delete_slot -> Slot_Number;
		*head_ref = delete_slot-> Next;
		free(delete_slot);
		return slot_num;
	}
	/*cancel reservation case 2: if the Slot list contain more than one Node*/
	/*make after delete_slot pointers to node after deleted node*/
	after_delete = delete_slot -> Next;
	/*search about node before node deleted*/
	while(before_delete -> Next != delete_slot)
	{
		before_delete = before_delete -> Next;
	}
	/*make before_delete pointers to after_delete node*/
	before_delete -> Next = after_delete;
	/*put deleted slot_id in slot_id */
	slot_num = delete_slot -> Slot_Number;
	/*delete the slot node and return slot_id */
	free(delete_slot);
	return slot_num;
}

void PrintPatientRecord(PatientNode* head_ref , u8 id)
{
	/*searching about id in the patient node list*/
	while(head_ref -> ID != id)
	{
		head_ref = head_ref -> Next;
	}
	/*print the patient record data*/
	printf("Patient Name   : %s\n",head_ref -> Name);
	printf("Patient Age    : %d\n",head_ref -> Age);
	printf("Patient Gender : %s\n",head_ref -> Gender);
	
	return;
}

void PrintTodayReservation(Slot* head_ref)
{
	/*check from Slot list */
	if (head_ref == NULL)
	{
		printf("--------------------------NO RESERVATION YET--------------------\n");
		return;
	}
	/*print all reservation slots */
	while(head_ref != NULL)
	{
		printf("Slot Time : %s    is reserve for Patient ID :  %d\n",head_ref -> Slot_Time , head_ref -> ID);
		head_ref = head_ref -> Next;
	}
	return;
	
}