#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<Windows.h>
#include<time.h>
#pragma warning (disable:4996)

SYSTEMTIME t;
void intro();
void login();
int cmpPassword();
void upper_string(char*);

// kah hou
void add();
void search();
void modify();
void display(int);
void deleteStaff();
void staffMain();
struct StaffInfo {
	char id[6], frtname[15], lstname[15];
	int passw;
	char pst[25];
	int age;
	double slry;
	char adres[67];
} staff;
//


//alvin
//Requirement function
int displayChoice(); void addBooking(); void displayCurBooking();
void modifyBooking(); void searchBookDtl(); void cancelFunc(); void refreshDateFunc(); void bookingMain();
//Validation Function
int validTime(int, int, int, int); int validFacilityCode(char); int validDate(int);
//Display purpose
void headingDate(int plus, char place[]);
void subDisplayCurBooking(char type, char place[]);
void subBodyDcb(char id[6], char type, int court, int timeInHrs, int timeInMin, int timeOutHrs, int timeOutMin, char memId[6], int hrs, int min, int day, int month);
void infoCodeOfSport(); void displayDate(int);
//Collect facility info to display
void searchDisplayFac(char searchCode[4], char court[4], char type[30], char searchDescript[30], char searchVenue[30], char id[4]);
typedef struct {
	int day, month, year;
}DateBooking;
typedef struct {
	char memId[6], id[6], type;
	int court;
	int dateChoice;
	int timeInHrs, timeOutHrs, timeInMin, timeOutMin, hrs, min;
	DateBooking d;
}Booking;
//


// yiyang
void addFacility();
void searchFacility();
void modifyFacility();
void displayFacility();
void deleteFacility();
void backupFacility();
void facilityMain();
struct Facility { char facilityCode[4], facilityType[20], facilityDescript[20], facilityVenue[30]; int facilityMin, facilityMax; };
//


//weng ni
void addMember();
void searchMember();
void modifyMember();
void displayAll(int stop);
void deleteMember();
void sortMember();
void memberMain();
struct Date { int day, month, year; };
struct Member { char memberId[6], name[40], gender, IC[15], contactNum[15]; struct Date DOB; } members;
FILE* fPtr;
//

void bodyDisplyCurBooking(Booking b[], int c, int num, char ch);
void searchBookFacility(char type, char ch, int court, int num, struct Facility search[], int fCount, char FacilityId[4]);


main() {



	intro();
	login();

	int option;
	do {
		system("cls");
		printf("Main\n");
		printf("====\n");
		printf("1. Staff information\n");
		printf("2. Member information\n");
		printf("3. Facility informaton\n");
		printf("4. Booking system\n");
		printf("0. Exit\n");

		printf("Select an option : ");
		rewind(stdin);
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			staffMain();
			break;
		case 2:
			memberMain();
			break;
		case 3:
			facilityMain();
			break;
		case 4:
			bookingMain();
			break;
		case 0:
			printf("Thank you and see you soon\n");
			break;
		default:
			printf("Invalid number\n");
			printf("Press any key to select your option again..........");
			getch();
		}

	} while (option != 0);

}
void intro() {

	time_t t;
	time(&t);

	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t%s", ctime(&t));
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxx(       Welcome to Our System        )xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

}
void login() {
	char readId[6];
	int readPassw;
	int sCount = 0;
	int password, staffId;
	int j, check, reRead;
	struct StaffInfo staff[100];

	FILE* information;
	information = fopen("Info.bin", "rb");

	while (fread(&staff[sCount], sizeof(staff[sCount]), 1, information) != 0)
	{
		sCount++;
	}
	fclose(information);

	if (information == NULL)
	{
		printf("Unable to open File.");
		exit(-1);
	}

	printf("\t\t\t\t\t\t\tEnter Staff ID : ");
	rewind(stdin);
	scanf("%s", readId);
	upper_string(readId);

	printf("\t\t\t\t\t\t\tEnter password : ");
	rewind(stdin);
	scanf("%d", &readPassw);
	for (int i = 0; i < sCount; i++) {
		password = cmpPassword(readPassw, staff[i].passw);
		staffId = strcmp(readId, staff[i].id);
		if (staffId == 0 && password == 1) {
			check = i;
			break;
		}
		else {
			check = 101;
		}

	}
	password = cmpPassword(readPassw, staff[check].passw);
	staffId = strcmp(readId, staff[check].id);

	if (staffId == 0 && password == 1) {

		printf("\n\n\t\t\t\t\t\t\tLogin Succesfully\n");
		printf("\t\t\t\t\t\t\tPress any key to continue ....... ");
		getch();

	}
	else {
		reRead = 0; j = reRead;
		do {

			if (j == reRead) {
				system("cls");
				intro();
				printf("\t\t\t\t\t\t\tRe-enter staff ID : ");
				rewind(stdin);
				scanf("%s", readId);
				upper_string(readId);

				printf("\t\t\t\t\t\t\tRe-enter password : ");
				rewind(stdin);
				scanf("%d", &readPassw);
				j = sCount; reRead = 0;
			}
			staffId = strcmp(readId, staff[reRead].id);
			password = cmpPassword(readPassw, staff[reRead].passw);
			reRead++;
		} while (staffId != 0 || password != 1);

		printf("\n\n\t\t\t\t\t\t\tLogin Succesfully\n");
		printf("\t\t\t\t\t\t\tPress any key to continue ....... ");
		getch();
	}

}
int cmpPassword(int input, int actual) {

	if (input == actual) {
		return 1;
	}
	else
		return 0;

}
void upper_string(char* string)
{
	while (*string)
	{
		if (*string >= 'a' && *string <= 'z')
		{
			*string = *string - 32;
		}
		string++;
	}
}

