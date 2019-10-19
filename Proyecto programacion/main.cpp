#include "MyLists/MyLists.h"
void Starting_Products_Accounts(List& list);

int main() {

	List list;
	List Accounts;
	Starting_Products_Accounts(list);
	//LoadData(Productfilename,list);
	

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
void Starting_Products_Accounts(List& list) {
	using namespace std::string_literals;
	list.add(new Product(2,"leche"s,10,11,23,5));
	list.add(new Product(4, "pan"s, 10, 20, 20, 2));
	list.add(new Product(1, "agua"s, 10, 11, 12, 8));
	list.add(new Product(3, "huevos"s, 10, 15, 20, 5));
	list.add(new Product(5, "refresco"s, 10, 11, 10, 3));
	

}

