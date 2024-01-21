#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h> //colors
#include <time.h> //srand(time)
#define MAX_LENGTH 100
#include "main2.h"


const char *Adminfile = "admin.txt";
const char *informationcmpt = "information-compte.txt";
const char *FileLogIn = "auth.txt";
const char *NewFileName = "tmp.txt";
const char *NewFileName2 = "tmp2.txt";
const char *InfoPaylpal = "PaypalDipot.txt";
const char *InfoVirement = "InfoVirement.txt";
const char *Logfile = "Logfile.txt";

FILE *p;

// initialisation des "structures"
typedef struct {
    int jour,mois,annee;

}date;

typedef struct {
      int id;
      char nom[20];
      char prenom[20];
      char CIN[15];
      char type_Compte[20];
      char type_de_reclamations[20];
      char state[20];
      char password[20];
      uint64_t hashpass;
      float montant ;
      date date_naissance;
      int tele;

}client;
client Pclient;
client cl, clt;

typedef struct{
    char nom[20], prenom[20];
    char password[50];
    int num;
    double some;

}clientinfo;

clientinfo InfoClt;

typedef struct {
    int id;
    char nom[20];
    char prenom [20];
    char tel[20];
    char password[20];
    uint64_t hashpass;

}Admin;

typedef struct {

     int numero_compte;
     float solde ;
     client Client ;
}Compte;



// fonction de verification jour
void test_jour(int a, int m) {
    int jour;
    printf("\n\t\t\t\t\t\tJOUR : ");
    scanf("%d", &jour);

    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        if (jour < 1 || jour > 31){
            printf("jour invalide");
            sleep(2);
            test_mois(a, m);
        }
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (jour < 1 || jour > 30){
            printf("jour invalide");
            sleep(2);
        }
    } else if (m == 2) {
        if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
            if (jour > 29 || jour < 1) {
                printf("SAISIE INVALIDE ");
                sleep(2);
                test_jour(a, m);
            }
        } else {
            if (jour > 28 || jour < 1) {
                printf("SAISIE INVALIDE ");
                sleep(2);
                test_jour(a, m);
            }
        }
    }
}

// fonction de verification annee
int test_annee() {
    int annee;
    printf("\n\t\t\t\t\t\tANNEE : ");
    scanf("%d", &annee);
    if (annee < 1900){
        printf("annee invalide");
        sleep(2);
        test_annee();
    }
    else if (annee > 2005){
        printf("vous devez avoir plus de 18 ans");
        sleep(2);
        test_annee();}
    return annee;
}


// fonction de verification mois
void test_mois() {
    int mois;
    printf("\n\t\t\t\t\t\tMOIS : ");
    scanf("%d", &mois);
    if (mois < 1 || mois > 12){
        printf("mois invalide, Veuillez saisir un mois entre 1 et 12");
        sleep(2);
        test_mois();
    }
}

//log in
void succeed()
{

    int choix;
    system("cls");

    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*                   CLIENT                             *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          [1]- Gerer mon compte                       *\n");
    printf("\t\t*          [2]- Depose                                 *\n");
    printf("\t\t*          [3]- Retire de l'argent                     *\n");
    printf("\t\t*          [4]- Transferer                             *\n");
    printf("\t\t*          [5]- Solde                                  *\n");
    printf("\t\t*          [6]- Log out                                *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t********************************************************\n");
    printf("\t\t\tENTRER VOTRE CHOIX : ");

    if (scanf("%d", &choix) != 1) {
        // Input is not an integer
        printf("Choix invalide.s'il vous plais Entrer un numero\n");
        sleep(2);
        succeed();
    }
    switch(choix)
    {
        case 1 :    manageClientAccount();break;
        case 2 :    dipose();break;
        case 3 :    withdraw();break;
        case 4 :    SendMoney();break;
        case 5 :    ClientBalance();break;
        case 6 :    Logout();break;
        default :
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("\n\n\t\t\t\tInvalide option.!");sleep(2);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            succeed();break;
    }
}

void manageClientAccount()
{
    system("cls");
    int choix;

    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t******************************************************\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*              MENU DES PARAMETRES                   *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [1] Changer le mot de passe                       *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [2] Consulter l'admin                             *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [3] Changer le type du compte                     *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [4] Supprimer votre compte                        *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [0] Retourner au menu principal                   *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t******************************************************\n");

    printf("\n\t\t\t==>  ");

    if (scanf("%d", &choix) != 1) {
        // Input is not an integer
        printf("Choix invalide.s'il vous plais Entrer un numero\n");
        sleep(2);
        manageClientAccount();
    }
    switch(choix)
    {
        case 1 :    Confirme_change_passwd();break;
        case 2 :    Admin_Consulting();break;
        case 3 :    Change_AC_type();break;
        case 4 :    int nt;char passwd[50];
                    printf("Conffirmer la suppression. entrer votre mot de passe : ");
                    read_password(passwd);
                    if(strcmp(passwd, Pclient.password)==0 && AccDelete())
                    {
                        printf("merci de consulter l'agence pour effectuer la demarche");
                        sleep(2);
                        char c = getche();
                        Logout();
                    }
                    else{
                        printf("merci de consulter l'agence pour effectuer la demarche");sleep(3);Logout();
                    }
                    break;

        case 0 :    succeed();break;
        default :
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("\n\n\t\t\t\tInvalide option.!");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            sleep(2);manageClientAccount();break;



    }

}

