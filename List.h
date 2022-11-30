#pragma once
#include <initializer_list>

template<typename T>
class List
{
private:
	struct Node {
		T* data = nullptr;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

public:
	class Iterator {
		friend class List; // List�͗F�B(������������q����)
	private:
		Node* node = nullptr;
		Iterator(Node* ptr) : node(ptr) {}

	public:
		T& operator*() {
			return *node->data;
		}

		//��u
		Iterator operator++(int) {
			Iterator save = *this;
			node = node->next;
			return save;
		}

		//�O�u
		Iterator& operator++() {
			node = node->next;
			return *this;
		}

		bool operator==(const Iterator& o) const {
			return this->node == o.node;
		}

		bool operator!=(const Iterator& o) const {
			return !(*this == o);
		}
	};

private:
	Node* dummy; //�_�~�[�m�[�h�A�F�X�Ɗ�ɂȂ�q
	size_t size = 0;

public:
	List() {
		dummy = new Node();
		dummy->next = dummy;
		dummy->prev = dummy;
	};

	~List() {
		Clear();
		delete dummy;
	}

	// �������q���X�g�ŏ�����������
	List(std::initializer_list<T> list) : List() {
		for (auto p = list.begin(); p != list.end(); p++) {
			PushBack(*p);
		}
	}

	// �R�s�[�͂�����Ƃ߂�ǂ������̂ō���͋֎~��
	List(const List& o) = delete;
	List& operator=(const List& o) = delete;

	// ���[�u�Ȃ炦���񂿂Ⴄ
	List(List&& o) {
		this->dummy = o.dummy;
		o.dummy = nullptr;
	}
	List& operator=(List&& o) {
		this->dummy = o.dummy;
		o.dummy = nullptr;
		return this;
	}

	// �擪�v�f���w���C�e���[�^���擾
	Iterator Begin() const {
		return Iterator(dummy->next);
	}

	// �����v�f�̈����w���C�e���[�^���擾
	Iterator End() const {
		return Iterator(dummy);
	}

	// �C�ӈʒu�փA�N�Z�X����
	// �w��ʒu�����X�g�ɑ΂��ĕs���ȏꍇ��End()��Ԃ�
	// ���X�g�̃����_���A�N�Z�X�̑��p�͖{���͗ǂ��Ȃ��̂ł�߂悤
	Iterator At(size_t index) const {
		if (index >= size) return End();
		
		Iterator itr = Begin();
		for (size_t i = 0; i < index; i++) {
			itr++;
		}

		return itr;
	}

	size_t Size() const {
		return size;
	}

	bool Empty() const {
		return size == 0;
	}

	void PushBack(const T& o) {
		Node* newNode = new Node;
		newNode->data = new T(o);

		Node* end = dummy->prev;
		end->next = newNode;
		dummy->prev = newNode;
		newNode->prev = end;
		newNode->next = dummy;

		size++;
	}

	void PushFront(const T& o) {
		Node* newNode = new Node;
		newNode->data = new T(o);

		Node* begin = dummy->next;
		begin->prev = newNode;
		newNode->prev = dummy;
		newNode->next = begin;

		size++;
	}

	void PopBack() {
		if (size == 0) return;

		Node* end = dummy->prev;
		end->prev->next = dummy;
		dummy->prev = end->prev;

		if (end->data != nullptr) delete end->data;
		delete end;
		size--;
	}

	void PopFront() {
		if (size == 0) return;

		Node* begin = dummy->next;
		begin->next->prev = dummy;
		dummy->next = begin->next;
		
		if (begin->data != nullptr) delete begin->data;
		delete begin;
		size--;
	}

	// �w�肵���ʒu�̑O�ɗv�f��}������
	void Insert(const Iterator& iterator, const T& o) {
		Node* newNode = new Node;
		newNode->data = new T(o);

		Node* prev = iterator.node->prev;
		prev->next = newNode;
		newNode->prev = prev;
		newNode->next = iterator.node;
		iterator.node->prev = newNode;
		
		size++;
	}

	// �w�肵���ʒu�̗v�f���폜����
	Iterator Erase(const Iterator& iterator) {
		Node* node = iterator.node;

		Node* next = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node->data;
		delete node;
		size--;
		return next;
	}

	// �S�v�f���폜����
	void Clear() {
		if (size == 0) return;

		Node* now = dummy->next;
		Node* next = nullptr;
		while (now->data != nullptr) {
			next = now->next;
			delete now->data;
			delete now;
			now = next;
		}

		dummy->prev = dummy;
		dummy->next = dummy;
		size = 0;
	}
};