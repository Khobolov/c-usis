#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lesson {
    int code;
    char name[15];
    int credit;
    int quota;
    int teacher_id;
};

struct Teacher {
    int id;
    char nickname[15];
    char name[21];
    char surname[21];
    char title[21];
};

struct Student {
    int id;
    char nickname[15];
    char name[21];
    char surname[21];
    int lesson_count;
    int credit;
};

struct StudentLessonRegistration {
    int id;
    int code;
};


int main() {

    struct Lesson lesson;
    struct Teacher teacher;
    struct Student student;
    struct StudentLessonRegistration studentReg;

    int ch, idCountTeacher, idCountStudent;
    int techId, studentId;
    char nickName[15];


    menus();

    scanf("%d", &ch);
    printf("\n");
    switch (ch) {
        case 1:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch) {
                case 1:
                    idCountTeacher = countTeacher(teacher);
                    regTeacher(teacher, idCountTeacher);
                    break;
                case 2:
                    idCountStudent = countStudent(student);
                    regStudent(student, idCountStudent);
                    break;
            }
            break;

        case 2:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch) {
                case 1:
                    //  Login Teacher
                    printf("*** Welcome to Login Panel for Teachers ***\n\n");

                    printf("## Please, Enter your Nickname: ");
                    scanf("%s", nickName);

                    if (availableTeacher(teacher, nickName) == 1) {
                        printf("\n*** Hello dear Teacher ***\n\n");

                        //  Lesson modules
                        menuLesson();

                        //  Find Teacher id with Nickname
                        techId = findTeachId(teacher, nickName);

                        scanf("%d", &ch);
                        printf("\n");
                        switch (ch) {
                            case 1:
                                addLesson(lesson, techId);
                                break;
                            case 2:
                                editLesson(lesson, techId);
                                break;
                            case 3:
                                showLesson(lesson, techId);
                                break;
                            case 4:
                                deleteLesson(lesson); // * Delete //
                                break;
                        }

                    } else {
                        printf("There is no teacher with such Nickname\n");
                    }

                    break;

                case 2:
                    //Login Student
                    printf("*** Welcome to Login Panel for Students ***\n\n");

                    printf("## Please, Enter your Nickname: ");
                    scanf("%s", nickName);

                    if (availableStudent(student, nickName) == 1) {
                        printf("\n*** Hello dear Sdutent ***\n\n");

                        //  Student module
                        menuStudent();

                        //  Find Student id with Nickname
                        studentId = findStudentId(student, nickName);

                        scanf("%d", &ch);
                        printf("\n");
                        switch (ch) {
                            case 1:
                                showLessonForStudent(lesson);
                                break;

                            case 2:
                                studentLessonReg(student, lesson, studentReg, studentId);
                                break;

                            case 3:
                                showLessonRegistered(studentReg, studentId);
                                break;

                            default:
                                break;
                        }

                    } else {
                        printf("There is no student with such Nickname\n");
                    }

                    break;
            }

            break;

        case 3:
            menuUser();
            scanf("%d", &ch);
            printf("\n");
            switch (ch) {
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

void menus() {
    printf("1.  Register User\n");
    printf("2.  Login User\n");
    printf("3.  Show Users\n");
    printf("Your choice : ");
}

void menuUser() {
    printf("1.  Teacher\n");
    printf("2.  Student\n");
    printf("Your choice : ");
}

void menuLesson() {
    printf("1.  Add Lesson\n");
    printf("2.  Edit Lesson\n");
    printf("3.  Show Lessons\n");
    printf("4.  Delete Lesson\n");
    printf("Your choice : ");
}

void menuStudent() {
    printf("1.  Show All Lesson\n");
    printf("2.  Join Lesson\n");
    printf("3.  Show Registered Lesson");
    printf("Your choice : ");
}

void regTeacher(struct Teacher teacher, int id) {
    char nickname[15];
    FILE *fptr;

    fptr = fopen("Users/Teachers.txt", "a");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    printf("Nickname: ");
    scanf("%s", nickname);

    if (availableTeacher(teacher, nickname) == 1) {
        printf("Nickname: %s is Available in the Teachers", nickname);
    } else {
        teacher.id = id;
        strcpy(teacher.nickname, nickname);

        printf("Name: ");
        scanf("%s", teacher.name);

        printf("Surname: ");
        scanf("%s", teacher.surname);

        printf("Title: ");
        scanf("%s", teacher.title);

        fwrite(&teacher, sizeof(struct Teacher), 1, fptr);

        if (fwrite != 0) {
            printf("contents to file written successfully !\n");
        } else {
            printf("error writing file !\n");
        }

        fclose(fptr);

        printf("Teacher added\n\n");
    }
}

void regStudent(struct Student student, int id) {
    char nickname[15];
    FILE *fptr;

    fptr = fopen("Users/Students.txt", "a");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    printf("Nickname: ");
    scanf("%s", nickname);

    if (availableStudent(student, nickname) == 1) {
        printf("Nickname %s is Available in the Students", nickname);
    } else {
        student.id = id;
        strcpy(student.nickname, nickname);

        printf("Name: ");
        scanf("%s", student.name);

        printf("Surname: ");
        scanf("%s", student.surname);

        student.lesson_count = 0; //default
        student.credit = 0; //default

        fwrite(&student, sizeof(struct Student), 1, fptr);

        if (fwrite != 0) {
            printf("contents to file written successfully !\n");
        } else {
            printf("error writing file !\n");
        }

        fclose(fptr);

        printf("Student added\n\n");
    }
}

void showTeacher(struct Teacher teacher) {
    FILE *fptr;

    fptr = fopen("Users/Teachers.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&teacher, sizeof(struct Teacher), 1, fptr)) {
        printf("Id = %d\nNickname = %s\nName = %s\nSurName = %s\nTitle = %s\n\n", teacher.id, teacher.nickname,
               teacher.name, teacher.surname, teacher.title);
    }

    fclose(fptr);
}

void showStudent(struct Student student) {
    FILE *fptr;

    fptr = fopen("Users/Students.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&student, sizeof(struct Student), 1, fptr)) {
        printf("Id = %d\nNickname = %s\nName = %s\nSurName = %s\nLesson Count = %d\nCredit: %d\n\n", student.id,
               student.nickname, student.name, student.surname, student.lesson_count, student.credit);
    }

    fclose(fptr);
}

//  Add Lesson  //
void addLesson(struct Lesson lesson, int teacher_id) {
    int code;
    FILE *fptr;

    fptr = fopen("Lessons.txt", "a");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    printf("Code: ");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 1) {
        printf("Code %d is Available in the Lessons", code);
    } else {
        lesson.code = code;
        lesson.teacher_id = teacher_id;

        printf("Name: ");
        scanf("%s", lesson.name);

        printf("Credit: ");
        scanf("%d", &lesson.credit);

        printf("Quota: ");
        scanf("%d", &lesson.quota);

        fwrite(&lesson, sizeof(struct Lesson), 1, fptr);

        if (fwrite != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");

        fclose(fptr);

        printf("Lesson added\n\n");
    }

}

//  Student register to Lesson  //
void studentLessonReg(struct Student student, struct Lesson lesson, struct StudentLessonRegistration studentReg, int id) {
    int code, lessonCredit, studentOldCredit, studentNewCredit;
    FILE *fptr, *fpo, *fpw, *fpl;
    int checkReg, checkQuo;

    fptr = fopen("StudentLessonRegistration.txt", "a");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    printf("Code: ");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 0) {
        printf("Code %d is not Available in the Lessons", code);
    } else {

        checkReg = checkLessonReg(studentReg, id, code);

        if (checkReg == 0) {
            checkQuo = checkQuota(lesson, studentReg, code);

            if (checkQuo == 0) {
                studentReg.id = id;
                studentReg.code = code;

                fwrite(&studentReg, sizeof(struct StudentLessonRegistration), 1, fptr);

                if (fwrite != 0)
                    printf("contents to << StudentLessonRegistration >> file written successfully !\n");
                else
                    printf("error writing to << StudentLessonRegistration >> file !\n");

                fclose(fptr);


                fpl = fopen("Lessons.txt", "r");

                if (fpl == NULL) {
                    printf("Error!");
                    exit(1);
                }

                while (fread(&lesson, sizeof(struct Lesson), 1, fpl))
                {
                  if (lesson.code == code)
                  {
                      lessonCredit = lesson.credit;
                  }
                  
                }
                fclose(fpl);


                fpo = fopen("Users/Students.txt", "r");
                fpw = fopen("Users/StudentTemps.txt", "w");

                if (fpo == NULL) {
                    printf("Error!");
                    exit(1);
                }

                if (fpw == NULL) {
                    printf("Error!");
                    exit(1);
                }

                while (fread(&student, sizeof(struct Student), 1, fpo))
                {
                   if (student.id == id)
                   {
                        studentOldCredit = student.credit;

                        studentNewCredit = lessonCredit + studentOldCredit;

                        student.credit = studentNewCredit;

                        fwrite(&student, sizeof(struct Student), 1, fpw);

                        if (fwrite != 0){
                            printf("contents to << Student >> file written successfully !\n");
                        } else{
                            printf("error writing to << Student >> file !\n");
                        }
                   }else
                   {
                       fwrite(&student, sizeof(struct Student), 1, fpw);
                   }
                   
                }
                fclose(fpo);
                fclose(fpw);


                fpo = fopen("Users/StudentTemps.txt", "r");
                fpw = fopen("Users/Students.txt", "w");
                while (fread(&lesson, sizeof(struct Student), 1, fpo)) {
                    fwrite(&lesson, sizeof(struct Student), 1, fpw);
                }
                fclose(fpo);
                fclose(fpw);

                printf("Lesson registration success\n\n");

            } else {
                printf("Quota limit detected");
            }
        } else {
            printf("Registration limit detected");
        }

    }
}