//Managing the client's account >> Password
void Confirme_change_passwd()
{
        system("cls");
        char Crpassword[50];
        char Npasswd[50], CNpasswd[50];
        //Getting the password
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\tEntrer votre mot de passe : ");
        read_password(Crpassword);
        cl.hashpass = hash_password(Crpassword);

        //Comparing the passwords
        if(cl.hashpass == Pclient.hashpass)
        {
            do{
                printf("\n\t\tNouveau mot de passe : ");scanf("%s", Npasswd);
                if(strlen(Npasswd) <= 6)
                {
                    printf("\n\t\t-Mot De Passe invalide, un mot de passe securise doit contenir au moins 6 caracteres!\n\n");

                }

            }while(strlen(Npasswd) <= 6);


            printf("\t\tComfirmer le Nouveau mot de passe : ");scanf("%s", CNpasswd);
            if(strcmp(CNpasswd, Npasswd)!=0)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
                printf("\n\t\tles mots de passe ne sont pas identiques!!");
                sleep(2);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                Confirme_change_passwd();
            }
            else
            {
                if(change_password_auth(Npasswd) && change_password_info(Npasswd))
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    printf("\n\t\tLe mot de passe e ete change..!\n");
                    printf("\t\t\tRetourner..");
                    for(int i=3; i>0; i--)
                    {
                        printf(".");
                        sleep(1);
                    }
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                    manageClientAccount();

                }
                else
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
                    printf("\n\t\tle mot de pass n'est pas changer!!");
                    for(int i=3; i>0; i--)
                    {
                        printf("!");
                        sleep(1);
                    }
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                    manageClientAccount();
                }
            }


        }
        else
        {
            printf("\n\t\t\tLe mot de passe est incorrect!!");
            sleep(3);
            manageClientAccount();

        }

}
//Changing the Client's password
int change_password_auth(const char Newpassword[])
{
    //changing Autfile
    p = fopen(FileLogIn, "rt");
    if(!p)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    FILE *p1 = fopen(NewFileName, "wt+");
    if(!p1)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    int valide=0;
    uint64_t password;
    do{

        fscanf(p, "%d\t%llu\n", &clt.id, &password);

        if(Pclient.id==clt.id)
        {
            clt.hashpass = hash_password(Newpassword);
            fprintf(p1, "%d\t%llu\n", clt.id, clt.hashpass);
            valide =1;
        }
        else{
            fprintf(p1, "%d\t%llu\n", clt.id, password);
        }
    }while(!feof(p));
    fclose(p);
    fclose(p1);
    if(valide && remove(FileLogIn)==0 &&rename(NewFileName, "auth.txt")==0)
    {

        return 1;
    }
    else
    {
        return 0;
    }



}
//changing compte-info file
int change_password_info(const char Newpassword[])
{
    FILE *p2= fopen(informationcmpt, "rt");
    if(!p2)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    FILE *p3 = fopen("tmp.txt", "wt+");
    if(!p3)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    int valide=0;
    do{
        fscanf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %.2f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state);
        if(Pclient.id==cl.id)
        {
            uint64_t hashed_password = hash_password(Newpassword);
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %.2f || type_compte : %s || State = %s\n", cl.id, hashed_password, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
            //getino
            Pclient.montant = cl.montant;
            Pclient.hashpass = hashed_password;
            strcpy(Pclient.CIN, cl.CIN);
            strcpy(Pclient.type_Compte, cl.type_Compte);
            strcpy(Pclient.nom, cl.nom);
            strcpy(Pclient.prenom, cl.prenom);
            strcpy(Pclient.state, cl.state);
            valide =1;
        }
        else{
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %.2f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
        }
    }while(!feof(p2));

    fclose(p2);
    fclose(p3);
    if(valide && remove(informationcmpt)==0 &&rename(NewFileName, "information-compte.txt")==0)
    {

        return 1;
    }
    else
    {
        return 0;
    }

}
//Managing the client's account >> Consultation
void Admin_Consulting()
{

    int choix;
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t**************************************\n");
    printf("\t\t*          Admine Consulting         *\n");
    printf("\t\t**************************************\n");
    printf("\n\n");
    printf("\t\tMail de l'Admine : massin2020nh@gmail.com\n\n");
    printf("\t\t\t[1] Envoyer une reclamation\n");
    printf("\t\t\t[0] Retourner\n");
    printf("\n\n\t\t\t\t==> ");

    if (scanf("%d", &choix) != 1) {
        // Input is not an integer
        printf("\n\t\tChoix invalide.s'il vous plais Entrer un numero\n");
        sleep(2);
        Admin_Consulting();
    }
    switch(choix)
    {
        case 1:     reclamations(&Pclient.id);break;
        case 0:     manageClientAccount();break;
        default :
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("\t\t\t\tInvalide option !");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
             sleep(2);Admin_Consulting();


    }


}

//Managing the client's account >> Change account type
void Change_AC_type()
{
    system("cls");
    int choix;
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t************************************************************\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t*  Votre compte est un compte : %s\n", Pclient.type_Compte);
    printf("\t\t*                                                          *\n");
    printf("\t\t*  Les types possibles :                                   *\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t*      [1] Compte COURANT                                  *\n");
    printf("\t\t*      [2] Compte CHEQUE                                   *\n");
    printf("\t\t*      [3] Compte ETUDIANT                                 *\n");
    printf("\t\t*      [4] Voir les caractéristiques de chaque type        *\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t*      [0] Retourner                                       *\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t************************************************************\n");

    printf("\t\t\t ==>    ");

    if (scanf("%d", &choix) != 1) {
        // Input is not an integer
        printf("Choix invalide.s'il vous plais Entrer un numero.\n");
        sleep(2);
        Change_AC_type();
    }

    void modifyAccType(char acctype[])
    {
        printf("\n\t\t\tVous avez choisir un compte %s\n", acctype);

        if(changeinfo_typeaccount(acctype))
        {
            printf("\n\t\t\tRetourner.."); for(int i=3; i>0; i--){printf(".");sleep(2);};
            manageClientAccount();

        }
        else

        {

            printf("\nUne erreur s'est produite");
            sleep(2);

        }
    }
    switch(choix)
    {
        case 1 : modifyAccType("COURANT");break;
        case 2 : modifyAccType("CHEQUE");break;
        case 3 : modifyAccType("ETUDIANT");break;
        case 4 : system("cls");ActypeDocumentation();Change_AC_type();break;
        case 0 : manageClientAccount();break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("Choix invalide\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            sleep(2); Change_AC_type();

    }


}
int changeinfo_typeaccount(char acctype[])
{
    FILE *p2= fopen(informationcmpt, "rt");
    if(!p2)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    FILE *p3 = fopen("tmp.txt", "wt+");
    if(!p3)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    int valide=0;

    while (fscanf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9)
    {
        if(Pclient.id==cl.id)
        {
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, acctype, cl.state);
            //getino
            Pclient.montant = cl.montant;
            Pclient.hashpass = cl.hashpass;
            strcpy(Pclient.CIN, cl.CIN);
            strcpy(Pclient.type_Compte, acctype);
            strcpy(Pclient.nom, cl.nom);
            strcpy(Pclient.state, cl.state);
            valide =1;
        }
        else{
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
        }
    }

    fclose(p2);
    fclose(p3);
    if(valide && remove(informationcmpt)==0 &&rename(NewFileName, "information-compte.txt")==0)
    {

        return 1;
    }
    else
    {
        return 0;
    }


}
//Documentation about Acc types
void ActypeDocumentation()
{
    //We can chow a file without doing this manualy
    // Define a two-dimensional array to store the table
    printf("\n\n\n\n\n");
    char categories[][30] = {"Compte CHEQUE", "Compte ETUDIANT", "Compte COURANT"};
    char descriptions[][100] = {
        "Compte de base pour la gestion quotidienne de l'argent.",
        "Pour les etudiants, ce type de compte peut offrir des frais reduits ou des avantages speciaux.",
        "Ce compte est destine a epargner de l'argent a moyen ou long terme."};

    // Display header
    printf("\t\t Documentation sur les types de compte possible ");
    printf("\n\n");
    printf("\t\t%-20s %-50s\n", "Category", "Description");
    printf("\t\t--------------------------------------------------------------\n");

    // Display each row of the table
    for (int i = 0; i < 3; ++i)
    {
        printf("\t\t%-20s %-50s\n", categories[i], descriptions[i]);
    }
    char ts;
    printf("\n\n");
    printf("\t\t Retourve/entrer quelque chose..");ts = getche();
}

