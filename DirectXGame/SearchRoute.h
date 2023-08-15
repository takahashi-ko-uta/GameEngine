#pragma once
#include <stdio.h>
#include <memory.h>
#include <list>
#include <queue>
#include <vector>
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

class SearchRoute
{
public:
	// �폜����
	enum EraseResult
	{
		NotFound,		// ������
		Erased,			// �폜
		CouldntErased	// �폜�ł��Ȃ�
	};

	// Map�̃}�X��
	struct Cell
	{
		Cell() :
			X(-1),
			Y(-1)
		{
		}

		Cell(int x, int y)
		{
			X = x;
			Y = y;
		}

		int X;		// ��
		int Y;		// �s
	};


	// �m�[�h
	struct Node
	{
		Node() :
			Node(0, 0)
		{
		}

		Node(int x, int y) :
			Position(x, y),
			HeuristicCost(Infinity),
			TotalCost(0)
		{
			AdjacentNodes.clear();
		}

		Cell Position;						// �m�[�h���W
		std::vector<Node*> AdjacentNodes;	// �אڃm�[�h(��)
		float HeuristicCost;				// �q���[���X�e�B�b�N�R�X�g
		float TotalCost;					// �R�X�g(�q���[���X�e�B�b�N�R�X�g����)
	};
	
	// �����\�[�g�p�֐�
	bool Less(Node* a, Node* b);
	// �Z���͈̓`�F�b�N�֐�
	bool IsCellWithinTheRange(int x, int y);
	// �m�[�h�̍쐬
	void CreateMap();
	// �R�X�g������
	void InitCost(int heuristic_cost, int total_cost);
	// �q���[���X�e�B�b�N�R�X�g�v�Z(�m�[�h�ƃS�[���܂ł̋�����Ԃ��Ă���)
	float CalculateHeuristic(const Node* node, const Node* Goal);
	// �Z����r
	bool IsEqualCell(const Cell& a, const Cell& b);

	EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);
	// �I�[�v�����X�g�ɒǉ�
	bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);
	void AStar(Cell start, Cell goal);

	//getter
	void GetRoute(XMINT2 route[40]);
private:
	const static int MapWidth = 11;
	const static int MapHeight = 11;
	const static int Infinity = 100000;

	// �R�X�g�e�[�u��
	int CostTable[MapHeight][MapWidth] =
	{
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1
	};

	// �O���t
	Node Map[MapHeight][MapWidth];

	XMINT2 routeSave[40];

};

