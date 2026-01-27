// Simple C++ JSON integration example using nlohmann/json
// Interactive version:
// - Prompts for name, age, address, and three hobbies
// - Saves the data to output JSON file (default: output.json or argv[1])

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using json = nlohmann::ordered_json; // preserves insertion order instead of sorting keys

int main(int argc, char* argv[]) {
	try {
		const std::string outPath = (argc > 1 && argv[1] && std::string(argv[1]).size() > 0)
			? std::string(argv[1])
			: std::string("output.json");

		std::string name;
		std::string ageStr;
		std::string address;
		std::string hobby1;
		std::string hobby2;
		std::string hobby3;

		std::cout << "Enter name: ";
		std::getline(std::cin, name);
		if (name.empty()) {
			std::cerr << "Name cannot be empty.\n";
			return 1;
		}

		std::cout << "Enter age (number): ";
		std::getline(std::cin, ageStr);
		if (ageStr.empty()) {
			std::cerr << "Age cannot be empty.\n";
			return 1;
		}
		int age = 0;
		try {
			size_t pos = 0;
			age = std::stoi(ageStr, &pos);
			if (pos != ageStr.size() || age < 0) {
				std::cerr << "Invalid age input.\n";
				return 1;
			}
		} catch (...) {
			std::cerr << "Invalid age input.\n";
			return 1;
		}

		std::cout << "Enter address: ";
		std::getline(std::cin, address);
		if (address.empty()) {
			std::cerr << "Address cannot be empty.\n";
			return 1;
		}

		std::cout << "Enter hobby 1: ";
		std::getline(std::cin, hobby1);
		if (hobby1.empty()) {
			std::cerr << "Hobby 1 cannot be empty.\n";
			return 1;
		}

		std::cout << "Enter hobby 2: ";
		std::getline(std::cin, hobby2);
		if (hobby2.empty()) {
			std::cerr << "Hobby 2 cannot be empty.\n";
			return 1;
		}

		std::cout << "Enter hobby 3: ";
		std::getline(std::cin, hobby3);
		if (hobby3.empty()) {
			std::cerr << "Hobby 3 cannot be empty.\n";
			return 1;
		}

		json data = {
			{"name", name},
			{"age", age},
			{"address", address},
			{"hobbies", {
				{"hobby1", hobby1},
				{"hobby2", hobby2},
				{"hobby3", hobby3}
			}}
		};

		std::ofstream out(outPath);
		if (!out) {
			std::cerr << "Failed to open output file: " << outPath << "\n";
			return 1;
		}
		out << data.dump(2) << '\n';
		out.close();

		std::cout << "Saved data to '" << outPath << "'.\n";
		return 0;
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}
}
