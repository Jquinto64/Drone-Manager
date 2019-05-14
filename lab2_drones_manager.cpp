#include "lab2_drones_manager.hpp"
#include <iostream>

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}


DronesManager::~DronesManager() {
	DroneRecord* current = first;
	while (current != NULL) {
		DroneRecord* next = current->next;
		delete current;
		current = next;
	}
	first = NULL;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
		bool is_identical = true;
		is_identical = is_identical && lhs.droneID == rhs.droneID;
		is_identical = is_identical && lhs.range == rhs.range;
		is_identical = is_identical && lhs.yearBought == rhs.yearBought;
		is_identical = is_identical && lhs.droneType == rhs.droneType;
		is_identical = is_identical && lhs.manufacturer == rhs.manufacturer;
		is_identical = is_identical && lhs.description == rhs.description;
		is_identical = is_identical && lhs.batteryType == rhs.batteryType;
		return is_identical;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if (first == NULL && size == 0 && last == NULL) return true;
	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	DroneRecord* current = first;
	DroneRecord* searcher = first;

	if (index > size - 1 || index < 0)  {
		return DroneRecord(*last);
	}

	for (unsigned int i = 0; i < index; i++) {
		searcher = searcher->next;
	}
	return DroneRecord(*searcher);
}

unsigned int DronesManager::search(DroneRecord value) const {
	DroneRecord* current = first;
	unsigned int count = 0;

	if (first == NULL) return 0;
	else {
		while (current != NULL) {
			if (DroneRecord(*current) == value) return count;
			else {
				current = current->next;
				++count;
			}
		}
	}
	if (current == NULL) return size;
	return count;
}

void DronesManager::print() const {
	cout << "(";
	DroneRecord* end = first;
	while (end) { // don't need to specify NULL
		cout << "<-" << "[" << (end->droneID) << "]"; // prints node
		end = end->next;

		if (end)
			cout << "->";
	}
	cout<<")\n";
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord* current = first;
	if (index > size - 1 || index < 0) return false;

	for (unsigned int i = 0; i < index; i++) {
		current = current->next;
	}
	if (index == 0) insert_front(value);
	else {
		DroneRecord* node = new DroneRecord(value);
		node->prev = current->prev;
		current->prev = node;
		node->next = current;
		node->prev->next = node;
		++size;
	}
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* node = new DroneRecord(value);

	if (first != NULL) {
		node->next = first;
		node->prev = NULL;
		first->prev = node;
		first = node;
	}
	else if (first == NULL) {
		first = node;
		first->next = NULL;
		first->prev = NULL;
		last = first;
	}
	++size;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* temp = first;
	DroneRecord* node = new DroneRecord(value);
	// Case 0: Empty List
	// First pointer points to null:
	if (first == NULL) {
		first = node;
		first->next = NULL;
		first->prev = NULL;
		last = first;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
		temp->next->next = NULL;
		temp->next->prev = temp;
		last = node;
	}
	++size;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	DroneRecord* iterator = first;

	if (first == NULL) return false;
	if (index > size - 1 || index < 0) return false;

	if (index == 0) remove_front();
	else if (index == size - 1) remove_back();
	else {
		for (unsigned int i = 0; i < index; i++) iterator = iterator->next;

		// NULL<-[]-><-[it]-><-[]-><-[]->NULL
		DroneRecord* deleter = iterator;
		iterator = iterator->prev;
		iterator->next = deleter->next;
		deleter->next->prev = iterator;
		delete deleter;
		--size;
	}
	return true;
}

bool DronesManager::remove_front() {
	// Case 0: Empty List
	if (!first) return false;

	// Case 1: One Element
	else if (!first->next) {
		delete first; // clean up memory
		first = NULL; // Have first point to nothing
		last = NULL;
	}

	// Case 2: Multiple nodes in the list
	else {
		DroneRecord* temp = first;
		DroneRecord* place_holder = first;
		temp = temp->next;
		first = temp;
		delete place_holder;
		temp->prev = NULL;

	}
	--size; // update size
	return true;
}

bool DronesManager::remove_back() {
	// Case 0: Empty List
	if (!first) {return false;}

	// Case 1: One Element
	else if (!first->next) {
		delete first; // clean up memory
		first = NULL; // Have first point to nothing
		last = NULL;
	}

	// Case 2: Multiple nodes in the list
	else {
		DroneRecord* end = first; // initialize end pointer

		while (end->next->next) {
			end = end->next;
		}
		// -><-[]-><-[]->NULL;
		delete end->next;
		end->next = NULL;
		last = end;
	}
	--size; // update size
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	remove(index);
	if (index == size) insert_back(value);
	else if (index == 0) insert_front(value);
	else insert(value, index);
	return true;
}

bool DronesManager::reverse_list() {
	if (first == NULL) return false;
	else if (first->next == NULL) return true;
	else {
		DroneRecord* temp = NULL;
		DroneRecord* current = first;
		DroneRecord* sentry = first;

		while (current != NULL) {
			// (NULL(temp))<-[]-><-[]-><-[]->NULL
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}
		if (temp != NULL) first = temp->prev;
		last = sentry;
	}
	return true;
}

