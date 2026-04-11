#include <stdio.h>
#include <string.h>

typedef struct {
    int creditScore;
    float income;
    float businessTurnover;
} Customer;

typedef struct {
    char cardName[50];
    char cardType[20];
    float minIncome;
    float minTurnover;
} Card;

void displayBenefits(char cardType[], Customer c) {
    printf("\nBenefits Included:\n");

    if (strcmp(cardType, "Normal") == 0) {
        printf("- Cashback on daily spending\n");
        printf("- Fuel surcharge waiver\n");
    }

    if (strcmp(cardType, "Middle") == 0) {
        printf("- Online shopping discounts\n");
        printf("- Dining offers\n");
        if (c.creditScore >= 700)
            printf("- Low interest EMI options\n");
    }

    if (strcmp(cardType, "Premium") == 0) {
        printf("- Airport lounge access\n");
        printf("- Free luxury dining\n");
        printf("- Exclusive online shopping offers\n");
        printf("- Priority loan processing\n");
        printf("- Personal banking assistance\n");

        if (c.creditScore >= 750 && c.income >= 80000)
            printf("- Complimentary hotel upgrades\n");
    }

    if (strcmp(cardType, "HNI") == 0) {
        printf("- Unlimited airport lounge access\n");
        printf("- Private personal banker\n");
        printf("- Exclusive luxury dining & shopping\n");
        printf("- Preferential loan & wealth management\n");
        printf("- Invite-only elite financial services\n");

        if (c.creditScore >= 800 && c.businessTurnover >= 2000000) {
            printf("- Private jet privileges\n");
            printf("- VIP concert & global event access\n");
            printf("- Premium art gallery & auction access\n");
        }
    }
}

int main() {
    Customer user;
    Card cards[4] = {
        {"Normal Saver Card", "Normal", 15000, 0},
        {"Lifestyle Plus Card", "Middle", 30000, 0},
        {"Elite Premium Card", "Premium", 70000, 0},
        {"HNI Black Card", "HNI", 120000, 1000000}
    };

    printf("Enter Credit Score: ");
    scanf("%d", &user.creditScore);

    printf("Enter Monthly Income: ");
    scanf("%f", &user.income);

    printf("Enter Annual Business Turnover (0 if none): ");
    scanf("%f", &user.businessTurnover);

    int selected = -1;

    for (int i = 3; i >= 0; i--) {
        if (user.income >= cards[i].minIncome &&
            user.businessTurnover >= cards[i].minTurnover &&
            user.creditScore >= 650) {
            selected = i;
            break;
        }
    }

    if (selected != -1) {
        printf("\nRecommended Credit Card:\n");
        printf("Card Name: %s\n", cards[selected].cardName);
        printf("Card Category: %s\n", cards[selected].cardType);
        displayBenefits(cards[selected].cardType, user);
    } else {
        printf("\nNo suitable card found for your profile.\n");
    }

    return 0;
}
