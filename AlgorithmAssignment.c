/*
    TU856 / 1 - ALGORITHM DESIGN AND PROBLEM SOLVING: CMPU1001 ASSIGNMENT

    Author: Paulina Czarnota C21365726

    Submission Date: 22/04/2022

    Program Description: This C program consists of 4 teams of pharmaceutical company employees with their team membership details and line certifications.

    This program is menu-driven and provides 4 following functions: 
    
        1. Sorts each team by surname using merge sort then combines the 4 teams of employees into one array. Displays each team separately. Sorts each team with merge sort. Merges the 4 teams into one array. Displays full list of employees.

        2. Prints a list of employees certified for all 3 lines.

        3. Searches employees by surname.

        4. Exits the program.

    The data in the program is structured with 4 arrays which represent 4 teams of 6 employees. Each employee contains details such as employee id, first name, surname and work line. A separate array contains the line certifications of each employee. The line certifications consist of employee id and line certification.
               
    Data consists of:
    
        Employee ID, First Name, Surname, Line

        Team 1:

            8, Ryuhei, Matsuda, 1
            3, Hiroshi, Abe, 1
            7, Toma, Ikuta, 3
            1, Namie, Amuro, 2
            4, Hikaru, Utada, 3
            19, Maaya, Sakamoto, 2

        Team 2:

            14, Nanase, Aikawa, 1
            23, Tatsuya, Fujiwara, 1
            5, Hiroyuki, Sanada, 1
            11, Yui, Asaka, 1
            10, Saori, Atsumi, 2
            6, Takuya, Kimura, 0

        Team 3:

            20, Kanata, Hongo, 1
            2, Mika, Nakashima, 0
            22, Yoko, Ono, 1
            18, Kiyoshi, Atsumi, 1
            24, Yusaku, Matsuda, 2
            15, Kyoko, Fukada, 0

        Team 4:

            17, Miyoshi, Umeki, 3
            16, Ryusei, Yokohama, 2
            12, Jun, Matsumoto, 3
            13, Kento, Yamazaki, 1
            9, Yui, Aragaki, 1
            21, Yuko, Aoki, 2

        Certifications:
        
            Employee ID, Earned Certification ID

            Employees:

                8, 3
                3, 7
                7, 4
                1, 5
                4, 5
                19, 5
                14, 3
                23, 7
                5, 0
                11, 1
                10, 4
                6, 3
                20, 2
                2, 2
                22, 5
                18, 2
                24, 7
                15, 2
                17, 2
                16, 7
                12, 4
                13, 0
                9, 6
                21, 1
*/


// The libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbolic names
#define Number_Teams 4 // Number of teams
#define Number_Team_Members 6 // Number of employees in each team
#define Number_Certs 24 // Number of certifications

// Character and structure templates
typedef char String[30];
typedef struct Employees_Records
{
    int employeeID;
    String firstName;
    String surname;
    int workLine;
} Employees_Records;
typedef struct Certifications
{
    int employeeID;
    int certID;
} Certifications;

// The function signatures
void EmployeeList(struct Employees_Records *employeeList, int size);
void SortEmployees(struct Employees_Records *employeeList, int start, int end);
void MergeEmployees(struct Employees_Records *employeeList, int start, int mid, int end);
void CombineTeams(struct Employees_Records *teams[], struct Employees_Records *employeeList, int numberTeamMember, int numberTeam);
int SearchSurname(struct Employees_Records *employeeList, String key, int start, int end);

// The option functions
void ProcessTeams(struct Employees_Records *teams[], struct Employees_Records *employeeList, int numberTeamMember, int numberTeam);
void FullCerts(struct Employees_Records *employeeList);
void GetEmployeeBySurname(struct Employees_Records *employeeList, int count);

// The global varables: g_ 

