#include"DFSBFS.h"

using namespace std;


void swap(int& A, int& B)
{
	int c = A;
	A = B;
	B = c;
}

struct Node
{
	int v;
	bool bVisit = false;

	Node* mConnections[10001];
	int mConnectSize = 0;

	bool operator==(Node& rhs) { return this->v == rhs.v; }

	bool Contains(Node* node)
	{
		for (int i = 0; i < mConnectSize; i++)
		{
			if (mConnections[i] == node)
				return true;
		}

		return false;
	}

	inline bool operator>(Node* rhs) { return this->v > rhs->v ? true : false; }
	inline bool operator<(Node* rhs) { return this->v < rhs->v ? true : false; }
};
void searchDFS(Node* node, ostream& out, stack<Node*>& history);

void swapNode(Node*& a, Node*& b)
{
	Node* c = a;
	a = b;
	b = c;
}

void traceNode(Node* node, ostream& out)
{
}

void searchBFS(queue<Node*> nodeQueue, ostream& out)
{


	while (nodeQueue.empty() == false)
	{
		Node* node = nodeQueue.front();
		nodeQueue.pop();
		out << node->v << " ";
		node->bVisit = true;
		for (int i = 0; i < node->mConnectSize; i++)
		{
			Node* connection = node->mConnections[i];
			if (connection->bVisit == false)
			{
				nodeQueue.push(connection);
				connection->bVisit = true;
			}

		}


	}



}

void backTrack(stack<Node*>& history, ostream& out)
{
	if(history.size() > 1)
		history.pop();
	Node* peek = history.top();

	for (int i = 0; i < peek->mConnectSize; i++)
	{
		if (peek->mConnections[i]->bVisit == false)
			searchDFS(peek, out, history);
	}
}

void searchDFS(Node* node, ostream& out, stack<Node*>& history)
{
	if (node == nullptr) return;

	if (node->bVisit == false)
	{
		out << node->v << " ";
		node->bVisit = true;
		history.push(node);
	}

	for (int i = 0; i < node->mConnectSize; i++)
	{
		Node* connection = node->mConnections[i];

		if (connection->bVisit == false)
			searchDFS(connection, out, history);
	}

	// 인접 노드를 모두 방문한 경우
	backTrack(history,out);
	
}

void connectionSort(Node** connections, int size)
{
	for (int i = 1; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			if (connections[j] > connections[i])
				swapNode(connections[i], connections[j]);
		}

	}
}

void generateConnections(int N, int M, Node* vertices, int arguments[][2])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int argumentIndex = arguments[j][0] - 1;
			int connect = arguments[j][1] - 1;
			Node* vertex = &vertices[argumentIndex];

			if (vertex->Contains(&vertices[connect]) == true)
				break;

			int connectIndex = vertex->mConnectSize;
			int otherConnectIndex = vertices[connect].mConnectSize;
			vertex->mConnections[connectIndex] = &vertices[connect];
			vertices[connect].mConnections[otherConnectIndex] = vertex;

			vertex->mConnectSize++;
			vertices[connect].mConnectSize++;
		}
	}

	if (M > 0)
	{
		for (int i = 0; i < N; i++)
			connectionSort(vertices[i].mConnections, vertices[i].mConnectSize);

	}
	
}

void NewDFS(int N, int M, int V, int arguments[][2], ostream& out)
{
	Node* vertices = new Node[N];
	stack<Node*> history;

	for (int i = 0; i < N; i++)
		vertices[i].v = i + 1;

	generateConnections(N, M, vertices, arguments);

	searchDFS(&vertices[V - 1], out, history);

	delete[] vertices;
}

void BFS(int N, int M, int V, int arguments[][2], ostream& out)
{
	Node* vertices = new Node[N];
	Node* root = &vertices[V - 1];
	queue<Node*> nodeQueue;

	for (int i = 0; i < N; i++)
		vertices[i].v = i + 1;

	generateConnections(N, M, vertices, arguments);

	nodeQueue.push(root);

	searchBFS(nodeQueue, out);
	delete[] vertices;
}