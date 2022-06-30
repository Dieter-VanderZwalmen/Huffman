
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

//inheritance gebeurt met public zie week 7 inheritance
#include <memory>
//#include <iostream>
#include <functional>

namespace data
{
	//Een node is een voorstelling van een branch of een leaf (ongekend)
	//branch is een tak met 2 NODES aan
	//een leaf is een uiteinde met waarde


	template<typename T>
	class Node
	{
	public:
		virtual ~Node() {}; //a virtual destructor.
		//The virtual function is the parent class function
		//in de opdracht staat
		//You shouldn’t have to override it in subclasses.
	};

	template<typename T>
	class Branch : public Node<T>
	{
	
	private:
		
		//std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
		const std::unique_ptr<Node<T>> left_child;
		const std::unique_ptr<Node<T>> right_child;
	public:
		//constructor
		//std::move is used to indicate that an object t may be "moved from", i.e.allowing the efficient transfer of resources from t to another object.
		Branch(std::unique_ptr<Node<T>> left_child, std::unique_ptr<Node<T>> right_child) : left_child(std::move(left_child)), right_child(std::move(right_child)) {}


		//getters (Do not give away ownership! Instead, simply return it as a reference.) -> daarom * bij de return
		//const spammen kan hier geen kwaad
		const Node<T>& get_left_child() const { return *left_child; }
		const Node<T>& get_right_child() const { return *right_child; }

	};



	template<typename T>
	class Leaf : public Node<T>
	{
	private:
		const T value;

	public:
		//constructor
		Leaf(const T& value) : value(value) {}
		

		//getter
		const T& get_leaf() const
		{
			return value; 
		}
	};


	template<typename IN, typename OUT>
	std::unique_ptr<Node<OUT>> map(const Node<IN>& tree, std::function<OUT(const IN&)> function)
	{




		//om te checken of iets een instance is van dynamic cast je en indien dit niet nullptr is (een nullptr is een pointer dat naar null wijst kort gezegd)
		const Leaf<IN>* leaf = dynamic_cast<const Leaf<IN>*>(&tree);
		if (leaf != nullptr)
		{
			//std:make_unique returned std::unique_ptr of an instance of type T.
			return std::make_unique<Leaf<OUT>>(function(leaf->get_leaf()));
		}
		else {
			
			const Branch<IN>* branch = dynamic_cast<const Branch<IN>*>(&tree);
			return std::make_unique<Branch<OUT>>(map(branch->get_left_child(), function), map(branch->get_right_child(), function));
		}
		/* hulp van lector/guide

		if tree is leaf
			create new leaf with value = function(old_value)
		else tree is branch
			new_left_child = apply map to left child
			new_right_child = apply map to right child
			create new branch with new_left_child and new_right_child
		*/

	};


	


};


#endif




