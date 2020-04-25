#include <stdio.h>
#include "requisition.h"
#define DEBUG

void create_card(); //1.요청서입력
void read_card(); //2.요청서 검색(개별, 날짜, 지역별)
void list_card(); // 3.전체 요청서 읽기
void rerrange(); // 4.최적화
void update_card(); // 5.요청서 업데이트
void delete_card(); // 6.요청서삭제
void load_card(); // 7.요청서 불러오기
void save_card(); // 8.요청서 저장.
void delete_card_all(); // 9.요청서 전체삭제
void charge();
void array_date();
void analysis();
/*
데이타 분석(나이별, 장소별, 월별)
날짜별 정렬
매출액 확인(전체, 특정날짜)
가장 매출이 많은 날.
*/
int main(){
    int n;
    while(1){
        printf("\nmenu : 1.요청서 입력 2.요청서 검색(개별, 날짜, 지역별) 3.전체 요청서 읽기 4.최적화 5.요청서업데이트 6.요청서삭제 \n");
        printf("7.요청서 불러오기 8.요청서 저장 9.요청서 전체삭제 10.매출액확인(총매출액, 날짜별, 가장많은날) 11.날짜순 정렬\n12.데이터 분석(나이, 장소, 월별, 종합)0.종료\n");
        scanf("%d", &n);
        switch(n){
            case 1:
                create_card();
                break;
            
            case 2: 
                read_card();
                break;

            case 3:  
                list_card();
                break;
            case 4: 
                rerrange();
                break;
            case 5: 
                update_card();
                break;
            case 6: 
                delete_card();
                break;
            case 7: 
                load_card();
                break;
            case 8: 
                save_card();
                break;
            case 9: 
                delete_card_all();
                break;
            case 10: 
                charge();
                break;
            case 11: 
                array_date();
                break;
            case 12: 
                analysis();
                break;
            case 0:
                printf("exit ...\n");
                return 0;
        }
    }
}

void create_card(){
    int age, space, date;
    char name[80], city[80], phone[80];
    if(!r_available()){
        printf("요청서를 저장할 공간이 부족합니다.\n\n");
        return ;
    }else{
        printf("날짜는? ");
        scanf("%d", &date);
        printf("이름은? ");
        scanf("%s", name);
        printf("나이는? ");
        scanf("%d", &age);
        printf("전화번호는? ");
        scanf("%s", phone);
        printf("주소는? ");
        scanf("%s", city);
        printf("평수는? ");
        scanf("%d", &space);
        r_create(date, name, age, phone, city, space);
    }
}


void read_card(){
    int n;
    char name[40];
    int date;
    char city[40];
    T_request* p[MAX];
    int size=0;
    printf("1. 이름으로 검색 2. 날짜별 검색 3. 지역별 검색>> ");
    scanf("%d", &n);
    if(n==1){
        printf("이름을 입력하세요. >> ");
        scanf("%s", name);
        if(r_search_by_name(name)==NULL){
            printf("동일한 이름을 찾지 못했습니다.\n\n");
            return ;
        }else{
            p[0]=r_search_by_name(name);
            printf("----------------------------------------------------\n");
            printf("%s",r_to_string(p[0]));
            printf("----------------------------------------------------\n");
            return ;
        }
    }else if(n==2){
        printf("날짜를 입력하세요. >> ");
        scanf("%d", &date);
        if(r_search_by_date(date)==NULL){
            printf("%d에 해당하는 요청서를 찾지 못했습니다.\n\n", date);
            return ;
        }else{
            r_get_all_by_date(p, date, &size);
            printf("%d날짜의 요청서 리스트입니다.\n", date);
            printf("----------------------------------------------------\n");
            for(int i=0; i<size; i++){
                printf("[%d]. %s", i+1, r_to_string(p[i]));
            }
            printf("----------------------------------------------------\n");
        }
    }else if(n==3){
        printf("지역를 입력하세요. >> ");
        scanf("%s", city);
        if(r_search_by_city(city)==NULL){
            printf("%s지역에 해당하는 요청서를 찾지 못했습니다.\n\n", city);
            return ;
        }else{
            r_get_all_by_city(p, city, &size);
            printf("%s지역의 요청서 리스트입니다.\n", city);
            printf("----------------------------------------------------\n");
            for(int i=0; i<size; i++){
                printf("[%d]. %s", i+1, r_to_string(p[i]));
            }
            printf("----------------------------------------------------\n");
        }
    }else{
        printf("잘못입력하셨습니다.\n\n");
        return ;
    }
}

void list_card(){
   int size=r_count();
   T_request* p[MAX];
   r_get_all(p);
   printf("\n모든요청서\n");
   printf("----------------------------------------------------\n");
   for(int i=0; i<size; i++){
       T_request* t = p[i];
       printf("%d. %s", i+1, r_to_string(t));
   }
   printf("----------------------------------------------------\n\n");
}

