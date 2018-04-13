// Copyright 2013-2017, GlobalLogic.
// All rights reserved.
//

#include "gtest/gtest.h"

#include "entry.h"
#include "sort.h"

#include <limits>
#include <vector>
#include <ctime>


const char* buf_hello = "Hello Global World!";

const char* buf_company = "As a full-lifecycle product development services company, \
						  we offer the opportunity to work on amazing projects, using \
						  the latest disruptive technologies, with other designer and \
						  engineers who are experts in their field. We offer competitive \
						  salaries, the stability of a global company, and customized \
						  professional development that gives you exposure to a variety \
						  of interesting, hands-on projects.";

TEST(Entry, sizeof)
{
	typedef struct { char* b; int s; } entry_t;
	EXPECT_EQ(sizeof(entry_t), sizeof(Entry));
}

TEST(Entry, set)
{
	Entry entry;
	entry.set(buf_hello, strlen(buf_hello) + 1);

	EXPECT_STREQ(buf_hello, entry.buf());
}

TEST(Entry, buf)
{
	Entry entry;
	entry.set(buf_company, strlen(buf_company) + 1);

	EXPECT_NE(buf_company, entry.buf());
	EXPECT_STREQ(buf_company, entry.buf());
}

TEST(Entry, init_buf)
{
	Entry entry;

	EXPECT_THROW(entry.set(0, 1), std::logic_error);
}

TEST(Entry, init_len)
{
	Entry entry;

	EXPECT_THROW(entry.set(buf_hello, 0), std::logic_error);
	EXPECT_THROW(entry.set(buf_hello, std::numeric_limits<unsigned int>::max()), std::logic_error);
}

TEST(Entry, init_values)
{
	Entry* pEntry = new Entry;

	EXPECT_EQ(0, pEntry->buf());
	EXPECT_EQ(0, pEntry->size());

	delete pEntry;
}

TEST(Entry, two_entrys)
{
	Entry entry;
	entry.set(buf_company, strlen(buf_company) + 1);

	Entry entry2 = entry;

	EXPECT_NE(entry.buf(), entry2.buf());
	EXPECT_EQ(entry.size(), entry2.size());
	EXPECT_STREQ(entry.buf(), entry2.buf());
}

TEST(Entry, two_entrys2)
{
	Entry* pEntry = new Entry;
	pEntry->set(buf_hello, strlen(buf_hello) + 1);

	Entry entry;
	entry = *pEntry;

	EXPECT_NE(entry.buf(), pEntry->buf());
	EXPECT_EQ(entry.size(), pEntry->size());
	EXPECT_STREQ(entry.buf(), pEntry->buf());

	delete pEntry;
}

TEST(Entry, destruction)
{
	Entry* pEntry = new Entry;

	// TODO: Need to improve leak checking.
	//pEntry->set(buf_company, strlen(buf_company) + 1);
	//EXPECT_TRUE(0 != pEntry->buf());
	//pEntry->~Entry();
	//EXPECT_TRUE(0 == pEntry->buf());

	delete pEntry;
}

TEST(Entry, encode)
{
	const int size = strlen(buf_hello) + 1;

	Entry entry;
	entry.set(buf_hello, size);

	EXPECT_STREQ(buf_hello, entry.buf());

	entry.encode();

	EXPECT_STRNE(buf_hello, entry.buf());

	char buf[size];
	memcpy(buf, buf_hello, size);

	::encode(buf, size);

	EXPECT_STREQ(buf, entry.buf());
}

TEST(Entry, decode)
{
	Entry entry;
	entry.set(buf_company, strlen(buf_company) + 1);

	EXPECT_STREQ(buf_company, entry.buf());

	entry.encode();

	EXPECT_STRNE(buf_company, entry.buf());

	entry.decode();

	EXPECT_STREQ(buf_company, entry.buf());
}

void test(const char* buf, int size)
{
	Entry entry;
	entry.set(buf, size);

	for(int i=0; i<size; i++)
	{
		ASSERT_EQ(buf[i], *(entry.buf()+i)) << "i is: " << i;
	}

	entry.encode();

	std::vector<char> vect(size);
	memcpy(&vect[0], buf, size);

	::encode(&vect[0], size);

	for(int i=0; i<size; i++)
	{
		ASSERT_EQ(vect[i], *(entry.buf()+i)) << "i is: " << i;
	}

	entry.decode();

	for(int i=0; i<size; i++)
	{
		ASSERT_EQ(*(buf+i), entry.buf()[i]) << "i is: " << i;
	}
}

TEST(Entry, test_1)
{
	char buf[] = {1};
	test(buf, sizeof(buf));
}

TEST(Entry, test_2)
{
	char buf[] = {1, 2};
	test(buf, sizeof(buf));
}

TEST(Entry, test_3)
{
	char buf[] = {1, 2, 3};
	test(buf, sizeof(buf));
}

TEST(Entry, test_rand)
{
	srand( time(0) );
	int size = 10000;
	char* buf = new char[size];

	for( int i=0; i<size; i++)
	{
		buf[i] = rand();
	}

	test(buf, size);

	delete[] buf;
}


std::vector<Package> packages {
	{"Box0", {2, 1, 5}, 6},
	{"Box1", {4, 2, 2}, 4},
	{"Box2", {1, 1, 1}, 4},
	{"Box3", {4, 2, 4}, 3},
	{"Box4", {2, 2, 3}, 1},
	{"Box5", {1, 3, 5}, 2},
};

TEST(Entry, sort)
{
	auto sorted_packages1 {packages};

	std::sort(sorted_packages1.begin(), sorted_packages1.end(), lessByTask);

	const std::vector<Package> expected {
		{"Box4", {2, 2, 3}, 1}, 
		{"Box5", {1, 3, 5}, 2}, 
		{"Box3", {4, 2, 4}, 3},
		{"Box2", {1, 1, 1}, 4},
		{"Box0", {2, 1, 5}, 6},
		{"Box1", {4, 2, 2}, 4},
	};

	ASSERT_TRUE(expected == sorted_packages1);
}

TEST(Entry, sort_my_container)
{
	auto sorted_packages2 {packages};

	mySortContainer(sorted_packages2);

	const std::vector<Package> expected {
		{"Box1", {4, 2, 2}, 4},
		{"Box0", {2, 1, 5}, 6},
		{"Box2", {1, 1, 1}, 4},
		{"Box3", {4, 2, 4}, 3},
		{"Box5", {1, 3, 5}, 2},
		{"Box4", {2, 2, 3}, 1},
	};

	ASSERT_TRUE(expected == sorted_packages2);
}

TEST(Entry, sort_array)
{
	const size_t ARR_SIZE = 9;
	int array[ARR_SIZE] {1,8,7,2,5,9,3,5,1};

	mySortContainer(array);

	const int expected[ARR_SIZE] {9,8,7,5,5,3,2,1,1};

	ASSERT_TRUE(std::vector<int>(expected, expected + ARR_SIZE) == std::vector<int>(array, array + ARR_SIZE));
}


int main(int argc, char **argv)
{
	printf("Running main() from Entry_gTest.cpp\n");

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
