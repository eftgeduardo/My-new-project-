
//revisar todo lo URGENTE puede pasar un bug
#include "MyLists/MyLists.h"
#include <conio.h>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
/*
https://stackoverflow.com/questions/35298610/password-masking-in-c/35300991#35300991

*/

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
//int MostrarInventario();
int MostrarInventarioAlpha();
int MostrarInventarioID();
int Cortecaja();
int RegresoMenu() { return 0; };


int AltasCuentas();
int BajasCuentas();
int ConsultasCuentas();
//int ModificacionesCuentas() { return 0; };
int MostrarCuentas();
int ModificacionCuentas();
int ModificacionPassword();
int ModificacionTypeAccount();

int MenuVentas();
void MenuTicket(int pc,int pv);
int CortedeCajaVendedor() { return 0; };

int GetNumber();
int GetNumberVentas();

typedef int(*FunctionPointer)();
FunctionPointer functionPointers[] = {
	NULL,
	ValidacionAdministrador,
	ValidacionVentas,
	NULL,
	MenuVentas,
	AltasProductos,
	BajasProductos,
	consultas,//consultas
	NULL,//8 modificaciones
	nullptr,
	NULL,//10 administrar cuentas
	Cortecaja,//11 corte de caja (si tiene funcion)
	RegresoMenu,//principal
	ModificacionesPC,
	ModificacionesPV,
	ModificacionesExistencia,//15
	ModificacionesID,
	RegresoMenu,//17administracion
	AltasCuentas,
	BajasCuentas,
	ConsultasCuentas,
	nullptr,//21 modificacion cuentas
	MostrarCuentas,
	RegresoMenu,//23
	ModificacionCuentas,
	ModificacionPassword,
	RegresoMenu,//26
	//inicio de ventas	
	nullptr,//27
	CortedeCajaVendedor,//28
	MostrarInventarioID,//29
	MostrarInventarioAlpha,//30
	RegresoMenu,//31
	ModificacionTypeAccount

};


int state = 0;

std::string AccountAdmin = "admin";
std::string password = "hola";


int Automata[][MaxSizeOfOption] = {
	{1,2,-1,-2},//menu principal
	{0,3,-2},//verificador Admin
	{0,4,-2},//verificador
	
	{5,6,7,8,9,10,11,12}, //Administrador------------
	{4,28,-2},//ventas
	//inicio de Administrador
	{3,-2},
	{3,-2},
	{3,-2},
	{13,14,15,16,17,-2},//8 modificaciones
	{29,30,31,-2},
	{18,19,20,21,22,23,-2},//10 cuentas
	{3,-2},//11
	{0,-2},//12
	{8,-2},
	{8,-2},
	{8,-2},
	{8,-2},//16
	{3,-2},//17 regreso menu anterior 
	{10,-2},//18 sub menu de cuentas
	{10,-2},//19
	{10,-2},//20
	{24,25,32,26,-2},//21 modificacion
	{10,-2},//22
	{3,-2},//23 regreso menu anterior 
	{21,-2},//24 submenu de modificacion
	{21,-2},//25
	{10,-2},//26 regreso menu anterior 
	//inicio de ventas
	{4,-2},//27
	{0,-2},//28

	{9,-2},//29
	{9,-2},//30
	{3,-2},//31
	{21,-2}

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
	{"Regresar al menu anterior"},//23
	{"Modificacion nombre cuenta"},//24
	{"Modificacion de password"},//25
	{"Regresar al menu anterior"},//26
	{"Menu Ticket"},//27ventas
	{"CortedeCajaVendedor"},//28ventas

	{"Por ID"},//29orden de inventario
	{"Por Producto"},//30
	{"Regresar al menu anterior"},//31
	{"Cambiar Admin estatus"}



};


List product;
List account;
List ventas;
//costo por ventas
//pc_caja
int CurrentAccount = 0;//which account you are in



