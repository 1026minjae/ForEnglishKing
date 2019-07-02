#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
#include <conio.h>

#define CLEAR system("CLS");
#define PAUSE system("PAUSE");
#define GotoXY(Pos) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos)

#define ANSWER SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

enum {BACKSPACE=8,TAB,ENTER=13,UP=72,DOWN=80};

using namespace std;

int choose_File();
int choose_Hat_Suck_File();
void StarLine(int n);

char txtfiles[200][70];

char sentences[20][360];
char haeseok[20][720];

char ch[205];

FILE *fp;
FILE *fp_h;

int main()
{
    int sent_cnt;
    int haeseok_cnt;
    int letter_cnt; //한문장에 글자가 몇 개인지 셉니다
    char c;

    START:
    WHITE
    if((sent_cnt=choose_File())==-1) return 0; CLEAR
    if((sent_cnt=choose_Hat_Suck_File())==-1) return 0; CLEAR

    sent_cnt=0;
    haeseok_cnt=0;
    letter_cnt=0;

    while((c=fgetc(fp))!=EOF)
    {
        if(c=='.' || c=='?' || c=='!' || c==':' || c==';')
        {
            sentences[sent_cnt][letter_cnt++]='.';
            sentences[sent_cnt][letter_cnt]='\0';
            sent_cnt++;
            letter_cnt=0;
        }
        else
        {
            sentences[sent_cnt][letter_cnt++]=c;
        }
    }
    fclose(fp);

    while((c=fgetc(fp_h))!=EOF) //한글도 되나? 되네...
    {
        if(c=='.' || c=='?' || c=='!' || c==':' || c==';')
        {
            sentences[haeseok_cnt][letter_cnt++]='.';
            sentences[haeseok_cnt][letter_cnt]='\0';
            haeseok_cnt++;
            letter_cnt=0;
        }
        else
        {
            haeseok[haeseok_cnt][letter_cnt++]=c;
        }
    }
    fclose(fp_h);

    CONTIN:
    cout<<"영작하여라"<<endl;
    for(int i=0;i<sent_cnt;i++)
    {
        cout<<haeseok[i]<<endl;
        cout<<"[영작>";
        cin.getline(ch, 200);
        ANSWER
        cout<<sentences[i]<<endl;
        WHITE
    }

    cout<<"다시 하시겠습니까?(Y/N) : "<<endl;
    if((c=getch())=='Y' || c == 'y')
    {
        cout<<"동일한 파일로 다시하시겠습니까? (Y/N) : "<<endl;
        if((c=getch())=='Y' || c=='y')
        {
            CLEAR
            goto CONTIN;
        }
        else
        {
            CLEAR
            goto START;
        }
    }

    return 0;
}

int choose_File()
{
    struct dirent *de;
    char file_cnt=0;
    char point=0;
    char c;
    char fileloc[78];
    COORD cursor={0,2};
    DIR *dr = opendir("\File");

    if (dr == NULL)  // 디렉토리가 안 열리면 오류를 표시한다.
    {
        CLEAR
        printf("File 폴더가 없습니다. 다시 한번 확인해주세요.\n" );
        PAUSE
        return -1;
    }

    while ((de = readdir(dr)) != NULL)
    {
        if(!strcmp(de->d_name, "."))
            continue;
        else if(!strcmp(de->d_name, ".."))
            continue;
        strcpy(txtfiles[file_cnt++], de->d_name);
    }
    closedir(dr);

    if(file_cnt==0)
    {
        printf("* 학습할 수 있는 파일이 File 폴더 안에 존재하지 않습니다. 파일을 제대로 넣었는지 다시 확인해주세요. *\n"); PAUSE
        return -1;
    }

    StarLine(80);
    printf("* 학습할 파일을 선택해주세요 *\n");
    for(c=0;c<file_cnt;c++)
        printf("\t%s\n",txtfiles[c]);

    PRINT:
    GotoXY(cursor);
    printf("        ");
    cursor.Y=point+2;
    GotoXY(cursor);
    printf("[학습>");
    while((c=getch())!=ENTER)
    {
        switch(c)
        {
        case UP:
            if(point!=0)
                point--;
            break;
        case DOWN:
            if(point!=file_cnt-1)
                point++;
            break;
        }
        goto PRINT;
    }

    strcat(fileloc,"File\\");
    strcat(fileloc,txtfiles[point]);
    fp=fopen(fileloc,"r+");

    return 0;
}

int choose_Hat_Suck_File()
{
    struct dirent *de;
    char file_cnt=0;
    char point=0;
    char c;
    char fileloc[90];
    COORD cursor={0,2};
    DIR *dr = opendir("\HaeseokFile");

    if (dr == NULL)  // 디렉토리가 안 열리면 오류를 표시한다.
    {
        CLEAR
        printf("HaeseokFile 폴더가 없습니다. 다시 한번 확인해주세요.\n" );
        PAUSE
        return -1;
    }

    while ((de = readdir(dr)) != NULL)
    {
        if(!strcmp(de->d_name, "."))
            continue;
        else if(!strcmp(de->d_name, ".."))
            continue;
        strcpy(txtfiles[file_cnt++], de->d_name);
    }
    closedir(dr);

    if(file_cnt==0)
    {
        printf("* 학습할 수 있는 파일이 HaeseokFile 폴더 안에 존재하지 않습니다. 파일을 제대로 넣었는지 다시 확인해주세요. *\n"); PAUSE
        return -1;
    }

    StarLine(80);
    printf("* 학습할 파일을 선택해주세요 *\n");
    for(c=0;c<file_cnt;c++)
        printf("\t%s\n",txtfiles[c]);

    PRINT:
    GotoXY(cursor);
    printf("        ");
    cursor.Y=point+2;
    GotoXY(cursor);
    printf("[학습>");
    while((c=getch())!=ENTER)
    {
        switch(c)
        {
        case UP:
            if(point!=0)
                point--;
            break;
        case DOWN:
            if(point!=file_cnt-1)
                point++;
            break;
        }
        goto PRINT;
    }

    strcpy(fileloc,"");
    strcat(fileloc,"HaeseokFile\\");
    strcat(fileloc,txtfiles[point]);
    fp_h=fopen(fileloc,"r+");

    return 0;
}

void StarLine(int n)
{
    int i;

    for(i=0;i<n;i++)
        cout<<"*";
    cout<<endl;
    return;
}
