#include <stdio.h>

struct student
{
    int roll;
    char name[30];
    float mark;
};

void add()
{
    struct student s;
    FILE *fp;

    fp = fopen("student.dat", "ab");

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %29[^\n]", s.name);

    printf("Enter Mark: ");
    scanf("%f", &s.mark);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully\n");
}

void display()
{
    struct student s;
    FILE *fp;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\nRoll Number: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMark: %.2f\n", s.mark);
    }

    fclose(fp);
}

void search()
{
    struct student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            printf("\nName: %s", s.name);
            printf("\nMark: %.2f\n", s.mark);
            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Student not found\n");

    fclose(fp);
}

void update()
{
    struct student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            printf("Enter New Name: ");
            scanf(" %29[^\n]", s.name);

            printf("Enter New Mark: ");
            scanf("%f", &s.mark);

            found = 1;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if(found == 1)
        printf("Record updated successfully\n");
    else
        printf("Student not found\n");
}

void delete()
{
    struct student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if(found == 1)
        printf("Record deleted successfully\n");
    else
        printf("Student not found\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            add();
            break;

            case 2:
            display();
            break;

            case 3:
            search();
            break;

            case 4:
            update();
            break;

            case 5:
            delete();
            break;

            case 6:
            printf("Thank you");
            break;

            default:
            printf("Invalid choice");
        }

    } while(choice != 6);

    return 0;
}