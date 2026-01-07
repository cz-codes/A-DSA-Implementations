//FIX free_table() - invalid pointer error
//Address qns on line 77

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define PRIME 509
#define TABLE_SIZE 100
#define MAXLOOP 50

//Structures
typedef struct {
    int value;
    int has_value;
} NullableInt;

typedef struct {
    int a;
    int b;
}HashValues;


//Global Variables and Pointer
NullableInt *Table1;
NullableInt *Table2;

HashValues h1;
HashValues h2;

//Functions
void free_table(NullableInt *Table){
    for(int i=0;i<TABLE_SIZE;i++){
        free(&Table[i]);
    }
    free(Table);
}
void generate_constants(HashValues *h){
    srand(time(NULL));
    h->a = (rand() % (PRIME - 1)) + 1;
    h->b = (rand() % (PRIME - 1));
    return;
}

size_t compute_hash(int a, int b, int key){
    return ( ( ( a * key ) + b ) % PRIME ) % TABLE_SIZE;
}

size_t hash(int key, HashValues *h){
    return compute_hash(h->a,h->b,key);
}

int lookup(int key){
    size_t i1 = hash(key,&h1);
    size_t i2 = hash(key,&h2);

    if(Table1[i1].value==key) return 1;
    if(Table2[i2].value==key) return 1;

    return 0;
}

void rehash(){
    int *temp_Table = calloc(TABLE_SIZE, sizeof(int));
    int j = 0;
    for(int i=0;i<TABLE_SIZE;i++){
        if(Table2[i].has_value){
            temp_Table[j++] = Table2[i].value;
        }
    }

    generate_constants(&h2);

    free_table(Table2);
    Table2 = calloc(TABLE_SIZE, sizeof(NullableInt));

    for(int i=0;i<=j;i++){
        int element = temp_Table[i];

        // size_t index = hash(element,&h2);
        // Table2[index].value = element;
        // Table2[index].has_value = 1;
        //QNS:
        //What if two values collide here, when hasing with the new hash fuction
        //do we take the key , now evicted and out after maxloop in (insertion) and insert it as last element in temp_table?,then hash it in too
        // or do we just generate_constants for both tables and hash everykey back in
        //or do we call insert on every key in  the temp_table, after ofcourse - generate_constant(&h2);

        insert(element);
    }
 
    
}

int insert(int key){

    if(lookup(key)){
        printf("Key already in Table.\n");
        return 0;
    }

    int i = 0;
    while (i != MAXLOOP)
    {
        size_t i1 = hash(key,&h1);
        if(Table1[i1].has_value){
            int evicted = Table1[i1].value;
            Table1[i1].value = key;
            key = evicted;
        }else{
            Table1[i1].value = key;
            Table1[i1].has_value = 1;
            break;
        }

        size_t i2 = hash(key,&h2);
        if(Table2[i2].has_value){
            int evicted = Table1[i1].value;
            Table2[i2].value = key;
            key = evicted;
        }else{
            Table2[i2].value = key;
            Table2[i2].has_value= 1;
            break;
        }
        i++;
    }
    
    if(i==MAXLOOP) rehash();

    return 0;
}

void init(){
    Table1 = calloc(TABLE_SIZE, sizeof(NullableInt));
    Table2 = calloc(TABLE_SIZE, sizeof(NullableInt));

    generate_constants(&h1);
    generate_constants(&h2);
}

void print_cuckoo(){
    printf("Table 1\n");
    printf("h(k) = ( (( %d * key )+%d) %% %d ) %% %d\n",h1.a,h1.b,PRIME,TABLE_SIZE);
    printf("Index : Value\n");
    for(int i=0;i<TABLE_SIZE;i++){
        if(Table1[i].has_value){
            printf("%d : %d\n",i,Table1[i].value);
        }
    }

    printf("\nTable 2\n");
    printf("h(k) = ( (( %d * key )+%d) %% %d ) %% %d\n",h2.a,h2.b,PRIME,TABLE_SIZE);
    printf("Index : Value\n");
    for(int i=0;i<TABLE_SIZE;i++){
        if(Table2[i].has_value){
            printf("%d : %d\n",i,Table2[i].value);
        }
    }
}

void main(){
    init();
    for(int i=0;i<100;i++){
        insert(i);
    }
    print_cuckoo();
    
}
