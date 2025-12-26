//Banking System Capstone Project
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct newAccount{
    char name[100];
    long long int accNo;
    int PIN;
    float initialDeposit;
}Acc;

void newAccount(Acc **arr,int* ptr,int* capacity);
void login(Acc arr[],int lim);
void deposit(Acc arr[],int lim);
void withdraw(Acc arr[],int lim);
void balance(Acc arr[],int lim);
void transfer(Acc arr[],int lim);
void close(Acc arr[],int* lim);

int main(){
    int i=0;
    int capacity = 1000;
    Acc *cust = (Acc*)malloc(capacity*sizeof(Acc));
    if (cust==NULL){
        printf("Memory Allocation failed\n");
        return 1;
    }
    FILE *fptr=fopen("bankCustomers.dat","rb");
    if (fptr!=NULL){
        while (fread(&cust[i],sizeof(Acc),1,fptr)==1){
            i++;
        }
        fclose(fptr);
    }
    while (1>0){
        printf("******************************************************************************\n");
        printf("                               Banking System                                 \n");
        printf("******************************************************************************\n");
        printf("Operations\n");
        printf("Create New Account (Enter 1)\n");
        printf("Login(Authentication) (Enter 2)\n");
        printf("Deposit Money (Enter 3)\n");
        printf("Withdraw Money (Enter 4)\n");
        printf("Balance Inquiry (Enter 5)\n");
        printf("Transfer Money (Enter 6)\n");
        printf("Close Account (Enter 7)\n");
        int num;
        scanf("%d",&num);
        switch (num) {
            case 1:{
                newAccount(&cust,&i,&capacity);
                break;
            }
            case 2:
                login(cust,i);
                break;
            case 3:
                deposit(cust,i);
                break;
            case 4:
                withdraw(cust,i);
                break;
            case 5:
                balance(cust,i);
                break;
            case 6:
                transfer(cust,i);
                break;
            case 7:
                close(cust,&i);
                break;
            default :
                printf("Invalid Operation...\n");
                break;
        }
        printf("Do you want to perform more operations : (y/n)?");
        char ask;
        getchar();
        scanf("%c",&ask);
        if (ask=='n'){
            break;
        }
    }
    free(cust);
    return 0;
}

void newAccount(Acc **arr,int* ptr,int* capacity){
    if (*ptr>=*capacity){
        *capacity+=1000;

        Acc *temp = (Acc*)realloc(*arr, (*capacity)*sizeof(Acc));
        if (temp==NULL){
            printf("Memory Reallocation Failed\n");
            return;
        }
        *arr = temp;
    }
    printf("Enter your name : ");
    char nm[100];
    getchar();
    fgets(nm,100,stdin);
    strcpy((*arr)[*ptr].name,nm);
    printf("Your account No. is : ");
    time_t t= time(NULL);
    (*arr)[*ptr].accNo = t;
    printf("%lld\n",(*arr)[*ptr].accNo);
    printf("Set your PIN : ");
    scanf("%d",&(*arr)[*ptr].PIN);
    printf("Deposit some initial amount : ");
    scanf("%f",&(*arr)[*ptr].initialDeposit);
    FILE *fptr;
    fptr=fopen("bankCustomers.dat","ab");
    fwrite(&(*arr)[*ptr],sizeof(Acc),1,fptr);
    fclose(fptr);
    printf("Account Created Successfully\n");
    (*ptr)++;
    return;
}

void login(Acc arr[],int lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    for (int i=0;i<lim;i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
        }
    }
    if (count==1){
        printf("Login Successful...\n");
    }
    else{
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}

void deposit(Acc arr[],int lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    for (int i=0;i<lim;i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
            float depo;
            printf("Enter amount to deposit : ");
            scanf("%f",&depo);
            arr[i].initialDeposit+=depo;
            break;
        }
    }
    if (count==1){
        int var=0;
        FILE *fptr=fopen("bankCustomers.dat","wb");
        while(var<lim){
            fwrite(&arr[var],sizeof(Acc),1,fptr);
            var++;
        }
        fclose(fptr);
        printf("Deposit Successful and Balance Updated\n");
    }
    else{
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}

void withdraw(Acc arr[],int lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    for (int i=0;i<lim;i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
            float wdw;
            printf("Enter amount to withdraw : ");
            scanf("%f",&wdw);
            if (arr[i].initialDeposit>=wdw){
                arr[i].initialDeposit-=wdw;
            }
            else{
                printf("Insufficient Balance\n");
                return;
            }
            break;
        }
    }
    int var=0;
    FILE *fptr=fopen("bankCustomers.dat","wb");
    while(var<lim){
        fwrite(&arr[var],sizeof(Acc),1,fptr);
        var++;
    }
    fclose(fptr);
    if (count==1){
        printf("Withdraw Successful and Balance Updated\n");
    }
    else{
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}

void balance(Acc arr[],int lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    for (int i=0;i<lim;i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
            printf("Balance : %f\n",arr[i].initialDeposit);
        }
    }
    if (count!=1){
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}

void transfer(Acc arr[],int lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    int sender,receiver;
    for (int i=0;i<lim;i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
            sender=i;
            break;
        }
    }
    if (count==1){
        printf("Enter recipient's account Number : ");
        long long int accno1;
        scanf("%lld",&accno1);
        int count1=0;
        for (int i=0;i<lim;i++){
            if (arr[i].accNo==accno1){
                count1++;
                receiver=i;
                break;
            }
        }
        if (count1==1){
            printf("Enter amount to transfer : ");
            float trnsfr;
            scanf("%f",&trnsfr);
            if (arr[sender].initialDeposit>=trnsfr){
                arr[sender].initialDeposit-=trnsfr;
                arr[receiver].initialDeposit+=trnsfr;
                int var=0;
                FILE *fptr=fopen("bankCustomers.dat","wb");
                while(var<lim){
                    fwrite(&arr[var],sizeof(Acc),1,fptr);
                    var++;
                }
                fclose(fptr);
                printf("Amount Successfully Transfered...\n");
            }
            else{
                printf("Insufficient Balance\n");
            }
        }
        else{
            printf("Access Denied(Wrong Recipient's Acc No./Recipient's Account doesn't exist)\n");
        }
    }
    else{
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}

void close(Acc arr[],int* lim){
    printf("Enter your account Number : ");
    long long int accno;
    scanf("%lld",&accno);
    int pin;
    printf("Enter PIN of your account Number : ");
    scanf("%d",&pin);
    int count=0;
    int idx;
    for (int i=0;i<(*lim);i++){
        if (arr[i].accNo==accno && arr[i].PIN==pin){
            count++;
            idx=i;
            break;
        }
    }
    if (count==1){
        int var=0;
        FILE *fptr=fopen("bankCustomers.dat","wb");
        while(var<(*lim)){
            if (var!=idx){
                fwrite(&arr[var],sizeof(Acc),1,fptr);
            }
            var++;
        }
        fclose(fptr);
        int ct=0;
        fptr=fopen("bankCustomers.dat","rb");
        while(fread(&arr[ct],sizeof(Acc),1,fptr)==1){
            ct++;
        }
        fclose(fptr);
        *lim=ct;
        printf("Account Deleted Successfully\n");
    }
    else{
        printf("Access Denied(Wrong PIN/Acc No./Account doesn't exist)\n");
    }
    return;
}