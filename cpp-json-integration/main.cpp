// Simple C++ JSON integration example using nlohmann/json
// Read-Display-Update flow:
// - Reads existing JSON file (or creates default if missing)
// - Displays current data to screen
// - Prompts for updates to name, age, address, and hobbies
// - Saves updated data back to file

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using json = nlohmann::ordered_json; // preserves insertion order instead of sorting keys

// Helper to get string input with optional default
std::string getInput(const std::string& prompt, const std::string& currentValue) {
	std::cout << prompt << " [current: " << currentValue << "]: ";
	std::string input;
	std::getline(std::cin, input);
	return input.empty() ? currentValue : input;
}

// Helper to get integer input with optional default
int getIntInput(const std::string& prompt, int currentValue) {
	std::cout << prompt << " [current: " << currentValue << "]: ";
	std::string input;
	std::getline(std::cin, input);
	if (input.empty()) return currentValue;
	try {
		size_t pos = 0;
		int val = std::stoi(input, &pos);
		if (pos != input.size() || val < 0) {
			std::cerr << "Invalid input, keeping current value.\n";
			return currentValue;
		}
		return val;
	} catch (...) {
		std::cerr << "Invalid input, keeping current value.\n";
		return currentValue;
	}
}

int main(int argc, char* argv[]) {
	try {
		const std::string filePath = (argc > 1 && argv[1] && std::string(argv[1]).size() > 0)
			? std::string(argv[1])
			: std::string("output.json");

		json data;

		// Step 1: Read existing file or create default
		std::ifstream infile(filePath);
		if (infile) {
			infile >> data;
			infile.close();
			std::cout << "=== Current data in '" << filePath << "' ===\n";
		} else {
			// Create default structure if file doesn't exist
			data = {
				{"name", ""},
				{"age", 0},
				{"address", ""},
				{"hobbies", {
					{"hobby1", ""},
					{"hobby2", ""},
					{"hobby3", ""}
				}}
			};
			std::cout << "File not found. Creating new template.\n";
		}

		// Step 2: Display current data
		std::cout << data.dump(2) << "\n\n";

		// Step 3: Prompt for updates
		std::string name = data.value("name", std::string(""));
		int age = data.value("age", 0);
		std::string address = data.value("address", std::string(""));
		std::string hobby1 = data["hobbies"].value("hobby1", std::string(""));
		std::string hobby2 = data["hobbies"].value("hobby2", std::string(""));
		std::string hobby3 = data["hobbies"].value("hobby3", std::string(""));

		std::cout << "=== Update fields (leave blank to keep current) ===\n";

		name = getInput("Enter name", name);
		age = getIntInput("Enter age", age);
		address = getInput("Enter address", address);
		hobby1 = getInput("Enter hobby 1", hobby1);
		hobby2 = getInput("Enter hobby 2", hobby2);
		hobby3 = getInput("Enter hobby 3", hobby3);

		// Step 4: Update and save
		data["name"] = name;
		data["age"] = age;
		data["address"] = address;
		data["hobbies"]["hobby1"] = hobby1;
		data["hobbies"]["hobby2"] = hobby2;
		data["hobbies"]["hobby3"] = hobby3;

		std::ofstream outfile(filePath);
		if (!outfile) {
			std::cerr << "Failed to open file for writing: " << filePath << "\n";
			return 1;
		}
		outfile << data.dump(2) << '\n';
		outfile.close();

		std::cout << "\n=== Updated data ===\n";
		std::cout << data.dump(2) << "\n";
		std::cout << "Saved to '" << filePath << "'.\n";
		return 0;
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}
}
