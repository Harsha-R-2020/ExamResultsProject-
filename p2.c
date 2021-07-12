#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct login
{
    char name[30];
    char username[30];
    char password[20];
};
typedef struct student{
    int rno;
    char name[20];
    struct subject{
        char scode[6];
        int credit;
        int mark;
    }sub[6];
    float gpa;
}student;

void login (void);
void registration (void);
void dispallmarks(void);
void entermarks(void);
void search (char[]);

int main (void)
{
    int option;
    printf("//\t**WELCOME TO EXAMCELL PORTAL**\t//");
    printf("\n1-Register\n2-Login\n\n");
    printf("\nEnter Your Choice : ");
    scanf("%d",&option);

    getchar();

    if(option == 1)
        {
            system("CLS");
            registration();
        }

    else if(option == 2)
        {
            system("CLS");
            login();
        }
}

void login (void)
{
    char username[30],password[20];
    int ch,found=0;
    FILE *log;

    log = fopen("login.txt","r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    struct login l;

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username: ");
    fflush(stdin);
    gets(username);
    printf("\nPassword: ");
    fflush(stdin);
    gets(password);

    while(fread(&l,sizeof(l),1,log))
        {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)

            {
                printf("\nSuccessfully Logged In\n");
                printf("\nWelcome %s \n",l.name);
                if (strcmp(l.username,"admin")==0){
                disp:
                    system("cls");
                    printf("\n//\t**WELCOME ADMIN**\t//");
                    printf("\n1.View Student marks\n");
                    printf("\n2.Enter Student Marks\n");
                    printf("\n3.Log out and Exit\n");
                    printf("\nEnter your Choice : ");
                    scanf("%d",&ch);
                    switch (ch)
                    {
                    case 1:
                        dispallmarks();
                        goto disp;
                        break;

                    case 2:
                        entermarks();
                        goto disp;
                        break;
                    case 3:
                        printf("\nThank You Logging out .....\tHave A Nice Day(:");
                    }
                }
                else{
                    search(username);
                    printf("\nThank You Logging out .....\tHave A Nice Day(:");
                }
                found=1;
            }
        }
        if(!found){
            printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
        }

    fclose(log);
    printf("Press any key.....");
    getch();

    return;
}




void registration(void)
{

    FILE *log;

    log=fopen("login.txt","a");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }


    struct login l;

    printf("\nWelcome Kindly enter your details for registration.\n\n");
    printf("\nEnter your Name:");
    scanf("%s",l.name);
    printf("Thank you.\nNow please choose a username and password as credentials for system login.\n");
    printf("Ensure the username is no more than 30 characters long.\n");
    printf("\nIf you are a Student you should keep your Username as your rollno\n\nAnd do not forget your password \n");
    printf("\nEnter Username:");
    fflush(stdin);
    scanf("%s",l.username);
    printf("\nEnter Password:");
    scanf("%s",l.password);


    fwrite(&l,sizeof(l),1,log);
    fclose(log);

    printf("\nConfirming details...\n...\nWelcome!!!\n\n");
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");
    getch();
    system("CLS");
    login();
}
void entermarks(void){
        student *s;
        FILE *fp;
        int n,i,j;

        printf("Enter how many students : ");
        scanf("%d",&n);
        s = (student*)calloc(n,sizeof(student));
        fp = fopen("mystudents1.txt","a");

        for(i=0;i<n;i++){
            printf("Enter RollNo : ");
            scanf("%d",&s[i].rno);
            fflush(stdin);
            printf("Enter Name : ");
            scanf("%[^\n]s",s[i].name);
            for(j=0;j<6;j++){
                printf("Enter Subject Code : ");
                scanf("%s",s[i].sub[j].scode);
                printf("Enter the Credit Value : ");
                scanf("%d",&s[i].sub[j].credit);
                printf("Enter Marks of Sub%d : ",j+1);
                scanf("%d",&s[i].sub[j].mark);

            }

            fwrite(s+i,sizeof(student),1,fp);
        }
        fclose(fp);
}

void dispallmarks(void){
      student s1;
        FILE *fp;
        int j;
        fp = fopen("mystudents1.txt","r");
        while(fread(&s1,sizeof(student),1,fp))
        {
            printf("\n%-5d%-20s",s1.rno,s1.name);
            for(j=0;j<6;j++){
                printf("%4d",s1.sub[j].mark);
            }
        }
        fclose(fp);
        printf("\nEnter any key to continue.....");
        getch();
}

void search(char username[30]){
    int i, j, found=0,c,c1=0;
    student s1;
    FILE *fp;
    int rno=atoi(username);
    fp = fopen("mystudents1.txt","r");
    printf("\t\tYour Mark Sheet ");
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found = 1;
            c=0;
            printf("\nRoll no:  %d\nName :   %s",s1.rno,s1.name);
            for(j=0;j<6;j++){
                if(s1.sub[j].mark>=91 && s1.sub[j].mark<=100){
                    printf("\nGrade for Subject-%d\t%s\t:\tO",j+1,s1.sub[j].scode);
                    c+=(s1.sub[j].credit)*10;
                }
                else if(s1.sub[j].mark>=81 && s1.sub[j].mark<=90){
                    printf("\n\nGrade for Subject-%d\t%s\t:\tA+",j+1,s1.sub[j].scode);
                    c+=(s1.sub[j].credit)*9;
                }
                else if(s1.sub[j].mark>=71 && s1.sub[j].mark<=80){
                    printf("\n\nGrade for Subject-%d\t%s\t:\tA",j+1,s1.sub[j].scode);
                    c+=(s1.sub[j].credit)*8;
                }
                else if(s1.sub[j].mark>=61 && s1.sub[j].mark<=70){
                    printf("\n\nGrade for Subject-%d\t%s\t:\tB+",j+1,s1.sub[j].scode);
                    c+=(s1.sub[j].credit)*7;
                }
                else if(s1.sub[j].mark>=51 && s1.sub[j].mark<=60){
                    printf("\n\nGrade for Subject-%d\t%s\t:\tB",j+1,s1.sub[j].scode);
                    c+=(s1.sub[j].credit)*6;
                }
                else if(s1.sub[j].mark<=50){
                    printf("\n\nGrade for Subject-%d\t%s\t:\tU",j+1,s1.sub[j].scode);
                }
                c1+=s1.sub[j].credit;
            }
            s1.gpa=c/c1;
            printf("\n\nYour GPA is : %.2f",s1.gpa);
        }
    }
    if(!found)
        printf("\nNot Found.....Make Sure that You have registered your roll no as your user id.... \n");
    fclose(fp);
}
