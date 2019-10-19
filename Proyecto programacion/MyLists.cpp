
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
		//std::cout << *(Product*)node;
		node = node->next;
	}


}

std::ostream& operator<<(std::ostream& os, Product& pd)
{
	os << pd.id << pd.product << pd.pv << std::endl;
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
			std::cout << *(Product*)pd;
			return;
		}

		pd = pd->next;

	}
	std::cout << "no existe producto";
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



Product::Product(int id, std::string product, int pv)
{
	this->id = id;
	this->product = product;
	this->pv = pv;

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
		EraseToRewrite("Product.bin"s);

	}
	//auto nombre = ;`
	char SizeString = char(data.product.size());
	std::ofstream file("Product.bin", std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send

	file.write(&SizeString, sizeof(SizeString));

	file.write(data.product.data(), data.product.size());
	//todo lo demas
	file.write(reinterpret_cast<char*>(&data.existencia), sizeof(data.existencia));
	file.write(reinterpret_cast<char*>(&data.id), sizeof(data.id));
	file.write(reinterpret_cast<char*>(&data.pc), sizeof(data.pc));
	file.write(reinterpret_cast<char*>(&data.pv), sizeof(data.pv));
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
	std::ofstream file("Product.bin", std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send
	file.write(&SizeString, sizeof(SizeString));
	file.write(data.account.data(), data.account.size());
	//todo lo demas

	//Data.write(reinterpret_cast<char*>(&SizeString), sizeof( SizeString));
	file.close();
}
