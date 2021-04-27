#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__
#include "Assistance.h"					// ���������
#include "MineHeap.h"
#include "UFSets.h"
//#include "Kruskal.h"
#include "LinkStack.h"



// ����ͼ���ڽӾ�����
template <class ElemType>
class AdjMatrixUndirGraph
{
protected:
	// �ڽӾ�������ݳ�Ա:
	int vexNum, vexMaxNum, arcNum;			// ������Ŀ������Ķ��������Ŀ�ͱ���
	int** arcs;							    // ��ű���Ϣ�ڽӾ���
	ElemType* vertexes;						// ��Ŷ�����Ϣ������
	mutable Status* tag;					// ��־����
	int Infinity;                           // �������
public:
	// �ڽӾ������͵ķ�������:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, int infin = DEFAULT_INFINITY);
	// ������es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE, int infin = DEFAULT_INFINITY);
	// ��������Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	~AdjMatrixUndirGraph();					// ��������
	void Clear();			              // ���ͼ
	bool IsEmpty();                 // �ж�����ͼ�Ƿ�Ϊ��
	int GetOrder(ElemType& d) const;// �󶥵�����
	Status GetElem(int v, ElemType& d) const;// �󶥵��Ԫ��ֵ
	Status SetElem(int v, const ElemType& d);// ���ö����Ԫ��ֵ
	int GetVexNum() const;					// ���ض������
	int GetWeight(const int& v1, const int& v2);
	int GetArcNum() const;					// ���ر���
	int GetEdgeNum();
	int FirstAdjVex(int v) const;		// ���ض���v�ĵ�һ���ڽӵ�
	int NextAdjVex(int v1, int v2) const;		 // ���ض���v1�������v2����һ���ڽӵ�
	void InsertVex(const ElemType& d);			 // ����Ԫ��ֵΪd�Ķ���
	void InsertArc(int v1, int v2, int weight);			     // ���붥��Ϊv1��v2�ı�
	void DeleteVex(const ElemType& d);			 // ɾ��Ԫ��ֵΪd�Ķ���
	void DeleteArc(int v1, int v2);			     // ɾ������Ϊv1��v2�ı�
	Status GetTag(int v) const;			         // ���ض���v�ı�־
	void SetTag(int v, Status val) const;	   // ���ö���v�ı�־Ϊval
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType>& g);	// ���ƹ��캯��
	AdjMatrixUndirGraph<ElemType>& operator =(const AdjMatrixUndirGraph<ElemType>& g);
	// ��ֵ�������
	void Display();	                         // ��ʾ�ڽӾ�������ͼ
	//void DisplayShortAB(const int v1, const int v2);      //��ʾA�嵽B������·��
	//void ShortestPathDij(int v0, int* path, int* dist);   //ʹ�õϽ�˹�����㷨�ҵ���Դ��v0��������������·��
