#pragma once

#include <iostream>
#include <fstream>
#include <iomanip> 

const std::string Productfilename = "res\\Product.bin";
const std::string Accountfilename = "res\\Account.bin";
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
	int pv_caja=0;
	int pc_caja=0;
	Account() = default;
	Account(std::string account, std::string password, bool isadmin);
	Account(std::string account, std::string password, bool isadmin,int pc_caja,int pv_caja);
	void display(std::ostream& os) override;
	void SaveData(IntrusiveNode& head) override;
};
struct Venta : IntrusiveNode {

	std::string product="";
	int cantidad=0;
	int precioUnitario=0;
	Venta() = default;
	Venta(std::string product,int cantidad,int precioUnitario);
	void display(std::ostream& os) override;
	void SaveData(IntrusiveNode& head) override;
	
};
std::ostream& operator<<(std::ostream& os, Product& pd);
std::ostream& operator<<(std::ostream& os, Account& acc);
std::ostream& operator<<(std::ostream& os, Venta& ven);
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
	void EmptyList ();

};

void PrintInventoryTags();
void PrintAccountTags();
//find account
int findProduct(List list, std::string ProductSearched);
int findProduct(List list, int ID);
int findAccount(List list, std::string account_searched);
void DisplayProduct(List list, std::string ProductSearched);
void DeepCopyProduct(Product* pd, Product* to_copy);
void SwapListElements(IntrusiveNode* ActualNode);
void SortProductsAlpha(List list);
void SortProductsID(List list);
//by id display products


void EraseToRewrite(std::string Filename);
void LoadProductData(std::string filename, List& list);
void LoadAccountData(std::string filename, List& list);



