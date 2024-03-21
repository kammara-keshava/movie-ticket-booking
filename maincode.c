#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<errno.h>
#include<math.h>
// #include <windows.h>
#include<unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>

#define DATE_LENGTH 11
#define SLOT_COUNT 3

int firstclassA[26]; // three arrays are used to print the layout and store the booked ticket numbers in the array
int firstclass_B_F[5][20];
int secondclass_G_M[7][14];

struct unselect
{
    char row_unselect;
    int chair_number;
    struct unselect *next; // unselect linked list is used to store seat numbers booked by users
    struct unselect *prev;
};

struct unselect *head_unselect = NULL;
struct unselect *newnode, *temp1; // temp1 and newnode pointer is used for creating linked list for storing booking tickets information

struct snacks
{
    char cat_type; // catageory type
    int food_item; // for snacks                       // snacks linked list is used to store the snack items,quantity,price of each snack;
    int quantity;
    int price;
    struct snacks *lnext;
    struct snacks *rnext;
};

struct snacks *sna_head = NULL;
struct snacks *newnode1, *temporary1;

void Create_Layout(); // used to create layout for theatre

void Display_Layout(); //  used to display the theatre layout

void Booking_Tickets(); // this function is brain of the program which is used for backend purpose

int Seat_Is_Available_Or_Not(char row_selection, int seat_number); // used to check the seat entered by the user is available or not

int Valid_Seat_No_Or_Not(char row_selection, int seat_number); // used to check the seat entered by the user is valid or not

void create_CLL_for_unselection(char row_selection, int seat_number); // used to create linked list for storing booked seat numbers

void display_booked_tickets(); // used to display the booked tickets

int change_tickets(); // This function  works as user menu driven program for asking user want to change the seat numbers or not

void change_tickets_edit_layout(); //  This function is used to updation of theatre layout after changing the tickets and verifying user has enter valid input or not for changing the tickets

void edit_CLL_for_unselection(char row, int seatnumber); // This function is used to delete the node of changed tickets

void title_of_project(); // This function is used to display the title of the project using the text file "platform.txt"

void display_movie_details(); // This function is used to diplay the movie details using five text files---- "adipurush.txt", "brahmastra.txt" ,"fast_x.txt",  "gamechanger.txt",  "jailer.txt"

void display_slots_dates(); // used to diplay theatre names , available booking dates, available booking slots;

// snacks code
void display_snacks(); // used to display the snacks using the text file "snacks.txt";

void booking_snacks(); // important function for booking snack which is used for backend purpose like entered snack is valid or not

void create_linked_list_for_snacks(char food_code, int food, int qua); // used to store snack item, quantity, price of the snack using snack linked list;

void display_selected_snacks(); // used to display the booking summary and selected snacks with amount

void after_selecting_one_snack(); // This function is used as a menu driven program for asking user to 1.add snacks 2.Edit snacks 3.Go for payment

void calculate_amount_for_snacks(char food_code, int food, int qua); // used to calculate and store the price of enter snack in the snacks linked list

void edit_snacks(); // This function used as a menu driven program after clicking editing snacks Then it will display the option for 1.remove item 2.change quantity

void remove_snack_item(); // used to delete the unwanted snack data in the snack linked list

void change_quantity(); // used to change the quantity of the snack;

int check_doubly_adding_snacks(char food_code, int food); // used to increase the quantity of snack by one without aking user to enter the quantity if the entered snack is already present in the list
// snacks code

int calculate_ticket_amount(); // used to calculate the amount for the booked tickets

int calculate_number_0f_tickets(); // used to calculate the number of tickets

void do_calulation(); // used to do some basic calculations for generating bill

void display_final_bill(int, int, int); // used to display the finall bill

void loading_animation(); // used to display the loading animation

char Teatre_Name[30];
char Movie_Name[30];
char Booking_Time[15];
char Booking_Date[15];

int main()
{

    title_of_project();
    Create_Layout();
    Display_Layout();
    Booking_Tickets();
}

void Create_Layout()
{

    for (int i = 0; i < 26; i++)
    {
        firstclassA[i] = i + 1;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
            firstclass_B_F[i][j] = j + 1;
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
            secondclass_G_M[i][j] = j + 1;
    }
}

