/*****************************
* Recipe Book Program:
* This program allows the users to enter details 
* of recipes, including name, calories, all ingredients
* and all steps to make the recipe.
*
* It can also load recipes from a txt file and save them
* to a txt file as well.
*
* The goal of this program is to preserve the heritage of cooking
* by storing traditional recipes easily, so that they can be passed 
* on to future generations without being destroyed on paper.
*/



#include "Recipe.h"
#include <iostream>
using namespace std;

int main() {
	while (true) {  //while loop allows user to loop back to main menu during the program
		
		cout << "Recipe Book v1.0\n\n"
			<< "[1] View Recipes\n"
			<< "[2] Enter New Recipe\n"
			<< "[3] Save\n"
			<< "[4] Load\n"
			<< "[0] Exit\n\n";			

		cout << "Please enter the number beside your selection:\n";

		int selection;
		cin >> selection; //read menu selection from user
		cout << '\n';

		validate(selection, 0, 4); //validate if user input is within range for this menu

		switch (selection) { //open a menu or a function based on the user's selection
		case 1:
			viewRecipes(); //calls function thath opens the view recipe menu
			break;
		case 2:
			addRecipe(); //calls function that prompts user for recipe details
			break;
		case 3:
			save(); //saves all current recipes to a .txt file in specific directory
			break;
		case 4:
			load(); //reads.txt file from a specific directory and copies recipes into the program
			break;
		case 0:
			cout << "Exiting...\n"; //exits the progam
			return 0;
		default:
			cerr << "Unexpected error in recipe_main.cpp: main()\n"; //catches an error if there is unexpected input
			return 0;
		}
	}
}



