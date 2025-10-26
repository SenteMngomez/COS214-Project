#ifndef SECTION_H
#define SECTION_H


#include "Iterator.h"
#include "ChatIterator.h"
#include "Person.h"
#include "Staff.h"

#include <string>
#include <vector>

class Section {

	public:

		Section(std::string name);

		~Section();

		friend class Iterator;

		virtual void notify(Person* person) = 0;

		void addPerson(Person* person);

		void setAdmin(Staff* admin);
		
		Person* removePerson(Person* person);

		Iterator* createIterator();

		std::string getName() const;

		std::string getHistory() const;

		void addToHistory(Person* person);

	private:
		std::string name;
		std::vector<std::string> history;

	protected:
		Staff* admin;
		std::vector<Person*> personList;
};

#endif
