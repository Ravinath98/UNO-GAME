
//library files...
#include <SFML/Graphics.hpp>   //SFML graphics library...
#include  <iostream>
#include <SFML/Audio.hpp>      //SFML audio library...
#include <cstdlib>             //library for getting abs()
#include <time.h>               //time library...
#include <string>
#include <sstream>

using namespace std;
using namespace sf;
int xSize = 1900;   //x axis size of the window
int ySize = 800;   //y axis size of the window
int cxSize = 66;    //width of the card(size)
int cySize = 105;   //height of the card(size)
Text colorChoose;
int checkButton; //check the button for choosing card after a wild card..........
RenderWindow window(VideoMode(xSize, ySize), "GAME", sf::Style::Close | sf::Style::Resize);  //showing the gaming window...


//global variables declaration
int stopRound = 0;
int userPosition = 8 * cxSize;
int pileCurrent = 15;  //this is the pile topest card index........(after dividing and get the first card from the pile) --> this used later...
int selectedCards[20];
int selectedCardsCount = 0;
int in = 0;
int pileCards = 15;
int computerCards = 7;
int blueStartNum = 1;
int blueEndNum = 19;
int yellowStartNum = 20;
int yellowEndNum = 38;
int redStartNum = 39;
int redEndNum = 57;
int greenStartNum = 58;
int greenEndNum = 76;
int blueRev1 = 81;
int blueRev2 = 82;
int yellowRev1 = 79;
int yellowRev2 = 80;
int redRev1 = 77;
int redRev2 = 78;
int greenRev1 = 83;
int greenRev2 = 84;
int blueSkip1 = 91;
int blueSkip2 = 92;
int yellowSkip1 = 87;
int yellowSkip2 = 88;
int redSkip1 = 85;
int redSkip2 = 86;
int greenSkip1 = 89;
int greenSkip2 = 90;
int blueDraw21 = 93;
int blueDraw22 = 94;
int yellowDraw21 = 97;
int yellowDraw22 = 98;
int redDraw21 = 95;
int redDraw22 = 96;
int greenDraw21 = 99;
int greenDraw22 = 100;
int wildStart = 101;
int wildEnd = 104;
int wildDraw4Start = 105;
int wildDraw4End = 108;
int choosingCard;




RectangleShape cards[109];  //RectangleShape class cards objects array..
struct node  //struct for doubly linked list..
{
    int data;
    node* next;
    node* prev;
};

class cardSets  //class for doubly linked list
{
private:
    node* start;
public:
    cardSets()
    {
        start = NULL;

    }

    void addCard(int x)  //add card to a plyer hand card set(linked list,in here add cards end of the list)
    {

        node* newNode; //define a new node...
        node* temp;
        newNode = new node; //allocate memory...
        newNode->data = x;
        temp = start;
        if (start == NULL)
        {
            start = newNode;
            newNode->prev = NULL;
            newNode->next = NULL;
            return;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
            newNode->next = NULL;
            return;
        }

    }


