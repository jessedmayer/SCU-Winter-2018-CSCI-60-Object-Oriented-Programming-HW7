//each ant need to know whats next to it
//ant object of array, can check position in array
//array of organism objects
//multidimensional array
//gives two levels of de-referencing
//3 questions movement( x or y axis)
//if you want to move left or right need to change column
//move function checks if direction is open
//de-referencing of array at location
//move can be member function of organism or not
//board can be a class which is private member of organism
//if board is class ant, doodlebug have to be friend to board class
//board can just be multidimensional array of pointers
//dynamics array stores pointers to objects
//don't name your ants
//vectors cause them to shift if one gets deleted
//move function native to each organism
//no names
//each turn go through board if nothing there next, if ant check ant stuff
//when ant dies need to clear memory and set position to null

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

int random(int min, int max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

class Organism{
public:
    Organism(){;}
    Organism(int t);                      //sets organism's type
    //virtual void move();
    //virtual void breed();
    int Type;
    int getType(){return Type;}
    int X;
    int Y;
    int time_step=0;
    int last_eaten=0;
};

Organism::Organism(int t) {
    Type=t;
}

class Ant : public Organism{            //represented by 'O' in ANSCII 079
public:
    Ant();
    //void move();
    //void breed();

};

Ant::Ant() : Organism(1){}

class Doodlebug : public Organism{      //represented by 'X' in ANSCII 088
public:
    Doodlebug();
    //void move();
    //void breed();
    //void starve();
};

Doodlebug::Doodlebug() : Organism(2){}

void initialize(Organism ***array2d){               //initializes 2d board and spawns first set of ants and doodlebugs
    static bool first = true;
    if (first) {
        // Create 2D array of pointers:
        Organism ***array2d = new Organism **[20];
        for (int i = 0; i < 20; ++i) {
            array2d[i] = new Organism *[20];
        }

        for (int i = 0; i < 20; ++i) {              // Null out the pointers contained in the array
            for (int j = 0; j < 20; ++j) {
                array2d[i][j] = nullptr;
            }
        }
        int i=0;
        while(i<100){                               //spawns ants
            int x=random(0,20);
            int y=random(0,20);
            if(array2d[y][x]==nullptr) {
                array2d[y][x] = new Ant();
                i++;
            }
        }
        while(i<5){                                 //spawns doodlebugs
            int x=random(0,20);
            int y=random(0,20);
            if(array2d[y][x]==nullptr) {
                array2d[y][x] = new Doodlebug();
                i++;
            }
        }
        first = false;
    }
}

void print(Organism ***array2d){                    //prints out the 2d board
    for (int i=0; i<=19; i++){
        for ( int j=0; j<=19; j++){
            if(array2d[i][j]==nullptr){
                cout<< ".";
            }
            else if(array2d[i][j]->getType()==1){
                cout<< "O";
            }
            else if(array2d[i][j]->getType()==2) {
                cout<< "X";
            }
        }
        cout<<endl;
    }
}

void antsMove(Organism ***array2d) {
    for (int i = 0; i <= 19; i++) {                      //i=x   j=y
        for (int j = 0; j <= 19; j++) {
            if (array2d[i][j]->getType() == 1) {
                int step = random(1, 4);

                if (step == 1) {
                    if (i + 1 <= 19 && array2d[j][i + 1] == nullptr) {
                        *array2d[j][i + 1] = *array2d[j][i];
                        array2d[j][i] = nullptr;
                    }
                }
                if (step == 2) {
                    if (i - 1 >= 0 && array2d[j][i - 1] == nullptr) {
                        *array2d[j][i - 1] = *array2d[j][i];
                        array2d[j][i] = nullptr;
                    }
                }
                if (step == 3) {
                    if (j + 1 <= 19 && array2d[j + 1][i] == nullptr) {
                        *array2d[j + 1][i] = *array2d[j][i];
                        array2d[j][i] = nullptr;
                    }
                }
                if (step == 4) {
                    if (j - 1 >= 0 && array2d[j - 1][i] == nullptr) {
                        *array2d[j - 1][i] = *array2d[j][i];
                        array2d[j][i] = nullptr;
                    }
                }
            }
        }
    }
}

void doodlebugsMove(Organism ***array2d) {
    for (int i = 0; i <= 19; i++) {                      //i=x   j=y
        for (int j = 0; j <= 19; j++) {
            if (array2d[i][j]->getType() == 2) {
                if(i+1<=19&&array2d[j][i + 1]->getType() == 1){
                    array2d[j][i]->last_eaten=0;
                    *array2d[j][i + 1] = *array2d[j][i];
                    array2d[j][i] = nullptr;
                }
                else if(i-1>=0&&array2d[j][i - 1]->getType() == 1){
                    array2d[j][i]->last_eaten=0;
                    *array2d[j][i - 1] = *array2d[j][i];
                    array2d[j][i] = nullptr;
                }
                else if(j+1<=19&&array2d[j + 1][i]->getType() == 1){
                    array2d[j][i]->last_eaten=0;
                    *array2d[j + 1][i] = *array2d[j][i];
                    array2d[j][i] = nullptr;
                }
                else if(j-1>=0&&array2d[j - 1][i]->getType() == 1){
                    array2d[j][i]->last_eaten=0;
                    *array2d[j - 1][i] = *array2d[j][i];
                    array2d[j][i] = nullptr;
                }
                else{
                    int step = random(1, 4);

                    if (step == 1) {
                        if (i + 1 <= 19 && array2d[j][i + 1] == nullptr) {
                            array2d[j][i]->last_eaten++;
                            *array2d[j][i + 1] = *array2d[j][i];
                            array2d[j][i] = nullptr;
                        }
                    }
                    if (step == 2) {
                        if (i - 1 >= 0 && array2d[j][i - 1] == nullptr) {
                            array2d[j][i]->last_eaten++;
                            *array2d[j][i - 1] = *array2d[j][i];
                            array2d[j][i] = nullptr;
                        }
                    }
                    if (step == 3) {
                        if (j + 1 <= 19 && array2d[j + 1][i] == nullptr) {
                            array2d[j][i]->last_eaten++;
                            *array2d[j + 1][i] = *array2d[j][i];
                            array2d[j][i] = nullptr;
                        }
                    }
                    if (step == 4) {
                        if (j - 1 >= 0 && array2d[j - 1][i] == nullptr) {
                            array2d[j][i]->last_eaten++;
                            *array2d[j - 1][i] = *array2d[j][i];
                            array2d[j][i] = nullptr;
                        }
                    }
                }
            }
        }
    }
}

void antsBreed(Organism ***array2d) {
    for (int i = 0; i <= 19; i++) {                      //i=x   j=y
        for (int j = 0; j <= 19; j++) {
            if (array2d[i][j]->getType() == 1) {
                array2d[j][i]->time_step++;
                if (array2d[j][i]->time_step == 3) {
                    if (i + 1 <= 19 && array2d[j][i + 1] == nullptr) {
                        array2d[j][i + 1] = new Ant();
                    } else if (i - 1 >= 0 && array2d[j][i - 1] == nullptr) {
                        array2d[j][i - 1] = new Ant();
                    } else if (j + 1 <= 19 && array2d[j + 1][i] == nullptr) {
                        array2d[j + 1][i] = new Ant();
                    } else if (j - 1 >= 0 && array2d[j - 1][i] == nullptr) {
                        array2d[j - 1][i] = new Ant();
                    }
                }
            }
        }
    }
}

void doodlebugBreed(Organism ***array2d) {
    for (int i = 0; i <= 19; i++) {                      //i=x   j=y
        for (int j = 0; j <= 19; j++) {
            if (array2d[i][j]->getType() == 2) {
                array2d[j][i]->time_step++;
                if (array2d[j][i]->time_step == 8) {
                    if (i + 1 <= 19 && array2d[j][i + 1] == nullptr) {
                        array2d[j][i + 1] = new Doodlebug();
                    } else if (i - 1 >= 0 && array2d[j][i - 1] == nullptr) {
                        array2d[j][i - 1] = new Doodlebug();
                    } else if (j + 1 <= 19 && array2d[j + 1][i] == nullptr) {
                        array2d[j + 1][i] = new Doodlebug();
                    } else if (j - 1 >= 0 && array2d[j - 1][i] == nullptr) {
                        array2d[j - 1][i] = new Doodlebug();
                    }
                }
            }
        }
    }
}

void doodlebugStarve(Organism ***array2d) {
    for (int i = 0; i <= 19; i++) {                      //i=x   j=y
        for (int j = 0; j <= 19; j++) {
            if (array2d[i][j]->getType() == 2) {
                array2d[i][j]->last_eaten++;
                if (array2d[i][j]->last_eaten >= 3) {
                    array2d[j][i] = nullptr;
                }
            }
        }
    }
}

void antsSpawn(Organism ***array2d, int &i){
    int x=random(0,19);
    int y=random(0,19);
    if(array2d[y][x]==nullptr) {
        array2d[y][x] = new Ant();
        i++;
    }
    else{
        antsSpawn(array2d,i);
    }
}

void doodlebugsSpawn(Organism ***array2d, int &i){
    int x=random(0,19);
    int y=random(0,19);
    if(array2d[y][x]==nullptr) {
        array2d[y][x] = new Doodlebug();
        i++;
    }
    else{
        antsSpawn(array2d,i);
    }
}

void turn(Organism ***array2d, bool first){                     //prints out and increments turns on the board
    //initialize(array2d);
    if (first) {
        // Create 2D array of pointers:
        Organism ***array2d = new Organism **[20];
        for (int i = 0; i < 20; i++) {
            array2d[i] = new Organism *[20];
        }

        for (int i = 0; i < 20; i++) {              // Null out the pointers contained in the array
            for (int j = 0; j < 20; j++) {
                array2d[i][j] = nullptr;
            }
        }
        int i(0),j(0);
        while (i < 100) {                               //spawns ants
            antsSpawn(array2d, i);
        }


        while (j < 5) {                                 //spawns doodlebugs
            doodlebugsSpawn(array2d, j);
        }
    }

    print(array2d);

    antsMove(array2d);
    doodlebugsMove(array2d);

    antsBreed(array2d);
    doodlebugBreed(array2d);
    doodlebugStarve(array2d);

    bool Enter;
    cout <<"Press enter to increment"<<endl;
    cin>>Enter;
    if(Enter==1){
        turn(array2d,0);
    }
}


int main(){
    Organism ***array2d;
    turn(array2d,1);


    return 0;
}