#include "File.h"

Block File::getBlock(int index) const
{
	/* TODO */
	Node<Block>* temp = blocks.getNodeAtIndex(index);
	if(temp == NULL) return Block();
	else return temp->data;
}

size_t File::fileSize() const
{
	/* TODO */
    size_t size = 0;
    Node<Block>* curr = blocks.getFirstNode();
    while (curr) {
        size += curr->data.getSize();
        curr = curr->next;
    }
    return size;
}

int File::numBlocks() const
{
	/* TODO */
	return blocks.getSize();
}

bool File::isEmpty() const
{
	/* TODO */
	return blocks.isEmpty();
}

bool File::operator==(const File &rhs) const
{
	/* TODO */
	Node<Block>* curr = blocks.getFirstNode();
	Node<Block>* other = rhs.blocks.getFirstNode();
	if(curr == NULL && other == NULL && this->numBlocks() == rhs.numBlocks()) return true;
	else if(curr!=NULL && other!= NULL && this->numBlocks() == rhs.numBlocks()){
	    while(curr && other){
    	    if(curr->data == other->data) {
    	        curr = curr->next;
    	        other = other->next;
    	    }
    	    else{ 
    	        return false;
    	    }
	    }
	    if(curr) return false;
	    else if(other) return false;
	    else return true;
	}
    else return false;
}

void File::newBlock(const Block &block)
{
	/* TODO */
	blocks.append(block);
}

void File::removeBlock(int index)
{
	/* TODO */
	blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	/* TODO */
	blocks.mergeNodes(sourceIndex, destIndex);
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}