//  Show Lessons for Teacher    //
void showLesson(struct Lesson lesson, int id) {
    FILE *fptr;

    fptr = fopen("Lessons.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&lesson, sizeof(struct Lesson), 1, fptr)) {
        if (lesson.teacher_id == id) {
            printf("Code = %d\nName = %s\nCredit = %d\nQuota = %d\nTeacher Id = %d\n\n", lesson.code, lesson.name,
                   lesson.credit, lesson.quota, lesson.teacher_id);
        }
    }

    fclose(fptr);
}

//  Show Lessons for Students    //
void showLessonForStudent(struct Lesson lesson) {
    FILE *fptr;

    fptr = fopen("Lessons.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&lesson, sizeof(struct Lesson), 1, fptr)) {
        printf("Code = %d\nName = %s\nCredit = %d\nQuota = %d\n\n", lesson.code, lesson.name,
               lesson.credit, lesson.quota);
    }

    fclose(fptr);
}

void showLessonRegistered(struct StudentLessonRegistration studentReg, int id) {
    FILE *fptr;

    fptr = fopen("StudentLessonRegistration.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&studentReg, sizeof(struct StudentLessonRegistration), 1, fptr)) {
        if (studentReg.id == id) {
            printf("Student id: %d\nCode: %d\n\n", studentReg.id, studentReg.code);
        }
    }

    fclose(fptr);
}

