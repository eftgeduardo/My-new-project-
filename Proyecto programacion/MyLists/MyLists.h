#pragma once

#include <iostream>
#include <fstream>
#include <iomanip> 

const std::string Productfilename = "res\\Product.bin";
const std::string Accountfilename = "Account.bin";
struct IntrusiveNode {
	IntrusiveNode* next;
	virtual void display(std::ostream& os) = 0;
	virtual void SaveData(IntrusiveNode& head) = 0;
};

struct Product : IntrusiveNode {
	int id = 0;
	std::string product = "";
	int pv = 0;
	int pc = 0;
	int existencia = 0;
	int nr = 0;
	Product() = default;
	Product(int id, std::string product, int pc,int pv,int existencias,int nr);
	void display(std::ostream& os) override;
	void SaveData(IntrusiveNode& head);
	//friend std::ostream& operator<<(std::ostream& os,Product pd);
};
struct Account : IntrusiveNode {
	std::string account;
	std::string password;
	bool isadmin = false;

	Account() = default;
	Account(std::string account, std::string password, bool isadmin);
	void display(std::ostream& os) override;
	void SaveData(IntrusiveNode& head) override;
};
std::ostream& operator<<(std::ostream& os, Product& pd);
std::ostream& operator<<(std::ostream& os, Account& acc);


struct List {
	//using Allocator = IntrusiveNode *();
	//Allocator* allocator;
	IntrusiveNode* head = nullptr;
	IntrusiveNode* tail = nullptr;
	int count = 0;
	void add(IntrusiveNode*);
	IntrusiveNode* get(int position);
	void remove(int position);
	void display();
	void SaveData();

};

bool findProduct(List list, std::string ProductSearched);
void DisplayProduct(List list, std::string ProductSearched);
void DeepCopyProduct(Product* pd, Product* to_copy);
void SwapListElements(IntrusiveNode* ActualNode);
void AlphabeticalDisplayProducts(List list);



void EraseToRewrite(std::string Filename);
void LoadData(std::string filename, List& list);

//void displayProducts();

//2 save data, tipo Product y tipo Cuentas

//IntrusiveNode* MyNodeAllocator();


