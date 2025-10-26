#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
#define VEHICLE_TYPES 3
#define VEHICLE_NAME_LENGTH 10
#define FUEL_PRICE 310

void storeCities(char cities[MAX_CITIES][MAX_NAME_LENGTH], int *count);//count means there is city count already we have
void displayCities(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void renameCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void removeCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void storeInterCityDistance(float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void displayInterCityDistance(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void editIntercityDistances(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void showVehicleList(char vehicles[3][10],float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3]);
void deliveryRequestHandling(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count,float cityDistance[MAX_CITIES][MAX_CITIES],char vehicles[3][10], float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3]);


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
    float deliveryCost,deliveryTime,fuelConsumption,fuelCost,operationalCost,profit,finalChargeToCustomer;

    do
    {
        printf("1.Add new City\n");
        printf("2.Rename or Remove City\n");
        printf("3.Store Intercity Distance\n");
        printf("4.Edit distances from Two Cities\n");
        printf("5.Show Vehicle List\n");
        printf("6..Make Delivery Request\n");
         printf("7.Show All Deliveries\n");
        printf("8.Exit\n");
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
            editIntercityDistances(cities,cityDistance,count);
            displayInterCityDistance(cities,cityDistance,count)
            break;
        case 5:
             showVehicleList(vehicles,vehicleCapacity,vehicleRatePerKm,vehicleAvgSpeed,vehicleFuelEfficiency);
             break;
        case 6:
            deliveryRequestHandling(cities,count,cityDistance,vehicles,vehicleCapacity,vehicleRatePerKm,vehicleAvgSpeed,vehicleFuelEfficiency);
            break;
        case 7:
            break;
        default:
            printf("Invalid choice\n");



        }
    }
    while(choice != 8);
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
void editIntercityDistances(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count)
{
    int i,city1Index,city2Index;
    float newDistance;
    if(count < 2)
    {
        printf("No Enough Cities Available for Edit Distances!\n");
        return;
    }
    printf("Enter City1 Index:");
    scanf("%d",&city1Index);
    printf("Enter City2 Index:");
    scanf("%d",&city2Index);

    displayCities(cities,count);

    if(city1Index < 1 || city1Index > count || city2Index <1 || city2Index > count)
    {
        printf("Invalid city Index!\n");
        return;
    }
    printf("Current distance between %s and %s:%.2f km]\n",cities[city1Index-1],cities[city2Index-1],cityDistance[city1Index-1][city2Index-1]);

    printf("Enter New Distance:");
    scanf("%f",&newDistance);

    cityDistance[city1Index-1][city2Index-1] = cityDistance[city2Index-1][city1Index-1]=newDistance;
}
void showVehicleList(char vehicles[3][10],float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3])
{
    int i;
    printf("\n     Vehicle Management list     \n");
    printf("Type\tCapacity\tRate Per km(LKR)\tAvg Speed(km/h)\tFuel Efficiency(km/l)  \n");
    for(i=0; i<VEHICLE_TYPES; i++)
    {
        printf("%s  \t%f  \t%f \t%f    \t%f  ",vehicles[i],vehicleCapacity[i], vehicleRatePerKm[i],vehicleAvgSpeed[i],vehicleFuelEfficiency[i]);
        printf("\n");

    }
}
void deliveryRequestHandling(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count,float cityDistance[MAX_CITIES][MAX_CITIES],char vehicles[3][10], float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3])
{
    int sourceIdx,destIdx,vehicleType;
    float weight,distance;
    if(count < 2)
    {
        printf("No Enough Cities Available for Dilivery!\n");
        return;
    }

    printf("Enter Source City Index:");
    scanf("%d",&sourceIdx);

    printf("Enter Destination City Index:");
    scanf("%d",&destIdx);

    if(sourceIdx == destIdx)
    {
        printf("Invalid Index !\n");
        return ;
    }
    displayInterCityDistance(cities,cityDistance,count);
    distance = cityDistance[sourceIdx-1][destIdx-1];

    printf("Enter Vehicle Type(van=0,truck=1,lorry=2):");
    scanf("%d",&vehicleType);

    if(vehicleType<0 || vehicleType>2)
    {
        printf("Invalid Vehicle Type!\n");
        return;
    }

    printf("Enter weight in kg:");
    scanf("%f",&weight);

    if(weight > vehicleCapacity[vehicleType])
    {
        printf("Invalid Weight!");
        return ;
    }
    float calcDeliveryCost = distance*vehicleRatePerKm[vehicleType]*(1.0+weight/1000);
    printf("%.2f\n",calcDeliveryCost);

    float calcDeliveryTime = distance/vehicleAvgSpeed[vehicleType];
    printf("%.2f\n",calcDeliveryTime);

    float fuelConsumption = distance/vehicleFuelEfficiency[vehicleType];
    printf("%.2f\n",fuelConsumption);

    float fuelCost = fuelConsumption*FUEL_PRICE;
    printf("%.2f\n",fuelCost);

    float operationalCost = calcDeliveryCost+fuelCost;
    printf("%.2f\n",operationalCost);

    float profit = calcDeliveryCost*0.25;
    printf("%.2f\n",profit);

    float finalChargeToCustomer = operationalCost+profit;
    printf("%.2f\n",finalChargeToCustomer);

     //Delivery Details
    deliverySource[deliveryCount]=sourceIdx-1;
    deliveryDestination[deliveryCount]=destIdx-1;
    deliveryVehicle[deliveryCount]=vehicleType;
    deliveryWeight[deliveryCount]=weight;
    deliveryCost[deliveryCount]=calcDeliveryCost;
    deliveryTime[deliveryCount]=calcDeliveryTime;
    deliveryFuelCost[deliveryCount]=fuelCost;
    deliveryFinalCharge[deliveryCount]=finalChargeToCustomer;
    deliveryCount++;
}
