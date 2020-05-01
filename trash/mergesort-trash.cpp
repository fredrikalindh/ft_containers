Node *get_middle(Node *first){
	if (first->next != 0){
		for (Node *fast = first; fast != 0; fast = fast->next){
			if (fast && fast->next){
				fast = fast->next;
				first = first->next;
			}
	}}
	if (first->prev)
		first->prev->next = 0;
	return first;
}
// void l_merge(Node *a, Node *c, Node *d){
// 	Node *save;
// 	Node *b = c;
// 	std::cout << "\nLIST TO BE MERGED: ";
// 	for (Node *trav = a; trav != d; trav = trav->next){
// 		std::cout << trav->value << ' ';
// 	}
// 	std::cout  << '\n';
// 	while (a && c && a != b && c != d){
// 		std::cout << "v--A	[1]	C--v\n" << a->value << "		   " << c->value << '\n';
// 		if (c && c->value < a->value) {
// 			save = c->next;
// 			splice(a, *this, c);
// 			c = save;
// 			// a = a->prev;
// 		}
// 		else
// 			a = a->next;
// 	}
// }
// void l_merge(Node *a, Node *c, Node *d){
// 	// Node *b = c;
// 	std::cout << "\nLIST TO BE MERGED: ";
// 	for (Node *trav = a; trav != d; trav = trav->next){
// 		std::cout << trav->value << ' ';
// 	}
// 	std::cout  << '\n';
// 	while (a != c && c != d){
// 		std::cout << "v--A	[1]	C--v\n" << a->value << "		   " << c->value << '\n';
// 		if (c->value < a->value) {
// 			a->swap(*c);
// 			if (c->next != d)
// 				c = c->next;
// 		}
// 		else{
// 			a = a->next;
// 		}
// 	}
// }
// void quicksort(Node *first, Node *last){
// 	if (first == last || first->next == last)
// 		return ;
// 	// std::cout << "| ";
// 	// for (Node *trav = first; trav != last; trav = trav->next)
// 	// 	std::cout << trav->value << " | ";
// 	// std::cout << "\n";
// 	Node *middle = get_middle(first, last);
// 	// std::cout << "--------- " << middle->value << " ---------" << '\n';
// 	quicksort(first, middle);
// 	quicksort(middle, last);
// 	first = l_merge(first, middle, last);
// 	std::cout << "AFTER MERGE: ";
// 	for (Node *trav = first; trav != last; trav = trav->next)
// 		std::cout << trav->value << " ";
// 	std::cout << "\n\n";
// }


// void	unique(){
// 	iterator it2;
// 	for (Node *it1 = d_first; it1->next != 0; it1 = it1->next)
// 	{
// 		it2 = it1->next;
// 		while (it2 != 0){
// 			if (*it2 == it1->value){
// 				it2 = erase(it2);
// 			}else
// 				it2++;
// 		}
// 	}
// }
// template <class BinaryPredicate>
// void	unique (BinaryPredicate binary_pred){
// 	iterator it2;
// 	for (Node *it1 = d_first; it1 != 0; it1 = it1->next)
// 	{
// 		it2 = it1->next;
// 		while (it2 != 0)
// 		{
// 			if (binary_pred(*it2, it1->value)){
// 				it2 = erase(it2);
// 			}else
// 				it2++;
// 		}
// 	}
// }