// kah hou
void staffMain() {


	int choice;
	do {
		system("cls");

		printf("\t\t\tSTAFF INFORMATION SYSTEM\n");
		printf("\n===================================================================\n");
		printf("-----1. Add Staff Information\n");
		printf("-----2. Search Staff Information\n");
		printf("-----3. Modify Staff Information\n");
		printf("-----4. Display Staff Information\n");
		printf("-----5. Delete Staff Information\n");
		printf("-----6. Exit\n");
		printf("===================================================================\n");
		printf("Select your choice : ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			add();
			break;
		case 2:
			search();
			break;
		case 3:
			modify();
			break;
		case 4:
			display(1);
			break;
		case 5:
			deleteStaff();
			break;
		case 6:
			break;
		default:
			printf("Invalid number!\n");
			printf("Press any key to select your choice again...........");
			getch();
		}


	} while (choice != 6);



}
void add() {

	struct StaffInfo staff;

	int x, count = 0;
	char ent;

	FILE* information;

	do {

		system("cls");
		printf("Add Staff record\n");
		printf("=========\n\n");

		printf("Enter your staff ID : ");
		rewind(stdin);
		scanf("%[^\n]", &staff.id);
		upper_string(staff.id);



		printf("Enter your First Name : ");
		rewind(stdin);
		scanf("%[^\n]", &staff.frtname);



		printf("Enter your Last Name : ");
		rewind(stdin);
		scanf("%[^\n]", &staff.lstname);
		rewind(stdin);

		printf("Enter your password : ");
		rewind(stdin);
		scanf("%d", &staff.passw);


		printf("Enter your position : ");
		rewind(stdin);
		scanf("%[^\n]", &staff.pst);


		printf("Enter your age : ");
		rewind(stdin);
		scanf("%d", &staff.age);


		printf("Enter your Salary :");
		rewind(stdin);
		scanf("%lf", &staff.slry);


		printf("Enter your Address : ");
		rewind(stdin);
		scanf("%[^\n]", &staff.adres);



		information = fopen("Info.bin", "ab");

		if (!information) {
			printf("cannnot open this file");
			exit(-1);
		}

		fwrite(&staff, sizeof(staff), 1, information);
		fclose(information);
		printf("Add new staff record succesfully\n\n");
		printf("Press enter to comfirm add staff Info or enter 0 to stop system :");
		rewind(stdin);
		scanf("%c", &ent);

	} while (ent != '0');


}
void search() {

	struct StaffInfo staff[100];

	FILE* information;
	information = fopen("Info.bin", "rb");

	if (information == NULL)
	{
		printf("Unable to open File.");
		exit(-1);
	}

	int i = 0, currentRecords = 0, x = 0;
	char search[6], ent;
	int status;

	while (fread(&staff[i], sizeof(staff[i]), 1, information) != 0)
	{
		i++;
		currentRecords++;
	}
	fclose(information);
	do {
		status = 0;
		system("cls");
		printf("Search\n");
		printf("=======\n\n");

		printf("Enter staff ID to search: ");
		rewind(stdin);
		scanf("%s", search);


		for (int i = 0; i < currentRecords; i++)
		{
			if (strcmp(search, staff[i].id) == 0)
			{

				printf("Name              : %s ", staff[i].frtname);
				printf("%s\n", staff[i].lstname);
				printf("Password          : %d\n", staff[i].passw);
				printf("Position          : %s\n", staff[i].pst);
				printf("Age               : %d\n", staff[i].age);
				printf("Salary            : %.2f\n", staff[i].slry);
				printf("Address           : %s", staff[i].adres);
				printf("\n");


			}
			else
				status++;
		}

		if (status == currentRecords)
			printf("Invalid staff ID....\n");

		printf("\n(Enter to continue searching)(x to exit):");
		rewind(stdin);
		scanf("%c", &ent);

	} while (ent != 'x');

}
void modify() {

	struct StaffInfo staff[100];

	FILE* information;
	information = fopen("Info.bin", "rb");

	if (!information)
	{
		printf("Unable to open File.");
		exit(-1);
	}


	int record = 0, i = 0, status = 0;
	char ent;
	char id[6];


	while (fread(&staff[i], sizeof(staff[i]), 1, information) != 0)
	{
		i++;
		record++;
	}

	fclose(information);

	do {
		status = 0;
		system("cls");
		display(0);
		printf("Modify staff info\n");
		printf("=================\n\n");

		printf("Enter Staff ID to modify: ");
		rewind(stdin);
		scanf("%s", &id);


		for (int i = 0; i < record; i++)
		{
			if (strcmp(id, &staff[i].id) == 0)
			{


				printf("\n");
				printf("Enter New staff ID : ");
				rewind(stdin);
				scanf("%s", &staff[i].id);


				printf("\n");
				printf("Enter First Name : ");
				rewind(stdin);
				scanf("%[^\n]", &staff[i].frtname);


				printf("\n");
				printf("Enter Last Name :");
				rewind(stdin);
				scanf("%[^\n]", staff[i].lstname);

				printf("\n");
				printf("Enter New password : ");
				rewind(stdin);
				scanf("%d", &staff[i].passw);


				printf("\n");
				printf("Enter  New Position: ");
				rewind(stdin);
				scanf("%s", &staff[i].pst);


				printf("\n");
				printf("Enter your New Age : ");
				rewind(stdin);
				scanf("%d", &staff[i].age);


				printf("\n");
				printf("ENter New Salary : ");
				rewind(stdin);
				scanf("%f", &staff[i].slry);


				printf("\n");
				printf("Enter New Address : ");
				rewind(stdin);
				scanf("[^\n]", staff[i].adres);

				information = fopen("Info.bin", "wb");

				if (!information)
				{
					printf("Unable to open File.");
					exit(-1);
				}
				for (int i = 0; i < record; i++)
				{
					fwrite(&staff[i], sizeof(staff[i]), 1, information);
				}
				fclose(information);
				printf("\n");
				printf("!! Modify successful !!\n");
			}
			else
			{
				status++;
			}
		}

		if (status == record)
			printf("Invalid staff ID .......\n\n");


		printf("(Enter to continue modify)(x to exit):\n");
		rewind(stdin);
		scanf("%c", &ent);

	} while (ent != 'x');

}
void display(int stop) {

	struct StaffInfo staff;
	FILE* information;
	information = fopen("Info.bin", "rb");

	int i = 0;
	system("cls");
	printf("\n");
	printf("\n============================================\n");
	printf("        DISPLAY All Information                  ");
	printf("\n============================================\n");
	printf("\n");

	printf("Staff ID  Name      \t\tPassword      \t\tPosition      \tAge      Salary           Address\n");
	printf("============================================================================================================================================\n");
	while (fread(&staff, sizeof(staff), 1, information) != 0)
	{
		printf("%-7s\t", staff.id);
		printf(" %-s ", staff.frtname);
		printf("%-14s", staff.lstname);
		printf("\t%-4d", staff.passw);
		printf("\t%24s", staff.pst);
		printf("\t%2d", staff.age);
		printf("\t%.2lf", staff.slry);
		printf("\t\t%s\n", staff.adres);
		i++;
	}

	fclose(information);
	printf("============================================================================================================================================\n");




	if (stop == 1) {
		printf("\nPress any key to back.......");
		getch();
	}

}
void deleteStaff() {

	struct StaffInfo staff[100];

	int sCount;
	int status;
	char id[6];
	char ent;
	FILE* information;


	do {
		sCount = 0;
		information = fopen("Info.bin", "rb");

		if (!information) {
			printf("unable to open file.");
			exit(-1);
		}

		while (fread(&staff[sCount], sizeof(staff[sCount]), 1, information) != 0)
		{
			sCount++;
		}

		fclose(information);
		status = 0;
		system("cls");
		display(0);
		printf("\n\nDelete staff record%d\n", sCount);
		printf("===================\n");
		printf("\n");
		printf("Enter staff ID to delete: ");
		rewind(stdin);
		scanf("%s", id);

		for (int j = 0; j < sCount; j++) {
			if (strcmp(id, staff[j].id) == 0) {
				printf("\n");
				printf("are you sure you want to delete?(y = yes/n = no): ");
				rewind(stdin);
				scanf("%c", &ent);

				if (ent == 'y') {

					for (int i = j; i < sCount; i++) {

						staff[i] = staff[i + 1];
					}
					sCount--;
					printf("%d\n", sCount);

					information = fopen("Info.bin", "wb");

					if (!information) {
						printf("unable to open file.\n");
						exit(-1);
					}

					for (int update = 0; update < sCount; update++) {
						fwrite(&staff[update], sizeof(staff[update]), 1, information);
					}
					fclose(information);
					sCount++;
					printf("\n");
					printf("Delete successful !!\n");
				}
				else
					printf("Delete unsuccessfully !! \n");


			}
			else
				status++;

		}

		if (status == sCount)
			printf("Invalid staff ID\n");

		printf("(Enter to continue delete)(x to exit):\n");
		rewind(stdin);
		scanf("%c", &ent);

	} while (ent != 'x');

}
//

