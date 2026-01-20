/*
* ---------- Group Members ----------
* Kidus Anteneh         RCD/0264/2017
* Eyuel Esubalew        RCD/1690/2017
* Akbari Girma          RCD/0235/2017
* Birhanemedin Mulat    RCD/0242/2017
* -----------------------------------
*/

#include <iostream>
#include <string>
#include <vector>
#include "main.h"

void FileLoad(Book& BookInventory, NodeList& myNodeList, User& user, processRental& rental) {
	
	loadSaveFile load;
	load.BookFileLoad(BookInventory);
	load.RentalFileLoad(myNodeList, user, rental, BookInventory);
	
}
bool BookAdd(Book &BookInventory) {
	bool exists = false;
	while (true)
	{
		system("cls");
		int BCount;
		std::string Title;
		std::string ISBN;

		std::cout << "Enter Book Title: ";
		

		std::cin.ignore();
		std::getline(std::cin, Title);
		std::cout << "Enter Book ISBN: ";
		std::getline(std::cin, ISBN);

		std::cout << "Enter Book Count: ";
		std::cin >> BCount;
		if (std::cin.fail() || BCount < 0) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input. Please enter a valid book count.\n";
			continue;
		}
		for (int i = 0; i < BookInventory.getAvailableBook(); i++) {
			if (Title == BookInventory.getBooks()[i][0] || ISBN == BookInventory.getBooks()[i][1]) {
				std::cout << "There Is A Book Under The Same Name/ISBN, Please Enter a different book\n";
				exists = true;
				return false;
			}
		}
		if (exists == false){
			BookInventory.setTitle(Title);
			BookInventory.setBookCount(BCount);
			BookInventory.setISBN(ISBN);
			BookInventory.setBooks();
			std::cout << "Book Added Successfully!\n";
		}

		std::cout << "Do you want to add another book? (y/n): ";
		char choice;
		std::cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			continue;
		}
		else {
			return true;
		}

	}
}

bool rent(std::string UserName, std::string Title, int UserID, Book& BookInventory, User& user, processRental& rental, NodeList& myNodeList) {
	system("cls");
	bool isbnCheck = false;
	std::vector <std::vector<std::string>>& books = BookInventory.getBooks();
	std::cin.ignore(10000, '\n');
	while (true) {
		std::string ISBN;
		std::cout << "-------------------------------------------------------------------------------------\n";
		BookInventory.displayBooks();
		std::cout << "-------------------------------------------------------------------------------------\n";
		std::cout << "Enter Book ISBN to Rent: ";
		std::getline(std::cin, ISBN);


		for (int i = 0; i < BookInventory.getAvailableBook(); i++) {
			if (books[i][1] == ISBN) {
				if (std::stol(books[i][2]) >= 1) {
					
					std::cout << "-------------------------------------------------------------------------------------\n";
					std::cout << "User : " << UserName << " | Have Rented: " << books[i][0] << " | Successfully.\n";
					std::cout << "-------------------------------------------------------------------------------------\n";
					int count = std::stol(books[i][2]);
					count -= 1;

					myNodeList.dataSetter(BookInventory, rental, user, i);
					myNodeList.dataSetter(BookInventory, i, count);
					isbnCheck = true;
					return true;
				}
				else if (std::stol(books[i][2]) < 1) {
					std::cout << "Ther Books Was Rented_Out.\n";
					return false;
				}
			}
		}
		
		if (isbnCheck == false) {
			std::cout << "Ther Is No Book Under That ISBN. Please Enter a Correct ISBN Number\n";
			continue;
		}
		
		
	}
}
void BookRent(Book &BookInventory,User &user, processRental &rental, NodeList &myNodeList) {
	system("cls");
	while (true) {
		std::string UserName, ISBN, Title;
		int UserID;

		std::cout << "Enter User Name: ";
		std::cin.ignore();
		std::getline(std::cin, UserName);

		while (true) {
			std::cout << "Enter User ID: ";
			std::cin >> UserID;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Invalid input. Please enter a valid User ID.\n";
				continue;
			}

			else if (UserID < 1000 || UserID > 99999999) {

				std::cout << "UserID Must Be A 4 to 8 Digit Number, And Greater Than 1000\n";
				continue;
			}
			else if (UserID >= 1000 && UserID <= 99999999) {
				user.setUser_Name_ID(UserName, UserID);
				break;
			}
			else {
				std::cout << "Please Enter Valid UserID\n";
				continue;
			}
		}

		int dupechecker = myNodeList.duplicateChecker(UserName, UserID);
		if (dupechecker == 0) {
			while (true) {


				char choice;
				if (myNodeList.rentalLimit(UserID) == true) {
					std::cout << "User Have Rented A Book Before, Please Return The Book To Continue.\n";
					return;
				}
				else {


					std::cout << "Press (Y/y) To Rent A Book, (N/n) To Go Back To Main-Menu: ";
					std::cin >> choice;
					std::cin.ignore(10000, '\n');
					if (choice == 'Y' || choice == 'y') {

						bool wasRented = rent(UserName, Title, UserID, BookInventory, user, rental, myNodeList);
						if (wasRented == true) {
							break;
						}
						else {
							continue;
						}
					}
					else if (choice == 'N' || choice == 'n') {
						break;
					}
					else {
						std::cout << "invalid input\n";
						continue;
					}
				}
			}
			break;
		}
		else if (dupechecker == 2) {
			while (true) {
				bool wasRented = rent(UserName, Title, UserID, BookInventory, user, rental, myNodeList);
				if (wasRented == false) {
					char choice;
					std::cout << "Press (Y/y) To Rent Another Book, (N/n) To Go Back To Main-Menu: ";
					std::cin >> choice;
					if (choice == 'Y' || choice == 'y') {
						wasRented = rent(UserName, Title, UserID, BookInventory, user, rental, myNodeList);
					}
					else if (choice == 'N' || choice == 'n') {
						break;
					}
					else {
						std::cout << "invalid input\n";
						continue;
					}
				}
				else {
					break;
				}
			}
			break;
		}
		else {
			continue;
		}

	}
}

