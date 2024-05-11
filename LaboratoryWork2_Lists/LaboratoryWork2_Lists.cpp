#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct ListNode
{
	int data = NULL;
	ListNode* next = nullptr;
	ListNode* prev = nullptr;
};

ListNode* list = new ListNode;
int arraySize = 16;
int arrayEnd = 0;
int* arrayMass = new int[arraySize];

steady_clock::time_point startTime;
steady_clock::time_point endTime;

ListNode* createList(ListNode* curr) {
	int dataUser = 0;
	cout << "Please, enter a data (number) for element of List: ";
	if (cin >> dataUser)
	{
		curr->data = dataUser;
		ListNode* next = new ListNode;
		next->prev = curr;
		cout << "Element added!\n";
		curr->next = createList(next);
		return curr;
	}

	cout << "Element not added!\n";
	delete curr;
	return nullptr;
}

void clearList(ListNode* list) {
	ListNode* curr = list;
	while (curr->next != nullptr) {
		curr = curr->next;
	}

	while (curr != list) {
		curr = curr->prev;
		delete curr->next;
	}
	list->data = NULL;
}

void showList(ListNode* curr) {
	cout << "Elements of lists: ";
	while (curr != nullptr) {
		cout << curr->data << ' ';
		curr = curr->next;
	}
	cout << '\n';
}

int getLength(ListNode* curr) {
	int res = 0;
	while (curr != nullptr)
	{
		curr = curr->next;
		res++;
	}
	return res;
}

bool insertValue(ListNode* curr, int index, int value) {
	if (index < getLength(curr) && index >= 0)
	{
		ListNode* listNode = new ListNode;
		int i = 0;
		while (i < (index - 1))
		{
			curr = curr->next;
			i++;
		}
		if (index == 0)
		{
			int tmp = curr->data;
			curr->data = value;
			listNode->data = value;
		}
		else {
			listNode->data = value;
		}
		listNode->next = curr->next;
		listNode->prev = curr;
		curr->next->prev = listNode;
		curr->next = listNode;
		return 1;
	}

	else if (getLength(curr) == index) {
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		ListNode* listNode = new ListNode;
		listNode->data = value;
		listNode->prev = curr;
		curr->next = listNode;
		return 1;
	}
	else return 0;
}

float removeByIndex(ListNode* curr, int index) {
	if (index < getLength(curr) && index >= 0)
	{
		if (getLength(curr) == 1 && index == 0)
		{
			int res = curr->data;
			curr->data = 0;
			return res;
		}

		else if (index == 0) {
			int res = curr->data;
			curr->data = curr->next->data;
			if (curr->next->next != nullptr) {
				curr->next->next->prev = curr;
			}
			ListNode* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
			return res;
		}
		else {
			int i = 0;
			while (i < index) {
				curr = curr->next;
				i++;
			}
			if (curr->prev != nullptr) {
				curr->prev->next = curr->next;
			}
			if (curr->next != nullptr) {
				curr->next->prev = curr->prev;
			}
			int res = curr->data;
			delete curr;
			return res;
		}
	}
	else {
		return 0.5;
	}
}

int removeByValue(ListNode* curr, int value) {
	int i = 0;
	while (curr != nullptr && curr->data != value)
	{
		curr = curr->next;
		i++;
	}

	if (curr != nullptr)
	{
		if (getLength(curr) == 1 && i == 0) {
			int res = curr->data;
			curr->data = 0;
			return i;
		}
		else if (i == 0) {
			int res = curr->data;
			curr->data = curr->next->data;
			if (curr->next->next != nullptr) {
				curr->next->next->prev = curr;
			}
			ListNode* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
			return i;
		}
		else {
			if (curr->prev != nullptr) {
				curr->prev->next = curr->next;
			}
			if (curr->next != nullptr) {
				curr->next->prev = curr->prev;
			}
			int res = curr->data;
			delete curr;
			return i;
		}
	}
	else return -1;
}

