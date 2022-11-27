#ifndef MUF_H
#define MUF_H

/**
 * Class to hold makeset-union-find
*/
class MUF
{
private:
    int* dad, *rank;
    unsigned long size;
public:
    MUF(int);
    MUF(const MUF&);
    MUF& operator=(const MUF&);
    ~MUF();

    void MakeSet(int);
    void Union(int, int);
    int Find(int);
};

#endif