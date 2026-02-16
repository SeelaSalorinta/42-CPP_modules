#include "PmergeMe.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>

// ===== Vector =====

/* A Block = one "element" of the algorithm*/
struct BlockV
{
	const unsigned int* vals;
	std::size_t	len;
	// key = value used for comparisons (last element of block)
	unsigned int key() const { return vals[len - 1]; }
};

/* Flatten blocks back into a normal array */
static std::vector<unsigned int> flattenBlocks(const std::vector<BlockV>& blocks)
{
	std::vector<unsigned int> out;
	std::size_t total = 0;

	for (std::size_t i = 0; i < blocks.size(); ++i)
		total += blocks[i].len;
	out.reserve(total);

	for (std::size_t i = 0; i < blocks.size(); ++i)
		out.insert(out.end(), blocks[i].vals, blocks[i].vals + blocks[i].len);
	return out;
}

/* Split array into blocks of size blockSize
	leftover elements go into tail */
static std::vector<BlockV> makeBlocks(const std::vector<unsigned int>& vec,
	std::size_t blockSize, std::vector<unsigned int>& tail)
{
	std::vector<BlockV> blocks;
	tail.clear();

	const std::size_t totalElements = vec.size();
	const std::size_t numFullBlocks = totalElements / blockSize;
	const std::size_t elementsInFullBlocks = numFullBlocks * blockSize;

	blocks.reserve(numFullBlocks);
	for (std::size_t i = 0; i < elementsInFullBlocks; i += blockSize)
	{
		BlockV b;
		b.vals = &vec[i];
		b.len = blockSize;
		blocks.push_back(b);
	}

	if (elementsInFullBlocks < totalElements)
		tail.assign(vec.begin() + elementsInFullBlocks, vec.end());

	return blocks;
}

/* Pair-sort by key, swap WHOLE blocks*/
static void pairSortBlocks(std::vector<BlockV>& blocks)
{
	for (std::size_t i = 0; i + 1 < blocks.size(); i += 2)
	{
		if (blocks[i + 1].key() < blocks[i].key())
			std::swap(blocks[i], blocks[i + 1]);
	}
}

/* Build Jacobsthal insertion order for pend elements */
static std::vector<std::size_t> buildJacobsthalOrder(std::size_t pendSize)
{
	std::vector<std::size_t> order;
	if (pendSize == 0)
		return order;

	const std::size_t totalB = pendSize + 1; // include b1

	//1) Create Jacobstahl numbers
	std::vector<std::size_t> J;
	J.push_back(0);
	J.push_back(1);
	while (J.back() < totalB)
	{
		std::size_t n = J.size();
		J.push_back(J[n - 1] + 2 * J[n - 2]);
	}

	//2) Generate pend insertion order by walking Jacobsthal ranges backwards
	std::vector<bool> used(totalB + 1, false);

	for (std::size_t i = 3; i < J.size(); ++i)
	{
		std::size_t previous = J[i - 1];
		std::size_t current = J[i];
		if (current > totalB)
			current = totalB;

		for (std::size_t cur = current; cur > previous; --cur)
		{
			if (cur >= 2 && cur <= totalB && !used[cur])
			{
				used[cur] = true;
				order.push_back(cur - 2); // b2 is in-> 0 idx etc.
			}
		}
	}

	for (std::size_t i = totalB; i >= 2; --i)
	{
		if (!used[i])
		{
			used[i] = true;
			order.push_back(i - 2);
		}
	}
	return order;
}

/* Binary search insertion position by block.key()
	only search in main[0..limit)*/
