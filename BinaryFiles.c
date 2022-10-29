#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *studentFile, *copyFile;

struct Record{
    char studentId[3], studentName[30], emailId[30], courseId[9], grade[3];
};

// create file function
void create(){

    // open file
    studentFile = fopen("students.bin", "wb");

    // random student info
    char randomStudents[5][5][30] = {
        {"12", "Ashley", "ashley@tru.ca", "COMP3321", "A+"},
        {"34", "Tyler", "tyler@tru.ca", "ENGL2314", "F-"},
        {"45", "Maddy", "maddy@tru.ca", "CMNS1291", "B+"},
        {"56", "Jaymie", "jaymie@tru.ca", "COMP4342", "A-"},
        {"77", "Graham", "graham@tru.ca", "MATH5231", "C+"}
    };

    // create records and add in file
    for(int n = 0; n < 5; n++) {
        struct Record student;
        strcpy(student.studentId, randomStudents[n][0]);
        strcpy(student.studentName, randomStudents[n][1]);
        strcpy(student.emailId, randomStudents[n][2]);
        strcpy(student.courseId, randomStudents[n][3]);
        strcpy(student.grade, randomStudents[n][4]);
        fwrite(&student, sizeof(struct Record), 1, studentFile);
    }

    printf("\nBinary file has been created.\n");

    // close file
    fclose(studentFile);

}

// display file contents function
void display(){
    // define struct
    struct Record student;

    // open file
    studentFile = fopen("students.bin","rb");

    // check if file exists
    if (studentFile == NULL){
        printf("Error opening file!");
        exit(1);
    }

    // display all records in the file
    printf("\nDisplaying Records...\n\n");
    while(fread(&student, sizeof(struct Record), 1, studentFile)){
        printf("StudentID: %s\tName: %s\t EmailID: %s\tCourseID: %s\tGrade: %s\n", student.studentId, student.studentName, student.emailId, student.courseId, student.grade);
    };

    // close file
    fclose(studentFile);

}

// display the contents of a specific record
void seek(){
    // initial variables
    char id[3];
    int exists = 0;

    // define struct
    struct Record student;

    // open file
    studentFile = fopen("students.bin", "rb");

    // check if file exists
    if (studentFile == NULL){
        printf("Error opening file!");
        exit(1);
    }

    // get prompt from user
    printf("\nPlease enter the id of the student: ");
    scanf("%s", id);

    // reads through file records and finds matching one
    while(fread(&student, sizeof(struct Record), 1, studentFile)){
        if(strcmp(student.studentId, id) == 0) {
            exists = 1;
            printf("\nStudentID: %s\tName: %s\t EmailID: %s\tCourseID: %s\tGrade: %s\n", student.studentId, student.studentName, student.emailId, student.courseId, student.grade);
        }
    };

    // tells user if there is no matching record
    if (exists == 0){
        printf("\nNo student exists.\n");
    }

    // close file
    fclose(studentFile);

}

