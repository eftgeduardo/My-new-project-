#include "MyLists/MyLists.h"
void Starting_Products_Accounts(List& list, List& account);

int main() {

	List product;
	List account;
	//Starting_Products_Accounts(product,account);
	LoadProductData(Productfilename,product);
	LoadAccountData(Accountfilename, account);


	//products
	PrintInventoryTags();
	product.display();
	product.SaveData();
	std::cout << std::endl;
	PrintAccountTags();
	//accounts
	account.display();
	account.SaveData();

}
void Starting_Products_Accounts(List& product,List& account) {
	using namespace std::string_literals;
	product.add(new Product(2,"leche"s,10,11,23,5));
	product.add(new Product(4, "pan"s, 10, 20, 20, 2));
	product.add(new Product(1, "agua"s, 10, 11, 12, 8));
	product.add(new Product(3, "huevos"s, 10, 15, 20, 5));
	product.add(new Product(5, "refresco"s, 10, 11, 10, 3));

	account.add(new Account("admin"s, "hola"s, true));
	account.add(new Account("ventas"s, "12345"s, false));

	

}

