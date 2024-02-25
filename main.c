/* Include libraries*/
#include <Stdio.h>
#include "Lib/Std_Type.h"
#include "Lib/config.h"

/*define variables that used */ 
u8 Mode;
u8 counter = 0;
u8 Feature;
u8 check_id;
u8 check_slot_id;
u16 Password;
	
	
u8 patient_id;
u8 patient_age;
u8 patient_name[Name_Size];
u8 patient_gender[Gender_Size];
	
u8 slot_num;
u8 slot_time_not_reserved[Slot_Size][Slot_Time_Size] = {"2pm to 2:30pm","2:30pm to 3pm","3pm to 3:30pm","4pm to 4:30pm","4:30pm to 5pm"};
u8 slot_time_reserved[Slot_Size][Slot_Time_Size];
	
/* create head pointer to Slot struct and PatientNode struct */

PatientNode* Head_P = NULL;
Slot* Head_S = NULL ;

/*Define main function */

void main(void)
{
	/* print the welcome message and ask the user to choose between admin Mode or user Mode*/
	printf("-----------------------------..WELCOME IN CLINIC MANAGEMENT SYSTEM..^_^..-----------------------\n");
	printf("Please Choose from the following:\n");
	printf("For Admin Mode Enter----------> 1\n");
	printf("For User Mode Enter-----------> 2\n");
	printf("For Exit Entr-----------------> 0\n");
	printf("Please Enter Your Choice: ");
	scanf("%d",&Mode);
	/*check from the user entered */ 
	while ((Mode > User_Mode) && (Mode < Exit))
	{
		printf("Incorrect Choose, Please try agin: ");
		scanf("%d",&Mode);
	}
	/*---------------------------------------------------------------------------------
	                                           SUPER LOOP                        
	-----------------------------------------------------------------------------------*/										   
	while(TRUE)
	{
		if (Mode == Exit )
		{
			printf("-----------------..GOOD BYE..^_^..------------------");
			break;
		}
		else
		{
			/*---------------------------------------------------------------------------------------
											  ADMIN MODE
			-----------------------------------------------------------------------------------------*/
			if (Mode == Admin_Mode)
			{
				printf("-------------------------------\n");
				printf("  WELCOME IN ADMIN MODE..^_^  \n");
				printf("-------------------------------\n");
				/*               LOG IN                 */
				printf("Please Enter Your Password : ");
				scanf("%d",&Password);
				counter++;
				while ((Password != Admin_Password) && (counter < Number_Of_Try))
				{
					printf("Incorrect Password, Please try agin: ");
					scanf("%d",&Password);
					counter++;
				}
				/*               LOG IN FAILD                    */
				if((counter == Number_Of_Try) && (Password != Admin_Password))
				{
					printf("YOU ENTER PASSWORD INCORRECT 3 TIMES,SYSTEM WILL EXIT\nGOOD BYE ^_^");
					break;
				}
				/*                  LOG IN SUCCEED                 */
				else
				{
					while(TRUE)
					{
						printf("---------------------------------------------------------------------\n");
						printf("For Add New Patient Record Please Enter---------> 1\n");
						printf("For Edit Patient Record Please Enter------------> 2\n");
						printf("For Reserve A Slot With The Doctor Please Enter-> 3\n");
						printf("For Cancel Reservation Please Enter-------------> 4\n");
						printf("For Exit Or Change Mode Please Enter------------> 5\n");
						printf("---------------------------------------------------------------------\n");
						printf("Please Enter Your Choice : ");
						scanf("%d",&Feature);
						
						switch(Feature)
						{
							case 1:
								/*Add New Patient Record:   
								Func:Add_New_Patient(PatientNode ** head_ref, u8 name[], u8 age , u8 gender[] , u8 id);*/
								printf("-------------------------------------\n");
								printf("        ADD NEW PATIENT RECORD       \n");
								printf("-------------------------------------\n");
								/*       Get Patient Data from Admin          */
								printf("Please Enter Patient ID : ");
								scanf("%d",&patient_id);
								/* check id exist or not:
								func:u8 Check_Id(PatientNode** head_ref, u8 id);*/
								check_id = Check_Id(&Head_P,patient_id);
								while(check_id == Exist )
								{
									printf("ID is Exist please Enter another one : ");
									scanf("%d",&patient_id);
									check_id = Check_Id(&Head_P,patient_id);
								}
								printf("Please Enter Patient Name(No space): ");
								scanf("%s",patient_name);
								printf("Please Enter patient Age: ");
								scanf("%d",&patient_age);
								printf("Please Enter Patient Gender: ");
								scanf("%s",patient_gender);
								/*               Add Patient Record        */
								Add_New_Patient(&Head_P, patient_name, patient_age, patient_gender, patient_id);
								printf("-----------------ADDED-------------------\n");
								break;
								
							case 2:
								/* Edit Patient Record:
								func: Edit_Patient(PatientNode* head_ref , u8 id , u8 age , u8 name[] , u8 gender[]);*/
								printf("-----------------------------------------\n");
								printf("           EDIT PATIENT RECORD           \n");
								printf("-----------------------------------------\n");
								/*     Get patient id from admin and check it exist or Not For edit record         */
								printf("Please Enter Patient ID: ");
								scanf("%d",&patient_id);
								check_id = Check_Id(&Head_P , patient_id);
								if(check_id == Not_Exist)
								{
									printf("-------------INCORRECT ID-------------\n");
									break;
								}
								/* Get data from admin to change patient old record */
								printf("Please Enter Patient Name : ");
								scanf("%s",patient_name);
								printf("Please Enter Patient Age : ");
								scanf("%d",&patient_age);
								printf("Please Enter Patient Gender : ");
								scanf("%s",patient_gender);
								/* Put New data in old record  */
								Edit_Patient(Head_P , patient_id , patient_age , patient_name , patient_gender);
								printf("-------------------EDITED-------------------\n");
								break;
								
							case 3: 
								/*  Reserve A Slot:
								func:Reserve_Slot(Slot**head_ref , u8 id ,u8 slot_id, u8 slot_time[]); */
								printf("----------------------------------------------\n");
								printf("                 Reserve A Slot               \n");
								printf("----------------------------------------------\n");
								/* show the available slots to admin */
								printf("The Available Slots :  \n");
								for(counter = First_Index ; counter < Slot_Size ; counter++ )
								{
									if(slot_time_not_reserved[counter][First_Index] != Reserved)
									{
										printf("%d - %s\n",counter + Array_Factor, slot_time_not_reserved[counter]);
									}
								}
								/*Get Patient Id From admin and check it Exist or not for reserve a slot */
								printf("Please Enter Patient ID : ");
								scanf("%d",&patient_id);
								check_id = Check_Id(&Head_P , patient_id);
								check_slot_id = Check_Slot_Id(&Head_S , patient_id);
								if(check_id == Not_Exist)
								{
									printf("----------------INCORRECT PATIENT ID-------------\n");
									break;
								}
								/*check if the patient reserve or not*/
								if(check_slot_id == Exist)
								{
									printf("----------PATIEND ALREADY RSERVED SLOT-------------\n");
									break;
								}
								/* Get Slot Number from admin to reserve */
								printf("Please Enter Number Of Slot To Reserve : ");
								scanf("%d",&slot_num);
								/*check from user input*/
								if((slot_num > Slot_Size) || (slot_num < Array_Factor))
								{
									printf("------------INCORRECT CHOISE-------------\n");
									break;
								}
								/* reserve a slot */
								if (slot_time_not_reserved[slot_num - Array_Factor][First_Index] != Reserved)
								{
									Reserve_Slot(&Head_S , patient_id , slot_num , slot_time_not_reserved[slot_num - Array_Factor]);
									/* copy slot that reserved in slot_time_reserved array */
									for(counter = First_Index ; counter < Slot_Time_Size ; counter++)
									{
										slot_time_reserved[slot_num - Array_Factor][counter] = slot_time_not_reserved[slot_num - Array_Factor][counter];
									}
									/* set slot_time as reserved in slot_time_not_reserved */
									slot_time_not_reserved[slot_num - Array_Factor][First_Index] = Reserved;
									printf("-------------------SLOT RESERVATUION--------------------\n");
									break;
								}
								else
								{
									printf("-------------------INCORRECT CHOISE------------------------\n");
									break;
								}
								
							case 4:	
								/*Cancel Reservation:
								func:u8 Cancel_Reservation(Slot**head_ref , u8 id);*/
								printf("----------------------------------------------\n");
								printf("              CANCEL RESERVATION              \n");
								printf("----------------------------------------------\n");
								/* Get Patient Id to cancel reservation */
								printf("Please Enter Patient ID: ");
								scanf("%d",&patient_id);
								/* cancel reservation and get slot number */
								slot_num = Cancel_Reservation(&Head_S , patient_id);
								/*check Patient that has id reserved slot or not*/
								if(slot_num == Not_Found)
								{
									printf("------------------PATIENT NOT RESERVED ANY SLOT----------------------\n");
									break;
									
								}
								/*return slot time from slot_time_reserved in slot_time_not_reserved */
								for(counter = First_Index ; counter < Slot_Time_Size ; counter++)
								{
									slot_time_not_reserved[slot_num - Array_Factor][counter] = slot_time_reserved[slot_num - Array_Factor][counter];
								}
								printf("------------------RESERVATION CANCELED-------------------\n");
								break;
								
							case 5: 
								/* Exit Or Change Mode */
								printf("--------------------------------------\n");
								printf("          EXIT OR CHANGE MODE         \n");
								printf("--------------------------------------\n");
								printf("EXIT--------------------------> 0\n");
								printf("CHANGE MODE-------------------> 2\n");
								printf("Please Enter Your Choice: ");
								scanf("%d",&Mode);
								if ((Mode != Exit) ||(Mode != User_Mode))
								{
									printf("-----------INCORRECT CHOISE------------\n");
								}
								break;
							
							default:printf("----------------------INCORRECT CHOISE------------------------\n"); break;
						}
						if((Mode == Exit) || (Mode == User_Mode))
						{
							break;
						}
					}
				}
			}
			/*----------------------------------------------------------------------------------------------------
													   USER MODE
			-------------------------------------------------------------------------------------------------------*/
			else
			{
				printf("--------------------------------------------------------\n");
				printf("              WELCOME IN USER MODE..^_^                \n");
				printf("--------------------------------------------------------\n");
				
				while(TRUE)
				{
					printf("-----------------------------------------------------------------------\n");
					printf("For View Patient Record Please Enter-------------------> 1\n");
					printf("For View Today\'s Reservations Please Enter-------------> 2\n");
					printf("For Exit Or Change Mode Please Enter-------------------> 3\n");
					printf("-----------------------------------------------------------------------\n");
					printf("Please Enter Your Choice : ");
					scanf("%d",&Feature);
					switch(Feature)
					{
						case 1:
							/* View Patient Record:
							func:PrintPatientRecord(PatientNode* head_ref , u8 id);*/
							printf("-----------------------------------------\n");
							printf("               PATIENT RECORD            \n");
							printf("-----------------------------------------\n");
							printf("Please Enter Patient ID: ");
							scanf("%d",&patient_id);
							/* check from ID */
							check_id = Check_Id(&Head_P , patient_id);
							if(check_id == Not_Exist)
							{
								printf("-------------------INCORRECT ID--------------------\n");
								break;
							}
							/* print Patient Record */
							PrintPatientRecord(Head_P , patient_id);
							break;
							
						case 2: 
							/*View Today's Reservations:
							func: PrintTodayReservation(Slot* head_ref); */
							printf("--------------------------------------------------\n");
							printf("                 TODAY\'S RESERVATIONS            \n");
							printf("--------------------------------------------------\n");
							/*print reserved slots */
							PrintTodayReservation(Head_S);
							break;
							
						case 3:	
							/* Exit Or Change Mode */
							printf("--------------------------------------\n");
							printf("          EXIT OR CHANGE MODE         \n");
							printf("--------------------------------------\n");
							printf("EXIT--------------------------> 0\n");
							printf("CHANGE MODE-------------------> 1\n");
							printf("Please Enter Your Choice: ");
							scanf("%d",&Mode);
							if ((Mode != Exit) ||(Mode != Admin_Mode))
							{
								printf("-----------INCORRECT CHOISE------------\n");
							}
							break;
							
						default:printf("----------------------INCORRECT CHOISE------------------------\n"); break;	
					}
					if((Mode == Exit ) || (Mode == Admin_Mode))
					{
						break;
					}
				}
			}
		}		
	}
}