//Diposer de l'argent
void dipose()
{
    int choix;
    system("cls");
  printf("\n\n\n\n");
    printf("\t\t**************************************************\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      Deposer de l'argent a partir de :          *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      [1] Compte PayPal                          *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      [2] Virement Bancaire                      *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      [0] Retourner                              *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t**************************************************\n");
     printf("\t\t\t ==> ");

    if (scanf("%d", &choix) != 1) {
        // Input is not an integer
        printf("Invalid input. Please enter a number.\n");
        sleep(2);
        manageClientAccount();
    }
    // Nettoyer le tampon d'entrée
    while(getchar() != '\n');

    switch (choix) {
        case 1:
            DepotPayPal();
            break;
        case 2:
            DepotVrm();
            break;
        case 0:
            succeed();
            break;
        // Ajoutez d'autres cas pour d'autres méthodes si nécessaire
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("Choix non valide.\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            sleep(2);
            dipose();
            break;
    }
}


//Methode de depot
void DepotPayPal() {
    //getting information about user
    char name[20];char choix[20];
    char prenom[20];
    // Saisir les informations personnelles pour PayPal
    printf("\n\n");
    printf("\n\t=============================================================\n");
    printf("\t\tSaisissez vos informations personnelles pour PayPal:\n");
    printf("\t\t\tNom: ");
    scanf("%s", InfoClt.nom);

    printf("\t\t\tPrenom: ");
    scanf("%s",InfoClt.prenom);


    printf("\t\t\tNumero du compte: ");
    scanf("%d",&InfoClt.num);


    printf("\t\t\tMot de passe du Compte Paypal: ");
    read_password(InfoClt.password);

    printf("\n\t\tInformations personnelles pour PayPal:\n");
    printf("\n\t\t\tNom: %s", InfoClt.nom);
    printf("\n\t\t\tPrenom: %s", InfoClt.prenom);
    printf("\n\t\t\tNumero du Paypayl: %d", InfoClt.num);
    printf("\n\n\t\t\t\tConfirmez [Y,n] : "); scanf("%s", choix);

    if(strcmp(choix, "n") && strcmp(choix , "non"))  //Problem in this
    {
        FILE *p= fopen(InfoPaylpal, "at");
        if(!p)
        {
            printf("\nYou have an error ");
            sleep(2);
            dipose();

        }
        fprintf(p, "%-20d || %-20s %-20s || %-20d || %-20s\n ", Pclient.id, InfoClt.nom, InfoClt.prenom, InfoClt.num, InfoClt.password);

        fclose(p);
        int choix=0;
        printf("\n\t\tEntrer la somme que vous voulez diposer en($) : "); scanf("%lf", &InfoClt.some);
        fgets(InfoClt.password, sizeof(InfoClt.password), stdin);
        if(InfoClt.some > 0 && InfoClt.some<1000000)
        {
            printf("\t\tVous voulez diposer %0.2f $, Confirmez par 1 : ", InfoClt.some); scanf("%d",&choix);
            if(choix ==1)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the Green color
                printf("\n\t\tle dipot a ete effectuer avec succes..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);

                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                if(changeINFO(Pclient.id))  //changing client info
                dipose();
                else{

                    printf("Une erreur se produit");
                    sleep(2);
                    dipose();
                    }
            }
            else
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
                printf("\n\t\t L'operation n'a pas ete effectuer ..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);

                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                dipose();
            }
        }
        else if(InfoClt.some <0)
        {
            choix =0;
            printf("\t\t\tVous voulez diposer %0.2f $, Confirmez par 1", (-1*InfoClt.some)); scanf("%d",&choix);
            if(choix ==1)
            {
                printf("\t\t\tle dipot a ete effectuer avec succes..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);
                }
                if(changeINFO(Pclient.id))  //changing client info
                dipose();
                else{

                    printf("Une erreur se produit");
                    sleep(2);
                    dipose();
                    }

            }
            else{

                dipose();
            }

        }
        else if(InfoClt.some > 1000000)
        {

            choix =0;
            char c;
            printf("\t\t\tVous voulez diposer une tres grande somme\n");
            printf("\t\t\t\t Consulter l'agence ..!");
            for(int i =3; i>0; i--)
            {
                printf("!");
                sleep(1);

            }
            c = getche(); //press to continue
            dipose();

        }
        else
        {
            printf("\t\t\tL'operation n'a pas ete validee..");
            for(int i =3; i>0; i--)
            {
                printf(".");
                sleep(1);

            }
            dipose();

        }
    }
    else
    {
        printf("\t\t\tL'operation n'a pas ete confirmer...");
        sleep(2);
        dipose();
    }


}
//Updating changes
int changeINFO(int id)
{
    FILE *p2= fopen(informationcmpt, "rt");
    if(!p2)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    FILE *p3 = fopen("tmp.txt", "wt+");
    if(!p3)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    int valide=0;


    while (fscanf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9)
    {
        if(cl.id=id)
        {
            float newAmount = InfoClt.some + cl.montant;
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, newAmount, cl.type_Compte, cl.state);
            //get-inofo
            Pclient.montant = newAmount;
            Pclient.hashpass = cl.hashpass;
            strcpy(Pclient.CIN, cl.CIN);
            strcpy(Pclient.type_Compte, cl.type_Compte);
            strcpy(Pclient.nom, cl.nom);
            strcpy(Pclient.prenom, cl.prenom);
            strcpy(Pclient.state, cl.state);
            valide =1;
        }
        else{
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
        }
    }

    fclose(p2);
    fclose(p3);
    if(valide && remove(informationcmpt)==0 &&rename(NewFileName, "information-compte.txt")==0)
    {

        return 1;
    }
    else
    {
        return 0;
    }



}

