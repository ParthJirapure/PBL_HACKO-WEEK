#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

int totalQueries = 0;
int successfulQueries = 0;
int fallbackQueries = 0;

int feesCount = 0, examCount = 0, admissionCount = 0, hostelCount = 0, placementCount = 0;

char lastTopic[50] = "";
char lastYear[50] = "";
char lastCourse[50] = "";
int lastSem = -1;
int fallbackCount = 0;

void toLowerCase(char *str)
{
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

int extractSemester(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        if(str[i] == 's' && str[i+1] == 'e' && str[i+2] == 'm')
        {
            int j = i + 3;
            while(str[j] == ' ') j++;
            if(isdigit(str[j]))
                return str[j] - '0';
        }
    }
    return -1;
}

void extractCourse(char *str, char course[])
{
    char *courses[] = {"cs", "ai", "it", "ece", "me", "ce"};
    int n = 6;

    for(int i = 0; i < n; i++)
    {
        if(strstr(str, courses[i]))
        {
            strcpy(course, courses[i]);
            return;
        }
    }
    strcpy(course, "");
}

void extractDateKeyword(char *str, char dateWord[])
{
    char *dates[] = {"today","tomorrow","monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
    int n = 9;

    for(int i = 0; i < n; i++)
    {
        if(strstr(str, dates[i]))
        {
            strcpy(dateWord, dates[i]);
            return;
        }
    }
    strcpy(dateWord, "scheduled date");
}

void extractYear(char *str, char year[])
{
    if(strstr(str, "first")) strcpy(year, "1st year");
    else if(strstr(str, "second")) strcpy(year, "2nd year");
    else if(strstr(str, "third")) strcpy(year, "3rd year");
    else if(strstr(str, "fourth")) strcpy(year, "4th year");
    else strcpy(year, "");
}

int detectIntent(char *str)
{
    if(strstr(str, "fees") || strstr(str, "fee")) return 1;
    if(strstr(str, "admission")) return 2;
    if(strstr(str, "exam")) return 3;
    if(strstr(str, "hostel")) return 4;
    if(strstr(str, "placement")) return 5;
    return 0;
}

void updateAnalytics(int intent, int success)
{
    totalQueries++;

    if(success)
        successfulQueries++;
    else
        fallbackQueries++;

    switch(intent)
    {
        case 1: feesCount++; break;
        case 2: admissionCount++; break;
        case 3: examCount++; break;
        case 4: hostelCount++; break;
        case 5: placementCount++; break;
    }
}

void showAnalytics()
{
    printf("\n========== CHATBOT ANALYTICS ==========\n");
    printf("Total Queries Handled      : %d\n", totalQueries);
    printf("Successful Responses       : %d\n", successfulQueries);
    printf("Fallback / Unclear Queries : %d\n", fallbackQueries);

    printf("\nIntent Breakdown:\n");
    printf("Fees       : %d\n", feesCount);
    printf("Admissions : %d\n", admissionCount);
    printf("Exams      : %d\n", examCount);
    printf("Hostel     : %d\n", hostelCount);
    printf("Placement  : %d\n", placementCount);

    int max = feesCount;
    char mostAsked[50] = "Fees";

    if(admissionCount > max) { max = admissionCount; strcpy(mostAsked, "Admissions"); }
    if(examCount > max) { max = examCount; strcpy(mostAsked, "Exams"); }
    if(hostelCount > max) { max = hostelCount; strcpy(mostAsked, "Hostel"); }
    if(placementCount > max) { max = placementCount; strcpy(mostAsked, "Placement"); }

    if(max > 0)
        printf("\nMost Asked Topic           : %s\n", mostAsked);
    else
        printf("\nMost Asked Topic           : No data yet\n");

    printf("=======================================\n");
}

void fallback()
{
    fallbackCount++;
    updateAnalytics(0, 0);

    if(fallbackCount == 1)
    {
        printf("I am not sure I understood that. Could you please clarify your question?\n");
        printf("You can ask about admissions, fees, exams, hostel or placements.\n");
    }
    else if(fallbackCount == 2)
    {
        printf("I am still unable to understand the query.\n");
        printf("Try asking something like: 'What are the fees?' or 'When is SEM 5 CS exam?'\n");
    }
    else
    {
        printf("I recommend contacting a human advisor for further assistance.\n");
        printf("Email: advisor@institute.edu\n");
        printf("Help Desk: www.institute.edu/helpdesk\n");
        fallbackCount = 0;
    }
}

void respond(char *processed)
{
    int sem = extractSemester(processed);
    char course[50], dateWord[50], year[50];
    int intent = detectIntent(processed);

    extractCourse(processed, course);
    extractDateKeyword(processed, dateWord);
    extractYear(processed, year);

    if(intent == 1) strcpy(lastTopic, "fees");
    else if(intent == 2) strcpy(lastTopic, "admission");
    else if(intent == 3) strcpy(lastTopic, "exam");
    else if(intent == 4) strcpy(lastTopic, "hostel");
    else if(intent == 5) strcpy(lastTopic, "placement");

    if(strlen(year) > 0) strcpy(lastYear, year);
    if(strlen(course) > 0) strcpy(lastCourse, course);
    if(sem != -1) lastSem = sem;

    if(intent == 1)
    {
        printf("The fee structure ranges from 80000 to 120000 per year depending on the course.\n");
        fallbackCount = 0;
        updateAnalytics(intent, 1);
        return;
    }

    if(intent == 2)
    {
        printf("Admissions open in June. Applications are available on the institute website.\n");
        fallbackCount = 0;
        updateAnalytics(intent, 1);
        return;
    }

    if(intent == 4)
    {
        printf("Hostel facilities are available for both boys and girls with separate accommodation.\n");
        fallbackCount = 0;
        updateAnalytics(intent, 1);
        return;
    }

    if(intent == 5)
    {
        printf("The placement cell works with companies like TCS, Infosys and Wipro.\n");
        fallbackCount = 0;
        updateAnalytics(intent, 1);
        return;
    }

    if(intent == 3 || strcmp(lastTopic, "exam") == 0)
    {
        if(sem != -1 && strlen(course) > 0)
        {
            printf("Exam schedule for SEM %d %s course is %s.\n", sem, course, dateWord);
        }
        else if(strlen(year) > 0)
        {
            printf("The exam schedule for %s students will be announced next month.\n", year);
        }
        else if(lastSem != -1 && strlen(lastCourse) > 0)
        {
            printf("Exam schedule for SEM %d %s course is %s.\n", lastSem, lastCourse, dateWord);
        }
        else if(strlen(lastYear) > 0)
        {
            printf("The exam schedule for %s students will be announced next month.\n", lastYear);
        }
        else
        {
            printf("Which semester, course or year students are you asking about?\n");
        }

        fallbackCount = 0;
        updateAnalytics(3, 1);
        return;
    }

    if(strlen(year) > 0 && strcmp(lastTopic, "exam") == 0)
    {
        printf("The exam schedule for %s students will be announced next month.\n", year);
        fallbackCount = 0;
        updateAnalytics(3, 1);
        return;
    }

    fallback();
}

void simulateChannel(char *channel)
{
    char input[MAX], processed[MAX];

    printf("\n===== %s Chat Interface =====\n", channel);
    printf("Type 'exit' to return to channel menu\n");
    printf("Type 'analytics' to view chatbot analytics\n\n");

    while(1)
    {
        printf("You: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        strcpy(processed, input);
        toLowerCase(processed);

        if(strcmp(processed, "exit") == 0)
            break;

        if(strcmp(processed, "analytics") == 0)
        {
            showAnalytics();
            continue;
        }

        respond(processed);
        printf("\n");
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n=====================================\n");
        printf("1. Web Chatbot\n");
        printf("2. Mobile App Chatbot\n");
        printf("3. WhatsApp Chatbot\n");
        printf("4. Show Analytics\n");
        printf("5. Exit\n");
        printf("Select channel: ");

        scanf("%d", &choice);
        getchar();

        if(choice == 1)
            simulateChannel("Web");
        else if(choice == 2)
            simulateChannel("Mobile App");
        else if(choice == 3)
            simulateChannel("WhatsApp");
        else if(choice == 4)
            showAnalytics();
        else if(choice == 5)
            break;
        else
            printf("Invalid option\n");
    }

    return 0;
}
