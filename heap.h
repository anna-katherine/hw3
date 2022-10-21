#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
	int nary; // m
	PComparator comp; // c
	void trickleUp (int location); // for inserting members
	void heapify (int location); // must maintain heap property
	std::vector<T> content; // heap itself
};

// Add implementation of member functions here
template <typename T, typename PComparator> //constructor DONE
Heap<T, PComparator>::Heap(int m, PComparator c): nary(m), comp(c)
{
	
};

template <typename T, typename PComparator> // destructor DONE
Heap<T, PComparator>::~Heap(){}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int index)
{
	int first = (index + 1) * nary - nary + 1; 
	if (first > (int)content.size() - 1)
		return;
	int temp = first;
	for (int ind = 0; ind < nary; ind++) // while less than aryness, iterate and check each node by +ind
	{
		if (((first + ind) < (int)content.size()) && comp(content[first + ind], content[temp]))
			temp = first + ind; // if not back and needs to be swapped
	}
	if (comp(content[temp], content[index]))
	{
		std::swap(content[temp], content[index]); //check smallest one and make recursive call til done
		heapify(temp);
	}
}

template <typename T, typename PComparator> // DONE (for insert, moving up the node)
void Heap<T, PComparator>::trickleUp(int index)
{
	if (index == 0)
		return;

	int parent = (index - 1)/nary;
	if (parent >= 0 && comp(content[index], content[parent]))
	{
			std::swap(content[index], content[parent]);
			index = parent;
	}
	else
	{
		return;
	}
	trickleUp(index); // make recursive call throughout tree (swap index and parent)
}

// DONE
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
	return content.size();
}

// DONE
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
	return (content.size()==0);
}

//DONE
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
	content.push_back(item);
	trickleUp(Heap<T, PComparator>::size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
// DONE
template <typename T, typename PComparator>
T const & Heap<T, PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Empty heap!");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return content[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
// DONE
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Empty heap!");
  }
	content[0] = content.back();
	content.pop_back();
	// maintain the heap property by calling heapify (just like what I wrote in lab 7)
	heapify(0);
}



#endif

