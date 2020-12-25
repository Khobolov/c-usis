#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lesson
{
    int code;
    char name[15];
    int credit;
    int quota;
    int teacher_id;
};

struct Teacher
{
    int id;
    char name[30];
    char surname[30];
    char title[30];
};

struct Student
{
    int id;
    char name[30];
    char surname[30];
    int lesson_count;
    int credit;
};

int main() {

    struct Lesson lesson;
    struct Teacher teacher;
    struct Student student;

    int ch;
    char firstName[30];

    menus();

    scanf("%d", &ch);
    printf("\n");
    switch (ch)
    {
        case 1:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch)
            {
                case 1:
                    regTeacher(teacher);
                    break;
                case 2:
                    regStudent(student);
                    break;                
            }
            break;

        case 2:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch)
            {
            case 1: 
                //Login Teacher
                printf("*** Welcome to Login Panel for Teachers ***\n\n");

                printf("## Please, Enter your Firstname: ");
                scanf("%s", firstName);

                if (loginTeacher(teacher, firstName) == 1)
                {
                    printf("\n***Hello dear Teacher***\n\n");
                     
                    //Lesson modules
                    menuLesson();
                    scanf("%d", &ch);
                    printf("\n");
                    switch (ch)
                    {
                    case 1:
                        addLesson(lesson);
                        break;
                    case 2:
                        editLesson(lesson);
                        break;
                    case 3:
                        showLesson(lesson);
                        break;
                    case 4: 
                        deleteLesson(lesson);
                        break;
                    }
                    break;
                }
                else
                {
                    printf("There is no teacher with such Name\n");
                }
            
            case 2:
                //Login Student                
                break;
            }

            break;

        case 3:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch)
            {
                case 1:
                    showTeacher(teacher);
                    break;
                case 2:
                    showStudent(student);
                    break;
             }
            break;
    }    

    return 0;
}

void menus()
{
    printf("1.  Register User\n");
    printf("2.  Login User\n");
    printf("3.  Show Users\n");
    printf("Your choice : ");
}

void menuUser()
{
    printf("1.  Teacher\n");
    printf("2.  Student\n");
    printf("Your choice : ");
}

void menuLesson()
{
    printf("1.  Add Lesson\n");
    printf("2.  Edit Lesson\n");
    printf("3.  Show Lessons\n");
    printf("4.  Delete Lesson\n");
    printf("Your choice : ");
}

void regTeacher(struct Teacher teacher)
{
    int id;
    FILE *fptr;

    fptr = fopen("Users/Teachers.txt", "a");

        if(fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }

            printf("Id: ");
            scanf("%d", &id);

        if (availableTeacher(teacher, id) == 1)
        {
            printf("Id %d is Available in the Teachers", id);
        }
        else
        {
                
            teacher.id = id;
            
            printf("Name: ");
            scanf("%s", teacher.name);

            printf("SurName: ");
            scanf("%s", teacher.surname);

            printf("Title: ");
            scanf("%s", teacher.title);

            fwrite (&teacher, sizeof(struct Teacher), 1, fptr);

            if(fwrite != 0) 
                {
                    printf("contents to file written successfully !\n"); 
                } 
                else 
                {
                    printf("error writing file !\n"); 
                }
               
            fclose(fptr);

            printf("Teacher added\n\n");
        }
}

void regStudent(struct Student student)
{
    int id;
    FILE *fptr;

    fptr = fopen("Users/Students.txt", "a");

        if(fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }

            printf("Id: ");
            scanf("%d", &id);

        if (availableStudent(student, id) == 1)
        {
            printf("Id %d is Available in the Students", id);
        }
        else
        {
            student.id = id;
            
            printf("Name: ");
            scanf("%s", student.name);

            printf("Surname: ");
            scanf("%s", student.surname);

            printf("Lesson Count: ");
            scanf("%d", &student.lesson_count);

            printf("Credit: ");
            scanf("%d", &student.credit);

            fwrite (&student, sizeof(struct Student), 1, fptr);

            if(fwrite != 0) 
                {
                    printf("contents to file written successfully !\n"); 
                } 
                else 
                {
                    printf("error writing file !\n"); 
                }
               
            fclose(fptr);

            printf("Student added\n\n");
        }
}

void showTeacher(struct Teacher teacher)
{
    FILE *fptr;

    fptr = fopen("Users/Teachers.txt", "r");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    while(fread(&teacher, sizeof(struct Teacher), 1, fptr)) 
    {
        printf("Id = %d\nName = %s\nSurName = %s\nTitle = %s\n\n", teacher.id, teacher.name, teacher.surname, teacher.title);
    }
        
    fclose (fptr); 
}

void showStudent(struct Student student)
{
    FILE *fptr;

    fptr = fopen("Users/Students.txt", "r");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    while(fread(&student, sizeof(struct Student), 1, fptr)) 
    {
        printf("Id = %d\nName = %s\nSurName = %s\nLesson Count = %d\nCredit: %d\n\n", student.id, student.name, student.surname, student.lesson_count, student.credit);
    }
        
    fclose (fptr); 
}


