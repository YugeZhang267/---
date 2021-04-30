//ShortestPath_Dij.h
#ifndef SHORTESTPATH_DIJ_H_
#define SHORTESTPATH_DIJ_H_
#include "Assistance.h"	
#include <iostream>
#include "AdjMatrixUndirGraph.h"
#include "LinkStack.h"

template<class ElemType>
void DisplayShortAB(const int v1, const int v2, AdjMatrixUndirGraph<ElemType> &g)
//��ʾA�嵽B������·��
{
	int* path = new int[g.GetVexNum()];
	int* dist = new int[g.GetVexNum()];
	ShortestPathDij(v1, path, dist,g);
	if (dist[v2] == g.GetInfinity())
	{
		ElemType e1, e2;
		g.GetElem(v1, e1);
		g.GetElem(v2, e2);
		cout << e1 << "��" << e2 << "����ͨ!" << endl;
	}
	else
	{
		LinkStack<int> ls;
		ls.Push(v2);
		for (int i = path[v2]; i != -1; i = path[i])
			ls.Push(i);
		int index;
		ls.Pop(index);
		ElemType e;
		g.GetElem(index, e);
		cout << e;
		for (ls.Pop(index); !ls.IsEmpty(); ls.Pop(index))
		{
			g.GetElem(index, e);
			cout << " -> " << e;
		}
		g.GetElem(v2, e);
		cout << " -> " << e;
		cout << "   ���·������Ϊ��" << dist[v2] << endl;
	}
}


template<class ElemType>
void ShortestPathDij(int v0, int* path, int* dist,AdjMatrixUndirGraph<ElemType>& g)
//ʹ�õϽ�˹�����㷨�ҵ���Դ��v0��������������·��
{
	int v, u, MinVal;
	int num = g.GetVexNum();
	for (v = 0; v < num; v++)
	{
		dist[v] = g.GetWeight(v0,v);
		if (dist[v] == g.GetInfinity() || dist[v] == 0)   //v0��v֮��û��ֱ��·��
			path[v] = -1;
		else
		{
			path[v] = v0;
		}
		g.SetTag(v,UNVISITED);      //��ʼ�����ж����tagΪUNVISITED
	}
	g.SetTag(v0,VISITED);
	for (int i = 1; i < num; i++)      //�ҵ���ǰ�������Сֵ
	{
		MinVal = 1000;
		u = v0;
		for (v = 0; v < num; v++)
		{
			if (g.GetTag(v) == UNVISITED && dist[v] < MinVal)
			{
				u = v;
				MinVal = dist[v];
			}
		}
		g.SetTag(u, VISITED);         //��u���뼯��U��
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))
		{
			if (g.GetTag(v) == UNVISITED && dist[v] > MinVal + g.GetWeight(u,v))
			{
				dist[v] = MinVal + g.GetWeight(u, v);
				path[v] = u;
			}
		}
	}
}



#endif

