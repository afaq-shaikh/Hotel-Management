#include <iostream>
#include <map>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include <vector>

class Hotel {
private:
    struct Room {
        std::string type;
        double price;
        bool available;
        bool checkedIn;
        std::string amenities;
        std::string customerName;
        std::string customerContact;
        std::string checkInDate;
        std::string checkOutDate;
    };

    std::map<int, Room> rooms;
    double totalRevenue = 0.0;

public:
    void addRoom(int roomNumber, const std::string& roomType, double roomPrice, const std::string& amenities) {
        if (rooms.find(roomNumber) == rooms.end()) {
            Room newRoom{roomType, roomPrice, true, false, amenities};
            rooms[roomNumber] = newRoom;
        } else {
            std::cout << "Room number already exists." << std::endl;
        }
    }

    void bookRoom(int roomNumber, const std::string& customerName, const std::string& customerContact, const std::string& checkInDate, const std::string& checkOutDate) {
        auto it = rooms.find(roomNumber);
        if (it != rooms.end()) {
            if (it->second.available) {
                it->second.available = false;
                it->second.checkedIn = true;
                it->second.customerName = customerName;
                it->second.customerContact = customerContact;
                it->second.checkInDate = checkInDate;
                it->second.checkOutDate = checkOutDate;
                totalRevenue += it->second.price;
                std::cout << "Room " << roomNumber << " has been booked for " << customerName << "." << std::endl;
            } else {
                std::cout << "Room " << roomNumber << " is not available." << std::endl;
            }
        } else {
            std::cout << "Room number does not exist." << std::endl;
        }
    }

    void cancelBooking(int roomNumber) {
        auto it = rooms.find(roomNumber);
        if (it != rooms.end()) {
            if (!it->second.available) {
                it->second.available = true;
                it->second.checkedIn = false;
                totalRevenue -= it->second.price;
                std::cout << "Booking for Room " << roomNumber << " has been canceled." << std::endl;
            } else {
                std::cout << "No booking found for Room " << roomNumber << "." << std::endl;
            }
        } else {
            std::cout << "Room number does not exist." << std::endl;
        }
    }

    void checkAvailability(int roomNumber) {
        auto it = rooms.find(roomNumber);
        if (it != rooms.end()) {
            if (it->second.available) {
                std::cout << "Room " << roomNumber << " is available." << std::endl;
            } else {
                std::cout << "Room " << roomNumber << " is not available." << std::endl;
            }
        } else {
            std::cout << "Room number does not exist." << std::endl;
        }
    }

    void displayAvailableRooms() {
        std::cout << "Available Rooms:" << std::endl;
        for (const auto& [roomNumber, room] : rooms) {
            if (room.available) {
                std::cout << "Room " << roomNumber << ": Type - " << room.type << ", Price - $" << std::fixed << std::setprecision(2) << room.price << std::endl;
            }
        }
    }

    void displayBookedRooms() {
        std::cout << "Booked Rooms:" << std::endl;
        for (const auto& [roomNumber, room] : rooms) {
            if (!room.available) {
                std::cout << "Room " << roomNumber << ": Type - " << room.type << ", Price - $" << std::fixed << std::setprecision(2) << room.price;
                std::cout << ", Checked-in: " << (room.checkedIn ? "Yes" : "No");
                std::cout << ", Customer Name: " << room.customerName << ", Customer Contact: " << room.customerContact;
                std::cout << ", Check-in Date: " << room.checkInDate << ", Check-out Date: " << room.checkOutDate << std::endl;
            }
        }
    }

    void displayAllRooms() {
        std::cout << "All Rooms:" << std::endl;
        for (const auto& [roomNumber, room] : rooms) {
            std::cout << "Room " << roomNumber << ": Type - " << room.type << ", Price - $" << std::fixed << std::setprecision(2) << room.price;
            std::cout << ", Available: " << (room.available ? "Yes" : "No") << ", Checked-in: " << (room.checkedIn ? "Yes" : "No");
            std::cout << ", Amenities: " << room.amenities << std::endl;
        }
    }

