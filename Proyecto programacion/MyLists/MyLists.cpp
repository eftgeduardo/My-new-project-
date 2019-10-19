
#include "MyLists.h"


void List::add(IntrusiveNode* node) {
	//auto node = allocator();
	if (head != nullptr) {
		tail->next = node;
		tail = node;
	}
	else {
		head = node;
		tail = node;
	}
	count++;
	//return node;
}
IntrusiveNode* List::get(int position) {
	auto node = head;
	for (int i = 0; i < position; i++) {
		node = node->next;
	}
	return node;
}
void List::remove(int position) {
	if (position == 0) {
		auto to_delete = head;
		head = to_delete->next;
		if (tail == to_delete) {
			tail = nullptr;
		}
		delete to_delete;
		count--;
		return;
	}
	if (position < count) {
		auto prev = get(position - 1);
		auto to_delete = prev->next;
		auto next = to_delete->next;
		prev->next = next;
		if (tail == to_delete) {
			tail = prev;
		}
		delete to_delete;
	}
	count--;


}
void List::display()
{
	auto* node = head;

	std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(15) << "producto" << std::left << std::setw(5)
		<< "PC" << std::left << std::setw(5) << "PV" << std::left << std::setw(15) << "Existencias"
		<< std::left << std::setw(20) << "Nivel de reorden" << std::endl << std::endl;
	for (int i = 0; i < count; i++) {
		node->display(std::cout);
		//std::cout << *(Product*)node;
		node = node->next;
	}

}
void List::SaveData()
{
	auto* node = head;

	for (int i = 0; i < count; i++) {
		node->SaveData(*head);
		node = node->next;
	}


}

std::ostream& operator<<(std::ostream& os, Product& pd)
{
	std::cout << std::left << std::setw(5) << pd.id << std::left << std::setw(15) << pd.product << std::left << std::setw(5)
		<< pd.pc << std::left << std::setw(5) << pd.pv << std::left << std::setw(15) << pd.existencia
		<< std::left << std::setw(20) << pd.nr << std::endl;

	return os;
	// TODO: insert return statement here
}
std::ostream& operator<<(std::ostream& os, Account& acc)
{
	os << acc.account << (acc.isadmin ? "Verdadero" : "Falso") << std::endl;
	return os;
}

bool findProduct(List list, std::string ProductSearched)
{
	//list.count
	IntrusiveNode* pd = new Product();
	pd = list.head;

	for (int position = 0; position < list.count; position++) {
		if (((Product*)pd)->product == ProductSearched)
			return true;
		pd = pd->next;

	}
	return false;


}
void DisplayProduct(List list, std::string ProductSearched)
{
	IntrusiveNode* pd = new Product();
	pd = list.head;

	

	for (int position = 0; position < list.count; position++) {
		if (((Product*)pd)->product == ProductSearched) {
			std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(15) << "producto" << std::left << std::setw(5)
				<< "PC" << std::left << std::setw(5) << "PV" << std::left << std::setw(15) << "Existencias"
				<< std::left << std::setw(20) << "Nivel de reorden" << std::endl << std::endl;
			std::cout << *(Product*)pd;
			return;
		}

		pd = pd->next;

	}
	std::cout << "no existe producto"<<std::endl;
}
void DeepCopyProduct(Product* pd, Product* to_copy)
{
	pd->id = to_copy->id;
	pd->existencia = to_copy->existencia;
	pd->nr = to_copy->nr;
	pd->pc = to_copy->pc;
	pd->product = to_copy->product;
	pd->pv = to_copy->pv;
}
void SwapListElements(IntrusiveNode* ActualNode)
{
	IntrusiveNode* NextNode = new Product();
	NextNode = ActualNode->next;
	IntrusiveNode* temp = new Product();

	////actual->temp
	DeepCopyProduct((Product*)temp, (Product*)ActualNode);
	//next->actual 
	DeepCopyProduct((Product*)ActualNode, (Product*)NextNode);
	//temp->next
	DeepCopyProduct((Product*)NextNode, (Product*)temp);

}
void AlphabeticalDisplayProducts(List list)
{
	IntrusiveNode* TempActual = new Product();


	IntrusiveNode* TempNext = new Product();



	for (int i = 0; i < list.count - 1; i++) {
		TempActual = list.head;
		TempNext = TempActual->next;
		for (int j = 0; j < list.count - i - 1; j++) {
			if (((Product*)TempNext)->product.compare(((Product*)TempActual)->product) == -1) {//si sale positivo significa que el actual es menor que el siguiente
				//std::cout << "hola" << TempNext->producto.compare(TempActual->producto) << std::endl;
				SwapListElements(TempActual);
			}
			TempActual = TempNext;
			TempNext = TempActual->next;
		}

		//sino huba CAMBIO un break;
	}


}

