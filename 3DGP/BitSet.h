#pragma once

#include <vector>

class BitSet
{
private:
	static constexpr int c_bitSize = sizeof(unsigned int) * 8 - 1;
	static int s_byteSize;

	std::vector<unsigned int> m_bits;
public:
	BitSet();

	void SetBit(unsigned int _index);
	void ClearBit(unsigned int _index);

	bool IsBitSet(unsigned int _index);

	void SetAll();
	void ClearAll();

	void Display();
};
