
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct dugum{
    int key;
    // istenilen diger bilgiler
};

struct heap{
    struct dugum *dizi; // struct dugum dizi[15];
    int kapasite;
    int eleman_sayisi;
};

struct heap *heap_olustur(int kapasite){
    struct heap *gecici;
    gecici=(struct heap*)malloc(sizeof(struct heap));
    if(!gecici){
        printf("Dinamik alan ayirma basarisiz... \n");
        exit(1);
    }
    gecici->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));
    if(!gecici->dizi){
       printf("Dinamik alan ayirma basarisiz... \n");
       exit(1);
    }
    gecici->kapasite=kapasite;
    gecici->eleman_sayisi=0;
    return gecici;
}

void heap_olustur_yeni(struct heap **h,int kapasite){

    *h=(struct heap*)malloc(sizeof(struct heap));
    if(!*h){
        printf("Dinamik alan ayirma basarisiz... \n");
        exit(1);
    }
    (*h)->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));
    if(!(*h)->dizi){
       printf("Dinamik alan ayirma basarisiz... \n");
       exit(1);
    }
    (*h)->kapasite=kapasite;
    (*h)->eleman_sayisi=0;

}

void print_heap(struct heap *heap){
    int i;
    for(i=0; i<heap->eleman_sayisi; i++) printf("%5d",heap->dizi[i].key);
    printf("\n");

}

void initialize_heap(struct heap *heap,int eleman_sayisi, int aralik){
    int i,j;
    int yeni,cik;

    if(eleman_sayisi >heap->kapasite) {
        printf("Heap gerekli kapasiteye sahip degil... exit...\n");
        exit(1);
    }
    srand(time(NULL));

    heap->dizi[0].key=rand()%aralik;
    for(i=1; i<eleman_sayisi; i++){
        while(1){
            cik=1;
            yeni=rand()%aralik;
            for(j=0; j<i; j++){
                if(yeni==heap->dizi[j].key){
                    cik=0; break;
                }
            }
            if(cik==0) continue;
            heap->dizi[i].key=yeni;
            break;
        }
    }
    heap->eleman_sayisi=eleman_sayisi;
}

void buble_down(struct heap *heap, int index){
    int sol,sag;
    sol=2*index+1;
    sag=2*index+2;
    int temp_key;

    while((sol <heap->eleman_sayisi &&
            heap->dizi[index].key < heap->dizi[sol].key) ||
           (sag <heap->eleman_sayisi &&
            heap->dizi[index].key < heap->dizi[sag].key)){
        if(sag>=heap->eleman_sayisi || heap->dizi[sol].key >heap->dizi[sag].key){
          temp_key = heap->dizi[sol].key;
          heap->dizi[sol].key=heap->dizi[index].key;
          heap->dizi[index].key=temp_key;
          index=2*index+1;

       }
        else{
          temp_key = heap->dizi[sag].key;
          heap->dizi[sag].key=heap->dizi[index].key;
          heap->dizi[index].key=temp_key;
          index=2*index+2;
        }
          sol=2*index+1;
          sag=2*index+2;
    }

}

void heapify(struct heap *heap){
    int i;
    for(i=heap->eleman_sayisi/2-1; i>=0; i--) buble_down(heap,i);
}

void buble_up(struct heap *heap, int index){
    int parent, temp_key;
    parent=(index-1)/2;

    while(parent>=0 && heap->dizi[parent].key <heap->dizi[index].key){
        temp_key= heap->dizi[parent].key;
        heap->dizi[parent].key=heap->dizi[index].key;
        heap->dizi[index].key=temp_key;
        index=parent;
        parent=(index-1)/2;

    }
}


void heap_insert(struct heap *heap,int key){
    if(heap->eleman_sayisi <heap->kapasite){
        heap->eleman_sayisi++;
        heap->dizi[heap->eleman_sayisi-1].key=key;
        buble_up(heap,heap->eleman_sayisi-1);
    }
}

void delete_max(struct heap *heap){
    int temp_key;
    if(heap->eleman_sayisi>1){
        temp_key=heap->dizi[0].key;
        heap->dizi[0].key=heap->dizi[heap->eleman_sayisi-1].key;
        heap->dizi[heap->eleman_sayisi-1].key=temp_key;
        heap->eleman_sayisi--;
        buble_down(heap,0);
    }
}

void heap_sort(struct heap *heap){
    int i;
    int temp=heap->eleman_sayisi;
    for(i=1; i<temp; i++) delete_max(heap);
    heap->eleman_sayisi=temp;
}

int heap_mi(struct heap* h){
    int i;
    if(h==NULL) return 1;
    for(i=0; i< h->eleman_sayisi/2; i++){
        if(h->dizi[i].key < h->dizi[2*i+1].key ||
           2*i+2 < h->eleman_sayisi && h->dizi[i].key < h->dizi[2*i+2].key)
            return 0;
    }
    return 1;
}


int main(int argc, char** argv) {

    struct heap *heap=heap_olustur(1001);
    initialize_heap(heap,1001,1000);
    print_heap(heap);
    printf("heap mi: %d\n",heap_mi(heap));
    heapify(heap);
    print_heap(heap);

    printf("heap mi: %d\n",heap_mi(heap));
 //   heap_insert(heap,102);
 //   print_heap(heap);
 //   printf("heap mi: %d\n",heap_mi(heap));

 //   delete_max(heap);
 //   print_heap(heap);

    heap_sort(heap);
    print_heap(heap);


    return (EXIT_SUCCESS);
}

