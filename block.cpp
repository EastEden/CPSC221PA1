#include "block.h"

using namespace std;
using namespace cs221util;

void Block::build(PNG & im, int column, int width){
	for(int i=0;i<width;i++){                								//i is the width of the block
		data.push_back(std::vector<HSLAPixel>());
		for(unsigned int j=0;j<im.height();j++){							//j is the height of the block
			data[i].push_back(*im.getPixel(column+i,j));
		}
	}
}

void Block::render(PNG & im, int column) const{
	for(unsigned int i=0;i<data.size();i++){
		for(unsigned int j=0;j<data[0].size();j++){
			HSLAPixel *hp = im.getPixel(column+i,j);
			*hp = data.at(i).at(j);
		}
	}
} 

void Block::greyscale(){
	for(unsigned int i=0;i<data.size();i++){
		for(unsigned int j=0;j<data[0].size();j++){
			data.at(i).at(j).s = 0.0;
		}
	}
}

int Block::width() const{
	return data.at(0).size();
}

int Block::height() const{
	return data.size();
}
