#include <iostream>
#include <CreateIndexAPP.h>

using namespace std;


// ./CreateIndex [RELATION] filename [ATTRIBUTE] attributeOrder [TYPE] simple/complex
int main(int argc, char* argv[])
{

	if(argc != 4) cout<<"Please follow the format below: \n./CreateIndex [RELATION] filename [ATTRIBUTE] attributeOrder [TYPE] simple/complex";
	else CreateIndexAPP::CreateIndex(argv[1],atoi(argv[2]),argv[3]);

    return 0;
}