void BookReturn(Book& BookInventory, User& user, processRental& rental, NodeList& myNodeList) {
	system("cls");
	std::vector <std::vector<std::string>>& books = BookInventory.getBooks();
	bool Exists = false;
	
	int UserID;
	RentalNode* temp = myNodeList.getHead(); 

	std::cout << "Enter Your UserID: ";
	std::cin >> UserID;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Please Enter A valid ID.\n";
		Exists = true;
	}
	else {
		while (temp != nullptr) {

			if (UserID == stol(temp->getData().getRenter()[1])) {

				if (temp->getData().getRentalCheck() == true) {
					std::cout << "You Have Returned The Book Successfully.\n";

					for (int i = 0; i < BookInventory.getAvailableBook(); i++) {
						if (books[i][1] == temp->getData().getRentedBook()[1]) {
							int count = std::stol(books[i][2]);
							count += 1;
							myNodeList.dataSetter(BookInventory, i, count);
						}
					}

					temp->getData().setRentCount();
					temp->getData().setRentalCheck();
					Exists = true;
					break;
				}
				else if (temp->getData().getRentalCheck() == false) {
					std::cout << "User Dosent Have A Book To Return A Book.\n";
					Exists = true;
				}
				break;

			}
			temp = temp->getNext();

		}
		
	}
	if (Exists == false) {
		std::cout << "User Dosent Exist. Please Check Again And Try Again.\n";
	}
}

void RentalLog(NodeList &myNodeList ) {
	RentalNode* temp = myNodeList.getHead();
	system("cls");
	if (temp == nullptr) {
		std::cout << "There Is No User Saved In The Program\n";
	}
	
		std::cout << "UserName | Rented_Book | ISBN | RentalDate | RentalStatus\n";
		std::cout << "-------------------------------------------------------------------------------------\n";
	while (temp != nullptr) {
		auto& renter = temp->getData().getRenter(); 
		auto& book = temp->getData().getRentedBook(); 
		if (renter.size() >= 2 && book.size() >= 2) {
			std::cout << temp->getData().getRenter()[0] << " | "
				<< temp->getData().getRentedBook()[0] << " | "
				<< temp->getData().getRentedBook()[1] << " | "
				<< temp->getData().getRentalDate() << " | "
				<< (temp->getData().getRentalCheck() ? "Rented" : "Returned") << std::endl;
			std::cout << "-------------------------------------------------------------------------------------\n";
		}
		temp = temp->getNext();
		
	}
}

int main() {
	Book BookInventory;
	processRental rental;
	User user;
	NodeList myNodeList;
	std::vector <std::vector<std::string>> &books = BookInventory.getBooks();
	
	FileLoad(BookInventory, myNodeList, user, rental);
	

	while (true){
		system("cls");
		int choice;
		std::cout << "1. Display Books\n";
		std::cout << "2. Add Book\n";
		std::cout << "3. Rent Book\n";
		std::cout << "4. Return Book\n";
		std::cout << "5. Rental Log\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice : ";
		
		std::cin >> choice;
		

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
			continue;
		}
		switch (choice) {
			case 1:
				system("cls");
				BookInventory.displayBooks();
				break;
			case 2:
				BookAdd(BookInventory);
				break;
			case 3:
				BookRent(BookInventory, user, rental, myNodeList);
				break;
			case 4:
				BookReturn(BookInventory, user, rental, myNodeList);
				break;
			case 5:
				RentalLog(myNodeList);
				break;
			case 6:
				// Exit
				std::cout << "Saving data...\n";
				loadSaveFile saveload;
				saveload.BookFileSave(BookInventory);
				saveload.RentalFileSave(myNodeList);
				std::cout << "Exiting the program.\n";
				return 0;
			default:
				std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
		}
		system("pause");

	}

	return 0;
}