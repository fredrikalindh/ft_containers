
	Node *getMiddle(Node *fast, Node* end){
		Node *slow = fast;
		while (fast != end && fast->next != end)
		{
			fast = fast->next;
			if (fast->next != end) {
				fast = fast->next;
				slow = slow->next;
				// std::cout << "__GETMIDDLE__: "<< slow->value << '\n';
			}
		}
		return slow;
	}
	// Node *getMiddle(Node *n, size_t s){
	// 	Node *trav = n;
	// 	for (size_t i = 0; i < s; i++)
	// 		trav = trav->next;
	// 	std::cout << "SEGV GETMIDDLE? s = " << s << '\n';
	// 	return trav->next;
	// }
	Node *mergeList(Node *a, Node *b)
	{
		if (!a)
			return b;
		if (!b)
			return a;
		if (a->value < b->value) {
			a->next = mergeList(a->next, b);
			a->next->prev = a;
			a->prev = 0;
			return a;
		}
		else {
			b->next = mergeList(a, b->next);
			b->next->prev = b;
			b->prev = 0;
			return b;
		}
	}

	void ft_mergesort(Node **n, Node *last){
		Node *a;
		Node *b;
		if (*n == last || (*n)->next == last)
			return ;
		a = *n;
		b = getMiddle(*n, last);
		ft_mergesort(&a, b);
		ft_mergesort(&b, last);
		std::cout << "N VALUE = " << (*n)->value << '\n';
		*n = mergeList(a, b);
	}
	// void ft_mergesort(Node **n, size_t s){
	// 	Node *a;
	// 	Node *b;
	// 	if (!*n || !(*n)->next || s < 2)
	// 		return ;
	// 	a = *n;
	// 	b = getMiddle(*n, s / 2);
	// 	ft_mergesort(&a, s / 2);
	// 	std::cout << " ?? " << '\n';
	// 	ft_mergesort(&b, s / 2);
	// 	*n = mergeList(a, b);
	// }

	// void	sort(){
	// 	if (lsize < 2)
	// 		return ;
	// 	std::cout << "\nlsize = " << lsize << '\n';
	// 	ft_mergesort(&first, 0);
	// 	std::cout << "SEGV ft_mergesort?" << '\n';
	// }
