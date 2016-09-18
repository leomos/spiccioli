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
    res.name = strdup(s);
    res.value = n;
    return res;
}

//mette in ordine la stringa
char * order_str(char * str){ //ok
    char * new_str = strdup(str);
    size_t counter = 0;
    size_t i = 0;
    char temp = '0';
    //definisce il numero max di iterazioni
    for(counter=0; counter<strlen(new_str); counter++){
        //controlla ogni carattere con quello successivo
        for(i=0; i<(strlen(new_str)-1); i++){
            if (new_str[i]>new_str[i+1]){
                temp = new_str[i+1];
                new_str[i+1] = new_str[i];
                new_str[i] = temp;
            }
        }
    }
    return new_str;
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
    //printf("%s\n", s);
    char* c = strdup(s);
    int index = 0;
    while(*c!='\0' && *c != ':'){
        index++;
        c++;
    }
    char* res = malloc(sizeof(char)*index);
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
    char* c = strdup(s);
    int index = 0;
    while(*c!='\0' && *c != ','){
        index++;
        c++;
    }
    char* res = malloc(sizeof(char)*index);
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

//toglie la sottostringa
void remove_substring(char *s,const char *toremove)
{
  while( s=strstr(s,toremove) )
    memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}

//toglie il valore più alto
char *delete_highest_value(char *str){//ok
	char *token = NULL;
	char *temporary_string = NULL;
	char *token_relative_to_highest_value = NULL;
	char *first_copy_of_str = strdup(str);
	char *second_copy_of_str = strdup(str);

	int temporary_max = 0;
	int current_value = 0;

	token = strtok(first_copy_of_str, ",");

	while(token != NULL ){

		if(token != NULL) {
			temporary_string = strdup(token);
			while(*temporary_string != ':') temporary_string++;
			temporary_string++;
			current_value = atoi(temporary_string);
			if(current_value > temporary_max){
				temporary_max = current_value;
				token_relative_to_highest_value = token;
			}
        }

		token = strtok(NULL, ",");
	}
    remove_substring(second_copy_of_str, strcat(token_relative_to_highest_value,","));

    return second_copy_of_str;
}

char* spiccioli_base(int value, char* str){//ok

    int n_var = conta_vir(str)+1;
    coppia c[n_var];
    int i;

    for(i=0;i<n_var;i++){
        c[i] = init_coppia(var_name(str), var_value(str));
        while(*str != ',' && *str != '\0'){
            str++;
        }str++;
    }

    char* res = malloc(1);
    int result_length = 0;
    
    while(value != 0){
        int m = max(c, n_var);
        int m_index = max_index(c, n_var);
        if (value-m >= 0){
            value = value-m;
            result_length = strlen(res)+strlen(c[m_index].name);
            realloc(res,result_length);
            strcat(res,c[m_index].name);
            
        }
        else{
            c[m_index].value = -1;
        }
    }
    res[result_length] = '\0';
    return res;
}

char* spiccioli(int value, char *str){
    int n_var = conta_vir(str)+1;
    int i;
    int low_len=0;
    char* res;
    char* best_res;
    char*new_str = strdup(str);

    for (i=0; i<n_var; i++){
        res = spiccioli_base(value, new_str);
        if (low_len==0){
            // il primo risultato che trova lo aggiunge
            best_res = res;
            low_len = strlen(best_res);
        }
        // lo salva solo se la sequenza è minore
        if (strlen(res)<low_len){
            free(best_res);
            best_res = res;
            low_len = strlen(best_res);
        }
        new_str = delete_highest_value(new_str);
    }
    //free(delete_highest_value);
    return order_str(best_res);
}

//moneta più frequente
char most_freq_coin(char*str){
    char coin;
    char *s;
    int main_count = 0;
    int tmp_count = 0;
    int i;

    s = order_str(str);
    while(*s != '\0'){
        if(*s+1 != '\0'){
            if(*s == *(s+1)){
                tmp_count++;
            } else {
                if(main_count < tmp_count){
                    main_count = tmp_count;
                    coin = *s;
                    tmp_count = 0;
                }
            }
        }
        s++;
    }

    return coin;//mettere "%c" nel printf altrimenti aggiungere il '\0'
}



int main(){

	assert(strcmp(delete_highest_value("a:150,b:15,c:14,d:10,e:5,f:3,g:2,h:1"),"b:15,c:14,d:10,e:5,f:3,g:2,h:1")==0);
    assert(strcmp(spiccioli(20, "b:2,a:9,c:1"), "aab")==0);
    assert(strcmp(spiccioli(4, "a:5,b:2,c:1"),"bb")==0);
    assert(strcmp(spiccioli(12,"a:3,b:2"),"aaaa")==0);
    assert(strcmp(spiccioli(20, "a:6,b:5,c:1"), "bbbb")==0);
    assert(strcmp(spiccioli(21, "a:2,b:2,c:3"), "ccccccc")==0);
    assert(strcmp(spiccioli(151, "a:150,b:15,c:14,d:10,e:5,f:3,g:2,h:1"), "ah")==0);
    assert(strcmp(spiccioli(8, "a:6,b:4,c:2,d:1"), "ac")==0);
    assert(most_freq_coin("aaaabbaabccccccbbcccccc")=='c');
    return 0;
}
