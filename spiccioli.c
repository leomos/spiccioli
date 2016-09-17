#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//struct nome-valore
typedef struct coppia{//ok
    char* name;
    int value;
}coppia;

//inizializza le coppie nome-valore
coppia init_coppia(char* s, int n){//ok
    coppia res;
    res.name = malloc(sizeof(char)*strlen(s));
    strcpy(res.name, s );
    res.value = n;
    return res;
}

//conta le virgole
int conta_vir(char* s){ //ok
    int res=0;
    while(*s != '\0'){
        if(*s == ','){
            res++;
        }
        s++;
    }
    return res;
}

//prende il valore prima dei ':'
char* var_name(char* s){ //ok
    char* c = malloc(sizeof(char)*strlen(s));
    strcpy(c, s);
    int index = 0;
    while(*c!='\0' && *c != ':'){
        index++;
        c++;
    }
    char* res = malloc(sizeof(char)*index+1);
    strncpy(res, s, index);
    res[index] = '\0';
    return res;
}

//prende il valore prima della ','
int var_value(char* s){ //ok
    while(*s != ':'){
        s++;
    }
    s++;
    char* c = malloc(sizeof(char)*strlen(s));
    strcpy(c, s);
    int index = 0;
    while(*c!='\0' && *c != ','){
        index++;
        c++;
    }
    char* res = malloc(sizeof(char)*index+1);
    strncpy(res, s, index);
    res[index] = '\0';
    return atoi(res);
}

//prende il max dei valori
int max(coppia c[], int dim){//ok
    int i;
    int max = c[0].value;
    for (i=1;i<dim;i++){
        if (max < c[i].value)
            max = c[i].value;
    }
    return max;
}

//indica l'indice del valore max
int max_index(coppia c[], int dim){//ok
    int res;
    int m = max(c, dim);
    int i;
    for(i=0;i<dim;i++){
        if (c[i].value==m){
            res = i;
        }
    }
    return res;
}

char* spiccioli(int value, char* str){

    int n_var = conta_vir(str)+1;
    coppia c[n_var];
    int i;

    for(i=0;i<n_var;i++){
        c[i] = init_coppia(var_name(str), var_value(str));
        while(*str != ',' && *str != '\0'){
            str++;
        }str++;
    }
    int res_size;
    for(i=0;i<n_var;i++){
        res_size+=strlen(c[i].name);
    }

    char* res = malloc(sizeof(char)*res_size);

    while(value != 0){
        int m = max(c, n_var);
        int m_index = max_index(c, n_var);
        if (value-m >= 0){
            value = value-m;
            strcat(res,c[m_index].name);
        }
        else{
            c[m_index].value = -1;
        }
    }
    res[res_size] = '\0';
    return res;
}

int main(){
    assert(strcmp(spiccioli(20, "b:2,a:9,c:1"), "aab")==0);
    assert(strcmp(spiccioli(4, "a:5,b:2,c:1"),"bb")==0);
    assert(strcmp(spiccioli(12,"a:3,b:2"),"aaaa")==0);
    assert(strcmp(spiccioli(20, "a:6,b:5,c:1"), "aaacc")==0);
    assert(strcmp(spiccioli(21, "a:2,b:2,c:3"), "ccccccc")==0);
    assert(strcmp(spiccioli(151, "a:150,b:15,c:14,d:10,e:5,f:3,g:2,h:1"), "ah")==0);
    assert(strcmp(spiccioli(8, "a:6,b:4,c:2,d:1"), "ac")==0);
    //printf("%s",spiccioli(7026, "s:9,t:17,j:6000,a:3,b:4"));
    //printf("coppia nome = %s, coppia value = %d", c.name, c.value);
    // printf("%d", var_value("aljs:985"));
    return 0;
}