bool swapElements(ListNode* curr, int i, int j) {
	if (i > j)
		swap(i, j);

	if (getLength(curr) > i && getLength(curr) > j && i >= 0 && j >= 0 && i != j) {
		int count = 0;
		while (count < i) {
			curr = curr->next;
			count++;
		}
		ListNode* second = curr;
		while (count < j) {
			second = second->next;
			count++;
		}

		if (i == 0)
			swap(curr->data, second->data);

		else if (abs(i - j) == 1) {
			ListNode* firstPrev = curr->prev;

			curr->prev = second;
			curr->next = second->next;
			if (second->next != nullptr)
				second->next->prev = curr;

			second->next = curr;
			second->prev = firstPrev;
			if (firstPrev != nullptr)
				firstPrev->next = second;
		}

		else {
			ListNode* firstPrev = curr->prev;
			ListNode* firstNext = curr->next;

			curr->prev = second->prev;
			curr->next = second->next;

			if (second->prev != nullptr)
				second->prev->next = curr;

			if (second->next != nullptr)
				second->next->prev = curr;


			second->prev = firstPrev;
			second->next = firstNext;

			if (firstPrev != nullptr)
				firstPrev->next = second;

			if (firstNext != nullptr)
				firstNext->prev = second;
		}
		return 1;
	}
	return 0;
}

float getValue(ListNode* curr, int index) {
	int i = 0;
	while (curr != nullptr)
	{
		if (i == index)
			return curr->data;

		curr = curr->next;
		i++;
	}
	return 0.5;
}

int getIndex(ListNode* curr, int value) {
	int i = 0;
	while (curr != nullptr) {
		if (curr->data == value) return i;

		curr = curr->next;
		i++;
	}
	return -1;
}

void showArray(int* array)
{
	cout << "Elements of Array: ";
	for (int i = 0; i < arrayEnd; i++) {
		cout << *(array + i) << ' ';
	}
	cout << '\n';
}

int* expandArray(int* array) {
	int* tmp = array;
	array = new int[arraySize * 2];
	for (int i = 0; i < arraySize; i++) {
		*(array + i) = *(tmp + i);
	}
	arraySize *= 2;
	delete[] tmp;
	return array;
}

int* fillArray(int* array)
{
	int a;
	int i = 0;
	while (!(cin.fail())) {
		cin >> a;
		if ((i + 1) == arraySize) {
			array = expandArray(array);
		}
		*(array + i) = a;
		i++;
	}
	arrayEnd = i;
	return array;
}

int* insertValueArray(int* array, int value, int index)
{
	int* tmp = array;
	arrayEnd++;
	if (arrayEnd > arraySize) {
		arraySize *= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (index == i) {
			*(array + i) = value;
			j--;
		}
		else {
			*(array + i) = *(tmp + j);
		}
	}
	delete[] tmp;

	return array;
}

int* removeByIndexArray(int* array, int index)
{
	int* tmp = array;
	arrayEnd--;
	if (arrayEnd < arraySize / 2) {
		arraySize /= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (index == i) {
			j++;
		}
		*(array + i) = *(tmp + j);
	}
	delete[] tmp;

	return array;
}

int* removeByValueArray(int* array, int value) {
	int* tmp = array;
	arrayEnd--;
	if (arrayEnd < arraySize / 2) {
		arraySize /= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (value == *(tmp + i)) {
			j++;
		}
		*(array + i) = *(tmp + j);
	}
	delete[] tmp;

	return array;
}