    void addCardPositionX(int x1)    // add the position of card to linked list , (X coordinate)...
    {

        node* tem = new node;
        tem->data = x1;
        tem->next = NULL;
        if (start == NULL)
        {
            start = tem;

        }

    }
    int scoreCount()
    {
        node* temp;
        temp = start;
        int total = 0;
        while (temp != NULL)
        {

            if (temp->data == 2 || temp->data == 3 || temp->data == 21 || temp->data == 22 || temp->data == 40 || temp->data == 41 || temp->data == 59 || temp->data == 60)
            {
                total = total + 1;
            }
            else if (temp->data == 4 || temp->data == 5 || temp->data == 23 || temp->data == 24 || temp->data == 42 || temp->data == 43 || temp->data == 61 || temp->data == 62)
            {
                total = total + 2;
            }
            else if (temp->data == 6 || temp->data == 7 || temp->data == 25 || temp->data == 26 || temp->data == 44 || temp->data == 45 || temp->data == 63 || temp->data == 64)
            {
                total = total + 3;
            }
            else if (temp->data == 8 || temp->data == 9 || temp->data == 27 || temp->data == 28 || temp->data == 46 || temp->data == 47 || temp->data == 65 || temp->data == 66)
            {
                total = total + 4;
            }
            else if (temp->data == 10 || temp->data == 11 || temp->data == 29 || temp->data == 30 || temp->data == 48 || temp->data == 49 || temp->data == 67 || temp->data == 68)
            {
                total = total + 5;
            }
            else if (temp->data == 12 || temp->data == 13 || temp->data == 31 || temp->data == 32 || temp->data == 50 || temp->data == 51 || temp->data == 69 || temp->data == 70)
            {
                total = total + 6;
            }
            else if (temp->data == 14 || temp->data == 15 || temp->data == 33 || temp->data == 34 || temp->data == 52 || temp->data == 53 || temp->data == 71 || temp->data == 72)
            {
                total = total + 7;
            }
            else if (temp->data == 16 || temp->data == 17 || temp->data == 35 || temp->data == 36 || temp->data == 54 || temp->data == 55 || temp->data == 73 || temp->data == 74)
            {
                total = total + 8;
            }
            else if (temp->data == 18 || temp->data == 19 || temp->data == 37 || temp->data == 38 || temp->data == 56 || temp->data == 57 || temp->data == 75 || temp->data == 76)
            {
                total = total + 9;
            }
            else if (temp->data > 76 && temp->data < 101)
            {
                total = total + 20;
            }
            else if (temp->data > 100 && temp->data < 109)
            {
                total = total + 50;
            }




        }
        return total;
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    void displayCards1(int value)  //display my card set(bottom player me) //this is for after enter the enter button....
    {

        node* temp;
        temp = start;
        int x5 = xSize / 32;  //first location(x) of our card set..
        int y5 = ySize - cySize; //first location(y) of our card set..
        while (temp != NULL)
        {
            if (temp->data == value)
            {
                cards[value].setPosition(xSize / 2 - 100, ySize / 2 - 100); //selected card position
                window.draw(cards[value]);

                temp = temp->next;
                x5 = x5 + cxSize;
            }
            else
            {

                cards[temp->data].setPosition(x5, y5);
                window.draw(cards[temp->data]);

                temp = temp->next;
                // addCardPositionX(x5);
                x5 = x5 + cxSize;
            }

        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////


    void displayCards(int value, int selectedCards[])  //display my card set(bottom player me)
    {

        node* temp;
        temp = start;
        int x5 = xSize / 32;  //first location(x) of our card set..
        int y5 = ySize - cySize; //first location(y) of our card set..
        while (temp != NULL)
        {
            if (temp->data == value)
            {
                cards[value].setPosition(xSize / 2 - 100, ySize / 2 - 100); //selected card position
                window.draw(cards[value]);

                temp = temp->next;
                x5 = x5 + cxSize;
            }
            else
            {
                int t = 0;
                for (int i = 0; i < 20; i++)
                {
                    if (x5 == selectedCards[i])
                    {
                        t = 1;
                    }
                }
                if (t == 0)
                {
                    cards[temp->data].setPosition(x5, y5);
                    window.draw(cards[temp->data]);
                    temp = temp->next;
                }


                x5 = x5 + cxSize;






            }

        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    void removeCard(int val)  //search and remove card....
    {
        node* temp;
        temp = start;
        if (temp->next == NULL)  //if one node in the list...
        {
            if (temp->data != val)  //if that one element data is not the finding data..
            {
                cout << "Finding data doesn't exist in the list!!!!!" << endl;
                return;
            }
            start = NULL;
            delete temp;
            return;

        }

        while (temp->data != val)
        {
            temp = temp->next;
            if (temp == NULL)  //if finding element doesn't found in the list
            {
                cout << "Finding data doesn't exist in the list!!!!!" << endl;
                return;
            }

        }
        //if finding element found..........
        if (temp->next == NULL)  //if value in the last node....
        {
            temp->prev->next = NULL;
            delete temp;
            return;

        }
        if (temp->prev == NULL)  //if value in the first node...
        {
            temp->next->prev = NULL;
            start = temp->next;
            delete temp;
            return;
        }
        else	//if value in the middle of the list..
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
            return;
        }
    }

    int searchAndDisplay(int value, int compare)  //search and display card....yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
    {
        Font font1;
        if (font1.loadFromFile("Data/BAU.TTF") == 0)  //if cannot load the font...then close the program
        {
            return 1;
        }
        if (value == 1) //blue number 
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= blueStartNum && temp->data <= blueEndNum)
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (abs(temp->data - compare) == 18 || abs(temp->data - compare) == 19 || abs(temp->data - compare) == 20 || abs(temp->data - compare) == 37 || abs(temp->data - compare) == 38 || abs(temp->data - compare) == 39 || abs(temp->data - compare) == 56 || abs(temp->data - compare) == 57 || abs(temp->data - compare) == 58 || abs(temp->data - compare) == 1)
                {
                    if (temp->data % 2 == 0)
                    {
                        if (abs(temp->data - 1 - compare) == 18 || abs(temp->data - 1 - compare) == 19 || abs(temp->data - 1 - compare) == 20 || abs(temp->data - 1 - compare) == 37 || abs(temp->data - 1 - compare) == 38 || abs(temp->data - 1 - compare) == 39 || abs(temp->data - 1 - compare) == 56 || abs(temp->data - 1 - compare) == 57 || abs(temp->data - 1 - compare) == 58 || temp->data + 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }

                    }
                    else
                    {
                        if (abs(temp->data + 1 - compare) == 18 || abs(temp->data + 1 - compare) == 19 || abs(temp->data + 1 - compare) == 20 || abs(temp->data + 1 - compare) == 37 || abs(temp->data + 1 - compare) == 38 || abs(temp->data + 1 - compare) == 39 || abs(temp->data + 1 - compare) == 56 || abs(temp->data + 1 - compare) == 57 || abs(temp->data + 1 - compare) == 58 || temp->data - 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }
                    }
                }
                else if (temp->data == blueRev1 || temp->data == blueRev2 || temp->data == blueDraw21 || temp->data == blueDraw22 || temp->data == blueSkip1 || temp->data == blueSkip2) //blue draw2 ,skip ,reverse cards..
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)  //wild cards......
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);


                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End) //wild draw4 cards...
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                temp = temp->next;
            }
            return -1;
        }
        else if (value == 2) // if yellow number
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= yellowStartNum && temp->data <= yellowEndNum)   //put yellow number....
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (abs(temp->data - compare) == 18 || abs(temp->data - compare) == 19 || abs(temp->data - compare) == 20 || abs(temp->data - compare) == 37 || abs(temp->data - compare) == 38 || abs(temp->data - compare) == 39 || abs(temp->data - compare) == 56 || abs(temp->data - compare) == 57 || abs(temp->data - compare) == 58 || abs(temp->data - compare) == 1) //put card equal to another same number..
                {
                    if (temp->data % 2 == 0)
                    {
                        if (abs(temp->data - 1 - compare) == 18 || abs(temp->data - 1 - compare) == 19 || abs(temp->data - 1 - compare) == 20 || abs(temp->data - 1 - compare) == 37 || abs(temp->data - 1 - compare) == 38 || abs(temp->data - 1 - compare) == 39 || abs(temp->data - 1 - compare) == 56 || abs(temp->data - 1 - compare) == 57 || abs(temp->data - 1 - compare) == 58 || temp->data + 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }

                    }
                    else
                    {
                        if (abs(temp->data + 1 - compare) == 18 || abs(temp->data + 1 - compare) == 19 || abs(temp->data + 1 - compare) == 20 || abs(temp->data + 1 - compare) == 37 || abs(temp->data + 1 - compare) == 38 || abs(temp->data + 1 - compare) == 39 || abs(temp->data + 1 - compare) == 56 || abs(temp->data + 1 - compare) == 57 || abs(temp->data + 1 - compare) == 58 || temp->data - 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }
                    }
                }
                else if (temp->data == yellowRev1 || temp->data == yellowRev2 || temp->data == yellowDraw21 || temp->data == yellowDraw22 || temp->data == yellowSkip1 || temp->data == yellowSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1;
        }
        else if (value == 3) // if red number
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= redStartNum && temp->data <= redEndNum)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (abs(temp->data - compare) == 18 || abs(temp->data - compare) == 19 || abs(temp->data - compare) == 20 || abs(temp->data - compare) == 37 || abs(temp->data - compare) == 38 || abs(temp->data - compare) == 39 || abs(temp->data - compare) == 56 || abs(temp->data - compare) == 57 || abs(temp->data - compare) == 58 || abs(temp->data - compare) == 1)
                {
                    if (temp->data % 2 == 0)
                    {
                        if (abs(temp->data - 1 - compare) == 18 || abs(temp->data - 1 - compare) == 19 || abs(temp->data - 1 - compare) == 20 || abs(temp->data - 1 - compare) == 37 || abs(temp->data - 1 - compare) == 38 || abs(temp->data - 1 - compare) == 39 || abs(temp->data - 1 - compare) == 56 || abs(temp->data - 1 - compare) == 57 || abs(temp->data - 1 - compare) == 58 || temp->data + 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }

                    }
                    else
                    {
                        if (abs(temp->data + 1 - compare) == 18 || abs(temp->data + 1 - compare) == 19 || abs(temp->data + 1 - compare) == 20 || abs(temp->data + 1 - compare) == 37 || abs(temp->data + 1 - compare) == 38 || abs(temp->data + 1 - compare) == 39 || abs(temp->data + 1 - compare) == 56 || abs(temp->data + 1 - compare) == 57 || abs(temp->data + 1 - compare) == 58 || temp->data - 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }
                    }
                }
                else if (temp->data == redRev1 || temp->data == redRev2 || temp->data == redDraw21 || temp->data == redDraw22 || temp->data == redSkip1 || temp->data == redSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1; //if doesn't found a matching card....................................
        }
        else if (value == 4) //green number..
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= greenStartNum && temp->data <= greenEndNum)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (abs(temp->data - compare) == 18 || abs(temp->data - compare) == 19 || abs(temp->data - compare) == 20 || abs(temp->data - compare) == 37 || abs(temp->data - compare) == 38 || abs(temp->data - compare) == 39 || abs(temp->data - compare) == 56 || abs(temp->data - compare) == 57 || abs(temp->data - compare) == 58 || abs(temp->data - compare) == 1)
                {
                    if (temp->data % 2 == 0)
                    {
                        if (abs(temp->data - 1 - compare) == 18 || abs(temp->data - 1 - compare) == 19 || abs(temp->data - 1 - compare) == 20 || abs(temp->data - 1 - compare) == 37 || abs(temp->data - 1 - compare) == 38 || abs(temp->data - 1 - compare) == 39 || abs(temp->data - 1 - compare) == 56 || abs(temp->data - 1 - compare) == 57 || abs(temp->data - 1 - compare) == 58 || temp->data + 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }

                    }
                    else
                    {
                        if (abs(temp->data + 1 - compare) == 18 || abs(temp->data + 1 - compare) == 19 || abs(temp->data + 1 - compare) == 20 || abs(temp->data + 1 - compare) == 37 || abs(temp->data + 1 - compare) == 38 || abs(temp->data + 1 - compare) == 39 || abs(temp->data + 1 - compare) == 56 || abs(temp->data + 1 - compare) == 57 || abs(temp->data + 1 - compare) == 58 || temp->data - 1 == compare)
                        {
                            cards[temp->data].setPosition(320, 320);
                            window.draw(cards[temp->data]);
                            return temp->data;
                        }
                    }
                }
                else if (temp->data == greenRev1 || temp->data == greenRev2 || temp->data == greenDraw21 || temp->data == greenDraw22 || temp->data == greenSkip1 || temp->data == greenSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1; //if doesn't found a matching card....................................
        }
        else if (value == 5) //blue skip,draw2,reverse
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= blueStartNum && temp->data <= blueEndNum)  //choose by color...
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (compare >= 85 && compare <= 92) //skip card...
                {
                    if (temp->data >= 85 && temp->data <= 92)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 78 && compare <= 84) //reverse card...
                {
                    if (temp->data >= 78 && temp->data <= 84)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 93 && compare <= 100)  //draw 2..
                {
                    if (temp->data >= 93 && temp->data <= 100)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }

            }
            return -1; //if card not found..

        }
        else if (value == 6)  //yellow skip,draw2,reverse
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= yellowStartNum && temp->data <= yellowEndNum) //choose by color...
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (compare >= 85 && compare <= 92) //skip card...
                {
                    if (temp->data >= 85 && temp->data <= 92)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 78 && compare <= 84) //reverse card...
                {
                    if (temp->data >= 78 && temp->data <= 84)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 93 && compare <= 100)  //draw 2..
                {
                    if (temp->data >= 93 && temp->data <= 100)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
            }
            return -1;
        }
        else if (value == 7) //red skip,draw2,reverse
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= redStartNum && temp->data <= redEndNum) //choose by color...
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (compare >= 85 && compare <= 92) //skip card...
                {
                    if (temp->data >= 85 && temp->data <= 92)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 78 && compare <= 84) //reverse card...
                {
                    if (temp->data >= 78 && temp->data <= 84)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 93 && compare <= 100)  //draw 2..
                {
                    if (temp->data >= 93 && temp->data <= 100)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
            }
            return -1;

        }
        else if (value == 8)  //green skip,draw2,reverse
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= greenStartNum && temp->data <= greenEndNum) //choose by color...
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (compare >= 85 && compare <= 92) //skip card...
                {
                    if (temp->data >= 85 && temp->data <= 92)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 78 && compare <= 84) //reverse card...
                {
                    if (temp->data >= 78 && temp->data <= 84)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (compare >= 93 && compare <= 100)  //draw 2..
                {
                    if (temp->data >= 93 && temp->data <= 100)
                    {
                        cards[temp->data].setPosition(320, 320);
                        window.draw(cards[temp->data]);
                        return temp->data;
                    }
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);


                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
            }
            return -1;

        }
        else if (value == 9)  //wild Red
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= redStartNum && temp->data <= redEndNum)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data == redRev1 || temp->data == redRev2 || temp->data == redDraw21 || temp->data == redDraw22 || temp->data == redSkip1 || temp->data == redSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1; //if doesn't found a matching card....................................
        }
        else if (value == 10)  //wild Green
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= greenStartNum && temp->data <= greenEndNum)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }

                else if (temp->data == greenRev1 || temp->data == greenRev2 || temp->data == greenDraw21 || temp->data == greenDraw22 || temp->data == greenSkip1 || temp->data == greenSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1; //if doesn't found a matching card....................................
        }
        else if (value == 11)  //wild Blue
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= blueStartNum && temp->data <= blueEndNum)
                {

                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }

                else if (temp->data == blueRev1 || temp->data == blueRev2 || temp->data == blueDraw21 || temp->data == blueDraw22 || temp->data == blueSkip1 || temp->data == blueSkip2) //blue draw2 ,skip ,reverse cards..
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)  //wild cards......
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End) //wild draw4 cards...
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1;
        }
        else if (value == 12)  //wild Yellow
        {
            node* temp;
            temp = start;
            while (temp != NULL)
            {
                if (temp->data >= yellowStartNum && temp->data <= yellowEndNum)   //put yellow number....
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }

                else if (temp->data == yellowRev1 || temp->data == yellowRev2 || temp->data == yellowDraw21 || temp->data == yellowDraw22 || temp->data == yellowSkip1 || temp->data == yellowSkip2)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                else if (temp->data >= wildStart && temp->data <= wildEnd)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);

                    return temp->data;
                }
                else if (temp->data >= wildDraw4Start && temp->data <= wildDraw4End)
                {
                    cards[temp->data].setPosition(320, 320);
                    window.draw(cards[temp->data]);
                    return temp->data;
                }
                temp = temp->next;
            }
            return -1;
        }


    }

};