void DepotVrm() {
 //getting information about user
    char name[20];char choix[20];
    char prenom[20];
    // Saisir les informations personnelles pour PayPal
    printf("\n\n");
    printf("\n\t=================================================================================================\n");
    printf("\t\tSaisissez vos informations personnelles pour effectuer un Virement Banquaire:\n");

    printf("\t\t\tNom: ");
    scanf("%s", InfoClt.nom);

    printf("\t\t\tPrenom: ");
    scanf("%s",InfoClt.prenom);


    printf("\t\t\tNumero du compte: ");
    scanf("%d",&InfoClt.num);


    printf("\t\t\tMot de passe du Compte Bancaire: ");
    read_password(InfoClt.password);

    // Traitez les informations personnelles comme vous le souhaitez
    printf("\n\t\tInformations personnelles pour PayPal:\n");
    printf("\n\t\t\tNom: %s", InfoClt.nom);
    printf("\n\t\t\tPrenom: %s", InfoClt.prenom);
    printf("\n\t\t\tRIB: %d", InfoClt.num);
    printf("\n\t\t\t\tConfirmez [Y,n] : "); scanf("%s", choix);

    if(strcmp(choix, "n") && strcmp(choix , "non"))
    {
        FILE *p= fopen(InfoVirement, "at");
        if(!p)
        {
            printf("You have an error ");
            sleep(2);
            dipose();

        }
        fprintf(p, "%d   ||   %s %s   ||   %d   ||   %s", Pclient.id, InfoClt.nom, InfoClt.prenom, InfoClt.num, InfoClt.password);

        fclose(p);
        int choix=0;
        printf("\n\t\tEntrer la somme que vous voulez diposer en($) : ");
        scanf("%lf", &InfoClt.some);

        if(InfoClt.some > 0 && InfoClt.some<1000000)
        {
            printf("\t\tVous voulez dipose %0.2f $, Confirmez par 1 : ", InfoClt.some); scanf("%d",&choix);
            if(choix ==1)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the green color
                printf("\t\tle dipot a ete effectuer avec succes..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);

                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color

                if(changeINFO(Pclient.id)) manageClientAccount(); //changing client info
                else{

                        printf("Une erreur se produit");
                        sleep(2);
                        manageClientAccount();
                    }
            }
            else
            {
                printf("\t\t L'operation n'a pas ete effectuer ..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);

                }
                manageClientAccount();
            }
        }
        else if(InfoClt.some <0)
        {
            choix =0;
            printf("\t\t\tVous voulez dipose %0.2df $, Confirmez par 1", (-1*InfoClt.some)); scanf("%d",&choix);
            if(choix ==1)
            {
                printf("\t\t\tle dipot a ete effectuer avec succes..!");
                for(int i =3; i>0; i--)
                {
                    printf("!");
                    sleep(1);
                    manageClientAccount();
                }

            }

        }
        else if(InfoClt.some > 1000000)
        {

            choix =0;
            printf("\t\t\tVous voulez diposer une tres grande somme\n");
            printf("\t\t\t\t Consulter l'agence ..!");
                printf("\t\t\tle dipot a ete effectuer avec succes..!");
            for(int i =3; i>0; i--)
            {
                printf("!");
                sleep(1);

            }
            manageClientAccount();

        }
        else
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the green color
            printf("\t\tle dipot a ete effectuer avec succes..!");
            for(int i =3; i>0; i--)
            {
                printf("!");
                sleep(1);

            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color

            if(changeINFO(Pclient.id)) manageClientAccount(); //changing client info
            else{

                    printf("Une erreur se produit");
                    sleep(2);
                    manageClientAccount();
                }
        }
    }
    else
    {
        printf("\t\t\tL'operation n'a pas ete confirmer...");
        sleep(2);
        dipose();
    }

}