// update a specific record
void update(){
    // initial variables
    char id[2], updateVal[30];
    int updateFieldNum;

    // define struct
    struct Record student;

    // open original file
    studentFile = fopen("students.bin","rb+");

    // check if original file exists
    if (studentFile == NULL){
        printf("Error opening file!");
        exit(1);
    }

    // open temp copy file
    copyFile = fopen("copy.bin", "wb+");

    // prompt user for id they want to update
    printf("\nPlease enter the id of the student: ");
    scanf("%s", id);

    // read through the records
    while(fread(&student, sizeof(struct Record), 1, studentFile)){

        // copy all records that aren't being updated to the copy file,
        if(strcmp(student.studentId, id) != 0) {
            fwrite(&student, sizeof(struct Record), 1, copyFile);

        // else update the record and then copy it to the file
        } else {
            // print matching id information
            printf("\nStudentID: %s\tName: %s\t EmailID: %s\tCourseID: %s\tGrade: %s\n", student.studentId, student.studentName, student.emailId, student.courseId, student.grade);

            // prompt user for which field to update
            printf("\n\tFields:\n");
            printf("\t1. StudentID\n\t2. Name\n\t3. EmailID\n\t4. CourseID\n\t5. Grade\n\n");
            printf("\nWhich field # would you like to update?: ");
            scanf("%d", &updateFieldNum);

            // prompt user for what they want to update the val to
            printf("\nWhat would you like to update it to?: ");
            scanf("%s", updateVal);

            // update the proper field with new info 
            //(I know a switch statement makes the most sense here, but it causes errors with the struct declarations. I spent hours trying to fix with no luck)
            if (updateFieldNum == 1){
                struct Record studentIdUpdate;
                strcpy(studentIdUpdate.studentId, updateVal);
                strcpy(studentIdUpdate.studentName, student.studentName);
                strcpy(studentIdUpdate.emailId, student.emailId);
                strcpy(studentIdUpdate.courseId, student.courseId);
                strcpy(studentIdUpdate.grade, student.grade);
                fwrite(&studentIdUpdate, sizeof(struct Record), 1, copyFile);
                printf("\nStudent ID updated.\n");
            } else if(updateFieldNum == 2) {
                // update student name
                struct Record studentNameUpdate;
                strcpy(studentNameUpdate.studentId, student.studentId);
                strcpy(studentNameUpdate.studentName, updateVal);
                strcpy(studentNameUpdate.emailId, student.emailId);
                strcpy(studentNameUpdate.courseId, student.courseId);
                strcpy(studentNameUpdate.grade, student.grade);
                fwrite(&studentNameUpdate, sizeof(struct Record), 1, copyFile);
                printf("\nStudent name updated.\n");
            } else if (updateFieldNum == 3){
                // update student email Id
                struct Record studentEmailUpdate;
                strcpy(studentEmailUpdate.studentId, student.studentId);
                strcpy(studentEmailUpdate.studentName, student.studentName);
                strcpy(studentEmailUpdate.emailId, updateVal);
                strcpy(studentEmailUpdate.courseId, student.courseId);
                strcpy(studentEmailUpdate.grade, student.grade);
                fwrite(&studentEmailUpdate, sizeof(struct Record), 1, copyFile);
                printf("\nStudent email ID updated.\n");
            } else if (updateFieldNum == 4){
                // update student course id
                struct Record studentCourseUpdate;
                strcpy(studentCourseUpdate.studentId, student.studentId);
                strcpy(studentCourseUpdate.studentName, student.studentName);
                strcpy(studentCourseUpdate.emailId, student.emailId);
                strcpy(studentCourseUpdate.courseId, updateVal);
                strcpy(studentCourseUpdate.grade, student.grade);
                fwrite(&studentCourseUpdate, sizeof(struct Record), 1, copyFile);
                printf("\nStudent course ID updated.\n");
            } else if (updateFieldNum == 5) {
                // update student grade
                struct Record studentGradeUpdate;
                strcpy(studentGradeUpdate.studentId, student.studentId);
                strcpy(studentGradeUpdate.studentName, student.studentName);
                strcpy(studentGradeUpdate.emailId, student.emailId);
                strcpy(studentGradeUpdate.courseId, student.courseId);
                strcpy(studentGradeUpdate.grade, updateVal);
                fwrite(&studentGradeUpdate, sizeof(struct Record), 1, copyFile);
                printf("\nStudent ID updated.\n");
            } else {
                printf("Invalid input. Please enter a number between 1 and 5.\n");
            }

        }

    }

    // close files
    fclose(studentFile);
    fclose(copyFile);

    // replace original with updated copy
    remove("students.bin");
    rename("copy.bin", "students.bin");

}

// delete a specific record
void delete(){
    // initial variables
    char id[30];
    int updateFieldNum, exists = 0;

    // define struct
    struct Record student;

    // open original file
    studentFile = fopen("students.bin","rb+");

    // check if original file exists
    if (studentFile == NULL){
        printf("Error opening file!");
        exit(1);
    }

    // open temp copy file
    copyFile = fopen("copy.bin", "wb+");

    // prompt user for id they want to update
    printf("\nPlease enter the id or name of the student: ");
    scanf("%s", id);

    // copy all the records except the deleted one
    while(fread(&student, sizeof(struct Record), 1, studentFile)){
        if(strcmp(student.studentId, id) != 0 && strcmp(student.studentName, id) != 0){
            fwrite(&student, sizeof(struct Record), 1, copyFile);
        } else {
            printf("\nStudent #%s has been deleted.\n", student.studentId);
            exists = 1;
        }
    }

    // let user know if the student ID doesnt exist
    if (exists == 0)
        printf("\nNo student exists with that ID or name.\n");

    // close files
    fclose(studentFile);
    fclose(copyFile);

    // replace original with updated copy
    remove("students.bin");
    rename("copy.bin", "students.bin");

}

// main
int main(void) {
    // initial variables
    int choice, exit=0;

    // main menu
    while (exit == 0){
        // print menu to screen
        printf("\n**********************************************\n");
        printf("\n    M A I N  M E N U\n");
        printf("1. Create the Binary File\n2. Display the contents of the file\n3. Seek a specific record\n4. Update the contents of a record\n5. Delete a record\n6. Exit\n");

        // get user prompt
        printf("\nPlease enter your choice .... ");
        scanf("%d", &choice);
        printf("\n**********************************************\n");

        // perform the function the user chose
        switch(choice) {
            case 1:
                // create file
                create();
                break;

            case 2:
                // display file contents
                display();
                break;

            case 3:
                // look for specific record
                seek();
                break;

            case 4:
                // update specific record
                update();
                break;

            case 5:
                // delete specific record
                delete();
                break;

            case 6:
                // exit program
                exit = 1;
                printf("\nExiting Program... GoodBye!\n");
                printf("\n**********************************************\n");
                break;

            default:
                printf("\nInvalid input. Please enter a number between 1 and 6.\n");

        }

    }

    return 0;
}