void addLesson(struct Lesson lesson)
{
    int code;
    FILE *fptr;

    fptr = fopen("Lessons.txt", "a");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    printf("Code: ");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 1)
    {
        printf("Code %d is Available in the Lessons", code);
    }
    else
    {
        lesson.code = code;
        
        printf("Name: ");
        scanf("%s", lesson.name);

        printf("Credit: ");
        scanf("%d", &lesson.credit);

        printf("Quota: ");
        scanf("%d", &lesson.quota);

        fwrite (&lesson, sizeof(struct Lesson), 1, fptr);

        if(fwrite != 0)  
            printf("contents to file written successfully !\n"); 
        else 
            printf("error writing file !\n"); 

        fclose(fptr);

        printf("Lesson added\n\n");
    }

}

void showLesson(struct Lesson lesson)
{
    FILE *fptr;

    fptr = fopen("Lessons.txt", "r");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    while(fread(&lesson, sizeof(struct Lesson), 1, fptr)) 
    {
        printf ("Code = %d\nName = %s\nCredit = %d\nQuota = %d\n\n", lesson.code, lesson.name, lesson.credit, lesson.quota);
    }
        
    fclose (fptr); 
}

//  Update Lesson
void editLesson(struct Lesson lesson)
{
    FILE *fpt;
    FILE *fpo;
    int code, ch;

    printf("Enter Code to update:");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 0)
    {
        printf("Code %d is not Available in the Lessons", code);
    }
    else
    {
        fpo = fopen("Lessons.txt", "r");
        fpt = fopen("LessonTemps.txt", "w");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpo))
        {
        if (lesson.code != code)
            fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
        else
        {
            printf("\n\t1. Update Title: %d of Lesson", lesson.code);
            printf("\n\t2. Update Name: %s of Lesson", lesson.name);
            printf("\n\t3. Update Credit: %d of Lesson", lesson.credit);
            printf("\n\t3. Update Quota: %d of Quota", lesson.quota);
            printf("\nEnter your choice:");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
                printf("Code : ");
                scanf("%d", &lesson.code);
                break;
            case 2:
                printf("Name : ");
                scanf("%s", lesson.name);
                break;
            case 3:
                printf("Credit : ");
                scanf("%d", &lesson.credit);
            case 4:
                printf("Quota : ");
                scanf("%d", &lesson.quota);
                break;
            default:
                printf("Invalid Selection");
                break;
            }
            fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
        }
        }
        fclose(fpo);
        fclose(fpt);

        fpo = fopen("Lessons.txt", "w");
        fpt = fopen("LessonTemps.txt", "r");
        while (fread(&lesson, sizeof(struct Lesson), 1, fpt))
        {
            fwrite(&lesson, sizeof(struct Lesson), 1, fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("Lesson Updated");
    }
}

void deleteLesson(struct Lesson lesson)
{
    FILE *fpo;
    FILE *fpt;
    int code, s;

    printf("Enter the Code you want to Delete :");
    scanf("%d", &code);
    
    if (availableCode(lesson, code) == 0)
    {
        printf("Code %d is not Available in the Lessons\n", code);
    }
    else
    {
        fpo = fopen("Lessons.txt", "r");
        fpt = fopen("LessonTemps.txt", "w");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpo))
        {
        if (lesson.code != code)
            fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
        }
        fclose(fpo);
        fclose(fpt);
        
        fpo = fopen("Lessons.txt", "w");
        fpt = fopen("LessonTemps.txt", "r");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpt))
        {
            fwrite(&lesson, sizeof(struct Lesson), 1, fpo);
        }
        
        printf("\nLesson deleted!\n");
        fclose(fpo);
        fclose(fpt);
    }
    
}

//  Count Line //
// int countLine(struct Lesson lesson)
// {
//     int linesCount = 0;
//     FILE *fptr;

//     fptr = fopen("Lessons.txt", "r");

//     if(fptr == NULL)
//     {
//         printf("Error!");
//         exit(1);
//     }

//     while(fread(&lesson, sizeof(struct Lesson), 1, fptr)) {
//          linesCount++;
//    }
//     fclose(fptr);

//     return linesCount;
// }

//  Check ID is Available //
int availableCode(struct Lesson lesson, int code)
{
    FILE *fp;

    fp = fopen("Lessons.txt", "r");
    
    while (!feof(fp))
    {
        fread(&lesson, sizeof(struct Lesson), 1, fp);

        if (code == lesson.code)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

int availableTeacher(struct Teacher teacher, int id)
{
    FILE *fp;

    fp = fopen("Users/Teachers.txt", "r");
    
    while (!feof(fp))
    {

        fread(&teacher, sizeof(struct Teacher), 1, fp);

        if (id == teacher.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

int availableStudent(struct Student student, int id)
{
    FILE *fp;

    fp = fopen("Users/Students.txt", "r");
    
    while (!feof(fp))
    {

        fread(&student, sizeof(struct Student), 1, fp);

        if (id == student.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

int loginTeacher(struct Teacher teacher, char firstname[])
{
    FILE *fp;

    fp = fopen("Users/Teachers.txt", "r");
    
    while (!feof(fp))
    {

        fread(&teacher, sizeof(struct Teacher), 1, fp);

        if (strcmp(firstname, teacher.name) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}