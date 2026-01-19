#pragma once
#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream>


class Book {
protected:
	std::vector <std::vector <std::string>> Books;
	int AvailableBook = 0;
	int BookCount = 0;
	std::string CurrentISBN;
	std::string CurrentTitle;
public:
	void setNewCount(int i, int NewCount) {
		Books[i][2] = std::to_string(NewCount);
	}
	std::vector<std::vector<std::string>>& getBooks() {
		return Books;
	}
	void setBookCount(int count) {
		BookCount = count;
	}
	void setISBN(std::string ISBN) {
		CurrentISBN = ISBN;
	}
	void setTitle(std::string title) {
		CurrentTitle = title;
	}
	std::string getTitle(int i) {
		return Books[i][0];
	}
	std::string getISBN(int i) {
		return Books[i][1];
	}
	std::string getBookCount(int i) {
		return Books[i][2];
	}
	int getAvailableBook() {
		return AvailableBook;
	}
	void setAvailablebooks() {
		AvailableBook = Books.size();
	}
	void setBooks() {
		std::vector <std::string> BookRow;
		std::string Bcount = std::to_string(BookCount);

		BookRow.push_back (CurrentTitle);
		BookRow.push_back (CurrentISBN);
		BookRow.push_back (Bcount);

		Books.push_back(BookRow);
		setAvailablebooks();
		
	}
	void displayBooks() {
		for (int i = 0; i < AvailableBook; i++) {
			std::cout << "-------------------------------------------------------------------------------------\n";
			std::cout << "Title: " << Books[i][0] << " | ISBN: " << Books[i][1] << "| BookCount: " << Books[i][2] << std::endl;
		}
		std::cout << "-------------------------------------------------------------------------------------\n";
	}
	~Book(){
		Books.clear();
	}
};

class User {
private:
	std::string UserName;
	std::string UserID;
	
public:
	void setUser_Name_ID(std::string Name, int ID) {
		UserName = Name;
		UserID = std::to_string(ID);
	}
	std::string getUserName() {
		return UserName;
	}
	std::string getUserID() {
		return UserID;
	}

};

class processRental {
private:
	int i;
	int RentCount = 0;
	bool RentalCheck = false;
	std::string RentalDate = " ";
	std::vector <std::string> RentedBook = {};
	std::vector <std::string> Renter = {};
public:
	void storageCleaner() {
		RentedBook.clear();
		Renter.clear();
	}
	void setIndex(int index) {
		i = index;
	}
	void setRentCount() {
		if (RentCount >= 1) {
			RentCount = 0;
		}
		else {
			RentCount = 1;
		}
	}
	int getRentCount() {
		return RentCount;
	}
	void setRentalCheck() {
		if (RentCount > 0) RentalCheck = true;
		else RentalCheck = false;
	}
	void setRentalCheck(bool isRented) {
		if (isRented == true) {
			RentCount = 1;
			RentalCheck = true;
		}
		else {
			RentalCheck = false;
			RentCount = 0;
		}
	}
	void setRenter(User u) {
		Renter.clear();
		Renter.push_back(u.getUserName());
		Renter.push_back(u.getUserID());
	}
	void setRentedBook(Book b) {
		RentedBook.push_back(b.getTitle(i));
		RentedBook.push_back(b.getISBN(i));
		RentedBook.push_back(b.getBookCount(i));
	}
	void setRentedBook(std::string title, std::string ISBN, std::string BookCount) {
		RentedBook.push_back(title);
		RentedBook.push_back(ISBN);
		RentedBook.push_back(BookCount);
	}
	bool getRentalCheck() {
		return RentalCheck;
	}
	std::vector <std::string>& getRentedBook() {
		return RentedBook;
	}
	std::vector <std::string>& getRenter() {
		return Renter;
	}
	int setNdgetYear() {
		int year;
		while (true) {
			std::cout << "Enter The Current Year (YYYY): ";
			std::cin >> year;
			if (year < 2025) {
				std::cout << "Please Enter The Current date\n";
				continue;
			}
			else if (year >= 2025) {
				std::cout << "year have been set_up\n";
				return year;
				
			}
		}
	}
	
