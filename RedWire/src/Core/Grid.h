#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include "Type2.h"

namespace RedWire
{
	struct Grid;
	struct Cell;
	struct Wire;
	struct Gate;
	struct Join;

	struct Grid
	{
		struct Tile
		{
			Tile();

			static const int size = 32;

			std::shared_ptr<Cell> cells[size][size];
		};

		Grid();

		Cell* const get(const Int2& position) const;
		uint32_t getColor(const Int2& position) const;

		size_t getWireCount() const;
		size_t getGateCount() const;

		void addWire(const Int2& position);
		void addGate(const Int2& position);
		void addJoin(const Int2& position);

		void remove(const Int2& position);

		void update();

	private:

		std::shared_ptr<Cell> getPtr(const Int2& position) const;
		void set(const Int2& position, const std::shared_ptr<Cell> cell);

		struct SearchPack
		{
			SearchPack(Wire* const wire, std::unordered_set<Int2>& replaced, const std::shared_ptr<Cell>& bundle) : wire(wire), replaced(replaced), bundle(bundle)
			{

			}

			Wire* const wire;

			std::unordered_set<Int2>& replaced;
			const std::shared_ptr<Cell>& bundle;
		};

		std::unordered_set<Int2> floodReplace(const Int2& position, const std::shared_ptr<Cell>& bundle);
		void floodSearch(const SearchPack& pack, const Int2& source, const Int2& direction);

		bool splitNeighbors(const Int2& position);
		void scanPort(const Int2& position);

		void refreshGate(const Int2& position, const int neighborCount, Gate& gate);
		void refreshJoin(const Int2& position, const int neighborCount, Join& join);

		void removeWire(const Int2& position);
		void removeGate(const Int2& position);
		void removeJoin(const Int2& position);

		std::unordered_map<Int2, Tile> tiles;
		std::vector<std::shared_ptr<Wire>> wires;
		std::vector<std::shared_ptr<Gate>> gates;
	};
}