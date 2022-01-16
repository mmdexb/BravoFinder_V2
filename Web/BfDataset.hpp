//
// Created by Webster Zhang on 2022/1/16.
//

#include <memory>
#include <iostream>
#include "bfhandler.hpp"

using namespace std;

class BfDataset
{
private:
    BfDataset() {
        dataset = std::shared_ptr<bf::DataSet>(new bf::DataSet);
        dataset->SetDataPath("/media/psf/Home/Documents/Coding/VATPRC/BravoFinder/PMDG");
        dataset->Initialize();
    };
    ~BfDataset() {
        dataset = nullptr;
    };
    BfDataset(const BfDataset&);
    BfDataset& operator=(const BfDataset&);
public:
    shared_ptr<bf::DataSet> dataset;

    static BfDataset& getInstance()
    {
        static BfDataset instance;
        return instance;
    }
};