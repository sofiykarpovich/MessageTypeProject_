#include <iostream>
#include "MessageType.h"

using namespace messaging;

int main() {
	std::cout << "=== MessageType Example ===\n\n";


	MessageType type = MessageType::Server;
	std::string serialized = Serialize(type);
	std::cout << "Serialized: " << serialized << "\n\n";


	MessageType parsed;
	if (Deserialize("session", parsed)) {
		std::cout << "Deserialized: " << ToString(parsed) << "\n\n";
	} else {
		std::cout << "Failed to deserialize!\n";
	}


	std::cout << "Enter message type (system / server / session): ";
	MessageType userType;
	if (std::cin >> userType) {
		std::cout << "You entered: " << userType << "\n";
	} else {
		std::cerr << "Invalid input!\n";
	}


return 0;
}
