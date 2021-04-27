#include "AdjMatrixUndirGraph.h"		// �ڽӾ�������ͼ
#include <iostream>
#include <fstream>
#include "Kruskal.h"
#include "Assistance.h"
#include "ShortestPath_Dij.h"
int jc(int n) {
	int count = n;
	for (int i = n - 1; i > 1; i--) {
		count = count * i;
	}
	return count;
}

using namespace std;
int main(void)
{
	try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		int N, M;
		ifstream file("test3.txt", ios::in);
		int count_ = 0;
		if (!file)
		{
			cout << "���ļ�ʧ��";
			return 0;
		}
		file >> N;
		char* vexs = new char[N];
		for (int i = 0; i < N; i++) file >> vexs[i];
		file >> M;
		AdjMatrixUndirGraph<char> g(vexs, N, 10);
		AdjMatrixUndirGraph<char> g_1(vexs, N, 10), g_2(vexs, N, 10);
		KruskalEdge<char, int>* e_all;//���б�����
		int* a;
		a = new int[M];
		int cost = 0; int cost_1 = 0;

		e_all = new KruskalEdge < char, int>[M];
		for (int i = 0; i < M; i++) {
			if (i < N - 1)
				a[i] = 1;
			else
				a[i] = 0;
		}

		DFSTraverse<char>(g, Write<char>);

		cout << endl << "=================" << endl;
		char c = '0', e, e1, e2;
		int v, v1, v2, w; //w��ʾȨ�أ�����·����
		for (int i = 0; i < M; i++)
		{
			file >> e1;
			file >> e2;
			file >> w;
			e_all[i].vertex1 = e1;
			e_all[i].vertex2 = e2;
			e_all[i].weight = w;
			v1 = g.GetOrder(e1);
			v2 = g.GetOrder(e2);
			g.InsertArc(v1, v2, w);
		}
		for (int i = 0; i < M; i++) {
			cout << e_all[i].vertex1 << " " << e_all[i].vertex2 << " " << e_all[i].weight << endl;
		}

		cout << endl << "���֮�乫·���ڽӾ���Ϊ��" << endl;
		if (g.IsEmpty()) cout << "��ͼΪ�ա�" << endl;
		else  g.Display();
		while (c != '4') {
			cout << endl << "1. �����ʽ����ͨ·����";
			cout << endl << "2. �������ҽԺ�����";
			cout << endl << "3. ��·ϵͳ";
			cout << endl << "4. �˳�";
			cout << endl << "ѡ����(0~4):";
			cin >> c;
			switch (c) {
			case '1':
				cost = MiniSpanTreeKruskal(g);
				cout << "**********************" << endl;
				//					g_2 = g;

				for (int i = 0; i < (jc(M) / (jc(N - 1) * jc(M - N + 1))); i++) {
					g_2 = g_1;
					for (int n = 0; n < M; n++) {
						if (a[n] == 1) {
							v1 = g.GetOrder(e_all[n].vertex1);
							v2 = g.GetOrder(e_all[n].vertex2);
							g_2.InsertArc(v1, v2, e_all[n].weight);
						}
					}
					/**/
					for (int n = 0; n < M; n++) {
						cout << a[n] << " ";
					}
					cout << endl;

					DFS(g_2, 0, Write<char>);
					cout << endl << "=================" << endl;
					int c0 = 0;
					int c1 = 0;
					int flag_ = 0;
					for (int i = 0; i < g_2.GetVexNum(); i++) {
						if (g_2.GetTag(i) == UNVISITED) {
							flag_ = 1;
						}
					}

					if (flag_ == 0) {
						cost_1 = g_2.Get_tree_value();
						if (cost_1 == cost) {

							cost_1 = MiniSpanTreeKruskal(g_2);
							count_++;
						}
					}



					//if (g_2.IsCon()==0) {
					for (int j = 0; j < M; j++) {

						if (a[j] == 1 && a[j + 1] == 0) {//����10
							a[j] = 0;
							a[j + 1] = 1;

							break;
						}
						if (a[j] == 0)
							c0++;
						if (a[j] == 1)
							c1++;
					}
					for (int i = 0; i < c1; i++) {
						a[i] = 1;
					}
					for (int i = 0; i < c0; i++) {
						a[i + c1] = 0;
					}

				}

				cout << "�����У�" << count_;
				//					MiniSpanTreeKruskal(g_2);

				break;
			case '2':
				int** distt, ** pathh;
				// ����洢�ռ�
				distt = new int* [g.GetVexNum()], pathh = new int* [g.GetVexNum()];
				for (int i = 0; i < g.GetVexNum(); i++) {
					distt[i] = new int[g.GetVexNum()];
					pathh[i] = new int[g.GetVexNum()];
				}
				ShortestPathFloyd(g, pathh, distt);	// ��Floyd�㷨�����·��
				DisplayHospitalLocation(g, pathh, distt);// ��ʾ���·�� 
				cout << endl;

				// �ͷŴ洢�ռ�
				for (int j = 0; j < g.GetVexNum(); j++) {
					delete[]distt[j];
					delete[]pathh[j];
				}
				delete[]distt; delete[]pathh;
				break;
			case '3':
				cout << endl << "�����ѯ���A��B";
				cin >> e1 >> e2;
				v1 = g.GetOrder(e1);
				v2 = g.GetOrder(e2);
				DisplayShortAB(v1, v2,g);
				break;
			}
		}
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}