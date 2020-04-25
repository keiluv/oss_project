#include "requisition.h"
//#define DEBUG
T_request* request[MAX];
int _count = 0;


int r_available(){
    if(_count  < MAX) return 1;
    else return 0;
}

int r_first_available(){
    int i;
    for(i=0; i<MAX; i++){
        if(request[i]==NULL){
            break;
        }
    }
    return i;
}

int r_count(){
    return _count;
}

T_request* r_search_by_name(char* t_name){
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(t_name, request[i]->name)==0){
#ifdef DEBUG
    printf("\n[DEBUF] %s의 요청서를 찾았습니다.\n\n", t_name);
#endif
            return request[i];
        }
    }
    return NULL;
}

T_request* r_search_by_date(int t_date){
    for(int i=0; i<MAX; i++){
        if(request[i] && t_date == request[i]->date){
#ifdef DEBUG
    printf("\n[DEBUF] %d날짜에 해당하는 요청서를 찾았습니다.\n\n", t_date);
#endif
            return request[i];
        }
    }
    return NULL;
}

T_request* r_search_by_city(char* t_city){
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(t_city,request[i]->city)==0){
#ifdef DEBUG
    printf("\n[DEBUF] %s에 해당하는 요청서를 찾았습니다.\n\n", t_city);
#endif
            return request[i];
        }
    }
    return NULL;
}
 // 구조체 배열과 날짜를 받아서 날짜일치하는 요청서구조체를 구조체배열에 차곡차곡넣기.
void r_get_all_by_date(T_request* a[], int date, int *size){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i] && (date == request[i]->date) ){
            a[c] = request[i];
            c++;
            *size+=1;
        }
    }
#ifdef DEBUG
    printf("\n[DEBUF] get by date 총 %d개의 구조체발견.\n\n", c);
#endif
}

void r_get_all_by_city(T_request* a[], char* city, int *size){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(city, request[i]->city)==0){
            a[c] = request[i];
            c++;
            *size+=1;
        }
    }
#ifdef DEBUG
    printf("\n[DEBUF] get by city 총 %d개의 구조체발견.\n\n", c);
#endif
}

void r_create(int t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space){
    int index = r_first_available();
    request[index] = (T_request*)malloc(sizeof(T_request));
    T_request* p=request[index];
    p->date = t_date;
    strcpy(p->name, t_name);
    p->age = t_age;
    strcpy(p->phone, t_phone);
    strcpy(p->city, t_city);
    p->space = t_space;
    p->charge = t_space*10000;
    _count++;
#ifdef DEBUG
    printf("\n[DEBUF] 요청서생성완료.\n\n");
#endif
}

void r_update(T_request* p, int t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space){
    p->date = t_date;
    strcpy(p->name, t_name);
    p->age = t_age;
    strcpy(p->phone, t_phone);
    strcpy(p->city, t_city);
    p->space = t_space;
#ifdef DEBUG
    printf("\n[DEBUF] 업데이트 완료.\n\n");
#endif
}

void r_delete(T_request* p){
    int index=0;
    for(int i=0; i<MAX; i++){
        if(p==request[i]){
            index = i;
#ifdef DEBUG
    printf("\n[DEBUF] delete 해당항목 발견.\n\n");
#endif
            break;
        }
    }
    request[index] = NULL;
    free(p);
    _count--;
}

void r_delete_all(){
    for(int i=0; i<MAX; i++){
        if(request[i]!=NULL){
            free(request[i]);
        }
        request[i]=NULL;
    }
    _count=0;
}

char* r_to_string(T_request* T){
    static char str[200];
    sprintf(str, " [%d]%s, %d세, %s, %s, %d평\n", T->date, T->name, T->age, T->phone, T->city, T->space);
#ifdef DEBUG
    printf("\n[DEBUF] to_string : string생성 완료.\n\n");
#endif
    return str;
}

char* r_to_string_save(T_request* T){
    static char str[200];
    sprintf(str, "%d %s %d %s %s %d\n", T->date, T->name, T->age, T->phone, T->city, T->space);
#ifdef DEBUG
    printf("\n[DEBUF] to_string_save : string생성 완료.\n\n");
#endif
    return str;
}

