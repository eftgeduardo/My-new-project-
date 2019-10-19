#include "MyLists.h"
std::string Productfilename = "Product.bin";
int main() {
	using namespace std::string_literals;
	List list;
	List Accounts;

	LoadData(Productfilename,list);

	//list.add(new Product(10, "hola"s, 5));
	//list.add(new Product(6, "a"s, 6));
	//list.add(new Product(6, "c"s, 6));
	//list.display();
	//DisplayProduct(list, "hola");
	//AlphabeticalDisplayProducts(list);

	list.display();
	list.SaveData();
	//Accounts.add(new Account("hola"s, "hola"s, true));
	//Accounts.add(new Account("hola2"s, "hola"s, false));
	//Accounts.display();


	//cout<
	//NewProduct.next;



}

