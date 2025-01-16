/*------------------------------------------------------------------------------*/
/* Fichier : TP4Q1_Code_Equipe_C						*/
/* AUTEUR : Ndiaye, Serigne Mbacke, Diallo Mamadou Billo, Dennler Julian	*/
/* DATE : 12/11/2021															*/
/* Description : Programme pour maintenir l'inventaire				*/
/*Nom du projet: EasyStock							*/
/*------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;
const int MAX_JEU = 50;
enum Type_PF { PC, XBOXONE, PS5, SWITCH };
struct Type_jeu{
	string Nom;
	Type_PF Plateforme;
	bool Neuf;
	int Qte;
	double Prix;
};
/* D�claration des fonctions */
int LireFichier(Type_jeu Inventaire[MAX_JEU]);
void AfficherInfoJeux(Type_jeu Inventaire[],int TailleTab);
void AfficherResultatRecherche(Type_jeu Inventaire[],int TailleTab);
int RechercherUnJeu(Type_jeu Inventaire[],int TailleTab); // cette fonction permet de faire une recherche dans le tableau et nous retourne l'indice si on a trouve un jeu 
void SupprimerCopieJeu(Type_jeu Inventaire[],int TailleTab);
int AjouterJeu(Type_jeu Inventaire[],int TailleTab);
Type_PF Lireenrigistrement(int choix);
void AfficherEnregistrement(int val);
void AfficherStructur(Type_jeu Jeu);
void AfficherEntete();
void Quitter(Type_jeu Inventaire[],int TailleTab);



