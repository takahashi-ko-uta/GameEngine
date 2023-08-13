#include "SearchRoute.h"
#include "imgui.h"
using namespace DirectX;

// 昇順ソート用関数
bool SearchRoute::Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost)
	{
		return true;
	}

	return false;
}

// セル範囲チェック関数
bool SearchRoute::IsCellWithinTheRange(int x, int y)
{
	if (x >= 0 &&
		x < MapWidth &&
		y >= 0 &&
		y < MapHeight)
	{
		return true;
	}

	return false;
}

// ノードの作成
void SearchRoute::CreateMap()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Map[y][x].Position.x = x;
			Map[y][x].Position.y = y;

			XMINT2 adjacent_cells[] =
			{
				XMINT2(x, y - 1),
				XMINT2(x - 1, y),
				XMINT2(x + 1, y),
				XMINT2(x, y + 1),
			};

			// 隣接ノードの追加
			for (const XMINT2& cell : adjacent_cells)
			{
				if (IsCellWithinTheRange(cell.x, cell.y) == true &&
					CostTable[cell.y][cell.x] == 1)
				{
					Map[y][x].AdjacentNodes.push_back(&Map[cell.y][cell.x]);
				}
			}
		}
	}
}

// コスト初期化
void SearchRoute::InitCost(int heuristic_cost, int total_cost)
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Map[y][x].HeuristicCost = heuristic_cost;
			Map[y][x].TotalCost = total_cost;
		}
	}
}

// ヒューリスティックコスト計算(ノードとゴールまでの距離を返している)
float SearchRoute::CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(Goal->Position.x - node->Position.x);
	float y = fabsf(Goal->Position.y - node->Position.y);

	return sqrtf(x * x + y * y);
}

// セル比較
bool SearchRoute::IsEqualCell(const XMINT2& a, const XMINT2& b)
{
	if (a.x == b.x &&
		a.y == b.y)
	{
		return true;
	}

	return false;
}

SearchRoute::EraseResult  SearchRoute::EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
	// クローズリストチェック
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// ノードと同じセルがあるか調べる
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// コストの比較
			if (new_cost < (*itr)->TotalCost)
			{
				list.erase(itr);
				return EraseResult::Erased;
			}
			else
			{
				return EraseResult::CouldntErased;
			}
		}
	}

	return EraseResult::NotFound;
}

// オープンリストに追加
bool SearchRoute::AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost)
{
	bool can_update = true;

	std::list<Node*> node_list[] =
	{
		close_list,
		open_list
	};

	for (std::list<Node*>& list : node_list)
	{
		// リストに同じノードがあってリストの方のコストが高いなら削除
		if (EraseNode(list, adjacent_node, cost) == EraseResult::CouldntErased)
		{
			can_update = false;
		}
	}

	if (can_update == true)
	{
		open_list.push_back(adjacent_node);
		return true;
	}

	return false;
}

void SearchRoute::AStar(XMINT2 start, XMINT2 goal)
{
	std::list<Node*> open_list;
	std::list<Node*> close_list;

	//const Node* start_node = &Map[start.Y][start.X];
	const Node* goal_node = &Map[goal.y][goal.x];

	// 更新したノード位置保存用
	XMINT2 last_update_cells[MapHeight][MapWidth];

	// グラフの初期化
	InitCost(Infinity, 0);

	// スタートノードの指定
	open_list.push_back(&Map[start.y][start.x]);

	// 経路探索回数
	int count = 0;

	// オープンリストがなくなるまで回す
	while (open_list.empty() == false)
	{
		count++;

		Node* search_node = (*open_list.begin());
		// 探索リストから除外
		open_list.erase(open_list.begin());

		// ゴールに到達したら終わり
		if (IsEqualCell(search_node->Position, goal) == true)
		{
			// クローズリストに最後のノードを追加する
			close_list.push_back(search_node);
			break;
		}

		for (Node* adjacent_node : search_node->AdjacentNodes)
		{
			// 計算を行っていなかった場合だけ計算
			if (adjacent_node->HeuristicCost == Infinity)
			{
				// ヒューリスティクスコスト計算
				adjacent_node->HeuristicCost = CalculateHeuristic(adjacent_node, goal_node);
			}

			// ノード間コスト
			float edge_cost = CostTable[adjacent_node->Position.y][adjacent_node->Position.x];
			// 取得ノードのトータルコスト
			float node_cost = search_node->TotalCost;
			/*
				トータルコスト算出
					ノード間コスト + ヒューリスティックコスト + 取得ノードのトータルコスト
			*/
			float total_cost = edge_cost + adjacent_node->HeuristicCost + node_cost;

			// ノード追加
			if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
			{
				// トータルコストを更新
				adjacent_node->TotalCost = total_cost;

				if (adjacent_node->Position.y == 0 && adjacent_node->Position.x == 2)
				{
					int xx = 0;
					xx = 100;
				}

				// 経路を更新したセルを保存
				last_update_cells[adjacent_node->Position.y][adjacent_node->Position.x] = search_node->Position;
			}
		}

		bool is_add_close = true;

		// クローズリストチェック
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			// ノードと同じセルがあるか調べる
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		// 同じノードが無かったので追加
		if (is_add_close == true)
		{
			// このノードの探索終了
			close_list.push_back(search_node);
		}

		// 昇順ソート
		//open_list.sort(Less);
	}

	// 経路復元
	std::list<XMINT2> route_list;

	// ゴールセルから復元する
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		XMINT2 route = route_list.front();

		// スタートセルなら終了
		if (IsEqualCell(route, start) == true)
		{
			// 復元した経路を表示
			for (XMINT2& cell : route_list)
			{
				ImGui::Text("x = %d y = %d\n", cell.x, cell.y);
			}
			break;
		}
		else
		{
			if (IsCellWithinTheRange(route.x, route.y) == true)
			{
				// 追加
				route_list.push_front(last_update_cells[route.y][route.x]);
			}
			else
			{
				ImGui::Text("経路は見つからなかった\n");
				break;
			}
		}
	}

	ImGui::Text("探索回数 = %d\n", count);
}