//  void All_mintree();
	int Get_tree_value();
	void ShortestPathFloyd(const AdjMatrixUndirGraph<ElemType>& g, int** path, int** dist);
	void DisplayHospitalLocation(const AdjMatrixUndirGraph<ElemType>& g, int** path, int** dist);
	int GetInfinity()const;
};

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::Get_tree_value()
{
	int c = 0;
	for (int i = 0; i < vexNum; i++) {
		for (int j = 0; j < vexNum; j++) {
			if (GetWeight(i, j) != Infinity)
				c += GetWeight(i, j);
		}
	}
	return c / 2;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetWeight(const int& v1, const int& v2)
{
	return arcs[v1][v2];
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetEdgeNum()
{
	return arcNum;
}
/*
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::All_mintree()
{
	int count, VexNum = GetVexNum();
	KruskalEdge<ElemType, char> KEdge;
	MinHeap<KruskalEdge<ElemType, char> > ha(g.GetEdgeNum());
	ElemType* kVex, v1, v2;
	kVex = new ElemType[VexNum];	// ���嶥������,�洢������Ϣ
	for (int i = 0; i < VexNum; i++)
		g.GetElem(i, kVex[i]);
	UFSets<ElemType> f(kVex, VexNum);// ���ݶ������鹹�첢�鼯
	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
			if (v < u) {	// ��v < u�ı߲��뵽��С��
				g.GetElem(v, v1);
				g.GetElem(u, v2);
				KEdge.vertex1 = v1;
				KEdge.vertex2 = v2;
				KEdge.weight = g.GetWeight(v, u);
				ha.Insert(KEdge);
			}
	count = 0;					    // ��ʾ�Ѿ���ѡ�ı���

	while (count < VexNum - 1) {
		ha.DeleteTop(KEdge);        // �ӶѶ�ȡһ����
		v1 = KEdge.vertex1;
		v2 = KEdge.vertex2;
		if (f.Differ(v1, v2)) {	// ���������������㲻��ͬһ������
			cout << "��:( " << v1 << ", " << v2 << " ) Ȩ:" << KEdge.weight << endl; // ����߼�Ȩֵ
			f.Union(v1, v2);		// �������������ڵ����ϲ���һ����
			count++;
		}
	}
}
*/
// ����ͼ���ڽӾ������ʵ�ֲ���
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum, int infin)
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ

{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	Infinity = infin;

	vertexes = new ElemType[vexMaxNum];      // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			       // ���ɱ�־����
	arcs = (int**)new int* [vexMaxNum];     // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
		{
			if (u == v) arcs[v][u] = 0;
			else arcs[v][u] = Infinity;
		}
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexMaxNum, int infin)
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	Infinity = infin;

	vertexes = new ElemType[vexMaxNum];     // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			      // ���ɱ�־����
	arcs = (int**)new int* [vexMaxNum];    // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.
{
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// ����������ͷŶ�����ռ�õĿռ�
{
	delete[]vertexes;					// �ͷŶ�������
	delete[]tag;						    // �ͷű�־

	for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
		delete[]arcs[v];
	delete[]arcs;					    // �ͷ��ڽӾ���
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetOrder(ElemType& d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ������-1.
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			return v;	    // ����d����,�����������
	return -1;	        // ����d������,����-1
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType& d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v��Χ��,����Ԫ�ز�����
	else {
		d = vertexes[v];	  // ������v��Ԫ��ֵ����d
		return ENTRY_FOUND;	// ����Ԫ�ش���
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType& d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v��Χ��,����λ�ô�
	else {
		vertexes[v] = d;		// ������Ԫ�ص�ֵ��Ϊd
		return SUCCESS;		  // �����޸ĳɹ�
	}
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
// ������������ض������
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetArcNum() const
// ������������ر���
{
	return arcNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�����
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");// �׳��쳣

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0 && arcs[v][u] != Infinity)
			return u;

	return -1;					// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw
		Error("v1���ܵ���v2!");		// �׳��쳣

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0 && arcs[v1][u] != Infinity)
			return u;

	return -1;						// ����-1��ʾ����һ���ڽӵ�
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType& d)
// ������������붥��d
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�Ķ��������ܳ�������������!");	// �׳��쳣

	vertexes[vexNum] = d;
	tag[vexNum] = UNVISITED;
	for (int v = 0; v <= vexNum; v++) {
		arcs[vexNum][v] = 0;
		arcs[v][vexNum] = 0;
	}
	vexNum++;
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertArc(int v1, int v2, int weight)
// ���������������������v1��v2�ı�
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] == Infinity) {	  // ԭ����ͼ��û�б�(v1, v2)
		arcNum++;
		arcs[v1][v2] = weight;
		arcs[v2][v1] = weight;
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType& d)
// ���������ɾ��Ԫ��Ϊd�Ķ���
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			break;
	if (v == vexNum)
		throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

	for (int u = 0; u < vexNum; u++)             // ɾ���붥��d������ı�
		if (arcs[v][u] != 0) {
			arcNum--;
			arcs[v][u] = Infinity;
			arcs[u][v] = Infinity;
		}

	vexNum--;
	if (v < vexNum) {
		vertexes[v] = vertexes[vexNum];
		tag[v] = tag[vexNum];
		for (int u = 0; u <= vexNum; u++)
			arcs[v][u] = arcs[vexNum][u];
		for (int u = 0; u <= vexNum; u++)
			arcs[u][v] = arcs[u][vexNum];
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteArc(int v1, int v2)
// ���������ɾ����������v1��v2�ı�
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] != Infinity) {	// ԭ����ͼ���ڱ�(v1, v2)
		arcNum--;
		arcs[v1][v2] = Infinity;
		arcs[v2][v1] = Infinity;
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType>& g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;
	Infinity = g.Infinity;

	vertexes = new ElemType[vexMaxNum];		// ���ɶ�����������
	tag = new Status[vexMaxNum];			// ���ɱ�־����
	arcs = (int**)new int* [vexMaxNum];	// �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {	// ���ƶ�����������
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>& AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType>& g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&g != this) {
		delete[]vertexes;				// �ͷŶ�������
		delete[]tag;						  // �ͷű�־

		for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
			delete[]arcs[v];
		delete[]arcs;					  // �ͷ��ڽӾ���
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;
		Infinity = g.Infinity;

		vertexes = new ElemType[vexMaxNum];	 // ���ɶ�����������
		tag = new Status[vexMaxNum];			   // ���ɱ�־����
		arcs = (int**)new int* [vexMaxNum]; // �����ڽӾ���
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++) {	 // ���ƶ�����������
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
				arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Display()
// �������: ��ʾ�ڽӾ�������ͼ
{

	for (int v = 0; v < vexNum; v++)
		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++) {
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
		{
			if (arcs[v][u] != Infinity)
				cout << "\t" << arcs[v][u];
			else
			{
				cout << "\t" << "��";
			}
		}
		cout << endl;
	}
}