// Team 1 with 6 employees 
struct Employees_Records g_Team1[Number_Team_Members] = 
{
    {8, "Ryuhei", "Matsuda", 1}, {3, "Hiroshi", "Abe", 1}, {7, "Toma", "Ikuta", 3}, {1, "Namie", "Amuro", 2}, {4, "Hikaru", "Utada", 3}, {19, "Maaya", "Sakamoto", 2}
};

// Team 2 with 6 employees 
struct Employees_Records g_Team2[Number_Team_Members] = 
{
    {14, "Nanase", "Aikawa", 1}, {23, "Tatsuya", "Fujiwara", 1}, {5, "Hiroyuki", "Sanada", 1}, {11, "Yui", "Asaka", 1}, {10, "Saori", "Atsumi", 2}, {6, "Takuya", "Kimura", 0}
};

// Team 3 with 6 employees 
struct Employees_Records g_Team3[Number_Team_Members] = 
{
    {20, "Kanata", "Hongo", 1}, {2, "Mika", "Nakashima", 0}, {22, "Yoko", "Ono", 1}, {18, "Kiyoshi", "Atsumi", 1}, {24, "Yusaku", "Matsuda", 2}, {15, "Kyoko", "Fukada", 0}
};

// Team 4 with 6 employees 
struct Employees_Records g_Team4[Number_Team_Members] = 
{
    {17, "Miyoshi", "Umeki", 3}, {16, "Ryusei", "Yokohama", 2}, {12, "Jun", "Matsumoto", 3}, {13, "Kento", "Yamazaki", 1}, {9, "Yui", "Aragaki", 1}, {21, "Yuko", "Aoki", 2}
};
    
// The certifications
struct Certifications g_Certifications[] =
{
    {8, 3}, {3, 7}, {7, 4}, {1, 5}, {4, 5}, {19, 5}, {14, 3}, {23, 7}, {5, 0}, {11, 1}, {10, 4}, {6, 3}, {20, 2}, {2, 2}, {22, 5}, {18, 2}, {24, 7}, {15, 2}, {17, 2}, {16, 7}, {12, 4}, {13, 0}, {9, 6}, {21, 1}
};

struct Employees_Records g_TeamsCombined[Number_Teams * Number_Team_Members];


int main()
{   
    // The main variables
    int userInput;
    int sortSurname = 0;
    int employeeCount = Number_Team_Members * Number_Teams;

    // The program name
    printf("\n\n\t\t The Employee Certification Program \n");
   
    // Loop - it stops when user enters option 4
    while (userInput != 4)
    {
        // The main menu 
        printf("\n ________________________________________________________________________________");
        printf("\n\n Main Menu \n\n");
        printf("(1) Sort the teams by surname and combine the teams \n");
        printf("(2) Display a list of the employees certified to work on all three lines \n");
        printf("(3) Search for a specific employee by surname \n");
        printf("(4) Exit program \n");
        printf("____________________________________________________________________________________\n\n");
        printf("\n Please select one of the above options from the menu \n");
        printf("\n > ");
        userInput = 0;
        scanf("%d", &userInput);

        while (getchar() != '\n');

        // Switch on user input
        switch (userInput)
        {
            case 1:
            {
                printf("Sorting the teams by surname and then combining the teams...\n");
                
                // Array of teams
                Employees_Records *teams[Number_Teams] = {g_Team1, g_Team2, g_Team3, g_Team4};
                
                // Print, sort, combine the teams and then print combined teams
                ProcessTeams(teams, g_TeamsCombined, Number_Team_Members, Number_Teams);

                sortSurname = 1;
         
                break;
            }
            case 2:
            {
                // Check if teams have been sorted, option 1 must be selected first
                if (sortSurname == 0)
                {
                    printf("Please select option 1 first.\n");

                    break;
                }

                printf("List of employees with certification to work on all three lines...\n");
             

                // Print all employees with all certifications
                FullCerts(g_TeamsCombined);

                break;
            }
            case 3:
            {
                // Check if teams have been sorted, option 1 must be selected first
                if(sortSurname == 0)
                {
                    printf("Please select option 1 first.\n");

                    break;
                }

                printf("Search for the employee's surname...\n\n");
                printf("ALERT! Please enter the surname with upper case! \n");

                // Search for employee by surname
                GetEmployeeBySurname(g_TeamsCombined, employeeCount);

                break;
            }
            case 4:
            {
                // Exit program
                printf("\nExiting program...\n");

                break;
            }
            default:
            {
                // Invalid input
                printf("\n\aInvalid input. Please try again.\n");

                break;
            }
        }
    }
}

