#include <iostream>
#include <string>

void init_grille(char tab[][6])
{
    for(int i=0; i<5; i++)
    {
        for(int j=0 ; j<6; j++)
        {
            tab[i][j] = ' ';
        }
    }
    std::cout<<"\n";
}


void affiche_grille(char tab[][6])
{
    std::cout << "_______________________________" <<std::endl;
    std::cout << "| 1  | 2  | 3  | 4  | 5  | 6  |"<<std::endl;
    std::cout << "| "<<tab[0][0] << "  | " << tab[0][1] << "  | " << tab[0][2] << "  |" << tab[0][3] << "   |" << tab[0][4] << "   |" << tab[0][5] << "   |" << std::endl;
    std::cout << "|____|____|____|____|____|____|" <<std::endl;
    std::cout << "| 7  | 8  | 9  | 10 | 11 | 12 |"<<std::endl;
    std::cout << "| "<<tab[1][0] << "  | " << tab[1][1] << "  | " << tab[1][2] << "  |" << tab[1][3] << "   |" << tab[1][4] << "   |" << tab[1][5] << "   |" << std::endl;
    std::cout << "|____|____|____|____|____|____|" <<std::endl;
    std::cout << "| 13 | 14 | 15 | 16 | 17 | 18 |"<<std::endl;
    std::cout << "| "<<tab[2][0] << "  | " << tab[2][1] << "  | " << tab[2][2] << "  |" << tab[2][3] << "   |" << tab[2][4] << "   |" << tab[2][5] << "   |" << std::endl;
    std::cout << "|____|____|____|____|____|____|" <<std::endl;
    std::cout << "| 19 | 20 | 21 | 22 | 23 | 24 |"<<std::endl;
    std::cout << "| "<<tab[3][0] << "  | " << tab[3][1] << "  | " << tab[3][2] << "  |" << tab[3][3] << "   |" << tab[3][4] << "   |" << tab[3][5] << "   |" << std::endl;
    std::cout << "|____|____|____|____|____|____|" <<std::endl;
    std::cout << "| 25 | 26 | 27 | 28 | 29 | 30 |"<<std::endl;
    std::cout << "| "<<tab[4][0] << "  | " << tab[4][1] << "  | " << tab[4][2] << "  |" << tab[4][3] << "   |" << tab[4][4] << "   |" << tab[4][5] << "   |" << std::endl;
    std::cout << "|____|____|____|____|____|____|" <<std::endl;
}

char forme(int joueur)
{
    if(joueur == 1)
        return 'X';
    return 'O';
}

int changement_joueur ( int joueur)
{
    if(joueur == 1)
        return 2;
    return 1;
}


int deplacementNotAttack(char tab[][6], int xprecedent, int yprecedent, int xnouveau, int ynouveau, char car)
{
    tab[xprecedent][yprecedent] = ' ';
    tab[xnouveau][ynouveau] = car;
    return 1;
}


// return un code genre 963 pour savoir que c'est une attaque puis utiliser ca dans un if pour set la prise d'une atre piece
int deplacementIsAttack(char tab[][6], int xprecedent, int yprecedent, int xnouveau, int ynouveau, char car, char deplacement)
{
    if(deplacement == 's'){
        if(xnouveau +1  <=4 && tab[xnouveau +1][ynouveau] == ' '){
            tab[xprecedent][yprecedent] = ' ';
            tab[xnouveau][ynouveau] = ' ';
            xnouveau ++;
            tab[xnouveau][ynouveau] = car;
            return 963;
        }
    }else if(deplacement == 'z'){
        if(xnouveau - 1 >=0  && tab[xnouveau -1][ynouveau] == ' '){
            tab[xprecedent][yprecedent] = ' ';
            tab[xnouveau][ynouveau] = ' ';
            xnouveau --;
            tab[xnouveau][ynouveau] = car;
            return 963;
        }
    }else if(deplacement == 'd'){
        if(ynouveau + 1 <=5 && tab[xnouveau][ynouveau + 1] == ' '){
            tab[xprecedent][yprecedent] = ' ';
            tab[xnouveau][ynouveau] = ' ';
            ynouveau ++;
            tab[xnouveau][ynouveau] = car;
            return 963;
        }
    }else if(deplacement == 'q'){
        if(ynouveau - 1 >=0 && tab[xnouveau][ynouveau - 1] == ' ') {
            tab[xprecedent][yprecedent] = ' ';
            tab[xnouveau][ynouveau] = ' ';
            ynouveau--;
            tab[xnouveau][ynouveau] = car;
            return 963;
        }
    }
    return 0;
}

