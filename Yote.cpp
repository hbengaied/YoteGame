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

int InsertPieceIA(char tab[][6], int numero_joueur){
    for(int i = 0;i<5;i++){
        for(int j = 0; j<6;j++){
            if(tab[i][j] == forme(numero_joueur))
                return 1;
        }
    }
    return 0;
}

int InsertSafe(char tab[][6], int numero_joueur){
    for(int i = 0; i <5 ;i++){
            for(int j = 0; j<6;j++){
                if(tab[i][j] == ' '){
                    //si la place est libre voir si on peut inserer
                    if(
                        (i - 1 >=0 && (tab[i-1][j] == ' ' || tab[i -1][j] == forme(numero_joueur))) &&
                        (i - 2 >=0 && (tab[i-2][j] == ' ' || tab[i -2][j] == forme(numero_joueur))) &&
                        (i + 1 >=0 && (tab[i+1][j] == ' ' || tab[i +1][j] == forme(numero_joueur))) &&
                        (i + 2 >=0 && (tab[i+2][j] == ' ' || tab[i +2][j] == forme(numero_joueur))) && 
                        (j - 1 >=0 && (tab[i][j-1] == ' ' || tab[i][j-1] == forme(numero_joueur))) &&
                        (j - 2 >=0 && (tab[i][j-2] == ' ' || tab[i][j-2] == forme(numero_joueur))) &&
                        (j + 1 >=0 && (tab[i][j+1] == ' ' || tab[i][j+1] == forme(numero_joueur))) &&
                        (j + 2 >=0 && (tab[i][j+2] == ' ' || tab[i][j+2] == forme(numero_joueur)))
                        ){
                            tab[i][j] = forme(numero_joueur);
                            return 1;
                        }
                }
            }
        }
    return 0;
}


//peut etre pcq c'est <0 donc marche pas 
// int NoPieceAround(char tab[][6], int x, int y, int numero_joueur){
//     if(
//         (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
//         (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
//         (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
//         (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
//     ){
//         return 1;
//     }
//     return 0;
// }

