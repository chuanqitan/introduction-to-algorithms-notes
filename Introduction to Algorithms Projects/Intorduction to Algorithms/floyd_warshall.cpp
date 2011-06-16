#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include <limits>
#include "graphics.h"

using namespace std;


namespace ita
{
    void FloydWarshall()
    {
        cout << "FloydWarshall最短路径" << endl;
        //生成P384页的图25-1
        vector<int> v;
        v.push_back( 1 );
        v.push_back( 2 );
        v.push_back( 3 );
        v.push_back( 4 );
        v.push_back( 5 );
        GrpahicsViaAdjacencyMatrix<int, int> g( v, Digraph );
        g.Link2Vertex( 0, 1, 3 );
        g.Link2Vertex( 0, 2, 8 );
        g.Link2Vertex( 0, 4, -4 );
        g.Link2Vertex( 1, 4, 7 );
        g.Link2Vertex( 1, 3, 1 );
        g.Link2Vertex( 2, 1, 4 );
        g.Link2Vertex( 3, 2, -5 );
        g.Link2Vertex( 3, 0, 2 );
        g.Link2Vertex( 4, 3, 6 );

        int const n = v.size();	//顶点的个数
        vector<vector<vector<int>>> D( n + 1, vector<vector<int>>( n, vector<int>( n, 0 ) ) );

        for ( int i = 0; i < n; ++i )
        {
            for ( int j = 0; j < n; ++j )
            {
                D[0][i][j] = numeric_limits<int>::max();
                if ( i == j )
                {
                    D[0][i][j] = 0;
                }
                if ( g.GetEdge()[i][j] != 0 )
                {
                    D[0][i][j] = g.GetEdge()[i][j];
                }
            }
        }

        for ( int k = 1; k <= n; ++k )
        {
            //中间结点允许为[0 ... k-1]的情况
            for ( int i = 0; i < n; ++i )
            {
                for ( int j = 0; j < n; ++j )
                {
                    D[k][i][j] = min( D[k - 1][i][j]
                                      , ( D[k - 1][i][k - 1] == numeric_limits<int>::max() || D[k - 1][k - 1][j] == numeric_limits<int>::max()
                                          ? numeric_limits<int>::max()
                                          : D[k - 1][i][k - 1] + D[k - 1][k - 1][j] ) );
                }
            }
        }

        for ( int i = 0; i < n; ++i )
        {
            for ( int j = 0; j < n; ++j )
            {
                cout << D[n][i][j] << "  ";
            }
            cout << endl;
        }
    }
}