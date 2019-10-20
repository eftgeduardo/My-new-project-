#include "MyLists/MyLists.h"
#include <conio.h>
#include <sstream>
#include <stdlib.h>

#define MaxSizeOfOption 8
using namespace std::string_literals;

void Starting_Products_Accounts(List& list, List& account);

int PrintMenus();
int MenuPrincipal() { return 0; };

int ValidacionAdministrador();
int ValidacionVentas();
int Admin() { return 0; };
void MenuOptions();
int AltasProductos();
int BajasProductos();
int consultas();
int ModificacionesPC();
int ModificacionesPV();
int ModificacionesExistencia();
int ModificacionesID();
int MostrarInventario();
int RegresoMenu() { return 0; };


int AltasCuentas();
int BajasCuentas();
int ConsultasCuentas();
int ModificacionesCuentas() { return 0; };
int MostrarCuentas();


int GetNumber();

typedef int(*FunctionPointer)();
FunctionPointer functionPointers[] = {
	NULL,
	ValidacionAdministrador,
	ValidacionVentas,
	NULL,
	NULL,
	AltasProductos,
	BajasProductos,
	consultas,//consultas
	NULL,//8 modificaciones
	MostrarInventario,
	NULL,//10 administrar cuentas
	NULL,//11 corte de caja (si tiene funcion)
	RegresoMenu,//principal
	ModificacionesPC,
	ModificacionesPV,
	ModificacionesExistencia,//15
	ModificacionesID,
	RegresoMenu,//17administracion
	AltasCuentas,
	BajasCuentas,
	ConsultasCuentas,
	ModificacionesCuentas,
	MostrarCuentas,
	RegresoMenu
};


int state = 0;

std::string AccountAdmin = "admin";
std::string password = "hola";


int Automata[][MaxSizeOfOption] = {
	{1,2,-1,-2},//menu principal
	{0,3,-2},//verificador Admin
	{0,4,-2},//verificador 
	{5,6,7,8,9,10,11,12}, //Administrador------------
	{0,-2},
	{3,-2},
	{3,-2},
	{3,-2},
	{13,14,15,16,17,-2},//8 modificaciones
	{3,-2},
	{18,19,20,21,22,23,-2},//10 cuentas
	{3,-2},//11
	{0,-2},//12
	{8,-2},
	{8,-2},
	{8,-2},
	{8,-2},//16
	{3,-2},//17 regreso menu anterior 
	{10,-2},//18 cuentas
	{10,-2},//19
	{10,-2},//20
	{10,-2},//21
	{10,-2},//22
	{3,-2}//23 regreso menu anterior 

};
char ScreenOptions[][30]{
	{"Menu Principal"},//0
	{"Admin"},//1 verificadores
	{"Vendedor"},//2 verificadores
	{"Menu Admin"},//3 
	{"Menu ventas"},//4
	{"altas"},//5
	{"bajas"},//6
	{"consultas"},//7
	{"Modificaciones"},//8
	{"Mostrar Inventario"},//9
	{"Administracion de cuentas"},//10cuentas
	{"corte general caja"},//11
	{"Regresar al menu anterior"},//12
	{"Precio de compra"}, //13 Modificaciones
	{"Precio de venta"},//14
	{"Existencias"},//15
	{"Nivel de reorden"},//16
	{"Regresar al menu anterior"},//17
	{"Altas"},//18 CUENTAS
	{"Bajas"},//19
	{"Consultas"},//20
	{"modificaciones"},//21
	{"Mostrar cuentas de usuarios"},//22
	{"Regresar al menu anterior"}//23


	



};


List product;
List account;
int main() {
	/*
	List product;
	List account;
	//Starting_Products_Accounts(product,account);



	//products
	PrintInventoryTags();
	product.display();
	product.SaveData();
	std::cout << std::endl;
	PrintAccountTags();
	//accounts
	account.display();
	account.SaveData();
	*/
	LoadProductData(Productfilename, product);
	LoadAccountData(Accountfilename, account);
	MenuOptions();
	return 0;

}



