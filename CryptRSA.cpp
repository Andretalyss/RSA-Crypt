#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>

using namespace std;
 
long int p, q, n, t, verify;
long int pub[100], pri[100], temp[100], j, i;

char mes[100], enc[100];
char msg[100];

int VerifyPrime(long int prime);
void Found();
long int Dkeys(long int x);
void Encrypt();
void Decrypt();
void WriteArchive();

int main()
{
    printf("Primeiro número primo: ");
    cin >> p;

    //verify = VerifyPrime(p);
    if (!VerifyPrime(p)){
        printf("Não é primo\n");
        return 0;
    }

    printf("Segundo número primo: ");
    cin >> q;

    if (!VerifyPrime(q) || p == q){
        printf("Não é primo\n");
        return 0;
    }
    
    printf("Messagem: ");
    fflush(stdin);
    cin.ignore();
    fgets(msg,100,stdin);
    if(msg[strlen(msg)-1] == '\n')
     msg[strlen(msg)-1] = '\0';
       
    for (i = 0; msg[i] != '\0'; i++)
        mes[i] = msg[i];

    n = p * q;
    t = (p - 1) * (q - 1);

    Found();

    Encrypt();
    WriteArchive();
    Decrypt();
    printf("\n\n");

    return 0;
}

void Found(){
    int k;
    k = 0;

    for (i = 2; i < t; i++){
        if (t % i == 0)
            continue;

        verify = VerifyPrime(i);
        if (verify == 1 && i != p && i != q){
            pub[k] = i;
            verify = Dkeys(pub[k]);

            if (verify > 0){
                pri[k] = verify;
                k++;
            }

            if (k == 99)
                break;
        }
    }

    printf("\nPublic Keys\tPrivate Keys\n");
    for (i = 0; i < j - 1; i++)
        printf("%ld\t\t%ld\n", pub[i],pri[i]);

}

int VerifyPrime(long int prime)
{
    int i;
    j = sqrt(prime);
    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
            return 0;
    }
    return 1;
}

long int Dkeys(long int x){
    long int k = 1;

    while (1){
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

void Encrypt(){
    long int pt, ct, key = pub[0], k, len;
    i = 0;
    len = strlen(msg);

    while (i != len){
        pt = mes[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++){
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        enc[i] = ct;
        i++;
    }

    enc[i] = -1;
    i=0;
    printf("\nMessage encrypted: ");
    while(enc[i] != -1){
        printf("%c", enc[i]);
        i++;
    }
}

void Decrypt(){
    long int pt, ct, key = pri[0], k;
    i = 0;

    while (enc[i] != -1){
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++){
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        mes[i] = pt;
        i++;
    }

    mes[i] = -1;
    i=0;
    printf("\nMessage descrypted: ");
    while(mes[i] != -1){
        printf("%c", mes[i]);
        i++;
    }   
}

void WriteArchive(){
    FILE *arq;
    arq = fopen("Archive/Cryptografed.txt", "wb");
    if(!arq)
        puts("Don't open");

    int i=0;
    while(enc[i] != -1){
    fwrite(enc,1,sizeof(enc),arq);
    i++;
    }

    fclose(arq);
}