void rerrange(){
    r_rerrange();
    printf("최적화가 완료되었습니다.\n\n");
}

void update_card(){
    int age, space, date;
    char name[80], city[80], phone[80];
    T_request* p;
    printf("이름을 입력하세요 > ");
    scanf("%s", name);
    if(r_search_by_name(name)==NULL){
        printf("해당하는 이름이 없습니다.\n");
        return ;
    }else{
        p = r_search_by_name(name);
        printf("날짜는? ");
        scanf("%d", &date);
        printf("나이는? ");
        scanf("%d", &age);
        printf("전화번호는? ");
        scanf("%s", phone);
        printf("주소는? ");
        scanf("%s", city);
        printf("평수는? ");
        scanf("%d", &space);
        r_update(p, date, name, age, phone, city, space);
        printf("정보수정이 완료되었습니다\n\n");
   }
}

void delete_card(){
    char name[30];
    T_request* p;
    printf("삭제할 요청서의 이름을 입력하세요 > ");
    scanf("%s", name);
    if(r_search_by_name(name)==NULL){
        printf("%s의 요청서를 찾을 수 없습니다.\n", name);
        return ;
    }else{
        p=r_search_by_name(name);
        r_delete(p);
        printf("삭제되었습니다.\n");
    }

}

void load_card(){
    FILE* f = fopen("request.txt", "r");
    int age, space, date;
    char name[80], city[80], phone[80];
    int i=0;
    printf("읽어들인 정보.\n");
    while(!feof(f)){
        if(!r_available()){
            printf("저장공간이 부족합니다.\n");
            break;
        }
        int n = fscanf(f, "%d %s %d %s %s %d\n", &date, name, &age, phone, city, &space);
        if(n<6) break;
        r_create(date, name, age, phone, city, space);
        printf("%s의 요청서를 읽었습니다\n", name);
        i++;
    }
    printf(" 총 %d개의 요청서를 불러왔습니다.\n", i);
    printf(" 현제 요청서 갯수는 %d개 입니다.\n\n", r_count());

}

void save_card(){
    FILE* f = fopen("request.txt", "a+");
    T_request* p[MAX];
    r_get_all(p);
    int size = r_count();
    for(int i=0; i<size; i++){
        fprintf(f, "%s", r_to_string_save(p[i]));
    }
    printf("\n\n%d개의 요청서가 저장되었습니다.\n\n", size);
    fclose(f);
}

void delete_card_all(){
    r_delete_all();
    printf("전체삭제 되었습니다\n\n");
}

void charge(){//3개 기능을 구현한 후 한개의 함수로 합치는 과정에서 변수선언 과정에서 size라는 이름의 변수가 중복되어 컴파일 오류가 나타나는 현상을 겪음.
    int n;
    T_request* p[MAX];
    int date;
    int size_date=0;
    int sum=0;
    int size=r_count();
    printf("[매출액 확인]\n");
    printf("1.총 매출액 확인  2.날짜별 매출액 확인  3.매출이 가장 많은날 확인 > ");
    scanf("%d", &n);
    if(n==1){
        r_get_all(p);
        for(int i=0; i<size; i++){
            T_request *t = p[i];
            sum+=r_getcharge(t);
        }
        printf("총매출액 : %d만원\n", sum/10000);
    }else if(n==2){
        printf("매출액을 확인 할 날짜를 입력하세요 > ");
        scanf("%d", &date);
        if(r_search_by_date(date)==NULL){
            printf("%d에 해당하는 요청서를 찾지 못했습니다.\n\n", date);
            return ;
        }
        r_get_all_by_date(p, date, &size_date);
        for(int i=0; i<size_date; i++){
            T_request *t = p[i];
            sum+=r_getcharge(t);
        }
        printf("\n총 %d건이 검색되었습니다.\n",size_date);
        printf("[%d] 매출액 : %d만원\n\n", date, sum/10000);
        printf("----------------------------------------------------\n");
        for(int i=0; i<size_date; i++){
            T_request *t = p[i];
            printf("%s", r_to_string(t));
        }
        printf("----------------------------------------------------\n");
    }else if(n==3){
        int date_list[MAX]={0,};
        int size_date=0;
        int a_date[MAX]={0,};
        int index=0;
        int sum[MAX][2]={0,}, max=0;
        r_date_list(date_list, &size_date, a_date);//어떤날짜가 있는지 배열, 총몇개의 날짜가 있는지 사이즈, 날짜별로 갯수.
        #ifdef DEBUG
        printf("date_size : %d\n", size_date);
        for(int i=0; i<size_date; i++){
            printf("%d : %d\n", date_list[i], a_date[i]);
        }
        #endif
        int get_size=0;
        for(int i=0; i<size_date; i++){
            get_size=0;
            r_get_all_by_date(p, date_list[i], &get_size);
            for(int j=0; j<get_size; j++){
                sum[i][0]+=r_getcharge(p[j]);
                sum[i][1] = i;
            }
        }
            for(int j=0; j<size_date; j++){
                if(max < sum[j][0]){
                    max = sum[j][0];
                    index = sum[j][1];
                }
            }
            T_request *m[MAX];
            get_size =0;
            r_get_all_by_date(m, date_list[index], &get_size);
            printf("매출액이 가장 많은날 : %d\n", m[0]->date);
            printf("매출액 : %d원\n", max);
            printf("비고\n");
            for(int i=0; i<get_size; i++){
                printf("%s", r_to_string(m[i]));
            }
    }
}

