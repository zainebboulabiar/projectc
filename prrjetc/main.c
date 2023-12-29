#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>


typedef struct{
	char username[50];
	char name[50];
	int bus_num;
	int num_of_seats;
}pd;

typedef struct{
    char username[50];
    char password[50];
} account;

void reservation(void);
void viewdetails(void);
void printticket(char name[],int,int,float);
void specificbus(int);
float charge(int,int);
void createAccount(void);
int checkAccount(char username[], char password[]);

int main()

{
		system("cls");
	printf("\t\t|                       BUS TICKET RERSERVATION                      |\n");
    printf("\t\t|                               welcome                              |\n");
    printf("\t\t|                                                                    |\n");
    printf("\t\t----------------------------------------------------------------------\n");
    printf("\t\t-----------------------press any key to continue----------------------\n");
    printf("\t\t----------------------------------------------------------------------\n");
	getch();


    char enteredUsername[50], enteredPassword[50];
    int loginResult;

    // demande au voyageur s il a un compte
    printf("Do you have an account? (yes/no): ");
    char hasAccount;
    scanf(" %c", &hasAccount);

    if (hasAccount == 'y') {
        // voyageur a un compte, demander username et password
        printf("Enter Username: ");
        fflush(stdin);
        gets(enteredUsername);

        printf("Enter Password: ");
        gets(enteredPassword);

        loginResult = checkAccount(enteredUsername, enteredPassword);
        if (loginResult == 1) {
            printf("Login successful!\n");

        } else {
            printf("Incorrect username or password.\n");
            printf("Would you like to create a new account? (yes/no): ");
            char createNewAccount;
            scanf(" %c", &createNewAccount);

            if (createNewAccount == 'y') {
                createAccount();
                printf("Account created successfully!\n");
            } else {
                printf("Exiting the program.\n");
                return 0;
            }
        }
    } else {
        // Traveler doesn't have an account, create a new account
        createAccount();
        printf("Account created successfully!\n");
    }


 int menu_choice, choice_return;
    start:


	system("cls");
	printf("\n=================================\n");
	printf("    BUS RESERVATION SYSTEM");
	printf("\n=================================");
	printf("\n1>> Reserve A Ticket");
	printf("\n------------------------");
	printf("\n2>> View All Available Bus");
	 printf("\n------------------------");
	printf("\n3>> View Reservations");
    printf("\n------------------------");
    printf("\n4>> Modify Reservation");
    printf("\n------------------------");
	printf("\n5>> Exit");
	printf("\n------------------------");
    printf("\n\n-->");
	scanf("%d",&menu_choice);
	switch(menu_choice)
	{
		case 1:
			reservation();
			break;
		case 2:
			viewdetails();
			printf("\n\nPress any key to go to Main Menu..");
			getch();
			break;

        case 3:
            viewReservations();
            printf("\n\nPress any key to go back to Main Menu...");
            getch();
            break;

        case 4:
            modifyReservation();
            printf("\n\nPress any key to go back to Main Menu...");
            getch();
            break;

        case 5:
            return(0);

		default:
			printf("\nInvalid choice");
	}
	goto start;
	return(0);
}


//fonction pour creer unn compte

void createAccount(void) {
    system("cls");
    printf("=========== Create Traveler Account ===========\n");

    account newAccount;
    printf("Enter Username: ");
    fflush(stdin);
    gets(newAccount.username);

    printf("Enter Password: ");
    gets(newAccount.password);

    FILE *accountFile;
    accountFile = fopen("user_accounts.txt", "a");
    fprintf(accountFile, "%s %s\n", newAccount.username, newAccount.password);
    fclose(accountFile);

    printf("Account created successfully!\n");
    printf("Press any key to go back to Main Menu...");
    getch();
}


//fonction pour verifier que le compte existe ou non

int checkAccount(char username[], char password[]) {
    FILE *accountFile;
    accountFile = fopen("user_accounts.txt", "r");
    if (accountFile == NULL) {
        printf("Error opening the file!");
        exit(1);
    }

    account currentAccount;
    while (fscanf(accountFile, "%s %s", currentAccount.username, currentAccount.password) != EOF) {
        if (strcmp(username, currentAccount.username) == 0 && strcmp(password, currentAccount.password) == 0) {
            fclose(accountFile);
            return 1; // Successful login
        }
    }

    fclose(accountFile);
    return 0; // Invalid username or password
}











//fonction pour afficher les detaille des bus
void viewdetails(void)
{
	system("cls");
	printf("\nBUS.No\BUS Name\t\t\tDestinations   \t\tfare\t\tTime\n");
	printf("\n101\tBus A\ttunis to nabel\t\t          10.D\t\t   9am");
	printf("\n102\tBus B\ttunis to jerba\t\t          60.D\t\t   12pm");
	printf("\n103\tBus C\tsfax to bizert\t\t          40.D\t\t    8am");
	printf("\n104\tBus D\tnabel to beja\t\t           30.D\t\t   11am");
	printf("\n105\tBus E\ttunis to kef\t\t            40.D\t\t7am");
}
//fonction pour reserver un billet de bus
void reservation(void)
{
	char confirm;
	int i=0;
	float charges;
	pd passdetails;
	FILE *fp;
	fp=fopen("seats_reserved.txt","a");
	system("cls");

	printf("\nEnter Your Name:> ");
	fflush(stdin);
	gets(passdetails.name);

	printf("\nEnter Number of seats:> ");
	scanf("%d",&passdetails.num_of_seats);
	printf("\n\n>>Press Enter To View Available Bus<< ");
	getch();
	system("cls");
	viewdetails();
	printf("\n\nEnter bus number:> ");
	start1:
	scanf("%d",&passdetails.bus_num);
	if(passdetails.bus_num>=101 && passdetails.bus_num<=105)
	{
		charges=charge(passdetails.bus_num,passdetails.num_of_seats);
		printticket(passdetails.name,passdetails.num_of_seats,passdetails.bus_num,charges);
	}
	else
	{
		printf("\nInvalid bus Number! Enter again--> ");
		goto start1;
	}

	printf("\n\nConfirm Ticket (y/n):>");
	start:
	scanf(" %c",&confirm);
	if(confirm == 'y')
	{
		fprintf(fp,"%s\t\t%d\t\t%d\t\t%.2f\n",&passdetails.name,passdetails.num_of_seats,passdetails.bus_num,charges);
		printf("==================");
		printf("\n Reservation successful\n");
		printf("==================");
		printf("\nPress any key to go back to Main menu");
	}
	else
	{
		if(confirm=='n'){
			printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
		}
		else
		{
			printf("\nInvalid choice entered! Enter again-----> ");
			goto start;
		}
	}
	fclose(fp);
	getch();
}
// Fonction pour calculer les frais bas�s sur le num�ro du bus et le nombre de si�ges

