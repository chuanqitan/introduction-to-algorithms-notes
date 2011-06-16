#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include "graphics.h"

using namespace std;


namespace ita
{
    /// �õ���������
    GrpahicsViaAdjacencyMatrix<string, int> GetResidualNetwork( GrpahicsViaAdjacencyMatrix<string, int> &g, vector<vector<int>> &f )
    {
        GrpahicsViaAdjacencyMatrix<string, int> gplus( g.GetVertex(), Digraph );

        for ( int i = 0; i < g.GetVertex().size(); ++i )
        {
            for ( int j = i + 1; j < g.GetVertex().size(); ++j )
            {
                if ( g.IsLinked( i, j ) || g.IsLinked( j, i ) )
                {
                    gplus.Link2Vertex( i, j, g.GetEdge()[i][j] - f[i][j] + f[j][i] );
                    gplus.Link2Vertex( j, i, g.GetEdge()[i][j] + g.GetEdge()[j][i] - gplus.GetEdge()[i][j] );
                }
            }
        }

        return gplus;
    }

    /// ���ù�������㷨�õ�����·��
    vector<int> GetAugmentingPath( GrpahicsViaAdjacencyMatrix<string, int> &g )
    {
        vector<int> path;

        //q��һ������pair<Ҫ�����Ľ��ı�ţ��ڸù������·�������ĸ����>
        queue<int> q;
        //ÿһ������������ȱ����е�ǰ�ĸ����
        vector<int> parent( g.GetVertex().size() );
        //��ʶһ������Ƿ񱻷��ʹ���
        vector<bool>	trivaled( g.GetVertex().size(), false );

        //��s==0�Ľ�㿪ʼ
        q.push( 0 );
        parent[0] = -1;
        trivaled[0] = true;

        while( !q.empty() )
        {
            int front = q.front();
            for ( int i = 0; i < g.GetVertex().size(); ++i )
            {
                if ( !trivaled[i] && g.IsLinked( front, i ) )
                {
                    q.push( i );
                    parent[i] = front;
                    trivaled[i] = true;

                    if ( i == g.GetVertex().size() - 1 )
                    {
                        //�ҵ���t��㡣���������·��
                        int current_index = i;
                        while( current_index != -1 )
                        {
                            path.push_back( current_index );
                            current_index = parent[current_index];
                        }

                        //��תΪ����·��������
                        reverse( path.begin(), path.end() );
                        break;
                    }
                }
            }
            q.pop();
        }

        return path;
    }

    /// FordFulkerson������㷨
    int FordFulkerson( GrpahicsViaAdjacencyMatrix<string, int> &g )
    {
        int const n = g.GetVertex().size();
        vector<vector<int>> f( n, vector<int>( n, 0 ) );

        while ( true )
        {
            //�õ���������
            auto gplus = GetResidualNetwork( g, f );
            auto a_path = GetAugmentingPath( gplus );
            if ( a_path.empty() )
            {
                //����·��Ϊ�գ�ѭ������
                break;
            }

            vector<int> path_values;
            for ( int i = 0; i < a_path.size() - 1; ++i )
            {
                path_values.push_back( gplus.GetEdge()[a_path[i]][a_path[i + 1]] );
            }
            int min_path_value = *min_element( path_values.begin(), path_values.end() );

            for ( int i = 0; i < a_path.size() - 1; ++i )
            {
                int u = a_path[i];
                int v = a_path[i + 1];

                f[u][v] += min_path_value;

				//�㷨����P405ҳ����һ�䡣����ԭ���Ϻ�������һ���ǲ�Ӧ���еģ�������ʵҲ֤��������һ����Ǵ����
				//�����ˣ�Ҳ���������ϵ�һ��bug�ɣ�
                //f[v][u] = -f[u][v];
            }
        }

        return accumulate( f[0].begin(), f[0].end(), 0 );
    }



    void testFordFulkerson()
    {
        cout << "FordFulkerson�����" << endl;
        //����P397ҳ��ͼ26-1(a)
        vector<string> v;
        v.push_back( "s" );
        v.push_back( "v1" );
        v.push_back( "v2" );
        v.push_back( "v3" );
        v.push_back( "v4" );
        v.push_back( "t" );
        GrpahicsViaAdjacencyMatrix<string, int> g( v, Digraph );
        g.Link2Vertex( 0, 1, 16 );
        g.Link2Vertex( 0, 2, 13 );
        g.Link2Vertex( 1, 3, 12 );
        g.Link2Vertex( 1, 2, 10 );
        g.Link2Vertex( 2, 1, 4 );
        g.Link2Vertex( 2, 4, 14 );
        g.Link2Vertex( 3, 2, 9 );
        g.Link2Vertex( 3, 5, 20 );
        g.Link2Vertex( 4, 3, 7 );
        g.Link2Vertex( 4, 5, 4 );

        cout << FordFulkerson( g ) << endl;
    }
}