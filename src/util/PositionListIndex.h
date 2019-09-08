//
// Created by kek on 30.07.2019.
//

#pragma once

#include <vector>
#include <memory>
#include "../model/Column.h"

using std::vector, std::shared_ptr;

class ColumnLayoutRelationData;

class PositionListIndex {
private:
    vector<vector<int>> index;
    vector<int> nullCluster;
    int size;
    double entropy;
    long nep;
    unsigned int relationSize;
    unsigned int originalRelationSize;
    vector<int> probingTableCache;

    PositionListIndex(vector<vector<int>> index, vector<int> nullCluster, int size, double entropy,
                      long nep, unsigned int relationSize, unsigned int originalRelationSize);

    static long calculateNep(long numElements);
    static void sortClusters(vector<vector<int>> & clusters);
    static bool takeProbe(int position, ColumnLayoutRelationData & relationData, Vertical & probingColumns, vector<int> & probe);

public:
    static const int singletonValueId;
    static shared_ptr<PositionListIndex> createFor(vector<int>& data, bool isNullEqNull);
    vector<int> getProbingTable();
    vector<int> getProbingTable(bool isCaching);
    vector<vector<int>> & getIndex();
    long getNep() const { return nep; }           //ADDED: getNep()

    shared_ptr<PositionListIndex> intersect(shared_ptr<PositionListIndex> that);
    shared_ptr<PositionListIndex> probe(vector<int> probingTable);
    shared_ptr<PositionListIndex> probeAll(Vertical probingColumns, ColumnLayoutRelationData & relationData);
};