void MenuOptions() {
	int Size;
	char CharacterInput;
	int Option;
	while (state != -1) {


		if (functionPointers[state] == nullptr) {
			Size = PrintMenus();

			CharacterInput = _getch();
			Option = CharacterInput - '0';
			
			
		}
		else {
			Option = functionPointers[state]();
		}

		if (Option <= 9 && Option >= 0)
		{
			state = Automata[state][Option];
			
		}
		system("cls");
		//Option = getchar();
		
	};
	return;
}
int PrintMenus() {
	std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
	int i;
	for (i = 0; i < MaxSizeOfOption; i++) {

		if (Automata[state][i] == -2) break;
		if (Automata[state][i] == -1) {
			std::cout << i << ". salir juego" << std::endl;
		}
		else {
			std::cout << i << ". " << ScreenOptions[Automata[state][i]] << std::endl;
		}
	}
	return i;//returns size of option
}
int ValidacionAdministrador() {
	std::string acc;
	std::string passw;
	std::string DataString = "";
	char ch;
	//Account = "admin"
	//std::cin.ignore();
	std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
	//std::getline(std::cin, passw);
	while (true) {
		int position;
		
		std::cout << "ingrese cuenta: ";

		//std::cin >> acc;
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}

			acc.push_back(ch);
			std::cout << ch;
			ch = _getch();

		}
		std::cout << std::endl;

		std::cout << "ingrese contrasena: ";
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}
			passw.push_back(ch);
			std::cout << '*';
			ch = _getch();

		}
		position=findAccount(account, acc);
		if (position >= 0) {
			if (passw == ((Account*)account.get(position))->password && acc == ((Account*)account.get(position))->account&& ((Account*)account.get(position))->isadmin) {
				return 1;
			}
		}
		
		
		
		system("cls");
		std::cout <<"cuenta o password incorrecto. Intente de nuevo" << std::endl << std::endl;
		std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
		acc = "";
		passw = "";



	}



}
int ValidacionVentas() {
	return 0;
}



