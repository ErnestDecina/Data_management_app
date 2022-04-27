 /*
Program Desc:
Author: Ernest John Decina
Date: 28 March 2022

Edited by:
Due Date: 22 April 2022
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbolic Names
#define EMPLOYEE_SIZE 6
#define TEAM_SIZE 4
#define NAME_SIZE 25
#define LINE_SIZE 3

//  Sturctures
struct name_qualification // Name && Qualification of Employee
{
    int employee_id;
    char firstname[NAME_SIZE];
    char surname[NAME_SIZE];
    int work_line[LINE_SIZE];
    int qualification;
};

struct team_info // Team
{
    // Creating an Array of Employees
    struct name_qualification employee[EMPLOYEE_SIZE];
};

struct surname_id
{
    int id;
    char surname[NAME_SIZE];
};

// Function
void read_data(struct surname_id [],struct team_info []); // Reading data into structures from .txt file
int sort_surnames(struct surname_id [], struct team_info []); // Puts all data into one array then sorts in alphabetical order
void merge_sort(struct surname_id [], int, int);
void merge(struct surname_id [], int, int, int);
int check_sort(struct surname_id [], int); // Checking if the sub arrays in the merge sort is already sorted
void find_certificate(struct team_info[]); // Find employees who have 3 Line Certificate
void search_emp(struct surname_id [], struct team_info []); // Binary Search
int binary_search_char(struct surname_id [], char [], int, int); // Binary Search for Characters
void clear_buffer(void); // Clearing input buffer to ignore enter input



// Driver Code
int main()
{
    // Vars
    int menu_status = 1;
    char menu_option = ' ';
    char **all_surname = malloc(sizeof(char *) * (TEAM_SIZE * EMPLOYEE_SIZE)); // Creating array of all surnames

    // Dynamically create an array of structures
    struct team_info *team = malloc(TEAM_SIZE * sizeof(*team));
    struct surname_id person[TEAM_SIZE * EMPLOYEE_SIZE];
    

    // Read data from .txt file into the array of structures
    read_data(person, team);

    printf("\nBefore sort:");
    for(register int i = 0; i < TEAM_SIZE * EMPLOYEE_SIZE; i++)
    {
        printf("\n%s", person[i].surname);
    } // End for

    // Sort Names
    merge_sort(person, 0, TEAM_SIZE * EMPLOYEE_SIZE - 1);


    do
    {   
        printf("\n\na) List of Employee's in order");
        printf("\nb) List of Total 3 Certified Employees");
        printf("\nc) Search for Employee");
        printf("\nd) End program");

        // Choosing Option
        printf("\nChoose option: ");
        scanf("%c", &menu_option);

        switch(menu_option)
        {
            // Putting all employees surname in one and sort in alphabetical order
            case 'a':
            {
                printf("\nAfter sort:");
                sort_surnames(person, team);
                break;
            } // End case 'a'

            case 'b':
            {
                find_certificate(team);
                break;
            } // End case 'b'

            case 'c':
            {
                search_emp(person, team);
                break;
            } // End case 'c'

            case 'd':
            {
                printf("\nProgram End");
                menu_status = 0; 
                break;
            } // End case 'd'

            default:
            {
                printf("\nInvalid Option");
                break;
            } // End default
        } // End Switch
        clear_buffer();
    } while(menu_status == 1);

    // Free data
    free(team);
    free(all_surname);     
    // End Program
    return 0;
}

// Functions
// void read_data(struct team_info team[])
// parameter 1: structure team_info array of teams
// reading name_qualifications in to the structure
void read_data(struct surname_id last_names[], struct team_info team[]) 
{
    // Vars
    int h = 0;

    // Opening file
    FILE* fp;
    fp = fopen("name_qualification.txt", "r");

    if (fp == NULL)
    {   
        printf("File Does not Exsist\n");
 
    } // End If
    else
    {
        for(register int i = 0; i < TEAM_SIZE; i++)
        {
            for (register int j = 0; j < EMPLOYEE_SIZE; j++)
            {
                fscanf(fp, "%d %s %s {%d, %d, %d} %d\n", &team[i].employee[j].employee_id, team[i].employee[j].firstname, team[i].employee[j].surname, &team[i].employee[j].work_line[0], &team[i].employee[j].work_line[1], &team[i].employee[j].work_line[2], &team[i].employee[j].qualification);
            } // End for
        } //  End for
    } // End Else

    // putting all last_names into one array
    while (h < TEAM_SIZE * EMPLOYEE_SIZE)
    {
        for(register int i = 0; i < TEAM_SIZE; i++)
        {
            for (register int j = 0; j < EMPLOYEE_SIZE; j++)
            {
                last_names[h].id = team[i].employee[j].employee_id;
                strcpy(last_names[h].surname, team[i].employee[j].surname);
                h = h + 1;
            } // End for
        } //  End for
    } // End while

    fclose(fp); // Stop using file
} // End void read_data(struct team_info [])

// int sort_surnames(char **last_names, struct team_info team[])
// parameter 1: string array containing lastname strings
// parameter 2: structure team_info array of teams
int sort_surnames(struct surname_id last_names[], struct team_info team[])
{
    for(register int i = 0; i < TEAM_SIZE * EMPLOYEE_SIZE; i++)
    {
        printf("\n%s", last_names[i].surname);
    } // End for
}

// void merge_sort(char *array[], int first_index, int last_index)
// sorts array using merge sort
// parameter 1 : array of characters
// parameter 2 : first index
// parameter 3 : last index
void merge_sort(struct surname_id array[], int first_index, int last_index)
{
    if (first_index < last_index)
    {   
        if (check_sort(array, last_index) == 0)
        {
            int middle_index = first_index + (last_index - first_index) / 2;

            // Sorting 1st half
            merge_sort(array, first_index, middle_index);
            // Sorting 2nd half
            merge_sort(array, middle_index + 1, last_index);
            // Merging results
            merge(array, first_index, middle_index, last_index);
        } // End if
    } // End if
} // End void merge_sort(int [][NAME_SIZE], int first_index, int last_index)

// void merge(char *array_unsorted[], int first_index, int middle_index,int last_index)
// Merges Subarrays together
// parameter 1 : array of characters
// parameter 2 : first index
// parameter 2 : middle index
// parameter 4 : last index
void merge(struct surname_id array_unsorted[], int first_index, int middle_index,int last_index)
{
    
    static int i = 0, j = 0, k = 0;
    int size_left = (middle_index - first_index) + 1;
    int size_right = (last_index - middle_index);

    /* create temp arrays */
    char **temp_L = malloc(sizeof(char *) * size_left);
    char **temp_R = malloc(sizeof(char *) * size_right);
    int *temp_L_id = malloc(sizeof(int *) * size_left);
    int *temp_R_id = malloc(sizeof(int *) * size_right);

    /* Copy data to temp arrays L[] and R[] */ 
    for (i = 0; i < size_left; i++)
    {
        temp_L[i] = malloc( sizeof(array_unsorted[first_index + i].surname));
        temp_L_id[i] = array_unsorted[first_index + i].id;
        strcpy(temp_L[i], array_unsorted[first_index + i].surname);
    }
        
    for (j = 0; j < size_right; j++)
    {
        temp_R[j] = malloc( sizeof(array_unsorted[middle_index + j + 1].surname));
        temp_R_id[j] = array_unsorted[middle_index + j + 1].id;
        strcpy(temp_R[j], array_unsorted[middle_index + j + 1].surname);
    }

    i = 0; 
    j = 0; 
    k = first_index; 
    while (i < size_left && j < size_right) 
    {
        if (strcmp(temp_L[i], temp_R[j]) < 0) 
        {
            array_unsorted[k].id = temp_L_id[i];
            strcpy(array_unsorted[k].surname, temp_L[i]);
            i++;
        }
        else 
        {
            array_unsorted[k].id = temp_R_id[j];
            strcpy(array_unsorted[k].surname, temp_R[j]);
            j++;
        }
        k++;
    }

    while (i < size_left) 
    {
        array_unsorted[k].id = temp_L_id[i];
        strcpy(array_unsorted[k].surname, temp_L[i]);
        i++;
        k++;
    }

    while (j < size_right) 
    {
        array_unsorted[k].id = temp_R_id[j];
        strcpy(array_unsorted[k].surname, temp_R[j]);
        j++;
        k++;
    }
} // End void merge(int [][NAME_SIZE], int first_index, int middle_index,int last_index)

