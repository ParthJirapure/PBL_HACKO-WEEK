#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_FAQS 10
#define MAX_LEN 200
#define MAX_TOKENS 50

struct FAQ {
    char question[MAX_LEN];
    char answer[MAX_LEN];
    char intent[30];
};

struct FAQ faqs[MAX_FAQS] = {
    {"college timings", "College timings are 9 AM to 4 PM.", "timings"},
    {"fees structure", "The annual fees is Rs. 80,000.", "fees"},
    {"exam schedule", "Exams start from March 10.", "exams"},
    {"hostel facilities", "Hostel is available for boys and girls.", "hostel"},
    {"scholarship details", "Merit scholarships are available.", "scholarship"},
    {"contact office", "Contact office at 9876543210.", "contact"}
};

char *stopwords[] = {
    "the","is","are","was","were","a","an","to","of","for","on",
    "in","at","what","when","how","tell","me","about"
};

int faqCount = 6;
int stopwordCount = 17;

void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void removePunctuation(char str[]) {
    int i, j = 0;
    char temp[MAX_LEN];
    for (i = 0; str[i]; i++) {
        if (isalnum(str[i]))
            temp[j++] = str[i];
        else
            temp[j++] = ' ';
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int isStopword(char *word) {
    for (int i = 0; i < stopwordCount; i++) {
        if (strcmp(word, stopwords[i]) == 0)
            return 1;
    }
    return 0;
}

/* ---------- SYNONYM CHECKERS ---------- */

int inList(char *token, char *list[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(token, list[i]) == 0)
            return 1;
    }
    return 0;
}

void normalizeToken(char *token) {
    char *feesWords[] = {"fee","fees","tuition","payment","pay"};
    char *examWords[] = {"exam","exams","test","tests","paper"};
    char *hostelWords[] = {"hostel","host","accommodation","room"};
    char *scholarWords[] = {"scholarship","scholar","grant","aid"};
    char *contactWords[] = {"contact","call","phone","number","reach"};

    if (inList(token, feesWords, 5)) {
        strcpy(token, "fees"); return;
    }
    if (inList(token, examWords, 5)) {
        strcpy(token, "exams"); return;
    }
    if (inList(token, hostelWords, 4)) {
        strcpy(token, "hostel"); return;
    }
    if (inList(token, scholarWords, 4)) {
        strcpy(token, "scholarship"); return;
    }
    if (inList(token, contactWords, 5)) {
        strcpy(token, "contact"); return;
    }

    int len = strlen(token);
    if (len < 2) return;

    for (int i = 0; i < faqCount; i++) {
        if (strncmp(faqs[i].intent, token, len) == 0) {
            strcpy(token, faqs[i].intent);
            return;
        }
    }
}

int tokenize(char str[], char tokens[][30]) {
    int count = 0;
    char *token = strtok(str, " ");

    while (token != NULL) {
        normalizeToken(token);
        if (!isStopword(token))
            strcpy(tokens[count++], token);
        token = strtok(NULL, " ");
    }
    return count;
}

void classifyIntent(char tokens[][30], int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        for (int j = 0; j < faqCount; j++) {
            if (strcmp(tokens[i], faqs[j].intent) == 0) {
                printf("Intent: %s\n", faqs[j].intent);
                return;
            }
        }
    }
    printf("Intent: General\n");
}

int findBestFAQ(char tokens[][30], int tokenCount) {
    int best = -1, maxScore = 0;

    for (int i = 0; i < faqCount; i++) {
        int score = 0;
        char temp[MAX_LEN];
        strcpy(temp, faqs[i].question);

        char *word = strtok(temp, " ");
        while (word) {
            for (int j = 0; j < tokenCount; j++) {
                if (strcmp(tokens[j], word) == 0)
                    score++;
            }
            word = strtok(NULL, " ");
        }

        if (score > maxScore) {
            maxScore = score;
            best = i;
        }
    }
    return best;
}

void chatbot() {
    char query[MAX_LEN];
    char tokens[MAX_TOKENS][30];

    printf("\nEnter your question: ");
    fgets(query, MAX_LEN, stdin);
    query[strcspn(query, "\n")] = '\0';

    toLowerCase(query);
    removePunctuation(query);

    int tokenCount = tokenize(query, tokens);

    classifyIntent(tokens, tokenCount);

    for (int i = 0; i < faqCount; i++) {
        for (int j = 0; j < tokenCount; j++) {
            if (strcmp(tokens[j], faqs[i].intent) == 0) {
                printf("Answer: %s\n", faqs[i].answer);
                return;
            }
        }
    }

    int idx = findBestFAQ(tokens, tokenCount);
    if (idx != -1)
        printf("Answer: %s\n", faqs[idx].answer);
    else
        printf("Sorry, I could not understand your query.\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Student FAQ Chatbot ---");
        printf("\n1. Ask a Question");
        printf("\n2. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) chatbot();
        else if (choice == 2) printf("Thank you for using the chatbot.\n");
        else printf("Invalid choice.\n");

    } while (choice != 2);

    return 0;
}