//administracion
int MostrarInventario() {//falta mejorar
	PrintInventoryTags();
	product.display();
	while (_getch() != '*') {
	}
	return 0;


}
void PrintAltasTag() {
	std::cout << std::string(3, '-') << "Altas" << std::string(3, '-') << std::endl;
	PrintInventoryTags();
	product.display();

}
int AltasProductos() {//comporbar que el ID sea diferente
	std::string temp_product= "";
	int temp_id = 0;
	int temp_pv = 0;
	int temp_existencias = 0;
	int temp_pc = 0;
	int temp_nr = 0;


	
	int temp;
	
	while (true) {

		/*
			std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(15) << "producto" << std::left << std::setw(5)
		<< "PC" << std::left << std::setw(5) << "PV" << std::left << std::setw(15) << "Existencias"
		<< std::left << std::setw(20) << "Nivel de reorden" << std::endl << std::endl;
		*/
		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << "Escribe tu ID" << std::endl;
		temp = GetNumber();
		if (temp == -1)
			return 0;
		temp_id = temp;
		system("cls");
		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id <<std::endl << std::endl;
		std::cout << "Escribe tu producto" << std::endl;
		std::cin >> temp_product;
		if (temp_product == ("*"s)) {
			return 0;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");

		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product
			<< std::endl << std::endl;
		std::cout << "Escribe tu PC" << std::endl;
		temp = GetNumber();
		if (temp == -1)
			return 0;
		temp_pc = temp;
		system("cls");
		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
			<< temp_pc << std::endl << std::endl;

		std::cout << "Escribe tu PV" << std::endl;

		temp = GetNumber();
		if (temp == -1)
			return 0;
		temp_pv = temp;
		system("cls");
		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
			<< temp_pc << std::left << std::setw(5) << temp_pv << std::endl << std::endl;
		std::cout << "Escribe tu existencias" << std::endl;
		temp = GetNumber();
		if (temp == -1)
			return 0;
		temp_existencias = temp;
		system("cls");
		//---------------------------------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
			<< temp_pc << std::left << std::setw(5) << temp_pv<< std::left << std::setw(15) << temp_existencias
			<< std::endl << std::endl;
		std::cout << "Escribe nivel de reorden" << std::endl;
		temp = GetNumber();
		if (temp == -1)
			return 0;
		temp_nr = temp;

		//condiciones
		if (findProduct(product, temp_product) == -1 && temp_pv < temp_pc && temp_existencias > temp_nr) {
			product.add(new Product(temp_id, temp_product, temp_pc, temp_pv, temp_existencias, temp_nr));
			system("cls");
			std::cout << "producto exitosamente creado" << std::endl;

		}
		else {
			system("cls");
			std::cout << "producto no creado" << std::endl;

		}



	}
	




}
int BajasProductos() {
	std::string product_to_search;
	int position;
	while (true) {
		std::cout << std::string(3, '-') << "Bajas" << std::string(3, '-') << std::endl;
		PrintInventoryTags();
		product.display();

		std::cout << "Escribe el nombre del producto a eliminar" << std::endl;
		std::cin >> product_to_search;//get string
		if (product_to_search == "*") {
			return 0;
		}

		position = findProduct(product, product_to_search);
		if (position == -1) {
			system("cls");
			std::cout << "producto no existente" << std::endl;
		}
		else {
			system("cls");
			product.remove(position);
			std::cout << "producto exitosamente eliminado" << std::endl;
		}

		//DeleteNode()




	}



}
int consultas() {
	std::string temp_product;
	int position;
	char ch;
	while (temp_product != ("*"s)) {
		std::cout << std::string(3, '-') << "Consultas" << std::string(3, '-') << std::endl;
		std::cout << "Escribe el nombre del producto a consultar" << std::endl;
		std::cin >> temp_product;
		if (temp_product == "*"s) {
			return 0;
		}
		DisplayProduct(product, temp_product);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ch = getchar();
		if ( ch== '*') {
			return 0;
		}
		system("cls");
	}

	return 0;




}

using InputFn=void(Product*,int temp);
//administracion -> modificaciones
int ComunModificaciones(InputFn* modifier,std::string impresion) {
	PrintInventoryTags();
	product.display();
	std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
	while (true) {
		int temp;
		std::string temp_producto;
		int position;
		std::cout << "Escribe el nombre del producto a cambiar" << std::endl;
		std::cin >> temp_producto;
		if (temp_producto == ("*"s)) {
			return 0;
		}
		position = findProduct(product, temp_producto);
		std::cout <<impresion << std::endl;
		
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (position >= 0) {


			temp = GetNumber();
			if (temp == -1)
				return 0;
			//esto 
			modifier(((Product*)product.get(position)),temp);
			//((Product*)product.get(position))->pc=temp;
			system("cls");
			std::cout << "Cambio exitoso" << std::endl;

		}
		else {
			system("cls");
			std::cout << "Producto no existente vuelve a intentar" << std::endl;
		}
		std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
		PrintInventoryTags();
		product.display();
	}


};
int ModificacionesPC() { 
	
	return ComunModificaciones([](Product* pd, int temp) {
		pd->pc = temp;
		},"nuevo PC"s);

};
int ModificacionesPV() {
	return ComunModificaciones([](Product* pd, int temp) {
		pd->pv = temp;
		}, "nuevo PV"s);
};
int ModificacionesExistencia() { 
	return ComunModificaciones([](Product* pd, int temp) {
		pd->existencia = temp;
		}, "Numero de Existencias "s);
};
int ModificacionesID() {
	return ComunModificaciones([](Product* pd, int temp) {
		pd->id = temp;
		}, "Cambio de ID"s);
};


//cuentas
int AltasCuentas() {
	

	while (true)
	{
		char ch;
		std::string temp_account = "";
		std::string temp_password = "";
		std::string validation_password = "";
		bool isadmin;

			std::cout << "Escribe una nueva cuenta" << std::endl;
		std::cin >> temp_account;

		if (temp_account == ("*"s)) {
			return 0;
		}
		std::cout << std::endl;
		//temp password
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Escriba password" << std::endl;
		
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}
			temp_password.push_back(ch);
			std::cout << '*';
			ch = _getch();

		}
		std::cout << std::endl;
		//Validation
		std::cout << "Escriba nuevamenta la misma password" << std::endl;
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}
			validation_password.push_back(ch);
			std::cout << '*';
			ch = _getch();

		}
		std::cout << std::endl;
		if (temp_password==validation_password){
	

			do {
				std::cout << "Es administrador (s/n)" << std::endl;
				ch = _getch();
				if (ch != 's', ch != 'n') {
					std::cout << "Escibe s o n para proseguir" << std::endl;
				}
			} while (ch != 's'&& ch != 'n');
			//(acc.isadmin ? "Si" : "No")
			account.add(new Account(temp_account, temp_password, (ch == 's' ? true : false)));
		}

		else {
			std::cout << "no se pudo crear cuenta" << std::endl;
		}
		
	}


	
}
int BajasCuentas() {
	std::string account_to_search;
	int position;
	char ch;
	std::string temp_password = "";
	while (true) {
		std::cout << std::string(3, '-') << "Bajas" << std::string(3, '-') << std::endl;
		PrintAccountTags();
		account.display();

		std::cout << "Escribe el nombre de la cuenta a eliminar" << std::endl;
		std::cin >> account_to_search;//get string
		if (account_to_search == "*") {
			return 0;
		}

		position = findAccount(account, account_to_search);
		if (position == -1) {
			system("cls");
			std::cout << "Cuenta no existente" << std::endl;
		}
		else {
			std::cout << "Antes de eliminar escriba el password de la cuenta" << std::endl;
			ch = _getch();
			while (ch != 13) {//character 13 is enter
				if (ch == '*') {
					return 0;
				}
				temp_password.push_back(ch);
				std::cout << '*';
				ch = _getch();

			}
			std::cout << std::endl;
			if (temp_password == ((Account*)account.get(position))->password) {
				system("cls");
				product.remove(position);
				std::cout << "Cuenta exitosamente eliminado" << std::endl;

			}
			else {
				system("cls");
				std::cout << "No se pudo eliminar cuenta" << std::endl;
			}



		}

		//DeleteNode()




	}
}
int ConsultasCuentas() { 
	std::string account_to_search;
	int position;
	
	while (true)
	{
		std::cout << "Escribe el nombre de una cuenta" << std::endl;
		std::cin >> account_to_search;//get string
		if (account_to_search == "*") {
			return 0;
		}
		position = findAccount(account, account_to_search);
		system("cls");
		if (position == -1) {
			std::cout << "No se encontro la cuenta" << std::endl;
		}
		else {
			PrintAccountTags();
			std::cout << *((Account*)account.get(position));
		}
		


	}

};
int MostrarCuentas() {
	PrintAccountTags();
	account.display();
	while (_getch() != '*') {
	}
	return 0;

}

//modificaciones pendientes de cuentas



/*------------Extra----------------*/
int GetNumber() {
	std::string input = "";
	int Number;
	while (true) {
		//std::cout << "Please enter a valid number: ";
		std::getline(std::cin, input);
		if (input == "*")
			return -1;
		// This code converts from string to number safely.
		std::stringstream myStream(input);
		if (myStream >> Number)
			return Number;
		std::cout << "Invalid number, please try again" << std::endl;
	}



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

