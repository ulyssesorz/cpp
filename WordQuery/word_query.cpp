#include "TextQuery.h"
#include"Query.h"

int main()
{
    ifstream infile("infile.txt");
    TextQuery tq(infile);
    //print(cout, tq.query("Alice"));

    Query q1 = Query("fiery") & Query("bird") | Query("wind");
    Query q2 = Query("long");
    Query q3 = ~Query("red");
    print(cout, q1.eval(tq));
    print(cout, q2.eval(tq));
    print(cout, q3.eval(tq));
    return 0;
}