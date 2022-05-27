#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../header/item.hpp"
#include "../header/archetypes.hpp"
#include "../header/bag.hpp"
#include "../header/combat.hpp"
#include "../header/entity.hpp"
#include "../header/player.hpp"
#include "../header/item.hpp"
#include "../header/Enemies/Boss.hpp"
#include "../header/Enemies/Minion.hpp"
#include "../header/Enemies/Enemy.hpp"
#include "../header/Weapon/weapon.hpp"

using namespace std;

Player* archetype_choice();
void story(Player*, Bag);
void print_base_stats(Bag);
void print_level_up(Bag);
void print_paths();
Enemy* check_enemy(string, int);

const int size = 4;
const int size_prompt = 3;
const string prompt[10] = {
    "You have defeated your first enemy and continue to explore the dungeon. There appears a dimly lit path to the left and a shiny path to the right. Which one will you explore? (l/r)",
    "You continue to survey the eerie dungeon and come across another set of paths. One with loud sounds and another with mist. Which one will you partake? in (l/r)",
    "As you get deeper into the dungeon, an additional pair of left and right paths come into your vision. Both paths radiating an immense pressure. Choose carefully. (l/r)",
};

//Using i*2+1 to access left child and i*2+2 to access right child
const string choices[100] = {
    "You have entered the infamous dungeon and as you traverse the dungeon you stumble across 2 dark paths to the left and to the right. Which one will you choose? (l/r)", 
    "You have chosen the left path and you hear a faint shhhhhh sound", //Goblin
    "You have decided to take the right path and you see something jumping", //Slime
    //2nd Level
    "You explore the left path and realize that you are hungry. Coincidently, a medium-sized chicken approaches you, but something bizarre occurs", //Chicken
    "You decided to venture the right path. As you keep surveilling you feel an immense presence and something running towards you", //Goblin
    "You have chosen the left path and you feel a small shake as if something heavy was jumping", //Slime
    "You chose to proceed to the right path and you yearn for some food. A chicken walks up to you", //Chicken
    //3rd Level
    "Upon exploring the left path, you realize that this dungeon ain't too bad aside from the chicken. You then hear a bouncing, slimy sound", //Slime
    "While traversing the right path, you stumble across a natural, rocky slide. As you slide down deeper into the dungeon, a goblin jumps from the shadows", //Goblin
    "As you continue to investigate the dungeon, you see something flapping its wings and fall gracefully", //Chicken
    "You decided to investigate the right path. As you wonder why there are only 2 paths throughout the dungeon, a goblin leaps from the shadows", //Goblin
    "You think to yourself that the dungeon is a piece of cake as you explore the left path. Then a something fat that is jumping comes into sight", //Slime
    "You decided to venture the right path in which you hear a bawk bawk sound", //Chicken
    "Decidingly, you inspect the left path and are immediately with a sole goblin", //Goblin
    "You chose to proceed to the right path. As you keep inspecting, you see a cluster of small slimes that merge", //Slime
}; 




int main()
{
    system("clear");
    string anyKey;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "|                                                 |" << endl;
    cout << "|               Gary Goomba's Dungeon             |" << endl;
    cout << "|                                                 |" << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << endl;
    while(anyKey != "1" && anyKey != "2") {
        cout << "Menu:\n[1] Play\n[2] Exit" << endl;
        cout << ">";
        cin >> anyKey;
        if(anyKey == "1") break;
        else if(anyKey == "2") exit(0);
        else cout << "Sorry that is an invalid option, please type '1' to play and '2' to quit" << endl;
    }

    system("clear");
    
    Player* adventurer = archetype_choice();
    Bag inventory(adventurer);

    cout << "Press any key and enter to continue . . ." << endl;
    cin >> anyKey;
    system("clear");

    story(adventurer, inventory);

    return 0;

}