// int check_sort(struct surname_id []);
// Checks if the subarrays of the merge sort is already sorted
// parameter 1: surname_id sturcture to check if the surnames are already sorted
int check_sort(struct surname_id surname[], int n)
{
    // No elements || The array has been checked and been sorted
    if (n == 1 || n == 0)
    {   
        return 1;
    } // End if
        
    // Found a unsorted pair
    else if (strcmp(surname[n - 1].surname, surname[n - 2].surname) < 0)
    {
        return 0;
    } // End if
        
 
    // Check the rest
    return check_sort(surname, n - 1);
} // End int check_sort(struct surname_id []);

// void find_certificate(struct team_info[]); 
// Finding Employees that have a 3 line Certificate
// Parameter 1 : team_info structure array
void find_certificate(struct team_info team[])
{
    for(register int i = 0; i < TEAM_SIZE; i++)
    {
        for (register int j = 0; j < EMPLOYEE_SIZE; j++)
        {
            if(team[i].employee[j].qualification == 3)
            {
                printf("\n");
                printf("\nName: %s %s", team[i].employee[j].firstname, team[i].employee[j].surname);
                printf("\nId: %d", team[i].employee[j].employee_id);
                printf("\nWork Lines: ");
                for (register int k = 0; k < LINE_SIZE; k++)
                {
                    if(team[i].employee[j].work_line[k] != 0)
                    {
                        printf("%d ", team[i].employee[j].work_line[k]);
                    } // End if
                } // End for
                printf("\nQualification Certificates: %d", team[i].employee[j].qualification);
            } // End if 
        } // End for
    } //  End for
} // void find_certificate(struct team_info[]); 