void Display_Layout()
{

    char rowalbhabet = 'A';
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------FIRST  CLASS-Rs. 210---------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("| %c: |\t  ", rowalbhabet);
    rowalbhabet++;
    for (int i = 0; i < 26; i++)
    {
        if (firstclassA[i] == 'X')
        {
            if (i > 8)
                printf("| %c | ", firstclassA[i]); // for displaying X in correct format
            else
                printf("| %c |", firstclassA[i]);
        }
        else
            printf("  %d  ", firstclassA[i]);
    }
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++)
    {
        printf("| %c: |\t  ", rowalbhabet);
        rowalbhabet++;

        int k = 0;
        for (int j = 0; j < 26; j++)
        {

            if (j < 3)
            {
                if (firstclass_B_F[i][k] == 'X')
                {
                    printf("| %c |", firstclass_B_F[i][k]);
                }
                else
                    printf("  %d  ", firstclass_B_F[i][k]);
                k++;
            }
            else if (j > 5 && j < 20)
            {
                if (firstclass_B_F[i][k] == 'X')
                {
                    if (k > 8)
                        printf("| %c | ", firstclass_B_F[i][k]); // for displaying X in correct format
                    else
                        printf("| %c |", firstclass_B_F[i][k]);
                }
                else
                    printf("  %d  ", firstclass_B_F[i][k]);
                k++;
            }
            else if (j > 22)
            {
                if (firstclass_B_F[i][k] == 'X')
                {
                    if (k > 8)
                        printf("| %c | ", firstclass_B_F[i][k]); // for displaying X in correct format
                    else
                        printf("| %c |", firstclass_B_F[i][k]);
                }
                else
                    printf("  %d  ", firstclass_B_F[i][k]);
                k++;
            }
            else
            {
                printf("     ");
            }
        }
        printf("\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    printf("\n\n\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------SECOND  CLASS-Rs. 170-----------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                       -----------------------------------------------------------------------------\n");
    for (int i = 0; i < 7; i++)
    {
        printf("| %c: |\t  ", rowalbhabet);
        rowalbhabet++;

        printf("                              ");

        for (int j = 0; j < 14; j++)
        {
            if (secondclass_G_M[i][j] == 'X')
            {
                if (j > 8)
                    printf("| %c | ", secondclass_G_M[i][j]); // for displaying X in correct format
                else
                    printf("| %c |", secondclass_G_M[i][j]);
            }
            else
                printf("  %d  ", secondclass_G_M[i][j]);
        }

        printf("\n");
        printf("                                       -----------------------------------------------------------------------------\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n\n\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------||ALL  EYES  THIS  WAY  PLEASE||------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void Booking_Tickets()
{

    int book_ticket_choice, no_of_tickets, count_temp_index = 0, no_ticket_left, result_seat_available; // count_temp is for char of seat selection index value
    char row_selection;                                                                                 // result_seat_availble is for checking if seat is already booked or not

    int seat_no_valid; // seat_no_valid is for checking seat number is valid or not

    printf("1. SELECT TICKETS\n2. BACK\n");

invalid_input_choice:
    scanf("%d", &book_ticket_choice);

    if (book_ticket_choice == 1)
    {
        printf("Enter the \"NUMBER OF TICKETS\" : ");

    invalid_tickets:

        scanf("%d", &no_of_tickets);

        if (no_of_tickets > 8)
        {
            printf("\n\nYou can book \"MAXIMUM OF 8 TICKETS\" only\n");
            printf("Select the \"NUMBER OF TICKETS AGAIN\" : ");
            goto invalid_tickets;
        }

        printf("\n\n");
        no_ticket_left = no_of_tickets;

        int chairs_of_seat_selection[no_of_tickets];

        fflush(stdin);

        printf("Select the \"SEAT NUMBER\" : \n");
        scanf("%c", &row_selection);

        if (row_selection > 96 && row_selection < 123)
            row_selection = row_selection - 32;

    verify_seats:

        if (no_ticket_left > 0)
        {

            while (no_ticket_left > 0)
            {
                scanf("%d", &chairs_of_seat_selection[count_temp_index]);

                // function call for verification of seat number is valid or not

                seat_no_valid = Valid_Seat_No_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index]);

                if (seat_no_valid == 0)
                {
                    printf("Enter \"VALID INPUT\" : \n");
                    fflush(stdin);
                    scanf("%c", &row_selection);

                    if (row_selection > 96 && row_selection < 123)
                        row_selection = row_selection - 32;

                    goto verify_seats;
                }

                switch (row_selection)
                {

                case 'A':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclassA[chairs_of_seat_selection[count_temp_index] - 1] = 'X';

                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'B':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclass_B_F[0][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'C':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclass_B_F[1][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'D':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclass_B_F[2][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'E':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclass_B_F[3][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'F':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        firstclass_B_F[4][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'G':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[0][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'H':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[1][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'I':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }
                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[2][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'J':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[3][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'K':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }
                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[4][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;
                        no_ticket_left--;
                    }
                    break;

                case 'L':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[5][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                case 'M':
                    result_seat_available = Seat_Is_Available_Or_Not(row_selection, chairs_of_seat_selection[count_temp_index] - 1);

                    if (result_seat_available == 0)
                    {
                        printf("This seat is \"ALREADY RESERVED\"\n");
                        printf("Choose \"ANOTHER SEAT\": \n");
                        fflush(stdin);
                        scanf("%c", &row_selection);

                        if (row_selection > 96 && row_selection < 123)
                            row_selection = row_selection - 32;

                        goto verify_seats;
                    }

                    else
                    {
                        create_CLL_for_unselection(row_selection, chairs_of_seat_selection[count_temp_index]);

                        secondclass_G_M[6][chairs_of_seat_selection[count_temp_index] - 1] = 'X';
                        count_temp_index++;

                        no_ticket_left--;
                    }
                    break;

                default:
                    printf("Enter the \"VALID INPUT\" : \n");
                }
                if (no_ticket_left > 0)
                {

                    fflush(stdin);
                    scanf("%c", &row_selection);

                    if (row_selection > 96 && row_selection < 123)
                        row_selection = row_selection - 32;

                    goto verify_seats;
                }
            }

            int res_change_tickets, res_proceed_r_back; // res_change_tickets is used for store the return value of change_tickets function

            if (no_ticket_left == 0)
            {
                system("cls"); // system cls

                display_booked_tickets();

                res_change_tickets = change_tickets();

            verifya1:

                system("cls"); // system cls

                if (res_change_tickets == 2)
                {
                    Display_Layout();
                    printf("1. PROCEED\n2. GO BACK\n");

                invalid_input_for_proceed:

                    scanf("%d", &res_proceed_r_back);

                    if (res_proceed_r_back == 1)
                    {
                        system("cls");
                        printf("1.WANT SNACKS\n");
                        printf("2.Go For Payment\n");

                        int want_snacks;
                    snacks_invalid:
                        scanf("%d", &want_snacks);
                        if (want_snacks == 1)
                        {
                            booking_snacks();
                        }
                        else if (want_snacks == 2)
                            // display_selected_snacks();
                            do_calulation();
                        else
                        {
                            printf("INVALID INPUT: ");
                            goto snacks_invalid;
                        }
                        // go for bill payment
                    }
                    else if (res_proceed_r_back == 2)
                    {
                        res_change_tickets = change_tickets();
                        goto verifya1;
                    }

                    else
                    {
                        printf("Enter \"VALID INPUT\" : \n");
                        goto invalid_input_for_proceed;
                    }
                }
                if (res_change_tickets == 1)
                {
                    count_temp_index--;
                    no_ticket_left++;
                    Display_Layout();
                    change_tickets_edit_layout();

                    printf("\nEnter \"NEW SEAT\" number : \n");
                    fflush(stdin);
                    scanf("%c", &row_selection);

                    if (row_selection > 96 && row_selection < 123)
                        row_selection = row_selection - 32;

                    goto verify_seats;
                }
            }
        }
    }
    else if (book_ticket_choice == 2)
    {
        system("cls");
        display_slots_dates();
        Display_Layout();
        Booking_Tickets();
    }

    else
    {
        printf("INVALID INPUT:\n");
        printf("Please Enter Correct Input: ");
        goto invalid_input_choice;
    }
}

// int Seat_Is_Available_Or_Not(char row_selection, int seat_number)
// {
//     switch (row_selection)
//     {
//     case 'A':
//         if (firstclassA[seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'B':
//         if (firstclass_B_F[0][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'C':
//         if (firstclass_B_F[1][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'D':
//         if (firstclass_B_F[2][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'E':
//         if (firstclass_B_F[3][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'F':
//         if (firstclass_B_F[4][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'G':
//         if (secondclass_G_M[0][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'H':
//         if (secondclass_G_M[1][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'I':
//         if (secondclass_G_M[2][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'J':
//         if (secondclass_G_M[3][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'K':
//         if (secondclass_G_M[4][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'L':
//         if (secondclass_G_M[5][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;

//     case 'M':
//         if (secondclass_G_M[6][seat_number] == 'X')
//             return 0;
//         else
//             return 1;
//         break;
//     }
// }
#define NUM_SEATS_PER_ROW 10

int Seat_Is_Available_Or_Not(char row_selection, int seat_number)
{
    int row_index;

    if (row_selection >= 'A' && row_selection <= 'F')
        row_index = row_selection - 'A';
    else if (row_selection >= 'G' && row_selection <= 'M')
        row_index = row_selection - 'G' + 6;
    else {
        // Invalid row selection
        return -1;
    }

    if (seat_number < 0 || seat_number >= NUM_SEATS_PER_ROW) {
        // Invalid seat number
        return -1;
    }

    if (row_selection <= 'F') {
        if (firstclass_B_F[row_index][seat_number] == 'X')
            return 0;
        else
            return 1;
    } else {
        if (secondclass_G_M[row_index][seat_number] == 'X')
            return 0;
        else
            return 1;
    }
}

int Valid_Seat_No_Or_Not(char row_selection, int seat_number)
{
    if (row_selection == 'A')
    {
        if (seat_number > 0 && seat_number < 27)
            return 1;
        else
            return 0;
    }
    else if (row_selection > 65 && row_selection < 71)
    {
        if (seat_number > 0 && seat_number < 21)
            return 1;
        else
            return 0;
    }
    else if (row_selection > 70 && row_selection < 78)
    {
        if (seat_number > 0 && seat_number < 15)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

void create_CLL_for_unselection(char row_selection, int seat_number)
{

    if (head_unselect == NULL)
    {
        head_unselect = (struct unselect *)malloc(sizeof(struct unselect));
        temp1 = head_unselect;
    }
    else
    {
        newnode = (struct unselect *)malloc(sizeof(struct unselect));
        temp1->next = newnode;
        newnode->prev = temp1;
        temp1 = newnode;
    }
    head_unselect->prev = temp1;
    temp1->next = head_unselect;

    temp1->row_unselect = row_selection;
    temp1->chair_number = seat_number;
}

void display_booked_tickets()
{
    struct unselect *temp;
    temp = head_unselect;
    printf("_____________________\n");
    printf("|                   |\n");
    printf("| Selected Tickets: |\n");
    printf("|___________________|\n");
    printf("|                   |\n");
    do
    {
        if (temp->chair_number < 10)
            printf("|       %c%d          |\n", temp->row_unselect, temp->chair_number);
        else
            printf("|      %c%d          |\n", temp->row_unselect, temp->chair_number);

        temp = temp->next;
    } while (temp != head_unselect);

    printf("|___________________|\n");
}

// int change_tickets()
// {
//     int change_choice;
//     printf("Do you want to CHANGE your seats?\n");
//     printf("1. CHANGE\n2. CONFIRM\n");
//     scanf("%d", &change_choice);
//     while (1)
//     {
//         if (change_choice == 1)
//         {
//             break;
//         }
//         else if (change_choice == 2)
//             return 2;
//         else
//         {
//             printf("Enter \"VALID INPUT\" : \n");
//             scanf("%d", &change_choice);
//         }
//     }
//     if (change_choice == 1)
//         return 1;
// }
int change_tickets() {
    int change_choice;
    printf("Do you want to CHANGE your seats?\n");
    printf("1. CHANGE\n2. CONFIRM\n");
    scanf("%d", &change_choice);

    // Loop until valid choice is made
    while (change_choice != 1 && change_choice != 2) {
        printf("Enter a valid input (1 or 2): \n");
        scanf("%d", &change_choice);
    }

    if (change_choice == 1)
        return 1;
    else // change_choice must be 2 here
        return 2;
}

void change_tickets_edit_layout()
{
    char temp_seat_row;
    int temp_seat_number;
    printf("Enter the SEAT NUMBER \"YOU WISH TO CHANGE\" : \n");

check_verify:

    fflush(stdin);
    scanf("%c", &temp_seat_row);

    if (temp_seat_row > 96 && temp_seat_row < 123)
        temp_seat_row = temp_seat_row - 32;

    scanf("%d", &temp_seat_number);

    struct unselect *temp = head_unselect;
    int temp_veify = 0;
    do
    {
        if (temp->chair_number == temp_seat_number && temp->row_unselect == temp_seat_row)
            temp_veify = 1;
        temp = temp->next;
    } while (temp != head_unselect);

    if (temp_veify == 0)
    {
        printf("Enter a \"VALID INPUT\" : \n");
        goto check_verify;
    }

    edit_CLL_for_unselection(temp_seat_row, temp_seat_number);

    switch (temp_seat_row)
    {
    case 'A':
        firstclassA[temp_seat_number - 1] = temp_seat_number;
        break;
    case 'B':
        firstclass_B_F[0][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'C':
        firstclass_B_F[1][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'D':
        firstclass_B_F[2][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'E':
        firstclass_B_F[3][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'F':
        firstclass_B_F[4][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'G':
        secondclass_G_M[0][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'H':
        secondclass_G_M[1][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'I':
        secondclass_G_M[2][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'J':
        secondclass_G_M[3][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'K':
        secondclass_G_M[4][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'L':
        secondclass_G_M[5][temp_seat_number - 1] = temp_seat_number;
        break;
    case 'M':
        secondclass_G_M[6][temp_seat_number - 1] = temp_seat_number;
        break;
    }
}

void edit_CLL_for_unselection(char row, int seatnumber)
{

    struct unselect *temp;
    temp = head_unselect;
    if (temp->chair_number == seatnumber && temp->row_unselect == row)
    {
        if (head_unselect->next == head_unselect)
        {
            head_unselect == NULL;
            free(temp);
        }
        else
        {
            temp->next->prev = head_unselect->prev;
            temp->prev->next = head_unselect->next;
            head_unselect = head_unselect->next;
            free(temp);
        }
    }
    else if (temp->prev->chair_number == seatnumber && temp->prev->row_unselect == row)
    {
        temp1 = temp1->prev;
        if (head_unselect->next == head_unselect)
        {
            head_unselect = NULL;
            free(temp);
        }
        else
        {
            temp = head_unselect->prev;
            head_unselect->prev = temp->prev;
            temp->prev->next = head_unselect;
            free(temp);
        }
    }
    else
    {

    check:
        while (temp->chair_number != seatnumber)
            temp = temp->next;
        if (temp->row_unselect != row)
        {
            temp = temp->next;
            goto check;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        free(temp);
    }
}

void title_of_project()
{
    system("cls");
    char ch;
    FILE *ptr = fopen("platform.txt", "r");

    while (ch != EOF)
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    }

    fclose(ptr);

    printf("\n\n");

    int check;
    printf("1.SELECT MOVIES\n2.EXIT\n");
verify:
    scanf("%d", &check);

    if (check < 1 && check > 2)
    {
        printf("\nIvalid Input:\n");
        printf("Please \"Enter Correct Input\":\n");
        goto verify;
    }

    if (check == 2)
        exit(0);

    system("cls");

    display_movie_details();
}

void display_movie_details()
{
    char ch = 0;
    FILE *ptr;
    ptr = fopen("movies_list.txt", "r");
    while (ch != EOF)
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    }
    fclose(ptr);

    int movies_list_choice;
    printf("\n");
invalid_choice:
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &movies_list_choice);

    if (movies_list_choice < 1 || movies_list_choice > 5)
    {
        printf("Invalid Input: \n");
        goto invalid_choice;
    }

    system("cls");

    FILE *ptr1;
    char temp_ch = 0;
    printf("\n");
    switch (movies_list_choice)
    {
    case 1:
        ptr1 = fopen("adipurush.txt", "r");
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(ptr1);
            printf("%c", temp_ch);
        }
        fclose(ptr1);
        strcpy(Movie_Name, "ADIPURUSH");
        break;
    case 2:
        ptr1 = fopen("gamechanger.txt", "r");
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(ptr1);
            printf("%c", temp_ch);
        }
        fclose(ptr1);
        strcpy(Movie_Name, "GAME CHANGER");
        break;
    case 3:
        ptr1 = fopen("fast_x.txt", "r");
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(ptr1);
            printf("%c", temp_ch);
        }
        fclose(ptr1);
        strcpy(Movie_Name, "FAST X");
        break;
    case 4:
        ptr1 = fopen("brahmastra.txt", "r");
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(ptr1);
            printf("%c", temp_ch);
        }
        fclose(ptr1);
        strcpy(Movie_Name, "BRAHMASTRA PART TWO:DEV");
        break;
    case 5:
        ptr1 = fopen("jailer.txt", "r");
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(ptr1);
            printf("%c", temp_ch);
        }
        fclose(ptr1);
        strcpy(Movie_Name, "JAILER");
        break;
    }
    printf("\n\n");

    int go_r_back;
    printf("1.BOOK TICKETS\n2.BACK\n3.EXIT\n");
input_invalid:
    scanf("%d", &go_r_back);

    if (go_r_back == 1)
        ;
    else if (go_r_back == 2)
    {
        system("cls");
        display_movie_details(); // ***************recursion is used in this line***************//
    }

    else if (go_r_back == 3)
    {
        exit(0);
    }

    else
    {
        printf("\nInvalid Input: \n");
        printf("Please Correct Input: \n");
        goto input_invalid;
    }

    system("cls");
    display_slots_dates();
}

void display_slots_dates()
{

    int k;
    char *charNames[] = {"ADIPURUSH", "GAME CHANGER", "FAST-X", "BRAHMASTRA PART TWO:DEV", "JAILER"};
    char *charmall[] = {"CINEPOLIS:PVP SQUARE MALL", "PVR:RIPPLES", "INOX:URVASI COMPLEX"};

    printf("_______________________________________________________________________\n");
    printf("|                                                                     |\n");
    printf("|                       THEATRES AVAILABLE:                           |\n");
    printf("|---------------------------------------------------------------------|\n");
    printf("|                   1-CINEPOLIS:PVP SQUARE MALL                       |\n");
    printf("|                   2-PVR:RIPPLES                                     |\n");
    printf("|                   3-INOX:URVASI COMPLEX                             |\n");
    printf("|_____________________________________________________________________|\n\n");

invalid_mall:
    printf("Enter Choice: ");
    scanf("%d", &k);
    if (k > 0 && k <= sizeof(charmall) / sizeof(charmall[0]))
        ;
    else
    {
        printf("INVALID INPUT: \n");
        goto invalid_mall;
    }

    time_t today;
    struct tm *date_info;
    char dates[3][DATE_LENGTH]; // dates array is used to display today date and next consequtive two dates
    int p, slotNumber;          // p is used to scan the date choice
    today = time(NULL);
    for (int i = 0; i < 3; i++)
    {
        date_info = localtime(&today);
        date_info->tm_mday += i;
        mktime(date_info);
        strftime(dates[i], DATE_LENGTH, "%d-%m-%y", date_info);
    }
k:

    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s\n", i + 1, dates[i]);
    }
    printf("SELECT THE DATE: ");
    scanf("%d", &p);
    if (p < 1 || p > 3)
    {
        printf("Invalid position!\n");
        goto k;
    }
    else
    {
        strcpy(Booking_Date, dates[p - 1]);
    }

    system("cls");

    bool slots[SLOT_COUNT][3] = {{false, false, false}, {false, false, false}, {false, false, false}};

    printf("_______________________________________________________________________________________________________________________________________________\n");
    printf("|                                                                                                                                             |\n");
    printf("|---------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("| %s                                                                                                                                    |\n", dates[p - 1]);

    switch (k)
    {
    case 1:
        printf("| CINEPOLIS:PVP SQUARE MALL                                                                                                                   |\n");
        strcpy(Teatre_Name, "CINEPOLIS:PVP SQUARE MALL");
        break;
    case 2:
        printf("| PVR:RIPPLES                                                                                                                                 |\n");
        strcpy(Teatre_Name, "PVR:RIPPLES");
        break;
    case 3:
        printf("| INOX:URVASI COMPLEX                                                                                                                         |\n");
        strcpy(Teatre_Name, "INOX:URVASI COMPLEX");
        break;
    }
    printf("|---------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                                                                             |\n");

    printf("|                                                  ------------------              ------------------              ------------------         |\n");
    printf("|                                                  |slot--1: 10:00 AM|             |slot--2: 2:00 PM|              |slot--3: 6:00 PM|         |\n");
    printf("|                                                  -------------------             ------------------              ------------------         |\n");
    printf("|_____________________________________________________________________________________________________________________________________________|\n\n");
s:
    printf("Enter SLOT:");
    scanf("%d", &slotNumber);
    if (slotNumber < 1 || slotNumber > SLOT_COUNT)
    {
        printf("Invalid slot number!\n");
        goto s;
    }

    switch (slotNumber)
    {
    case 1:
        strcpy(Booking_Time, "10:00 AM");
        break;
    case 2:
        strcpy(Booking_Time, "02:00 PM");
        break;
    case 3:
        strcpy(Booking_Time, "06:00 PM");
    }
    int selectedDay = p - 1;
    int selectedSlot = slotNumber - 1;
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int currentHour = localTime->tm_hour;
    if (p == 1 && currentHour >= 10 && selectedSlot == 0)
    {
        system("cls");
        printf("Sorry, Slot-1 time has exceeded for Day %s.\n", dates[p - 1]);
        printf("Please choose another slot.\n");
        goto k;
    }
    else if (p == 1 && currentHour >= 14 && selectedSlot == 1)
    {
        system("cls");
        printf("Sorry, Slot-2 time has exceeded on %s.\n", dates[p - 1]);
        printf("Please choose another slot.\n");
        goto k;
    }
    else if (p == 1 && currentHour >= 18 && selectedSlot == 2)
    {
        system("cls");
        printf("Sorry, Slot-3 time has exceeded on %s.\n", dates[p - 1]);
        printf("Please choose another slot.\n");
        goto k;
    }
    else
    {
        if (slots[selectedDay][selectedSlot])
        {
            printf("Sorry, Slot-%d is already booked on %s.\n", slotNumber, dates[p - 1]);
        }
        else
        {
            slots[selectedDay][selectedSlot] = true;
            printf("Slot:-%d is booked on %s\n", slotNumber, dates[p - 1]);
        }
    }

    system("cls");
}

void display_snacks()
{
    system("cls");
    FILE *ptr = fopen("snacks.txt", "r");
    char ch = 0;
    while (ch != EOF)
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    }
    printf("\n");
}

void booking_snacks()
{
    system("cls");
    display_snacks();
    char food_code;
    int food, qua;

invalid_food:
    printf("Enter The item: ");

    fflush(stdin);
    scanf("%c", &food_code);

    if (food_code > 96 && food_code < 123)
        food_code = food_code - 32;

    scanf("%d", &food);

    if (food_code == 'P' || food_code == 'S' || food_code == 'D')
    {
        switch (food_code)
        {
        case 'P':
            if (food > 0 && food < 7)
                ;
            else
            {
                printf("\nIvalid Food item: \n");
                goto invalid_food;
            }
            break;
        case 'S':
            if (food > 0 && food < 7)
                ;
            else
            {
                printf("\nIvalid Food item: \n");
                goto invalid_food;
            }
            break;

        case 'D':
            if (food > 0 && food < 5)
                ;
            else
            {
                printf("\nIvalid Food item: \n");
                goto invalid_food;
            }
            break;
        }
    }
    else
    {
        printf("\nInvalid Food Item:\n");
        goto invalid_food;
    }

    int res_food_already_present_r_no = check_doubly_adding_snacks(food_code, food);

    if (res_food_already_present_r_no == 0)
    {
        system("cls");
        goto verify_food;
    }
    printf("Enter quantity: ");
    scanf("%d", &qua);

    system("cls");

    create_linked_list_for_snacks(food_code, food, qua);
    calculate_amount_for_snacks(food_code, food, qua);

verify_food:
    display_selected_snacks();
    after_selecting_one_snack();
}

void create_linked_list_for_snacks(char food_code, int food, int qua)
{
    if (sna_head == NULL)
    {
        sna_head = (struct snacks *)malloc(sizeof(struct snacks));
        temporary1 = sna_head;
    }
    else
    {
        newnode1 = (struct snacks *)malloc(sizeof(struct snacks));
        temporary1->rnext = newnode1;
        newnode1->lnext = temporary1;
        temporary1 = newnode1;
    }
    temporary1->cat_type = food_code;
    temporary1->food_item = food;
    temporary1->quantity = qua;

    temporary1->rnext = sna_head;
    sna_head->lnext = temporary1;
}

void do_calulation()
{
    int subtotal2 = 0;
    struct snacks *temporary2 = sna_head;
    int tickets_amount = calculate_ticket_amount();

    int convenience_fee = 15 * calculate_number_0f_tickets();

    if (sna_head != NULL)
    {
        do
        {
            subtotal2 += temporary2->price;
            temporary2 = temporary2->rnext;
        } while (temporary2 != sna_head);
    }

    system("cls");
    loading_animation();

    display_final_bill(tickets_amount, convenience_fee, subtotal2);
}

void display_selected_snacks()
{
    int subtotal2 = 0;
    struct snacks *temporary2 = sna_head;
    int tickets_amount = calculate_ticket_amount();
    struct unselect *temp = head_unselect;
    int convenience_fee = 15 * calculate_number_0f_tickets();
    int sub_total_1 = tickets_amount + convenience_fee;
    printf("\n\n");

    printf("____________________________________________________\n");
    printf("|                                                  |\n");
    printf("|                BOOKING SUMMARY                   |\n");
    printf("|__________________________________________________|\n");
    do
    {
        if (temp->chair_number > 9)
            printf("| %c%d                                              |\n", temp->row_unselect, temp->chair_number);
        else
            printf("| %c%d                                               |\n", temp->row_unselect, temp->chair_number);
        temp = temp->next;
    } while (temp != head_unselect);
    if (tickets_amount < 1000)
        printf("|(%d TICKETS)                               Rs.%d  |\n", calculate_number_0f_tickets(), tickets_amount);
    else
        printf("|(%d TICKETS)                               Rs.%d |\n", calculate_number_0f_tickets(), tickets_amount);
    if (convenience_fee < 100)
        printf("| Convenience Fees                         Rs.%d   |\n", convenience_fee);
    else
        printf("| Convenience Fees                         Rs.%d  |\n", convenience_fee);

    printf("|__________________________________________________|\n");
    printf("|                                                  |\n");

    if (sna_head == NULL)
    {
        if (sub_total_1 < 1000)
            printf("| SUB TOTAL                                Rs.%d  |\n", sub_total_1);
        else
            printf("| SUB TOTAL                                Rs.%d |\n", sub_total_1);

        printf("|__________________________________________________|\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");

        if (sub_total_1 + subtotal2 < 1000)
            printf("| AMOUNT PAYABLE                           Rs.%d  |\n", sub_total_1 + subtotal2);
        else
            printf("| AMOUNT PAYABLE                           Rs.%d |\n", sub_total_1 + subtotal2);

        printf("|__________________________________________________|\n");
    }

    else
    {

        if (sub_total_1 < 1000)
            printf("| SUB TOTAL-1                              Rs.%d  |\n", sub_total_1);
        else
            printf("| SUB TOTAL-1                              Rs.%d |\n", sub_total_1);

        printf("|__________________________________________________|\n");

        printf("|                                                  |\n");
        printf("|               FOOD & BEVERAGES                   |\n");
        printf("|__________________________________________________|\n");
        printf("|                                                  |\n");

        do
        {
            switch (temporary2->cat_type)
            {
            case 'P':
                switch (temporary2->food_item)
                {

                case 1:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Large Flavored Popcorn(Qt. %d)        Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Large Flavored Popcorn(Qt. %d)        Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 2:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Large Salted Popcorn(Qt. %d)          Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Large Salted Popcorn(Qt. %d)          Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 3:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Medium  Flavoured Popcorn(Qt. %d)     Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Medium  Flavoured Popcorn(Qt. %d)     Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 4:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Medium Salted Popcorn(Qt. %d)         Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Medium Salted Popcorn(Qt. %d)         Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 5:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Small Caramel Popcorn(Qt. %d)         Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Small Caramel Popcorn(Qt. %d)         Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 6:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Small Salted Popcorn(Qt. %d)          Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Small Salted Popcorn(Qt. %d)          Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;
                }
                break;
            case 'S':
                switch (temporary2->food_item)
                {
                case 1:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Loaded Fries(Qt. %d)                  Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Loaded Fries(Qt. %d)                  Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 2:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Cheese Paneer Burger(Qt. %d)          Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Cheese Paneer Burger(Qt. %d)          Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 3:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Veggie Momos(Qt. %d)                  Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Veggie Momos(Qt. %d)                  Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 4:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Margherita Pizza(Qt. %d)              Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Margherita Pizza(Qt. %d)              Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 5:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Classic Chicken Pizza(Qt. %d)         Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Classic Chicken Pizza(Qt. %d)         Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;
                case 6:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Jalapeno Nachos(Qt. %d)               Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Jalapeno Nachos(Qt. %d)               Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;
                }
                break;
            case 'D':
                switch (temporary2->food_item)
                {
                case 1:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Cappuccino(Qt. %d)                    Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Cappuccino(Qt. %d)                    Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 2:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Coke 440 ml(Qt. %d)                   Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Coke 440 ml(Qt. %d)                   Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 3:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Thumbs Up 500 ml(Qt. %d)              Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Thumbs Up 500 ml(Qt. %d)              Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;

                case 4:
                    if (temporary2->price < 1000)
                        printf("| (%c%d)Redbull 330 ml(Qt. %d)                Rs.%d  |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    else
                        printf("| (%c%d)Redbull 330 ml(Qt. %d)                Rs.%d |\n", temporary2->cat_type, temporary2->food_item, temporary2->quantity, temporary2->price);
                    break;
                }
                break;
            }
            subtotal2 += temporary2->price;
            temporary2 = temporary2->rnext;
        } while (temporary2 != sna_head);
        printf("|__________________________________________________|\n");
        printf("|                                                  |\n");
        if (subtotal2 < 1000)
            printf("| SUB TOTAL-2                              Rs.%d  |\n", subtotal2);
        else
            printf("| SUB TOTAL-2                              Rs.%d |\n", subtotal2);
        printf("|__________________________________________________|\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");
        if (sub_total_1 + subtotal2 < 1000)
            printf("| AMOUNT PAYABLE                           Rs.%d  |\n", sub_total_1 + subtotal2);
        else
            printf("| AMOUNT PAYABLE                           Rs.%d |\n", sub_total_1 + subtotal2);

        printf("|__________________________________________________|\n");
    }
}

void after_selecting_one_snack()
{

    int choice;
    printf("\n1.Add items\n2.Edit items\n3.Go For Payment\n");
verify:
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("\nEnter a valid input:\n");
        goto verify;
    }

    switch (choice)
    {
    case 1:

        booking_snacks();
        break;
    case 2:
        system("cls");
        display_selected_snacks();
        edit_snacks();
        break;
    case 3: // Bill

        system("cls");
        do_calulation();

        break;
    }
}

void calculate_amount_for_snacks(char food_code, int food, int qua)
{
    switch (food_code)
    {
    case 'P':
        switch (food)
        {
        case 1:
            temporary1->price = qua * 399;
            break;
        case 2:
            temporary1->price = qua * 349;
            break;
        case 3:
            temporary1->price = qua * 379;
            break;
        case 4:
            temporary1->price = qua * 349;
            break;
        case 5:
            temporary1->price = qua * 379;
            break;
        case 6:
            temporary1->price = qua * 339;
            break;
        }
        break;

    case 'S':
        switch (food)
        {
        case 1:
            temporary1->price = qua * 119;
            break;
        case 2:
            temporary1->price = qua * 199;
            break;
        case 3:
            temporary1->price = qua * 139;
            break;
        case 4:
            temporary1->price = qua * 219;
            break;
        case 5:
            temporary1->price = qua * 299;
            break;
        case 6:
            temporary1->price = qua * 249;
            break;
        }
        break;

    case 'D':
        switch (food)
        {
        case 1:
            temporary1->price = qua * 119;
            break;
        case 2:
            temporary1->price = qua * 199;
            break;
        case 3:
            temporary1->price = qua * 249;
            break;
        case 4:
            temporary1->price = qua * 179;
            break;
        }
        break;
    }
}

void edit_snacks()
{
    int choice;
    printf("\n1.Remove item\n2.Change Quantity\n3.Back\n");

verify:
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("\nEnter a valid input:\n");
        goto verify;
    }
    switch (choice)
    {

    case 1:
        remove_snack_item();
        system("cls");
        display_selected_snacks();
        after_selecting_one_snack();
        break;
    case 2:
        system("cls");
        display_selected_snacks();
        change_quantity();
        system("cls");
        display_selected_snacks();
        after_selecting_one_snack();
        break;
    case 3:
        after_selecting_one_snack();
        break;
    }
}

void remove_snack_item()
{
    char food_code;
    int food;

    printf("\n\n");
invalid_input1:

    printf("Enter the SNACK \"YOU WISH TO REMOVE\" : ");
    fflush(stdin);
    scanf("%c", &food_code);

    if (food_code > 96 && food_code < 123)
        food_code = food_code - 32;

    scanf("%d", &food);

    int verify = 0;
    struct snacks *temporary2 = sna_head;

    do
    {
        if (temporary2->cat_type == food_code && temporary2->food_item == food)
            verify = 1;

        temporary2 = temporary2->rnext;
    } while (temporary2 != sna_head);

    if (verify == 0)
    {
        printf("\nInvalid Input: \n");
        goto invalid_input1;
    }

    struct snacks *temporary3;
    temporary3 = sna_head;
    if (temporary3->food_item == food && temporary3->cat_type == food_code)
    {
        if (sna_head->rnext == sna_head)
        {
            sna_head == NULL;
            free(temporary3);
        }
        else
        {
            temporary3->rnext->lnext = sna_head->lnext;
            temporary3->lnext->rnext = sna_head->rnext;
            sna_head = sna_head->rnext;
            free(temporary3);
        }
    }
    else if (temporary3->lnext->food_item == food && temporary3->lnext->cat_type == food_code)
    {
        temporary3 = temporary3->lnext;

        temporary1 = temporary1->lnext;

        if (sna_head->rnext == sna_head)
        {
            sna_head = NULL;
            free(temporary3);
        }
        else
        {
            temporary3 = sna_head->lnext;
            sna_head->lnext = temporary3->lnext;
            temporary3->lnext->rnext = sna_head;
            free(temporary3);
        }
    }
    else
    {

    check:
        while (temporary3->food_item != food)
            temporary3 = temporary3->rnext;
        if (temporary3->cat_type != food_code)
        {
            temporary3 = temporary3->rnext;
            goto check;
        }

        temporary3->lnext->rnext = temporary3->rnext;
        temporary3->rnext->lnext = temporary3->lnext;

        free(temporary3);
    }
}

void change_quantity()
{

    char food_code;
    int food, qua;

    printf("\n\n");
invalid_input1:

    printf("Enter the \"SNACK YOU WISH TO CHANGE THE QUANTITY\": ");

    fflush(stdin);
    scanf("%c", &food_code);

    if (food_code > 96 && food_code < 123)
        food_code = food_code - 32;

    scanf("%d", &food);

    int verify = 0;
    struct snacks *temporary2 = sna_head;

    do
    {
        if (temporary2->cat_type == food_code && temporary2->food_item == food)
        {
            verify = 1;
            break;
        }

        temporary2 = temporary2->rnext;
    } while (temporary2 != sna_head);

    if (verify == 0)
    {
        printf("\nInvalid Input: \n");
        goto invalid_input1;
    }

    printf("Enter the new quantity: ");
    scanf("%d", &qua);

    temporary2->quantity = qua;

    switch (food_code)
    {
    case 'P':
        switch (food)
        {
        case 1:
            temporary2->price = qua * 399;
            break;
        case 2:
            temporary2->price = qua * 349;
            break;
        case 3:
            temporary2->price = qua * 379;
            break;
        case 4:
            temporary2->price = qua * 349;
            break;
        case 5:
            temporary2->price = qua * 379;
            break;
        case 6:
            temporary2->price = qua * 339;
            break;
        }
        break;

    case 'S':
        switch (food)
        {
        case 1:
            temporary2->price = qua * 119;
            break;
        case 2:
            temporary2->price = qua * 199;
            break;
        case 3:
            temporary2->price = qua * 139;
            break;
        case 4:
            temporary2->price = qua * 219;
            break;
        case 5:
            temporary2->price = qua * 299;
            break;
        case 6:
            temporary2->price = qua * 249;
            break;
        }
        break;

    case 'D':
        switch (food)
        {
        case 1:
            temporary2->price = qua * 119;
            break;
        case 2:
            temporary2->price = qua * 199;
            break;
        case 3:
            temporary2->price = qua * 249;
            break;
        case 4:
            temporary2->price = qua * 179;
            break;
        }
        break;
    }
}

int check_doubly_adding_snacks(char food_code, int food)
{

    struct snacks *temporary2 = sna_head;
    int verify = 1;
    if (sna_head == NULL)
        return 1;
    else
    {
        do
        {
            if (temporary2->cat_type == food_code && temporary2->food_item == food)
            {
                temporary2->price = temporary2->price / temporary2->quantity;
                temporary2->quantity++;
                temporary2->price = temporary2->price * temporary2->quantity;
                verify = 0;
                break;
            }
            temporary2 = temporary2->rnext;
        } while (temporary2 != sna_head);
    }

    return verify;
}

int calculate_ticket_amount()
{
    struct unselect *temp = head_unselect;
    int sum = 0;
    do
    {

        if (temp->row_unselect >= 65 && temp->row_unselect <= 70)
        {
            sum = sum + 210;
        }
        else
            sum = sum + 170;

        temp = temp->next;
    } while (temp != head_unselect);

    return sum;
}

int calculate_number_0f_tickets()
{
    struct unselect *temp = head_unselect;
    int count = 0;
    do
    {
        temp = temp->next;
        count++;
    } while (temp != head_unselect);

    return count;
}

void display_final_bill(int total_amount, int convi_fee, int food)
{
    system("cls");
    printf("____________________________________________________________\n");
    printf("|                                                          |\n");
    printf("|                   TRENDY TICKETS                         |\n");
    printf("|            Your Booking Is Confirmed!                    |\n");
    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");
    if (Movie_Name[0] == 'A')
        printf("| %s                                                |\n", Movie_Name);
    else if (Movie_Name[0] == 'G')
        printf("| %s                                             |\n", Movie_Name);
    else if (Movie_Name[0] == 'F')
        printf("| %s                                                   |\n", Movie_Name);
    else if (Movie_Name[0] == 'B')
        printf("| %s                                  |\n", Movie_Name);
    else
        printf("| %s                                                   |\n", Movie_Name);
    printf("| %s                                                 |\n", Booking_Date);
    printf("| %s                                                 |\n", Booking_Time);
    if (Teatre_Name[0] == 'C')
        printf("| %s                                |\n", Teatre_Name);
    else if (Teatre_Name[0] == 'P')
        printf("| %s                                              |\n", Teatre_Name);
    else
        printf("| %s                                      |\n", Teatre_Name);

    struct unselect *temp = head_unselect;

    do
    {
        if (temp->chair_number > 9)
            printf("| %c%d                                                      |\n", temp->row_unselect, temp->chair_number);
        else
            printf("| %c%d                                                       |\n", temp->row_unselect, temp->chair_number);
        temp = temp->next;
    } while (temp != head_unselect);

    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");
    printf("|                TRENDY TICKETS VERIFIED!                  |\n");
    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");
    printf("| ORDER SUMMARY:                                           |\n");
    printf("|                                                          |\n");
    if (total_amount < 1000)
        printf("| TOTAL AMOUNT                                    Rs.%d   |\n", total_amount);
    else
        printf("| TOTAL AMOUNT                                    Rs.%d  |\n", total_amount);

    if (convi_fee < 100)
        printf("| CONVENIENCE FEES                                Rs.%d    |\n", convi_fee);
    else
        printf("| CONVENIENCE FEES                                Rs.%d   |\n", convi_fee);

    if (food == 0)
        printf("| BEVARAGES                                       Rs.%d     |\n", food);
    else if (food < 1000)
        printf("| BEVARAGES                                       Rs.%d   |\n", food);
    else
        printf("| BEVARAGES                                       Rs.%d  |\n", food);

    int a = total_amount + convi_fee + food;

    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");
    if ((a) < 1000)
        printf("| AMOUNT PAID                                     Rs.%d   |\n", a);
    else
        printf("| AMOUNT PAID                                     Rs.%d  |\n", a);
    printf("|__________________________________________________________|\n");

    printf("\n\n");

    char ch = 0;
    FILE *ptr = fopen("ending.txt", "r");

    while (ch != EOF)
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    }

    fclose(ptr);
}

// void loading_animation()
// {

//     for (int i = 0; i < 4; i++)
//     {

//         printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPlease Wait");
//         for (int j = 0; j < 5; j++)
//         {
//             printf(" . ");
//             Sleep(300);
//         }
//         system("cls");
//     }
// }
void loading_animation()
{
    for (int i = 0; i < 4; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPlease Wait");
        fflush(stdout); // Flush the output buffer to ensure immediate printing

        for (int j = 0; j < 5; j++)
        {
            printf(" . ");
            fflush(stdout); // Flush the output buffer again

            // Sleep for 300 milliseconds
            sleep(1); // sleep function uses seconds, so sleep for 1 second instead of 300 milliseconds
        }
system("cls");
        // Clear the screen using ANSI escape codes
        printf("\033[H\033[J");
    }
}
