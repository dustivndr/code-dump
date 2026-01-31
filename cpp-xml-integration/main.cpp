// Simple C++ XML integration example using pugixml
// Read-Display-Update flow:
// - Reads existing XML file (or creates default if missing)
// - Displays current data to screen
// - Prompts for updates to name, age, address, and hobbies
// - Saves updated data back to file

#include <pugixml.hpp>

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

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

// Helper to convert XML to formatted string
std::string xmlToString(pugi::xml_document& doc) {
	std::stringstream ss;
	doc.save(ss, "\t", pugi::format_indent);
	return ss.str();
}

int main(int argc, char* argv[]) {
	try {
		const std::string filePath = (argc > 1 && argv[1] && std::string(argv[1]).size() > 0)
			? std::string(argv[1])
			: std::string("output.xml");

		pugi::xml_document doc;
		pugi::xml_node root;

		// Step 1: Read existing file or create default
		pugi::xml_parse_result result = doc.load_file(filePath.c_str());
		if (result) {
			root = doc.document_element();
			std::cout << "=== Current data in '" << filePath << "' ===\n";
		} else {
			// Create default structure if file doesn't exist
			root = doc.append_child("person");
			root.append_child("name").text().set("");
			root.append_child("age").text().set("0");
			root.append_child("address").text().set("");
			
			pugi::xml_node hobbies = root.append_child("hobbies");
			hobbies.append_child("hobby").text().set("");
			hobbies.append_child("hobby").text().set("");
			hobbies.append_child("hobby").text().set("");
			
			std::cout << "File not found. Creating new template.\n";
		}

		// Step 2: Display current data
		std::cout << xmlToString(doc) << "\n";

		// Step 3: Prompt for updates
		std::string name = root.child("name").text().as_string();
		int age = root.child("age").text().as_int();
		std::string address = root.child("address").text().as_string();
		
		std::string hobby1 = "";
		std::string hobby2 = "";
		std::string hobby3 = "";
		
		pugi::xml_node hobbies = root.child("hobbies");
		int hobbyIndex = 0;
		for (pugi::xml_node hobby = hobbies.child("hobby"); hobby && hobbyIndex < 3; hobby = hobby.next_sibling("hobby")) {
			if (hobbyIndex == 0) hobby1 = hobby.text().as_string();
			else if (hobbyIndex == 1) hobby2 = hobby.text().as_string();
			else if (hobbyIndex == 2) hobby3 = hobby.text().as_string();
			hobbyIndex++;
		}

		std::cout << "=== Update fields (leave blank to keep current) ===\n";

		name = getInput("Enter name", name);
		age = getIntInput("Enter age", age);
		address = getInput("Enter address", address);
		hobby1 = getInput("Enter hobby 1", hobby1);
		hobby2 = getInput("Enter hobby 2", hobby2);
		hobby3 = getInput("Enter hobby 3", hobby3);

		// Step 4: Update and save
		root.child("name").text().set(name.c_str());
		root.child("age").text().set(age);
		root.child("address").text().set(address.c_str());
		
		// Update hobbies
		hobbies = root.child("hobbies");
		hobbyIndex = 0;
		for (pugi::xml_node hobby = hobbies.child("hobby"); hobby && hobbyIndex < 3; hobby = hobby.next_sibling("hobby")) {
			if (hobbyIndex == 0) hobby.text().set(hobby1.c_str());
			else if (hobbyIndex == 1) hobby.text().set(hobby2.c_str());
			else if (hobbyIndex == 2) hobby.text().set(hobby3.c_str());
			hobbyIndex++;
		}

		if (!doc.save_file(filePath.c_str(), "\t", pugi::format_indent)) {
			std::cerr << "Failed to save file: " << filePath << "\n";
			return 1;
		}

		std::cout << "\n=== Updated data ===\n";
		std::cout << xmlToString(doc) << "\n";
		std::cout << "Saved to '" << filePath << "'.\n";
		return 0;
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}
}