///////////////////////////////////// MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
int main()
{


    


    window.setFramerateLimit(60);   //set fps (this can be changed...)

    window.setKeyRepeatEnabled(false); //even holding a key it will print one output in console..


    bool play = true;  //to stop gameloop
    Event event;        //Events handling object

    //States for button/events...
    bool enterButton = false;
    bool leftClick = false;
    bool rightClick = false;
    bool RButton = false;
    bool BButton = false;
    bool GButton = false;
    bool YButton = false;
    bool sButton = false;
    bool eButton = false;

    //Variabales..
    int mouseX = 0;
    int mouseY = 0;

    //Images...
    Texture cardImage[55];  //texture(cards images) objects array...



    Texture image;   //background image object...
    if (image.loadFromFile("Data/image4.png") == 0) {   //if not found the image..
        return 1;   //if program failed to load the image...
    }
    //back card...
    Texture backImageRotate;
    if (backImageRotate.loadFromFile("Data/back2.png") == 0) {   //if not found the image..
        return 1;   //if program failed to load the image...
    }

    Texture colors;
    if (colors.loadFromFile("Data/colors.png") == 0)
    {
        return 1;
    }
    ///LOADING CARDS................................................
    /////////////////////////////

    if (cardImage[0].loadFromFile("Data/back.png") == 0)
    {
        return 1;
    }

    if (cardImage[1].loadFromFile("Data/b0.png") == 0)
    {
        return 1;
    }

    if (cardImage[2].loadFromFile("Data/b1.png") == 0)
    {
        return 1;
    }

    if (cardImage[3].loadFromFile("Data/b2.png") == 0)
    {
        return 1;
    }

    if (cardImage[4].loadFromFile("Data/b3.png") == 0)
    {
        return 1;
    }

    if (cardImage[5].loadFromFile("Data/b4.png") == 0)
    {
        return 1;
    }

    if (cardImage[6].loadFromFile("Data/b5.png") == 0)
    {
        return 1;
    }

    if (cardImage[7].loadFromFile("Data/b6.png") == 0)
    {
        return 1;
    }

    if (cardImage[8].loadFromFile("Data/b7.png") == 0)
    {
        return 1;
    }

    if (cardImage[9].loadFromFile("Data/b8.png") == 0)
    {
        return 1;
    }

    if (cardImage[10].loadFromFile("Data/b9.png") == 0)
    {
        return 1;
    }

    if (cardImage[11].loadFromFile("Data/y0.png") == 0)
    {
        return 1;
    }

    if (cardImage[12].loadFromFile("Data/y1.png") == 0)
    {
        return 1;
    }

    if (cardImage[13].loadFromFile("Data/y2.png") == 0)
    {
        return 1;
    }

    if (cardImage[14].loadFromFile("Data/y3.png") == 0)
    {
        return 1;
    }

    if (cardImage[15].loadFromFile("Data/y4.png") == 0)
    {
        return 1;
    }

    if (cardImage[16].loadFromFile("Data/y5.png") == 0)
    {
        return 1;
    }

    if (cardImage[17].loadFromFile("Data/y6.png") == 0)
    {
        return 1;
    }

    if (cardImage[18].loadFromFile("Data/y7.png") == 0)
    {
        return 1;
    }

    if (cardImage[19].loadFromFile("Data/y8.png") == 0)
    {
        return 1;
    }

    if (cardImage[20].loadFromFile("Data/y9.png") == 0)
    {
        return 1;
    }

    if (cardImage[21].loadFromFile("Data/r0.png") == 0)
    {
        return 1;
    }

    if (cardImage[22].loadFromFile("Data/r1.png") == 0)
    {
        return 1;
    }

    if (cardImage[23].loadFromFile("Data/r2.png") == 0)
    {
        return 1;
    }

    if (cardImage[24].loadFromFile("Data/r3.png") == 0)
    {
        return 1;
    }

    if (cardImage[25].loadFromFile("Data/r4.png") == 0)
    {
        return 1;
    }

    if (cardImage[26].loadFromFile("Data/r5.png") == 0)
    {
        return 1;
    }

    if (cardImage[27].loadFromFile("Data/r6.png") == 0)
    {
        return 1;
    }

    if (cardImage[28].loadFromFile("Data/r7.png") == 0)
    {
        return 1;
    }

    if (cardImage[29].loadFromFile("Data/r8.png") == 0)
    {
        return 1;
    }

    if (cardImage[30].loadFromFile("Data/r9.png") == 0)
    {
        return 1;
    }

    if (cardImage[31].loadFromFile("Data/g0.png") == 0)
    {
        return 1;
    }

    if (cardImage[32].loadFromFile("Data/g1.png") == 0)
    {
        return 1;
    }

    if (cardImage[33].loadFromFile("Data/g2.png") == 0)
    {
        return 1;
    }

    if (cardImage[34].loadFromFile("Data/g3.png") == 0)
    {
        return 1;
    }

    if (cardImage[35].loadFromFile("Data/g4.png") == 0)
    {
        return 1;
    }

    if (cardImage[36].loadFromFile("Data/g5.png") == 0)
    {
        return 1;
    }

    if (cardImage[37].loadFromFile("Data/g6.png") == 0)
    {
        return 1;
    }

    if (cardImage[38].loadFromFile("Data/g7.png") == 0)
    {
        return 1;
    }

    if (cardImage[39].loadFromFile("Data/g8.png") == 0)
    {
        return 1;
    }

    if (cardImage[40].loadFromFile("Data/g9.png") == 0)
    {
        return 1;
    }

    if (cardImage[41].loadFromFile("Data/reverser.png") == 0)
    {
        return 1;
    }

    if (cardImage[42].loadFromFile("Data/reversey.png") == 0)
    {
        return 1;
    }

    if (cardImage[43].loadFromFile("Data/reverseb.png") == 0)
    {
        return 1;
    }

    if (cardImage[44].loadFromFile("Data/reverseg.png") == 0)
    {
        return 1;
    }

    if (cardImage[45].loadFromFile("Data/skipr.png") == 0)
    {
        return 1;
    }

    if (cardImage[46].loadFromFile("Data/skipy.png") == 0)
    {
        return 1;
    }

    if (cardImage[47].loadFromFile("Data/skipg.png") == 0)
    {
        return 1;
    }

    if (cardImage[48].loadFromFile("Data/skipb.png") == 0)
    {
        return 1;
    }

    if (cardImage[49].loadFromFile("Data/draw2b.png") == 0)
    {
        return 1;
    }

    if (cardImage[50].loadFromFile("Data/draw2r.png") == 0)
    {
        return 1;
    }

    if (cardImage[51].loadFromFile("Data/draw2y.png") == 0)
    {
        return 1;
    }

    if (cardImage[52].loadFromFile("Data/draw2g.png") == 0)
    {
        return 1;
    }

    if (cardImage[53].loadFromFile("Data/wild.png") == 0)
    {
        return 1;
    }

    if (cardImage[54].loadFromFile("Data/draw4.png") == 0)
    {
        return 1;
    }

    Texture unoButton;   //uno button image......
    if (unoButton.loadFromFile("Data/uno.png") == 0)
    {
        return 1;
    }

    Texture menu;   //uno button image......
    if (menu.loadFromFile("Data/menu.png") == 0)
    {
        return 1;
    }


    RectangleShape uno;       //define a rectangle....
    uno.setSize(Vector2f(200, 100));   //set the rectangle size...
    uno.setPosition(1200, 450);      //set the rectangle position..
    uno.setFillColor(Color::White);   //set the fill colour...
    uno.setTexture(&unoButton);    //load the image to the rectangle....


    //Render Shapes..(this is for making the cards rectangle shape.....)
      //Rectangular shape...
    RectangleShape rect1;       //define a rectangle....
    rect1.setSize(Vector2f(xSize, ySize));   //set the rectangle size...
    rect1.setPosition(0, 0);      //set the rectangle position..
    rect1.setFillColor(Color::White);   //set the fill colour...
    rect1.setTexture(&image);    //load the image to the rectangle....

    RectangleShape rectMy;       //define a rectangle....
    rectMy.setSize(Vector2f(xSize, ySize));   //set the rectangle size...
    rectMy.setPosition(0, 0);      //set the rectangle position..
    rectMy.setFillColor(Color::White);   //set the fill colour...
    rectMy.setTexture(&menu);    //load the image to the rectangle....



    RectangleShape col;
    col.setSize(Vector2f(103, 146));   //set the rectangle size...
    col.setPosition(500, 500);      //set the rectangle position..
    col.setFillColor(Color::White);   //set the fill colour...
    col.setTexture(&colors);    //load the image to the rectangle....

    //CARD OBJECTS ARRAY////////
    ////////////////////////


    //card print//////////
      //////////////
      //pile showing..
    cards[0].setSize(Vector2f(cxSize, cySize));   //set the rectangle size...
    cards[0].setFillColor(Color::White);   //set the fill colour...
    cards[0].setTexture(&cardImage[0]);    //load the image to the rectangle....

    //PLAYER 2(computer) CARDS (showing back side of the uno card)
    RectangleShape rect3;
    rect3.setSize(Vector2f(cySize, cxSize));   //set the rectangle size...
    rect3.setFillColor(Color::White);   //set the fill colour...
    rect3.setTexture(&backImageRotate);    //load the image to the rectangle....

    //blue card 0
    cards[1].setSize(Vector2f(cxSize, cySize));
    cards[1].setFillColor(Color::White);
    cards[1].setTexture(&cardImage[1]);
    //set other blue cards...
    int k1 = 2;
    for (int j1 = 2; j1 < 20; j1++)
    {

        cards[j1].setSize(Vector2f(cxSize, cySize));
        cards[j1].setFillColor(Color::White);
        cards[j1].setTexture(&cardImage[k1]);
        j1 = j1 + 1;
        cards[j1].setSize(Vector2f(cxSize, cySize));
        cards[j1].setFillColor(Color::White);
        cards[j1].setTexture(&cardImage[k1]);
        k1 = k1 + 1;
    }

    //yellow card 0
    cards[20].setSize(Vector2f(cxSize, cySize));
    cards[20].setFillColor(Color::White);
    cards[20].setTexture(&cardImage[11]);
    //set other yellow cards...
    int k2 = 12;
    for (int j2 = 21; j2 < 39; j2++)
    {

        cards[j2].setSize(Vector2f(cxSize, cySize));
        cards[j2].setFillColor(Color::White);
        cards[j2].setTexture(&cardImage[k2]);
        j2 = j2 + 1;
        cards[j2].setSize(Vector2f(cxSize, cySize));
        cards[j2].setFillColor(Color::White);
        cards[j2].setTexture(&cardImage[k2]);
        k2 = k2 + 1;
    }

    //red card 0
    cards[39].setSize(Vector2f(cxSize, cySize));
    cards[39].setFillColor(Color::White);
    cards[39].setTexture(&cardImage[21]);
    //set other red cards...
    int k3 = 22;
    for (int j3 = 40; j3 < 58; j3++)
    {

        cards[j3].setSize(Vector2f(cxSize, cySize));
        cards[j3].setFillColor(Color::White);
        cards[j3].setTexture(&cardImage[k3]);
        j3 = j3 + 1;
        cards[j3].setSize(Vector2f(cxSize, cySize));
        cards[j3].setFillColor(Color::White);
        cards[j3].setTexture(&cardImage[k3]);
        k3 = k3 + 1;
    }

    //green card 0
    cards[58].setSize(Vector2f(cxSize, cySize));
    cards[58].setFillColor(Color::White);
    cards[58].setTexture(&cardImage[31]);
    //set other green cards...
    int k4 = 32;
    for (int j4 = 59; j4 < 77; j4++)
    {

        cards[j4].setSize(Vector2f(cxSize, cySize));
        cards[j4].setFillColor(Color::White);
        cards[j4].setTexture(&cardImage[k4]);
        j4 = j4 + 1;
        cards[j4].setSize(Vector2f(cxSize, cySize));
        cards[j4].setFillColor(Color::White);
        cards[j4].setTexture(&cardImage[k4]);
        k4 = k4 + 1;
    }
    //WILD,REVERSE,SKIP,DRAW CARDS...........
    //////////////////////
    //REVERSE RED
    cards[77].setSize(Vector2f(cxSize, cySize));
    cards[77].setFillColor(Color::White);
    cards[77].setTexture(&cardImage[41]);

    cards[78].setSize(Vector2f(cxSize, cySize));
    cards[78].setFillColor(Color::White);
    cards[79].setTexture(&cardImage[41]);
    //REVERSE YELLOW
    cards[79].setSize(Vector2f(cxSize, cySize));
    cards[79].setFillColor(Color::White);
    cards[79].setTexture(&cardImage[42]);

    cards[80].setSize(Vector2f(cxSize, cySize));
    cards[80].setFillColor(Color::White);
    cards[80].setTexture(&cardImage[42]);
    //REVERSE BLUE
    cards[81].setSize(Vector2f(cxSize, cySize));
    cards[81].setFillColor(Color::White);
    cards[81].setTexture(&cardImage[43]);

    cards[82].setSize(Vector2f(cxSize, cySize));
    cards[82].setFillColor(Color::White);
    cards[82].setTexture(&cardImage[43]);

    //REVERSE GREEN
    cards[83].setSize(Vector2f(cxSize, cySize));
    cards[83].setFillColor(Color::White);
    cards[83].setTexture(&cardImage[44]);

    cards[84].setSize(Vector2f(cxSize, cySize));
    cards[84].setFillColor(Color::White);
    cards[84].setTexture(&cardImage[44]);

    //SKIP RED
    cards[85].setSize(Vector2f(cxSize, cySize));
    cards[85].setFillColor(Color::White);
    cards[85].setTexture(&cardImage[45]);

    cards[86].setSize(Vector2f(cxSize, cySize));
    cards[86].setFillColor(Color::White);
    cards[86].setTexture(&cardImage[45]);
    //SKIP YELLOW
    cards[87].setSize(Vector2f(cxSize, cySize));
    cards[87].setFillColor(Color::White);
    cards[87].setTexture(&cardImage[46]);

    cards[88].setSize(Vector2f(cxSize, cySize));
    cards[88].setFillColor(Color::White);
    cards[88].setTexture(&cardImage[46]);

    //SKIP GREEN
    cards[89].setSize(Vector2f(cxSize, cySize));
    cards[89].setFillColor(Color::White);
    cards[89].setTexture(&cardImage[47]);

    cards[90].setSize(Vector2f(cxSize, cySize));
    cards[90].setFillColor(Color::White);
    cards[90].setTexture(&cardImage[47]);

    //SKIP BLUE
    cards[91].setSize(Vector2f(cxSize, cySize));
    cards[91].setFillColor(Color::White);
    cards[91].setTexture(&cardImage[48]);

    cards[92].setSize(Vector2f(cxSize, cySize));
    cards[92].setFillColor(Color::White);
    cards[92].setTexture(&cardImage[48]);

    //DRAW 2 BLUE
    cards[93].setSize(Vector2f(cxSize, cySize));
    cards[93].setFillColor(Color::White);
    cards[93].setTexture(&cardImage[49]);

    cards[94].setSize(Vector2f(cxSize, cySize));
    cards[94].setFillColor(Color::White);
    cards[94].setTexture(&cardImage[49]);

    //DRAW 2 RED
    cards[95].setSize(Vector2f(cxSize, cySize));
    cards[95].setFillColor(Color::White);
    cards[95].setTexture(&cardImage[50]);

    cards[96].setSize(Vector2f(cxSize, cySize));
    cards[96].setFillColor(Color::White);
    cards[96].setTexture(&cardImage[50]);

    //DRAW 2 YELLOW
    cards[97].setSize(Vector2f(cxSize, cySize));
    cards[97].setFillColor(Color::White);
    cards[97].setTexture(&cardImage[51]);

    cards[98].setSize(Vector2f(cxSize, cySize));
    cards[98].setFillColor(Color::White);
    cards[98].setTexture(&cardImage[51]);

    //DRAW 2 GREEN
    cards[99].setSize(Vector2f(cxSize, cySize));
    cards[99].setFillColor(Color::White);
    cards[99].setTexture(&cardImage[52]);

    cards[100].setSize(Vector2f(cxSize, cySize));
    cards[100].setFillColor(Color::White);
    cards[100].setTexture(&cardImage[52]);

    //WILD CARDS
    cards[101].setSize(Vector2f(cxSize, cySize));
    cards[101].setFillColor(Color::White);
    cards[101].setTexture(&cardImage[53]);

    cards[102].setSize(Vector2f(cxSize, cySize));
    cards[102].setFillColor(Color::White);
    cards[102].setTexture(&cardImage[53]);

    cards[103].setSize(Vector2f(cxSize, cySize));
    cards[103].setFillColor(Color::White);
    cards[103].setTexture(&cardImage[53]);

    cards[104].setSize(Vector2f(cxSize, cySize));
    cards[104].setFillColor(Color::White);
    cards[104].setTexture(&cardImage[53]);

    //WILD DRAW 4 
    cards[105].setSize(Vector2f(cxSize, cySize));
    cards[105].setFillColor(Color::White);
    cards[105].setTexture(&cardImage[54]);

    cards[106].setSize(Vector2f(cxSize, cySize));
    cards[106].setFillColor(Color::White);
    cards[106].setTexture(&cardImage[54]);

    cards[107].setSize(Vector2f(cxSize, cySize));
    cards[107].setFillColor(Color::White);
    cards[107].setTexture(&cardImage[54]);

    cards[108].setSize(Vector2f(cxSize, cySize));
    cards[108].setFillColor(Color::White);
    cards[108].setTexture(&cardImage[54]);

    //index arrays for card types(FOR COMPARISON WHEN CHOOSING CARDS)....

    //BLUE CARDS...
    int blueCards[25];
    for (int i = 0; i < 19; i++)
    {
        blueCards[i] = i + 1;
    }
    blueCards[19] = 81;
    blueCards[20] = 82;
    blueCards[21] = 91;
    blueCards[22] = 92;
    blueCards[23] = 93;
    blueCards[24] = 94;

    //YELLOW CARDS...
    int yellowCards[25];
    for (int i = 0; i < 19; i++)
    {
        yellowCards[i] = i + 20;
    }
    yellowCards[19] = 79;
    yellowCards[20] = 80;
    yellowCards[21] = 87;
    yellowCards[22] = 88;
    yellowCards[23] = 97;
    yellowCards[24] = 98;

    //RED CARDS.......
    int redCards[25];
    for (int i = 0; i < 19; i++)
    {
        redCards[i] = i + 39;
    }
    redCards[19] = 77;
    redCards[20] = 78;
    redCards[21] = 85;
    redCards[22] = 86;
    redCards[23] = 95;
    redCards[24] = 96;

    //GREEN CARDS
    int greenCards[25];
    for (int i = 0; i < 19; i++)
    {
        greenCards[i] = i + 58;
    }
    greenCards[19] = 83;
    greenCards[20] = 84;
    greenCards[21] = 89;
    greenCards[22] = 90;
    greenCards[23] = 99;
    greenCards[24] = 100;

    //WILD CARDS
    int wildCards[4];
    for (int i = 0; i < 4; i++)
    {
        wildCards[i] = i + 101;
    }
    //WILD DRAW 4
    int wildDraw4[4];
    for (int i = 0; i < 4; i++)
    {
        wildDraw4[i] = i + 105;
    }
    ////END OF CARDS INDEX DEFINES....




    //FONTS//////////////////////////////////////////////////////////
    Font font;
    if (font.loadFromFile("Data/BAU.TTF") == 0)  //if cannot load the font...then close the program
    {
        return 1;
    }

    Text message;
    message.setFont(font);
    message.setCharacterSize(20);
    message.setString("Press 'Enter' to set the Deck");
    message.setPosition(100, 50);
    message.setFillColor(Color::Magenta);
    //skip
    Text skipCard;
    skipCard.setFont(font);
    skipCard.setCharacterSize(80);
    skipCard.setString("SKIP");
    skipCard.setPosition(550, 300);
    skipCard.setFillColor(Color::Magenta);
    //reverse
    Text reverseCard;
    reverseCard.setFont(font);
    reverseCard.setCharacterSize(80);
    reverseCard.setString("REVERSE");
    reverseCard.setPosition(550, 300);
    message.setFillColor(Color::Magenta);
    //draw2
    Text draw2Card;
    draw2Card.setFont(font);
    draw2Card.setCharacterSize(80);
    draw2Card.setString("DRAW 2");
    draw2Card.setPosition(550, 300);
    draw2Card.setFillColor(Color::Magenta);
    //draw4
    Text draw4Card;
    draw4Card.setFont(font);
    draw4Card.setCharacterSize(80);
    draw4Card.setString("DRAW 4");
    draw4Card.setPosition(550, 300);
    draw4Card.setFillColor(Color::Magenta);

    //wild color for computer...
    Text wildRedC;
    wildRedC.setFont(font);
    wildRedC.setCharacterSize(80);
    wildRedC.setString("RED");
    wildRedC.setPosition(550, 300);
    wildRedC.setFillColor(Color::Magenta);

    Text wildYellowC;
    wildYellowC.setFont(font);
    wildYellowC.setCharacterSize(80);
    wildYellowC.setString("YELLOW");
    wildYellowC.setPosition(550, 300);
    wildYellowC.setFillColor(Color::Magenta);

    Text wildGreenC;
    wildGreenC.setFont(font);
    wildGreenC.setCharacterSize(80);
    wildGreenC.setString("GREEN");
    wildGreenC.setPosition(550, 300);
    wildGreenC.setFillColor(Color::Magenta);

    Text wildBlueC;
    wildBlueC.setFont(font);
    wildBlueC.setCharacterSize(80);
    wildBlueC.setString("BLUE");
    wildBlueC.setPosition(550, 300);
    wildBlueC.setFillColor(Color::Magenta);
    sf::Music astronomiaMusic;  //define music object...
    if (astronomiaMusic.openFromFile("Data/click.wav") == 0)   //if music not loaded then exit the programm...
    {
        return 1;
    }

    

    ///SOUNDS
    //Sounds...
    sf::Music clickCard;     //sound buffer object that can load sounds from my computer....
    if (clickCard.openFromFile("Data/click.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;

    }
    sf::Music unoClick;     //sound buffer object that can load sounds from my computer....
    if (unoClick.openFromFile("Data/uno.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;

    }
    sf::Music shuffle;     //sound buffer object that can load sounds from my computer....
    if (shuffle.openFromFile("Data/shuffle.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;

    }
    sf::Music reverseClick;     //sound buffer object that can load sounds from my computer....
    if (reverseClick.openFromFile("Data/reverse.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;

    }
    sf::Music skipClick;     //sound buffer object that can load sounds from my computer....
    if (skipClick.openFromFile("Data/skip.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;

    }
    sf::Music draw2Click;     //sound buffer object that can load sounds from my computer....
    if (draw2Click.openFromFile("Data/draw2.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;
    }
    sf::Music draw4Click;     //sound buffer object that can load sounds from my computer....
    if (draw2Click.openFromFile("Data/draw4.wav") == 0)  //if failed to load sound program will exit..
    {
        return 1;
    }




    /////////////////////////////////////////////////////////////////////////////////////////
            //CREATE THE TABLE /// DIVIDE CARDS IN THE 4 PLAYERS 7 EACH............///////////
            //Card Array

    srand(time(0));
    int carray[108];
    int t;
    carray[0] = (rand() % 108) + 1;
    for (int i = 1; i < 108; i++)
    {

        do
        {
            t = 0;
            carray[i] = (rand() % 108) + 1;
            for (int j = 0; j < i; j++)
            {
                if (carray[j] == carray[i])
                {
                    t++;
                }
            }
        } while (t != 0);
    }

    //set players card sets......
    cardSets player1, player2, pile;  //define the linked list objects...
    //player 1=user...
    //player 2=computer...
   //Add card sets to players..

    //player 1 (user) linked list
    for (int i1 = 0; i1 < 7; i1++)
    {
        player1.addCard(carray[i1]);

    }

    //player 2 (computer) linked list
    for (int i2 = 7; i2 < 14; i2++)
    {
        player2.addCard(carray[i2]);

    }

    int temporyArray = carray[14];
    if (temporyArray > 76) //this do for if first card is a action card...(because if first card is a action card it gives some mess to this ...
    {
        for (int i = 15; i < 108; i++)
        {
            if (carray[i] < 77)
            {
                carray[14] = carray[i];
                carray[i] = temporyArray;
                break;

            }
        }
    }

    //pile linked list
    //this is start from 15 index because 14th index card is the first card get from the pile...
    for (int i5 = 15; i5 < 108; i5++)
    {
        pile.addCard(carray[i5]);
    }


    //first showing deck...

    window.draw(rectMy);
   
    //window.draw(message);
    window.display();
    int num = 0;

    // this is for check if 1 of card select ,then prevent to click again(location)
    int clickCount1 = 0;
    int clickCount2 = 0;
    int clickCount3 = 0;
    int clickCount4 = 0;
    int clickCount5 = 0;
    int clickCount6 = 0;
    int clickCount7 = 0;
    int clickCount8 = 0;
    int clickCount9 = 0;
    int clickCount10 = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int loopCount = 0; //count for pile printing..
    int mycount = 1;
    int outputCard = 0;
    int getOut = 0;
    //GAME LOOP ///////////////////////GAME LOOP////////////////////////////GAME LOOP /////////////////GAME LOOP ///////////////////
    //GAME LOOP.....////////////////////////////////////////////////GAME LOOP///////////////////////////////////GAME LOOP ////
    while (play == true && stopRound == 0) {

        //EVENTS



        while (window.pollEvent(event))  //check fps of all EVENTS(less than 60 fps)
        {



            if (event.type == Event::Closed) {  //close the window... stop the game..
                window.close();
                play = false;

            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)  //if enter presss
            {
                enterButton = true;
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter) //if enter release
            {
                enterButton = false;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //if mouse left press
            {
                leftClick = true;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) //if mouse left press
            {
                rightClick = true;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)  //if enter presss
            {
                sButton = true;
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::S) //if enter release
            {
                sButton = false;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)  //if enter presss
            {
                eButton = true;
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::E) //if enter release
            {
                eButton = false;
            }


            if (event.type == Event::MouseMoved) //if mouse moving
            {
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
            }


            if (event.type == Event::Resized)  //if window resized...
            {
                // update the view to the new size of the window
                FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(View(visibleArea));
            }



        }


        //LOGIC


        //mouse point location output.........
        cout << "Mouse X : " << mouseX << " Mouse Y : " << mouseY << endl;  //this showing mouse point location to the console(not in window)


        

        //RENDERING

              //DIVIDING CARD SHOWING........
                /////////////////////////////////////////

        if (enterButton == true || num == 1)
        {
            //  cout << "OKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK" << endl;
            
            num = 1;

            //computer card showing....
            if (mycount < computerCards + 1)
            {
               
                int x2 = xSize / 32;
                int y2 = 0;
                window.draw(rect1);
                window.draw(uno);
              
                for (int i1 = 0; i1 < mycount; i1++)
                {
                    shuffle.play();
                    cards[0].setPosition(x2, y2);
                    x2 = x2 + cxSize;

                    window.draw(cards[0]);

                }
                //user cards showing....
                if (mycount == computerCards)      //My cards showing at the end of dividing(face side)
                {
                    player1.displayCards1(0);
                }
                cards[0].setPosition(xSize / 8, ySize / 4);  //cards[0] means the pile showing(uno card back side)
                window.draw(cards[0]);
                //1st card from pile.....
                cards[carray[14]].setPosition(xSize / 2, ySize / 2); //carray[14] means that the 14th random card taking and showing to the deck(because 1st card get from the pile)
                window.draw(cards[carray[14]]);

                cards[carray[28]].setPosition(xSize / 2, ySize / 2);
                window.draw(cards[carray[28]]);

                window.display();
                mycount = mycount + 1;


            }





        }
        else if (eButton == true)
        {
            return 0;
        }



        //after dividing cards....
        enterButton = false;
        //int outputCard = 0;


        window.draw(uno);


        /////////////////////////////////////CARD CLICKING...........//////////////
        // 1ST CARD Click ///////////
        if (leftClick == true && mouseX > xSize / 32 && mouseX < xSize / 32 + cxSize && mouseY>ySize - cySize && clickCount1 == 0)
        {
            
            clickCard.play();
            
            //1st player 
            clickCount1 = 1;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);

            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);

            }

            selectedCards[selectedCardsCount] = xSize / 32; //selected cards array...
            selectedCardsCount++;
            player1.displayCards(carray[0], selectedCards);  //our card set showing..
            outputCard = carray[0];  //(output from oure card set)to check with next player
            getOut = carray[0];

            player1.removeCard(carray[0]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            /////////////////////////////////////////////////////////////////////////////////////////////////
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }

                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);


            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {

                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                in = 1;

                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw4 cards..
            {

                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }

                //window.display();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////

            window.display();

        }
        // 2ND CARD Click
        else if (leftClick == true && mouseX > xSize / 32 + cxSize && mouseX < xSize / 32 + 2 * cxSize && mouseY>ySize - cySize && clickCount2 == 0)
        {

            clickCard.play();
            //1st player 
            clickCount2 = 1;
            in = 2;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }


            selectedCards[selectedCardsCount] = xSize / 32 + cxSize;
            selectedCardsCount++;
            player1.displayCards(carray[1], selectedCards);  //our card set showing........
            outputCard = carray[1];  //(output from oure card set)to check with next player
            getOut = carray[1];
            player1.removeCard(carray[1]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }

                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }

                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }

                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                in = 1;
                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild drw 4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }

                //window.display();
            }
            window.display();

        }


        // 2-ABOVE THIS.

        //3RD CARD Click
        else if (leftClick == true && mouseX > xSize / 32 + 2 * cxSize && mouseX < xSize / 32 + 3 * cxSize && mouseY>ySize - cySize && clickCount3 == 0)
        {

        clickCard.play();
                //  

                  //1st player 
            clickCount2 = 1;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }

            selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 2;
            selectedCardsCount++;
            player1.displayCards(carray[2], selectedCards);  //our card set showing
            outputCard = carray[2];  //(output from oure card set)to check with next player
            getOut = carray[2];
            player1.removeCard(carray[2]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);

            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                in = 1;
                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild drw4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }
                //window.display();
            }
            window.display();

        }
        //3RD ABOVE THIS
        //4TH CARD Click

        else if (leftClick == true && mouseX > xSize / 32 + 3 * cxSize && mouseX < xSize / 32 + 4 * cxSize && mouseY>ySize - cySize && clickCount4 == 0)
        {
        clickCard.play();

                //  

                  //1st player 
            clickCount4 = 1;
            in = 4;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }

            selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 3;
            selectedCardsCount++;
            player1.displayCards(carray[3], selectedCards);  //our card set showing
            getOut = carray[0];
            outputCard = carray[3];  //(output from oure card set)to check with next player
            player1.removeCard(carray[3]);  //removed that selected card from player(user)

            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                in = 1;

                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild drw4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }
                //window.display();
            }
            window.display();

        }

        //4 ABOVE THIS
        //5TH CARD Click
        else if (leftClick == true && mouseX > xSize / 32 + 4 * cxSize && mouseX < xSize / 32 + 5 * cxSize && mouseY>ySize - cySize && clickCount5 == 0)
        {
        clickCard.play();

                //  

                  //1st player 
            in = 5;
            clickCount5 = 1;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }


            selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 4;
            selectedCardsCount++;
            player1.displayCards(carray[4], selectedCards);  //our card set showing
            outputCard = carray[4];  //(output from oure card set)to check with next player
            getOut = carray[4];
            player1.removeCard(carray[4]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                in = 1;


                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }
                //window.display();
            }
            window.display();

        }
        //5 ABOVE THIS
        //6TH CARD Click
        else if (leftClick == true && mouseX > xSize / 32 + 5 * cxSize && mouseX < xSize / 32 + 6 * cxSize && mouseY>ySize - cySize && clickCount6 == 0)
        {
        clickCard.play();

                //1st player 
            in = 6;
            clickCount6 = 1;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }

            //1st card from pile.....

            //our card set showing.........
            selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 5;
            selectedCardsCount++;
            player1.displayCards(carray[5], selectedCards);
            outputCard = carray[5];  //(output from oure card set)to check with next player
            getOut = carray[5];
            player1.removeCard(carray[5]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }
                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }
            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);

                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                // window.display();
            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);

                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }
                //window.display();
            }
            window.display();

        }
        //6 ABOVE THIS
        //7 CARD Click
        else if (leftClick == true && mouseX > xSize / 32 + 6 * cxSize && mouseX < xSize / 32 + 7 * cxSize && mouseY>ySize - cySize && clickCount7 == 0)
        {

            clickCard.play();
                //1st player 
            in = 7;
            clickCount7 = 1;
            int x2 = xSize / 32;
            int y2 = 0;
            window.draw(rect1);
            window.draw(uno);
            for (int i1 = 0; i1 < computerCards - 1; i1++)
            {
                cards[0].setPosition(x2, y2);
                x2 = x2 + cxSize;
                window.draw(cards[0]);


            }

            //1st card from pile.....
            selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 6;
            selectedCardsCount++;
            player1.displayCards(carray[6], selectedCards);
            getOut = carray[6];
            outputCard = carray[6];  //(output from oure card set)to check with next player
            player1.removeCard(carray[6]);  //removed that selected card from player(user)
            //pile showing card..
            cards[0].setPosition(xSize / 8, ySize / 4);
            window.draw(cards[0]);
            if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
            {
                choosingCard = 1;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)  //if matching card found.........
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 93 || x == 94)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }

                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
            {
                choosingCard = 2;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 97 || x == 98)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }

                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
            {
                choosingCard = 3;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 95 || x == 96)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }

                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                //  window.display();
            }

            else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
            {
                choosingCard = 4;
                int x = player2.searchAndDisplay(choosingCard, outputCard);
                if (x != -1)
                {
                    player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                    computerCards = computerCards - 1;
                    if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 99 || x == 100)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            player1.addCard(carray[pileCurrent]);
                            cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                            userPosition = userPosition + cxSize;
                            window.draw(cards[carray[pileCurrent]]);
                            pileCurrent = pileCurrent + 1;
                        }
                    }
                    else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                    {
                        int randomColorComputer = rand() % 4;
                        if (randomColorComputer == 0)
                        {
                            window.draw(wildBlueC);
                        }
                        else if (randomColorComputer == 1)
                        {
                            window.draw(wildGreenC);
                        }
                        else if (randomColorComputer == 2)
                        {
                            window.draw(wildRedC);
                        }
                        else
                        {
                            window.draw(wildYellowC);
                        }
                    }


                }
                else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
                {
                    if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                    {
                        player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                        pileCurrent = pileCurrent + 1;

                    }
                    else //if doesn't match ,..keep that card......
                    {
                        computerCards = computerCards + 1;
                        pileCurrent = pileCurrent + 1;
                    }
                }
                // window.display();
            }

            else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
            {
                window.draw(reverseCard);


                // window.display();
            }
            else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
            {
                window.draw(skipCard);

            }
            else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
            {
                window.draw(draw2Card);
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
                computerCards = computerCards + 2;
                cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[outputCard]);
            }
            else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
            {
                ///////////llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
                // window.display();
                cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[101]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                in = 1;







            }
            else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw 4 cards..
            {
                cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
                window.draw(cards[105]);
                colorChoose.setFont(font);
                colorChoose.setCharacterSize(30);
                colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
                colorChoose.setPosition(500, 500);
                colorChoose.setFillColor(Color::Yellow);
                window.draw(colorChoose);
                window.draw(col);
                computerCards = computerCards + 4;
                for (int i = 0; i < 4; i++)
                {
                    player2.addCard(carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;
                }

                //window.display();
            }

            window.display();


        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 8TH CARD//////////
        else if (leftClick == true && mouseX > xSize / 32 + 7 * cxSize && mouseX < xSize / 32 + 8 * cxSize && mouseY>ySize - cySize && clickCount7 == 0)
        {

        clickCard.play();
        //1st player 
        in = 7;
        clickCount7 = 1;
        int x2 = xSize / 32;
        int y2 = 0;
        window.draw(rect1);
        window.draw(uno);
        for (int i1 = 0; i1 < computerCards - 1; i1++)
        {
            cards[0].setPosition(x2, y2);
            x2 = x2 + cxSize;
            window.draw(cards[0]);


        }

        //1st card from pile.....
        selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 6;
        selectedCardsCount++;
        player1.displayCards(carray[6], selectedCards);
       
        outputCard = carray[pileCurrent];  //(output from oure card set)to check with next player
        player1.removeCard(carray[pileCurrent]);  //removed that selected card from player(user)
        //pile showing card..
        cards[0].setPosition(xSize / 8, ySize / 4);
        window.draw(cards[0]);
        if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
        {
            choosingCard = 1;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)  //if matching card found.........
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 93 || x == 94)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
        {
            choosingCard = 2;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 97 || x == 98)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
        {
            choosingCard = 3;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 95 || x == 96)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
        {
            choosingCard = 4;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 99 || x == 100)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }


            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
        {
            window.draw(reverseCard);


            // window.display();
        }
        else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
        {
            window.draw(skipCard);

        }
        else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
        {
            window.draw(draw2Card);
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            computerCards = computerCards + 2;
            cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[outputCard]);
        }
        else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
        {
            ///////////llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
            // window.display();
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            in = 1;







        }
        else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw 4 cards..
        {
            cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[105]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            computerCards = computerCards + 4;
            for (int i = 0; i < 4; i++)
            {
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
            }

            //window.display();
        }

        window.display();


        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 9TH CARD
        else if (leftClick == true && mouseX > xSize / 32 + 8 * cxSize && mouseX < xSize / 32 + 9 * cxSize && mouseY>ySize - cySize && clickCount7 == 0)
        {

        clickCard.play();
        //1st player 
        in = 7;
        clickCount7 = 1;
        int x2 = xSize / 32;
        int y2 = 0;
        window.draw(rect1);
        window.draw(uno);
        for (int i1 = 0; i1 < computerCards - 1; i1++)
        {
            cards[0].setPosition(x2, y2);
            x2 = x2 + cxSize;
            window.draw(cards[0]);


        }

        //1st card from pile.....
        selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 6;
        selectedCardsCount++;
        player1.displayCards(carray[6], selectedCards);
        
        outputCard = carray[pileCurrent];  //(output from oure card set)to check with next player
        player1.removeCard(carray[pileCurrent]);  //removed that selected card from player(user)
        //pile showing card..
        cards[0].setPosition(xSize / 8, ySize / 4);
        window.draw(cards[0]);
        if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
        {
            choosingCard = 1;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)  //if matching card found.........
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 93 || x == 94)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
        {
            choosingCard = 2;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 97 || x == 98)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
        {
            choosingCard = 3;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 95 || x == 96)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
        {
            choosingCard = 4;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 99 || x == 100)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }


            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
        {
            window.draw(reverseCard);


            // window.display();
        }
        else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
        {
            window.draw(skipCard);

        }
        else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
        {
            window.draw(draw2Card);
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            computerCards = computerCards + 2;
            cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[outputCard]);
        }
        else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
        {
            ///////////llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
            // window.display();
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            in = 1;







        }
        else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw 4 cards..
        {
            cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[105]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            computerCards = computerCards + 4;
            for (int i = 0; i < 4; i++)
            {
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
            }

            //window.display();
        }

        window.display();


        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //10 th card.
        else if (leftClick == true && mouseX > xSize / 32 + 9 * cxSize && mouseX < xSize / 32 + 10 * cxSize && mouseY>ySize - cySize && clickCount7 == 0)
        {

        clickCard.play();
        //1st player 
        in = 7;
        clickCount7 = 1;
        int x2 = xSize / 32;
        int y2 = 0;
        window.draw(rect1);
        window.draw(uno);
        for (int i1 = 0; i1 < computerCards - 1; i1++)
        {
            cards[0].setPosition(x2, y2);
            x2 = x2 + cxSize;
            window.draw(cards[0]);


        }

        //1st card from pile.....
        selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 6;
        selectedCardsCount++;
        player1.displayCards(carray[6], selectedCards);
       
        outputCard = carray[pileCurrent];  //(output from oure card set)to check with next player
        player1.removeCard(carray[pileCurrent]);  //removed that selected card from player(user)
        //pile showing card..
        cards[0].setPosition(xSize / 8, ySize / 4);
        window.draw(cards[0]);
        if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
        {
            choosingCard = 1;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)  //if matching card found.........
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 93 || x == 94)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
        {
            choosingCard = 2;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 97 || x == 98)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
        {
            choosingCard = 3;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 95 || x == 96)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
        {
            choosingCard = 4;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 99 || x == 100)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }


            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
        {
            window.draw(reverseCard);


            // window.display();
        }
        else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
        {
            window.draw(skipCard);

        }
        else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
        {
            window.draw(draw2Card);
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            computerCards = computerCards + 2;
            cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[outputCard]);
        }
        else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
        {
            ///////////llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
            // window.display();
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            in = 1;







        }
        else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw 4 cards..
        {
            cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[105]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            computerCards = computerCards + 4;
            for (int i = 0; i < 4; i++)
            {
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
            }

            //window.display();
        }

        window.display();


        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //11th card
        else if (leftClick == true && mouseX > xSize / 32 + 6 * cxSize && mouseX < xSize / 32 + 7 * cxSize && mouseY>ySize - cySize && clickCount7 == 0)
        {

        clickCard.play();
        //1st player 
        in = 7;
        clickCount7 = 1;
        int x2 = xSize / 32;
        int y2 = 0;
        window.draw(rect1);
        window.draw(uno);
        for (int i1 = 0; i1 < computerCards - 1; i1++)
        {
            cards[0].setPosition(x2, y2);
            x2 = x2 + cxSize;
            window.draw(cards[0]);


        }

        //1st card from pile.....
        selectedCards[selectedCardsCount] = selectedCards[selectedCardsCount] = xSize / 32 + cxSize * 6;
        selectedCardsCount++;
        player1.displayCards(carray[6], selectedCards);
        getOut = carray[6];
        outputCard = carray[6];  //(output from oure card set)to check with next player
        player1.removeCard(carray[pileCurrent]);  //removed that selected card from player(user)
        //pile showing card..
        cards[0].setPosition(xSize / 8, ySize / 4);
        window.draw(cards[0]);
        if (outputCard >= blueStartNum && outputCard <= blueEndNum)  //blue numbers
        {
            choosingCard = 1;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)  //if matching card found.........
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 93 || x == 94)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard >= yellowStartNum && outputCard <= yellowEndNum) //yellow numbers
        {
            choosingCard = 2;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 97 || x == 98)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= redStartNum && outputCard <= redEndNum) //red numbers
        {
            choosingCard = 3;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 95 || x == 96)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }

            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            //  window.display();
        }

        else if (outputCard >= greenStartNum && outputCard <= greenEndNum) //green numbers
        {
            choosingCard = 4;
            int x = player2.searchAndDisplay(choosingCard, outputCard);
            if (x != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
                if (x == 105 || x == 106 || x == 107 || x == 108) //if computer put draw 4
                {
                    for (int i = 0; i < 4; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 99 || x == 100)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        player1.addCard(carray[pileCurrent]);
                        cards[pileCurrent].setPosition(userPosition, ySize - cySize);
                        userPosition = userPosition + cxSize;
                        window.draw(cards[carray[pileCurrent]]);
                        pileCurrent = pileCurrent + 1;
                    }
                }
                else if (x == 101 || x == 102 || x == 103 || x == 104) //if computer put wild card....
                {
                    int randomColorComputer = rand() % 4;
                    if (randomColorComputer == 0)
                    {
                        window.draw(wildBlueC);
                    }
                    else if (randomColorComputer == 1)
                    {
                        window.draw(wildGreenC);
                    }
                    else if (randomColorComputer == 2)
                    {
                        window.draw(wildRedC);
                    }
                    else
                    {
                        window.draw(wildYellowC);
                    }
                }


            }
            else  //if not found..........(get from the pile and if match, then put it , else keep it.......)
            {
                if (player2.searchAndDisplay(choosingCard, carray[pileCurrent]) != -1)  //if matches with the pile drawen card.....
                {
                    player2.searchAndDisplay(choosingCard, carray[pileCurrent]);
                    pileCurrent = pileCurrent + 1;

                }
                else //if doesn't match ,..keep that card......
                {
                    computerCards = computerCards + 1;
                    pileCurrent = pileCurrent + 1;
                }
            }
            // window.display();
        }

        else if (outputCard == greenRev1 || outputCard == greenRev2 || outputCard == redRev1 || outputCard == redRev2 || outputCard == yellowRev1 || outputCard == yellowRev2 || outputCard == blueRev1 || outputCard == blueRev2) //green action cards( reverse)...
        {
            window.draw(reverseCard);


            // window.display();
        }
        else if (outputCard == greenSkip1 || outputCard == greenSkip2 || outputCard == redSkip1 || outputCard == redSkip2 || outputCard == yellowSkip1 || outputCard == yellowSkip2 || outputCard == blueSkip1 || outputCard == blueSkip2) //skip...
        {
            window.draw(skipCard);

        }
        else if (outputCard == greenDraw21 || outputCard == greenDraw22 || outputCard == redDraw21 || outputCard == redDraw22 || outputCard == yellowDraw21 || outputCard == yellowDraw22 || outputCard == blueDraw21 || outputCard == blueDraw22)  //green draw2...
        {
            window.draw(draw2Card);
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            player2.addCard(carray[pileCurrent]);
            pileCurrent = pileCurrent + 1;
            computerCards = computerCards + 2;
            cards[outputCard].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[outputCard]);
        }
        else if (outputCard >= wildStart && outputCard <= wildEnd) //wild cards..
        {
            ///////////llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
            // window.display();
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            in = 1;







        }
        else if (outputCard >= wildDraw4Start && outputCard <= wildDraw4End) //wild draw 4 cards..
        {
            cards[105].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[105]);
            colorChoose.setFont(font);
            colorChoose.setCharacterSize(30);
            colorChoose.setString("Choose a color to play next player(Press G-Green or Y-Yellow or B-Blue or R-Red)");
            colorChoose.setPosition(500, 500);
            colorChoose.setFillColor(Color::Yellow);
            window.draw(colorChoose);
            window.draw(col);
            computerCards = computerCards + 4;
            for (int i = 0; i < 4; i++)
            {
                player2.addCard(carray[pileCurrent]);
                pileCurrent = pileCurrent + 1;
            }

            //window.display();
        }

        window.display();


        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (rightClick == true && mouseX > 500 && mouseX < 552 && mouseY>500 && mouseY < 573 && in == 1)
        {
            
            checkButton = 1;
            choosingCard = 11;
            if (player2.searchAndDisplay(choosingCard, outputCard) != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
            }
            // player1.displayCards(getOut);
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            // player1.displayCardsWild(getOut);
            // player1.removeCard(getOut);
            in = 0;
            window.display();

        }
        else if (rightClick == true && mouseX > 500 && mouseX < 552 && mouseY>573 && mouseY < 646 && in == 1)
        {
        
            checkButton = 2;
            choosingCard = 10;
            if (player2.searchAndDisplay(choosingCard, outputCard) != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
            }
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            // player1.displayCardsWild(getOut);
            // player1.removeCard(getOut);
            in = 0;
            window.display();


        }
        else if (rightClick == true && mouseX > 552 && mouseX < 604 && mouseY>573 && mouseY < 646 && in == 1)
        {
           
            checkButton = 3;
            choosingCard = 9;
            if (player2.searchAndDisplay(choosingCard, outputCard) != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;
            }
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            in = 0;
            //player1.displayCardsWild(getOut);
           // player1.removeCard(getOut);
            window.display();

        }
        else if (rightClick == true && mouseX > 552 && mouseX < 604 && mouseY>500 && mouseY < 573 && in == 1)
        {
           
            // checkButton = 4;
            choosingCard = 12;
            if (player2.searchAndDisplay(choosingCard, outputCard) != -1)
            {
                player2.removeCard(player2.searchAndDisplay(choosingCard, outputCard));
                computerCards = computerCards - 1;




            }
            cards[101].setPosition(xSize / 2 - 100, ySize / 2 - 100);
            window.draw(cards[101]);
            in = 0;

            //player1.displayCardsWild(getOut);
           // player1.removeCard(getOut);
            window.display();

        }
        else if (leftClick == true && mouseX > xSize / 8 && mouseX < xSize / 8 + cxSize && mouseY>ySize / 4 && mouseY < ySize / 4 + cySize) //if pile clicking...
        {
            
            player1.displayCards(pileCurrent, selectedCards);

            cards[carray[pileCurrent]].setPosition(userPosition, ySize - cySize);
            player1.addCard(carray[pileCurrent]);
            window.draw(cards[carray[pileCurrent]]);
            pileCurrent = pileCurrent + 1;
            userPosition = userPosition + cxSize;
            window.display();
        }

        else if (sButton == true)
        {
            unoClick.play();
            Text playerScore;
            playerScore.setFont(font);
            playerScore.setCharacterSize(80);
            playerScore.setString("YOUR SCORE");
            playerScore.setPosition(550, 300);
            playerScore.setFillColor(Color::Magenta);
            window.draw(playerScore);
            window.display();
            //stopRound = 1;



        }
        else if (eButton == true)
        {
            return 0;
        }
        sButton = false;
        leftClick = false;
        rightClick = false;



    }

    //clean up
    window.close();
    return 0;
}