Player* archetype_choice() {
    string choice;
    Player* adventurer;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "|               Archetypes                |" << endl;
    cout << "|                                         |" << endl;
    cout << "|  [1] Barbarian           [2] Wizard     |" << endl;
    cout << "|  [3] Archer              [4] Cleric     |" << endl;
    cout << "|              [5] Paladin                |" << endl;
    cout << "|                                         |" << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << endl;
    while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5") {
        cout << "Select the Archetype of your liking" << endl;
        cout << "> ";
	cin >> choice;
        cout << endl;
        if(choice == "1") {
	    cout << "You have selected the Barbarian class!" << endl;
            adventurer = new Barbarian();
        }
	else if(choice == "2") {
	    cout << "You have selected the Wizard class!" << endl;
            adventurer = new Wizard();
        }
        else if(choice == "3") {
	    cout << "You have selected the Archer class!" << endl;
            adventurer = new Archer();
        }

        else if(choice == "4") {
	    cout << "You have selected the Cleric class!" << endl;
            adventurer = new Cleric();
        }

        else if(choice == "5") {
	    cout << "You have selected the Paladin class!" << endl;
            adventurer = new Paladin();
        }
        else {
            cout << "Sorry that's not a valid choice, please type in the number corresponding to the archetype" << endl;
	}


        if(choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") { //Confirms if the player wants the selected class after base stats and starter weapons stats print
            Bag inventory(adventurer);
            cout << "Your archetype's base stats:" << endl;
            print_base_stats(inventory); 
            cout << "Your starter weapon:" << endl;
            cout << adventurer->getWeapon()->printStats() << endl;
            cout << endl;
            while(choice != "y" || choice != "n") {
                cout << "Are you sure you want the " << adventurer->getArchetype() << " class? Yes (y) or No (n)" << endl;
                cout << "> ";
                cin >> choice;
                if(choice == "y") {
	            return adventurer;
	        }
                else if(choice == "n") {
		    break;
	        }
                else {
		    cout << "Sorry that is not a valid option, type in 'y' for Yes and 'n' for No" << endl;
		}
            }
	}
    }
}

void story(Player* adventurer, Bag inventory) {
    string decision = "";
    string anyKey;
    
    int fightCounter = 0; //Level up after 1 fight, then level up after 2 fights, and so on
    int levelTrigger = 1;
    int promptCounter = 0;

    dmgpot dmg("strength potion", "When taken the user feels a slight boost to their muscles", 1);
    healthpot heal("healing potion", "When taken, a small angel pops out and sings a song", 1);
    inventory.add(&heal);

    cout << choices[0] << endl;
	
    for(unsigned int i = 0; i < size;) {
	while(decision != "l" && decision != "r") {
            cout << "> ";
	    cin >> decision;
	    if(decision == "l") {
	        i = i * 2 + 1;
                cout << choices[i] << endl;
                cout << endl;
	        combat fight(&inventory, check_enemy(choices[i], adventurer->getLevel()), &dmg);
                fight.printStats();
                fight.start("You have encountered an enemy!");
                inventory.add(&dmg);         
                fightCounter++;

	    }
	    else if(decision == "r") {
                 cout << choices[i] << endl;
                 cout << endl;
		 combat fight_two(&inventory, check_enemy(choices[i], adventurer->getLevel()), &heal);
                 fight_two.printStats();
                 cout << endl;
		 fight_two.start("An enemy jumps you!");       
                 inventory.add(&heal);
                 fightCounter++;
	    }
	    else {
		 cout << "Sorry that's not a valid choice, please type in 'l' for left or 'r' for right" << endl;
	    }
        }
        if(levelTrigger == fightCounter) {
	    print_level_up(inventory);
            levelTrigger++;
            fightCounter = 0;
        }       
        cout << "Press any key to continue and enter . . ." << endl;
        cin >> anyKey;
        system("clear");
        cout << prompt[promptCounter] << endl;
        promptCounter++;
        cin.ignore();
        decision = "";
    }
}

void print_base_stats(Bag inventory) {
    cout << "Health: " <<  inventory.getplayer()->getCurrHealth() << "/" << inventory.getplayer()->getMaxHealth() << endl;
    cout << "Attack: " << inventory.getplayer()->getAttack() << endl;
    cout << "Defense: " << inventory.getplayer()->getDefense() << endl; 
    cout << "Crit Rate: " << inventory.getplayer()->getCritRate() << endl;
}

void print_level_up(Bag inventory) {
    cout << "----------------------------------------" << endl;
    cout << "| Congratulations, you gained 2 levels! |" << endl; 
    cout << "----------------------------------------" << endl;
    print_base_stats(inventory);
    inventory.getplayer()->levelUp(2);
    cout << "      ↓      " << endl;
    print_base_stats(inventory);
}

//Makes and returns an enemy based on the choice the user made, that has the same level as the player
Enemy* check_enemy(string narrative, int level) {
    if(narrative.find("shh") != -1 || narrative.find("run") != -1 || narrative.find("goblin") != -1) {
	Enemy* goblin = new GoblinMinion(level-1);
        return goblin;
    }
    else if(narrative.find("jump") != -1 || narrative.find("slimy") != -1) {
	Enemy* slime = new SlimeMinion(level-1);
        return slime;
    }
    else {
	Enemy* chicken = new ChickenMinion(level-1);
        return chicken;
    }

}






