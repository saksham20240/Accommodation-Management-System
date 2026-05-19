#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Accommodation {
protected:
    std::string address;
    double rent;
    bool isAvailable;

public:
    Accommodation(const std::string& addr, double r, bool avail)
        : address(addr), rent(r), isAvailable(avail) {}

    virtual void displayInfo() const = 0;
    virtual ~Accommodation() = default;

    const std::string& getAddress() const { return address; }
    double getRent()                const { return rent; }
    bool   availability()           const { return isAvailable; }
    void   setAvailability(bool avail)    { isAvailable = avail; }
};

class Flat : public Accommodation {
private:
    int numberOfRooms;

public:
    Flat(const std::string& addr, double r, bool avail, int rooms)
        : Accommodation(addr, r, avail), numberOfRooms(rooms) {}

    void displayInfo() const override {
        std::cout << "Address: "         << address                        << '\n'
                  << "Rent: "            << rent                           << '\n'
                  << "Available: "       << (isAvailable ? "Yes" : "No")  << '\n'
                  << "Number of rooms: " << numberOfRooms                  << '\n';
    }

    int getNumberOfRooms() const { return numberOfRooms; }
};

class AccommodationManager {
private:
    std::vector<std::unique_ptr<Accommodation>> accommodations;

public:
    void addAccommodation(std::unique_ptr<Accommodation> acc) {
        accommodations.push_back(std::move(acc));
    }

    void displayAllAccommodations() const {
        for (const auto& acc : accommodations) {
            acc->displayInfo();
            std::cout << "--------------------------\n";
        }
    }

    void sortAccommodationsByRent() {
        std::sort(accommodations.begin(), accommodations.end(),
            [](const std::unique_ptr<Accommodation>& a,
               const std::unique_ptr<Accommodation>& b) {
                return a->getRent() < b->getRent();
            });
    }

    std::vector<const Accommodation*> searchByAvailability() const {
        std::vector<const Accommodation*> result;
        for (const auto& acc : accommodations) {
            if (acc->availability())
                result.push_back(acc.get());
        }
        return result;
    }
};

int main() {
    AccommodationManager manager;

    manager.addAccommodation(std::make_unique<Flat>("123 Main St",  1200.00, true,  2));
    manager.addAccommodation(std::make_unique<Flat>("456 Elm St",   1500.00, false, 3));
    manager.addAccommodation(std::make_unique<Flat>("789 Maple St", 1100.00, true,  1));

    std::cout << "All accommodations:\n";
    manager.displayAllAccommodations();

    std::cout << "Sorting accommodations by rent:\n";
    manager.sortAccommodationsByRent();
    manager.displayAllAccommodations();

    std::cout << "Available accommodations:\n";
    for (const auto* acc : manager.searchByAvailability()) {
        acc->displayInfo();
        std::cout << "--------------------------\n";
    }

    return 0;
}
