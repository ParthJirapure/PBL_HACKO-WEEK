#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 300

// -------------------- GLOBAL ANALYTICS --------------------
int totalQueries = 0;
int successfulQueries = 0;
int fallbackQueries = 0;

int feesCount = 0;
int examCount = 0;
int admissionCount = 0;
int hostelCount = 0;
int placementCount = 0;

// -------------------- CONTEXT --------------------
char lastIntent[50] = "";
char lastYear[30] = "";
char lastSem[30] = "";
char lastCourse[30] = "";

// -------------------- FUNCTION DECLARATIONS --------------------
void toLowerCase(char str[]);
void trimNewline(char str[]);
int containsWord(const char str[], const char word[]);
void extractEntities(char input[], char year[], char sem[], char course[]);
void detectIntent(char input[], char intent[]);
void answerQuery(char input[]);
void printAnalytics();
void showMenu();
void handoverSupport();
void simulateChannels();

// -------------------- MAIN --------------------
int main() {
    int choice;
    char input[MAX];

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("\n=== Student Query Chatbot ===\n");
                printf("Type your question (type 'exit' to stop)\n\n");

                while (1) {
                    printf("You: ");
                    fgets(input, sizeof(input), stdin);
                    trimNewline(input);

                    if (strcmp(input, "exit") == 0 || strcmp(input, "EXIT") == 0)
                        break;

                    answerQuery(input);
                    printf("\n");
                }
                break;

            case 2:
                simulateChannels();
                break;

            case 3:
                printAnalytics();
                break;

            case 4:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

// -------------------- MENU --------------------
void showMenu() {
    printf("\n=========================================\n");
    printf("     STUDENT QUERY CHATBOT SYSTEM\n");
    printf("=========================================\n");
    printf("1. Start Chatbot\n");
    printf("2. Multichannel Deployment Mockup\n");
    printf("3. View Analytics\n");
    printf("4. Exit\n");
    printf("=========================================\n");
}

// -------------------- LOWERCASE --------------------
void toLowerCase(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// -------------------- REMOVE NEWLINE --------------------
void trimNewline(char str[]) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// -------------------- WORD CHECK --------------------
int containsWord(const char str[], const char word[]) {
    return strstr(str, word) != NULL;
}

// -------------------- ENTITY EXTRACTION --------------------
void extractEntities(char input[], char year[], char sem[], char course[]) {
    strcpy(year, "");
    strcpy(sem, "");
    strcpy(course, "");

    // Year extraction
    if (containsWord(input, "first year") || containsWord(input, "1st year"))
        strcpy(year, "First Year");
    else if (containsWord(input, "second year") || containsWord(input, "2nd year"))
        strcpy(year, "Second Year");
    else if (containsWord(input, "third year") || containsWord(input, "3rd year"))
        strcpy(year, "Third Year");
    else if (containsWord(input, "final year") || containsWord(input, "fourth year") || containsWord(input, "4th year"))
        strcpy(year, "Final Year");

    // Semester extraction
    if (containsWord(input, "sem 1") || containsWord(input, "semester 1"))
        strcpy(sem, "SEM 1");
    else if (containsWord(input, "sem 2") || containsWord(input, "semester 2"))
        strcpy(sem, "SEM 2");
    else if (containsWord(input, "sem 3") || containsWord(input, "semester 3"))
        strcpy(sem, "SEM 3");
    else if (containsWord(input, "sem 4") || containsWord(input, "semester 4"))
        strcpy(sem, "SEM 4");
    else if (containsWord(input, "sem 5") || containsWord(input, "semester 5"))
        strcpy(sem, "SEM 5");
    else if (containsWord(input, "sem 6") || containsWord(input, "semester 6"))
        strcpy(sem, "SEM 6");
    else if (containsWord(input, "sem 7") || containsWord(input, "semester 7"))
        strcpy(sem, "SEM 7");
    else if (containsWord(input, "sem 8") || containsWord(input, "semester 8"))
        strcpy(sem, "SEM 8");

    // Course extraction
    if (containsWord(input, "cs") || containsWord(input, "computer science") || containsWord(input, "cse"))
        strcpy(course, "Computer Science");
    else if (containsWord(input, "it"))
        strcpy(course, "Information Technology");
    else if (containsWord(input, "mechanical"))
        strcpy(course, "Mechanical");
    else if (containsWord(input, "civil"))
        strcpy(course, "Civil");
    else if (containsWord(input, "electrical"))
        strcpy(course, "Electrical");
    else if (containsWord(input, "electronics"))
        strcpy(course, "Electronics");
}

// -------------------- INTENT DETECTION --------------------
void detectIntent(char input[], char intent[]) {
    strcpy(intent, "unknown");

    if (containsWord(input, "fee") || containsWord(input, "fees"))
        strcpy(intent, "fees");
    else if (containsWord(input, "exam") || containsWord(input, "date") || containsWord(input, "timetable"))
        strcpy(intent, "exam");
    else if (containsWord(input, "admission") || containsWord(input, "apply") || containsWord(input, "eligibility"))
        strcpy(intent, "admission");
    else if (containsWord(input, "hostel") || containsWord(input, "room"))
        strcpy(intent, "hostel");
    else if (containsWord(input, "placement") || containsWord(input, "company") || containsWord(input, "job"))
        strcpy(intent, "placement");
    else if (containsWord(input, "hello") || containsWord(input, "hi") || containsWord(input, "hey"))
        strcpy(intent, "greeting");
}

// -------------------- HANDOVER --------------------
void handoverSupport() {
    printf("Bot: I could not fully understand your query.\n");
    printf("Bot: Please contact student helpdesk at: support@college.edu\n");
    printf("Bot: Or visit the admin office / inquiry desk.\n");
}

// -------------------- ANSWER ENGINE --------------------
void answerQuery(char input[]) {
    char temp[MAX];
    char intent[50];
    char year[30], sem[30], course[30];

    strcpy(temp, input);
    toLowerCase(temp);

    totalQueries++;

    detectIntent(temp, intent);
    extractEntities(temp, year, sem, course);

    // ---------------- CONTEXT HANDLING ----------------
    // If user gives follow-up like "For third year?"
    if (strlen(intent) == 0 || strcmp(intent, "unknown") == 0) {
        if (strlen(lastIntent) > 0) {
            strcpy(intent, lastIntent);
        }
    }

    if (strlen(year) == 0 && strlen(lastYear) > 0)
        strcpy(year, lastYear);

    if (strlen(sem) == 0 && strlen(lastSem) > 0)
        strcpy(sem, lastSem);

    if (strlen(course) == 0 && strlen(lastCourse) > 0)
        strcpy(course, lastCourse);

    // Save latest context if newly found
    if (strcmp(intent, "unknown") != 0)
        strcpy(lastIntent, intent);

    if (strlen(year) > 0)
        strcpy(lastYear, year);

    if (strlen(sem) > 0)
        strcpy(lastSem, sem);

    if (strlen(course) > 0)
        strcpy(lastCourse, course);

    // ---------------- RESPONSES ----------------
    if (strcmp(intent, "greeting") == 0) {
        printf("Bot: Hello! I can help you with fees, exams, admissions, hostel, and placements.");
        successfulQueries++;
    }

    else if (strcmp(intent, "fees") == 0) {
        printf("Bot: Fee details:\n");
        if (strlen(year) > 0)
            printf("Bot: %s tuition fee is approximately Rs. 85,000 per year.\n", year);
        else
            printf("Bot: Tuition fee is approximately Rs. 85,000 per year.\n");
        printf("Bot: You can pay fees online through the college portal.");
        successfulQueries++;
        feesCount++;
    }

    else if (strcmp(intent, "exam") == 0) {
        printf("Bot: Exam information:\n");
        if (strlen(sem) > 0 && strlen(course) > 0)
            printf("Bot: %s %s exams are expected from 15 May 2026.\n", sem, course);
        else if (strlen(sem) > 0)
            printf("Bot: %s exams are expected from 15 May 2026.\n", sem);
        else if (strlen(year) > 0)
            printf("Bot: %s exam timetable will be released soon.\n", year);
        else
            printf("Bot: The exam timetable will be announced on the college notice board and portal.\n");

        successfulQueries++;
        examCount++;
    }

    else if (strcmp(intent, "admission") == 0) {
        printf("Bot: Admission details:\n");
        printf("Bot: Admissions are open from 1 June 2026.\n");
        printf("Bot: Required documents include mark sheets, ID proof, and passport size photos.\n");
        printf("Bot: Apply through the official college admission portal.");
        successfulQueries++;
        admissionCount++;
    }

    else if (strcmp(intent, "hostel") == 0) {
        printf("Bot: Hostel details:\n");
        printf("Bot: Hostel facility is available for boys and girls.\n");
        printf("Bot: Approximate hostel fee is Rs. 45,000 per year including mess.\n");
        printf("Bot: Contact the hostel office for room allotment.");
        successfulQueries++;
        hostelCount++;
    }

    else if (strcmp(intent, "placement") == 0) {
        printf("Bot: Placement details:\n");
        printf("Bot: Top recruiters include TCS, Infosys, Wipro, and Capgemini.\n");
        printf("Bot: Students become eligible for placements from 6th semester onwards.\n");
        printf("Bot: Placement training sessions are conducted regularly.");
        successfulQueries++;
        placementCount++;
    }

    else {
        fallbackQueries++;
        handoverSupport();
    }
}

// -------------------- ANALYTICS --------------------
void printAnalytics() {
    printf("\n========== CHATBOT ANALYTICS ==========\n");
    printf("Total Queries           : %d\n", totalQueries);
    printf("Successful Queries      : %d\n", successfulQueries);
    printf("Fallback Queries        : %d\n", fallbackQueries);
    printf("---------------------------------------\n");
    printf("Fees Queries            : %d\n", feesCount);
    printf("Exam Queries            : %d\n", examCount);
    printf("Admission Queries       : %d\n", admissionCount);
    printf("Hostel Queries          : %d\n", hostelCount);
    printf("Placement Queries       : %d\n", placementCount);
    printf("=======================================\n");
}

// -------------------- MULTICHANNEL MOCKUP --------------------
void simulateChannels() {
    printf("\n========== MULTICHANNEL DEPLOYMENT MOCKUP ==========\n");
    printf("1. Web Portal   : Chatbot embedded on college website\n");
    printf("2. Mobile App   : Chat support available inside student app\n");
    printf("3. WhatsApp Bot : Students can ask quick queries via WhatsApp\n");
    printf("4. CLI Version  : Console-based chatbot for project demo\n");
    printf("===================================================\n");
}
