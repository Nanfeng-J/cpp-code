#pragma once
#include<iostream>
using namespace std;

namespace key
{
	template<class k>
	class BSTNode
	{
	public:
		k _key;
		BSTNode* _left;
		BSTNode* _right;
		BSTNode(const k& key)
			:_key(key)
			,_left(nullptr)
			,_right(nullptr)
		{ }
	};

	template<class k>
	class BSTree
	{
	public:
		typedef BSTNode<k> Node;
		bool Insert(const k& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
					return false;
			}
			if (parent->_key > key)
				parent->_left = new Node(key);
			else
				parent->_right = new Node(key);
			return true;
		}
		bool Find(const k&key)
		{
			if (_root == nullptr)
			{
				return false;
			}
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
					return true;
			}
			return false;
			
		}
		bool Erase(const k& key)
		{
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//删除
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
					    }
						else
						{
							if (cur->_key < parent->_key)
							{
								parent->_left = cur->_right;
								delete cur;
							}
							else
							{
								parent->_right = cur->_right;
								delete cur;
							}
						}
					}
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
					    }
						if (cur->_key < parent->_key)
						{
							parent->_left = cur->_left;
						}
						else
							parent->_right = cur->_left; 
							delete cur;
					}
					else
					{
						//被删的节点左右子树都不为空
						//用该节点左子树的最右节点或该节点右子树的最左节点的值与该节点的值替换
						//然后删除替换过后的节点
					    //这里寻找右子树的最左节点
						Node* replace = cur->_right;
						Node* replaceparent = nullptr;
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
						}
						cur->_key = replace->_key;
						//if (replaceparent->_left == replace)
							replaceparent->_left = replace->_right;
						/*else
							replaceparent->_right = replace->_right;*/
						delete replace;
					}
					return true; 
				}
			}
			return false;
		}
		
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

		Node* _root=nullptr;
	};
}
namespace key_value
{
	template<class k,class v>
	class BSTNode
	{
	public:
		k _key;
		v _value;
		BSTNode* _left;
		BSTNode* _right;
		BSTNode(const k& key,const v& value)
			:_key(key)
			,_value(value)
			, _left(nullptr)
			, _right(nullptr)
		{
		}
	};

	template<class k,class v>
	class BSTree
	{
	public:
		typedef BSTNode<k,v> Node;
		//强制生成构造
		BSTree() = default;
		BSTree(const BSTree& t)
		{
			_root = Copy(t._root);
		}
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
		BSTree& operator=(BSTree tmp)
		{
			swap(_root, tmp.root);
			return *this; 
		}
		bool Insert(const k& key,const v& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key,value);
				return true;
			}
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
					return false;
			}
			if (parent->_key > key)
				parent->_left = new Node(key,value);
			else
				parent->_right = new Node(key,value);
			return true;
		}
		Node* Find(const k& key)
		{
			if (_root == nullptr)
			{
				return nullptr;
			}
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
					return cur;
			}
			return nullptr;

		}
		bool Erase(const k& key)
		{
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//删除
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur->_key < parent->_key)
							{
								parent->_left = cur->_right;
								delete cur;
							}
							else
							{
								parent->_right = cur->_right;
								delete cur;
							}
						}
					}
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						if (cur->_key < parent->_key)
						{
							parent->_left = cur->_left;
						}
						else
							parent->_right = cur->_left;
						delete cur;
					}
					else
					{
						//被删的节点左右子树都不为空
						//用该节点左子树的最右节点或该节点右子树的最左节点的值与该节点的值替换
						//然后删除替换过后的节点
						//这里寻找右子树的最左节点
						Node* replace = cur->_right;
						Node* replaceparent = nullptr;
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
						}
						cur->_key = replace->_key;
						//if (replaceparent->_left == replace)
						replaceparent->_left = replace->_right;
						/*else
							replaceparent->_right = replace->_right;*/
						delete replace;
					}
					return true;
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << " "<<root->_value;
			_InOrder(root->_right);
		}
		void Destroy(Node* root)
		{
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}

		Node* Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;

			Node* newRoot = new Node(root->_key, root->_value);
			newRoot->_left = Copy(root->_left);
			newRoot->_right = Copy(root->_right);
			return newRoot;
		}
	private:
		Node* _root = nullptr;
	};
}