void r_get_all(T_request* a[]){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i]!=NULL){
            a[c] = request[i];
            c++;
        }
    }
}

void r_rerrange(){ // 중간에 빈 공간 땡겨서 최적화.
    for(int i=0; i<MAX-1; i++){
        if(request[i]==NULL){
            request[i] = request[i+1];
            request[i+1] = NULL;
#ifdef DEBUG
    printf("\n[DEBUF] 최적화 .%d번째칸\n", i);
#endif
        }
    }
}

char* r_getname(T_request* p){
    return p->name;
}

char* r_getphone(T_request* p){
    return p->phone;
}

int r_getdate(T_request* p){
    return p->date;
}

int r_getage(T_request* p){
    return p->age;
}

char* r_getaddress(T_request* p){
    return p->city;
}

int r_getspace(T_request* p){
    return p->space;
}

int r_getcharge(T_request* p){
    if(p==NULL) return 0;
    return p->charge;
}

void r_array_by_date(){
    r_rerrange();
    for(int i=0; i<_count-1; i++){
        for(int j=0; j<_count-1; j++){
            if( request[j]->date < request[j+1]->date){
                T_request *temp = request[j];
                request[j] = request[j+1];
                request[j+1] = temp;
            }
        }
    }
}

void r_count_by_age(int *a){
    r_rerrange();
    int b[6]={20,30,40,50,60,100};
#ifdef DEBUG
    printf("\n[DEBUF] _count : %d\n\n", r_count());
#endif
    for(int i=0; i<5; i++){
        for(int j=0; j<_count; j++){
            if(b[i] <= r_getage(request[j]) && r_getage(request[j]) < b[i+1]){
                a[i]+=1;
#ifdef DEBUG
    printf("\n[DEBUF] a[%d] : %d.\n\n", i, a[i]);
#endif
            }
        }
    }
}

void r_count_by_date(int *a){
    int b_cmp[13]={20200101, 20200201, 20200301, 20200401,20200501,20200601,20200701,20200801,20200901,20201001,20201101,20201201,20201231};
    for(int i=0; i<12; i++){
            for(int j=0; j<_count; j++){
                if(b_cmp[i] < r_getdate(request[j]) && b_cmp[i+1] >= r_getdate(request[j])){
                    a[i]+=1;
                }
            }
        }
}

void r_city_list(char a[][100], int *size, int* b){
    r_rerrange();
    #ifdef DEBUG
    for(int j=0; j<_count; j++){
        printf("%d : %s\n", j+1, request[j]->city);
    }
    #endif
    int k=0;
    for(int j=0; j<_count; j++){
        k=0;
        for(int i=0; i<_count; i++){
            if(a[i]!=NULL && strcmp(a[i], request[j]->city)==0){
                k=1;
                #ifdef DEBUG
                printf("j : %d, a[%d] : 동일%s\n", j, i, a[i]);//디버그 하자-----------------------------------------------------------------
                #endif
                b[i]+=1;
            }
        }
        if(k==0){
            strcpy(a[*size], request[j]->city);
            #ifdef DEBUG
            printf("j : %d,  a[%d] = %s\n", j, *size, a[*size]);//디버그 하자----------------------------------------------------------------
            #endif
            b[*size]+=1;
            *size+=1;
        }
    }
}

void r_date_list(int *a, int *size, int *a_date){//어떤날짜가 있는지 배열, 총몇개의 날짜가 있는지 사이즈, 날짜별로 갯수.
    r_rerrange();
    int k=0;
    for(int j=0; j<_count; j++){
        k=0;
        for(int i=0; i<_count; i++){
            if(a[i]!=0 && a[i] == request[j]->date){
                k=1;
                #ifdef DEBUG
                printf("j : %d, a[%d] : 동일%d\n", j, i, a[i]);
                #endif
                a_date[i]+=1;
            }
        }
        if(k==0){
            a[*size] = request[j]->date;
            #ifdef DEBUG
            printf("j : %d,  a[%d] = %d\n", j, *size, a[*size]);
            #endif
            a_date[*size]+=1;
            *size+=1;
        }
    }
}