int main() {
	/*
	List product;
	List account;
	//



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
	Starting_Products_Accounts(product, account);
	//account.SaveData();
	//LoadProductData(Productfilename, product);
	LoadAccountData(Accountfilename, account);
	MenuOptions();
	product.SaveData();
	account.SaveData();
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
			Option = functionPointers[state]()+1;
			Size= 9;
		}

		if (Option <= 9 && Option > 0 && Option <= Size)
		{//&&Option<Size
			state = Automata[state][Option-1];
			
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
			std::cout << i+1 << ". salir juego" << std::endl;
		}
		else {
			std::cout << i+1 << ". " << ScreenOptions[Automata[state][i]] << std::endl;
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
		std::cin >> acc;
		if (acc == "*") {
			return 0;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "ingrese contrasena: ";
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}
			if (ch == 8) {
				passw.pop_back();
				std::cout << ch<<" "<<ch;

			}
			else {
				passw.push_back(ch);
				std::cout << '*';
				
			}
			ch = _getch();
			

		}
		position=findAccount(account, acc);
		if (position >= 0) {
			if (passw == ((Account*)account.get(position))->password && acc == ((Account*)account.get(position))->account&& ((Account*)account.get(position))->isadmin) {
				CurrentAccount = position;
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
		std::cin >> acc;
		if (acc == "*") {
			return 0;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "ingrese contrasena: ";
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == '*') {
				return 0;
			}
			if (ch == 8) {
				passw.pop_back();
				std::cout << ch << " " << ch;

			}
			else {
				passw.push_back(ch);
				std::cout << '*';

			}
			ch = _getch();


		}
		position = findAccount(account, acc);
		if (position >= 0) {
			if (passw == ((Account*)account.get(position))->password && acc == ((Account*)account.get(position))->account && ((Account*)account.get(position))->isadmin==false) {
				CurrentAccount = position;
				return 1;
			}
		}



		system("cls");
		std::cout << "cuenta o password incorrecto. Intente de nuevo" << std::endl << std::endl;
		std::cout << std::string(3, '-') << ScreenOptions[state] << std::string(3, '-') << std::endl;
		acc = "";
		passw = "";

	}

}



//administracion
/*int MostrarInventario() {//falta mejorar
	PrintInventoryTags();
	product.display();
	while (_getch() != '*') {
	}
	return 0;


}*/
int MostrarInventarioAlpha() {
	PrintInventoryTags();
	SortProductsAlpha(product);
	product.display();
	while (_getch() != '*') {
	}
	return 0;


}
int MostrarInventarioID() {
	PrintInventoryTags();
	SortProductsID(product);
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
	int lettercount;//lo necesito


	
	int temp;
	
	while (true) {

		/*
			std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(15) << "producto" << std::left << std::setw(5)
		<< "PC" << std::left << std::setw(5) << "PV" << std::left << std::setw(15) << "Existencias"
		<< std::left << std::setw(20) << "Nivel de reorden" << std::endl << std::endl;
		*/
		//----------------------------ID--------------------------
		PrintAltasTag();
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		do
		{
			
			std::cout << "Escribe tu ID" << std::endl;
			do
			{
				temp = GetNumber();
				if (temp == -1)
					return 0;
				if (temp == -2)
					std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
			} while (temp == -2);
			temp_id = temp;

			system("cls");
			if (findProduct(product, temp_id) != -1) {
				PrintAltasTag();
				//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::cout << "ID Invalido, intenta nuevamente" << std::endl;
			}

		} while (findProduct(product,temp_id)!=-1);

		//--------------------------Product-------------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::endl << std::endl;
		do
		{

			std::cout << "Escribe tu producto" << std::endl;
			std::cin >> temp_product;
			if (temp_product == ("*"s)) {
				return 0;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			if (findProduct(product, temp_product) != -1) {
				PrintAltasTag();
				std::cout << std::left << std::setw(5) << temp_id << std::endl << std::endl;

				std::cout << "ID Invalido, intenta nuevamente" << std::endl;
			}

		} while (findProduct(product, temp_product) != -1);
		


		//----------------------PC,PV----------------------
		
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product
			<< std::endl << std::endl;
		do
		{


			std::cout << "Escribe tu PC" << std::endl;
			do
			{	temp = GetNumber();
				if (temp == -1)
					return 0;
				if (temp == -2) 
					std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
			} while (temp==-2);
			temp_pc = temp;
			system("cls");


			//---------------------------------------------------------
			PrintAltasTag();
			std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
				<< temp_pc << std::endl << std::endl;

			std::cout << "Escribe tu PV" << std::endl;

			do
			{	temp = GetNumber();
				if (temp == -1)
					return 0;
				if (temp == -2)
					std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
			} while (temp == -2);
			temp_pv = temp;
			system("cls");
			if (temp_pc > temp_pv) {
				
				PrintAltasTag();
				std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product
					<< std::endl << std::endl;
				std::cout << "Precio de Compra debe ser menor a precio de Venta" << std::endl;
			}
		} while (temp_pc > temp_pv);


		//---------------------------existencias, reorden----------------------------
		PrintAltasTag();
		std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
			<< temp_pc << std::left << std::setw(5) << temp_pv << std::endl << std::endl;
		do
		{

			std::cout << "Escribe tu existencias" << std::endl;
			do
			{	temp = GetNumber();
				if (temp == -1)
					return 0;
				if (temp == -2)
					std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
			} while (temp == -2);

			temp_existencias = temp;
			system("cls");
			//----------------------------reorden---------------------------
			PrintAltasTag();
			std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
				<< temp_pc << std::left << std::setw(5) << temp_pv<< std::left << std::setw(15) << temp_existencias
				<< std::endl << std::endl;
			std::cout << "Escribe nivel de reorden" << std::endl;
			do
			{	temp = GetNumber();
				if (temp == -1)
					return 0;
				if (temp == -2)
					std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
			} while (temp == -2);

			temp_nr = temp;

			if (temp_existencias < temp_nr) {
				PrintAltasTag();
				std::cout << std::left << std::setw(5) << temp_id << std::left << std::setw(15) << temp_product << std::left << std::setw(5)
					<< temp_pc << std::left << std::setw(5) << temp_pv << std::left << std::setw(15) << temp_existencias
					<< std::endl << std::endl;
				std::cout << "Existencias debe ser mayor al Nivel de reorden  " << std::endl;
			}
		} while (temp_existencias < temp_nr);
		//condiciones
		if (findProduct(product, temp_product) == -1 && temp_pc < temp_pv && temp_existencias > temp_nr) {
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
int Cortecaja() {
	
	//std::cout<
	//print everything

	char ch;

	while (true) {
		int PC = 0;
		int PV = 0;
		system("cls");
		std::cout << std::string(3, '-') << "Corte Caja" << std::string(3, '-') << std::endl;
		IntrusiveNode* ac = new Account();
		ac = account.head;
		for (int position = 0; position < account.count; position++) {
			PC += ((Account*)ac)->pc_caja;
			PV += ((Account*)ac)->pv_caja;
			ac = ac->next;

		}
		std::cout << "PC total: " << PC << std::endl;
		std::cout << "PV total: " << PV << std::endl;
		//quiere vaciar caja?

		do {
			std::cout << "quiere Sacar toda la caja? (s/n)" << std::endl;
			ch = _getch();
			if (ch == '*') return 0;
			if (ch != 's' && ch != 'n') {
				std::cout << "Escibe s o n para proseguir" << std::endl;
			}
		} while (ch != 's' && ch != 'n');
		if (ch == 's') {
			ac = account.head;
			for (int position = 0; position < account.count; position++) {
				((Account*)ac)->pc_caja=0;
				((Account*)ac)->pv_caja=0;
				ac = ac->next;

			}


		}

	}






	while (_getch() != '*') {



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
			if (temp == -1)// URGENTE
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
		int position;
		std::string temp_account = "";
		std::string temp_password = "";
		std::string validation_password = "";
		//bool isadmin;
		std::cout << std::string(3, '-') << "Altas" << std::string(3, '-') << std::endl;
			std::cout << "Escribe una nueva cuenta" << std::endl;
		std::cin >> temp_account;
		position = findAccount(account, temp_account);
		if (position != -1) {
			system("cls");
			std::cout << "Cuenta ya existente" << std::endl;
		}
		else {
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
				if (ch == 8) {
					temp_password.pop_back();
					std::cout << ch << " " << ch;

				}
				else {
					temp_password.push_back(ch);
					std::cout << '*';

				}
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
				if (ch == 8) {
					validation_password.pop_back();
					std::cout << ch << " " << ch;

				}
				else {
					validation_password.push_back(ch);
					std::cout << '*';

				}
				ch = _getch();


			}
			std::cout << std::endl;
			if (temp_password == validation_password) {


				do {
					std::cout << "Es administrador (s/n)" << std::endl;
					ch = _getch();
					if (ch != 's' && ch != 'n') {
						std::cout << "Escibe s o n para proseguir" << std::endl;
					}
				} while (ch != 's' && ch != 'n');
				//(acc.isadmin ? "Si" : "No")
				account.add(new Account(temp_account, temp_password, (ch == 's' ? true : false)));
			}

			else {
				std::cout << "no se pudo crear cuenta" << std::endl;
			}

		}



		
	}


	
}
int BajasCuentas() {
	std::string account_to_search;
	int position;
	//char ch;
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

			//if (((Account*)account.get(position))->isadmin)
			//{
				//std::cout << "Antes de eliminar escriba el password de la cuenta" << std::endl;
				//ch = _getch();
				//while (ch != 13) {//character 13 is enter
				//	if (ch == '*') {
				//		return 0;
				//	}
				//	if (ch == 8) {
				//		temp_password.pop_back();
				//		std::cout << ch << " " << ch;
				//	}
				//	else {
				//		temp_password.push_back(ch);
				//		std::cout << '*';
				//	}
				//	ch = _getch();
				//}
				std::cout << std::endl;
				//if (temp_password == ((Account*)account.get(position))->password) {
					
				if (((Account*)account.get(CurrentAccount))->account != ((Account*)account.get(position))->account && ((Account*)account.get(0))->account != ((Account*)account.get(position))->account) {

					
					system("cls");
					account.remove(position);
					std::cout << "Cuenta exitosamente eliminado" << std::endl;
				}
				//}
				else {
					system("cls");
					std::cout << "No se pudo eliminar cuenta" << std::endl;
				}

			//}
			//else {
			//	system("cls");
			//	account.remove(position);
			//	std::cout << "Cuenta exitosamente eliminado" << std::endl;
			//	

			//}

			



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

int ModificacionCuentas() {
	std::string account_to_search;
	std::string NewName;
	int position;
	//char ch;
	std::string temp_password = "";
	while (true) {
		std::cout << std::string(3, '-') << "Modificacion nombre cuenta" << std::string(3, '-') << std::endl;
		PrintAccountTags();
		account.display();

		std::cout << "Escribe el nombre de la cuenta a modificar" << std::endl;
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
				std::cout << std::endl;
				if (((Account*)account.get(position))->account != ((Account*)account.get(0))->account) {//no quiero permitir que se modifique
					std::cout << "Escriba el nuevo nombre" << std::endl;
					std::cin >> NewName;
					system("cls");
					((Account*)account.get(position))->account = NewName;
					std::cout << "Cuenta exitosamente cambiada" << std::endl;
				}
				//}
				else {
					if (((Account*)account.get(CurrentAccount))->account == ((Account*)account.get(0))->account) {
						std::cout << "Escriba el nuevo nombre" << std::endl;
						std::cin >> NewName;
						system("cls");
						((Account*)account.get(position))->account = NewName;
						std::cout << "Cuenta exitosamente cambiada" << std::endl;
					}
					else {
						system("cls");
						std::cout << "No se puede modificar cuenta" << std::endl;
					}

				}

		}

		//DeleteNode()




	}
}

int ModificacionPassword() {

	std::string account_to_search;
	std::string NewPassword;
	int position;
	//char ch;
	std::string temp_password = "";
	while (true) {
		std::cout << std::string(3, '-') << "Modificacion Password cuenta" << std::string(3, '-') << std::endl;
		PrintAccountTags();
		account.display();

		std::cout << "Escribe el nombre de la cuenta a modificar" << std::endl;
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
			std::cout << std::endl;
			if (((Account*)account.get(position))->account != ((Account*)account.get(0))->account) {//no quiero permitir que se modifique
				std::cout << "Escriba el nuevo nombre" << std::endl;
				std::cin >> NewPassword;
				system("cls");
				((Account*)account.get(position))->password = NewPassword;
				std::cout << "Cuenta exitosamente cambiada" << std::endl;
			}
			//}
			else {
				if (((Account*)account.get(CurrentAccount))->account == ((Account*)account.get(0))->account) {
					std::cout << "Escriba el nuevo nombre" << std::endl;
					std::cin >> NewPassword;
					system("cls");
					((Account*)account.get(position))->password = NewPassword;
					std::cout << "Cuenta exitosamente cambiada" << std::endl;
				}
				else {
					system("cls");
					std::cout << "No se puede modificar cuenta" << std::endl;
				}

			}

		}


	};
}

int ModificacionTypeAccount() {
	std::string account_to_search;
	//std::string NewPassword;
	char ch;
	int position;
	//char ch;
	std::string temp_password = "";
	while (true) {
		std::cout << std::string(3, '-') << "Modificacion Password cuenta" << std::string(3, '-') << std::endl;
		PrintAccountTags();
		account.display();

		std::cout << "Escribe el nombre de la cuenta a modificar" << std::endl;
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
			std::cout << std::endl;
			if (((Account*)account.get(position))->account != ((Account*)account.get(0))->account) {//no quiero permitir que se modifique
				do {
					std::cout << "cambiar a administrador (s/n)" << std::endl;
					ch = _getch();
					if (ch != 's' && ch != 'n') {
						std::cout << "Escibe s o n para proseguir" << std::endl;
					}
				} while (ch != 's' && ch != 'n');
				//std::cin >> NewPassword;
				system("cls");
				//((Account*)account.get(position))->password = NewPassword;
				std::cout << "Cuenta exitosamente cambiada" << std::endl;
			}
			//}
			else {
				if (((Account*)account.get(CurrentAccount))->account == ((Account*)account.get(0))->account) {					//std::cin >> NewPassword;
					do {
						std::cout << "cambiar a administrador (s/n)" << std::endl;
						ch = _getch();
						if (ch != 's' && ch != 'n') {
							std::cout << "Escibe s o n para proseguir" << std::endl;
						}
					} while (ch != 's' && ch != 'n');

					system("cls");
					//((Account*)account.get(position))->password = NewPassword;
					std::cout << "Cuenta exitosamente cambiada" << std::endl;
				}
				else {
					system("cls");
					std::cout << "No se puede modificar cuenta" << std::endl;
				}

			}

		}


	};

}
//modificaciones pendientes de cuentas

//ventas
int MenuVentas() {

	int number=0;
	int position;
	std::string temp_product;
	char ch=0;
	int pv_caja=0;
	int pc_caja=0;
	//ventas
	while (true)
	{	

		std::cout << std::string(3, '*')<<"Producto"<< std::string(3, '*') <<std::endl;
		std::cin >> temp_product;
		if (temp_product == "*") {
			MenuTicket(pc_caja, pv_caja);
			return 0;
		}
		if (temp_product == "**") {
			return 1;
		
		}
		position = findProduct(product, temp_product);
		if (position == -1) {
			std::cout << "producto no existente" << std::endl;

		}
		else {
			std::cout << "Cantidad: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			number = GetNumberVentas();

			if (((Product*)product.get(position))->existencia != 0) {
				if (number == -1) {
					MenuTicket(pc_caja, pv_caja);
					return 0;
				}
				if (number == -2) return 1;//empty list y quitar el subtotal
				std::cout << std::endl;
				if (number > ((Product*)product.get(position))->existencia) {
					std::cout << "Este producto tiene en existencias " << ((Product*)product.get(position))->existencia << std::endl;
					std::cout << "QUiere eso (s/n) " << std::endl;;
					//number = GetNumberVentas();
					ch = _getch();
					if (ch == 's') {
						number = ((Product*)product.get(position))->existencia;
						((Product*)product.get(position))->existencia -= number;

						ventas.add(new Venta(temp_product, number, ((Product*)product.get(position))->pv));
						pv_caja += (((Product*)product.get(position))->pv) * number;
						pc_caja += (((Product*)product.get(position))->pc) * number;

					}

				}
				else {
					((Product*)product.get(position))->existencia -= number;

					ventas.add(new Venta(temp_product, number, ((Product*)product.get(position))->pv));
					pv_caja += (((Product*)product.get(position))->pv) * number;
					pc_caja += (((Product*)product.get(position))->pc) * number;


				}


			}
			else{
				std::cout << "Este producto NO tiene existencias. " << std::endl;
			}
		}


		/*while (ch != 13) {
			ch = _getch();
				if (ch == KEY_UP) {
					system("cls");
					number++;
					std::cout << "vamos a imprimir numeros y subirlos con la flechita" << std::endl;
					std::cout << number << std::endl;
					
				}
				if (ch == KEY_DOWN) {
					system("cls");
					number--;
					std::cout << "vamos a imprimir numeros y subirlos con la flechita" << std::endl;
					std::cout << number << std::endl;

				}
		}*/

	}


	return 0;
}
void MenuTicket(int pc, int pv) {
	system("cls");
	time_t rawtime=time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	std::cout << "Abarrotes -La Estrella-" << std::endl;
	std::cout << "RFC : ALE 730903 BB9" << std::endl;
	std::cout << "        Ticket de venta" << std::endl << std::endl;


	std::cout << "Hora: " << timeinfo.tm_hour << ":" << std::setfill('0') << std::setw(2) << timeinfo.tm_min << ":" << std::setfill('0') << std::setw(2) << timeinfo.tm_sec << std::endl;
	std::cout << "Fecha: " << timeinfo.tm_mday << "/" << timeinfo.tm_mon + 1 << "/" << timeinfo.tm_year + 1900 << std::endl;
	std::cout << std::setfill(' ') << std::endl;
	std::cout << "Vendedor: " << ((Account*)account.get(CurrentAccount))->account << std::endl << std::endl;

	
	

	std::cout << std::left << std::setw(10) << "Producto" << std::left << std::setw(10) << "Cantidad" << std::left << std::setw(10)
		<< "Precio" << std::left << std::setw(10) << "subtotal" << std::endl;


	if (ventas.count > 0) {
		ventas.display();
		std::cout << std::left << std::setw(30) << "Total" << std::left << std::setw(10) << pv<< std::endl;
		ventas.EmptyList();

	}
	else {
		std::cout << std::endl << "Ticket Vacio" << std::endl;
	}

	system("pause");
	//((Account*)account)
	((Account*)account.get(CurrentAccount))->pv_caja += pv;
	((Account*)account.get(CurrentAccount))->pc_caja += pc;
	account.SaveData();
	//total_pv = pv_caja;
	//total_pc = pc_caja;
	//pv_caja = 0;
	//pc_caja = 0;
	return;

}
void VentasCorteDeCaja(){
	std::cout << std::string(3, '-') << "Corte de Caja" << std::string(3, '-') << std::endl;
	std::cout << "Vendedor: " << ((Account*)account.get(CurrentAccount))->account << std::endl << std::endl;
	//std::cout << "PC: " << ((Account*)account.get(CurrentAccount))->pc_caja << std::endl;
	std::cout << "Vendio: " << ((Account*)account.get(CurrentAccount))->pv_caja<< std::endl;
}

//modificar cantidades


/*------------Extra----------------*/
int GetNumber() {//revisar todos por el doble asterisco que tenia antes
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
		std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
	}
}
int GetNumberVentas() {
	std::string input = "";
	int Number;
	while (true) {
		//std::cout << "Please enter a valid number: ";
		std::getline(std::cin, input);
		if (input == "*")
			return -1;
		if (input == "**")
			return -2;
		// This code converts from string to number safely.
		std::stringstream myStream(input);
		if (myStream >> Number)
			return Number;
		std::cout << "Numero Invalido, intenta nuevamente" << std::endl;
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