void array_date(){ //해당 구조체가 null인지 여부를 확인하지 않고 for문을 MAX만큼 돌려서 정렬하는 바람에 컴파일오류가 남. 이를 최적화 후에 _count번 반복하는 구조로 바꾸어 해결함.
    printf("시작");
    r_array_by_date();
    printf("\n날짜순 정렬이 완료되었습니다.\n\n");
}

void analysis(){
    int n;
    int a_age[5]={0,}; // 0.20대 1.30대 2.40대 3.50대 4.60대이상.
    int b_age[6]={20,30,40,50,60,100};
    char city_list[MAX][100]={0,};
    int size_city=0;
    int a_city[MAX]={0,};
    int a_date[12]={0,};
    T_request* p[MAX];
    r_get_all(p);
    printf("[데이터 통계]\n");
    printf("1.나이별 2.장소별 3.월별 4.종합> ");
    scanf("%d", &n);
    if(n==1){
        r_count_by_age(a_age);// a[i]=+1로해서 값이 재대로 안나왔음.
        for(int i=0; i<5; i++){
            if(i==4) printf("60대 이상 : %d명\n", a_age[i]);
            else printf("%d대 : %d명\n", b_age[i], a_age[i]);
            for(int j=0; j<r_count(); j++){
                if(b_age[i] <= r_getage(p[j]) && r_getage(p[j]) < b_age[i+1]){
                    printf("%s", r_to_string(p[j]));
                }
            }
            printf("\n");
        }
    }else if(n==2){
        /*
        장소별 분석
        요청서 구조체 한번 쭉 돌리면서 나온 지역들을 모은 지역배열을 생성(문자배열).
        출력
        */
        r_city_list(city_list, &size_city, a_city);
        #ifdef DEBUG
        printf("city_size : %d\n", size_city);
        for(int i=0; i<size_city; i++){
            printf("%s : %d\n", city_list[i], a_city[i]);
        }
        #endif
        /*
        r_get_by_city로 city를 city_list[0]부터 쭉 보내면서 구초제 할당한다음 리스트 출력!
        */
       T_request* m[MAX];
       int get_size=0;
       for(int i=0; i<size_city; i++){
            get_size=0;
            r_get_all_by_city(m, city_list[i], &get_size);
            printf("%s : %d명\n", city_list[i], a_city[i]);
            for(int j=0; j<get_size; j++){
                printf("%s", r_to_string(m[j]));
            }
            printf("\n");
       }
    }else if(n==3){     
        int b_cmp[13]={20200101, 20200201, 20200301, 20200401,20200501,20200601,20200701,20200801,20200901,20201001,20201101,20201201,20201231};
        r_count_by_date(a_date);
        for(int i=0; i<12; i++){
            printf("%d월달 : %d명\n", i+1, a_date[i]);
            for(int j=0; j<r_count(); j++){
                if(b_cmp[i] < r_getdate(p[j]) && b_cmp[i+1] >= r_getdate(p[j])){
                    printf("%s", r_to_string(p[j]));
                }
            }
            printf("\n");
        }


    }else if(n==4){
        printf("나이별 통계\n");
        r_count_by_age(a_age);// a[i]=+1로해서 값이 재대로 안나왔음.
        for(int i=0; i<5; i++){
            if(i==4) printf("60대 이상 : %d명\n", a_age[i]);
            else printf("%d대 : %d명\n", b_age[i], a_age[i]);
        }
        printf("\n지역별 통계\n");
        r_city_list(city_list, &size_city, a_city);
        for(int i=0; i<size_city; i++){
            printf("%s : %d명\n", city_list[i], a_city[i]);
        }
        printf("\n월별 통계\n");
        r_count_by_date(a_date);
        for(int i=0; i<12; i++){
            printf("%d월달 : %d명\n", i+1, a_date[i]);
        }
    }else{
        printf("잘못입력하셨습니다.\n");
        return ;
    }
}