int MyDeplacement(char tab[][6], int actuelX, int actuelY, int XDistination, int YDestination, char deplacement, int num_joueur){
    if(tab[XDistination][YDestination] == ' '){
        return deplacementNotAttack(tab,actuelX,actuelY,XDistination,YDestination, forme(num_joueur));
    }else if(tab[XDistination][YDestination] != forme(num_joueur)){
        return deplacementIsAttack(tab,actuelX,actuelY,XDistination,YDestination, forme(num_joueur), deplacement);
    }
    return 0;
}

int mouvementLastLigne(char deplacement,int num_joueur ,char tab[][6], int x, int y)
{
    int result = 0;
    switch (deplacement)
        {
            case 'z':
                result = MyDeplacement(tab,x,y,x-1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;

            case 'q':
                result = MyDeplacement(tab,x,y,x,y-1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'd':
                result = MyDeplacement(tab,x,y,x,y+1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            
            default:
                break;
        }
    return result;
}

int mouvementFirstLigne(char deplacement,int num_joueur ,char tab[][6], int x, int y){
    int result =0 ;
    switch (deplacement)
        {
            case 's':
                result = MyDeplacement(tab,x,y,x+1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;

            case 'q':
                result = MyDeplacement(tab,x,y,x,y-1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'd':
                result = MyDeplacement(tab,x,y,x,y+1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            
            default:
                break;
        }
    return result;
}

int mouvementLeftRow(char deplacement, int num_joueur, char tab[][6], int x, int y){
    int result = 0;
    switch (deplacement)
        {
            case 's':
                result = MyDeplacement(tab,x,y,x+1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;

            case 'z':
                result = MyDeplacement(tab,x,y,x-1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'd':
                result = MyDeplacement(tab,x,y,x,y+1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            
            default:
                break;
        }
    return result;
}

int mouvementRightRow(char deplacement, int num_joueur, char tab[][6], int x, int y){
    int result = 0;
    switch (deplacement)
        {
            case 's':
                result = MyDeplacement(tab,x,y,x+1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;

            case 'z':
                result = MyDeplacement(tab,x,y,x-1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'q':
                result = MyDeplacement(tab,x,y,x,y-1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            
            default:
                break;
        }
    return result;
}

int mouvementMidle(char deplacement, int num_joueur, char tab[][6], int x, int y){
    int result = 0;
    switch (deplacement)
        {
            case 's':
                result = MyDeplacement(tab,x,y,x+1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;

            case 'z':
                result = MyDeplacement(tab,x,y,x-1,y,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'q':
                result = MyDeplacement(tab,x,y,x,y-1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            case 'd':
                result = MyDeplacement(tab,x,y,x,y+1,deplacement,num_joueur);
                affiche_grille(tab);
                return result;
                break;
            
            default:
                break;
        }
    return result;
}



void placement(char car, char tab[][6], int num_joueur, int nombre_tour, int x, int y){
    car = forme(num_joueur);
    tab[x][y] = car;
    affiche_grille(tab);
    nombre_tour ++;
}

int GameFinish(char tab[][6], char car){
    for(int i = 0; i < 5 ;i++){
        for(int j = 0; j < 6; j++){
            if(tab[i][j] != car && tab[i][j] != ' '){
                return 1; //0 ca veut dire pas fini
            }
        }
    }
    return 0; //jeu fini
}

int nbPieceDecremente(int nbpiece){
    return nbpiece --;
}

int checkEnoughtPiece(int num_joueur, int piecejoueurun, int piecejoueurdeux){
    if(num_joueur == 1){
        if(piecejoueurun -1 >=0){
            return piecejoueurun -1;
        }else{
            return -1;
        }
    }else if(num_joueur == 2){
        if(piecejoueurdeux -1 >=0){
            return piecejoueurdeux -1;
        }else{
            return -1;
        }
    }
    return -1;
}

int deletePiece(char tab[][6], int emplacement, int num_joueur){
    char car = forme(num_joueur);
    switch (emplacement)
    {
    case 1:
        if(tab[0][0] != ' ' && tab[0][0] != car){
            tab[0][0] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 2:
        if(tab[0][1] != ' ' && tab[0][1] != car){
            tab[0][1] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 3:
        if(tab[0][2] != ' ' && tab[0][2] != car){
            tab[0][2] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 4:
        if(tab[0][3] != ' ' && tab[0][3] != car){
            tab[0][3] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 5:
        if(tab[0][4] != ' ' && tab[0][4] != car){
            tab[0][4] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 6:
        if(tab[0][5] != ' ' && tab[0][5] != car){
            tab[0][5] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;

    case 7:
        if(tab[1][0] != ' ' && tab[1][0] != car){
            tab[1][0] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 8:
        if(tab[1][1] != ' ' && tab[1][1] != car){
            tab[1][1] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 9:
        if(tab[1][2] != ' ' && tab[1][2] != car){
            tab[1][2] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 10:
        if(tab[1][3] != ' ' && tab[1][3] != car){
            tab[1][3] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 11:
        if(tab[1][4] != ' ' && tab[1][4] != car){
            tab[1][4] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 12:
        if(tab[1][5] != ' ' && tab[1][5] != car){
            tab[1][5] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 13:
        if(tab[2][0] != ' ' && tab[2][0] != car){
            tab[2][0] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 14:
        if(tab[2][1] != ' ' && tab[2][1] != car){
            tab[2][1] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 15:
        if(tab[2][2] != ' ' && tab[2][2] != car){
            tab[2][2] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 16:
        if(tab[2][3] != ' ' && tab[2][3] != car){
            tab[2][3] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 17:
        if(tab[2][4] != ' ' && tab[2][4] != car){
            tab[2][4] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 18:
        if(tab[2][5] != ' ' && tab[2][5] != car){
            tab[2][5] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 19:
        if(tab[3][0] != ' ' && tab[3][0] != car){
            tab[3][0] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 20:
        if(tab[3][1] != ' ' && tab[3][1] != car){
            tab[3][1] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 21:
        if(tab[3][2] != ' ' && tab[3][2] != car){
            tab[3][2] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 22:
        if(tab[3][3] != ' ' && tab[3][3] != car){
            tab[3][3] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 23:
        if(tab[3][4] != ' ' && tab[3][4] != car){
            tab[3][4] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 24:
        if(tab[3][5] != ' ' && tab[3][5] != car){
            tab[3][5] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 25:
        if(tab[4][0] != ' ' && tab[4][0] != car){
            tab[4][0] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 26:
        if(tab[4][1] != ' ' && tab[4][1] != car){
            tab[4][1] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 27:
        if(tab[4][2] != ' ' && tab[4][2] != car){
            tab[4][2] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 28:
        if(tab[4][3] != ' ' && tab[4][3] != car){
            tab[4][3] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 29:
        if(tab[4][4] != ' ' && tab[4][4] != car){
            tab[4][4] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    case 30:
        if(tab[4][5] != ' ' && tab[4][5] != car){
            tab[4][5] = ' ';
            return 1;
        }else{
            return 0;
        }
        break;
    
    default:
        return 0;
        break;
    }
    return 0;
}

int main()
{
    char tab[5][6];
    init_grille(tab);
    affiche_grille(tab);
    int partie{1};
    int position{0};
    char deplacement;
    char car = ' ';
    int num_joueur{1};
    int nombre_tour{0};
    int resDep = 0;
    int nbPieceJoueurUn = 6;
    int nbPieceJoueurDeux = 6;
    int nbPieceReserve = 0;
    int pieceTakeOk = 2;
    int emplacementToDelete =0;
    //int quitte{0};
    while(partie !=0 )
    {
        std::cout << "Nombre piece reserve joueur 1: "<<nbPieceJoueurUn<< "----------- Nombre piece reserve joueur 2: " << nbPieceJoueurDeux <<std::endl;
        std::cout << "Tour numéro : " <<nombre_tour << std::endl;
        std::cout << "Joueur numero : " << num_joueur << " Entrer votre position : ";
        std::cin >> position;
        switch (position)
        {
        // case 0:
        //         std::cout << "Joueur " <<num_joueur <<" a quitté le jeu" << std::endl;
        //         partie = 0;
        //         quitte = 1;
        //         break;
        case 1:
            if(tab[0][0] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,0);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][0] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;

                switch (deplacement)
                {
                case 's':
                    resDep = MyDeplacement(tab,0,0,1,0,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }
                        if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            std::cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+++++++++++++++++++++++++" << std::endl;
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                        //je gere pas l'erreur si le joueur essaye de prendre une mauvaise piece et lui dire que c pas possible
                    }
                    affiche_grille(tab);
                    break;

                case 'd':
                    resDep = MyDeplacement(tab,0,0,0,1,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;
                
                default:
                    break;
                }
            }
            break;

        case 25:
            if(tab[4][0] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,0);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][0] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;

                switch (deplacement)
                {
                case 'z':
                    resDep = MyDeplacement(tab,4,0,3,0,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;

                case 'd':
                    resDep = MyDeplacement(tab,4,0,4,1,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;
                
                default:
                    break;
                }
            }
            break;

        case 6:
            if(tab[0][5] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,5);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][5] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;

                switch (deplacement)
                {
                case 's':
                    resDep = MyDeplacement(tab,0,5,1,5,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;

                case 'q':
                    resDep = MyDeplacement(tab,0,5,0,4,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;
                
                default:
                    break;
                }
            }
            break;
        
        case 30:
            if(tab[4][5] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,5);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][5] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;

                switch (deplacement)
                {
                case 'z':
                    resDep = MyDeplacement(tab,4,5,3,5,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;

                case 'q':
                    resDep = MyDeplacement(tab,4,5,4,4,deplacement,num_joueur);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
                    affiche_grille(tab);
                    break;
                
                default:
                    break;
                }
            }
            break;


        case 2:
            if(tab[0][1] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,1);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][1] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementFirstLigne(deplacement,num_joueur,tab,0,1);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 3:
            if(tab[0][2] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,2);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][2] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementFirstLigne(deplacement,num_joueur,tab,0,2);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 4:
            if(tab[0][3] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,3);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][3] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementFirstLigne(deplacement,num_joueur,tab,0,3);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
         case 5:
            if(tab[0][4] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,0,4);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[0][4] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementFirstLigne(deplacement,num_joueur,tab,0,4);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 26:
            if(tab[4][1] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,1);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][1] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLastLigne(deplacement,num_joueur,tab,4,1);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 27:
            if(tab[4][2] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,2);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][2] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLastLigne(deplacement,num_joueur,tab,4,2);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 28:
            if(tab[4][3] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,3);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][3] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLastLigne(deplacement,num_joueur,tab,4,3);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
         case 29:
            if(tab[4][4] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,4,4);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[4][4] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLastLigne(deplacement,num_joueur,tab,4,4);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        
        case 7:
            if(tab[1][0] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,0);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][0] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLeftRow(deplacement,num_joueur,tab,1,0);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 13:
            if(tab[2][0] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,0);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][0] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLeftRow(deplacement,num_joueur,tab,2,0);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
         case 19:
            if(tab[3][0] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,0);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][0] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementLeftRow(deplacement,num_joueur,tab,3,0);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 12:
            if(tab[1][5] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,5);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][5] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementRightRow(deplacement,num_joueur,tab,1,5);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        case 18:
            if(tab[2][5] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,5);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][5] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementRightRow(deplacement,num_joueur,tab,2,5);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
         case 24:
            if(tab[3][5] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,5);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][5] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementRightRow(deplacement,num_joueur,tab,3,5);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 8:
            if(tab[1][1] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,1);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][1] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,1,1);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        
        case 9:
            if(tab[1][2] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,2);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][2] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,1,2);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 10:
            if(tab[1][3] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,3);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][3] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,1,3);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 11:
            if(tab[1][4] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,1,4);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[1][4] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,1,4);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 14:
            if(tab[2][1] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,1);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][1] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,2,1);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        
        case 15:
            if(tab[2][2] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,2);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][2] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,2,2);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 16:
            if(tab[2][3] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,3);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][3] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,2,3);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 17:
            if(tab[2][4] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,2,4);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[2][4] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,2,4);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 20:
            if(tab[3][1] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,1);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][1] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,3,1);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
        
        case 21:
            if(tab[3][2] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,2);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][2] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,3,2);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 22:
            if(tab[3][3] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,3);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][3] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,3,3);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;

        case 23:
            if(tab[3][4] == ' ')
            {
                nbPieceReserve = checkEnoughtPiece(num_joueur,nbPieceJoueurUn,nbPieceJoueurDeux);
                if(nbPieceReserve >=0){
                placement(car, tab,num_joueur,nombre_tour,3,4);
                nombre_tour ++;
                if(num_joueur == 1){
                    nbPieceJoueurUn = nbPieceReserve;
                }else {
                    nbPieceJoueurDeux = nbPieceReserve;
                }
                num_joueur=changement_joueur(num_joueur);
                }else{
                    std::cout <<"Vous n'avez plus de piece en reserve pour en introduire ! Vous pouvez que deplacer vos pions !" << std::endl;
                }
            }
            else if(tab[3][4] == forme(num_joueur))
            {
                std::cout<< " Vous pouvez deplacer votre pions " << std::endl;
                std::cin >> deplacement;
                resDep = mouvementMidle(deplacement,num_joueur,tab,3,4);
                    if(resDep == 963){
                        if(GameFinish(tab, forme(num_joueur)) != 0 && nombre_tour > 2){
                            std::cout<<"Entrer la piece a prendre sur le plateau : " <<std::endl;
                            std::cin>>emplacementToDelete;
                            pieceTakeOk = deletePiece(tab,emplacementToDelete,num_joueur); 

                        }else if (GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour <= 2){
                            //ici si le joueur n'a plus de piece sur le plateau et que le nb de tour est <=2 il doit piocher un jeton dans sa reserve
                            if(num_joueur == 1){
                                nbPieceJoueurDeux --;
                            }else{
                                nbPieceJoueurUn --;
                            }

                        }if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
                            partie = 0;
                        }

                        if(pieceTakeOk == 1){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                            pieceTakeOk = 2;
                        }else if(partie!=0 && pieceTakeOk == 2){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                    }
            }
            break;
            
        default:
            break;
        }
    // if(nombre_tour == 9)
    //     partie = 0;
        if(partie == 0){
            std::cout << "VICTOIRE DU JOUEUR "<< num_joueur << " C'EST LE JOUEUR AVEC LE SYMBOLE " << forme(num_joueur) << std::endl;
        }
    }

    return 0;
}

