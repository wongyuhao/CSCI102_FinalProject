#include "Recipe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>	
#include <algorithm>
#include <string>
#include <cctype>

//a vector to store all recipes as objects of type Recipe
vector<Recipe> recipeVector;

//constructor for class Recipe 
Recipe::Recipe(string n, int c, vector<string> in, vector<string> st) {
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
vector<string>& Recipe::getIngredients() {
	return ingredients;
}
vector<string>& Recipe::getSteps() {
	return steps;
}

//prints all details of the recipe
void Recipe::printRecipe() {
	cout << "--------------------" << endl;
	cout << "Recipe Name: " << name << endl;

	cout << "Calories (kcal): " << calories << endl;

	//for loop to print all elements in the ingredients vector of the object
	cout << "\nIngredients list:\n";
	for (int i = 0; i < ingredients.size(); i++) {
		cout << (i+1) << ". " << ingredients[i] << endl;
	}

	//for loop to print all elements in the steps vector of the object
	cout << "\nSteps list:\n";
	for (int i = 0; i < steps.size(); i++) {
		cout << (i+1) << ". " << steps[i] << endl;
	}
	
	cout << "--------------------" << endl;
}

//function that displays a menu to view recipes
void viewRecipes() {
	//if there is no recipe, prompt the user to return to main menu
	if (recipeVector.empty()) {
		cout << "No recipes found.\n\n";
		cout << "Select an option:\n"
			<< "[0] Main menu\n\n";
		
		cout << "Please enter the number beside your selection:\n";
		
		int selection;
		cin >> selection;			//read and validate user's input
		validate(selection, 0, 0);
		
		cout << '\n';
		return;
	}
	
	//print options to sort the recipes
	cout << "Sort recipes by:\n"
		<< "[1] Time entered\n"
		<< "[2] Name\n"
		<< "[3] Calories\n"
		<< "[4] Number of ingredients\n"
		<< "[5] Number of steps\n"
		<< "[0] Back\n\n";

	cout << "Please enter the number beside your selection:\n";
	
	int selection;
	cin >> selection;
	cout << '\n';

	validate(selection, 0, 5); //read and validate user's input
	
	//create a copy of the original vector to be sorted
	vector<Recipe> recipeVectorSorted = recipeVector;

	//based on the user's selection, sort the copied vector in a specific way
	switch (selection)
	{
	case 0:

		cout << '\n';
		return;
		break;
	case 1:
		// "sort by time" - does not sort vector, keeps it in chronological order
		viewRecipesByTime(recipeVectorSorted);
		break;
	case 2:
		// "sort by name" - uses a helper compare function to sort by the name attribute 
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByName);\
		// prints a list of all recipes in the sorted vector
		viewRecipesByName(recipeVectorSorted);
		break;
	case 3:
		//"sort by calories" - uses a helper compare function to sort by the calorie attribute 
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByCalories);
		// prints a list of all recipes in the sorted vector
		viewRecipesByCalories(recipeVectorSorted);
		break;
	case 4:
		//"sort by ingredients" - uses a helper compare function to sort by the number of ingredients in the object's ingredient vector 
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByIngredients);
		// prints a list of all recipes in the sorted vector
		viewRecipesByIngredients(recipeVectorSorted);
		break;
	case 5:
		//"sort by steps" - uses a helper compare function to sort by the number of steps in the object's steps vector
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeBySteps);
		// prints a list of all recipes in the sorted vector
		viewRecipesBySteps(recipeVectorSorted);
		break;
	default:
		cerr << "Unexpected error in recipe_definitions.cpp: viewRecipes(): printing sorted recipe list\n";
		return;
	}
	
	//prompt the user to view the details of 1 recipe or return to main menu
	cout << "Select an option:\n"
		<< "[1-" << recipeVectorSorted.size() << "] View selected recipe\n"
		<< "[0] Main menu\n\n";
		
	cout << "Please enter the number beside your selection:\n";

	cin >> selection;
	validate(selection, 0, recipeVectorSorted.size()); // validates the user's input, upper range of valid values is the number of recipes in the recipe vector

	if (selection == 0) {
		cout << '\n';
		return;
	}
	
	//print the selected recipe
	recipeVectorSorted[selection - 1].printRecipe();

	//prompt the user to return to main menu (continue)
	cout << "Select an option:\n"
		<< "[0] Continue\n\n";
		
	cout << "Please enter the number beside your selection:\n";
	
	cin >> selection;
	validate(selection, 0, 0);
}

// helper - compare functions
// returns true if the value of the first element is smaller than the second element
// used in sort() function above
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

//helper - view_sort functions
// uses a for loop to print the name of each recipe
// the sorted vector is passed to this function by reference to conserve memory and avoid making a copy
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
		cout << "\nInvalid response.\n"
			<< "Please enter the number beside your selection:\n";
		cin >> selection;
		cout << '\n';
	}
}