int NoPieceAround(char tab[][6], int x, int y, int numero_joueur){
    if(x == 0 && y ==0){
        if(
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x+1][y+1] == ' ' || tab[x+1][y+1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x == 0 && y ==5){
        if(
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x+1][y-1] == ' ' || tab[x+1][y+1] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x == 4 && y==0){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x-1][y+1] == ' ' || tab[x+1][y+1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x==4 && y==5){
        if(
            (tab[x-1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x-1][y-1] == ' ' || tab[x+1][y+1] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(
        (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
        (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
        (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
        (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
    ){
        return 1;
    }else if(x>0 && y==0){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x>0 && y==5){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x==0 && y>0){
        if(
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x==4 && y>0){
        if(
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur)) &&
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur))
        ){
            return 1;
        }
    }

    return 0;
}

int NoPieceAroundMove(char tab[][6], int x, int y, int numero_joueur){
    if(x == 0 && y ==0){
        if(
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x == 0 && y ==5){
        if(
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x == 4 && y==0){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(x==4 && y==5){
        if(
            (tab[x-1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y+1] == forme(numero_joueur))
            ){
                return 1;
            }
    }else if(
        (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
        (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
        (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
        (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
    ){
        return 1;
    }else if(x>0 && y==0){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x>0 && y==5){
        if(
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur)) &&
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x==0 && y>0){
        if(
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur)) &&
            (tab[x+1][y] == ' ' || tab[x+1][y] == forme(numero_joueur))
        ){
            return 1;
        }
    }else if(x==4 && y>0){
        if(
            (tab[x][y-1] == ' ' || tab[x][y-1] == forme(numero_joueur)) &&
            (tab[x][y+1] == ' ' || tab[x][y+1] == forme(numero_joueur)) &&
            (tab[x-1][y] == ' ' || tab[x-1][y] == forme(numero_joueur))
        ){
            return 1;
        }
    }

    return 0;
}

int AttackSafe(char tab[][6], int numero_joueur){
    for(int i = 0; i<5; i++){
        for(int j =0;j<6;j++){
            if(tab[i][j] == forme(numero_joueur)){
                if(i+1 <=4 && tab[i+1][j] == forme(changement_joueur(numero_joueur))){
                    if(i+2<=4 && tab[i+2][j]==' '){
                        tab[i+1][j] =' ';
                        if(NoPieceAround(tab,i+2,j,numero_joueur) == 1){
                            tab[i+2][j] =forme(numero_joueur);
                            tab[i][j] = ' ';
                            std::cout<<"Condition 1"<<std::endl;
                            return 1;
                        }else{
                            tab[i+1][j]= forme(changement_joueur(numero_joueur));
                        }
                    }
                }else if(i-1 >=0 && tab[i-1][j] == forme(changement_joueur(numero_joueur))){
                    if(i-2>=0 && tab[i-2][j]==' '){
                        tab[i-1][j] =' ';
                        if(NoPieceAround(tab,i-2,j,numero_joueur) == 1){
                            tab[i-2][j] =forme(numero_joueur);
                            tab[i][j] = ' ';
                            std::cout<<"Condition 4"<<std::endl;
                            return 1;
                        }else{
                            tab[i-1][j]= forme(changement_joueur(numero_joueur));
                        }
                    }
                }else if(j+1 <=5 && tab[i][j+1] == forme(changement_joueur(numero_joueur))){
                    if(j+2<=5 && tab[i][j+2]==' '){
                        tab[i][j+1] =' ';
                        if(NoPieceAround(tab,i,j+2,numero_joueur) == 1){
                            tab[i][j+2] =forme(numero_joueur);
                            tab[i][j] = ' ';
                            std::cout<<"Condition 3"<<std::endl;
                            return 1;
                        }else{
                            tab[i][j+1]= forme(changement_joueur(numero_joueur));
                        }
                    }
                }else if(j-1 >=0 && tab[i][j-1] == forme(changement_joueur(numero_joueur))){
                    if(j-2>=0 && tab[i][j-2]==' '){
                        tab[i][j-1] =' ';
                        if(NoPieceAround(tab,i,j-2,numero_joueur) == 1){
                            tab[i][j-2] =forme(numero_joueur);
                            tab[i][j] = ' ';
                            std::cout<<"Condition 4"<<std::endl;
                            return 1;
                        }else{
                            tab[i][j-1]= forme(changement_joueur(numero_joueur));
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int AttackNotSafe(char tab[][6], int numero_joueur){
    for(int i = 0; i<5; i++){
        for(int j =0;j<6;j++){
            if(tab[i][j] == forme(numero_joueur)){
                if(i+1 <=4 && tab[i+1][j] == forme(changement_joueur(numero_joueur))){
                    std::cout<<"Je suis dans la fct attacktest 1"<<std::endl;
                    if(i+2<=4 && tab[i+2][j]==' '){
                        tab[i+2][j] =forme(numero_joueur);
                        tab[i][j] = ' ';
                        tab[i-1][j]= ' ';
                        return 1;
                    }
                }else if(i-1 >=0 && tab[i-1][j] == forme(changement_joueur(numero_joueur))){
                    std::cout<<"Je suis dans la fct attacktest 2"<<std::endl;
                    if(i-2>=0 && tab[i-2][j]==' '){
                        tab[i-2][j] =forme(numero_joueur);
                        tab[i][j] = ' ';
                        tab[i-1][j]= ' ';
                        return 1;
                    }
                }else if(j+1 <=5 && tab[i][j+1] == forme(changement_joueur(numero_joueur))){
                    std::cout<<"Je suis dans la fct attacktest 3"<<std::endl;
                    if(j+2<=5 && tab[i][j+2]==' '){
                        tab[i][j+2] =forme(numero_joueur);
                        tab[i][j] = ' ';
                        tab[i][j+1]= ' ';
                        return 1;
                    }
                }else if(j-1 >=0 && tab[i][j-1] == forme(changement_joueur(numero_joueur))){
                    std::cout<<"Je suis dans la fct attacktest 4"<<std::endl;
                    if(j-2>=0 && tab[i][j-2]==' '){
                        tab[i][j-2] =forme(numero_joueur);
                        tab[i][j] = ' ';
                        tab[i][j-1]= ' ';
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


int PieceDeleteIA(char tab[][6], int numero_joueur){
    for(int i = 0; i <=4;i++){
        for(int j = 0; j <=5;j++){
            if(tab[i][j] != ' ' && tab[i][j] != forme(numero_joueur)){
                tab[i][j] = ' ';
                return 1;
            }
        }
    }
    return 0;
}


// int MovePieceForNotBeingEat(char tab[][6], int numero_joueur){
//     for(int i = 0;i<5;i++){
//         for(int j = 0; j<6;j++){
//             if(tab[i][j] == forme(numero_joueur)){
//                 if(i-1 >=0){
//                     if(tab[i-1][j] == ' '){
//                         if(NoPieceAroundMove(tab,i-1,j, numero_joueur) == 1){
//                             tab[i-1][j] = forme(numero_joueur);
//                             tab[i][j] = ' ';
//                             return 1;
//                         }
//                     }
//                 }else if(i+1 <=4){
//                     if(tab[i+1][j] == ' '){
//                         if(NoPieceAroundMove(tab,i+1,j, numero_joueur) == 1){
//                             tab[i+1][j] = forme(numero_joueur);
//                             tab[i][j] = ' ';
//                             return 1;
//                         }
//                     }
//                 }else if(j-1 >=0){
//                     if(tab[i][j-1] == ' '){
//                         if(NoPieceAroundMove(tab,i,j-1, numero_joueur) == 1){
//                             tab[i][j-1] = forme(numero_joueur);
//                             tab[i][j-1] = ' ';
//                             return 1;
//                         }
//                     }
//                 }else if(j+1 <=5){
//                     if(tab[i][j+1] == ' '){
//                         if(NoPieceAroundMove(tab,i,j+1, numero_joueur) == 1){
//                             tab[i][j+1] = forme(numero_joueur);
//                             tab[i][j+1] = ' ';
//                             return 1;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return 0;
// }

int MovePieceForNotBeingEat(char tab[][6], int numero_joueur){
    for(int i = 0;i<5;i++){
        for(int j = 0; j<6;j++){
            if(tab[i][j] == forme(numero_joueur)){
                if(i-1 >=0){
                    if(tab[i-1][j] != ' ' && tab[i-1][j] != forme(numero_joueur)){
                        if(NoPieceAroundMove(tab,i+1,j, numero_joueur) == 1){
                            tab[i+1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i,j-1, numero_joueur) == 1){
                            tab[i][j-1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i,j+1, numero_joueur) == 1){
                            tab[i][j+1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }
                    }
                }else if(i+1 <=4){
                    if(tab[i+1][j] != ' ' && tab[i+1][j] != forme(numero_joueur)){
                        if(NoPieceAroundMove(tab,i-1,j, numero_joueur) == 1){
                            tab[i-1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i,j-1, numero_joueur) == 1){
                            tab[i][j-1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i,j+1, numero_joueur) == 1){
                            tab[i][j+1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }
                    }
                }else if(j-1 >=0){
                    if(tab[i][j-1] != ' ' && tab[i][j-1] != forme(numero_joueur)){
                        if(NoPieceAroundMove(tab,i,j+1, numero_joueur) == 1){
                            tab[i][j+1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i+1,j, numero_joueur) == 1){
                            tab[i+1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i-1,j, numero_joueur) == 1){
                            tab[i-1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }
                    }
                }else if(j+1 <=5){
                    if(tab[i][j+1] != ' ' && tab[i][j+1] != forme(numero_joueur)){
                        if(NoPieceAroundMove(tab,i,j-1, numero_joueur) == 1){
                            tab[i][j-1] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i+1,j, numero_joueur) == 1){
                            tab[i+1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }else if(NoPieceAroundMove(tab,i-1,j, numero_joueur) == 1){
                            tab[i-1][j] = forme(numero_joueur);
                            tab[i][j] = ' ';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}


int MovePieceBcNotOtherSolution(char tab[][6], int numero_joueur){
    for(int i = 0; i<5;i++){
        for(int j = 0; j<6;j++){
            if(tab[i][j] == forme(numero_joueur)){
                if(i+1 <=4 && tab[i+1][j] == ' '){
                    tab[i+1][j] = forme(numero_joueur);
                    tab[i][j] = ' ';
                    return 1;
                }else if(j+1 <=5 && tab[i][j+1] == ' '){
                    tab[i][j+1] = forme(numero_joueur);
                    tab[i][j] = ' ';
                    return 1;
                }else if(i-1 >=0 && tab[i-1][j] == ' '){
                    tab[i-1][j] = forme(numero_joueur);
                    tab[i][j] = ' ';
                    return 1;
                }else if(j-1 >=0 && tab[i][j-1] == ' '){
                    tab[i][j-1] = forme(numero_joueur);
                    tab[i][j] = ' ';
                    return 1;
                }
            }
        }
    }
    return 0;
}

int  TurnIA(char tab[][6], int numero_joueur, int nombre_piece_IA, int nombre_piece_joueur){
    int SafeAttack;
    int SafeInsert;
    int haveToInsertIA = InsertPieceIA(tab,numero_joueur);
    int deletepiece;
    int SafeMove;
    //int NoChoiceMove;
    //si pas de piece sur le plateau il faut inserer
    if(haveToInsertIA == 0){
        //verif que la ou il insert y a pas de piece adverse à 2 case

        InsertSafe(tab,numero_joueur);
        return nombre_piece_IA -1 + 10000;
    }else{
        SafeAttack = AttackSafe(tab,numero_joueur);
        if(SafeAttack == 1){
            std::cout << "La valeur de SafeAttack mais je rentre dans =1 =" << SafeAttack<<std::endl;
            deletepiece = PieceDeleteIA(tab,numero_joueur);
            if(deletepiece == 0){
                return nombre_piece_joueur -1;
            }
        }else if(SafeAttack == 0){
            std::cout << "La valeur de SafeAttack dans le if ==0  =" << SafeAttack<<std::endl;
            SafeInsert=InsertSafe(tab,numero_joueur);
            if(SafeInsert == 1){
                //changement tour
                std::cout<<"IA A INSERER UNE PIECE SUR LE PLATEAU"<<std::endl;
                return nombre_piece_IA -1 + 10000;
            }else{
                //sinon faire un mouvement pour eviter de ce faire bouffer
                SafeMove = MovePieceForNotBeingEat(tab,numero_joueur);
                if(SafeMove == 1 ){
                    return 100;
                }else if(AttackNotSafe(tab,numero_joueur) ==1){
                    return 1;
                }else if(MovePieceBcNotOtherSolution(tab,numero_joueur) == 1){
                    return 100;
                }
            }
        }
    }
    // il est rentre dans aucun if else
    return 999;
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
    int ResultIA = 0;
    int tourIA =0;
    //int quitte{0};
    while(partie !=0 )
    {
        for(int i =0; i<10;i++){
            std::cout<< " "<<std::endl;
        }
        std::cout << "Nombre piece reserve joueur 1: "<<nbPieceJoueurUn<< "----------- Nombre piece reserve joueur 2: " << nbPieceJoueurDeux <<std::endl;
        std::cout << "Tour numéro : " <<nombre_tour << std::endl;

        if(num_joueur ==1){
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                                std::cout<<"JE RENTRE ICI CHANGEMENT JOUEUR CASE 15"<<std::endl;
                                nombre_tour ++;
                                num_joueur = changement_joueur(num_joueur);
                            }
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
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
                        }else if(resDep == 1 && partie !=0 ){
                            nombre_tour ++;
                            num_joueur = changement_joueur(num_joueur);
                        }
                }
                break;
                
            default:
                break;
            }
        }else if(num_joueur == 2){
            tourIA++;
            std::cout<<"+++++++++++++++++++++++"<<tourIA<<"+++++++++++++++++++++++++++++++"<<std::endl;
            ResultIA = TurnIA(tab,num_joueur,nbPieceJoueurDeux,nbPieceJoueurUn);
            if(ResultIA>=10000){
                nbPieceJoueurDeux = ResultIA - 10000;
                affiche_grille(tab);
                nombre_tour ++;
                num_joueur = changement_joueur(num_joueur);
            }else if(ResultIA !=100 && ResultIA != 999){
                nbPieceJoueurUn = ResultIA;
                affiche_grille(tab);
                nombre_tour ++;
                num_joueur = changement_joueur(num_joueur);
            }else{
                affiche_grille(tab);
                num_joueur = changement_joueur(num_joueur);
            }
        }
        if(GameFinish(tab, forme(num_joueur)) == 0 && nombre_tour > 2){
            std::cout <<"DSFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"<<std::endl;
            partie = 0;
        }

        if(partie == 0){
            std::cout << "VICTOIRE DU JOUEUR "<< num_joueur << " C'EST LE JOUEUR AVEC LE SYMBOLE " << forme(num_joueur) << std::endl;
        }
    }

    return 0;
}

