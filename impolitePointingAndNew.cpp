#include <cstdio>

class Distance{
private:
	int feet;
	float inches;

public:
	void getDist(){ //get length from user
		printf("\nEnter feet: ");
		scanf("%d", &feet);
		printf("\nEnter inches: ");
		scanf("%f", &inches);
	}
	void showDist(){//Display distance
		printf("%d feet - %f inches\n",feet, inches);
	}
};

int main(int argc, char **argv){
	Distance dist;		//Define a Distance object
	dist.getDist();		//access object mems
	dist.showDist();

	Distance *distPtr;		//pointer to Distance
	distPtr=new Distance;	//points to new Distance obj
	distPtr->getDist();		//now with -> op
	distPtr->showDist();
	printf("\n\n");

	return 0;

}
