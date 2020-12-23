//
// Created by gonzaga on 1/20/16.
//

#ifndef CREATEINDEX_CREATEINDEXAPP_H
#define CREATEINDEX_CREATEINDEXAPP_H

#include "ArboretumAPI.h"
#include <iostream>
#include <string>
#include <sstream>
#include <sfp/simple_file_parser.h>
using namespace std;

class CreateIndexAPP
{
public:
    static void CreateIndex(string filename, int attributeIndex, string indexType);
};


#endif //CREATEINDEX_CREATEINDEXAPP_H