// void search_emp(char *surnames[], struct team_info, int)
// searches for the employee using binary search
// paramter 1 : surname_id structure for the sorted surnames
// paramter 2 : team_info for all the information linked with the surnames
void search_emp(struct surname_id person[], struct team_info team[])
{
    // Vars
    char find_name[NAME_SIZE];
    int id_value = 0;
    int division_counter = 0;

    // Searching for Name
    printf("\nEnter surname to get full information: ");
    clear_buffer();
    scanf("%s", find_name);
    // fgets(find_name, NAME_SIZE - 1, stdin);

    // Call Binary Search
    id_value = (binary_search_char(person, find_name, 0, (TEAM_SIZE * EMPLOYEE_SIZE) - 1));

    if (id_value == -1)
    {
        printf("\nName not found in Database.");
    } // End if
    else
    {
        while (id_value > 5 + 1)
        {
            id_value = id_value - 5;
            division_counter++;
        } // End while

        id_value = id_value - 1;

        printf("\nName: %s %s", team[division_counter].employee[id_value].firstname, team[division_counter].employee[id_value].surname);
        printf("\nId: %d", team[division_counter].employee[id_value].employee_id);
        printf("\nWork Lines: ");
        for (register int i = 0; i < LINE_SIZE; i++)
        {
            if(team[division_counter].employee[id_value].work_line[i] != 0)
            {
                printf("%d ", team[division_counter].employee[id_value].work_line[i]);
            } // End if
        } // End for
        printf("\nQualification Certificates: %d", team[division_counter].employee[id_value].qualification);
    } // End else
} // End void search_emp(struct surname_id person[], struct team_info team[])

// int binary_search_char(struct surname_id person[], char find_name[], int first_index, int last_index)
// searches for given name using binar search
// paramter 1: surname_id structure for the sorted surnames
// paramter 2: the name that wants to found
// paramter 3: first index of the array
// paramter 4: last index of the array
int binary_search_char(struct surname_id person[], char find_name[], int first_index, int last_index)
{
    // int middle = ((last_index - first_index) / 2) + first_index;
    int middle = first_index + ((last_index - first_index) / 2);    

    // Start recursive search
    if (last_index > -1 )
    {
        // Middle Value == Found item
        if (strcmp(find_name, person[middle].surname) == 0) // in middle
        {
            // Found Value
            return person[middle].id;
        }  // End if
        // First Half
        else if (strcmp(find_name, person[middle].surname) < 0)
        {
            return binary_search_char(person, find_name, first_index, middle - 1);
        } // End else if
        
        // Second Half
        else
        {
            return binary_search_char(person, find_name, middle + 1, last_index);
        } // End else
    } // End if
    // Value doesnt exist
    else 
    {
        return -1;
    } // End else

} // End int binary_search_char(struct surname_id person[], int first_index, int middle_index)

// void clear_buffer(void)
// clears the input buffer
void clear_buffer(void)
{
    while(getchar() != '\n');
} // End void clear_buffer(void)