/* D�claration enum*/
int main() 
{
	int TailleTab=0;
	Type_jeu Inventaire[MAX_JEU];	
	 TailleTab= LireFichier(Inventaire);
int Choix;
do{ 
	cout << "------------------------------------------\n";
	cout << "INVENTAIRE DE MA BOUTIQUE PREFEREE \n";
	cout << "------------------------------------------\n";
	cout << "Veuillez s�l�ctionner parmi les choix suivants :\n";
	cout << "1 - Afficher les informations de tous les jeux \n";
	cout << "2 - Rechercher un jeu \n";
	cout << "3 - Supprimer une copie de jeu \n";
	cout << "4 - Ajouter un nouveau jeu \n";
	cout << "5 - Quitter \n";
	cout << "------------------------------------------\n";
	cout << "Quel est votre choix ?";
	cin >> Choix;
	switch (Choix)
	{
	case 1:
		AfficherInfoJeux(Inventaire,TailleTab);
		break;
	case 2:
	AfficherResultatRecherche(Inventaire,TailleTab);break;
	case 3 :
	SupprimerCopieJeu(Inventaire,TailleTab);break;
	case 4 :TailleTab=AjouterJeu(Inventaire,TailleTab);break;
	case 5 : Quitter(Inventaire,TailleTab);break;
	default:
		cout <<"votre choix n'est pas valide "<< endl ;
		break;
	}
}while(Choix!=5);
}
int LireFichier(Type_jeu Inventaire[MAX_JEU])// cette fonction initialise le tableau avec le fichier et nous retourne la taille du tableau 
{
	ifstream FicEntree;
	int TailleTab=0;
	
	setlocale(LC_CTYPE, "fr-FR");

	string Nom;
	int Val_Pf;
	Type_PF Plateforme;
	bool Neuf;
	int Qte;
	double Prix;
	
	FicEntree.open("Arcade.txt");
	if (!FicEntree.fail())
	{
		while (!FicEntree.eof())
		{
			FicEntree >> Nom;
			Inventaire[TailleTab].Nom=Nom;
			FicEntree >> Val_Pf;
			Inventaire[TailleTab].Plateforme=Lireenrigistrement( Val_Pf); // appel de la fonction Lireenrigistrement et affecttion de la valeur a plateforme 
			FicEntree >> Neuf;
			if (Neuf)
			{
				Inventaire[TailleTab].Neuf=true;
			}
			else 
			{
			Inventaire[TailleTab].Neuf=false;
			}
			FicEntree >> Qte;
			Inventaire[TailleTab].Qte=Qte; //conversion de la chaine en entier 
			FicEntree >> Prix;
			Inventaire[TailleTab].Prix=Prix;//conversion de la chaine en double
			
			TailleTab++;
		}
		 FicEntree.close(); 
		
	}
	else 
	{
		cout << " echec de l'ouverture du fichier " << endl;
	}
	return TailleTab;
}
void AfficherInfoJeux(Type_jeu Inventaire[],int TailleTab)  // cette fonction permet d'afficher le tableau de structure
{
	int j;
	if (TailleTab!=0)	
	{
		AfficherEntete();
		for (j=0;j<TailleTab;j++)
		{
			AfficherStructur(Inventaire[j]); // affiche du tableau de structure jeu a l'aide de la fonction AfficherStructure
		}
	}
}
void AfficherResultatRecherche(Type_jeu Inventaire[MAX_JEU],int TailleTab) //Cette fonction permet d'afficher la strcuture trouve apres une recherche
{
	int Indice;
	Indice= RechercherUnJeu(Inventaire, TailleTab); //initialisation de l'indice la valeur retourner par la fonction Rechercher un jeu 
	if(Indice!=0){
		AfficherEntete();
		AfficherStructur(Inventaire[Indice]);// appel de la fonction AfficherStructure pour afficher le jeu trouve
	}
	else{
		cout << " ce Jeu n'existe pas ";
	}
}
void SupprimerCopieJeu(Type_jeu Inventaire[MAX_JEU],int TailleTab) // cette fonction permet de supprimer uncopie de jeu a partir de l'indice retourner par la fonction RechercherUnJeu
{
	int Indice;
	Indice= RechercherUnJeu(Inventaire, TailleTab);//initialisation de l'indice la valeur retourner par la fonction Rechercher un jeu
	if(Indice!=0) // appel de la fonction et verification de l'existance du jeu 
	{
		if (Inventaire[Indice].Qte >0)
		{
			Inventaire[Indice].Qte =Inventaire[Indice].Qte-1;
			AfficherEntete(); // appel de la fonction pour afficher l'entet 
			AfficherStructur(Inventaire[Indice]); // appel de la fonction AfficherStructure apres la suppression d'un copie 
			cout << setw(5)<<"↓↓↓ COPIE SUPRIMER ↓↓↓"<< endl;  
		}
		else
		{
			cout << "Il n'y a plus de copies de ce jeu "<< endl;
		}
	}else{
		cout << " Jeu Introuvable ";
	}
}
int AjouterJeu(Type_jeu Inventaire[],int Taille_Tab)  // cette fonction permet d'ajouter un jeu au tableau et retourne la nouvelle taille du tableau 
{
	Taille_Tab=Taille_Tab+1;
	bool Neuf;
	char Reponse;
	double Prix;
	int NbCopies;
	string Nom_Du_Jeu;
	int choix;
	Type_PF plateforme;
	cout << " Quel est le nom du jeu (en majuscule sans espace )? ";
	cin >> Nom_Du_Jeu;
	Inventaire[Taille_Tab-1].Nom=Nom_Du_Jeu;
	cout << " Quelle est la plateforme (0:PC, 1:Xbox One, 2:ps5, 3:Switch )? ";
	cin >> choix;
    Inventaire[Taille_Tab-1].Plateforme=Lireenrigistrement(choix);
	cout << " S'agit-il d'un jeu neuf(o/n)? ";
	cin >> Reponse;
	plateforme=Lireenrigistrement(choix);
	Reponse = toupper(Reponse);
	if (Reponse == 'O')	{
		Neuf = true;
	}
	else{
		Neuf = false;
	}
	Inventaire[Taille_Tab-1].Neuf=Neuf;
	cout << " Combien de copies ? ";
	cin>> NbCopies;
	Inventaire[Taille_Tab-1].Qte=NbCopies;
	cout << " Quel est le Prix? ";
	cin>> Prix;
	Inventaire[Taille_Tab-1].Prix=Prix;
	cout << " ↓↓↓ JEU AJOUTE ↓↓↓"<< endl;
return Taille_Tab;
}
Type_PF Lireenrigistrement(int choix ) // cette fonction permet de lire un enregistrement a l'aide d'un entier
{Type_PF plateforme;
switch (choix)
	{
		case 0:plateforme= PC;break;
		case 1:plateforme=XBOXONE;break;
		case 2:plateforme=PS5;break;
		case 3:plateforme=SWITCH;break;
		default:cout << "votre choix n'est pas valide "<< endl;break;
	}
	return plateforme;
}
void AfficherEnregistrement(int val)// cette fonction permet d'afficher un enregistrement 
{		switch(val)
		{
					case PC:
					cout << setw(20)<< "PC"; break;
					case XBOXONE:
					cout << setw(20)<< "XBOXONE"; break;
					case PS5:
					cout << setw(20)<< "PS5"; break;
					case SWITCH:
					cout << setw(20)<< "SWITCH"; break;
		}

}
int RechercherUnJeu(Type_jeu Inventaire[MAX_JEU],int TailleTab) // cette fonction permet de rechercher un jeu dans l'inventaire et return l'indice ou  le jeu a ete  trouve
{
	bool trouvee = false,Neuf;
	char Reponse;
	int Indice=0;
	string Nom_Du_Jeu;
	int choix;
	Type_PF plateforme;
	cout << " Quel est le nom du jeu (en majuscule sans espace )? ";
	cin>> Nom_Du_Jeu;
	cout << " Quelle est la plateforme (0:PC, 1:Xbox One, 2:ps5, 3:Switch )? ";
	cin >> choix;
	cout << " S'agit-il d'un jeu neuf(o/n)? ";
	cin >> Reponse;
	plateforme=Lireenrigistrement(choix);
	Reponse = toupper(Reponse);
	if (Reponse == 'O')	{
		Neuf = true;
	}
	else{
		Neuf = false;
	}
	while (!trouvee && Indice<TailleTab)
	{
		if(Inventaire[Indice].Nom==Nom_Du_Jeu && Inventaire[Indice].Plateforme==plateforme&& Inventaire[Indice].Neuf==Neuf)
		{
			trouvee=true;
		}
		else{
			Indice++;
		}
	}
	if(trouvee)
	{
		return Indice; // retourner l'indice si le jeu a ete trouvee
	}
	else {
		return NULL; // retourner 0 si le jeu n'est pas trouve 
	}
}
void AfficherEntete() // cette fonction permet d'afficher l'entete
{cout << setw(20)<< "NOM"<< setw(20)<<"PLATEFORME"<< setw(15)<<"ETAT"<< setw(15)<<" NB COPIES"<< setw(15)<<"PRIX" << endl;
cout << setw(20)<< "---"<< setw(20)<<"----------"<< setw(15)<<"----"<< setw(15)<<"---------"<< setw(15)<<"----" << endl;
}
void Quitter(Type_jeu Inventaire[MAX_JEU],int TailleTab)  // cette fonction permet d'enregistrer le tableau dans le fichier 
{
ofstream FicSortie;
int i=0;

FicSortie.open("Arcade.txt");
	if (!FicSortie.fail())
	{
		while (i<TailleTab)
		{
			FicSortie << Inventaire[i].Nom;
			FicSortie<< "\t";
			FicSortie << Inventaire[i].Plateforme ;// appel de la fonction Lireenrigistrement et affecttion de la valeur a plateforme 
			FicSortie<< "\t";
			FicSortie <<Inventaire[i].Neuf;
			FicSortie<< "\t";
			FicSortie <<Inventaire[i].Qte;//conversion de la chaine en entier 
			FicSortie<< "\t";
			FicSortie <<Inventaire[i].Prix << endl;//conversion de la chaine en double
			
			i++;
		}
		 FicSortie.close(); 
		
	}
	else 
	{
		cout << " echec de l'ouverture du fichier " << endl;
	}
	cout << "↓↓↓ FICHIER ENREGISTRER ↓↓↓";
}
void AfficherStructur(Type_jeu Jeu) //cette fpnction permet d'afficher le structure jeu 
{
	cout << setw(21)<< Jeu.Nom;
			AfficherEnregistrement(Jeu.Plateforme);
			if (Jeu.Neuf)
			{
				cout << setw(15)<< " Neuf";
			}
			else 
			{
				cout << setw(15)<< "USAGE";
			}
			cout << setw(15)<< Jeu.Qte;
			cout << setw(15)<< Jeu.Prix << "$"<< endl;


}
