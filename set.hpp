

struct rb_tree_node
{
	Color			m_color;
	rb_tree_node*	m_parent;
	rb_tree_node*	m_leftChild;
	rb_tree_node*	m_rightChild;
	int				m_value;
};