static std::size_t upperBoundKey(const std::vector<BlockV>& main,
	std::size_t limit, const BlockV& b)
{
	std::size_t low = 0, high = limit;
	while (low < high)
	{
		std::size_t mid = low + (high - low) / 2;
		if (b.key() < main[mid].key())
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}

/* Build main chain from b1 and a's
	+ insert pend losers b2..bk in Jacobsthal order using binary insertion*/
static std::vector<BlockV> buildMainByInsertion(const std::vector<BlockV>& blocks)
{
	//1) Create as a's and b's
	const std::size_t blockSize = blocks.size();
	if (blockSize < 2)
		return blocks;

	std::vector<BlockV> bs;
	std::vector<BlockV> as;
	bs.reserve((blockSize + 1) / 2);
	as.reserve(blockSize / 2);

	for (std::size_t i = 0; i + 1 < blockSize; i += 2)
	{
		bs.push_back(blocks[i]);
		as.push_back(blocks[i + 1]);
	}

	const bool hasOdd = (blockSize % 2 == 1);
	BlockV odd;
	if (hasOdd)
		odd = blocks.back();

	//2) Create main from b1 and a's
	std::vector<BlockV> main;
	main.reserve(1 + as.size());
	main.push_back(bs[0]);
	main.push_back(as[0]);
	for (std::size_t i = 1; i < as.size(); ++i)
		main.push_back(as[i]);

	//3) Create pend from rest of b's + odd
	std::vector<BlockV> pend;
	std::size_t losers = (bs.size() > 1) ? (bs.size() - 1) : 0;
	std::size_t oddExtra = hasOdd ? 1 : 0;
	pend.reserve(losers + oddExtra);
	
	for (std::size_t i = 1; i < bs.size(); ++i)
		pend.push_back(bs[i]);
	if (hasOdd)
		pend.push_back(odd);

	//4) Form winnerlimits for every loser , not for odd
	std::vector<std::size_t> limit(pend.size(), main.size());
	const std::size_t realBCount = bs.size();
	std::size_t losersWithWinners = 0;
	if (realBCount >= 2)
		losersWithWinners = realBCount - 1;

	for (std::size_t i = 0; i < pend.size() && i < losersWithWinners; ++i)
	{
		std::size_t winnerIndex = 2 + i; // b2' winner a2 is at index 2 etc.
		if (winnerIndex > main.size())
			winnerIndex = main.size();
		limit[i] = winnerIndex;
	}

	const std::vector<std::size_t> order = buildJacobsthalOrder(pend.size());

	//5) Insert the pend to main in jacobstahl order using binary search
	for (std::size_t t = 0; t < order.size(); ++t)
	{
		const std::size_t pendIdx = order[t];
		if (pendIdx >= pend.size())
			continue;

		std::size_t winnerLimit = limit[pendIdx];
		if (winnerLimit > main.size())
			winnerLimit = main.size();

		const std::size_t insertPos = upperBoundKey(main, winnerLimit, pend[pendIdx]);

		main.insert(main.begin() + static_cast<std::ptrdiff_t>(insertPos), pend[pendIdx]);

		for (std::size_t i = 0; i < limit.size(); ++i)
			if (limit[i] >= insertPos)
				++limit[i];
	}

	return main;
}

static std::vector<unsigned int> sortRecursive(const std::vector<unsigned int>& vec,
	std::size_t blockSize)
{
	std::vector<unsigned int> tail;
	std::vector<BlockV> blocks = makeBlocks(vec, blockSize, tail);

	if (blocks.size() < 2)
		return vec;

	pairSortBlocks(blocks);

	std::vector<unsigned int> flattened = flattenBlocks(blocks);
	std::vector<unsigned int> rec = sortRecursive(flattened, blockSize * 2);

	std::vector<unsigned int> tail2;
	std::vector<BlockV> blocks2 = makeBlocks(rec, blockSize, tail2);

	std::vector<BlockV> mainBlocks = buildMainByInsertion(blocks2);

	std::vector<unsigned int> out = flattenBlocks(mainBlocks);

	out.insert(out.end(), tail.begin(), tail.end());

	return out;
}

void PmergeMe::fordJohnsonSort(std::vector<unsigned int>& v)
{
	if (v.size() <= 1)
		return;
	v = sortRecursive(v, 1);
}

// ===== Deque =====


/* A BlockD = one "element" of the algorithm*/
struct BlockD
{
	const unsigned int* vals;
	std::size_t	len;
	// key = value used for comparisons (last element of block)
	unsigned int key() const { return vals[len - 1]; }
};

/* Flatten blocks back into a normal array*/
static std::deque<unsigned int> flattenBlocksD(const std::deque<BlockD>& blocks)
{
	std::deque<unsigned int> out;
	for (std::deque<BlockD>::const_iterator it = blocks.begin(); it != blocks.end(); ++it)
		out.insert(out.end(), it->vals, it->vals + it->len);
	return out;
}

/* Split array into blocks of size blockSize
	leftover elements go into tail */
static std::deque<BlockD> makeBlocksD(const std::deque<unsigned int>& deq,
	std::size_t blockSize, std::deque<unsigned int>& tail,
	std::vector<unsigned int>& buf)
{
	std::deque<BlockD> blocks;
	tail.clear();

	buf.assign(deq.begin(), deq.end());

	const std::size_t totalElements = buf.size();
	const std::size_t numFullBlocks = totalElements / blockSize;
	const std::size_t elementsInFullBlocks = numFullBlocks * blockSize;

	for (std::size_t i = 0; i < elementsInFullBlocks; i += blockSize)
	{
		BlockD b;
		b.vals = &buf[i];
		b.len  = blockSize;
		blocks.push_back(b);
	}

	if (elementsInFullBlocks < totalElements)
	{
		for (std::size_t i = elementsInFullBlocks; i < totalElements; ++i)
			tail.push_back(buf[i]);
	}

	return blocks;
}

/* Pair-sort by key, swap WHOLE blocks*/
static void pairSortBlocksD(std::deque<BlockD>& blocks)
{
	for (std::size_t i = 0; i + 1 < blocks.size(); i += 2)
	{
		if (blocks[i + 1].key() < blocks[i].key())
			std::swap(blocks[i], blocks[i + 1]);
	}
}

/* Build Jacobsthal insertion order for pend elements */
static std::deque<std::size_t> buildJacobsthalOrderD(std::size_t pendSize)
{
	std::deque<std::size_t> order;
	if (pendSize == 0)
		return order;

	const std::size_t totalB = pendSize + 1; // include b1

	//1) Create Jacobstahl numbers
	std::deque<std::size_t> J;
	J.push_back(0);
	J.push_back(1);
	while (J.back() < totalB)
	{
		std::size_t n = J.size();
		J.push_back(J[n - 1] + 2 * J[n - 2]);
	}

	//2) Generate pend insertion order by walking Jacobsthal ranges backwards
	std::deque<bool> used(totalB + 1, false);

	for (std::size_t i = 3; i < J.size(); ++i)
	{
		std::size_t previous = J[i - 1];
		std::size_t current = J[i];
		if (current > totalB)
			current = totalB;

		for (std::size_t cur = current; cur > previous; --cur)
		{
			if (cur >= 2 && cur <= totalB && !used[cur])
			{
				used[cur] = true;
				order.push_back(cur - 2); // b2 is in-> 0 idx etc.
			} 
		}
	}

	for (std::size_t i = totalB; i >= 2; --i)
	{
		if (!used[i])
		{
			used[i] = true;
			order.push_back(i - 2);
		}
	}
	return order;
}

/* Binary search insertion position by block.key()
	only search in main[0..limit)*/
static std::size_t upperBoundKeyD(const std::deque<BlockD>& main,
	std::size_t limit, const BlockD& b)
{
	std::size_t low = 0, high = limit;
	while (low < high)
	{
		std::size_t mid = low + (high - low) / 2;
		if (b.key() < main[mid].key())
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}

/* Build main chain from b1 and a's
	+ insert pend losers b2..bk in Jacobsthal order using binary insertion*/
static std::deque<BlockD> buildMainByInsertionD(const std::deque<BlockD>& blocks)
{
	//1) Create as a's and b's
	const std::size_t blockSize = blocks.size();
	if (blockSize < 2)
		return blocks;

	std::deque<BlockD> bs;
	std::deque<BlockD> as;

	for (std::size_t i = 0; i + 1 < blockSize; i += 2)
	{
		bs.push_back(blocks[i]);
		as.push_back(blocks[i + 1]);
	}

	const bool hasOdd = (blockSize % 2 == 1);
	BlockD odd;
	if (hasOdd)
		odd = blocks.back();

	//2) Create main from b1 and a's
	std::deque<BlockD> main;
	main.push_back(bs[0]);
	main.push_back(as[0]);
	for (std::size_t i = 1; i < as.size(); ++i)
		main.push_back(as[i]);

	//3) Create pend from rest of b's + odd
	std::deque<BlockD> pend;
	for (std::size_t i = 1; i < bs.size(); ++i)
		pend.push_back(bs[i]);
	if (hasOdd)
		pend.push_back(odd);

	//4) Form winnerlimits for every loser , not for odd
	std::vector<std::size_t> limit(pend.size(), main.size());
	const std::size_t realBCount = bs.size();
	std::size_t losersWithWinners = 0;
	if (realBCount >= 2)
		losersWithWinners = realBCount - 1;

	for (std::size_t i = 0; i < pend.size() && i < losersWithWinners; ++i)
	{
		std::size_t winnerIndex = 2 + i; // b2' winner a2 is at index 2 etc.
		if (winnerIndex > main.size())
			winnerIndex = main.size();
		limit[i] = winnerIndex;
	}

	const std::deque<std::size_t> order = buildJacobsthalOrderD(pend.size());

	//5) Insert the pend to main in jacobstahl order using binary search
	for (std::size_t t = 0; t < order.size(); ++t)
	{
		const std::size_t pendIdx = order[t];
		if (pendIdx >= pend.size())
			continue;

		std::size_t winnerLimit = limit[pendIdx];
		if (winnerLimit > main.size())
			winnerLimit = main.size();

		const std::size_t insertPos = upperBoundKeyD(main, winnerLimit, pend[pendIdx]);

		main.insert(main.begin() + static_cast<std::ptrdiff_t>(insertPos), pend[pendIdx]);

		for (std::size_t i = 0; i < limit.size(); ++i)
			if (limit[i] >= insertPos)
				++limit[i];
	}

	return main;
}

static std::deque<unsigned int> sortRecursiveD(const std::deque<unsigned int>& deq,
	std::size_t blockSize)
{
	std::deque<unsigned int> tail;
	std::vector<unsigned int> buf;
	std::deque<BlockD> blocks = makeBlocksD(deq, blockSize, tail, buf);

	if (blocks.size() < 2)
		return deq;

	pairSortBlocksD(blocks);

	std::deque<unsigned int> flattened = flattenBlocksD(blocks);
	std::deque<unsigned int> rec = sortRecursiveD(flattened, blockSize * 2);

	std::deque<unsigned int> tail2;
	std::vector<unsigned int> buf2;
	std::deque<BlockD> blocks2 = makeBlocksD(rec, blockSize, tail2, buf2);

	std::deque<BlockD> mainBlocks = buildMainByInsertionD(blocks2);
	std::deque<unsigned int> out = flattenBlocksD(mainBlocks);

	out.insert(out.end(), tail.begin(), tail.end());
	return out;
}

void PmergeMe::fordJohnsonSort(std::deque<unsigned int>& d)
{
	if (d.size() <= 1)
		return;
	d = sortRecursiveD(d, 1);
}


void PmergeMe::run(int argc, char** argv)
{
	{
		const std::chrono::high_resolution_clock::time_point start =
			std::chrono::high_resolution_clock::now();

		fillFromArgs(_ogVec, argc, argv);
		_vec = _ogVec;
		fordJohnsonSort(_vec);

		const std::chrono::high_resolution_clock::time_point end =
			std::chrono::high_resolution_clock::now();
		_timeUsVec = std::chrono::duration<double, std::micro>(end - start).count();
	}

	{
		const std::chrono::high_resolution_clock::time_point start =
			std::chrono::high_resolution_clock::now();

		fillFromArgs(_deq, argc, argv);
		fordJohnsonSort(_deq);

		const std::chrono::high_resolution_clock::time_point end =
			std::chrono::high_resolution_clock::now();
		_timeUsDeq = std::chrono::duration<double, std::micro>(end - start).count();
	}

	printContainer("Before: ", _ogVec);
	printContainer("After:  ", _vec);

	std::cout << "Time to process a range of " << _vec.size()
		<< " elements with std::vector : " << _timeUsVec << " us\n";
	std::cout << "Time to process a range of " << _deq.size()
		<< " elements with std::deque  : " << _timeUsDeq << " us\n";
}
