#include <stdio.h>
#include <cs50.h>

int countf(long);
void printarray (unsigned int[], int);
int checkinput (unsigned int [], int);
int checkluhn (unsigned int [], int);

int main(void)
{

    long pan = 0;
    do
    {
        pan = get_long("Number: ");
    } while (pan <= 0); 
   
    int count = countf(pan);
    unsigned int panarray[count];
    unsigned int reversepanarray[count];

    for (int i = 1; i <= count; i++)
    {
        panarray[count-i] = pan % 10;
        reversepanarray[i-1] = pan % 10;
        pan /= 10;
    }

    if (!checkluhn (reversepanarray, count))
    {
        checkinput(panarray, count);
        return 0;
    } else {
        return 0;
    }
}

int countf(long pan)
{
    int i = 0;
    while (pan > 0)
    {
        pan /= 10;
        i++;
    }
    return i; 
}

void printarray (unsigned int arr[], int size)
{
    for (int i = 0; i < size; i++)  
        printf("%i", arr[i]);

    printf("\n");    
}

int checkinput (unsigned int arr[], int size)
{

    switch (arr[0]){
        // Visa 13 or 16 digits, start with 4 
        case 4:
            if (size == 16 || size == 13)
            {
                printf("VISA\n");
                return 0;
                } else {
                    printf("INVALID\n");
                    return 1;
                } 
            
            break;
        // Mastercard 16 digits, start with 51, 52, 53, 54, or 55 
        case 5:
            switch (arr[1]){
                case 1:
                    if (size == 16)
                    {
                        printf("MASTERCARD\n");
                        return 0;
                     } else {
                        printf("INVALID\n");
                        return 1;
                    } 
                    break;
                case 2:
                    if (size == 16)
                    {
                        printf("MASTERCARD\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    }              
                    break;
                case 3:
                    if (size == 16)
                    {
                        printf("MASTERCARD\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    }              
                    break;
                case 4:
                    if (size == 16)
                    {
                        printf("MASTERCARD\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    } 
                    break;
                case 5:                
                    if (size == 16)
                    {
                        printf("MASTERCARD\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    }             
                    break;
                default:
                    printf("INVALID\n");
                    return 1;
                    break;            
            }
            break;

        // Amex 15 digits, start with 34, 37
        case 3:
            switch (arr[1]){
                case 4:
                    if (size == 15)
                    {
                        printf("AMEX\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    } 
                    break;
                case 7:
                    if (size == 15)
                    {
                        printf("AMEX\n");
                        return 0;
                    } else {
                        printf("INVALID\n");
                        return 1;
                    } 
                    break;
                default:
                    printf("INVALID\n");
                    return 1;
                    break;
            }
            break;
        default:
            printf("INVALID\n");
            return 1;
            break;
    }
    return 1;
}

int checkluhn (unsigned int arr[], int size)
{
    int sum = 0;
    
    for (int i = 0; i < size; i += 2)
    {
        int innersum = arr[i+1] * 2;
        while (innersum > 0)
        {
            sum = sum + (innersum % 10);
            innersum /= 10;
        }

        sum = sum + arr[i];
    }
 
    if ((sum % 10) == 0)
        return 0;

    printf("INVALID\n");
    return 1;
}
