#include<iostream>
#include<vector>

using namespace std;

class Elements{

    private:
    vector<int> elements;

    public:
    Elements(){}

    Elements(int capacity){
        elements = vector<int>(capacity, -1);
    }

    int findParent(int element){  
        return elements[element]<0?element:findParent(elements[element]);
    }

    void unify(int firstElement, int secondElement){

        int firstElementParent = findParent(firstElement);
        int secondElementParent = findParent(secondElement);

        cout<<"firstElement="<<firstElement<<" firstElementParent="<<firstElementParent<<" secondElement="<<secondElement<<" secondElementParent="<<secondElementParent<<endl;

        if(firstElementParent==secondElementParent)
            return;
        
        if(elements[firstElementParent]<=elements[secondElementParent]){
            elements[firstElementParent] += elements[secondElementParent];
            elements[secondElementParent] = firstElementParent;
        }
        else{
            elements[secondElementParent] += elements[firstElementParent];
            elements[firstElementParent] = secondElementParent;
        }
    }

    void deleteElement(int elementIndex){

        int parentIndex = findParent(elementIndex);

        if(parentIndex==elementIndex){

            //Scan throu and pick a parent
            int newParent;
            for(int index = 0; index<elements.size(); index++){
                if(elements[index]==elementIndex){
                    newParent = index;
                    break;
                }
            }

            elements[newParent] = elements[parentIndex]-1;
            elements[parentIndex] = -1;

            for(int index = 0; index<elements.size(); index++){

                if(elements[index]==parentIndex){
                    elements[index] = newParent;
                }

            }


        }
        else{
            elements[parentIndex]+=1;
            elements[elementIndex] = -1;
        }

    }

    void printVector(){
        for(int element: elements){
            cout<<element<<"\t";
        }
        cout<<endl;
    }



};

int main(){

    Elements* elementSet = new Elements(4);

    elementSet->unify(0,1);
    elementSet->printVector();

    elementSet->unify(1,2);
    elementSet->printVector();

    elementSet->unify(2,3);
    elementSet->printVector();

    elementSet->deleteElement(2);
    elementSet->printVector();

    return 0;
}