//Alvin
void bookingMain() {
	int choice;

	do {

		system("cls");

		choice = displayChoice();

		switch (choice) {
		case 1:
			addBooking();
			break;
		case 2:
			displayCurBooking();
			break;
		case 3:
			modifyBooking();
			break;
		case 4:
			searchBookDtl();
			break;
		case 5:
			cancelFunc();
			break;
		case 6:
			refreshDateFunc();
			break;
		case 0:
			break;
		default:
			printf("Invalid number\n");
		}
	} while (choice != 0);


}
int displayChoice() {
	int choice;
	printf("Booking system \n");
	printf("=======+======\n");
	printf("1. New booking\n");
	printf("2. Display current booking\n");
	printf("3. Modify booking info\n");
	printf("4. Search booking details\n");
	printf("5. Cancel booking\n");
	printf("6. Refresh Date\n");
	printf("0. Exit\n");

	printf("Select your choice :");
	rewind(stdin);
	scanf("%d", &choice);

	return choice;
}
void addBooking() {

	GetLocalTime(&t);
	typedef struct {
		char memId[6];
		int id;
		char type;
		int court;
		int dateChoice;
		int timeInHrs, timeOutHrs, timeInMin, timeOutMin, hrs, min;
		DateBooking d;
	}Booking;

	int bookId = 1000;
	char comfirmAns, inputMemId[6];
	int c = 0;
	int notFound = 0;
	Booking b;
	struct Member p[20];
	Booking bCpy[45];

	FILE* memFile;
	memFile = fopen("member.bin", "rb");
	if (memFile == NULL) {
		printf("Failed to open file");
		exit(-6);
	}

	int mCount = 0, numRecords = 0;
	while (fread(&p[mCount], sizeof(members), 1, memFile) != 0) {
		numRecords++;
		mCount++;
	}
	fclose(memFile);

	FILE* fptr;
	fptr = fopen("bookDt.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}

	int i = 0;
	while (!feof(fptr)) {
		fscanf(fptr, "%[^,],B%d,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[i].memId, &bCpy[i].id, &bCpy[i].type, &bCpy[i].court, &bCpy[i].dateChoice, &bCpy[i].timeInHrs, &bCpy[i].timeInMin, &bCpy[i].timeOutHrs, &bCpy[i].timeOutMin, &bCpy[i].hrs, &bCpy[i].min, &bCpy[i].d.day, &bCpy[i].d.month);
		i++;
	}
	fclose(fptr);


	do {
		system("cls");
		printf("New Booking\n");
		printf("===========\n");
		notFound = 0;
		if (c == 0)
			bookId = 1 + bCpy[i - 1].id;



		printf("\nEnter the Member ID :");
		rewind(stdin);
		scanf("%s", inputMemId);
		for (int upper = 0; upper < 1; upper++) {
			inputMemId[upper] = toupper(inputMemId[upper]);
		}

		for (int i = 0; i < mCount; i++) {
			if (strcmp(p[i].memberId, inputMemId) == 0)
				printf("Member name : %s\n", p[i].name);
			else
				notFound++;

		}


		if (notFound < mCount) {
			printf("The booking ID : B%d\n", bookId);

			do {
				printf("\nBadminton = b , Karaoke = k ,Squash = s , Ping pong = p and Tennis = t \n");
				printf("Enter type of sports: ");
				rewind(stdin);
				scanf("%c", &b.type);
			} while (!validFacilityCode(b.type));
			if (b.type == 'b' || b.type == 's' || b.type == 't')
			{
				printf("\nCourt 1,2,3 and 4\n");
				printf("Which court you want: ");
				rewind(stdin);
				scanf("%d", &b.court);
			}
			else if (b.type == 'k') {
				printf("\nRoom 1,2,3 and 4\n");
				printf("Which room you want: ");
				rewind(stdin);
				scanf("%d", &b.court);
			}
			else
			{
				printf("\nTable 1, 2, 3 and 4\n");
				printf("Which table you want: ");
				rewind(stdin);
				scanf("%d", &b.court);
			}

			printf("\n1. "); displayDate(0); printf("2. "); displayDate(1);
			printf("3. "); displayDate(2);
			do {
				printf("\nSelect the Date :");
				rewind(stdin);
				scanf("%d", &b.dateChoice);
			} while (!validDate(b.dateChoice));

			printf("\nonly can book 1 hour or 2 hour \n");
			do {

				printf("Enter start time (hh:mm) in 24hour format :");
				rewind(stdin);
				scanf("%d:%d", &b.timeInHrs, &b.timeInMin);

				printf("\nEnter end time (hh:mm) in 24hour format :");
				rewind(stdin);
				scanf("%d:%d", &b.timeOutHrs, &b.timeOutMin);

			} while (!validTime(b.timeInHrs, b.timeInMin, b.timeOutHrs, b.timeOutMin));

			printf("\nComfirm (Y)es or (N)o ? ");
			rewind(stdin);
			scanf("%c", &comfirmAns);
			comfirmAns = tolower(comfirmAns);
			if (comfirmAns == 'y') {
				fptr = fopen("bookDt.txt", "a");
				if (fptr == NULL) {
					printf("Unable to open the file\n");
					exit(-1);
				}
				fprintf(fptr, "%s,B%d,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", inputMemId, bookId, b.type, b.court, b.dateChoice, b.timeInHrs, b.timeInMin, b.timeOutHrs, b.timeOutMin, t.wHour, t.wMinute, t.wDay, t.wMonth);
				fclose(fptr);

				system("cls");
				printf("\nThe new booking updated succesfully\n");
				printf("This is booking ID : B%d\n", bookId);
				printf("Press any key to back to main menu....... ");
				getch();
				comfirmAns = 'y';
			}
			else {
				system("cls");
				printf("\nNew booking updated unsuccesfully\n");
				printf("Back to menu (Y)es or (N)o ? ");
				rewind(stdin);
				scanf("%c", &comfirmAns);
				comfirmAns = tolower(comfirmAns);
			}
		}
		else {
			printf("\nNot found\n");
			printf("Back to menu (Y)es or (N)o ? ");
			rewind(stdin);
			scanf("%c", &comfirmAns);
			comfirmAns = tolower(comfirmAns);
		}
		c++;
	} while (comfirmAns != 'y');



}
void displayCurBooking() {
	int choiceSportsDcb;
	system("cls");
	do {

		printf("Type of facilities\n");
		printf("==================\n");
		printf("1.Badminton\n");
		printf("2.Ping Pong\n");
		printf("3.Karaoke\n");
		printf("4.Squash\n");
		printf("5.Tennis\n");
		printf("6.Exit\n");

		printf("Select your choice : ");
		rewind(stdin);
		scanf("%d", &choiceSportsDcb);


		switch (choiceSportsDcb) {
		case 1:
			system("cls");
			subDisplayCurBooking('b', "Court");
			break;
		case 2:
			system("cls");
			subDisplayCurBooking('p', "Table");
			break;
		case 3:
			system("cls"); subDisplayCurBooking('k', "Room");
			break;
		case 4:system("cls"); subDisplayCurBooking('s', "Court");
			break;
		case 5:system("cls"); subDisplayCurBooking('t', "Court");
			break;
		case 6:
			system("cls");
			break;
		default: printf("Invalid number\n");
		}

	} while (choiceSportsDcb != 6);
}
void modifyBooking() {
	GetLocalTime(&t);
	char bookId[6], ans;
	int bCount = 0, invalid = 0;
	FILE* fptr;
	Booking bCpy[45];
	fptr = fopen("bookDt.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}


	while (!feof(fptr)) {
		fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[bCount].memId, bCpy[bCount].id, &bCpy[bCount].type, &bCpy[bCount].court,
			&bCpy[bCount].dateChoice, &bCpy[bCount].timeInHrs, &bCpy[bCount].timeInMin, &bCpy[bCount].timeOutHrs, &bCpy[bCount].timeOutMin, &bCpy[bCount].hrs,
			&bCpy[bCount].min, &bCpy[bCount].d.day, &bCpy[bCount].d.month);

		bCount++;
	}
	fclose(fptr);

	do {
		invalid = 0;
		system("cls");
		printf("Modify Booking\n");
		printf("==============\n");
		printf("\nPlease enter your booking ID : ");
		rewind(stdin);
		scanf("%s", bookId);
		upper_string(bookId);

		for (int i = 0; i < bCount; i++) {
			if (strcmp(bookId, bCpy[i].id) == 0) {
				printf("Member ID : %s \nDate :", bCpy[i].memId); displayDate(bCpy[i].dateChoice); printf("Type: %c\nTime: %02d:%02d-%02d:%02d\n", bCpy[i].type, bCpy[i].timeInHrs, bCpy[i].timeInMin, bCpy[i].timeOutHrs, bCpy[i].timeOutMin);
				printf("Sure to modify (Y)es or (N)o ?");
				rewind(stdin);
				scanf("%c", &ans);
				ans = tolower(ans);
				if (ans == 'y') {
					do {
						printf("\nBadminton = b , Karaoke = k ,Squash = s , Ping pong = p and Tennis = t \n");
						printf("Enter type of sports: ");
						rewind(stdin);
						scanf("%c", &bCpy[i].type);
					} while (!validFacilityCode(bCpy[i].type));
					if (bCpy[i].type == 'b' || bCpy[i].type == 's' || bCpy[i].type == 't')
					{
						printf("\nCourt 1,2,3 and 4\n");
						printf("Which court you want: ");
						rewind(stdin);
						scanf("%d", &bCpy[i].court);
					}
					else if (bCpy[i].type == 'k') {
						printf("\nRoom 1,2,3 and 4\n");
						printf("Which room you want: ");
						rewind(stdin);
						scanf("%d", &bCpy[i].court);
					}
					else
					{
						printf("\nTable 1, 2, 3 and 4\n");
						printf("Which table you want: ");
						rewind(stdin);
						scanf("%d", &bCpy[i].court);
					}
					printf("\n1. "); displayDate(0); printf("2. "); displayDate(1);
					printf("3. "); displayDate(2);
					do {
						printf("\nSelect the Date :");
						rewind(stdin);
						scanf("%d", &bCpy[i].dateChoice);
					} while (!validDate(bCpy[i].dateChoice));

					do {

						printf("\nEnter start time (hh:mm) in 24hour format :");
						rewind(stdin);
						scanf("%d:%d", &bCpy[i].timeInHrs, &bCpy[i].timeInMin);

						printf("\nEnter end time (hh:mm) in 24hour format :");
						rewind(stdin);
						scanf("%d:%d", &bCpy[i].timeOutHrs, &bCpy[i].timeOutMin);

					} while (!validTime(bCpy[i].timeInHrs, bCpy[i].timeInMin, bCpy[i].timeOutHrs, bCpy[i].timeOutMin));


					fptr = fopen("bookDt.txt", "w");
					if (fptr == NULL) {
						printf("Unable to open the file\n");
						exit(-1);
					}
					for (int save = 0; save < bCount; save++) {
						fprintf(fptr, "%s,%s,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[save].memId, bCpy[save].id, bCpy[save].type, bCpy[save].court, bCpy[save].dateChoice, bCpy[save].timeInHrs, bCpy[save].timeInMin, bCpy[save].timeOutHrs, bCpy[save].timeOutMin, bCpy[save].hrs, bCpy[save].min, bCpy[save].d.day, bCpy[save].d.month);
					}
					fclose(fptr);
					printf("Modify succesfully\n");
				}
				else
					printf("Modify unsuccesfully\n");

			}
			else
				invalid++;

		}
		if (invalid == bCount)
			printf("Invalid ID\n");

		printf(" 0.Back to menu\n 1.Continue seacrh\n Select the choice: ");
		rewind(stdin);
		scanf("%c", &ans);
	} while (ans != '0');


}
void searchBookDtl() {

	GetLocalTime(&t);

	char bookId[6];
	int ans;
	int bCount = 0;
	FILE* fptr;
	Booking bCpy[45];
	FILE* file;
	struct Facility search[40];
	int fCount = 0; int i = 0;
	int invalid = 0;
	fptr = fopen("bookDt.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}


	while (!feof(fptr)) {
		fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[bCount].memId, bCpy[bCount].id, &bCpy[bCount].type, &bCpy[bCount].court,
			&bCpy[bCount].dateChoice, &bCpy[bCount].timeInHrs, &bCpy[bCount].timeInMin, &bCpy[bCount].timeOutHrs, &bCpy[bCount].timeOutMin, &bCpy[bCount].hrs,
			&bCpy[bCount].min, &bCpy[bCount].d.day, &bCpy[bCount].d.month);

		bCount++;
	}
	fclose(fptr);


	file = fopen("facility.txt", "r");
	if (file == NULL)
	{
		printf("This File Cannot Open !!\n");
		exit(-1);
	}
	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", search[fCount].facilityCode, search[fCount].facilityType, search[fCount].facilityDescript, search[fCount].facilityVenue, &search[fCount].facilityMin, &search[fCount].facilityMax) != -1)
	{
		fCount++;
	}
	fclose(file);

	do {
		system("cls");
		invalid = 0;
		printf("Search\n");
		printf("======\n");
		printf("\nPlease enter your booking ID : ");
		rewind(stdin);
		scanf("%s", bookId);

		upper_string(bookId);


		for (int i = 0; i < bCount; i++) {
			if (strcmp(bookId, bCpy[i].id) == 0) {
				printf("Member ID  : %s\n", bCpy[i].memId);
				printf("Date       : "); displayDate(bCpy[i].dateChoice);
				printf("Time       : %02d:%02d - %02d:%02d \n", bCpy[i].timeInHrs, bCpy[i].timeInMin, bCpy[i].timeOutHrs, bCpy[i].timeOutMin);
				searchBookFacility(bCpy[i].type, 'b', bCpy[i].court, 1, search, fCount, "BD1");
				searchBookFacility(bCpy[i].type, 'b', bCpy[i].court, 2, search, fCount, "BD2");
				searchBookFacility(bCpy[i].type, 'b', bCpy[i].court, 3, search, fCount, "BD3");
				searchBookFacility(bCpy[i].type, 'b', bCpy[i].court, 4, search, fCount, "BD4");
				searchBookFacility(bCpy[i].type, 'p', bCpy[i].court, 1, search, fCount, "PP1");
				searchBookFacility(bCpy[i].type, 'p', bCpy[i].court, 2, search, fCount, "PP2");
				searchBookFacility(bCpy[i].type, 'p', bCpy[i].court, 3, search, fCount, "PP3");
				searchBookFacility(bCpy[i].type, 'p', bCpy[i].court, 4, search, fCount, "PP4");
				searchBookFacility(bCpy[i].type, 'k', bCpy[i].court, 1, search, fCount, "KR1");
				searchBookFacility(bCpy[i].type, 'k', bCpy[i].court, 2, search, fCount, "KR2");
				searchBookFacility(bCpy[i].type, 'k', bCpy[i].court, 3, search, fCount, "KR3");
				searchBookFacility(bCpy[i].type, 'k', bCpy[i].court, 4, search, fCount, "KR4");
				searchBookFacility(bCpy[i].type, 's', bCpy[i].court, 1, search, fCount, "SQ1");
				searchBookFacility(bCpy[i].type, 's', bCpy[i].court, 2, search, fCount, "SQ2");
				searchBookFacility(bCpy[i].type, 's', bCpy[i].court, 3, search, fCount, "SQ3");
				searchBookFacility(bCpy[i].type, 's', bCpy[i].court, 4, search, fCount, "SQ4");
				searchBookFacility(bCpy[i].type, 't', bCpy[i].court, 1, search, fCount, "TN1");
				searchBookFacility(bCpy[i].type, 't', bCpy[i].court, 2, search, fCount, "TN2");
				searchBookFacility(bCpy[i].type, 't', bCpy[i].court, 3, search, fCount, "TN3");
				searchBookFacility(bCpy[i].type, 't', bCpy[i].court, 4, search, fCount, "TN4");
			}
			else
				invalid++;
		}

		if (invalid == bCount)
			printf("Invalid ID \n");


		printf(" 0.Back to menu\n 1.Continue seacrh\n Select the choice: ");
		rewind(stdin);
		scanf("%d", &ans);
	} while (ans != 0);
}
void searchBookFacility(char type, char ch, int court, int num, struct Facility search[], int fCount, char FacilityId[4]) {
	if (type == ch && court == num) {
		for (int f = 0; f < fCount; f++)
			searchDisplayFac(search[f].facilityCode, FacilityId, search[f].facilityType, search[f].facilityDescript, search[f].facilityVenue, search[f].facilityCode);
	}

}
void refreshDateFunc() {
	int  ans;
	int bCount = 0;
	FILE* fptr;
	Booking bCpy[45];
	fptr = fopen("bookDt.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}


	while (!feof(fptr)) {
		fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[bCount].memId, bCpy[bCount].id, &bCpy[bCount].type, &bCpy[bCount].court,
			&bCpy[bCount].dateChoice, &bCpy[bCount].timeInHrs, &bCpy[bCount].timeInMin, &bCpy[bCount].timeOutHrs, &bCpy[bCount].timeOutMin, &bCpy[bCount].hrs,
			&bCpy[bCount].min, &bCpy[bCount].d.day, &bCpy[bCount].d.month);

		bCount++;
	}
	fclose(fptr);

	printf("\n Refresh date\n (1)Yes or (0)No ?");
	rewind(stdin);
	scanf("%d", &ans);
	if (ans == 1) {
		for (int i = 0; i < bCount; i++) {
			if (bCpy[i].dateChoice == 1) {
				for (int remove = i; remove < bCount; remove++) {

					bCpy[remove] = bCpy[remove + 1];

				}
				bCount--;
				i--;
			}
		}



		fptr = fopen("bookDt.txt", "w");
		if (fptr == NULL) {
			printf("Unable to open the file\n");
			exit(-1);
		}
		for (int save = 0; save < bCount; save++) {
			fprintf(fptr, "%s,%s,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[save].memId, bCpy[save].id, bCpy[save].type, bCpy[save].court, bCpy[save].dateChoice, bCpy[save].timeInHrs, bCpy[save].timeInMin, bCpy[save].timeOutHrs, bCpy[save].timeOutMin, bCpy[save].hrs, bCpy[save].min, bCpy[save].d.day, bCpy[save].d.month);
		}
		fclose(fptr);
		bCount = 0;
		fptr = fopen("bookDt.txt", "r");
		if (fptr == NULL) {
			printf("Unable to open the file\n");
			exit(-1);
		}
		while (!feof(fptr)) {
			fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[bCount].memId, bCpy[bCount].id, &bCpy[bCount].type, &bCpy[bCount].court,
				&bCpy[bCount].dateChoice, &bCpy[bCount].timeInHrs, &bCpy[bCount].timeInMin, &bCpy[bCount].timeOutHrs, &bCpy[bCount].timeOutMin, &bCpy[bCount].hrs,
				&bCpy[bCount].min, &bCpy[bCount].d.day, &bCpy[bCount].d.month);

			bCount++;
		}
		fclose(fptr);
		for (int i = 0; i < bCount; i++) {
			if (bCpy[i].dateChoice == 2)
				bCpy[i].dateChoice = 1;
			else
				bCpy[i].dateChoice = 2;

		}

		fptr = fopen("bookDt.txt", "w");
		if (fptr == NULL) {
			printf("Unable to open the file\n");
			exit(-1);
		}
		for (int save = 0; save < bCount; save++) {
			fprintf(fptr, "%s,%s,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[save].memId, bCpy[save].id, bCpy[save].type, bCpy[save].court, bCpy[save].dateChoice, bCpy[save].timeInHrs, bCpy[save].timeInMin, bCpy[save].timeOutHrs, bCpy[save].timeOutMin, bCpy[save].hrs, bCpy[save].min, bCpy[save].d.day, bCpy[save].d.month);
		}
		fclose(fptr);

		printf("Refresh Succesfully\n");

	}
	else
		printf("Refresh Unsuccesfully\n");

	printf("\nPress any key to back to booking system......");
	getch();


}
void cancelFunc() {
	GetLocalTime(&t);
	char bookId[6], ans;

	FILE* fptr;
	Booking bCpy[45];

	do {
		system("cls");
		int invalid = 0;
		int bCount = 0;
		fptr = fopen("bookDt.txt", "r");
		if (fptr == NULL) {
			printf("Unable to open the file\n");
			exit(-1);
		}

		while (!feof(fptr)) {
			fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[bCount].memId, bCpy[bCount].id, &bCpy[bCount].type, &bCpy[bCount].court,
				&bCpy[bCount].dateChoice, &bCpy[bCount].timeInHrs, &bCpy[bCount].timeInMin, &bCpy[bCount].timeOutHrs, &bCpy[bCount].timeOutMin, &bCpy[bCount].hrs,
				&bCpy[bCount].min, &bCpy[bCount].d.day, &bCpy[bCount].d.month);

			bCount++;
		}
		printf("Cancel Booking\n");
		printf("==============\n");
		printf("\nEnter booking ID : ");
		rewind(stdin);
		scanf("%s", bookId);

		upper_string(bookId);

		for (int i = 0; i < bCount; i++) {
			if (strcmp(bookId, bCpy[i].id) == 0) {
				printf("Member ID : %s\n", bCpy[i].memId);
				printf("Type      : %c\n", bCpy[i].type);
				printf("Date      : "); displayDate(bCpy[i].dateChoice);
				printf("Time      : %02d:%02d - %02d:%02d \n", bCpy[i].timeInHrs, bCpy[i].timeInMin, bCpy[i].timeOutHrs, bCpy[i].timeOutMin);
				infoCodeOfSport();
				printf("Sure to cancel  (Y)es or (N)o ? ");
				rewind(stdin);
				scanf("%c", &ans);
				ans = tolower(ans);
				if (ans == 'y') {
					for (int remove = i; remove < bCount; remove++) {
						bCpy[remove] = bCpy[remove + 1];
					}
					bCount--;

					fptr = fopen("bookDt.txt", "w");
					if (fptr == NULL) {
						printf("Unable to open the file\n");
						exit(-1);
					}
					for (int save = 0; save < bCount; save++) {
						fprintf(fptr, "%s,%s,%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[save].memId, bCpy[save].id, bCpy[save].type, bCpy[save].court, bCpy[save].dateChoice, bCpy[save].timeInHrs, bCpy[save].timeInMin, bCpy[save].timeOutHrs, bCpy[save].timeOutMin, bCpy[save].hrs, bCpy[save].min, bCpy[save].d.day, bCpy[save].d.month);
					}
					fclose(fptr);
					bCount++;
					printf("Deleted Succussfully\n");

				}
				else
					printf("Deleted Unsuccussfully\n");

			}
			else
				invalid++;

		}

		if (invalid == bCount)
			printf("Invalid ID\n");

		printf(" 0.Back to menu\n 1.Continue delete\n Select the choice: ");
		rewind(stdin);
		scanf("%c", &ans);
	} while (ans != '0');
}
void displayDate(int date) {
	int minus = 0;
	if (t.wMonth == 2 && t.wDay >= 28) {
		if (t.wDay == 29 && t.wYear % 4 == 0) {
			minus = t.wDay;
		}
		else
			minus = t.wDay;
	}
	else if (t.wMonth == 1 || t.wMonth == 3 || t.wMonth == 5 || t.wMonth == 7 || t.wMonth == 8 || t.wMonth == 10 || t.wMonth == 12) {
		if (t.wDay == 31)
			minus = t.wDay;
		else
			minus = 0;
	}
	else {
		if (t.wDay == 30)
			minus = t.wDay;
		else
			minus = 0;
	}


	if (date == 0)
		printf("%d/%d/%d\n", t.wDay, t.wMonth, t.wYear);
	else if (date == 1)
		printf("%d/%d/%d\n", 1 + (t.wDay - minus), t.wMonth, t.wYear);
	else
		printf("%d/%d/%d\n", 2 + (t.wDay - minus), t.wMonth, t.wYear);
}
void searchDisplayFac(char searchCode[4], char court[4], char type[30], char searchDescript[30], char searchVenue[30], char id[4]) {

	if (strcmp(searchCode, court) == 0) {
		printf("Facility   : %s\n", id);
		printf("Type       : %s (%s)\n", type, searchDescript);
		printf("Venue      : %s\n", searchVenue);
	}
}
void infoCodeOfSport() {
	printf("\n b = \"Badminton\"\n k = \"Karaoke\"\n t = \"Tennis\"\n p = \"Ping Pong\"\n s = \"Squash\"\n\n ");
}
void subBodyDcb(char id[6], char type, int court, int timeInHrs, int timeInMin, int timeOutHrs, int timeOutMin, char memId[6], int hrs, int min, int day, int month) {
	printf("%s         %c       %d    %02d:%02d-%02d:%02d     %s     %d:%d,Date:%d/%d\n\n", id, type, court, timeInHrs, timeInMin, timeOutHrs, timeOutMin, memId, hrs, min, day, month);
}
void subDisplayCurBooking(char type, char place[]) {

	GetLocalTime(&t);
	Booking bCpy[45];
	int c = 0;
	FILE* fptr;
	fptr = fopen("bookDt.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}


	while (!feof(fptr)) {
		fscanf(fptr, "%[^,],%[^,],%c,%d##%d,%d:%d-%d:%d,%d:%d,%d/%d\n", bCpy[c].memId, bCpy[c].id, &bCpy[c].type, &bCpy[c].court, &bCpy[c].dateChoice, &bCpy[c].timeInHrs, &bCpy[c].timeInMin, &bCpy[c].timeOutHrs, &bCpy[c].timeOutMin, &bCpy[c].hrs, &bCpy[c].min, &bCpy[c].d.day, &bCpy[c].d.month);
		c++;
	}

	fclose(fptr);


	headingDate(0, place);
	bodyDisplyCurBooking(bCpy, c, 1, type);
	headingDate(1, place);
	bodyDisplyCurBooking(bCpy, c, 2, type);
	headingDate(2, place);
	bodyDisplyCurBooking(bCpy, c, 3, type);
	infoCodeOfSport();

}
void bodyDisplyCurBooking(Booking b[], int c, int num, char ch) {

	for (int i = 0; i < c; i++) {
		if (b[i].dateChoice == num && b[i].type == ch)
			subBodyDcb(b[i].id, b[i].type, b[i].court, b[i].timeInHrs, b[i].timeInMin, b[i].timeOutHrs, b[i].timeOutMin, b[i].memId, b[i].hrs, b[i].min, b[i].d.day, b[i].d.month);
	}
}
void headingDate(int plus, char place[]) {

	GetLocalTime(&t);

	printf("Date: "); displayDate(plus);
	printf("Booking ID   Type   %s    Start-End  Member ID   User Booking at\n", place);
	printf("==========   ====   =====    =========  =========   ===============\n");
}
int validTime(int inHrs, int inMin, int outHrs, int outMin) {
	int total;
	if (inHrs >= 10 && inHrs <= 22 && inMin >= 0 && inMin <= 59 && outHrs >= 10 && outHrs <= 22 && outMin >= 0 && outMin <= 59) {
		if (outMin - inMin == 0 && outHrs - inHrs <= 2 && outHrs - inHrs > 0)
			return 1;
		else
			return 0;

	}
	else
		return 0;

}
int validFacilityCode(char code) {
	if (code == 'b' || code == 'k' || code == 's' || code == 'p' || code == 't')
		return 1;
	else
		return 0;
}
int validDate(int choice) {
	if (choice == 1 || choice == 2 || choice == 3)
		return 1;
	else
		return 0;
}
//

//Yiyang
void facilityMain()
{
	int choose;
	do
	{
		system("cls");
		printf("Facility Module \n");
		printf("-----------------\n");
		printf("1. Add Facility \n");
		printf("2. Search Facility \n");
		printf("3. Modify Facility \n");
		printf("4. Display Facility \n");
		printf("5. Delete Facility \n");
		printf("6. Backup Facility \n");
		printf("7. Exit \n");
		printf("Please choose a option > ");
		scanf("%d", &choose);
		printf("-----------------------------\n");

		switch (choose)
		{
		case 1: {
			addFacility();
		}
			  break;
		case 2: {
			searchFacility();
		}
			  break;
		case 3: {
			modifyFacility();
		}
			  break;
		case 4: {
			displayFacility();
		}
			  break;
		case 5: {
			deleteFacility();
		}
			  break;
		case 6: {
			backupFacility();
		}
			  break;
		case 7:printf("Thank You, Bye Bye ! \n");
			break;
		default: printf("Please choose a correct option! \n");
			printf("-------------------------------\n");
			break;
		}
	} while (choose != 7);

	system("pause");
}
void addFacility()
{
	struct Facility facility;
	char answer;
	FILE* file;
	file = fopen("facility.txt", "a");
	if (file == NULL)
	{
		printf("This File Cannot Open !!\n");
		exit(-1);
	}

	do
	{
		printf("Enter new facility code > ");
		rewind(stdin);
		scanf("%[^\n]", facility.facilityCode);
		printf("Enter new facility type > ");
		rewind(stdin);
		scanf("%[^\n]", facility.facilityType);
		printf("Enter new facility description > ");
		rewind(stdin);
		scanf("%[^\n]", facility.facilityDescript);
		printf("Enter new facility venue > ");
		rewind(stdin);
		scanf("%[^\n]", facility.facilityVenue);
		printf("Enter new minimum users > ");
		rewind(stdin);
		scanf("%d", &facility.facilityMin);
		printf("Enter new maximum users > ");
		rewind(stdin);
		scanf("%d", &facility.facilityMax);

		fprintf(file, "%s,%s,%s,%s,%d,%d\n", facility.facilityCode, facility.facilityType, facility.facilityDescript, facility.facilityVenue, facility.facilityMin, facility.facilityMax);
		printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
		printf("-----------------------------------------------------------------------------------------------------\n");
		printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility.facilityCode, facility.facilityType, facility.facilityDescript, facility.facilityVenue, facility.facilityMin, facility.facilityMax);
		printf("-----------------------------------------------------------------------------------------------------\n");
		printf("New Facility have been added!! \n");
		printf("Continue for  add facility? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &answer);
		answer = toupper(answer);
		printf("-----------------------------\n");
	} while (answer == 'Y');
	fclose(file);
}
void searchFacility()
{
	struct Facility facility[40];
	int option, findMin, findMax, fCount = 0;
	char findCode[4], findType[20], ans;
	FILE* file;
	file = fopen("facility.txt", "r");
	if (file == NULL)
	{
		printf("This File Cannot Open !!\n");
		exit(-1);
	}
	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", facility[fCount].facilityCode, facility[fCount].facilityType, facility[fCount].facilityDescript, facility[fCount].facilityVenue, &facility[fCount].facilityMin, &facility[fCount].facilityMax) != -1)
	{
		fCount++;
	}
	fclose(file);
	do {
		printf("1. Facility Code\n");
		printf("2. Facility Type\n");
		printf("3. Minimum User\n");
		printf("4. Maximum User\n");
		printf("Do you want to search with ? ");
		scanf("%d", &option);

		switch (option)
		{
		case 1:
		{
			int notFound = 0;
			printf("---------------------\n");
			printf("Available Facility ID:\n");
			for (int a = 0; a < fCount; a++)
			{
				printf("%s ", facility[a].facilityCode);
			}
			printf("\n");
			printf("---------------------\n");
			printf("Enter code to search more details > ");
			rewind(stdin);
			scanf("%[^\n]", findCode);
			printf("-----------------------------\n");
			printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
			printf("-----------------------------------------------------------------------------------------------------\n");
			for (int a = 0; a < fCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
					printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);
				else
					notFound++;
			}
			if (notFound == fCount)
				printf("The Facility ID was not found ! \n");
			break;
		}

		case 2:
		{
			int notFound = 0;
			printf("Enter Facility Type > ");
			rewind(stdin);
			scanf("%[^\n]", findType);
			printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
			printf("-----------------------------------------------------------------------------------------------------\n");
			for (int a = 0; a < fCount; a++)
			{
				if (strcmp(findType, facility[a].facilityType) == 0)
				{
					printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);
				}
				else
					notFound++;
			}
			if (notFound == fCount)
				printf("Not Founded !\n");
			break;
		}

		case 3:
		{
			int notFound = 0;
			printf("Enter Minimum User > ");
			rewind(stdin);
			scanf("%d", &findMin);
			printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
			printf("-----------------------------------------------------------------------------------------------------\n");
			for (int a = 0; a < fCount; a++)
			{
				if (findMin == facility[a].facilityMin)
					printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);				else
					notFound++;
			}
			if (notFound == fCount)
				printf("Not Founded ! \n");
			break;
		}

		case 4:
		{
			int notFound = 0;
			printf("Enter Maximum User > ");
			rewind(stdin);
			scanf("%d", &findMax);
			printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
			printf("-----------------------------------------------------------------------------------------------------\n");
			for (int a = 0; a < fCount; a++)
			{
				if (findMax == facility[a].facilityMax)
					printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);				else
					notFound++;
			}
			if (notFound == fCount)
				printf("Not Founded ! \n");
			break;
		}

		default:printf("Please choose a correct option !\n\n");
			break;
		}
		printf("-----------------------------------------------------------------------------------------------------\n");
		printf("Continue to search ? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &ans);
		ans = toupper(ans);
		printf("-----------------------------\n");
	} while (ans == 'Y');
}
void modifyFacility()
{
	struct Facility facility[40];
	int mCount = 0, choose;
	char answer, findCode[4];
	FILE* file;
	file = fopen("facility.txt", "r");
	if (file == NULL)
	{
		printf("This File Cannot Open !!\n");
		exit(-1);
	}
	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", facility[mCount].facilityCode, facility[mCount].facilityType, facility[mCount].facilityDescript, facility[mCount].facilityVenue, &facility[mCount].facilityMin, &facility[mCount].facilityMax) != -1)
	{
		mCount++;
	}
	fclose(file);

	do
	{
		printf("1. All \n");
		printf("2. Facility Code \n");
		printf("3. Facility Type \n");
		printf("4. Facility Description \n");
		printf("5. Facility Venue \n");
		printf("6. Minimum User \n");
		printf("7. Maximum User \n");
		printf("What do you want to modify ? ");
		rewind(stdin);
		scanf("%d", &choose);
		printf("-----------------------------\n");
		switch (choose)
		{
		case 1:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Facility Code > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityCode);
					printf("Enter new Faciltiy Type > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityType);
					printf("Enter new Faciltiy Description > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityDescript);
					printf("Enter new Faciltiy Venue > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityVenue);
					printf("Enter new Faciltiy Minimum User > ");
					rewind(stdin);
					scanf("%d", &facility[a].facilityMin);
					printf("Enter new Faciltiy Maximum User > ");
					rewind(stdin);
					scanf("%d", &facility[a].facilityMax);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 2:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Facility Code > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityCode);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 3:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Faciltiy Type > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityType);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 4:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Faciltiy Description > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityDescript);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 5:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Faciltiy Venue > ");
					rewind(stdin);
					scanf("%[^\n]", facility[a].facilityVenue);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 6:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("---------------------------------------\n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Faciltiy Minimum User > ");
					rewind(stdin);
					scanf("%d", &facility[a].facilityMin);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		case 7:
		{
			int notFound = 0;
			printf("Enter Facility Code to modify > ");
			rewind(stdin);
			scanf("%[^\n]", &findCode);
			for (int a = 0; a < mCount; a++)
			{
				if (strcmp(findCode, facility[a].facilityCode) == 0)
				{
					printf("Original Facility Details : \n");
					printf("Facility Code         : %s \n", facility[a].facilityCode);
					printf("Facility Type         : %s \n", facility[a].facilityType);
					printf("Facility Description  : %s \n", facility[a].facilityDescript);
					printf("Facility Venue        : %s \n", facility[a].facilityVenue);
					printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
					printf("---------------------------------------\n");
					printf("Enter new Faciltiy Maximum User > ");
					rewind(stdin);
					scanf("%d", &facility[a].facilityMax);
					printf("Update Successfully !\n");
				}
				else
					notFound++;
			}
			if (notFound == mCount)
				printf("The Code was not found ! \n");
			break;
		}
		default:
		{
			printf("Please choose the correct option!! \n");
			break;
		}
		}

		file = fopen("facility.txt", "w");
		if (file == NULL)
		{
			printf("This File Canoot Open !! \n");
			exit(-1);
		}
		for (int i = 0; i < mCount; i++)
		{
			fprintf(file, "%s,%s,%s,%s,%d,%d \n", facility[i].facilityCode, facility[i].facilityType, facility[i].facilityDescript, facility[i].facilityVenue, facility[i].facilityMin, facility[i].facilityMax);
		}
		fclose(file);
		printf("Continue for modify ? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &answer);
		answer = toupper(answer);
		printf("-----------------------------\n");
	} while (answer == 'Y');
}
void displayFacility()
{
	struct Facility facility;
	int countFacility = 0;
	FILE* file;
	file = fopen("facility.txt", "r");
	if (file == NULL)
	{
		printf("This File Cannot Open !!\n");
		exit(-1);
	}
	printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", facility.facilityCode, facility.facilityType, facility.facilityDescript, facility.facilityVenue, &facility.facilityMin, &facility.facilityMax) != -1)
	{
		printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility.facilityCode, facility.facilityType, facility.facilityDescript, facility.facilityVenue, facility.facilityMin, facility.facilityMax);
		countFacility++;
	}
	printf("---------------------\n");
	printf("%d Facilities Listed.\n", countFacility);
	printf("---------------------\n");


	fclose(file);
	printf("\nPress any key to continue ......");
	getch();
}
void deleteFacility()
{
	struct Facility facility[40];
	int dCount = 0;
	char dltCode[4], answer, comfirm;
	FILE* file;
	file = fopen("facility.txt", "r");
	if (file == NULL)
	{
		printf("This File cannot open! \n");
		exit(-1);
	}

	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", facility[dCount].facilityCode, facility[dCount].facilityType, facility[dCount].facilityDescript, facility[dCount].facilityVenue, &facility[dCount].facilityMin, &facility[dCount].facilityMax) != -1)
	{
		dCount++;
	}
	fclose(file);
	do
	{
		int notFound = 0;
		printf("----------------------- \n");
		printf("Available Facility Id :\n");
		for (int a = 0; a < dCount; a++)
		{
			printf("%s ", facility[a].facilityCode);
		}
		printf("\n");
		printf("----------------------- \n");
		printf("Enter Facility ID to dalete > ");
		rewind(stdin);
		scanf("%[^\n]", dltCode);

		for (int a = 0; a < dCount; a++)
		{
			if (strcmp(dltCode, facility[a].facilityCode) == 0)
			{
				printf("Facility Details : \n");
				printf("---------------------------------------\n");
				printf("Facility Code         : %s \n", facility[a].facilityCode);
				printf("Facility Type         : %s \n", facility[a].facilityType);
				printf("Facility Description  : %s \n", facility[a].facilityDescript);
				printf("Facility Venue        : %s \n", facility[a].facilityVenue);
				printf("Facility Min-Max User : %d-%d \n", facility[a].facilityMin, facility[a].facilityMax);
				printf("---------------------------------------\n");
				printf("Comfirm to delete facility %s ? (Y/N) > ", facility[a].facilityCode);
				rewind(stdin);
				scanf("%c", &comfirm);
				comfirm = toupper(comfirm);
				if (comfirm == 'Y')
				{
					FILE* file2;
					file2 = fopen("backupfile.txt", "a");
					if (file2 == NULL)
					{
						printf("This file cannot open ! \n");
						exit(-1);
					}
					fprintf(file2, "%s,%s,%s,%s,%d,%d \n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);
					fclose(file2);
					for (int c = a; c < dCount; c++)
					{
						strcpy(facility[c].facilityCode, facility[c + 1].facilityCode);
						strcpy(facility[c].facilityType, facility[c + 1].facilityType);
						strcpy(facility[c].facilityDescript, facility[c + 1].facilityDescript);
						strcpy(facility[c].facilityVenue, facility[c + 1].facilityVenue);
						facility[c].facilityMin = facility[c + 1].facilityMin;
						facility[c].facilityMax = facility[c + 1].facilityMax;
					}
					dCount--;
					file = fopen("facility.txt", "w");
					if (file == NULL)
					{
						printf("This file cannot open! \n");
						exit(-1);
					}
					for (int c = 0; c < dCount; c++)
					{
						fprintf(file, "%s,%s,%s,%s,%d,%d \n", facility[c].facilityCode, facility[c].facilityType, facility[c].facilityDescript, facility[c].facilityVenue, facility[c].facilityMin, facility[c].facilityMax);
					}
					fclose(file);
					printf("Delete successful ! \n");
					printf("-----------------------------\n");
					dCount++;
				}
			}
			else
			{
				notFound++;
			}
			if (notFound == dCount)
			{
				printf("The Facility ID was not found ! \n");
			}
		}
		printf("Continue to delete ? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &answer);
		answer = toupper(answer);
		printf("-----------------------------\n");
	} while (answer == 'Y');


}
void backupFacility()
{
	struct Facility facility[40];
	int bCount = 0, notFound = 0;
	char answer, findCode[4];
	FILE* file2;
	file2 = fopen("backupfile.txt", "r");
	if (file2 == NULL)
	{
		printf("This file cannot open ! \n");
		exit(-1);
	}
	printf("The Facility that have been deleted :\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("Facility Code     Facility Type         Facility Description       Facility Venue        Min-Max User\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	while (fscanf(file2, "%[^,],%[^,],%[^,],%[^,],%d,%d \n", facility[bCount].facilityCode, facility[bCount].facilityType, facility[bCount].facilityDescript, facility[bCount].facilityVenue, &facility[bCount].facilityMin, &facility[bCount].facilityMax) != -1)
	{
		printf("   %s\t\t   %s\t\t     %s\t\t  %s\t    %d-%d\n", facility[bCount].facilityCode, facility[bCount].facilityType, facility[bCount].facilityDescript, facility[bCount].facilityVenue, facility[bCount].facilityMin, facility[bCount].facilityMax);
		bCount++;
	}
	fclose(file2);
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("Do you want to restore the facility ? (Y/N) > ");
	rewind(stdin);
	scanf("%c", &answer);
	answer = toupper(answer);
	if (answer == 'Y')
	{
		printf("Enter Facility code to restore > ");
		rewind(stdin);
		scanf("%[^\n]", findCode);
		for (int a = 0; a < bCount; a++)
			if (strcmp(findCode, facility[a].facilityCode) == 0)
			{
				FILE* file;
				file = fopen("facility.txt", "a");
				if (file == NULL)
				{
					printf("The file cannot open ! \n");
					exit(-1);
				}
				fprintf(file, "%s,%s,%s,%s,%d,%d \n", facility[a].facilityCode, facility[a].facilityType, facility[a].facilityDescript, facility[a].facilityVenue, facility[a].facilityMin, facility[a].facilityMax);
				fclose(file);
				for (int c = a; c < bCount; c++)
				{
					strcpy(facility[c].facilityCode, facility[c + 1].facilityCode);
					strcpy(facility[c].facilityType, facility[c + 1].facilityType);
					strcpy(facility[c].facilityDescript, facility[c + 1].facilityDescript);
					strcpy(facility[c].facilityVenue, facility[c + 1].facilityVenue);
					facility[c].facilityMin = facility[c + 1].facilityMin;
					facility[c].facilityMax = facility[c + 1].facilityMax;
				}
				bCount--;
				printf("Restore successful ! \n");
				printf("-----------------------------\n");
				file2 = fopen("backupfile.txt", "w");
				if (file2 == NULL)
				{
					printf("This file cannot open! \n");
					exit(-1);
				}
				for (int c = 0; c < bCount; c++)
				{
					fprintf(file2, "%s,%s,%s,%s,%d,%d \n", facility[c].facilityCode, facility[c].facilityType, facility[c].facilityDescript, facility[c].facilityVenue, facility[c].facilityMin, facility[c].facilityMax);
				}
				fclose(file2);
				bCount++;
			}
			else
			{
				notFound++;
			}
		if (notFound == bCount)
		{
			printf("The Facility ID was not found ! \n");
		}
	}

	printf("\nPress any key to continue ......");
	getch();
}
//

//Weng ni
void memberMain() {

	int choice;

	do {
		system("cls");
		printf("\nMember Management System\n");
		printf("-------------------------\n");
		printf("1. Add members info\n");
		printf("2. Search members info\n");
		printf("3. Modify members info\n");
		printf("4. Display all members info\n");
		printf("5. Delete members info\n");
		printf("6. Sort members info\n");
		printf("0. Exit\n");
		printf("Select an option:> ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			displayAll(1);
			addMember();
			break;
		case 2:
			system("cls");
			searchMember();
			break;
		case 3:
			system("cls");
			displayAll(1);
			modifyMember();
			break;
		case 4:
			system("cls");
			displayAll(1);
			break;
		case 5:
			system("cls");
			displayAll(1);
			deleteMember();
			break;
		case 6:
			system("cls");
			displayAll(1);
			sortMember();
			break;
		case 0:
			printf("Bye Bye!\n");
			break;
		default:
			printf("Incorrect choice\n");
		}
	} while (choice != 0);

}
void printMemberBanner(void)
{
	printf("\nMember Details\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Member ID\tName\t\t\t\t\t\tGender\t\tIC\t\t\tContact Number\t\tDate of Birth\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
void addMember() {

	printf("\nAdd Member Details\n");
	printf("--------------------\n");
	fPtr = fopen("member.bin", "ab");

	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-1);
	}

	char ansAdd;

	do {
		printf("\nEnter your member ID: ");
		rewind(stdin);
		scanf("%[^\n]", &members.memberId);

		printf("Enter your name: ");
		rewind(stdin);
		scanf("%[^\n]", &members.name);

		printf("Enter your gender: ");
		rewind(stdin);
		scanf("%c", &members.gender);

		printf("Enter your IC: ");
		rewind(stdin);
		scanf("%[^\n]", &members.IC);

		printf("Enter your contact number: ");
		rewind(stdin);
		scanf("%[^\n]", &members.contactNum);

		printf("Enter your date of birth(dd/mm/yyyy): ");
		rewind(stdin);
		scanf("%d %d %d", &members.DOB.day, &members.DOB.month, &members.DOB.year);

		fwrite(&members, sizeof(members), 1, fPtr);

		printMemberBanner();
		printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", members.memberId, members.name, members.gender, members.IC, members.contactNum, members.DOB.day, members.DOB.month, members.DOB.year);

		printf("\nDo you want to continue adding? (Y/N) ");
		rewind(stdin);
		scanf("%c", &ansAdd);
		ansAdd = toupper(ansAdd);

	} while (ansAdd == 'Y');

	fclose(fPtr);
	printf("\nPress any key to continue.......\n");
	getch();
}
void searchMember() {
	struct Member p[20];
	printf("\nSearch Member Details\n");
	printf("-----------------------\n");
	char searchID[6], ansSearch;

	do {
		fPtr = fopen("member.bin", "rb");
		if (fPtr == NULL) {
			printf("Failed to open file");
			exit(-2);
		}

		printf("\nMember ID > ");
		rewind(stdin);
		scanf("%[^\n]", &searchID);

		printMemberBanner();

		int i = 0;
		int numRecords = 0;

		while (fread(&p[i], sizeof(p[i]), 1, fPtr) != 0) {
			i++;
			numRecords++;
		}

		for (int i = 0; i < numRecords; i++) {

			if (strcmp(searchID, p[i].memberId) == 0) {

				printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", p[i].memberId, p[i].name, p[i].gender, p[i].IC, p[i].contactNum, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year);
			}
		}

		printf("\nDo you want to continue searching? (Y/N) ");
		rewind(stdin);
		scanf("%c", &ansSearch);
		ansSearch = toupper(ansSearch);

		fclose(fPtr);

	} while (ansSearch == 'Y');
	printf("\nPress any key to continue.......\n");
	getch();
}
void modifyMember() {
	struct Member p[20];

	printf("\nModify Member Details\n");
	printf("-----------------------\n");

	fPtr = fopen("member.bin", "rb");
	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-3);
	}

	int i = 0;
	int numRecords = 0;

	while (fread(&p[numRecords], sizeof(members), 1, fPtr) != 0) {
		numRecords++;
	}

	fclose(fPtr);

	fPtr = fopen("member.bin", "ab");
	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-4);
	}

	char sureToEdit, ansEdit, searchID[6], newName[40], newIC[15], newNum[15];
	int recordModified = 0, newDay, newMonth, newYear;

	do {

		printf("\nEnter ID of member to view for edit: ");
		rewind(stdin);
		scanf("%[^\n]", &searchID);

		for (int i = 0; i < numRecords; i++) {

			if (strcmp(searchID, p[i].memberId) == 0) {
				printf("Enter your name: ");
				rewind(stdin);
				scanf("%[^\n]", &newName);

				printf("Enter your IC: ");
				rewind(stdin);
				scanf("%[^\n]", &newIC);

				printf("Enter your contact number: ");
				rewind(stdin);
				scanf("%[^\n]", &newNum);

				printf("Enter your date of birth(dd/mm/yyyy): ");
				rewind(stdin);
				scanf("%d %d %d", &newDay, &newMonth, &newYear);

				printf("Sure to modify(Y = yes)? ");
				rewind(stdin);
				scanf("%c", &sureToEdit);
				sureToEdit = toupper(sureToEdit);

				if (sureToEdit == 'Y') {
					strcpy(p[i].name, newName);
					strcpy(p[i].IC, newIC);
					strcpy(p[i].contactNum, newNum);
					p[i].DOB.day = newDay;
					p[i].DOB.month = newMonth;
					p[i].DOB.year = newYear;
				}

				printMemberBanner();
				printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", p[i].memberId, p[i].name, p[i].gender, p[i].IC, p[i].contactNum, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year);
				recordModified++;
				printf("Number of records modified = %d\n", recordModified);
			}
		}

		printf("Do you want to continue editing? (Y/N) ");
		rewind(stdin);
		scanf("%c", &ansEdit);
		ansEdit = toupper(ansEdit);

	} while (ansEdit == 'Y');

	fclose(fPtr);

	FILE* fPtr;
	fPtr = fopen("member.bin", "wb");

	if (fPtr == NULL) {
		printf("Unable to open the file\n");
		exit(-5); //exit program
	}

	printMemberBanner();
	for (int i = 0; i < numRecords; i++) {
		printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", p[i].memberId, p[i].name, p[i].gender, p[i].IC, p[i].contactNum, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year);
		fwrite(&p[i], sizeof(p[i]), 1, fPtr);
	}

	fclose(fPtr); 
	printf("\nPress any key to continue.......\n");
	getch();
}
void deleteMember() {
	struct Member p[20];

	printf("\nDelete Member Details\n");
	printf("-----------------------\n");

	fPtr = fopen("member.bin", "rb");
	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-6);
	}

	char sureToDelete, ansDelete, searchID[6];
	int i = 0, numRecords = 0, recordDeleted = 0;

	while (fread(&p[i], sizeof(members), 1, fPtr) != 0) {
		numRecords++;
		i++;
	}

	do {
		printf("\nEnter ID of member to view for delete: ");
		rewind(stdin);
		scanf("%[^\n]", &searchID);

		for (int i = 0; i < numRecords; i++) {

			if (strcmp(searchID, p[i].memberId) == 0) {

				printf("Sure to delete(Y = yes)? ");
				rewind(stdin);
				scanf("%c", &sureToDelete);
				sureToDelete = toupper(sureToDelete);

				if (sureToDelete == 'Y') {
					for (int j = i; j < numRecords; j++)
					{
						p[j] = p[j + 1];
					}
					recordDeleted++;
				}
			}


		}
		printf("Number of records deleted = %d\n", recordDeleted);
		printf("Continue delete? (Y for yes) ");
		rewind(stdin);
		scanf("%c", &ansDelete);
		ansDelete = toupper(ansDelete);

	} while (ansDelete == 'Y');

	fclose(fPtr);

	fPtr = fopen("member.bin", "wb");

	if (fPtr == NULL) {
		printf("Unable to open the file\n");
		exit(-7); //exit program
	}

	printMemberBanner();

	for (int i = 0; i < (numRecords - recordDeleted); i++) {
		fwrite(&p[i], sizeof(p[i]), 1, fPtr);
		printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", p[i].memberId, p[i].name, p[i].gender, p[i].IC, p[i].contactNum, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year);
	}

	fclose(fPtr);
	printf("\nPress any key to continue.......\n");
	getch();
}
void displayAll(int stop) {
	printf("\nDisplay Member Details\n");
	printf("-----------------------\n");
	fPtr = fopen("member.bin", "rb");
	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-8);
	}
	printMemberBanner();

	fread(&members, sizeof(members), 1, fPtr);

	while (!feof(fPtr)) {
		printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", members.memberId, members.name, members.gender, members.IC, members.contactNum, members.DOB.day, members.DOB.month, members.DOB.year);
		fread(&members, sizeof(members), 1, fPtr);
	}

	fclose(fPtr);

	if (stop == 1) {
		printf("\nPress any key to continue.......\n");
		getch();
	}
}
void sortMember() {
	struct Member p[20];
	struct Member temp;

	printf("\nSort Member Details\n");
	printf("--------------------\n");
	fPtr = fopen("member.bin", "rb");

	if (fPtr == NULL) {
		printf("Failed to open file");
		exit(-9);
	}

	int i = 0, numRecords = 0;

	while (fread(&p[i], sizeof(members), 1, fPtr) != 0) {
		i++;
		numRecords++;
	}

	char order;

	do {

		printf("Do you want to sort in ascending order or descending order?(A for ascending/D for descending) ");
		rewind(stdin);
		scanf("%c", &order);

		order = toupper(order);

		if (order == 'A') {

			char key[20];
			//this method is insertion sort (ascending)

			for (int k = 0; k < numRecords; k++) {
				for (int step = 1; step < numRecords; step++) {
					strcpy(key, p[step].memberId);
					temp = p[step];
					int j = step - 1;

					while (strcmp(key, p[j].memberId) < 0 && j >= 0) { //compare key with each element on the left of it until an element smaller than the key is found

						p[step] = p[j];
						--j;
					}
					p[j + 1] = temp;
				}
			}
			fclose(fPtr);
		}

		else if (order == 'D') {

			char key[20];
			//this method is insertion sort (descending)

			for (int k = 0; k < numRecords; k++) {
				for (int step = 1; step < numRecords; step++) {
					strcpy(key, p[step].memberId);
					temp = p[step];
					int j = step - 1;

					while (strcmp(key, p[j].memberId) > 0 && j >= 0) { //compare key with each element on the left of it until an element bigger than the key is found

						p[step] = p[j];
						--j;
					}
					p[j + 1] = temp;
				}
			}
			fclose(fPtr);
		}

		else {
			printf("Invalid key, please enter again!\n");
		}
	} while (order != 'A' && order != 'D');

	fPtr = fopen("member.bin", "wb");

	if (fPtr == NULL) {

		printf("Unable to open the file\n");
		exit(-7); //exit program
	}

	printMemberBanner();

	for (int i = 0; i < numRecords; i++) {
		fwrite(&p[i], sizeof(p[i]), 1, fPtr);
		printf("%-6s\t\t%-30s\t\t\t%c\t\t%-15s\t\t%-15s\t\t%02d/%02d/%02d\n", p[i].memberId, p[i].name, p[i].gender, p[i].IC, p[i].contactNum, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year);
	}

	fclose(fPtr);
	printf("\nPress any key to continue.......\n");
	getch();
}
//