void EraseToRewrite(std::string Filename)
{

	//std::fstream Data("Lists.bin");
	//std::remove("Lists.bin");
	std::ofstream ofs;
	ofs.open(Filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();



}
void LoadData(std::string filename,List& list)
{	
	int pointer = 0;//position PTR where in archive I am
	std::ifstream file(filename, std::ifstream::binary);
	file.seekg(0, file.end);
	int length = file.tellg();//lenght of archive

	while (pointer != length) {
		int temp_id = 0;
		int temp_pv = 0;
		int temp_existencias = 0;
		int temp_pc = 0;
		int temp_nr = 0;
		std::string tempS_product = "";
		char ch;
		char SizeString;

		file.seekg(pointer);
		file.read(&SizeString, sizeof(SizeString));
		for (char i = 0; i < SizeString; i++) {
			file.read(&ch, sizeof(char));
			tempS_product.push_back(ch);
		}
		file.read(reinterpret_cast<char*>(&temp_id), sizeof(int));//id
		file.read(reinterpret_cast<char*>(&temp_pv), sizeof(int));//pv

		file.read(reinterpret_cast<char*>(&temp_existencias), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp_pc), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp_nr), sizeof(int));

		list.add(new Product(temp_id, tempS_product, temp_pc, temp_pv, temp_existencias, temp_nr));
		pointer = file.tellg();//position in file

	}



	file.close();

}


Product::Product(int id, std::string product, int pv, int pc, int existencias, int nr)
{
	this->id = id;
	this->product = product;
	this->pv = pv;
	this->existencia = existencias;
	this->nr = nr;
	this->pc = pc;
}
void Product::display(std::ostream& os)
{
	os << *this;
}
void Product::SaveData(IntrusiveNode& head)
{
	using namespace std::string_literals;
	auto data = *this;

	if (data.next == head.next) {
		EraseToRewrite(Productfilename);

	}
	//auto nombre = ;`
	char SizeString = char(data.product.size());
	std::ofstream file(Productfilename, std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send

	file.write(&SizeString, sizeof(SizeString));

	file.write(data.product.data(), data.product.size());
	//todo lo demas
	file.write(reinterpret_cast<char*>(&data.id), sizeof(data.id));
	file.write(reinterpret_cast<char*>(&data.pv), sizeof(data.pv));
	file.write(reinterpret_cast<char*>(&data.existencia), sizeof(data.existencia));
	file.write(reinterpret_cast<char*>(&data.pc), sizeof(data.pc));
	file.write(reinterpret_cast<char*>(&data.nr), sizeof(data.nr));

	//Data.write(reinterpret_cast<char*>(&SizeString), sizeof( SizeString));
	file.close();

}


Account::Account(std::string account, std::string password, bool isadmin)
{
	this->account = account;
	this->password = password;
	this->isadmin = isadmin;

}
void Account::display(std::ostream& os)
{
	os << *this;
}
void Account::SaveData(IntrusiveNode& head)
{

	auto data = *this;
	//auto nombre = ;
	//char nombre[5] = "hola";
	char SizeString = char(data.account.size());
	std::ofstream file(Accountfilename, std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send
	file.write(&SizeString, sizeof(SizeString));
	file.write(data.account.data(), data.account.size());
	//todo lo demas

	//Data.write(reinterpret_cast<char*>(&SizeString), sizeof( SizeString));
	file.close();
}
