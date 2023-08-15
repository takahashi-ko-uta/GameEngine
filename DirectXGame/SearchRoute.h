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
	// 削除結果
	enum EraseResult
	{
		NotFound,		// 未発見
		Erased,			// 削除
		CouldntErased	// 削除できない
	};

	// Mapのマス目
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

		int X;		// 列
		int Y;		// 行
	};


	// ノード
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

		Cell Position;						// ノード座標
		std::vector<Node*> AdjacentNodes;	// 隣接ノード(辺)
		float HeuristicCost;				// ヒューリスティックコスト
		float TotalCost;					// コスト(ヒューリスティックコスト込み)
	};
	
	// 昇順ソート用関数
	bool Less(Node* a, Node* b);
	// セル範囲チェック関数
	bool IsCellWithinTheRange(int x, int y);
	// ノードの作成
	void CreateMap();
	// コスト初期化
	void InitCost(int heuristic_cost, int total_cost);
	// ヒューリスティックコスト計算(ノードとゴールまでの距離を返している)
	float CalculateHeuristic(const Node* node, const Node* Goal);
	// セル比較
	bool IsEqualCell(const Cell& a, const Cell& b);

	EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);
	// オープンリストに追加
	bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);
	void AStar(Cell start, Cell goal);

	//getter
	void GetRoute(XMINT2 route[40]);
private:
	const static int MapWidth = 11;
	const static int MapHeight = 11;
	const static int Infinity = 100000;

	// コストテーブル
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

	// グラフ
	Node Map[MapHeight][MapWidth];

	XMINT2 routeSave[40];

};

