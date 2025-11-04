#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {


public:

	/**
	 * @brief Set the iterator to the first element.
	 */
	virtual void first() = 0;

	/**
	 * @brief Move the iterator to the next element.
	 */
	virtual void next() = 0;

	/**
	 * @brief Check if the iterator has reached the end.
	 * @return true if the iterator is done, false otherwise.
	 */
	virtual bool isDone() = 0;

	/**
	 * @brief Virtual destructor for Iterator.
	 */
	virtual ~Iterator(){}
};

#endif