// Utility functions
// Prints details of each employees in a array
// Params: employeeList[] - list of employees to print
// count - number of employees in array
void EmployeeList(struct Employees_Records *employeeList, int size)
{
    // Prints employee list
    printf("%-11s  %-12s  %-12s  %-4s\n", "Employee ID", "First Name", "Surname", "Work Line");
    
    for (int i = 0; i < size; i++)
    {
        printf("%11d  %-12s  %-12s  %4d\n", employeeList[i].employeeID, employeeList[i].firstName, employeeList[i].surname, employeeList[i].workLine);
    }
    printf("\n");
}

// Sorts employees in a array using modified merge sort
// Base case is reached when array size is less than 5 then insertion sort is used
// Params: employeeList[] - array of employees to sort
// start - starting index of array
// end - ending index of array
void SortEmployees(struct Employees_Records *employeeList, int start, int end)
{
    // Base case when start and end are the same
    if (start + 5 < end)
    {
        // Recursive case
        int mid = start + (end - start) / 2;
        SortEmployees(employeeList, start, mid);
        SortEmployees(employeeList, mid + 1, end);
        MergeEmployees(employeeList, start, mid, end);
    }
    else
    {
        // Base case
        // Insertion sort
        for (int i = start + 1; i <= end; i++)
        {
            Employees_Records key = employeeList[i];
            int j = i - 1;
            while (j >= start && strcmp(employeeList[j].surname, key.surname) > 0)
            {
                employeeList[j + 1] = employeeList[j];
                j--;
            }
            employeeList[j + 1] = key;
        }
    }
}

// Merges two sorted subarray into one sorted array
// Params: employeeList[] - array of employees to sort
// start - starting index of first subarray
// mid - ending index of first subarray
// end - ending index of second subarray
void MergeEmployees(struct Employees_Records *employeeList, int start, int mid, int end)
{
    // Create two temp arrays
    int nL = mid - start + 1;
    int nR = end - mid;
    Employees_Records *tempL = (Employees_Records *)malloc(sizeof(Employees_Records) * nL);
    Employees_Records *tempR = (Employees_Records *)malloc(sizeof(Employees_Records) * nR);

    // Copy elements from original array to temp arrays
    for (int i = 0; i < nL; i++)
    {
        tempL[i] = employeeList[start + i];
    }
    for (int i = 0; i < nR; i++)
    {
        tempR[i] = employeeList[mid + 1 + i];
    }

    // Merge temp arrays into original array
    int i = start, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (strcmp(tempL[j].surname, tempR[k].surname) < 0)
        {
            employeeList[i++] = tempL[j++];
        }
        else
        {
            employeeList[i++] = tempR[k++];
        }
    }

    // Copy remaining elements from temp arrays
    while (j < nL)
    {
        employeeList[i++] = tempL[j++];
    }
    while (k < nR)
    {
        employeeList[i++] = tempR[k++];
    }
    
}