/*
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::ShortestPathDij(int v0, int* path, int* dist)
//���õϽ�˹�����㷨���Դ��v0�������������·��
{
	int v, u, MinVal;
	for (v = 0; v < vexNum; v++)
	{
		dist[v] = arcs[v0][v];
		if (dist[v] == Infinity || dist[v] == 0)   //v0��v֮��û��ֱ��·��
			path[v] = -1;
		else
		{
			path[v] = v0;
		}
		tag[v] = UNVISITED;      //��ʼ�����ж����tagΪUNVISITED
	}
	tag[v0] = VISITED;
	for (int i = 1; i < vexNum; i++)      //�ҵ���ǰ�������Сֵ
	{
		MinVal = 1000;
		u = v0;
		for (v = 0; v < vexNum; v++)
		{
			if (GetTag(v) == UNVISITED && dist[v] < MinVal)
			{
				u = v;
				MinVal = dist[v];
			}
		}
		SetTag(u, VISITED);         //��u���뼯��U��
		for (v = FirstAdjVex(u); v != -1; v = NextAdjVex(u, v))
		{
			if (GetTag(v) == UNVISITED && dist[v] > MinVal + arcs[u][v])
			{
				dist[v] = MinVal + arcs[u][v];
				path[v] = u;
			}
		}
	}
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DisplayShortAB(const int v1, const int v2)
{
	int* path = new int[vexNum];
	int* dist = new int[vexNum];
	ShortestPathDij(v1, path, dist);
	LinkStack<int> ls;
	ls.Push(v2);
	for (int i = path[v2]; i != -1; i = path[i])
		ls.Push(i);
	int index;
	ls.Pop(index);
	cout << vertexes[index];
	for (ls.Pop(index); !ls.IsEmpty(); ls.Pop(index))
		cout << " -> " << vertexes[index];
	cout << " -> " << vertexes[v2];
}

*/

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetInfinity()const
{
	return Infinity;
}

template <class ElemType>
void ShortestPathFloyd(AdjMatrixUndirGraph<ElemType>& g, int** path, int** dist)
// �������: ��Floyd�㷨��������g�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
	for (int u = 0; u < g.GetVexNum(); u++)
		for (int v = 0; v < g.GetVexNum(); v++)
		{	// ��ʼ��path��dist
			dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < g.GetInfinity())
				path[u][v] = u;	// ���ڱ�<u,v>
			else
				path[u][v] = -1;											// �����ڱ�<u,v>
		}

	for (int k = 0; k < g.GetVexNum(); k++)
		for (int i = 0; i < g.GetVexNum(); i++)
			for (int j = 0; j < g.GetVexNum(); j++)
				if (dist[i][k] != DEFAULT_INFINITY && dist[k][j] != DEFAULT_INFINITY
					&& dist[i][k] + dist[k][j] < dist[i][j]) {
					// ��i��k�ٵ�j��·�����ȸ���
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
}

template <class ElemType>
void DisplayHospitalLocation(const AdjMatrixUndirGraph<ElemType>& g, int** path, int** dist)
{
	int sum_of_dist = 0;//��·���ܳ���
	int shortest_sum_of_dist = 0;//����̵�·���ܳ���
	int temp_location_v = 0;//����ʱȷ����ҽԺλ�ñ��
	ElemType e1, e2;
	ElemType temp_location_e;//����ʱȷ����ҽԺλ��
	for (int v1 = 0; v1 < g.GetVexNum(); v1++)
	{
		for (int v2 = 0; v2 < g.GetVexNum(); v2++)
		{
			if (v1 != v2)
			{
				g.GetElem(v1, e1);
				g.GetElem(v2, e2);
				sum_of_dist += dist[v1][v2];
			}
		}
		cout << endl << "��ҽԺ���� " << e1 << "�������������嵽ҽԺ��·���ܳ���Ϊ: " << sum_of_dist;
		if (v1 == 0)
		{
			shortest_sum_of_dist = sum_of_dist;
		}

		if (sum_of_dist < shortest_sum_of_dist)
		{
			shortest_sum_of_dist = sum_of_dist;
			temp_location_v = v1;
		}
		sum_of_dist = 0;
	}
	g.GetElem(temp_location_v, temp_location_e);
	cout << endl << endl << "���ϣ��������ҽԺ���� " << temp_location_e << " ʱ��������̵�·���ܳ���Ϊ��" << shortest_sum_of_dist;
	cout << endl << endl << "�ʽ��齫���ҽԺ���ڣ�" << temp_location_e << endl;
}
#endif

/*template <class ElemType>
void ShortestPathFloyd(const AdjMatrixUndirGraph<ElemType>& g, int** path, int** dist)
// �������: ��Floyd�㷨��������g�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
	for (int u = 0; u < g.GetVexNum(); u++)
		for (int v = 0; v < g.GetVexNum(); v++)
		{	// ��ʼ��path��dist
			dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < g.GetInfinity())
				path[u][v] = u;	// ���ڱ�<u,v>
			else
				path[u][v] = -1;											// �����ڱ�<u,v>
		}

	for (int k = 0; k < g.GetVexNum(); k++)
		for (int i = 0; i < g.GetVexNum(); i++)
			for (int j = 0; j < g.GetVexNum(); j++)
				if (dist[i][k] != DEFAULT_INFINITY && dist[k][j] != DEFAULT_INFINITY
					&& dist[i][k] + dist[k][j] < dist[i][j]) {
					// ��i��k�ٵ�j��·�����ȸ���
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
}*/