	void setRentalDate() {
		std::string month;
		int day;
		while (true) {
			std::cout << "Enter Day (DD): ";
			std::cin >> day;
			if (std::cin.fail()) {
				std::cin.ignore(10000, '\n');
				std::cin.clear();
				continue;
			}

			std::cin.ignore(10000, '\n');
			std::cout << "Enter Month (e.g. FEB): ";
			std::getline(std::cin, month);
			std::string NewMonth;
			for (int i = 0; i < month.size(); i++) {
				NewMonth += toupper(month[i]);
			}
			month = NewMonth;
			if (((month == "JAN" || month == "MAR" || month == "MAY" || month == "JUL" || month == "AUG" || month == "OCT" || month == "DEC") && day > 0 && day <= 31) ||
				((month == "SEP" || month == "APR" || month == "JUN" || month == "NOV") && day > 0 && day <= 30) ||
				(month == "FEB" && day > 0 && day <= 28)) {
				std::string daytxt = std::to_string(day);
				std::string year = std::to_string (setNdgetYear());
				RentalDate = daytxt + "/" + month + "/" + year;
				break;
			}
			else {
				std::cout << "Enter A Valid Date\n";
			}
		}
	}
	void setRentalDate(std::string date) {
		RentalDate = date;
	}
	std::string getRentalDate() {
		return RentalDate;
	}
};

class RentalNode {
private:
	processRental rental;
	RentalNode* next;
public:

	void setNext(RentalNode* n) {
		next = n;
	}
	RentalNode* getNext() {
		return next;
	}
	void setNUll() {
		next = nullptr;
	}
	void setData ( processRental r) {
		rental = r;
	}
	processRental& getData() {
		return rental;
	}
};

class NodeList {
private:
	RentalNode* head = nullptr;
	int nodeCounter = 0;
public:
	void addRental(processRental r) {
		RentalNode* Node = new RentalNode();
		Node->setData(r);
		Node->setNext(nullptr);
		Node->getNext();
		if (head == nullptr) {
			head = Node;
		}
		else{
			RentalNode* temp = head;
			while (temp->getNext() != nullptr) {
				temp = temp->getNext(); // Traverse to the end of the list
			}
			temp->setNext(Node); // Append the new node at the end of the list
		}
		std::cout << "Rental Successful!\n"; 
		std::cout << "------------------------------------------------\n";
		processRental rentalData = Node->getData();
		std::cout << rentalData.getRenter()[0] << " rented \"" << rentalData.getRentedBook()[0] << "\"\n";
	}
	
	RentalNode* getHead() {
		return head;
	}
	void setNodeCounter() {
		RentalNode* temp = getHead();
		nodeCounter = 0;
		while (temp != nullptr) {
			nodeCounter += 1;
			temp = temp->getNext();				
		}
		
	}
	int getNodeCounter() {
		return nodeCounter;
	}
	int duplicateChecker(std::string UserName, int UserID) {
		
		RentalNode* temp = getHead();
		while (temp != nullptr) {
			if (UserName == temp->getData().getRenter()[0] && stol(temp->getData().getRenter()[1]) == UserID) {
				std::cout << "Welcome back" << UserName << std::endl;
				return 0;
			}
			else if (UserName != temp->getData().getRenter()[0] && stol(temp->getData().getRenter()[1]) == UserID) {
				std::cout << "Ther Alrady exists A User Under That ID" << std::endl;
				return 1;
			}
			else {
				temp = temp->getNext();
			}
		}
		return 2;
	}

	void dataSetter(Book& BookInventory, processRental& rental, User& user, int i) {
		RentalNode* temp = getHead();
		bool isfound = false;

		while (temp != nullptr) {
			std::vector<std::string>& renter = temp->getData().getRenter();

			if (renter[1] == user.getUserID()) {
				processRental newRental;
				newRental.storageCleaner();
				newRental.setIndex(i);
				newRental.setRenter(user);
				newRental.setRentedBook(BookInventory);
				newRental.setRentCount();
				newRental.setRentalCheck();
				newRental.setRentalDate();
				temp->setData(newRental);
				isfound = true;
				break;
			}
			temp = temp->getNext();
		}

		if (!isfound) {
			rental.storageCleaner();
			rental.setIndex(i);
			rental.setRenter(user);
			rental.setRentedBook(BookInventory);
			rental.setRentCount();
			rental.setRentalCheck();
			rental.setRentalDate();

			addRental(rental);
			setNodeCounter();
		}
	}