//  Update Lesson
void editLesson(struct Lesson lesson, int id) {
    FILE *fpt;
    FILE *fpo;
    int code, ch;

    printf("Enter Code to update:");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 0) {
        printf("Code %d is not Available in the Lessons", code);
    } else {
        fpo = fopen("Lessons.txt", "r");
        fpt = fopen("LessonTemps.txt", "w");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpo)) {
            if (lesson.code != code)
                fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
            else {
                if (lesson.teacher_id == id) {
                    printf("\n\t1. Update Code: << %d >> of Lesson", lesson.code);
                    printf("\n\t2. Update Name: << %s >> of Lesson", lesson.name);
                    printf("\n\t3. Update Credit: << %d >> of Lesson", lesson.credit);
                    printf("\n\t3. Update Quota: << %d >> of Quota", lesson.quota);
                    printf("\nEnter your choice:");
                    scanf("%d", &ch);

                    switch (ch) {
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
                    printf("Lesson Updated");
                } else {
                    printf("You don't have permission ;) ");
                    fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
                }

            }
        }
        fclose(fpo);
        fclose(fpt);

        fpo = fopen("Lessons.txt", "w");
        fpt = fopen("LessonTemps.txt", "r");
        while (fread(&lesson, sizeof(struct Lesson), 1, fpt)) {
            fwrite(&lesson, sizeof(struct Lesson), 1, fpo);
        }
        fclose(fpo);
        fclose(fpt);

    }
}

