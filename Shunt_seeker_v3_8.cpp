#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <math.h>
#include <time.h>
#include <cstring>
#include "windows.h"
#include <shellapi.h>
#pragma comment(lib,"shell32.lib")
static HWND hBut;
float fs;
float X1;
char key1;
char str_global[90]="4_А-К_1ф";
char str_table[90]="Angara.gtb";
TCHAR str_path[MAX_PATH];
double time_shunt = 100.;
char time_shunt_old[8] = "100.000";
float V_ust;
using namespace std;

void Ust_rej() {
    char str_path1[90];
    strncpy(str_path1,str_path,strlen(str_path)-8);
    char str1[90]="C:\\Eurostag43\\Eurostag\\eustag_cpt.exe -lf ";
    char str2[90]="\\статика\\regim.ech";

    strcat(str1,str_path1);
    strcat(str1,str2);

    STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess(NULL,TEXT(str1),
		NULL,NULL,FALSE,NULL,NULL,NULL,&cif,&pi)==TRUE)
	{
		cout << "process" << endl;
		cout << "handle " << pi.hProcess << endl;
     WaitForSingleObject(pi.hProcess, INFINITE);
    // выполняем какой-либо код
//    ShowMessage("end of process");
    // закрываем хэндлы основного потока/процесса
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

//		Sleep(3000);				// подождать

	}
	}
void Pereh_proc(){
    char str_path1[90];
    strncpy(str_path1,str_path,strlen(str_path)-8);
    char str1[90]="C:\\Eurostag43\\Eurostag\\eustag_cpt.exe -s ";
    char str2[90]="\\события\\";
    char str3[90]="\\ДИНАМИКА\\ГЕНЕРАТОРЫ ";
    char str4[90]="\\статика\\regim";

    strcat(str1,str_path1);
    strcat(str1,str2);
    strcat(str1,str_global);
    strcat(str1," ");
    strcat(str1,str_path1);
    strcat(str1,str3);
    strcat(str1,str_path1);
    strcat(str1,str4);

    cout << str1 <<  endl;

    STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;

	if (CreateProcess(NULL,TEXT(str1),
		NULL,NULL,FALSE,NULL,NULL,NULL,&cif,&pi)==TRUE)
	{
		cout << "process" << endl;
		cout << "handle " << pi.hProcess << endl;
     WaitForSingleObject(pi.hProcess, INFINITE);
    // выполняем какой-либо код
//    ShowMessage("end of process");
    // закрываем хэндлы основного потока/процесса
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
	}
}

void Tabl_proc() {
    char str_path1[90];
    strncpy(str_path1,str_path,strlen(str_path)-8);
    char str1[90]="C:\\Eurostag43\\Eurostag\\eustag_t.exe ";
    char str2[90]="\\события\\";
    char str3[90]="\\события\\";
    char str4[90]=".res";

    strcat(str1,str_path1);
    strcat(str1,str2);
    strcat(str1,str_table);
    strcat(str1," ");
    strcat(str1,str_path1);
    strcat(str1,str3);
    strcat(str1,str_global);
    strcat(str1,str4);

    STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
    if (CreateProcess(NULL,TEXT(str1),
		NULL,NULL,FALSE,NULL,NULL,NULL,&cif,&pi)==TRUE)
	{
		cout << "process" << endl;
		cout << "handle " << pi.hProcess << endl;
     WaitForSingleObject(pi.hProcess, INFINITE);
    // выполняем какой-либо код
//    ShowMessage("end of process");
    // закрываем хэндлы основного потока/процесса
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
	}
}

void Voltage_to_fs() {
int n=0;
int a;
fstream F;
char str1[90];
strcpy(str1,str_path);
strcat(str1,"\\eurostag_t.out");

F.open(str1);
if (F)
{
 char word[64] ;
 char one[64], two[64], three[64], four[64], five[64], six[64];
 char drob[64];
   while (! F.eof())

   {

   F >> drob;
   F >> two;
   F >> three;
   F >> four;
   F >> five;
   F >> six;

   }
cout << drob << endl;
cout << two << endl;
cout << three << endl;
cout << four << endl;
cout << five << endl;
cout << six << endl;

fs = atof(drob);//this is much better way to do it
//fs=fs+250;
cout << fs << endl;

F.close();
cout << fs << endl;
}




}

void Extract_X1()
{fstream F1;
    char str1[90];
    char str2[90]=".seq";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,str_global);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);


    while ( atof(word1) !=time_shunt)
    {F1 >> word1;
     cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
//    cout << "dobralis' do zadannogo vremeni" << endl;

    F1.seekg(F1.tellg()+56);
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
    X1=atof(word1);
    cout << word1;
    F1.seekp(pos);

    F1 << X1;
    F1.close();
    }
}