	void dataSetter(Book &BookInventory, int i, int count) {
		BookInventory.setNewCount(i, count);
	}
	void NodeDataSetter(std::string UserName, std::string UserId, std::string title, std::string ISBN, std::string RenatlDate,std::string BookCount, std::string RentalStatus, processRental &rental,User &user) {
		user.setUser_Name_ID(UserName, stol(UserId));
		rental.setRenter(user);
		rental.setRentalDate(RenatlDate);
		rental.setRentedBook(title, ISBN, BookCount);
		if (RentalStatus == "Rented") rental.setRentalCheck(true);
		else if (RentalStatus == "Returned") rental.setRentalCheck(false);
		addRental(rental);
		setNodeCounter();
		rental.storageCleaner();

	}
	bool rentalLimit(int UserID) {
		RentalNode* temp = getHead(); 
		while (temp != nullptr) {
			if (UserID == stol(temp->getData().getRenter()[1])) {
				if (temp->getData().getRentalCheck()) {
					return true; 
				} 
			} 
			temp = temp->getNext(); 
		}
		return false;
	}

	~NodeList() {
		RentalNode* temp = getHead();
		while (temp != nullptr) {
			RentalNode* next = temp->getNext();
			delete temp;
			temp = next;
		}
		head = nullptr;
	}
	
};

class loadSaveFile {
public:
	void BookFileLoad(Book& bookinventory) {

		
		std::fstream file;
		file.open("books.txt", std::ios::in);

		if (!file.is_open()) {
			std::cout << "Error opening file!" << std::endl;
			return;
		}
		std::string Title, ISBN, BookCount;
		while (std::getline(file, Title, '|') && std::getline(file, ISBN, '|') && std::getline(file, BookCount)) {
			
			bookinventory.setTitle(Title);
			bookinventory.setISBN(ISBN);
			bookinventory.setBookCount(std::stoi(BookCount));
			bookinventory.setBooks();
			

		}
		std::cout << "Books loaded successfully!" << std::endl;
		file.close();
	}
	void BookFileSave(Book& bookinventory) {
		std::ofstream file;
		file.open("books.txt", std::ios::out);
		int AvlBooks = bookinventory.getAvailableBook();
		std::vector <std::vector <std::string>>& Books = bookinventory.getBooks();
		for (int i = 0; i < AvlBooks; i++) {
			file << Books[i][0] << "|" << Books[i][1] << "|" << Books[i][2]<< std::endl;
		}
		file.close();
	}


	void RentalFileLoad(NodeList &myNodeList, User user, processRental rental, Book BookInventory) {
		
		std::fstream file;
		file.open("Rental.txt", std::ios::in);

		if (!file.is_open()) {
			std::cout << "Error opening file!" << std::endl;
			return;
		}
		std::string UserName, UserId, Title, ISBN, RenatlDate, BookCount, RentalStatus;
		while (std::getline(file, UserName, '|') && 
			std::getline(file, UserId, '|') && 
			std::getline(file, Title, '|') && 
			std::getline(file, ISBN, '|') && 
			std::getline(file, RenatlDate, '|') && 
			std::getline(file, BookCount, '|') &&
			std::getline(file, RentalStatus)) {
			myNodeList.NodeDataSetter(UserName, UserId, Title, ISBN, RenatlDate, BookCount, RentalStatus, rental, user);
		}
		
		std::cout << "Users Have Been loaded successfully!" << std::endl;
		file.close();
	}
	void RentalFileSave(NodeList& myNodeList) {
		RentalNode* temp = myNodeList.getHead();

		std::ofstream file;
		file.open("Rental.txt", std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			std::cout << "Faild To Open The File\n";
		}
		
		while (temp != nullptr) {

			file << temp->getData().getRenter()[0]
				<< "|" << temp->getData().getRenter()[1]
				<< "|" << temp->getData().getRentedBook()[0]
				<< "|" << temp->getData().getRentedBook()[1]
				<< "|" << temp->getData().getRentalDate()
				<< "|" << temp->getData().getRentedBook()[2]
				<< "|" << (temp->getData().getRentalCheck() ? "Rented" : "Returned") << std::endl;;

			temp = temp->getNext();
		}
		
		file.close();
	}
};