// Combine sorted teams into one sorted array
// Params: *teams[] - array of teams to combine
// employeeList[] - array of employees
// teamMemberCount - number of members in each team
// teamCount - number of teams
void CombineTeams(struct Employees_Records *teams[], struct Employees_Records *employeeList, int teamMemberCount, int teamCount)
{
    int combinedSize = teamCount * teamMemberCount;
    // Concatenate teams into one array
    for (int i = 0; i < teamCount; i++)
    {
        for (int j = 0; j < teamMemberCount; j++)
        {
            employeeList[i * teamMemberCount + j] = teams[i][j];
        }
    }
    // Merge employeeList
    for (int i = 0; i < teamCount - 1; i++)
    {
        MergeEmployees(employeeList, 0, (i + 1) * teamMemberCount - 1, (i + 2) * teamMemberCount - 1);
    }

}

// Search employee list by surname
// Params: employeeList[] - array of employees to search
// key - surname to search for
// start - starting index of array
// end - ending index of array
// Return: index of employee if found, -1 if not found
int SearchSurname(struct Employees_Records *employeeList, String key, int start, int end)
{
    if (end >= start)
    {
        int mid = start + (end - start) / 2;

        if (strcmp(employeeList[mid].surname, key) == 0) return mid;

        if (strcmp(employeeList[mid].surname, key) > 0)
        {
            return SearchSurname(employeeList, key, start, mid - 1);
        }
        else
        {
            return SearchSurname(employeeList, key, mid + 1, end);
        }
    }

    return -1;
}

// The option functions
void ProcessTeams(struct Employees_Records *teams[], struct Employees_Records *employeeList, int teamMemberCount, int teamCount)
{
    // Displays each team separately
    printf("\nDisplaying teams...\n");

    for (int i = 0; i < teamCount; i++)
    {
        printf("Team %d:\n", i + 1);
        EmployeeList(teams[i], teamMemberCount);
    }
    
    // Sorts each team using merge sort
    printf("\nSorting teams...\n");

    for (int i = 0; i < teamCount; i++)
    {
        SortEmployees(teams[i], 0, teamMemberCount - 1);
    }
    // Displays each team separately
    for (int i = 0; i < teamCount; i++)
    {
        printf("Team %d:\n", i + 1);
        EmployeeList(teams[i], teamMemberCount);
    }
   
    // Combines teams to employeeList and displays 
    printf("\nCombining teams...\n");
    CombineTeams(teams, employeeList, teamMemberCount, teamCount);
    printf("\nCombined teams list:\n");
    EmployeeList(employeeList, teamCount * teamMemberCount);
}

// Displays the list of the employees certified to work on all three lines
void FullCerts(struct Employees_Records *employeeList)
{
    // Searches for full certifications
    printf("\nSearching for employees with full certifications...\n");
    
    for (int i = 0; i < Number_Certs; i++)
    {
        // For each full cert, it finds the employee linked to it and prints their details
        if ((employeeList + i) -> workLine == 3)
        {
              printf("\n%d. { %d , %s , %s , %d }", i , (employeeList + i) -> employeeID, (employeeList + i)->surname , (employeeList + i) -> firstName, (employeeList + i) -> workLine);
        }
    }

   printf("\n");
}

// Searches for a specific employee by surname
void GetEmployeeBySurname(struct Employees_Records *employeeList, int count)
{
    // Prompt user for surname
    String surname;
    int index;

    do
    {
        printf("\nEnter surname (max 29): \n\n> ");
        scanf("%29s", surname);

        if (strcmp(surname, "") == 0)
        {
            printf("\nSurname cannot be blank.\n");
        }
    } while (strcmp(surname, "") == 0);

    index = SearchSurname(employeeList, surname, 0, count - 1);

    if (index == -1)
    {
        printf("\nNo employees found with the surname '%s'.\n", surname);
    }
    else
    {
        printf("\n\n EMPLOYEE FOUND \n\n");
        printf("------------------ \n\n");
        printf("Employee ID:  %d\n\n", employeeList[index].employeeID);
        printf("First Name:  %s\n\n", employeeList[index].firstName);
        printf("Surname:  %s\n\n", employeeList[index].surname);
        printf("Work Line:  %d\n\n", employeeList[index].workLine);
    }

    printf("\n");
}