void Put_X1_in_calc()
{fstream F1;
    char str1[90];
    char str2[90]=".seq";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,str_global);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);
    while ( atof(word1) !=time_shunt)
    {F1 >> word1;
    cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
    F1.seekg(F1.tellg()+56);
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
//    X1=atof(word1);

    cout << word1;

    F1.seekp(pos);
    F1 << X1;
    F1.close();
    Pereh_proc();
    Tabl_proc();
    Voltage_to_fs();
    }
}

void Change_stoptime()
{fstream F1;
    char str1[90];
    char str2[90]=".seq";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,str_global);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);
    while ( atof(word1) !=200.)
    {F1 >> word1;
    cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
    F1.seekg(F1.tellg());
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
    F1.seekp(pos-7);
    F1 << 101.;
    F1.close();
     }
}

void Change_time_gtb(char *name_gtb)
{fstream F1;
    char str1[90];
    char str2[90]=".gtb";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,name_gtb);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);
    while ( atof(word1) !=100.000000)
    {F1 >> word1;
    cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
    F1.seekg(F1.tellg());
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
    F1.seekg(pos-27);
    F1 << time_shunt;
    F1.close();
     }
}

void Change_btime_gtb(char *name_gtb)
{fstream F1;
    char str1[90];
    char str2[90]=".gtb";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,name_gtb);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);
    while ( atof(word1) !=time_shunt)
    {F1 >> word1;
    cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
    F1.seekg(F1.tellg());
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
    F1.seekg(pos-27);
    F1 << time_shunt_old;
    F1.close();
//    cin >> key1;
     }
}

void Back_stoptime()
{fstream F1;
    char str1[90];
    char str2[90]=".seq";
    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,str_global);
    strcat(str1,str2);
F1.open(str1);
if(F1) {
    char word1[64];
    F1.seekg(0);
    while ( atof(word1) !=101.)
    {F1 >> word1;
    cout << word1 << endl;
 //    cout << F1.tellg() << endl;
 //    cout << F1.tellp() << endl;
    Sleep(30);
    }
    F1.seekg(F1.tellg());
    std::ios::pos_type pos = F1.tellg();
    F1 >> word1;
    F1.seekp(pos-7);
    F1 << 200.;
    F1.close();
     }
}

  // Функция отображения русских символов--------------------------------------
void shunt_seeker_main ()

{
    Change_stoptime();


    Ust_rej();
    Pereh_proc();
    Tabl_proc();
    Voltage_to_fs();
    Extract_X1();

   while (( fabs(fs-V_ust) > V_ust*0.02) or (fs > V_ust))
    {
        if (fs < V_ust)
    { X1=X1*1.01;
      X1=X1*100000;
      X1=floor(X1);
      X1=X1/100000;
    }
    if (fs > V_ust)
    { X1=X1*0.99;
      X1=X1*100000;
      X1=floor(X1);
      X1=X1/100000;
    }


    Put_X1_in_calc();
    }
    Back_stoptime();
     cout << "first bookmark 2\n";
     Sleep(3000);
}