//Money Withdraw
void withdraw()
{

    int confirmwithdraw(int id)
    {


            FILE *p2= fopen(informationcmpt, "rt");
            if(!p2)
            {
                fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
                return 1;
            }
            FILE *p3 = fopen("tmp.txt", "wt+");
            if(!p3)
            {
                fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
                return 1;
            }

            int valide=0;


            while (fscanf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9)
        {
                if(id ==cl.id)
                {
                    fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, Pclient.montant, cl.type_Compte, cl.state);
                    //get-inofo

                    Pclient.hashpass = cl.hashpass;
                    strcpy(Pclient.CIN, cl.CIN);
                    strcpy(Pclient.type_Compte, cl.type_Compte);
                    strcpy(Pclient.nom, cl.nom);
                    strcpy(Pclient.prenom, cl.prenom);
                    strcpy(Pclient.state, cl.state);
                    valide =1;
                }
                else{
                    fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte), cl.state;
                }
            }

            fclose(p2);
            fclose(p3);
            if(valide && remove(informationcmpt)==0 &&rename(NewFileName, "information-compte.txt")==0)
            {

                return 1;
            }
            else
            {
                return 0;
            }
    }


    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t************************************************************\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t*                   Faire un retrait                       *\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t*  Votre solde bancaire est : %.2f                         *\n", Pclient.montant);
    printf("\t\t*                                                          *\n");
    printf("\t\t*  Combien souhaitez-vous retirer (0 pour retourner):      *\n");
    printf("\t\t*                                                          *\n");
    printf("\t\t************************************************************\n");

    printf("\t\t\t==> ");

    if (scanf("%f", &clt.montant) != 1) {
        // Input is not an integer
        printf("\n\t\tMontant invalide! essayer a nouveau\n");
        sleep(2);
        withdraw();
    }
    if(clt.montant==0)
    {
        succeed();
    }

    else if(clt.montant<0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
        printf("\n\t\tVous ne pouvez pas retirer un montant negatif..!");
        for(int i =0; i<=3;i++)
        {
            printf("!");
            sleep(1);
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        succeed();
    }

    else if(Pclient.montant >= clt.montant)
    {
        Pclient.montant = Pclient.montant - clt.montant;
        if(confirmwithdraw(Pclient.id))
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the red color for the invalide option prompte
             printf("\n\t\t Le retrait a ete effectue avec succes..");
            for(int i =0; i<=3;i++)
            {
                printf("!");
                sleep(1);
            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            succeed();

        }
        else
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
            printf("\n\t\tOperation invalide!!");
            sleep(3);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            succeed();

        }

    }
    else
    {
        printf("\n\t\tSolde est insuffisant..");
        for(int i =0; i<3;i++)
        {
            printf("!");
            sleep(1);
        }
        succeed();
    }



}
void SendMoney()
{
    system("cls");
    int choix;

    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*              Transferer de l'argent                  *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          Votre solde bancaire est : %.2f             *\n", Pclient.montant);
    printf("\t\t********************************************************\n");

    printf("\n\t\t\tENTRER VOTRE mot de passe : ");
    read_password(clt.password);
    if(!strcmp(Pclient.password , clt.password))
    {
        char c;
        printf("\n\t\t\tEntrer ID du destinataire : ");
        scanf("%d", &clt.id);
        printf("\n\t\t\tENTREZ LE MONTANT A TRANSFERER : ");
        scanf("%f", &clt.montant);
        printf("\n\t\t\tCONFIRMER PAR Y/n : ");
        c = getche();
        if(c != 'n')
        {
            //Invalide Amount
            if(clt.montant > Pclient.montant || clt.montant<=0 )
            {
                int x;
                printf("\n\t\t\tLE MONTANT est invalide");
                printf("entrer 0 pour essayer a nouveau : ");
                scanf("%d", &x);
                if(!x)
                {
                    SendMoney();

                }
                else
                {
                    system("cls");
                    succeed();
                }


            }
            else
            {
                if(CheckReceiverID(clt.id))
                {
                    TransferMoney(clt.id);


                }
                else
                {
                    char c;

                    printf("\n\t\t\tID du destinataire est invalide");
                    sleep(2);
                    c = getche();
                    succeed();
                }


            }
        }

        else
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf("\n\t\t\tL'operation a ete annulee .\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            sleep(3);
            succeed();
        }
    }

    else
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
        printf("Mot de passe incorrect");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        sleep(3);
        succeed();
    }

}
//Confirm Swap
void TransferMoney(int id)
{

    FILE *p2= fopen(informationcmpt, "rt");
    if(!p2)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    FILE *p3 = fopen("tmp.txt", "wt+");
    if(!p3)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    int valide=0;
    double amountuser =0 ;

    while (fscanf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9)
 {
        if(id==cl.id)
        {
            valide ++;

            double Amount = clt.montant + cl.montant;
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, Amount, cl.type_Compte, cl.state);
        }
        else if(Pclient.id==cl.id)
        {
            valide ++;
            amountuser = cl.montant - clt.montant;
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, amountuser, cl.type_Compte, cl.state);

        }
        else{
            fprintf(p3, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
        }
    }

    fclose(p2);
    fclose(p3);
    if(valide==2 && remove(informationcmpt)==0 && rename(NewFileName, "information-compte.txt")==0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the green color

        printf("\n\n\t\t\tl'operation est valide\n");
        sleep(2);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        succeed();

    }
    else
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
        printf("\n\n\t\t\tl'operation est invalide  \n");
        sleep(2);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        succeed();
    }

}


//checking the ID of the receiver
int CheckReceiverID(int receiverID)
{
    p = fopen(FileLogIn, "rt");
    if(!p)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    int valide=0;
    int *pos;
    do{

        fscanf(p, "%d\t%s\n", &cl.id, cl.password);

        if(receiverID==clt.id)
        {
            valide =1;
            break;
        }


    }while(!feof(p));

    fclose(p);

    if(valide)
    {

        return 1;
    }
    else
    {
        return 0;
    }


}


//Delete account
int AccDelete()
{
    p = fopen(FileLogIn, "rt");

    if(!p)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 0;
    }
    FILE *p1 = fopen(NewFileName, "wt+");
    if(!p1)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 0;
    }

    int valide=0;
    do{

        fscanf(p, "%d\t%llu\n", &clt.id, &clt.hashpass);

        if(Pclient.id==clt.id)
        {
            valide =1;
        }
        else{
            fprintf(p1, "%d\t%llu\n", clt.id, clt.hashpass);
        }



    }while(!feof(p));
    fclose(p);
    fclose(p1);
    if(valide && remove(FileLogIn)==0 &&rename(NewFileName, "auth.txt")==0 && deactivateAcc())
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

