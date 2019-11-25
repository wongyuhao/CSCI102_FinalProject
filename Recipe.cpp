#include "Recipe.h"
#include <iostream>
#include <vector>
#include <iomanip>	
#include <algorithm>
#include <string>
#include <cctype>

//a vector of recipes
vector<Recipe> recipeVector;

Recipe::Recipe(string n, int c, vector<string> in, vector<string> st) {
	cout << "Recipe Created!\n";

	setName(n);
	setCalories(c);
	setIngredients(in);
	setSteps(st);
}

//setter function implementation
void Recipe::setName(string n) {
	name = n;
}
void Recipe::setCalories(int c) {
	calories = c;
}
void Recipe::setIngredients(vector<string> in) {
	ingredients = in;
}
void Recipe::setSteps(vector<string> st) {
	steps = st;
}

//getter function implementation
string Recipe::getName() {
	return name;
}
int Recipe::getCalories() {
	return calories;
}
int Recipe::getNumIngredients() {
	return ingredients.size();
}
int Recipe::getNumSteps() {
	return steps.size();
}

//print function
void Recipe::printRecipe() {
	cout << setfill('-') << setw(20) << endl;
	cout << "Recipe Name: " << name << endl;

	cout << "Calories (kcal): " << calories << endl;

	cout << "Ingredients list:\n";
	for (int i = 0; i < ingredients.size(); i++) {
		cout <<(i+1)<<". "<< ingredients[i] << endl;
	}

	cout << "Steps list:\n";
	for (int i = 0; i < steps.size(); i++) {
		cout << (i + 1) << ". " << steps[i] << endl;
	}

}

//view recipe menu function
void viewRecipes() {
	if (recipeVector.empty()) {
		cout << "No recipes found.\n\n";
		return;
	}

	cout << "Sort recipes by:\n"
		<< "[0] Back\n"
		<< "[1] Time entered\n"
		<< "[2] Name\n"
		<< "[3] Calories\n"
		<< "[4] Number of ingredients\n"
		<< "[5] Number of steps\n\n";

	cout << "Please enter the number beside your selection:\n";

	int selection;
	cin >> selection;
	cout << '\n';

	validate(selection, 0, 5);

	vector<Recipe> recipeVectorSorted = recipeVector;

	switch (selection)
	{
	case 0:
		return;
		break;
	case 1:
		viewRecipesByTime(recipeVectorSorted);
		break;
	case 2:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByName);
		viewRecipesByName(recipeVectorSorted);
		break;
	case 3:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByCalories);
		viewRecipesByCalories(recipeVectorSorted);
		break;
	case 4:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByIngredients);
		viewRecipesByIngredients(recipeVectorSorted);
		break;
	case 5:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeBySteps);
		viewRecipesBySteps(recipeVectorSorted);
		break;
	default:
		cerr << "Unexpected error in recipe_definitions.cpp: viewRecipes(): printing sorted recipe list\n";
		return;
	}

	cout << "Select an option:\n"
		<< "[0] Main menu\n"
		<< "[1-" << recipeVectorSorted.size() << "] View selected recipe\n\n";

	cin >> selection;
	validate(selection, 0, recipeVectorSorted.size());

	if (selection == 0) {
		return;
	}
	recipeVectorSorted[selection - 1].printRecipe();

	cout << "Select an option:\n"
		<< "[0] Main menu\n\n";

	cin >> selection;
	validate(selection, 0, 0);

	switch (selection) {
	case 0:
		return;
		break;
	default:
		cerr << "Unexpected error in recipe_definitions.cpp: viewRecipes(): printed recipe details\n";
		return;
	}
}

// helper- compare functions
bool cmpRecipeByName(Recipe a, Recipe b) {
	return a.getName() < b.getName();
}
bool cmpRecipeByCalories(Recipe a, Recipe b) {
	if (a.getCalories() != b.getCalories()) return a.getCalories() < b.getCalories();
	return a.getName() < b.getName();
}
bool cmpRecipeByIngredients(Recipe a, Recipe b) {
	if (a.getNumIngredients() != b.getNumIngredients()) return a.getNumIngredients() < b.getNumIngredients();
	return a.getName() < b.getName();
}
bool cmpRecipeBySteps(Recipe a, Recipe b) {
	if (a.getNumSteps() != b.getNumSteps()) return a.getNumSteps() < b.getNumSteps();
	return a.getName() < b.getName();
}

//helper- view_sort functions
void viewRecipesByTime(vector<Recipe>& temp) {
	cout << "All recipes sorted by time entered:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByName(vector<Recipe>& temp) {
	cout << "All recipes sorted by name:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByCalories(vector<Recipe>& temp) {
	cout << "All recipes sorted by calories:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << "[" << temp[i].getCalories() << " kcal] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByIngredients(vector<Recipe>& temp) {
	cout << "All recipes sorted by number of ingredients:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". [" << temp[i].getNumIngredients() << " ingredient(s)] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesBySteps(vector<Recipe>& temp) {
	cout << "All recipes sorted by number of steps:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". [" << temp[i].getNumSteps() << " step(s)] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}

//validate that selection is between l and r, inclusive
void validate(int& selection, int l, int r) {
	while (selection < l || selection > r) {
		cout << "Invalid response.\n"
			<< "Please enter the number beside your selection:\n";
		cin >> selection;
		cout << '\n';
	}
}

//add recipe function
void addRecipe() {
	while (true) {
		string temp_name;
		vector<string> temp_ingredients;
		string temp_ingredient;
		vector<string> temp_steps;
		string temp_step;
		int temp_calories;

		cout << "Enter name: ";
		cin.ignore();
		getline(cin, temp_name);

		cout << "Enter calories: ";
		cin >> temp_calories;

		cout << "Enter all ingredients in this recipe. Enter '0' to stop.\n";
		cin.ignore();
		while (true) {
			cout << temp_ingredients.size() + 1 << ". ";
			getline(cin, temp_ingredient);
			if (temp_ingredient == "0") {
				break;
			}
			else {
				temp_ingredients.push_back(temp_ingredient);
			}
		}

		cout << "Enter all steps for this recipe. Enter '0' to stop.\n";
		while (true) {
			cout << temp_steps.size() + 1 << ". ";
			getline(cin, temp_step);
			if (temp_step == "0") {
				break;
			}
			else {
				temp_steps.push_back(temp_step);
			}
		}

		Recipe temp_recipe(temp_name, temp_calories, temp_ingredients, temp_steps);
		recipeVector.push_back(temp_recipe);

		cout << "Add another recipe? (Y/N)\n";
		char poll;
		cin >> poll;

		while (tolower(poll) != 'y' && tolower(poll) != 'n') {
			cout << "Invalid response.\n"
				<< "Add another recipe? (Y/N)\n";
			cin >> poll;
		}

		if (tolower(poll) == 'n') {
			break;
		}
	}
}