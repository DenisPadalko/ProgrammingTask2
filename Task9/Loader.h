#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Loader
{
public:
    virtual const vector<string>& Load() const = 0;
};

class ConsoleLoader : public Loader
{
public:
    virtual const vector<string>& Load() const override;
};

class FileLoader : public Loader
{
public:
    virtual const vector<string>& Load() const override;
};