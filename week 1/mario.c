#include <cs50.h>
#include <stdio.h>

void printPyramids(int);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height (1-8): ");
    } 
    while (height <= 0 || height > 8);
   
    printPyramids(height);    
}

// this function print pyramide
void printPyramids(int height)
{
    for (int raw = 1; raw <= height; raw++)
    {
        for (int col = 0; col < height; col++)
        {
            if (col < (height - raw))
            {
                printf(" "); 
            }
            else
            {
                printf("#");
            }
             
        }
        
        printf("  ");
        
        for (int col = 0; col < height; col++)
        {
            if (col < raw)
            {
                printf("#"); 
            }   
        }
        printf("\n"); 
    }  
} 
