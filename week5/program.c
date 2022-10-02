#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int num;
    char name[20];
    char birth[5];
    char phone[15];
    float score;
    struct Student* next;
}Student;

void printProgram();
void selectProgram(int n, Student* head);
void makeStudent(Student* head);
void inputAll(Student* head);
void inputInformation(Student* ptr);
void printList(Student* head);
void createStudent(Student* head);
void revisePhone(Student* head);
void reviseScore(Student* head);
void addStudent(Student* head);
void deleteStudent(Student* head);

int main(void)
{
    int n = -1;
    Student* head = (Student*)malloc(sizeof(Student));
    Student* ptr = NULL;

    head->next = NULL; //head가 가리키는 것이 없음

    do {
        printProgram();
        scanf("%d", &n);
        selectProgram(n, head);
    } while (n != 0);

    ptr = head->next;
    while (ptr != NULL) {
        head = ptr->next;
        free(ptr);
        ptr = head;
    } //메모리 반환

    return 0;
}

void printProgram()
{
    printf("\n1) 저장할 학생 명수 입력\n");
    printf("2) 학생 정보 입력\n");
    printf("3) 학생 목록 출력\n");
    printf("4) 학생 정보 수정(핸드폰 번호)\n");
    printf("5) 학생 정보 수정(학점)\n");
    printf("6) 학생 정보 추가\n");
    printf("7) 학생 정보 삭제\n");
    printf("0) 종료\n");
    printf("입력 : ");
}

void selectProgram(int n, Student* head) {
    if (n==1) makeStudent(head);
    else if (n==2) inputAll(head);
    else if (n==3) printList(head);
    else if (n==4) revisePhone(head);
    else if (n==5) reviseScore(head);
    else if (n==6) addStudent(head);
    else if (n==7) deleteStudent(head);
}

void makeStudent(Student* head) {
    int n = -1;
    printf("학생 수를 입력하세요 : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) { //학생 수 만큼 노드 생성 후 연결
        createStudent(head);
    }
}

void createStudent(Student* head) {
    Student* new_node = (Student*)malloc(sizeof(Student));

    new_node->next = NULL; //새로운 노드의 다음은 NULL
    Student* ptr = NULL;

    if (head->next == NULL) { //head가 가리키는 것이 없으면
        head->next = new_node; //head가 new_node를 가리킴
        new_node = NULL;
        return;
    }

    ptr = head->next; //head가 가리키는 값을 ptr에 대입

    //head가 가리키는 값부터 다음을 가리키는 것이 null이 아닐 때까지
    while (ptr->next != NULL) {
        ptr = ptr->next;
    } //마지막 노드에 도달

    //마지막 노드에 새로운 노드 연결
    ptr->next = new_node;
    new_node = NULL;
}

void inputAll(Student* head)
{
    Student* ptr = head->next;
    while (ptr != NULL) {
        inputInformation(ptr);

        ptr = ptr->next;
        printf("\n");
    }
    ptr = NULL;
}

void inputInformation(Student* ptr){
    printf("학번을 입력하세요 : ");
    scanf("%d", &(ptr->num));
    printf("이름을 입력하세요 : ");
    scanf("%s", ptr->name);
    printf("생년을 입력하세요 : ");
    scanf("%s", ptr->birth);
    printf("핸드폰 번호를 입력하세요 : ");
    scanf("%s", ptr->phone);
    printf("학점을 입력하세요 : ");
    scanf("%f", &(ptr->score));
}


void printList(Student* head) {
    Student* ptr = head->next;

    while (ptr != NULL) {
        printf("학번 : %d\n", ptr->num);
        printf("이름 : %s\n", ptr->name);
        printf("생년 : %s\n", ptr->birth);
        printf("핸드폰 번호 : %s\n", ptr->phone);
        printf("학점 : %.2f\n\n", ptr->score);

        ptr = ptr->next;
    }
}

void revisePhone(Student* head) {
    Student* ptr=head->next;
    int sNum=-1;
    char sPhone[15];

    printf("핸드폰 번호를 바꿀 학번을 입력하세요 : ");
    scanf("%d", &sNum);

    while(ptr!=NULL){
        if (ptr->num==sNum) { //가리키고 있는 노드의 학번이 입력받은 값과 같다면
            printf("새로 바꿀 핸드폰 번호를 입력하세요 : ");//그 노드의 폰 번호를 바꾼다.
            scanf("%s", sPhone);
            strcpy(ptr->phone, sPhone);
            break;
        }
        ptr=ptr->next;
    }
    if (ptr==NULL) printf("\n* 존재하지 않는 학번입니다. *\n");
    else {
        printf("\n< 수정된 내용 >\n");
        printList(head);
    }
}

void reviseScore(Student* head){
    Student* ptr=head->next;
    int sNum=-1;
    float sScore;

    printf("학점을 바꿀 학번을 입력하세요 : ");
    scanf("%d", &sNum);

    while(ptr!=NULL){
        if (ptr->num == sNum) { //가리키고 있는 노드의 학번이 입력받은 값과 같다면
            printf("새로 바꿀 학점을 입력하세요 : ");//그 노드의 폰 번호를 바꾼다.
            scanf("%f", &sScore);
            ptr->score=sScore;
            break;
        }
        ptr=ptr->next;
    }
    if (ptr==NULL) printf("\n* 존재하지 않는 학번입니다. *\n");
    else {
        printf("\n< 수정된 내용 >\n");
        printList(head);
    }
}

void addStudent(Student* head){
    Student* ptr=head->next;

    createStudent(head);
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    inputInformation(ptr);

    printf("\n< 수정된 내용 >\n");
    printList(head);
}

void deleteStudent(Student* head){
    int sNum=-1;
    Student* ptr=NULL; //삭제 노드의 전 노드를 가리키는 포인터
    Student* removed=head->next; //삭제할 노드를 찾는 포인터

    printf("삭제할 학생의 학번을 입력하세요 : ");
    scanf("%d",&sNum);

    while(removed!=NULL){
        if (removed->num==sNum){
            if (ptr==NULL){ //삭제할 노드가 첫 번째 노드일때
                head->next=removed->next;
            }
            else { //삭제할 노드가 첫 번째가 아닐 때
                ptr->next=removed->next; //삭제 노드의 전 노드와 삭제 노드의 다음 노드 연결
            }
            free(removed);
            break; //노드를 삭제했으면 종료
        }
        ptr=removed; //ptr은 삭제 노드의 전 노드를 가리킨다.
        removed=removed->next;
    }
    if (removed==NULL) printf("\n* 존재하지 않는 학번입니다. *\n");
    else {
        printf("\n< 수정된 내용 >\n");
        printList(head);
    }
}