//  Delete Lesson //
void deleteLesson(struct Lesson lesson) {
    FILE *fpo;
    FILE *fpt;
    int code, s;

    printf("Enter the Code you want to Delete :");
    scanf("%d", &code);

    if (availableCode(lesson, code) == 0) {
        printf("Code %d is not Available in the Lessons\n", code);
    } else {
        fpo = fopen("Lessons.txt", "r");
        fpt = fopen("LessonTemps.txt", "w");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpo)) {
            if (lesson.code != code)
                fwrite(&lesson, sizeof(struct Lesson), 1, fpt);
        }
        fclose(fpo);
        fclose(fpt);

        fpo = fopen("Lessons.txt", "w");
        fpt = fopen("LessonTemps.txt", "r");

        while (fread(&lesson, sizeof(struct Lesson), 1, fpt)) {
            fwrite(&lesson, sizeof(struct Lesson), 1, fpo);
        }

        printf("\nLesson deleted!\n");
        fclose(fpo);
        fclose(fpt);
    }

}

//  Count Teacher row for auto increment  //
int countTeacher(struct Teacher teacher) {
    int linesCount = 1;
    FILE *fptr;

    fptr = fopen("Users/Teachers.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&teacher, sizeof(struct Teacher), 1, fptr)) {
        linesCount++;
    }
    fclose(fptr);

    return linesCount;
}

// Count Student row for auto increment //
int countStudent(struct Student student) {
    int linesCount = 1;
    FILE *fptr;

    fptr = fopen("Users/Students.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&student, sizeof(struct Student), 1, fptr)) {
        linesCount++;
    }
    fclose(fptr);

    return linesCount;
}

//  Check Lesson Code   //
int availableCode(struct Lesson lesson, int code) {
    FILE *fp;

    fp = fopen("Lessons.txt", "r");

    while (!feof(fp)) {
        fread(&lesson, sizeof(struct Lesson), 1, fp);

        if (code == lesson.code) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

//  Check Teacher Nickname  //
int availableTeacher(struct Teacher teacher, char nickname[]) {
    FILE *fp;

    fp = fopen("Users/Teachers.txt", "r");

    while (!feof(fp)) {
        fread(&teacher, sizeof(struct Teacher), 1, fp);

        if (strcmp(nickname, teacher.nickname) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

//  Check Student Nickname  //
int availableStudent(struct Student student, char nickname[]) {
    FILE *fp;

    fp = fopen("Users/Students.txt", "r");

    while (!feof(fp)) {

        fread(&student, sizeof(struct Student), 1, fp);

        if (strcmp(nickname, student.nickname) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    return 0;
}

//  Find teacher id with nickname   //
int findTeachId(struct Teacher teacher, char nickname[]) {
    FILE *fp;

    fp = fopen("Users/Teachers.txt", "r");

    while (!feof(fp)) {
        fread(&teacher, sizeof(struct Teacher), 1, fp);

        if (strcmp(nickname, teacher.nickname) == 0) {
            fclose(fp);
            return teacher.id;
        }
    }
    fclose(fp);

    return 0;
}

//  Find student id with nickname   //
int findStudentId(struct Student student, char nickname[]) {
    FILE *fp;

    fp = fopen("Users/Students.txt", "r");

    while (!feof(fp)) {
        fread(&student, sizeof(struct Student), 1, fp);

        if (strcmp(nickname, student.nickname) == 0) {
            fclose(fp);
            return student.id;
        }
    }
    fclose(fp);

    return 0;
}

int checkLessonReg(struct StudentLessonRegistration studentReg, int id, int Lessoncode) {
    FILE *fp;

    fp = fopen("StudentLessonRegistration.txt", "r");

    while (!feof(fp)) {
        fread(&studentReg, sizeof(struct StudentLessonRegistration), 1, fp);

        if (studentReg.id == id) {

            if (studentReg.code == Lessoncode) {
                fclose(fp);
                return 1;
            }

        }
    }
    fclose(fp);

    return 0;
}

int checkQuota(struct Lesson lesson, struct StudentLessonRegistration studentReg, int lessonCode) {
    int count = 0;
    FILE *fptr, *fpo;

    fptr = fopen("StudentLessonRegistration.txt", "r");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&studentReg, sizeof(struct StudentLessonRegistration), 1, fptr)) {

        if (studentReg.code == lessonCode) {
            count++;
        }
    }
    fclose(fptr);

    fpo = fopen("Lessons.txt", "r");

    if (fpo == NULL) {
        printf("Error!");
        exit(1);
    }

    while (fread(&lesson, sizeof(struct Lesson), 1, fpo)) {

        if (lesson.code == lessonCode) {
            if (lesson.quota == count) {
                fclose(fpo);
                return 1;
            }
        }

    }
    fclose(fpo);

    return 0;
}