float charge(int bus_num,int num_of_seats)
{
		if (bus_num==101)
	{
		return(10.0*num_of_seats);
	}
	if (bus_num==102)
	{
		return(60.0*num_of_seats);
	}
	if (bus_num==103)
	{
		return(40.0*num_of_seats);
	}
	if (bus_num==104)
	{
		return(30.0*num_of_seats);
	}
	if (bus_num==105)
	{
		return(40.0*num_of_seats);
	}
}


// Fonction pour imprimer le billet avec les d�tails du passager

void printticket(char name[],int num_of_seats,int bus_num,float charges)
{
	system("cls");
	printf("-------------------\n");
	printf("\tTICKET\n");
	printf("-------------------\n\n");
	printf("Name:\t\t\t%s",name);
	printf("\nNumber Of Seats:\t%d",num_of_seats);
	printf("\nBus Number:\t\t%d",bus_num);
	specificbus(bus_num);
	printf("\nCharges:\t\t%.2f",charges);
}


// Fonction pour afficher les d�tails sp�cifiques d'un bus
void specificbus(int bus_num)
{

	if (bus_num==101)
	{
		printf("\nBus:\t\t\tBUS A");
		printf("\nDestination:\t\tTUNIS to NABEL");
		printf("\nDeparture:\t\t9am ");
	}
	if (bus_num==102)
	{
		printf("\nBus:\t\t\tBUS B");
		printf("\nDestination:\t\tTUNIS to JERBA");
		printf("\nDeparture:\t\t12pm");
	}
	if (bus_num==103)
	{
		printf("\nBus:\t\t\tBUS C");
		printf("\nDestination:\t\tSFAX to BIZERT");
		printf("\nDeparture:\t\t8am");
	}
	if (bus_num==104)
	{
		printf("\nBus:\t\t\tBUS D");
		printf("\nDestination:\t\tNABEL to BEJA");
		printf("\nDeparture:\t\t11am ");
	}
	if (bus_num==105)
	{
		printf("\nBus:\t\t\tBUS C");
		printf("\nDestination:\t\tTUNIS to KEF");
		printf("\nDeparture:\t\t7am");
	}

}

//fonction pour afficher une reservation


void viewReservations(void) {
    // Add code to read and display reservations from the "seats_reserved.txt" file
    FILE *fp;
    fp = fopen("seats_reserved.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file!\n");
        return;
    }

    printf("\n================ Reservations ================\n");
    printf("Name\t\tSeats\tBus Number\tCharges\n");
    printf("-----------------------------------------------\n");

    pd passdetails;
    float charges;
    while (fscanf(fp, "%s %d %d %f", passdetails.name, &passdetails.num_of_seats, &passdetails.bus_num, &charges) != EOF) {
        printf("%s\t\t%d\t%d\t\t%.2f\n", passdetails.name, passdetails.num_of_seats, passdetails.bus_num, charges);
    }

    fclose(fp);
}

//fonction pour modifier une reservation

void modifyReservation(void) {

    FILE *fp, *tempFile;
    pd passdetails;
    float charges;
    int targetBusNum, targetSeats;
     char targetname;

    printf("\nEnter name hou make reservationto modify: ");
    scanf("%s", &targetname);


    printf("\nEnter Bus Number of the reservation to modify: ");
    scanf("%d", &targetBusNum);

    printf("Enter Number of Seats of the reservation to modify: ");
    scanf("%d", &targetSeats);

    fp = fopen("seats_reserved.txt", "r");
    tempFile = fopen("temp_reserved.txt", "w");
    if (fp == NULL || tempFile == NULL) {
        printf("Error opening the file!\n");
        return;
    }

    int modified = 0;
    while (fscanf(fp, "%s %d %d %f", passdetails.name, &passdetails.num_of_seats, &passdetails.bus_num, &charges) != EOF) {
        if (passdetails.bus_num == targetBusNum && passdetails.num_of_seats == targetSeats) {
            // Modify the reservation if found
            // You can add logic here to modify specific details
            printf("Enter new number of seats: ");
            scanf("%d", &passdetails.num_of_seats);

            charges = charge(passdetails.bus_num, passdetails.num_of_seats);
            modified = 1;
        }
        fprintf(tempFile, "%s %d %d %.2f\n", passdetails.name, passdetails.num_of_seats, passdetails.bus_num, charges);
    }

    fclose(fp);
    fclose(tempFile);

    if (!modified) {
        printf("Reservation not found!\n");
    } else {
        remove("seats_reserved.txt");
        rename("temp_reserved.txt", "seats_reserved.txt");
        printf("Reservation modified successfully!\n");
    }
}