    void displayTotalRevenue() {
        std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    }

    void modifyRoomPrice(int roomNumber, double newPrice) {
        auto it = rooms.find(roomNumber);
        if (it != rooms.end()) {
            it->second.price = newPrice;
            std::cout << "Room " << roomNumber << " price has been updated to $" << std::fixed << std::setprecision(2) << newPrice << std::endl;
        } else {
            std::cout << "Room number does not exist." << std::endl;
        }
    }

    // Function to display the menu and get user choice
    int displayMenu() {
        int choice;
        std::cout << "\n------------ Hotel Management System Menu ------------\n";
        std::cout << "1. Display Available Rooms\n";
        std::cout << "2. Display Booked Rooms\n";
        std::cout << "3. Book a Room\n";
        std::cout << "4. Cancel Booking\n";
        std::cout << "5. Modify Room Price\n";
        std::cout << "6. Display Total Revenue\n";
        std::cout << "7. Display All Rooms\n";
        std::cout << "8. Exit\n";
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Enter your choice (1-8): ";
        std::cin >> choice;
        return choice;
    }

    // Function to handle user's choice
    void handleChoice() {
        int choice;
        while (true) {
            choice = displayMenu();

            switch (choice) {
                case 1:
                    displayAvailableRooms();
                    break;
                case 2:
                    displayBookedRooms();
                    break;
                case 3:
                    bookRoomInteractive();
                    break;
                case 4:
                    cancelBookingInteractive();
                    break;
                case 5:
                    modifyRoomPriceInteractive();
                    break;
                case 6:
                    displayTotalRevenue();
                    break;
                case 7:
                    displayAllRooms();
                    break;
                case 8:
                    std::cout << "Exiting the Hotel Management System.\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    // Function to book a room interactively by taking user input
    void bookRoomInteractive() {
        int roomNumber;
        std::string customerName, customerContact, checkInDate, checkOutDate;

        std::cout << "Enter the room number to book: ";
        std::cin >> roomNumber;

        auto it = rooms.find(roomNumber);
        if (it != rooms.end()) {
            if (it->second.available) {
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);

                std::cout << "Enter customer contact: ";
                std::getline(std::cin, customerContact);

                std::cout << "Enter check-in date (YYYY-MM-DD): ";
                std::getline(std::cin, checkInDate);

                std::cout << "Enter check-out date (YYYY-MM-DD): ";
                std::getline(std::cin, checkOutDate);

                bookRoom(roomNumber, customerName, customerContact, checkInDate, checkOutDate);
            } else {
                std::cout << "Room " << roomNumber << " is not available for booking." << std::endl;
            }
        } else {
            std::cout << "Room number does not exist." << std::endl;
        }
    }

    // Function to cancel a booking interactively by taking user input
    void cancelBookingInteractive() {
        int roomNumber;
        std::cout << "Enter the room number to cancel the booking: ";
        std::cin >> roomNumber;
        cancelBooking(roomNumber);
    }

    // Function to modify room price interactively by taking user input
    void modifyRoomPriceInteractive() {
        int roomNumber;
        double newPrice;
        std::cout << "Enter the room number to modify the price: ";
        std::cin >> roomNumber;
        std::cout << "Enter the new price: $";
        std::cin >> newPrice;
        modifyRoomPrice(roomNumber, newPrice);
    }
};

int main() {
    Hotel hotel;
    hotel.addRoom(101, "Standard", 100, "Wi-Fi, TV");
    hotel.addRoom(102, "Deluxe", 150, "Wi-Fi, TV, Minibar");
    hotel.addRoom(103, "Suite", 200, "Wi-Fi, TV, Minibar, Jacuzzi");

    hotel.handleChoice(); // Display the menu and interact with the user

    return 0;
}