int main()
{

	bool isLive = true;
	while (isLive)
	{
		int optionUser;
		cout << "Please select option: \n";
		cout << "\t1 - Create a doubly-linked list\n";
		cout << "\t2 - Insert, remove, swap or get element of list\n";
		cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> optionUser;
		cout << "\n";
		switch (optionUser)
		{
		case 1: {
			int actionUserCreate;
			if (list->data != NULL) clearList(list);
			cout << "Please select Action of option: \n";
			cout << "\t1 - Add count element\n";
			cout << "\t2 - Add data element\n";
			cin >> actionUserCreate;
			cout << "\n";

			switch (actionUserCreate)
			{
			case 1: {
				int size;
				cout << "Add a size lists: ";
				cin >> size;
				startTime = steady_clock::now();
				ListNode* curr = list;
				while (size--)
				{
					curr->data = rand() % 100;
					curr->next = new ListNode;
					curr->next->prev = curr;
					curr = curr->next;
				}
				curr->prev->next = nullptr;
				delete curr;
				endTime = steady_clock::now();
				cout << "\n";
				showList(list);
				cout << "Time spent create List to size: "
					<< duration_cast<nanoseconds>(endTime - startTime).count()
					<< " nanoseconds.\n";


				startTime = steady_clock::now();
				int i = 0;
				curr = list;
				while (curr != nullptr) {
					if ((i + 1) == arraySize) {
						arrayMass = expandArray(arrayMass);
					}
					*(arrayMass + i) = curr->data;
					curr = curr->next;
					i++;
				}
				arrayEnd = i;
				endTime = steady_clock::now();
				cout << "\n";
				showArray(arrayMass);
				cout << "Time spent expand Array to size: "
					<< duration_cast<nanoseconds>(endTime - startTime).count()
					<< " nanoseconds.\n";

				break;
			}

			case 2: {
				cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "\n";
				cout << "If you want to exit add number, Please enter not number!\n";
				startTime = steady_clock::now();
				createList(list);
				endTime = steady_clock::now();
				showList(list);
				cout << "Time spent create List, when User added data: "
					<< duration_cast<nanoseconds>(endTime - startTime).count()
					<< " nanoseconds.\n";


				startTime = steady_clock::now();
				ListNode* curr = list;
				int i = 0;
				while (curr != nullptr) {
					if ((i + 1) == arraySize) {
						arrayMass = expandArray(arrayMass);
					}
					*(arrayMass + i) = curr->data;
					curr = curr->next;
					i++;
				}
				arrayEnd = i;
				endTime = steady_clock::now();
				cout << "\n";
				showArray(arrayMass);
				cout << "Time spent fill Array: "
					<< duration_cast<nanoseconds>(endTime - startTime).count()
					<< " nanoseconds.\n";

				break;
			}
			default:
				break;
			}

			cout << "\n";
			break;
		}

		case 2: {
			if (list->data == NULL) {
				cout << "Nothing has been created yet List and Array!\n";
				break;
			}
			int actionUserOperation;
			cout << "Please select Action of option: \n";
			cout << "\t1 - Insert element to List\n";
			cout << "\t2 - Remove element to List\n";
			cout << "\t3 - Swap two elements in List\n";
			cout << "\t4 - Get element of List\n";
			cin >> actionUserOperation;
			cout << "\n";

			switch (actionUserOperation)
			{
			case 1:
				int index, value;
				bool res;
				cout << "Add position for new Element: ";
				cin >> index;
				cout << "Add value for new Element: ";
				cin >> value;

				startTime = steady_clock::now();
				res = insertValue(list, index, value);
				endTime = steady_clock::now();

				if (!res)
					cout << "Error. Failed to insert element!\n";

				else {
					cout << "Successfully. Element was added to List!\n";
					cout << "Time spent insert element to List: "
						<< duration_cast<nanoseconds>(endTime - startTime).count()
						<< " nanoseconds.\n";
					showList(list);
				}

				startTime = steady_clock::now();

				if (index >= 0 && index < (arrayEnd + 1)) {
					arrayMass = insertValueArray(arrayMass, value, index);
					res = true;
				}
				else
					res = false;
				endTime = steady_clock::now();

				if (!res)
					cout << "Error. Failed to insert element!\n";

				else {
					cout << "Successfully. Element was added to Array!\n";
					cout << "Time spent insert element to Array: "
						<< duration_cast<nanoseconds>(endTime - startTime).count()
						<< " nanoseconds.\n";
					showArray(arrayMass);
				}

				break;

			case 2:
				int command;
				cout << "Do you want to remove element:\n";
				cout << "\t1 - by Index\n";
				cout << "\t2 - by Value\n";
				cin >> command;

				switch (command)
				{
				case 1:
					int index;
					float res;
					cout << "Add Index for remove element by Index: ";
					cin >> index;
					startTime = steady_clock::now();
					res = removeByIndex(list, index);
					endTime = steady_clock::now();

					if (res == 0.5)
						cout << "Your index is outside List!";
					else {
						cout << "Successfully. Your index removed from List by Index!\n";
						cout << "Time spent remove element to List by Index: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
						showList(list);
					}

					cout << "\n";

					res = false;
					startTime = steady_clock::now();
					if (index >= 0 && index < arrayEnd) {
						arrayMass = removeByIndexArray(arrayMass, index);
						res = true;
					}
					endTime = steady_clock::now();

					if (!res)
						cout << "Your index is outside Array!";

					else {
						cout << "Successfully. Your index removed from Array by Index!\n";
						cout << "Time spent remove element to Array by Index: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
						showArray(arrayMass);
					}
					cout << "\n";
					break;

				case 2:
					int value, result;
					cout << "Add Value for remove element by Value: ";
					cin >> value;
					startTime = steady_clock::now();
					result = removeByValue(list, value);
					endTime = steady_clock::now();

					if (result == -1)
						cout << "Your value is not in the List!";
					else {
						cout << "Successfully. Your index removed from List by Value!\n";
						cout << "Time spent remove element to List by Value: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
						showList(list);
					}

					cout << "\n";

					startTime = steady_clock::now();
					arrayMass = removeByValueArray(arrayMass, value);
					endTime = steady_clock::now();

					if (result == -1)
						cout << "Your value is not in the Array!";
					else {
						cout << "Successfully. Your index removed from Array by Value!\n";
						cout << "Time spent remove element to Array by Value: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
						showArray(arrayMass);
					}
					cout << "\n";


					break;
				default:
					break;
				}

				break;

			case 3:
				int i, j;
				bool resSwap;
				cout << "Add two index elements for swap in List: \n";
				cout << "First element: ";
				cin >> i;
				cout << "Second element: ";
				cin >> j;

				startTime = steady_clock::now();
				resSwap = swapElements(list, i, j);
				endTime = steady_clock::now();

				if (!resSwap)
					cout << "Your indexs is not in the list!\n";

				else {
					cout << "Successfully. Your indexs swap in List!\n";
					cout << "Time spent swap two elements in List: "
						<< duration_cast<nanoseconds>(endTime - startTime).count()
						<< " nanoseconds.\n";
					showList(list);
				}

				cout << "\n";

				startTime = steady_clock::now();
				if (resSwap) {
					swap(*(arrayMass + i), *(arrayMass + j));
				}
				endTime = steady_clock::now();

				if (!resSwap)
					cout << "Your indexs is not in the Array!\n";

				else {
					cout << "Successfully. Your indexs swap in Array!\n";
					cout << "Time spent swap two elements in Array: "
						<< duration_cast<nanoseconds>(endTime - startTime).count()
						<< " nanoseconds.\n";
					showArray(arrayMass);
				}
				cout << "\n";

				break;

			case 4:
				int commandGet;
				cout << "Do you want to get element:\n";
				cout << "\t1 - by Index\n";
				cout << "\t2 - by Value\n";
				cin >> commandGet;

				switch (commandGet) {
				case 1:
					int indexGet;
					float resGet;
					cout << "Enter index element in List: ";
					cin >> indexGet;
					startTime = steady_clock::now();
					resGet = getValue(list, indexGet);
					endTime = steady_clock::now();

					if (resGet == 0.5)
						cout << "Your index is outside list!";
					else {
						cout << "Successfully. Your index: " << indexGet << ", your Value: " << resGet << "\n";
						cout << "Time spent get element in List by Index: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
					}

					cout << "\n";

					startTime = steady_clock::now();

					if (indexGet >= 0 && indexGet < arrayEnd) {
						resGet = arrayMass[indexGet];
					}
					else {
						resGet = -1;
					}
					endTime = steady_clock::now();

					if (resGet == -1)
						cout << "Your index is outside Array!";
					else {
						cout << "Successfully. Your index: " << indexGet << ", your Value: " << resGet << "\n";
						cout << "Time spent get element in Array by Index: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
					}
					cout << "\n";

					break;

				case 2:
					int valueGet;
					float resIndex;
					cout << "Enter value element in List: ";
					cin >> valueGet;

					startTime = steady_clock::now();
					resIndex = getIndex(list, valueGet);
					endTime = steady_clock::now();

					if (resIndex == -1)
						cout << "Your value is not in the list!";

					else {
						cout << "Successfully. Your value: " << valueGet << ", your Index: " << resIndex << "\n";
						cout << "Time spent get element in List by Value: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
					}

					cout << "\n";

					startTime = steady_clock::now();
					resIndex = -1;
					for (int i = 0; i < arrayEnd; i++) {
						if (*(arrayMass + i) == valueGet) {
							resIndex = i;
							break;
						}
					}
					endTime = steady_clock::now();

					if (resIndex == -1)
						cout << "Your value is not in the Array!";

					else {
						cout << "Successfully. Your value: " << valueGet << ", your Index: " << resIndex << "\n";
						cout << "Time spent get element in Array by Value: "
							<< duration_cast<nanoseconds>(endTime - startTime).count()
							<< " nanoseconds.\n";
					}
					cout << "\n";

					break;

				default:
					break;
				}

			default:
				break;
			}

			cout << "\n";
			break;
		}

		case 0:
			isLive = false;
			break;
		default:
			break;
		}
	}

}
