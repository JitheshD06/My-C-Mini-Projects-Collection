#include <stdio.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
int fgets_solution(char *string);

typedef struct {
    char username[30];
    int acc_no; 
    float balance;
} Account;

int main() {
    int choice;
    while (1) {
        printf("\n***BANKING MANAGEMENT***\n");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                printf("Closing bank\n");
                return 0;
            default:
                printf("Invalid input, please try again.\n");
                break;
        }
    }
} 

void create_account() {
    Account acc;
    FILE *file = fopen("account.dat", "ab+");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }
    printf("Enter Your Name: ");
    fgets(acc.username, sizeof(acc.username), stdin);
    fgets_solution(acc.username);
    printf("Enter Your Account Number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;
    
    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

void deposit_money() {
    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_read;
    printf("Enter Your Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter The Amount You Want To Deposit: ");
    scanf("%f", &money);

    int found = 0;
    while (fread(&acc_read, sizeof(acc_read), 1, file)) {
        if (acc_read.acc_no == acc_no) {
            acc_read.balance += money;
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            found = 1;
            printf("Successfully Deposited %.2f. New Balance: %.2f\n", money, acc_read.balance);
            break;
        }
    }

    fclose(file);
    if (!found) {
        printf("Account Not Found!\n");
    }
}

void withdraw_money() {
    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    int acc_no;
    float money;
    Account acc_read;
    printf("Enter Your Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter The Amount You Want To Withdraw: ");
    scanf("%f", &money);

    int found = 0;
    while (fread(&acc_read, sizeof(acc_read), 1, file)) {
        if (acc_read.acc_no == acc_no) {
            if (acc_read.balance >= money) {
                acc_read.balance -= money;
                fseek(file, -sizeof(acc_read), SEEK_CUR);
                fwrite(&acc_read, sizeof(acc_read), 1, file);
                found = 1;
                printf("Successfully Withdrawn %.2f. New Balance: %.2f\n", money, acc_read.balance);
                break;
            } else {
                printf("Insufficient balance to withdraw %.2f!\n", money);
                found = 1;
                break;
            }
        }
    }

    fclose(file);
    if (!found) {
        printf("Account Not Found!\n");
    }
}

void check_balance() {
    FILE *file = fopen("account.dat", "rb");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("Enter Your Account Number: ");
    scanf("%d", &acc_no);

    int found = 0;
    while (fread(&acc_read, sizeof(acc_read), 1, file)) {
        if (acc_read.acc_no == acc_no) {
            printf("Your Account Balance is %.2f\n", acc_read.balance);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (!found) {
        printf("Account Not Found!\n");
    }
}

int fgets_solution(char *string) {
    int index = strcspn(string, "\n");
    if (index < strlen(string)) {
        string[index] = '\0';
    }
    return 0;
}
