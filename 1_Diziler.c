#include <stdio.h>
#include <stdlib.h>

int main()
{
    int dizi[3];
    dinamik_dizi_olustur(&dizi,3);
    dinamik_dizi_yaz(dizi,3);
    return 0;
}
void dinamik_dizi_olustur(int **dizi,int size)
{
    *dizi=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)
    {
        *(dizi+i)=rand()%10;
    }
}
void dinamik_dizi_yaz(int*dizi,int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d\t",(dizi+i));
        printf("%d\n",*(dizi+i));

    }
}