int deactivateAcc()
{
    FILE *p1 = fopen(informationcmpt, "rt");
    FILE *p2 = fopen(NewFileName2, "wt+");
    if(!p1)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 0;
    }

    if(!p2)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 0;
    }

    //this function checks the matching information of the specified id
    int trv=0;
    while (fscanf(p1, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9) {
            if (Pclient.id == cl.id) {
                strcpy(cl.state, "Deactivate");
                fprintf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);
                trv = 1;
                strcpy(Pclient.state, "Deactivate");
            }
            else
            {
                fprintf(p2, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", cl.id, cl.hashpass, cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);

            }
        }
    fclose(p1);
    fclose(p2);
    if(trv ==1 && remove(informationcmpt)==0 &&rename(NewFileName2, "information-compte.txt")==0)
    {

        return 1;
    }
    else{

        return 0;
    }



}
void ClientBalance()
{
    GetInfo(Pclient.id);
    system("cls");
    char c;
    printf("\n\n\n\n\n\n");
    printf("\t\t ******************************************************\n");
    printf("\t\t*                                                     *\n");
    printf("\t\t*           Votre solde est : %.2f $                  \n", Pclient.montant);
    printf("\t\t*                                                     *\n");
    printf("\t\t*                  tape quelque chose pour Retourner  *\n");
    printf("\t\t ******************************************************\n");

    c = getche();
    succeed();
}
void Logout()
{
    system("cls");
    AfficherMenuPrincipale();


}


void login(){
     FILE *p;

     int ide;
     char passwd[50];

    printf("\n\n\n\n\n\n");
    printf("\t\t**************************************************\n");
    printf("\t\t*                    Log in                      *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      DONNER VOTRE ID:                          *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      DONNER VOTRE MOT DE PASSE :               *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t**************************************************\n");
    //printf("\t\t\tVotre ID: ");
    gotoxy(40, 10);
    scanf("%d", &ide);

    //printf("\t\t\tVotre mot de passe: ");
    gotoxy(51, 12);
    //scanf("%s", passwd);
    read_password(passwd);
    cl.hashpass = hash_password(passwd);

    //init the pointer to the authentication file
    p = fopen(FileLogIn, "rt");
    if(!p)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    //this function checks if the client's password is correct
    int trv =0;
    do{

        fscanf(p, "%d\t%llu\n", &Pclient.id, &Pclient.hashpass);

        if(ide== Pclient.id && cl.hashpass == Pclient.hashpass )
        {
            trv =1;
            break;
        }
    }while(!feof(p));
    fclose(p);

    if(trv ==1 )
    {
        //Auth passed
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the green color
        printf("\n\n\n\t\t\t\tConnectez-vous avec succes!!");
        sleep(1);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        //Get info
        GetInfo(Pclient.id);

        //log file
        saveCurrentDateTime(Logfile, ide);
        //calling the succeed function
        succeed();

    }
    else
    {
        //Auth Failed
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
        printf("\n\n\n\t\t\t\tLa connexion a Echoue!!");
        sleep(2);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        system("cls");
        //calling the failed function
        menuClient();

    }
}
//Get info about the user
void GetInfo(int id)
{
    FILE *p1;
    p1 = fopen(informationcmpt, "rt+");
    if(!p1)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }

    //this function checks the matching information of the specified id
    int trv=0;










    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), p1)) {
        if (sscanf(buffer, "Id: %d || Password: %llu || Nom : %49s || Prénom : %49s || CIN : %19s || Num-Telephone: %d || Solde: %f || type_compte : %19s || State = %19s",
                   &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9) {
            if (id == cl.id) {
                // Found the matching ID
                trv =1;
                break;
            }
    }
    }

    fclose(p1);

    if(trv ==1)
    {
        strcpy(cl.state, "Activate");
        Pclient.hashpass = cl.hashpass;
        Pclient.montant = cl.montant;
        strcpy(Pclient.state, cl.state);
        strcpy(Pclient.CIN, cl.CIN);
        strcpy(Pclient.type_Compte, cl.type_Compte);
        strcpy(Pclient.nom, cl.nom);
        strcpy(Pclient.prenom, cl.prenom);

    }
    else{

        printf(" Error, TRY AGAIN LATER!!!");
        sleep(2);
        system("cls");
        menuClient();
    }

}


