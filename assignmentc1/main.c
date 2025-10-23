#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50

void storeCities(char cities[MAX_CITIES][MAX_NAME_LENGTH], int *count);//count means there is city count already we have
void displayCities(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void renameCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void removeCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void storeInterCityDistance(float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void displayInterCityDistance(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count);

int main()
{
    int choice;
    char cities[MAX_CITIES][MAX_NAME_LENGTH];
    int count = 0;
    float cityDistance[MAX_CITIES][MAX_CITIES];
    char vehicles[3][10] = {"Van","Truck","Lorry"};
    float vehicleCapacity[3] = {1000,5000,10000};
    float vehicleRatePerKm[3] = {30.0,40.0,80.0};
    float vehicleAvgSpeed[3] = {60.0,50.0,45.0};
    float vehicleFuelEfficiency[3] = {12.0,6.0,4.0};

    do
    {
        printf("1.Add new City\n");
        printf("2.Rename or Remove City\n");
        printf("3.Store Intercity Distance\n");
        printf("4.Edit distances from Two Cities\n");
        printf("5.Show Vehicle List\n");
        printf("6.Exit\n");
        printf("Enter your Choice:");
        scanf("%d",&choice);

        switch(choice)
        {

        case 1:
            storeCities(cities,&count);
            displayCities(cities,count);
            break;
        case 2:
            renameCity(cities,count);
            removeCity(cities,count);
            break;
        case 3:
            storeInterCityDistance(cityDistance,count);
            displayInterCityDistance(cities,cityDistance,count);
            break;
        case 4:
            break;
        case 5:

            break;
        default:
            printf("Invalid choice\n");



        }
    }
    while(choice != 6);
    return 0;
}
void storeCities(char cities[MAX_CITIES][MAX_NAME_LENGTH], int *count)
{
    int n,i;
    printf("How many Cities do you want to add?");
    scanf("%d",&n);
    getchar();

    for(i=0; i <n && *count<MAX_CITIES; i++)
    {

        printf("Enter city name %d:",*count+1);
        fgets(cities[*count],MAX_NAME_LENGTH,stdin);
        cities[*count][strcspn(cities[*count],"\n")]='\0';
        (*count)++;
    }

}
void displayCities(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count)
{
    int i;
    printf("\n       Cities List      \n");
    for(i=0; i< count; i++)
    {
        printf("%d. %s\n",i+1,cities[i]);
    }

}
void renameCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count)
{

    int i;
    int cityIndex;
    char newCityName[MAX_NAME_LENGTH];

    if(count == 0)
    {
        printf("No Cities Available for Rename\n");
        return ;

    }
    printf("What is the City index do you want to rename:");
    scanf("%d",&cityIndex);
    getchar();

    displayCities(cities,count);
    if(cityIndex<1 || cityIndex > count)
    {
        printf("Invalid City Index\n");
        return ;

    }
    printf("Enter new city name for '%s':",cities[cityIndex - 1]);
    fgets(newCityName,MAX_NAME_LENGTH,stdin);
    newCityName[strcspn(newCityName,"\n")]='\0';

    strcpy(cities[cityIndex - 1],newCityName);


    displayCities(cities,count);
}
void removeCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count)
{

    int cityIndex;

    if(count == 0)
    {
        printf("No Cities Available for Remove\n");
        return ;

    }

    displayCities(cities,count);

    printf("Enter City Index do you want to Remove:");
    scanf("%d",&cityIndex);
    getchar();

    strcpy(cities[cityIndex - 1]," ");

    displayCities(cities,count);

}
void storeInterCityDistance(float cityDistance[MAX_CITIES][MAX_CITIES],int count)
{
    int i,j;
    if(count < 2)
    {
        printf("No enough cities available Please add cities first!");
        return;
    }
    printf("\n      Enter Intercity Distances     \n");

    for(i=0; i<count; i++)
    {
        for(j=0; j<count; j++)
        {
            if(i==j)
            {
                cityDistance[i][j] = 0;
            }
            else if (i<j)
            {
                printf("Enter city %d to city %d distance:",i+1,j+1);
                scanf("%f",&cityDistance[i][j]);
                cityDistance[j][i] = cityDistance[i][j];
            }

        }
    }
}
void displayInterCityDistance( char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count)
{
    int i,j;
    printf("         InterCity Distance Matrix     \n");
    for(i=0; i<count; i++)
    {
        for(j=0; j<count; j++)
        {
            printf("%.2f  ",cityDistance[i][j]);
        }
        printf("\n");
    }
}

