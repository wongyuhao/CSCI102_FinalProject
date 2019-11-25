#include "Recipe.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	while (true) {
		cout << "Recipe Book v1.0\n\n"
			<< "[1] View Recipes\n"
			<< "[2] Enter New Recipe\n"
			<< "[3] Exit\n\n";

		cout << "Please enter the number beside your selection:\n";

		int selection;
		cin >> selection;
		cout << '\n';

		validate(selection, 0, 3);

		switch (selection) {
		case 1:
			viewRecipes();
			break;
		case 2:
			addRecipe();
			break;
		case 3:
			cout << "Exiting...\n";
			return 0;
		default:
			cerr << "Unexpected error in recipe_main.cpp: main()\n";
			return 0;
		}
	}
}