// fonction inscription du client
void inscription() {
    FILE *f;

    f = fopen(informationcmpt, "at");

    if (!f) {
        printf("Error opening file.\n");
        return;
    }
    //printf("\n\n\n\n\n");
    printf("\n\n\t\t******************* Inscription *******************\n\n");
    printf("\t\tSAISIR VOTRE NOM: ");
    scanf("%s", cl.nom);
    printf("\t\tSAISIR VOTRE PRENOM: ");
    scanf("%s", cl.prenom);
    printf("\t\tSAISIR VOTRE CIN: ");
    scanf("%s", cl.CIN);
    printf("\t\tSAISIR VOTRE num-telephone: ");
    scanf("%d", &cl.tele);

    printf("\n\t\tSAISIR VOTRE DATE DE NAISSANCE: ");
    if ((cl.date_naissance.annee = test_annee()) == 0) {
        printf("\n Inscription annulée.\n");
        fclose(f);
        sleep(2);
        system("cls");
        menuClient();
    }
    test_mois();
    test_jour(cl.date_naissance.annee, cl.date_naissance.mois);

    printf("\n\t\tSAISIR VOTRE PASSWORD: ");
    scanf("%s", cl.password);

    while(strlen(cl.password) < 5)
     {

        printf("\n\t\t-Mot De Passe invalide, un mot de passe securise doit contenir au moins 6 caracteres!\n\n");
        printf("\t\tSAISIR VOTRE PASSWORD: ");
        scanf("%s", cl.password);

    }

    do{

        printf("\n\t\tSaisir le montant a deposer: ");
        scanf("%f", &cl.montant);
        if(cl.montant <0)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color

            printf("\n\t\tLe montant est invalide");
            sleep(2);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        }
        else if( cl.montant >1000000){

            printf("\n\t\tLe montant est si important, consultez l'agence ");
            sleep(2);
            char c = getche();
            system("cls");
            menuClient();
        }


    }while(cl.montant <0);


    srand(time(NULL)); // Initialise le générateur de nombres aléatoires
    int generateRandom4DigitNumber() {
            return rand() % 9000 + 1000;
    }
    cl.id =generateRandom4DigitNumber();
    if(cl.id <1000 || cl.id >= 10000)
    {
        printf("error ,Reessayez plus tard");
        sleep(3);
        system("cls");
        menuClient();
    }
    else{
        while(checkIfIDExists(cl.id)) {
            srand(time(NULL));
            cl.id =generateRandom4DigitNumber();
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\n\t\tMemorisez votre identifiant pour vous connecter");
    printf("\n\n\t\t___Votre Id est___: %d #", cl.id);
    for(int i=0; i<5; i++)
    {
        printf("#");
        sleep(1);

    }
    char c =getche();
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
    strcpy(cl.state, " Activate");
    Pclient.hashpass = hash_password(cl.password);
    fprintf(f, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %.2f || type_compte : %s || State = %s\n",cl.id,Pclient.hashpass,cl.nom, cl.prenom, cl.CIN, cl.tele, cl.montant, cl.type_Compte, cl.state);

    fclose(f);
    addToAuthfile();
    system("cls");
    printf("\n\t\t************Mr,%s Votre Id est: %d ************************\n", cl.prenom, cl.id);
    menuClient();


}

//Check validation of ID
int checkIfIDExists(int id) {
    FILE *file = fopen(FileLogIn, "rt"); // Ouvre le fichier en mode lecture
    int currentID;
    char line[100]; // Supposition d'une longueur de ligne maximale
    uint64_t hashpass;

    if (file != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            // Utilise sscanf pour extraire l'ID et le mot de passe de chaque ligne
            if (sscanf(line, "%d\t%llu", &currentID, &hashpass) == 2) {
                if (currentID == id) {
                    fclose(file);
                    return true; // ID trouvé
                }
            }
        }
        fclose(file);
    } else {
        printf("Erreur d'ouverture du fichier.\n");
    }

    return false; // ID non trouvé
}



void addToAuthfile()
{
    FILE *p = fopen(FileLogIn, "at");
    if(!p)
    {
        fprintf(stderr, "\n\tSomething went wrong , try again Later\n\n");
        return 1;
    }
    cl.hashpass = hash_password(cl.password);
    fprintf(p, "%d\t%llu\n", cl.id, cl.hashpass);
    fclose(p);
}

// fonction type du banque pour inscription du client

void typeBanque(){
    int type;

        system("cls");
        printf("\n\n\n\n\n\n");
        printf("\t\t   **********************************************************\n");
        printf("\t\t*                                                        \t*\n");
        printf("\t\t*  VEUILLEZ ENTRER UN TYPE DU COMPTE QUE VOUS VOULEZ CREER:\t*\n");
        printf("\t\t*                                                        \t*\n");
        printf("\t\t*          [1]- COMPTE COURANT                           \t*\n");
        printf("\t\t*          [2]- COMPTE CHEQUE                            \t*\n");
        printf("\t\t*          [3]- COMPTE ETUDIANT                          \t*\n");
        printf("\t\t*          [4]- Documentation des types                  \t*\n");
        printf("\t\t*          [0]- retourner                                \t*\n");
        printf("\t\t*                                                        \t*\n");
        printf("\t\t   **********************************************************\n");
        printf("\t\t\tENTRER VOTRE CHOIX : ");
        scanf("%d", &type);
	   switch(type){
	        case 0: system("cls"); menuClient();
                break;
            case 1:strcpy(cl.type_Compte, "COURANT"); inscription();
                break;
            case 2:strcpy(cl.type_Compte, "CHEQUE");inscription();
                break;
            case 3:strcpy(cl.type_Compte, "ETUDIANT");inscription();
                break;
            case 4 : system("cls");ActypeDocumentation();typeBanque();
                break;
            default :
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
                printf("Option invalide");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
                sleep(2);system("cls"); typeBanque();
                break;

	   }
}
void menuClient() {
    int choix;

    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          BIENVENUE SUR LE MENU CLIENT                *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          [1]- S'INSCRIRE                             *\n");
    printf("\t\t*          [2]- SE CONNECTER                           *\n");
    printf("\t\t*          [0]- REVENIR AU MENU PRINCIPAL              *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t********************************************************\n");
    printf("\t\t\tENTRER VOTRE CHOIX : ");
    scanf("%d", &choix);

    switch (choix) {
    case 1:
        system("cls");
        typeBanque();
        break;
    case 2:
        system("cls");login();
        break;
    case 0:
        system("cls");AfficherMenuPrincipale();
        break;
    default :
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
        printf("\n\t\t\t\t\toption invalide ");
        for(int i=0; i<2; i++)
        {
            printf(".");
            sleep(1);
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        system("cls");menuClient();
        break;
    }

}



// interface 0 :choisir est ce que l'utilisateur est un admin ou est un client

void AfficherMenuPrincipale(){

    printf("\n\n\n\n\t\t");printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");printf("\n");
    printf("\t\t");        printf("::                                                                   ::");printf("\n");
    printf("\t\t");        printf("::            *****************************************              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *          WELCOME TO TDIA BANK         *              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *****************************************              ::");printf("\n");
    printf("\t\t");        printf("::                                                                   ::");printf("\n");
    printf("\t\t");        printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");printf("\n");
    printf("\n\n\t\t");  printf("                          << LOADING >>                          ");
                           printf("\n");
                           printf("\n\n");

   int choix;

    //printf("\t\t\t WELCOME TO OUR MENU \n\n");
    printf(" \t\t ETES VOUS UN ADMINISTRATEUR OU UN CLIENT ?\t\n\n");
    printf("\t\t [1]. CLIENT\n");
    printf("\t\t [2]. ADMINISTRATEUR \n\n");
    printf("\t\t ENTRER VOTRE CHOIX : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        system("cls");
        menuClient();
        break;
    case 2:
        system("cls");
        adminMenuDisplay();
         break;
    default:
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
        printf("\n\t\tchoix invalide. Ressayer une autre fois \n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        sleep(2);system("cls"); AfficherMenuPrincipale();
         break;

    }
 }



//interface 1 inerface pour admin pour se connecter ou non

void adminMenuDisplay() {

    int choix ;
    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          BIENVENUE SUR L'INTERFACE ADMINISTRATEUR    *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*          [1]- SE CONNECTER                           *\n");
    printf("\t\t*          [0]- REVENIR AU MENU PRINCIPAL              *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t********************************************************\n");
    printf("\t\t\tENTRER VOTRE CHOIX : ");
    scanf("%d", &choix);

     switch(choix){
         case 1: system("cls");loginAdmin();
         break;
         case 0:system("cls"); AfficherMenuPrincipale();
         break;
         default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf(" \n\t\t\t Ressayer une autre fois \n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
            sleep(2);
            system("cls");
            adminMenuDisplay();
     }

}
// fonction de la conexion d'un administrateur
void loginAdmin(){
     FILE *fa=fopen(Adminfile,"rt");
     Admin admin;
     int rp=0, ide;
     char passwd[50];

    printf("\n\n\n\n\n\n");
    printf("\t\t**************************************************\n");
    printf("\t\t*                Admin Log in                    *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      DONNER VOTRE ID:                          *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*      DONNER VOTRE MOT DE PASSE :               *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t**************************************************\n");

    gotoxy(40, 10); // Set cursor position for ID
    scanf("%d", &ide);

    // Similar for password, adjust the coordinates accordingly
    gotoxy(51, 12);
    read_password(passwd);
    clt.hashpass = hash_password(passwd);
    if (fa == NULL) {
      printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
     while (fscanf(fa, "%d\t%llu", &admin.id,&admin.hashpass)!= EOF) {

        if (admin.id == ide && admin.hashpass == clt.hashpass ) {
            rp=1;
          break;
        }
        }

    // tester la connexion de l'administrateur;
    if ( rp==1){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //Set the green color
        printf("\n\n\n\t\t\t LA CONNEXION EST BIEN FAITE");
        for(int i=0; i<3; i++)
        {
            printf("..");
            sleep(1);
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        system("cls");
        menueAdmin();
    }

    else{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color
        printf("\n\n\n\t\t\t la connexion est echouee ,Veuillez essayer une autre fois");
        for(int i=0; i<3; i++)
        {
            printf(".");
            sleep(1);
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
        system("cls");
        adminMenuDisplay();

     }
 fclose(fa);

}

//fonction d'affichge du menu pour admin
void menueAdmin()
{
     system("cls");
     int  choix;

    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t******************************************************\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*                    MENU ADMIN                      *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [1]: AJOUTER UN NOUVEAU Admin                     *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [2]: LISTER LES COMPTES DES CLIENTS               *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [3]: CONSULTATIONS DES RECLAMATIONS               *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*  [4]: QUITTEZ                                      *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t*                                                    *\n");
    printf("\t\t******************************************************\n");

    printf("\n\t\t\tCHOISIR UNE OPTION: ");

       scanf("%d",&choix);
       system("cls");
       switch(choix){

       case 1 :   AddAdmin();
                  break;
       case 2 :   cheakaccount() ;
                  break;
       case 3 :   Consulter_reclmations();system("cls");menueAdmin();
                  break;
       case 4 :   AfficherMenuPrincipale();//QUITTER
                  break;
       default:
           HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
           SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); //Set the red color for the invalide option prompte
            printf(" \t\n option invalide");sleep(2);system("cls");menueAdmin();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset color
       break;
          }

}

void AddAdmin()
{


    //pass


}

// fonction de lister les comptes bancaires
void cheakaccount(){
        FILE*comptes;
        comptes = fopen(informationcmpt, "rt"); // Ouvre le fichier en mode lecture
        if (comptes == NULL) {
            printf("Erreur lors de l'ouverture du fichier.");
            return 1 ;
        }

        printf("\t\t LES INFORMATIONS DU COMPTES BANCAIRES :\n\n ");
        printf("\t |     ID     |    NOM       |    PRENOM     |  SOLDE DISPONIBLE | Type Compte  | Num-Telephone |    CIN    |   State   |\n");
        printf("\t |------------|--------------|---------------|-------------------|--------------|---------------|-----------|-----------|\n");

    // Lecture du fichier et affichage ligne par ligne
        while (fscanf(comptes, "Id: %d || Password: %llu || Nom : %s || Prénom : %s || CIN : %s || Num-Telephone: %d || Solde: %f || type_compte : %s || State = %s\n", &cl.id, &cl.hashpass, cl.nom, cl.prenom, cl.CIN, &cl.tele, &cl.montant, cl.type_Compte, cl.state) == 9) {
            {
                printf("\t |    %5d   | %-12s | %-13s | %17.2f | %-12s | %-13d | %-9s | %-9s |\n", cl.id, cl.nom, cl.prenom, cl.montant, cl.type_Compte, cl.tele, cl.CIN, cl.state);
            }
        char c;
        printf("\n\t\t [0]- Retourner : ");
        c = getche();

        menueAdmin();


}
}
// fonction affiche les reclmataions des clients

 void Consulter_reclmations(){

  FILE *fr;
  fr=fopen(Reclamation,"rt");

    if (fr==NULL){
    printf("ERREUR D'OUVRIR LE FICHIER RECLMATIONS \n");
    return 1;
  }


    printf("\t\t LES RECLAMATIONS DES CLIENTS :\n\n ");

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fr) != NULL) {
        printf("\t\t %s \n", ligne);

    }

    fclose(fr); // Fermez le fichier après lectur
    char c;
    printf("\nAppuyez sur quelque chose pour continuer\n");
    c = getche();
 }

void asciiART()
{
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t _____ ____ ___    _         ____    _    _   _ _  __\n");
    printf("\t\t\t|_   _|  _ \\_ _|  / \\       | __ )  / \\  | \\ | | |/ /\n");
    printf("\t\t\t  | | | | | | |  / _ \\ _____|  _ \\ / _ \\ |  \\| | ' / \n");
    printf("\t\t\t  | | | |_| | | / ___ \\_____| |_) / ___ \\| |\\  | . \\ \n");
    printf("\t\t\t  |_| |____/___/_/   \\_\\    |____/_/   \\_\\_| \\_|_|\\_\\\n");


    sleep(2);

    printf("\n\n\n\t\t\t\t[");
    for(int i =0; i<3; i++)
    {
        printf("##############");
        sleep(1);
    }
    printf("]");
    system("cls");

}
int main()
{

   asciiART();

   AfficherMenuPrincipale();
   system("pause");

}
