#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
    int n;
    int* v;
   
    int S=0;
    
    
    scanf("%d",&n);
    v=(int*)malloc(n * sizeof(int));
    
    for (int i=0; i<n; i++){
        scanf("%d",&v[i]);
        S+=v[i];
    }
    printf("Suma este %d",S);
    free(v);
    


    return 0;
}