void time_to_log()
{fstream F2;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    cout << "Current time & date: " << asctime (timeinfo);

    char str1[90];
    char str2[90]="shunt.log";

    strcpy(str1,str_path);
    strcat(str1,"\\");
    strcat(str1,str2);
F2.open(str1, ios::out | ios::app);
if(F2) {

    F2 << "Current time & date: " << asctime (timeinfo)<< endl;
     }
F2.close();
}
int main()
{ //setlocale(0, "rus");



    SetConsoleCP(1251);
    SetConsoleOutputCP(866);

    GetCurrentDirectory(sizeof(str_path),str_path);
    ofstream ofs("shunt.log"); //создать
    ofs.close();
    time_to_log();

    char arr[30][20], file_list1[90];
    int i=0;
    float V_Boges500_0f, V_Boges500_1f, V_Boges500_2f, V_Boges220_0f, V_Boges220_1f, V_Angara500_0f, V_Angara500_1f, V_Angara500_2f;


   WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf = FindFirstFile(".\\*.seq",&FindFileData);
    if(hf != INVALID_HANDLE_VALUE){int i1=1;
        do{
            cout << FindFileData.cFileName << "\n";
            strcpy(arr[i1], TEXT(FindFileData.cFileName));
            i1++;
        }
        while(FindNextFile(hf,&FindFileData) != 0);
        FindClose(hf);
        i=i1-1;
        cout << i << "\n";
    }

   //!!!!!!!!!!!!!!!!!!!!!!!
    cout << "Enter the V_ust for V_Boges500_0f\n";
    cin >> V_Boges500_0f;
   //!!!!!!!!!!!!!!!!!!!!!!!
    cout << "Enter the V_ust for V_Boges500_1f\n";
    cin >> V_Boges500_1f;

    cout << "Enter the V_ust for V_Boges500_2f\n";
    cin >> V_Boges500_2f;

    cout << "Enter the V_ust for V_Boges220_0f\n";
    cin >> V_Boges220_0f;

    cout << "Enter the V_ust for V_Boges220_1f\n";
    cin >> V_Boges220_1f;

    cout << "Enter the V_ust for V_Angara500_0f\n";
    cin >> V_Angara500_0f;

    cout << "Enter the V_ust for V_Angara500_1f\n";
    cin >> V_Angara500_1f;

    cout << "Enter the V_ust for V_Angara500_2f\n";
    cin >> V_Angara500_2f;





   while (i>0){

    cout << arr[i] << "\n";
    strcpy(str_global,arr[i]);
    cout << str_global << "\n" ;



 if (strcmp(str_global,"4_А-К_0ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_0f;
    shunt_seeker_main ();
    cout << "first bookmark 1\n";
    }

 if (strcmp(str_global,"4_А-К_1ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_1f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_А-К_2ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_А-К_ОГ-1_0ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_ОГ-1_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_0f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_А-К_ОГ-1_2ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_ОГ-1_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_А-К_ОГ-2_2ф.seq")==0)
    {
    strcpy(str_global, "4_А-К_ОГ-2_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

if (strcmp(str_global,"4_А-О_2ф.seq")==0)
    {
    strcpy(str_global, "4_А-О_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

if (strcmp(str_global,"4_А-О_1ф.seq")==0)
    {
    strcpy(str_global, "4_А-О_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_1f;
    shunt_seeker_main ();
    }

if (strcmp(str_global,"4_А-О_0ф.seq")==0)
    {
    strcpy(str_global, "4_А-О_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_0f;
    shunt_seeker_main ();
    }

if (strcmp(str_global,"4_А-О_ОГ-1_0ф.seq")==0)
    {
    strcpy(str_global, "4_А-О_ОГ-1_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_0f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_А-О_ОГ-1_2ф.seq")==0)
    {
    strcpy(str_global, "4_А-О_ОГ-1_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_АТ_2ф.seq")==0)
    {
    strcpy(str_global, "4_АТ_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-А_1ф.seq")==0)
    {
    strcpy(str_global, "4_Б-А_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_1f;
    shunt_seeker_main ();
    }

     if (strcmp(str_global,"4_Б-А_0ф.seq")==0)
    {
    strcpy(str_global, "4_Б-А_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_0f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-А_2ф.seq")==0)
    {
    strcpy(str_global, "4_Б-А_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-А_ОГ-1.seq")==0)
    {
    strcpy(str_global, "4_Б-А_ОГ-1");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-О_2ф.seq")==0)
    {
    strcpy(str_global, "4_Б-О_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-О_ОГ-1_0ф.seq")==0)
    {
    strcpy(str_global, "4_Б-О_ОГ-1_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_0f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"5_уровБ-О_0ф.seq")==0)
    {
    strcpy(str_global, "5_уровБ-О_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_0f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"5_уровБ-О_1ф.seq")==0)
    {
    strcpy(str_global, "5_уровБ-О_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_1f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_Б-О_ОГ-1_2ф.seq")==0)
    {
    strcpy(str_global, "4_Б-О_ОГ-1_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"4_уровБ-Пр.seq")==0)
    {
    strcpy(str_global, "4_уровБ-Пр");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"7_Б-Пр_0ф.seq")==0)
    {
    strcpy(str_global, "7_Б-Пр_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_0f;
    shunt_seeker_main ();
    }

     if (strcmp(str_global,"3_АТ_0ф.seq")==0)
    {
    strcpy(str_global, "3_АТ_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_0f;
    shunt_seeker_main ();
    }

     if (strcmp(str_global,"3_АТ_1ф.seq")==0)
    {
    strcpy(str_global, "3_АТ_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

         if (strcmp(str_global,"3_АТ_1ф1.seq")==0)
    {
    strcpy(str_global, "3_АТ_1ф1");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

         if (strcmp(str_global,"3_Б-П_рА_0ф.seq")==0)
    {
    strcpy(str_global, "3_Б-П_рА_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_0f;
    shunt_seeker_main ();
    }

             if (strcmp(str_global,"ПР_7_АТ_0ф1.seq")==0)
    {
    strcpy(str_global, "ПР_7_АТ_0ф1");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_0f;
    shunt_seeker_main ();
    }

             if (strcmp(str_global,"ОС_7_АТ_0ф.seq")==0)
    {
    strcpy(str_global, "ОС_7_АТ_0ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_0f;
    shunt_seeker_main ();
    }

             if (strcmp(str_global,"3_Б-П_рА_1ф.seq")==0)
    {
    strcpy(str_global, "3_Б-П_рА_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

                 if (strcmp(str_global,"ПР_7_АТ_1ф1.seq")==0)
    {
    strcpy(str_global, "ПР_7_АТ_1ф1");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

                     if (strcmp(str_global,"ПР_7_ур_Пр-Р_1ф.seq")==0)
    {
    strcpy(str_global, "ПР_7_ур_Пр-Р_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

                         if (strcmp(str_global,"ПР_ОГ-220_7_Б-Пр.seq")==0)
    {
    strcpy(str_global, "ПР_ОГ-220_7_Б-Пр");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }


     if (strcmp(str_global,"7_Б-Пр_1ф.seq")==0)
    {
    strcpy(str_global, "7_Б-Пр_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"АПВ_4_А-К_2ф.seq")==0)
    {
    strcpy(str_global, "АПВ_4_А-К_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    }

 if (strcmp(str_global,"5_уров_А-К.seq")==0)
    {
    strcpy(str_global, "5_уров_А-К");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urov_A-K.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 500 kV Angara-Kamala-1 is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Angara");
    shunt_seeker_main ();
    Change_btime_gtb("Angara");
    time_shunt = 100.;
    }

 if (strcmp(str_global,"5_уров_А-О.seq")==0)
    {
    strcpy(str_global, "5_уров_А-О");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Angara.gtb");
    V_ust=V_Angara500_2f;
    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urov_A-O.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 500 kV Angara-Ozernaya is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Angara");
    shunt_seeker_main ();
    Change_btime_gtb("Angara");
    time_shunt = 100.;
    }

 if (strcmp(str_global,"5_уров_Б-А.seq")==0)
    {
    strcpy(str_global, "5_уров_Б-А");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urov_B-A.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 500 kV Boges-Angara is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Boges500");
    shunt_seeker_main ();
    Change_btime_gtb("Boges500");
    time_shunt = 100.;
    }

 if (strcmp(str_global,"5_уров_Б-Пр.seq")==0)
    {
    strcpy(str_global, "5_уров_Б-Пр");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
//    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urov_B-Pr.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 220 kV Boges-Priangarskaya is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Boges220");
    shunt_seeker_main ();
    Change_btime_gtb("Boges220");
    time_shunt = 100.;
    }

     if (strcmp(str_global,"4_уров_Б-Пр.seq")==0)
    {
    strcpy(str_global, "4_уров_Б-Пр");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges220.gtb");
    V_ust=V_Boges220_1f;
//    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '4_urov_B-Pr.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 220 kV Boges-Priangarskaya is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Boges220");
    shunt_seeker_main ();
    Change_btime_gtb("Boges220");
    time_shunt = 100.;
    }

 if (strcmp(str_global,"5_уров500_АТ.seq")==0)
    {
    strcpy(str_global, "5_уров500_АТ");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urov500_AT.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When AT1 (AT2) is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Boges500");
    shunt_seeker_main ();
    Change_btime_gtb("Boges500");
    time_shunt = 100.;
    }

 if (strcmp(str_global,"5_уровБ-О_2ф.seq")==0)
    {
    strcpy(str_global, "5_уровБ-О_2ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_2f;
    shunt_seeker_main ();
    cout << "-----------Vozmuchenie '5_urovB-O_2f.seq'------------------ \n";
    cout << "Enter the time of otkaz fazi circuit breaker gtb\n";
    cin >> time_shunt;
    cout << "Utochnite ostatochnoe pri Odnofaznom KZ U(When VL 500 kV Boges-Ozernaya is off) \n";
    cin >>  V_ust;
    Change_time_gtb("Boges500");
    shunt_seeker_main ();
    Change_btime_gtb("Boges500");
    time_shunt = 100.;
    }
                 if (strcmp(str_global,"4_Б-О_1ф.seq")==0)
    {
    strcpy(str_global, "4_Б-О_1ф");
    cout << "Enter the name of table (with .gtb)\n";
    strcpy(str_table, "Boges500.gtb");
    V_ust=V_Boges500_1f;
    shunt_seeker_main ();
    }

   i--;
   }
   cout << i << "\n";

   time_to_log();
   FreeConsole();
   MessageBoxA(NULL, str_path, "Calculations status", MB_SYSTEMMODAL|MB_OK);

}