//add recipe function
void addRecipe() {
	while (true) { // while block allow users to continue adding more recipes if needed
		// creates temporary variables to store user input 
		string temp_name;
		vector<string> temp_ingredients;
		string temp_ingredient;
		vector<string> temp_steps;
		string temp_step;
		int temp_calories;

		//prompt user for name of recipe
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, temp_name);

		//prompt user for calories of recipe
		cout << "Enter calories: ";
		cin >> temp_calories;

		//prompts user to enter all ingredients of the recipe
		cout << "Enter all ingredients in this recipe. Enter '0' to stop.\n";
		cin.ignore();
		while (true) { // while user has not entered the sentinel value
			cout << temp_ingredients.size() + 1 << ". ";
			getline(cin, temp_ingredient); // allow user to add ingredient
			if (temp_ingredient == "0") { // if input == sentiel value, end the loop
				break;
			}
			else { 
				// add the user's input to the vector that stores all ingredients of that recipe
				temp_ingredients.push_back(temp_ingredient);
			}
		}

		//prompts user to enter all steps of the recipe
		cout << "Enter all steps for this recipe. Enter '0' to stop.\n";
		while (true) {// while user has not entered the sentinel value
			cout << temp_steps.size() + 1 << ". ";
			getline(cin, temp_step); // allow user to add ingredient
			if (temp_step == "0") { // if input == sentiel value, end the loop
				break;
			}
			else {
				// add the user's input to the vector that stores all steps of that recipe
				temp_steps.push_back(temp_step);
			}
		}

		//creates a temporary object using the temporary variables
		Recipe temp_recipe(temp_name, temp_calories, temp_ingredients, temp_steps);
		// stores that object into the main recipe vector
		recipeVector.push_back(temp_recipe);
		// temp_recipe object will be destroyed upon exiting this iteration, so the next iteration will create a new object

		cout << "Recipe Created!\n";
		cout << "Add another recipe? (Y/N)\n";
		char poll;
		cin >> poll;

		//prompt the user to either add another recipe or stop
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

// saves all current recipes to a .txt file
void save(){
	int saveCount = 0;	//number of save files
	
	//overview file streams: the overview file stores the number of save files
	ifstream vin("data/overview");
	
	//if overview file exists, read the number of save files
	//otherwise, the number of save files is 0 by default
	if(vin){
		vin >> saveCount;
	}
	
	cout << "Select an option:\n";
	
	//print the option to overwrite a save file if at least one save file exists
	if(saveCount){
		cout << "[1-" << saveCount << "] Overwrite selected save file\n";
	}
	cout << "[" << saveCount+1 <<"] Create new save file\n"
		<< "[0] Main Menu\n\n";
	
	cout << "Please select the number beside your selection:\n";
	
	int selection;
	cin >> selection;
	validate(selection, 0, saveCount+1);
	
	//return to main menu
	if(selection == 0){
		cout << '\n';
		return;
	}
	
	//if a new save file is created, update overview file
	if(selection == saveCount+1){
		ofstream vout("data/overview", ios::trunc);
		saveCount++;
		vout << saveCount << '\n';
		vout.close();
	}
	
	//overwrite the selected save file
	ofstream fout("data/save" + to_string(selection), ios::trunc);
	
	fout << recipeVector.size() << '\n';
	
	for(Recipe r: recipeVector){
		fout << r.getName() << '\n';
		fout << r.getCalories() << '\n';
		fout << r.getNumIngredients() << '\n';
		for(string i: r.getIngredients()){
			fout << i << '\n';
		}
		fout << r.getNumSteps() << '\n';
		for(string s: r.getSteps()){
			fout << s << '\n';
		}
	}	
	
	//close file streams
	vin.close();
	fout.close();
	
	cout << "\nData saved.\n\n";
}

// loads recipes from a .txt file
void load(){
	int saveCount = 0;	//number of save files
	
	//read number of save files
	//if the file does not exist, the number of save files is 0 - no change required
	ifstream vin("data/overview");
	if(vin){
		vin >> saveCount;
	}
	
	cout << "Select an option:\n";
	
	//print the option to load save files if at least one save file exists
	if(saveCount){
		cout << "[1-" << saveCount << "] Load selected save file\n";
	}
	cout << "[0] Main Menu\n\n";
	
	cout << "Please enter the number beside your selection:\n";
	
	int index;
	cin >> index;
	validate(index, 0, saveCount);
	
	if(index == 0){
		cout << '\n';
		return;
	}
	
	//open the selected save file
	ifstream fin("data/save" + to_string(index));
	
	//ensures that file is found
	if(!fin){
		cout << "\nError: Save data not found.\n\n";
		return;
	}
	
	//clear recipeVector
	recipeVector = {};
	
	int _size;	//number of recipes
	fin >> _size;
	fin.ignore();
	
	//retrieve save file data
	for(int i=0; i<_size; i++){
		string temp_name;
		int temp_calories;
		vector<string> temp_ingredients;
		vector<string> temp_steps;
		
		getline(fin, temp_name);
		
		fin >> temp_calories;
		
		int ingredientCount;
		fin >> ingredientCount;
		fin.ignore();
		for(int j=0; j<ingredientCount; j++){
			string temp;
			getline(fin, temp);
			temp_ingredients.push_back(temp);
		}
		
		int stepsCount;
		fin >> stepsCount;
		fin.ignore();
		for(int j=0; j<stepsCount; j++){
			string temp;
			getline(fin, temp);
			temp_steps.push_back(temp);
		}
		
		recipeVector.push_back(Recipe(temp_name, temp_calories, temp_ingredients, temp_steps));
	}
	
	cout << "\nSave file loaded.\n\n";
	
	//close file streams
	vin.close();
	fin.close();
}
