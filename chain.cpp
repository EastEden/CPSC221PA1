#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  /* your code here */
	clear();
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  /* your code here */
	Node* newNode = new Node(ndata);

	newNode->next = head_;
	
	if(length_==0){
		newNode->prev = head_;
		head_ -> next = newNode;
	}

	else{
		newNode->prev = walk(head_,length_);
		newNode->prev -> next = newNode;
		head_ -> prev = newNode;
	}

	length_++;
}

/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length. 
 */
void Chain::moveBack(int startPos, int len, int dist){
  /* your code here */
	if(len>0){
	

		Node* startNode = walk(head_,startPos);
		Node* endNode   = walk(head_,startPos+len-1);
		Node* beginNode;
		Node* destNode;

		beginNode = walk(head_,startPos-1);
	
		if(startPos+len-1+dist>length_){
			destNode = walk(head_, startPos + dist + len - 1);
		}
		else{
			destNode = walk(head_, startPos+len-1+dist);
		}

		beginNode -> next = endNode -> next;
		endNode -> next ->prev = beginNode;

		startNode -> prev = destNode;
		endNode -> next = destNode -> next;
		endNode -> next -> prev = endNode; 
		 
		destNode -> next = startNode;

	}

}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
void Chain::roll(int k){
  /* your code here */
	int startPos = 1;
	int len = length_ - k;
	int dist = k;

	moveBack(startPos,len,dist);
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  /* your code here */
	Node* startNodePrev = new Node();
	Node* endNodeNext = new Node();

	startNodePrev = walk(head_,pos1) -> prev;
	
	endNodeNext = walk(head_,pos2) -> next;
	
	Node* temp = walk(head_,pos1);

	for(int i=pos1;i<=pos2;i++){

		Node* record = new Node();
		record = temp -> next;

		if(i == pos1){
			temp->next = endNodeNext;
			endNodeNext->prev =temp; 
		}
		else{
			temp->next = temp->prev;
		}

		if(i == pos2){
			temp->prev = startNodePrev;
			startNodePrev->next= temp;
		}
		else{
			temp->prev = record;
		}

		temp = record;
	}

}

/*
* Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  /* your code here */
	
	Node* curr = new Node();
	Node* now = new Node();
	Node* record = new Node();
	now = head_ -> next;
	curr = other.head_ -> next;
	
	if(length_ != other.length_){
		cout << "Block sizes differ." << endl;
	}

	else{
		for(int i=0;i<other.length_;i++){

			other.head_ -> next = curr -> next;
			curr -> next -> prev = other.head_;

			curr -> prev = now;
			curr -> next = now -> next;

			now -> next = curr;
			now -> prev = now->prev->next;

			curr = other.head_ -> next;
			now = now -> next -> next;

			length_++;
		}
		head_->prev = walk(head_,length_);
	}

}	


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  /* your code here */
	Node* curr = head_ -> next;
	while(length_>1){
		curr = curr -> next;
		delete[] curr -> prev;
		length_--;
	}
	delete[] curr;
	length_--;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  /* your code here */
	Node* curr = other.head_;
    head_ = new Node();
    head_->next = head_;
    head_->prev = head_;
    length_ = 0;
	while(curr->next != other.head_){
		Block* copyData = new Block();
		*copyData = curr->data;
		insertBack(*copyData);
		curr = curr -> next;
	}

}
