#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
#define VEHICLE_TYPES 3
#define VEHICLE_NAME_LENGTH 10
#define FUEL_PRICE 310
#define INF_DISTANCE 1e9f

void storeCities(char cities[MAX_CITIES][MAX_NAME_LENGTH], int *count);//count means there is city count already we have
void displayCities(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void renameCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void removeCity(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count);
void storeInterCityDistance(float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void displayInterCityDistance(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void editIntercityDistances(char cities[MAX_CITIES][MAX_NAME_LENGTH],float cityDistance[MAX_CITIES][MAX_CITIES],int count);
void showVehicleList(char vehicles[3][10],float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3]);
void deliveryRequestHandling(char cities[MAX_CITIES][MAX_NAME_LENGTH],int count,float cityDistance[MAX_CITIES][MAX_CITIES],char vehicles[3][10], float vehicleCapacity[3],float vehicleRatePerKm[3],float vehicleAvgSpeed[3],float vehicleFuelEfficiency[3]);
void showAllDeliveries(char cities[MAX_CITIES][MAX_NAME_LENGTH],char vehicles[3][10]);
void showReports(void);
float findMinDistanceRoute(int srcIdx, int destIdx, int count, float cityDistance[MAX_CITIES][MAX_CITIES], int path[MAX_CITIES], int *pathLen);

int main()
{
    int choice,i,j;
    char cities[MAX_CITIES][MAX_NAME_LENGTH];
    int count = 0;
    float cityDistance[MAX_CITIES][MAX_CITIES];
    char vehicles[3][10] = {"Van","Truck","Lorry"};
    float vehicleCapacity[3] = {1000,5000,10000};
    float vehicleRatePerKm[3] = {30.0,40.0,80.0};
    float vehicleAvgSpeed[3] = {60.0,50.0,45.0};
    float vehicleFuelEfficiency[3] = {12.0,6.0,4.0};
    float deliveryCost,deliveryTime,fuelConsumption,fuelCost,operationalCost,profit,finalChargeToCustomer;
    float deliveryDistance[MAX_DELIVERY];
    float deliveryProfit[MAX_DELIVERY];
    for(i = 0; i < MAX_CITIES; i++)
    {
        for( j = 0; j < MAX_CITIES; j++)
        {
            if(i == j) cityDistance[i][j] = 0.0f;
            else cityDistance[i][j] = INF_DISTANCE;
        }
    }



    do
    {
        printf("1.Add new City\n");
        printf("2.Rename or Remove City\n");
        printf("3.Store Intercity Distance\n");
        printf("4.Edit distances from Two Cities\n");
        printf("5.Show Vehicle List\n");
        printf("6..Make Delivery Request\n");
        printf("7.Show All Deliveries\n");
        printf("8.Show Reports\n");
        printf("9.Exit\n");
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
            showAllDeliveries(cities,vehicles);
            break;
        case 8:
            showReports();
            break;
        default:
            printf("Invalid choice\n");



        }
    }
    while(choice != 9);
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
void showAllDeliveries(char cities[MAX_CITIES][MAX_NAME_LENGTH],char vehicles[3][10])
{
    int i;
    if(deliveryCount==0)
    {
        printf("No deliveries added\n");
        return;
    }
    printf("\n    Delivery Records     \n");
    for(i=0; i<deliveryCount; i++)
    {
        printf("\nDelivery %d\n",i+1);
        printf("From:%s\n", cities[deliverySource[i]]);
        printf("To:%s\n",cities[deliveryDestination[i]]);
        printf("Vehicle:%s\n",vehicles[deliveryVehicle[i]]);
        printf("Weight:%.2f\n",deliveryWeight[i]);
        printf("Cost:%.2f\n", deliveryCost[i]);
        printf("Fuel Cost:%.2f\n",deliveryFuelCost[i]);
        printf("Final Charge:%.2f\n",deliveryFinalCharge[i]);
    }
}
void showReports(void)
{
    int i;
    if(deliveryCount == 0)
    {
        printf("No deliveries completed yet\n");
        return;
    }
    float sumDistance = 0.0f;
    float sumTime     = 0.0f;
    float sumRevenue  = 0.0f;
    float sumProfit   = 0.0f;
    float minDistance = deliveryDistance[0];
    float maxDistance = deliveryDistance[0];

    for(i = 0; i < deliveryCount; i++)
    {
        sumDistance += deliveryDistance[i];
        sumTime     += deliveryTime[i];
        sumRevenue  += deliveryFinalCharge[i];
        sumProfit   += deliveryProfit[i];

        if(deliveryDistance[i] < minDistance) minDistance = deliveryDistance[i];
        if(deliveryDistance[i] > maxDistance) maxDistance = deliveryDistance[i];
    }

    printf("\n   PERFORMANCE REPORTS   \n");
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", sumDistance);
    printf("Average Delivery Time: %.2f hours\n", sumTime / deliveryCount);
    printf("Total Revenue: %.2f LKR\n", sumRevenue);
    printf("Total Profit: %.2f LKR\n", sumProfit);
    printf("Shortest Route Completed: %.2f km\n", minDistance);
    printf("Longest Route Completed:  %.2f km\n", maxDistance);
}

float findMinDistanceRoute(int sourceIdx, int destIdx, int count, float cityDistance[MAX_CITIES][MAX_CITIES], int path[MAX_CITIES], int *pathLen)
{
    int i,k,v;
    int visited[MAX_CITIES] = {0};
    float distArr[MAX_CITIES];
    int prev[MAX_CITIES];

    for(i = 0; i < count; i++)
    {
        distArr[i] = INF_DISTANCE;
        prev[i]    = -1;
    }
    distArr[sourceIdx] = 0.0f;

    for(k = 0; k < count; k++)
    {
        float minVal = INF_DISTANCE;
        int u      = -1;
        for(i = 0; i < count; i++)
        {
            if(!visited[i] && distArr[i] < minVal)
            {
                minVal = distArr[i];
                u      = i;
            }
        }
        if(u == -1) break;
        visited[u] = 1;

        for(v = 0; v < count; v++)
        {
            if(!visited[v] && cityDistance[u][v] < INF_DISTANCE/2)
            {
                float alt = distArr[u] + cityDistance[u][v];
                if(alt < distArr[v])
                {
                    distArr[v] = alt;
                    prev[v]    = u;
                }
            }
        }
    }

    if(distArr[destIdx] >= INF_DISTANCE/2)
    {
        *pathLen = 0;
        return INF_DISTANCE;
    }

    int tempPath[MAX_CITIES];
    int idx = 0;
    for(v = destIdx; v != -1; v = prev[v])
    {
        tempPath[idx++] = v;
    }
    *pathLen = idx;
    for (i = 0; i < idx; i++)
    {
        path[i] = tempPath[idx - 1 - i];
    }

    return distArr[destIdx];
}



