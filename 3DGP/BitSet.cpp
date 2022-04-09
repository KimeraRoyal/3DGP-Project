#include "BitSet.h"

#include <cmath>

int BitSet::s_byteSize = static_cast<int>(std::log2(c_bitSize + 1));

BitSet::BitSet() : m_bits(1)
{ }

void BitSet::SetBit(const unsigned int _index)
{
	// Retrieve the index within the bit vector of the bit to manipulate.
	const unsigned int setIndex = _index >> s_byteSize;
	if(setIndex >= m_bits.size()) { m_bits.resize(setIndex + 1); }
	m_bits.at(setIndex) |= 0x1 << (_index & c_bitSize);
}

void BitSet::ClearBit(const unsigned int _index)
{
	// Retrieve the index within the bit vector of the bit to manipulate.
	const unsigned int setIndex = _index >> s_byteSize;
	if (setIndex >= m_bits.size()) { return; }
	m_bits.at(setIndex) &= ~(0x1 << (_index & c_bitSize));
}

bool BitSet::IsBitSet(const unsigned _index)
{
	// Retrieve the index within the bit vector of the bit to manipulate.
	const unsigned int setIndex = _index >> s_byteSize;
	if (setIndex >= m_bits.size()) { return false; }
	return m_bits.at(setIndex) & (1 << (_index & c_bitSize));
}

void BitSet::SetAll()
{
	std::fill(m_bits.begin(), m_bits.end(), 0x0 - 0x1);
}

void BitSet::ClearAll()
{
	std::fill(m_bits.begin(), m_bits.end(), 0x0);
}

void BitSet::CopyBits(BitSet& _other)
{
	if (_other.m_bits.size() > m_bits.size()) { m_bits.resize(_other.m_bits.size()); }
	ClearAll();
	
	for(unsigned int i = 0; i < _other.m_bits.size(); i++)
	{
		m_bits.at(i) = _other.m_bits.at(i);
	}
}

void BitSet::Display()
{
	unsigned int totalCount = 0;
	
	unsigned int currentBit = 0;
	unsigned int totalSet = 0;
	for(unsigned int bit : m_bits)
	{
		totalSet = 0;
		for(unsigned int i = 0; i <= c_bitSize; i++)
		{
			currentBit = (bit >> i) & 0x1;
			if (currentBit) { totalSet++; }
			std::printf("%u", currentBit);
		}

		totalCount += totalSet;
		std::printf(" - Bits Set: %u, Total Value: %u\n", totalSet, bit);
	}

	std::printf("Total Bits Set: %u\n\n", totalCount);
}
